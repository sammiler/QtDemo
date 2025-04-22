#include "mainwindow.h"
#include <QtNetwork/QHostInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , lookupId(-1)
{
    // 创建中心部件和主布局
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 创建输入区域布局
    QHBoxLayout *inputLayout = new QHBoxLayout();

    // 输入框
    inputLineEdit = new QLineEdit(this);
    inputLineEdit->setPlaceholderText("请输入主机名或 IP 地址");
    inputLayout->addWidget(inputLineEdit);

    // 查询按钮
    lookupButton = new QPushButton("查询", this);
    inputLayout->addWidget(lookupButton);

    // 中止按钮
    abortButton = new QPushButton("中止", this);
    inputLayout->addWidget(abortButton);

    // 添加输入布局到主布局
    mainLayout->addLayout(inputLayout);

    // 输出文本区域
    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);
    mainLayout->addWidget(outputText);

    // 设置窗口标题和大小
    setWindowTitle("主机信息查询");
    resize(600, 400);

    // 连接信号和槽
    connect(lookupButton, &QPushButton::clicked, this, &MainWindow::onLookupButtonClicked);
    connect(abortButton, &QPushButton::clicked, this, &MainWindow::onAbortButtonClicked);

    // 显示本地主机名
    QString localHostName = QHostInfo::localHostName();
    outputText->append("本地主机名: " + localHostName);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onLookupButtonClicked()
{
    const QString input = inputLineEdit->text().trimmed();
    if (input.isEmpty()) {
        outputText->append("错误: 请输入主机名或 IP 地址。");
        return;
    }

    // 执行异步查询
    lookupId = QHostInfo::lookupHost(input, this, SLOT(lookedUp(QHostInfo)));
    outputText->append("开始查询: " + input + " (ID: " + QString::number(lookupId) + ")");
}

void MainWindow::onAbortButtonClicked()
{
    if (lookupId != -1) {
        QHostInfo::abortHostLookup(lookupId);
        outputText->append("已中止查询 ID: " + QString::number(lookupId));
        lookupId = -1;
    } else {
        outputText->append("没有正在进行的查询可中止。");
    }
}

void MainWindow::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
        outputText->append("查询失败: " + host.errorString());
        lookupId = -1;
        return;
    }

    // 显示主机名
    outputText->append("找到主机名: " + host.hostName());

    // 显示 IP 地址
    for (const QHostAddress &address : host.addresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            outputText->append("找到 IPv4 地址: " + address.toString());
        } else if (address.protocol() == QAbstractSocket::IPv6Protocol) {
            outputText->append("找到 IPv6 地址: " + address.toString());
        } else {
            outputText->append("找到其他地址: " + address.toString());
        }
    }

    lookupId = -1;
}