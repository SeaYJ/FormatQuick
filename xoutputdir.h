#ifndef XOUTPUTDIR_H
#define XOUTPUTDIR_H
// 设置 UTF-8 编码
#pragma execution_character_set("UTF-8")

#include <QObject>
#include <QLineEdit>
#include <QMouseEvent>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>
#include <QPushButton>

#include <QDebug>
class XOutputDir : public QLineEdit
{
    Q_OBJECT
public:
    explicit XOutputDir(QWidget *parent = 0);
    ~XOutputDir();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *e);

private slots:
    void checkFilePath();

};

#endif // XOUTPUTDIR_H
