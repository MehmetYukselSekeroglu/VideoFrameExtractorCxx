#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <QDir>
#include <QDebug>

class VideoProcessor : public QThread
{
    Q_OBJECT

public:
    explicit VideoProcessor(QObject *parent = nullptr);
    void setVideoPath(const QString &path);
    void setOutputDir(const QString &dir);
    void stopProcessing();

protected:
    void run() override;

private:
    QString videoPath;
    QString outputDir;
    bool stopRequested = false;

    void clearOutputDirectory();

signals:
    void progressUpdated(int frameNumber);
    void finished();
    void errorOccurred(const QString &error);
    void logMessage(const QString &message);
    void totalFramesDetected(int frames); // YENİ SİNYAL

};

#endif // VIDEOPROCESSOR_H
