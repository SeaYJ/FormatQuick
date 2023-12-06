#ifndef FORMATMONITOR_H
#define FORMATMONITOR_H
// 设置 UTF-8 编码
#pragma execution_character_set("UTF-8")

#include <QString>
#include <QList>

typedef enum FROMAT_TYPE{
    IMAGE = 0,
    AUDIO = 1,
    VIDEO = 2
} FTYPE;

class FormatMonitor
{
public:
    FormatMonitor();

    FTYPE format(const QString ftype);
    bool isImage(const QString ftype);
    bool isAudio(const QString ftype);
    bool isVideo(const QString ftype);

    static const QStringList IFTypeList;
    static const QStringList AFTypeList;
    static const QStringList VFTypeList;

    // 注意
    // 这三个静态长量的初始化需要根据对应的 XFTypeList 变量值来确定
    static const QString ISupportFormatStr;
    static const QString ASupportFormatStr;
    static const QString VSupportFormatStr;
};


#endif // FORMATMONITOR_H
