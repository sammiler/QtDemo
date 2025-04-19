#include "mainwindow.h"
#include "TableModel.h"
#include <QMessageBox> // 显示消息框
#include <QDebug> // 打印调试信息

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Button Delegate Example");

    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    tableView = new QTableView(this);

    // 创建模型和代理模型
    fileModel = new TableModel(this);
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(fileModel);

    // 创建自定义按钮委托
    buttonDelegate = new TableViewDelegate(this); // 委托的父对象是窗口

    // 为操作列设置自定义委托
    tableView->setItemDelegateForColumn(FILE_OPERATE_COLUMN, buttonDelegate);

    // 设置代理模型到视图
    tableView->setModel(proxyModel);

    // 设置表头尺寸调整模式
    tableView->horizontalHeader()->setSectionResizeMode(FILE_NAME_COLUMN, QHeaderView::Fixed); // 文件名列拉伸
    tableView->horizontalHeader()->setSectionResizeMode(FILE_OPERATE_COLUMN, QHeaderView::Stretch); // 操作列适应按钮内容宽度 (虽然 sizeHint 不完全控制，但可以作为初始提示)
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // 如果单元格内容复杂需要自适应行高可以打开

    // 启用排序 (使用代理模型，可以排序)
    tableView->setSortingEnabled(true);

    // 连接委托的信号到主窗口的槽函数
    connect(buttonDelegate, &TableViewDelegate::open, this, &MainWindow::handleOpenButtonClicked);
    connect(buttonDelegate, &TableViewDelegate::deleteData, this, &MainWindow::handleDeleteButtonClicked);

    // *** 启用视图的鼠标跟踪 ***
    // 这是关键，确保委托的 editorEvent 能接收到 MouseMove 事件，从而实现划过效果
    tableView->setMouseTracking(true);

    // 添加表格视图到布局
    mainLayout->addWidget(tableView);

    // 生成并设置示例数据
    QList<FileRecord> recordList;
    for (int i = 0; i < 15; ++i) // 添加一些数据项
    {
        FileRecord record;
        record.strFileName = QString("File_%1.txt").arg(i + 1);
        recordList.append(record);
    }
    fileModel->updateData(recordList);

    // 调整窗口大小
    resize(400, 300);
}

MainWindow::~MainWindow()
{
    // 子控件和委托父对象是 this，会自动清理
}

// 处理“打开”按钮点击的槽函数
void MainWindow::handleOpenButtonClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    // *** 重要：将委托（代理模型）索引映射回源模型索引 ***
    QModelIndex sourceIndex = proxyModel->mapToSource(index);

    // 从源模型获取对应记录的文件名
    FileRecord record = fileModel->getRecord(sourceIndex.row());

    // 显示消息框或打印信息
    QMessageBox::information(this, QStringLiteral("打开文件"),
                             QStringLiteral("你点击了“打开”按钮：\n源模型行号：%1\n文件名：%2")
                             .arg(sourceIndex.row())
                             .arg(record.strFileName));
    qDebug() << "Open button clicked for source row:" << sourceIndex.row() << "file:" << record.strFileName;
}

// 处理“删除”按钮点击的槽函数
void MainWindow::handleDeleteButtonClicked(const QModelIndex &index)
{
     if (!index.isValid()) return;

    // *** 重要：将委托（代理模型）索引映射回源模型索引 ***
    QModelIndex sourceIndex = proxyModel->mapToSource(index);

    // 从源模型获取对应记录的文件名
    FileRecord record = fileModel->getRecord(sourceIndex.row());

    // 显示消息框或打印信息
     QMessageBox::warning(this, QStringLiteral("删除文件"),
                             QStringLiteral("你点击了“删除”按钮：\n源模型行号：%1\n文件名：%2")
                             .arg(sourceIndex.row())
                             .arg(record.strFileName));
     qDebug() << "Delete button clicked for source row:" << sourceIndex.row() << "file:" << record.strFileName;

    connect(tableView, &QTableView::clicked, this, &MainWindow::onTableViewClicked);

     // 注意：实际删除数据需要修改模型 (removeItem, beginRemoveRows/endRemoveRows)
     // 这里只是演示信号的触发和信息的获取。
}
void MainWindow::onTableViewClicked(const QModelIndex &index)
{
    // if (!index.isValid())
    //     return;
    //
    // // We only care about clicks on the checkbox column
    // if (index.column() == FILE_OPERATE_COLUMN)
    // {
    //     // *** CORRECT LOGIC: Map the proxy index to the source index ***
    //     QModelIndex sourceIndex = proxyModel->mapToSource(index);
    //
    //     // Now use the row from the source index to get the correct data/set data
    //     // The column should still be CHECK_BOX_COLUMN in the source model
    //     QModelIndex checkIndexInSource = fileModel->index(sourceIndex.row(), FILE_OPERATE_COLUMN);
    //
    //     // Get the current state using CheckStateRole from the source model
    //     bool bChecked = (fileModel->data(checkIndexInSource, Qt::CheckStateRole).toInt() == Qt::Checked);
    //
    //     // Toggle the state using setData on the source model
    //     // The value passed to setData for CheckStateRole should be Qt::Checked or Qt::Unchecked
    //     fileModel->setData(checkIndexInSource, !bChecked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
    //
    //     // Note: If the column's flags include Qt::ItemIsUserCheckable, clicking
    //     // usually automatically toggles the state and calls setData with Qt::CheckStateRole.
    //     // Explicitly calling setData here is redundant if the flag is set,
    //     // but serves to clearly show how you *would* modify the source data
    //     // after getting the correct source index. For demonstration, let's keep it explicit.
    //     // In a real app, you might just rely on the flag for simple toggling.
    // }
}