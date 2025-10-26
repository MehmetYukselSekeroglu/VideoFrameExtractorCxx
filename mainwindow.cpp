#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , videoProcessor(new VideoProcessor(this))
{
    ui->setupUi(this);
    setupConnections();

    // Varsayılan çıktı dizini
    ui->lineEdit_output_dir->setText("tmp/cv2output");

    // Progress bar'ı başlangıçta sıfırla
    ui->progressBar_status_bar->setValue(0);
    ui->progressBar_status_bar->setMinimum(0);

    // Timer for progress bar animation (optional)
    progressTimer = new QTimer(this);
    connect(progressTimer, &QTimer::timeout, this, &MainWindow::updateProgressAnimation);
}

MainWindow::~MainWindow()
{
    if(progressTimer && progressTimer->isActive()) {
        progressTimer->stop();
    }
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(videoProcessor, &VideoProcessor::progressUpdated, this, &MainWindow::onProgressUpdated);
    connect(videoProcessor, &VideoProcessor::finished, this, &MainWindow::onFinished);
    connect(videoProcessor, &VideoProcessor::errorOccurred, this, &MainWindow::onErrorOccurred);
    connect(videoProcessor, &VideoProcessor::logMessage, this, &MainWindow::onLogMessage);
    connect(videoProcessor, &VideoProcessor::totalFramesDetected, this, &MainWindow::onTotalFramesDetected);
}

void MainWindow::on_pushButton_select_video_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Video Dosyası Seç", "",
                                                    "Video Files (*.mp4 *.avi *.mov *.mkv *.wmv *.flv *.mpeg *.mpg);;All Files (*.*)");

    if(!fileName.isEmpty()) {
        ui->lineEdit_input_video->setText(fileName);
        // Video seçildiğinde çıktı dizinini otomatik ayarla
        QFileInfo fileInfo(fileName);
        QString autoOutputDir = QString("output_%1").arg(fileInfo.baseName());
        ui->lineEdit_output_dir->setText(autoOutputDir);

        addLogWithTimestamp("Video seçildi: " + fileName);
    }
}

void MainWindow::on_pushButton_select_output_dir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                                    "Çıktı Dizinini Seç", "",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty()) {
        ui->lineEdit_output_dir->setText(dir);
        addLogWithTimestamp("Çıktı dizini seçildi: " + dir);
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    if(ui->lineEdit_input_video->text().isEmpty()) {
        QMessageBox::warning(this, "Uyarı", "Lütfen bir video dosyası seçin!");
        return;
    }

    if(!QFile::exists(ui->lineEdit_input_video->text())) {
        QMessageBox::critical(this, "Hata", "Seçilen video dosyası bulunamadı!");
        return;
    }

    videoProcessor->setVideoPath(ui->lineEdit_input_video->text());
    videoProcessor->setOutputDir(ui->lineEdit_output_dir->text());

    ui->pushButton_start->setEnabled(false);
    ui->pushButton_stop->setEnabled(true);
    ui->progressBar_status_bar->setValue(0);

    // Clear previous logs but keep initial message
    ui->textBrowser_output->clear();

    addLogWithTimestamp("Video ayrıştırma işlemi başlatılıyor...");
    addLogWithTimestamp(QString("Kaynak: %1").arg(ui->lineEdit_input_video->text()));
    addLogWithTimestamp(QString("Hedef: %1").arg(ui->lineEdit_output_dir->text()));

    // Start progress animation
    if(progressTimer) {
        progressTimer->start(100); // Update every 100ms
    }

    videoProcessor->start();
}

void MainWindow::on_pushButton_stop_clicked()
{
    addLogWithTimestamp("Kullanıcı tarafından durduruluyor...");
    videoProcessor->stopProcessing();
    ui->pushButton_stop->setEnabled(false);

    if(progressTimer && progressTimer->isActive()) {
        progressTimer->stop();
    }
}

void MainWindow::onProgressUpdated(int frameNumber)
{
    // Progress bar'ı güncelle
    if(totalFrames > 0) {
        int progress = static_cast<int>((static_cast<double>(frameNumber) / totalFrames) * 100);
        ui->progressBar_status_bar->setValue(progress);
    } else {
        // Eğer toplam frame bilinmiyorsa, sadece frame numarasını göster
        ui->progressBar_status_bar->setValue(frameNumber % 100); // 0-99 arası döngü
    }

    // Her 100 frame'de bir detaylı log ekle
    if(frameNumber % 100 == 0 && frameNumber > 0) {
        QString speedInfo = "";
        if(!lastFrameTime.isNull()) {
            qint64 elapsed = lastFrameTime.msecsTo(QTime::currentTime());
            if(elapsed > 0) {
                double framesPerSecond = 100000.0 / elapsed; // 100 frame için FPS
                speedInfo = QString(" | Hız: %1 fps").arg(framesPerSecond, 0, 'f', 1);
            }
        }
        lastFrameTime = QTime::currentTime();

        QString percentInfo = "";
        if(totalFrames > 0) {
            double percent = (static_cast<double>(frameNumber) / totalFrames) * 100.0;
            percentInfo = QString(" | %%%1").arg(percent, 0, 'f', 1);
        }

        addLogWithTimestamp(QString("✓ %1. kare işlendi%2%3")
                                .arg(frameNumber)
                                .arg(percentInfo)
                                .arg(speedInfo));
    }
}

void MainWindow::onFinished()
{
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
    ui->progressBar_status_bar->setValue(100);

    addLogWithTimestamp("✓ Video ayrıştırma işlemi başarıyla tamamlandı!");

    if(progressTimer && progressTimer->isActive()) {
        progressTimer->stop();
    }
}

void MainWindow::onErrorOccurred(const QString &error)
{
    QMessageBox::critical(this, "Hata", error);
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);

    addLogWithTimestamp("✗ HATA: " + error);

    if(progressTimer && progressTimer->isActive()) {
        progressTimer->stop();
    }
}

void MainWindow::onLogMessage(const QString &message)
{
    addLogWithTimestamp(message);
}

void MainWindow::onTotalFramesDetected(int frames)
{
    totalFrames = frames;
    addLogWithTimestamp(QString("Video analiz edildi: Toplam %1 kare tespit edildi").arg(frames));
    ui->progressBar_status_bar->setMaximum(100); // Yüzde bazında ilerleme
}

void MainWindow::addLogWithTimestamp(const QString &message)
{
    QString timestamp = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    ui->textBrowser_output->append(QString("[%1] %2").arg(timestamp, message));

    // Scroll to bottom automatically
    QTextCursor cursor = ui->textBrowser_output->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textBrowser_output->setTextCursor(cursor);
}

void MainWindow::updateProgressAnimation()
{
    // Progress bar animasyonu (sadece toplam frame bilinmediğinde)
    if(totalFrames == 0) {
        int currentValue = ui->progressBar_status_bar->value();
        currentValue = (currentValue + 1) % 100;
        ui->progressBar_status_bar->setValue(currentValue);
    }
}
