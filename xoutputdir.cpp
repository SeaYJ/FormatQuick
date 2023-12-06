#include "xoutputdir.h"

#include <QDebug>

XOutputDir::XOutputDir(QWidget *parent)
    :QLineEdit(parent)
{
    connect(this, &QLineEdit::editingFinished, this, &XOutputDir::checkFilePath);
}

XOutputDir::~XOutputDir()
{

}

void XOutputDir::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        QString OutputDir = QFileDialog::getExistingDirectory(
            this,
            QString(tr("选择输出路径")),
            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/",
            QFileDialog::ShowDirsOnly);

        // 这里要判断文件夹是否存在
        // 当用户取消本次选择时，可能会出现路径不存在问题
        QFileInfo OutputDirInfo(OutputDir);
        if (OutputDirInfo.isDir())
            this->setText(OutputDir + "/");
    }

    // 保留默认双击事件
    QLineEdit::mouseDoubleClickEvent(e);
}

void XOutputDir::checkFilePath()
{
    // 暂时禁用 editingFinished 信号
    // 防止用户一次回车等特殊操作连续触发多次 editingFinished 信号，导致该函数被连续调用多次
    blockSignals(true);

    QString FilePath = this->text();
    QDir Dir(FilePath);
    QMessageBox ErrMsgBox;
    QPushButton* CreateDirBtn = ErrMsgBox.addButton(QString(tr("立即创建")), QMessageBox::YesRole);
    QPushButton* IgnoreBtn = ErrMsgBox.addButton(QString(tr("暂时忽略")), QMessageBox::YesRole);
    QString ErrMsgBoxTitle = QString(tr("错误"));
    QString ErrMsgBoxContent = QString("");

    // 检查文件路径是否存在
    if (!Dir.exists()) {
        // 文件路径不存在，询问是否创建文件夹
        ErrMsgBoxContent = QString(tr("文件路径：") + FilePath + tr("\t不存在！\n请问是否需要立即创建该文件夹？"));

        ErrMsgBox.setIcon(QMessageBox::Warning);
        ErrMsgBox.setWindowTitle(ErrMsgBoxTitle);
        ErrMsgBox.setText(ErrMsgBoxContent);
        ErrMsgBox.exec();

        if (ErrMsgBox.clickedButton() == CreateDirBtn)
        {
            // 使用 QDir 立即创建文件路径
            if (Dir.mkpath(FilePath)) {
                qDebug() << "Folder created successfully using QDir.";
            } else {
                qDebug() << "Failed to create folder using QDir.";
            }
        }
        else if (ErrMsgBox.clickedButton() == IgnoreBtn)
        {
            // 忽略
        }
    }

    // 恢复信号
    blockSignals(false);
}

