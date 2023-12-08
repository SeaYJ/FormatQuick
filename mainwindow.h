#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// 设置 UTF-8 编码
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QLayout>
#include <QGroupBox>
#include <QTabWidget>
#include <QTabBar>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QTableView>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QListView>
#include <QModelIndex>
#include <QMessageBox>
#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include <QDebug>

#include "formatmonitor.h"
#include "ffmpegconverter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    Ui::MainWindow *ui;
    const unsigned int MainWindowDefaultSize_Width = 1200;
    const unsigned int MainWindowDefaultSize_Height = 900;
    const unsigned int LayoutSpacing = 10;
    const char* AppName_Chinese = "快影格式";
    const char* AppName_English = "FormatQuick";

    // 定义一下常量，增加可读性
    // 替换页面的索引 int 值
    const unsigned int CurrentWidgetIsImage = 0;
    const unsigned int CurrentWidgetIsAudio = 1;
    const unsigned int CurrentWidgetIsVideo = 2;

    // 代表当前所在页面索引
    // 此变量保持实时更新
    // 默认在 0 号页面
    unsigned int CurrentWidgetIndex = 0;

    // 默认输出路径
    const QString DefaultOutputDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + AppName_English + "/";

    void InitUI();
    void InitConnect();
    void AddTasksToList(QList<QString>& urls);

    QGroupBox* MainGroup;
    QGroupBox* InfoGroup;

    QStandardItemModel* IReadListViewDataModel;
    QStandardItemModel* AReadListViewDataModel;
    QStandardItemModel* VReadListViewDataModel;

    void ReadFilesAndAddToTasks(const QString& Title, QStandardPaths::StandardLocation Location, const QString& FileFilter);
    void UpdateTaskOutputFormat(QTableView* TableView, QAbstractItemModel* DataModel, const QString &arg1);
    void DeleteSelectedTaskRows(QTableView* TableView, QAbstractItemModel* DataModel);
    void DeleteAllTaskRows(QAbstractItemModel* DataModel);

    FFMpegConverter FFMpegConverter;
    QFuture<bool> IConvertThread;
    QFuture<bool> AConvertThread;
    QFuture<bool> VConvertThread;

    bool StartImageConversion();
    bool StartAudioConversion();
    bool StartVideoConversion();
};

#endif // MAINWINDOW_H
