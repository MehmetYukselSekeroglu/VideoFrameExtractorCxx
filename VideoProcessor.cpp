#include "VideoProcessor.h"

VideoProcessor::VideoProcessor(QObject *parent) : QThread(parent)
{
}

void VideoProcessor::setVideoPath(const QString &path)
{
    videoPath = path;
}

void VideoProcessor::setOutputDir(const QString &dir)
{
    outputDir = dir;
}

void VideoProcessor::stopProcessing()
{
    stopRequested = true;
}

void VideoProcessor::run()
{
    stopRequested = false;

    if(videoPath.isEmpty()) {
        emit errorOccurred("Video dosyası seçilmedi!");
        return;
    }

    // Çıktı dizinini temizle

    // VideoProcessor::run() fonksiyonunda video açıldıktan sonra:
    cv::VideoCapture video(videoPath.toStdString());
    if(!video.isOpened()) {
        emit errorOccurred("Video açılamadı: " + videoPath);
        return;
    }

    // Toplam frame sayısını al ve sinyal gönder
    int totalFrames = static_cast<int>(video.get(cv::CAP_PROP_FRAME_COUNT));
    double fps = video.get(cv::CAP_PROP_FPS);
    emit totalFramesDetected(totalFrames);
    emit logMessage(QString("Video bilgileri: %1 kare, %2 FPS").arg(totalFrames).arg(fps));
    int frameNumber = 0;
    cv::Mat frame;

    emit logMessage("Video kareleri ayrıştırılıyor...");

    while(!stopRequested) {
        if(!video.read(frame)) {
            break;
        }

        QString filename = QString("%1/frame_%2.jpg").arg(outputDir).arg(frameNumber);
        if(!cv::imwrite(filename.toStdString(), frame)) {
            emit errorOccurred("Frame kaydedilemedi: " + filename);
            break;
        }

        emit progressUpdated(frameNumber);
        frameNumber++;
    }

    video.release();

    if(stopRequested) {
        emit logMessage("İşlem kullanıcı tarafından durduruldu");
    } else {
        emit logMessage(QString("İşlem tamamlandı! Toplam % kare ayrıştırıldı").arg(frameNumber));
    }

    emit finished();
}
