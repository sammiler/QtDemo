#include "mainwindow.h"

#include <QHeaderView> // 需要包含以设置 HeaderView 模式

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Download Progress Example");

    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    tableView = new QTableView(this);

    // 创建模型和委托
    fileModel = new TableModel(this);
    progressBarDelegate = new ProgressBarDelegate(this); // 委托的父对象是窗口，以便自动清理

    // 为进度条列设置自定义委托
    tableView->setItemDelegateForColumn(FILE_DOWNLOAD_PROGRESS_COLUMN, progressBarDelegate);

    // 设置模型到视图
    tableView->setModel(fileModel);

    // 设置表头尺寸调整模式
    tableView->horizontalHeader()->setSectionResizeMode(FILE_DOWNLOAD_FILE_NAME_COLUMN, QHeaderView::Stretch); // 文件名列拉伸
    tableView->horizontalHeader()->setSectionResizeMode(FILE_DOWNLOAD_SIZE_COLUMN, QHeaderView::ResizeToContents); // 大小列适应内容
    tableView->horizontalHeader()->setSectionResizeMode(FILE_DOWNLOAD_STATUS_COLUMN, QHeaderView::ResizeToContents); // 状态列适应内容
    tableView->horizontalHeader()->setSectionResizeMode(FILE_DOWNLOAD_PROGRESS_COLUMN, QHeaderView::Stretch); // 进度条列拉伸或适应内容都可以，拉伸能显示更宽的进度条
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // 行高适应内容 (确保进度条能完全显示)

    // 禁用排序 (如果需要排序，需要实现 SortFilterProxyModel)
    tableView->setSortingEnabled(false);

    // 添加表格视图到布局
    mainLayout->addWidget(tableView);

    // 创建后台线程
    downloadThread = new FileDownloadThread(this); // 线程的父对象是窗口，以便窗口关闭时线程能被清理

    // 连接线程的 transfer 信号到模型的 updateData 槽
    // Qt::QueuedConnection 是跨线程通信的默认连接方式，确保槽函数在接收者（模型，在主线程）的线程中执行
    connect(downloadThread, &FileDownloadThread::transfer, fileModel, &TableModel::updateData, Qt::QueuedConnection);

    // 启动线程
    downloadThread->start();

    resize(600, 300); // 设置窗口初始大小
}

MainWindow::~MainWindow()
{
    // 窗口销毁时，其子对象 (tableView, fileModel, progressBarDelegate, downloadThread) 都会被自动删除。
    // downloadThread 的析构函数会请求中断并等待线程结束。
}