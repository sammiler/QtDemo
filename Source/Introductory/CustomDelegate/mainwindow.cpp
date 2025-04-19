#include "mainwindow.h"
#include <QHeaderView>       // 需要 QHeaderView
#include <QAbstractItemView> // 需要 QAbstractItemView::SelectRows, QAbstractItemView::SingleSelection
#include <QFrame>            // 需要 QFrame::NoFrame
#include <QList>             // 需要 QList
#include <QStringList>       // 需要 QStringList
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 创建自定义模型实例
    m_tableModel = new TableModel(this);

    // 创建自定义委托实例
    m_checkBoxDelegate = new CheckBoxDelegate(this);

    // 创建 QTableView 实例
    m_tableView = new QTableView(this);

    // --- 设置 QTableView 的属性 ---
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 选择整行
    m_tableView->horizontalHeader()->setStretchLastSection(true);     // 水平表头最后一列拉伸
    m_tableView->horizontalHeader()->setHighlightSections(false);      // 水平表头不高亮
    m_tableView->verticalHeader()->setVisible(false);                 // 隐藏垂直表头 (行号)
    m_tableView->setShowGrid(false);                                  // 不显示网格线
    m_tableView->setFrameShape(QFrame::NoFrame);                      // 窗体形状：无边框
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 选择模式：单行选中

    // 将模型设置给视图
    m_tableView->setModel(m_tableModel);

    // !!! 为第一列 (复选框列) 设置自定义委托 !!!
    m_tableView->setItemDelegateForColumn(CHECK_BOX_COLUMN, m_checkBoxDelegate);
    // 如果希望所有列都使用这个委托（不常见），可以使用 m_tableView->setItemDelegate(m_checkBoxDelegate);


    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this); // 垂直布局
    layout->addWidget(m_tableView);               // 将表格视图添加到布局
    setLayout(layout);                             // 将布局设置到窗口上

    // 设置窗口大小
    resize(500, 400);

    // --- 加载示例数据并更新模型 ---
    QList<FileRecord> recordList;
    // 示例文件路径列表
    QStringList exampleFilePaths;
    exampleFilePaths << QStringLiteral("C:/Program Files/example1.exe")
                     << QStringLiteral("D:/Documents/report.docx")
                     << QStringLiteral("/home/user/pictures/image.png")
                     << QStringLiteral("E:/Archives/backup.zip")
                     << QStringLiteral("F:/Data/spreadsheet.xlsx")
                     << QStringLiteral("C:/Windows/System32/kernel32.dll")
                     << QStringLiteral("/var/log/syslog.txt");


    for (const QString &filePath : exampleFilePaths) // 遍历示例文件路径
    {
        FileRecord record;
        record.bChecked = false; // 默认不选中
        record.strFilePath = filePath; // 设置文件路径
        recordList.append(record); // 添加到列表中
    }

    // 更新模型数据，并通知视图刷新
    m_tableModel->updateData(recordList);

    qDebug() << "MainWindow created with TableView, Model, and Delegate.";
}

// 析构函数
MainWindow::~MainWindow()
{
    // m_tableView, m_tableModel, m_checkBoxDelegate 的父对象是 this，窗口销毁时它们会自动销毁
    qDebug() << "MainWindow destroyed.";
}