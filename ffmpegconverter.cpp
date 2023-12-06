#include "ffmpegconverter.h"

FFMpegConverter::FFMpegConverter(QObject *parent)
    : QObject{parent}
{

}

bool FFMpegConverter::ConvertImage(const QString &inputFile, const QString &outputFile)
{
    qDebug() << "子线程开始执行转换！IMAGE!";
    QThread::sleep(1000);
    return RunFFMpegCommand("ffmpeg -i " + inputFile + " " + outputFile);
}

bool FFMpegConverter::ConvertAudio(const QString &inputFile, const QString &outputFile)
{
    qDebug() << "子线程开始执行转换！AUDIO!";
    QThread::sleep(1000);
    return RunFFMpegCommand("ffmpeg -i " + inputFile + " " + outputFile);
}

bool FFMpegConverter::ConvertVideo(const QString &inputFile, const QString &outputFile)
{
    qDebug() << "子线程开始执行转换！VIDEO!";
    QThread::sleep(1000);
    return RunFFMpegCommand("ffmpeg -i " + inputFile + " " + outputFile);
}

bool FFMpegConverter::RunFFMpegCommand(const QString &Command)
{
    QProcess process;
    process.setProgram("ffmpeg");
    process.setArguments(Command.split(' '));
    process.start();
    process.waitForFinished(-1);

    // 将ffmpeg的输出写入日志文件
    QFile logFile("log.txt");
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << process.readAllStandardOutput() << "\n";
        logFile.close();
    }

    // 从日志文件中读取ffmpeg输出，判断转换是否成功
    return CheckConversionResult();
}

bool FFMpegConverter::CheckConversionResult()
{
    QFile logFile("log.txt");
    if (logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&logFile);
        QString logContent = in.readAll();
        logFile.close();

        // 在这里根据ffmpeg输出的日志内容判断转换结果，可以根据具体情况来设计
        // 例如，检查是否包含关键字 "Error" 表示转换失败
        if (logContent.contains("Error")) {
            qDebug() << "Conversion failed.";
            return false;
        } else {
            qDebug() << "Conversion succeeded.";
            return true;
        }
    }

    return false;
}
