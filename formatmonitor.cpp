#include "formatmonitor.h"

const QStringList FormatMonitor::IFTypeList = {
    "AVIF",
    "BMP",
    "EXR",
    "GIF",
    "HDR",
    "ICO",
    "JP2", "JPEG", "JPG",
    "PBM", "PCX", "PFM", "PGM", "PIX", "PNG", "PPM",
    "RAS", "RGB",
    "SGI", "SUN",
    "TGA", "TIFF",
    "WBMP", "WEBP",
    "XBM", "XWD",
    "YUV"
};
const QStringList FormatMonitor::AFTypeList = {
    "AAC", "AC3", "AIFF", "AMR", "AU",
    "CAF",
    "DTS",
    "FLAC",
    "GSM",
    "IRCAM",
    "M4A", "MP2", "MP3",
    "OGA", "OGG", "OPUS",
    "RA",
    "SPX",
    "TTA",
    "VOC",
    "W64", "WAV", "WMA", "WV"
};
const QStringList FormatMonitor::VFTypeList = {
    "3G2", "3GP",
    "ASF", "AVI",
    "DV",
    "F4V", "FLV",
    "HEVC",
    "M2TS", "M2V", "M4V", "MJPEG", "MKV", "MOV", "MP4", "MPEG", "MPG", "MTS", "MXF",
    "OGV",
    "RM",
    "SWF",
    "TS",
    "VOB",
    "WTV"
};

const QString FormatMonitor::ISupportFormatStr =
    QString("*.avif ")+
    QString("*.bmp ")+
    QString("*.exr ")+
    QString("*.gif ")+
    QString("*.hdr ")+
    QString("*.ico ")+
    QString("*.jp2 ")+ QString("*.jpeg ")+ QString("*.jpg ")+
    QString("*.pbm ")+ QString("*.pcx ")+ QString("*.pfm ")+ QString("*.pgm ")+ QString("*.pix ")+ QString("*.png ")+ QString("*.ppm ")+
    QString("*.ras ")+ QString("*.rgb ")+
    QString("*.sgi ")+ QString("*.sun ")+
    QString("*.tga ")+ QString("*.tiff ")+
    QString("*.wbmp ")+ QString("*.webp ")+
    QString("*.xbm ")+ QString("*.xwd ")+
    QString("*.yuv");

const QString FormatMonitor::ASupportFormatStr =
    QString("*.aac ")+ QString("*.ac3 ")+ QString("*.aiff ")+ QString("*.amr ")+ QString("*.au ")+
    QString("*.caf ")+
    QString("*.dts ")+
    QString("*.flac ")+
    QString("*.gsm ")+
    QString("*.ircam ")+
    QString("*.m4a ")+ QString("*.mp2 ")+ QString("*.mp3 ")+
    QString("*.oga ")+ QString("*.ogg ")+ QString("*.opus ")+
    QString("*.ra ")+
    QString("*.spx ")+
    QString("*.tta ")+
    QString("*.voc ")+
    QString("*.w64 ")+ QString("*.wav ")+ QString("*.wma ")+ QString("*.wv");

const QString FormatMonitor::VSupportFormatStr =
    QString("*.3g2 ")+ QString("*.3gp ")+
    QString("*.asf ")+ QString("*.avi ")+
    QString("*.dv ")+
    QString("*.f4v ")+ QString("*.flv ")+
    QString("*.hevc ")+
    QString("*.m2ts ")+ QString("*.m2v ")+ QString("*.m4v ")+ QString("*.mjpeg ")+ QString("*.mkv ")+ QString("*.mov ")+ QString("*.mp4 ")+ QString("*.mpeg ")+ QString("*.mpg ")+ QString("*.mts ")+ QString("*.mxf ")+
    QString("*.ogv ")+
    QString("*.rm ")+
    QString("*.swf ")+
    QString("*.ts ")+
    QString("*.vob ")+
    QString("*.wtv");

FormatMonitor::FormatMonitor()
{
}

bool FormatMonitor::isImage(const QString ftype)
{
    return FormatMonitor::IFTypeList.contains(ftype);
}

bool FormatMonitor::isAudio(const QString ftype)
{
    return FormatMonitor::AFTypeList.contains(ftype);
}

bool FormatMonitor::isVideo(const QString ftype)
{
    return FormatMonitor::VFTypeList.contains(ftype);
}
