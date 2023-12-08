#ifndef FFMPEGCONVERTER_H
#define FFMPEGCONVERTER_H
// 设置 UTF-8 编码
#pragma execution_character_set("utf-8")

#include <QObject>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDateTime>

#include <QThread>
#include <QDebug>

//#include "formatmonitor.h"

class FFMpegConverter : public QObject
{
    Q_OBJECT
public:
    explicit FFMpegConverter(QObject *parent = nullptr);

    // 图片格式转换
    bool ConvertImage(const QString &inputFile, const QString &outputFile);

    // 音频格式转换
    bool ConvertAudio(const QString &inputFile, const QString &outputFile);

    // 视频格式转换
    bool ConvertVideo(const QString &inputFile, const QString &outputFile);

signals:

private:
    bool RunFFMpegCommand(const QStringList &CommandList);
};

#endif // FFMPEGCONVERTER_H
