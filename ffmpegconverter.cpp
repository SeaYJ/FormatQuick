#include "ffmpegconverter.h"

FFMpegConverter::FFMpegConverter(QObject *parent)
    : QObject{parent}
{

}

bool FFMpegConverter::ConvertImage(const QString &inputFile, const QString &outputFile)
{
    QStringList CommandList;
    CommandList << "-i"
                << inputFile
                << "-y"
                << outputFile;
    return RunFFMpegCommand(CommandList);
}

bool FFMpegConverter::ConvertAudio(const QString &inputFile, const QString &outputFile)
{
    QStringList CommandList;
    CommandList << "-i"
                << inputFile
                << "-y"
                << outputFile;
    return RunFFMpegCommand(CommandList);
}

bool FFMpegConverter::ConvertVideo(const QString &inputFile, const QString &outputFile)
{
    QStringList CommandList;
    CommandList << "-i"
                << inputFile
                << "-y"
                << outputFile;
    return RunFFMpegCommand(CommandList);
}

bool FFMpegConverter::RunFFMpegCommand(const QStringList &CommandList)
{
    QProcess FFMpegProcess;
    QString FFMpegPath = QCoreApplication::applicationDirPath() + "/bin/ffmpeg.exe";

    FFMpegProcess.start(FFMpegPath, CommandList);
    FFMpegProcess.waitForFinished(-1);

    if (FFMpegProcess.exitCode() == 0)
    {
        return true;
    }
    else
    {
        QString ErrorTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QFile logFile("log.txt");
        if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(&logFile);
            out << "----- STRAT LOG " << ErrorTime << " -----" << "\n"
                << "Error executing FFMpeg command. Exit code:" << FFMpegProcess.exitCode() << "\n"
                << "Error details:" << FFMpegProcess.readAllStandardError() << "\n"
                << "----- END LOG " << ErrorTime << " -----" << "\n\n\n";
            logFile.close();
        }
        return false;
    }
}
