#include "mainwindow.h"

#include <QRandomGenerator>
#include <QDateTime> // 如果TableModel中使用QDateTime
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("HTML Delegate Example");

    // 设置主布局
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    // 创建 TableView
    tableView = new QTableView(this);

    // 创建模型
    fileModel = new TableModel(this);

    // 创建 HTML 委托
    htmlDelegate = new HtmlDelegate(this);

    // 为文件名列设置自定义 HTML 委托
    // tableView->setItemDelegateForColumn(FILE_NAME_COLUMN, htmlDelegate);
    // 其他列使用默认委托 (如果需要其他自定义绘制，需要再创建并设置其他委托)
    tableView->setItemDelegate(htmlDelegate); // 改用这行，将委托设置给整个视图

    // 设置模型到 TableView
    tableView->setModel(fileModel);

    // 可选：调整列大小模式
    tableView->horizontalHeader()->setSectionResizeMode(FILE_NAME_COLUMN, QHeaderView::Stretch); // 文件名列拉伸
    tableView->horizontalHeader()->setSectionResizeMode(FILE_SIZE_COLUMN, QHeaderView::ResizeToContents); // 大小列根据内容调整
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // 禁用排序 (本例模型未实现setData或UserRole用于复杂排序，简单起见禁用)
    // 如果需要排序，需要实现 SortFilterProxyModel 和 TableModel 的相关方法
    tableView->setSortingEnabled(false);


    // 生成并设置示例数据
    QList<FileRecord> recordList;
    QRandomGenerator *rng = QRandomGenerator::global();

    for (int i = 0; i < 10; ++i)
    {
        FileRecord record;
        record.strFileName = QString("Document_%1.txt").arg(i + 1); // 原始文件名
        record.nSize = rng->bounded(100, 10000001); // 随机大小

        recordList.append(record);
    }
    fileModel->updateData(recordList);


    // 将 TableView 添加到布局
    mainLayout->addWidget(tableView);

    // 调整窗口大小
    resize(500, 400);

    QTimer::singleShot(0, this, &MainWindow::adjustRowHeights);
}

MainWindow::~MainWindow()
{
    // 子控件和委托父对象是 this，会自动清理
}

void MainWindow::adjustRowHeights() const {
    // 确保 tableView 和 model 都有效
    if (tableView && tableView->model()) {
        // 调整所有行高以适应内容
        tableView->resizeRowsToContents();
        // 你也可以只调整特定列的行高（如果只有特定列影响行高的话）
        // tableView->resizeRowsToContents(FILE_NAME_COLUMN);
    }
}
