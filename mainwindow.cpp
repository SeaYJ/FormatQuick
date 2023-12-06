#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formatmonitor.h"
#include "xoutputdir.h"
#include "ffmpegconverter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化主窗口界面
    InitUI();
    // 初始化信号连接
    InitConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if(mimeData->hasUrls())
    {
        QList<QUrl> urls_t = mimeData->urls();

        // mimeData->urls() 返回的数据类型不能直接使用，
        // 需要将其转换成一个字符串类型的路径
        QList<QString> urls;
        for (int i = 0; i < urls_t.size(); i++)
        {
            urls.append(urls_t.at(i).toLocalFile());
        }

        AddTasksToList(urls);
    }
}

bool MainWindow::StartImageConversion()
{
    // 从 QStandardItemModel 中获取参数
//    QModelIndex index = IReadListViewDataModel->index(0, 0); // 假设参数在第一行第一列
    QString inputFile = "";
    QString outputFile = "";

    // 调用 FFMpegConverter 类的 ConvertImage 函数
    return FFMpegConverter.ConvertImage(inputFile, outputFile);
}

void MainWindow::InitUI()
{
    // 设置主窗口标题
    setWindowTitle(QString(tr(AppName_Chinese)));
    QSize MainWindowDefaultSize(MainWindowDefaultSize_Width, MainWindowDefaultSize_Height);
    resize(MainWindowDefaultSize);
    setFixedSize(MainWindowDefaultSize);

    // 接受拖拽事件
    setAcceptDrops(true);

    // 切换到默认页面
    ui->CtrlGroup->setCurrentIndex(CurrentWidgetIndex);

    // 对输入列表 TabView 进行设置
    QStringList TabViewHorizontalHeaders;
    TabViewHorizontalHeaders << "状态"
                             << "文件名"
                             << "文件格式"
                             << "目标格式"
                             << "文件绝对路径";
    ui->IReadListView->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 设置不允许编辑
    ui->AReadListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->VReadListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *IHearView = new QHeaderView(Qt::Horizontal);
    QHeaderView *AHearView = new QHeaderView(Qt::Horizontal);
    QHeaderView *VHearView = new QHeaderView(Qt::Horizontal);

    IReadListViewDataModel = new QStandardItemModel();
    AReadListViewDataModel = new QStandardItemModel();
    VReadListViewDataModel = new QStandardItemModel();

    IReadListViewDataModel->setHorizontalHeaderLabels(TabViewHorizontalHeaders);
    AReadListViewDataModel->setHorizontalHeaderLabels(TabViewHorizontalHeaders);
    VReadListViewDataModel->setHorizontalHeaderLabels(TabViewHorizontalHeaders);

    IHearView->setModel(IReadListViewDataModel);
    AHearView->setModel(AReadListViewDataModel);
    VHearView->setModel(VReadListViewDataModel);

    IHearView->setSectionResizeMode(QHeaderView::Interactive);           // 设置用户可调节列宽度
    AHearView->setSectionResizeMode(QHeaderView::Interactive);
    VHearView->setSectionResizeMode(QHeaderView::Interactive);

    IHearView->setSectionResizeMode(0, QHeaderView::ResizeToContents);   // 设置第一列自适应内容
    AHearView->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    VHearView->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    IHearView->setSectionResizeMode(4, QHeaderView::ResizeToContents);   // 设置文件绝对路径列自适应内容
    AHearView->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    VHearView->setSectionResizeMode(4, QHeaderView::ResizeToContents);

    ui->IReadListView->setHorizontalHeader(IHearView);
    ui->AReadListView->setHorizontalHeader(AHearView);
    ui->VReadListView->setHorizontalHeader(VHearView);

    ui->IReadListView->setAlternatingRowColors(true); //隔行变色
    ui->AReadListView->setAlternatingRowColors(true);
    ui->VReadListView->setAlternatingRowColors(true);

    // “输出路径”相关设置
    ui->IOutputDir->setText(DefaultOutputDir);
    ui->AOutputDir->setText(DefaultOutputDir);
    ui->VOutputDir->setText(DefaultOutputDir);

    // “统一设置输出格式”设置列表项
    ui->IOutputFormat->addItems(FormatMonitor::IFTypeList);
    ui->AOutputFormat->addItems(FormatMonitor::AFTypeList);
    ui->VOutputFormat->addItems(FormatMonitor::VFTypeList);

    ui->IOutputFormat->setView(new QListView());        // 使之允许修改高度，高度在 StyleSheet 中定义
    ui->AOutputFormat->setView(new QListView());
    ui->VOutputFormat->setView(new QListView());

    ui->IOutputFormat->setCurrentText(QString("JPG"));  // 设置默认“统一格式”
    ui->AOutputFormat->setCurrentText(QString("MP3"));
    ui->VOutputFormat->setCurrentText(QString("MP4"));
}

void MainWindow::InitConnect()
{
    // 切换页面时触发，确保变量 CurrentWidgetIndex 始终指向对应的页面
    connect(ui->CtrlGroup, &QTabWidget::currentChanged, this, [=](int index){
        CurrentWidgetIndex = index;
    });

    // 导入文件按钮
    // 图片页
    connect(ui->IFileReadBtn, &QPushButton::clicked, this, [=]() {
        ReadFilesAndAddToTasks(QString(tr("选择图片文件")), QStandardPaths::PicturesLocation, QString(tr("图片文件(") + FormatMonitor::ISupportFormatStr + tr(");;所有文件(*.*)")));
    });
    // 音频页
    connect(ui->AFileReadBtn, &QPushButton::clicked, this, [=]() {
        ReadFilesAndAddToTasks(QString(tr("选择音频文件")), QStandardPaths::MusicLocation, QString(tr("音频文件(") + FormatMonitor::ASupportFormatStr + tr(");;所有文件(*.*)")));
    });
    // 视频页
    connect(ui->VFileReadBtn, &QPushButton::clicked, this, [=]() {
        ReadFilesAndAddToTasks(QString(tr("选择视频文件")), QStandardPaths::MoviesLocation, QString(tr("视频文件(") + FormatMonitor::VSupportFormatStr + tr(");;所有文件(*.*)")));
    });

    // 统一设置输出格式
    // 图片页
    connect(ui->IOutputFormat, &QComboBox::currentTextChanged, this, [=](const QString &arg1) {
        UpdateTaskOutputFormat(ui->IReadListView, IReadListViewDataModel, arg1);
    });
    // 音频页
    connect(ui->AOutputFormat, &QComboBox::currentTextChanged, this, [=](const QString &arg1) {
        UpdateTaskOutputFormat(ui->AReadListView, AReadListViewDataModel, arg1);
    });
    // 视频页
    connect(ui->VOutputFormat, &QComboBox::currentTextChanged, this, [=](const QString &arg1) {
        UpdateTaskOutputFormat(ui->VReadListView, VReadListViewDataModel, arg1);
    });

    // 删除选中任务
    // 图片页
    connect(ui->IDelOneTaskBtn, &QPushButton::clicked, this, [=]() {
        DeleteSelectedTaskRows(ui->IReadListView, IReadListViewDataModel);
    });
    // 音频页
    connect(ui->ADelOneTaskBtn, &QPushButton::clicked, this, [=]() {
        DeleteSelectedTaskRows(ui->AReadListView, AReadListViewDataModel);
    });
    // 视频页
    connect(ui->VDelOneTaskBtn, &QPushButton::clicked, this, [=]() {
        DeleteSelectedTaskRows(ui->VReadListView, VReadListViewDataModel);
    });

    // 清空全部任务
    // 图片页
    connect(ui->IDelAllTaskBtn, &QPushButton::clicked, this, [=]() {
        DeleteAllTaskRows(IReadListViewDataModel);
    });
    // 音频页
    connect(ui->ADelAllTaskBtn, &QPushButton::clicked, this, [=]() {
        DeleteAllTaskRows(AReadListViewDataModel);
    });
    // 视频页
    connect(ui->VDelAllTaskBtn, &QPushButton::clicked, this, [=]() {
        DeleteAllTaskRows(VReadListViewDataModel);
    });

    // 任务执行相关
    connect(ui->IStartTaskBtn, &QPushButton::clicked, this, [=]() {
        qDebug() << "开始执行任务！";
        // 处理一下线程退出问题！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
        IConvertThread = QtConcurrent::run(this, &MainWindow::StartImageConversion);
    });
    connect(ui->IEndTaskBtn, &QPushButton::clicked, this, [=]() {
        qDebug() << "结束执行任务！";
    });

}

void MainWindow::InitTheard()
{
}

void MainWindow::AddTasksToList(QList<QString> &urls)
{
    QMessageBox ErrMsgBox;
    QPushButton* IgnoreAllBtn = ErrMsgBox.addButton(QString(tr("忽略全部")), QMessageBox::YesRole);
    QPushButton* IgnoreBtn = ErrMsgBox.addButton(QString(tr("忽略此项")), QMessageBox::YesRole);
    QPushButton* ExitBtn = ErrMsgBox.addButton(QString(tr("终止加载")), QMessageBox::YesRole);
    bool IgnoreAllFlag = false;
    QString ErrMsgBoxTitle = QString(tr("错误"));
    QString ErrMsgBoxContent = QString("");

    // 断定单个文件格式是否符合当前页面指定格式
    bool FormatMatchFlag = false;

    // 创建文件格式监视器对象，进行过滤格式工作
    FormatMonitor* FMonitor = new FormatMonitor();

    for (int i = 0; i < urls.size(); i++)
    {
        QFileInfo FileInfo(urls.at(i));

        // 如果拖入的文件格式不符合当前页面支持的格式，就拦截！
        if (CurrentWidgetIndex == CurrentWidgetIsImage)
        {
            if (!(FMonitor->isImage(FileInfo.suffix().toUpper())))
            {
                FormatMatchFlag = false;
                ErrMsgBoxContent = QString(FileInfo.absoluteFilePath() + tr("\n不是一张图片！"));
            }
            else
            {
                FormatMatchFlag = true;
            }
        }
        else if (CurrentWidgetIndex == CurrentWidgetIsAudio)
        {
            if (!(FMonitor->isAudio(FileInfo.suffix().toUpper())))
            {
                FormatMatchFlag = false;
                ErrMsgBoxContent = QString(FileInfo.absoluteFilePath() + tr("\n不是一个音频！"));
            }
            else
            {
                FormatMatchFlag = true;
            }
        }
        else if (CurrentWidgetIndex == CurrentWidgetIsVideo)
        {
            if (!(FMonitor->isVideo(FileInfo.suffix().toUpper())))
            {
                FormatMatchFlag = false;
                ErrMsgBoxContent = QString(FileInfo.absoluteFilePath() + tr("\n不是一个视频！"));
            }
            else
            {
                FormatMatchFlag = true;
            }
        }

        // 单个文件格式不符合当前页面指定格式，并且已经选择“忽略全部”
        if (IgnoreAllFlag && !FormatMatchFlag)
        {
            continue;
        }

        // 单个文件格式不符合当前页面指定格式，但是未选择“忽略全部”
        if (!IgnoreAllFlag && !FormatMatchFlag)
        {
            ErrMsgBox.setIcon(QMessageBox::Warning);
            ErrMsgBox.setWindowTitle(ErrMsgBoxTitle);
            ErrMsgBox.setText(ErrMsgBoxContent);
            ErrMsgBox.exec();

            if (ErrMsgBox.clickedButton() == IgnoreAllBtn)
            {
                IgnoreAllFlag = true;
                continue;
            }
            else if (ErrMsgBox.clickedButton() == IgnoreBtn)
            {
                continue;
            }
            else if (ErrMsgBox.clickedButton() == ExitBtn)
            {
                break;
            }
            else
            {
                continue;
            }
        }

        // 整合一条文件信息
        QList<QStandardItem *> newRowListViewData;
        newRowListViewData.append(new QStandardItem("未完成"));
        newRowListViewData.append(new QStandardItem(FileInfo.fileName()));
        newRowListViewData.append(new QStandardItem(FileInfo.suffix().toUpper()));

        if (CurrentWidgetIndex == CurrentWidgetIsImage)
            newRowListViewData.append(new QStandardItem(ui->IOutputFormat->currentText()));
        else if (CurrentWidgetIndex == CurrentWidgetIsAudio)
            newRowListViewData.append(new QStandardItem(ui->AOutputFormat->currentText()));
        else if (CurrentWidgetIndex == CurrentWidgetIsVideo)
            newRowListViewData.append(new QStandardItem(ui->VOutputFormat->currentText()));

        newRowListViewData.append(new QStandardItem(FileInfo.absoluteFilePath()));

        // 加入对应的页面
        if (CurrentWidgetIndex == CurrentWidgetIsImage)
        {
            IReadListViewDataModel->appendRow(newRowListViewData);
        }
        else if (CurrentWidgetIndex == CurrentWidgetIsAudio)
        {
            AReadListViewDataModel->appendRow(newRowListViewData);
        }
        else if (CurrentWidgetIndex == CurrentWidgetIsVideo)
        {
            VReadListViewDataModel->appendRow(newRowListViewData);
        }
    }

    // 对应页面进行刷新数据
    if (CurrentWidgetIndex == CurrentWidgetIsImage)
    {
        ui->IReadListView->setModel(IReadListViewDataModel);
    }
    else if (CurrentWidgetIndex == CurrentWidgetIsAudio)
    {
        ui->AReadListView->setModel(AReadListViewDataModel);
    }
    else if (CurrentWidgetIndex == CurrentWidgetIsVideo)
    {
        ui->VReadListView->setModel(VReadListViewDataModel);
    }

    delete FMonitor;
}

void MainWindow::ReadFilesAndAddToTasks(const QString &Title, QStandardPaths::StandardLocation Location, const QString &FileFilter)
{
    QList<QString> urls;

    QStringList FilesList = QFileDialog::getOpenFileNames(
        this,
        Title,
        QStandardPaths::writableLocation(Location),
        FileFilter);

    for (int i = 0; i < FilesList.size(); i++)
    {
        urls.append(FilesList[i]);
    }

    AddTasksToList(urls);
}

// “统一设置输出格式”设置时，遍历列表并修改
void MainWindow::UpdateTaskOutputFormat(QTableView *TableView, QAbstractItemModel *DataModel, const QString &arg1)
{
    // 如果没有数据就不用进行后面的逻辑了
    if (DataModel->rowCount() <= 0)
        return;

    // 如果有选中数据，那就只更改被选中的行数据
    QModelIndexList SelectedIndexes = TableView->selectionModel()->selectedIndexes();
    if (SelectedIndexes.count() <= 0)   // 没有选中数据，直接全部设置
    {
        for (int row = 0; row < DataModel->rowCount(); row++)
        {
            QModelIndex AlterIndex = DataModel->index(row, 3);
            DataModel->setData(AlterIndex, arg1);
        }
    }
    else                                // 存在被选中的数据，只对被选中的数据进行设置
    {
        for (int i = 0; i < SelectedIndexes.count(); i++)
        {
            QModelIndex AlterIndex = DataModel->index(SelectedIndexes.at(i).row(), 3);
            DataModel->setData(AlterIndex, arg1);
        }
    }
}

void MainWindow::DeleteSelectedTaskRows(QTableView *TableView, QAbstractItemModel *DataModel)
{
    QItemSelectionModel *SelectionModel = TableView->selectionModel();

    // 检查是否为空
    // 当数据为空时，TableView->selectionModel() 会返回一个空指针，进而导致程序的崩溃（没有该检查的话）！
    if (!SelectionModel)
        return;

    // 检查是否有选中的行
    if (!SelectionModel->hasSelection())
        return;

    // 获取当前选中的行
    QModelIndexList SelectedIndexes = SelectionModel->selectedRows();

    // 检查是否有选中的行
    if (SelectedIndexes.isEmpty())
        return;

    // 按照倒序的方式逐行删除选中的数据
    // 一定要倒序删除，正序删除会在选中很多行数据的时候出现无法全部删除的情况！
    for (int i = SelectedIndexes.count() - 1; i >= 0; --i)
    {
        DataModel->removeRow(SelectedIndexes.at(i).row());
    }
}

void MainWindow::DeleteAllTaskRows(QAbstractItemModel *DataModel)
{
    if (DataModel->rowCount() <= 0)
        return ;

    DataModel->removeRows(0, DataModel->rowCount());
}
