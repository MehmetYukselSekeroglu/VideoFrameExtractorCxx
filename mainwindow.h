#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "VideoProcessor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_select_video_clicked();
    void on_pushButton_select_output_dir_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_stop_clicked();

    void onProgressUpdated(int frameNumber);
    void onFinished();
    void onErrorOccurred(const QString &error);
    void onLogMessage(const QString &message);
    void onTotalFramesDetected(int frames);

private:
    Ui::MainWindow *ui;
    VideoProcessor *videoProcessor;
    QTimer *progressTimer = nullptr;
    QTime lastFrameTime;
    int totalFrames = 0;

    void setupConnections();
    void addLogWithTimestamp(const QString &message);
    void updateProgressAnimation();
};
#endif // MAINWINDOW_H
