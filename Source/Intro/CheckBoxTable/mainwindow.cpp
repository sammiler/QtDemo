#include "mainwindow.h"
#include <QHeaderView>       // 需要 QHeaderView
#include <QAbstractItemView> // 需要 QAbstractItemView::SelectRows, QAbstractItemView::SingleSelection
#include <QFrame>            // 需要 QFrame::NoFrame
#include <QList>             // 需要 QList
#include <QStringList>       // 需要 QStringList
#include <QDebug>            // 需要 qDebug

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 创建自定义组件实例，以当前窗口为父对象
    m_tableModel = new TableModel(this);
    m_checkBoxDelegate = new CheckBoxDelegate(this);
    m_tableHeaderView = new TableHeaderView(Qt::Horizontal, this); // 创建水平表头视图

    // 创建 QTableView 实例
    m_tableView = new QTableView(this);

    // !!! 设置 QTableView 使用自定义表头视图 !!!
    m_tableView->setHorizontalHeader(m_tableHeaderView);

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


    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this); // 垂直布局
    layout->addWidget(m_tableView);               // 将表格视图添加到布局
    setLayout(layout);                             // 将布局设置到窗口上

    // 设置窗口大小
    resize(500, 400);

    // --- 连接信号槽以同步复选状态 ---
    // 1. 当模型中的任何行项复选状态改变时，通知表头更新其主复选状态
    //    模型发射 stateChanged(Qt::CheckState)
    //    表头接收 onStateChanged(int)
    connect(m_tableModel, &TableModel::stateChanged, m_tableHeaderView, &TableHeaderView::onStateChanged);

    // 2. 当表头的主复选状态改变时，通知模型更新所有行项的复选状态
    //    表头发射 stateChanged(Qt::CheckState)
    //    模型接收 onStateChanged(int)
    connect(m_tableHeaderView, &TableHeaderView::stateChanged, m_tableModel, &TableModel::onStateChanged);


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

    qDebug() << "MainWindow created with all components and connections.";
}

// 析构函数
MainWindow::~MainWindow()
{
    // 所有组件的父对象是 this，窗口销毁时它们会自动销毁
    qDebug() << "MainWindow destroyed.";
}