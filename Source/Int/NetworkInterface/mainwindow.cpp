#include "mainwindow.h"
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QHostAddress>
#include <QDebug>

MainWindow::MainWindow(QWidget *const parent)
    : QMainWindow(parent)
    , refreshButton(new QPushButton("刷新", this))
    , outputText(new QTextEdit(this))
    , mainLayout(new QVBoxLayout)
{
    // 创建中心部件
    const QPointer<QWidget> centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 设置布局
    centralWidget->setLayout(mainLayout);

    // 配置输出文本框
    outputText->setReadOnly(true);
    mainLayout->addWidget(outputText);

    // 添加刷新按钮
    mainLayout->addWidget(refreshButton);

    // 设置窗口标题和大小
    setWindowTitle("网络信息查询");
    resize(600, 400);

    // 连接信号和槽
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::onRefreshButtonClicked);

    // 初始显示网络信息
    displayNetworkInfo();
}

MainWindow::~MainWindow() = default;

void MainWindow::onRefreshButtonClicked()
{
    outputText->clear();
    displayNetworkInfo();
}

void MainWindow::displayNetworkInfo()
{
    // 获取所有 IP 地址
    const QList<QHostAddress> addressList = QNetworkInterface::allAddresses();
    outputText->append("=== 所有 IP 地址 ===");
    for (const QHostAddress &address : addressList) {
        if (!address.isNull()) {
            outputText->append("地址: " + address.toString());
        }
    }

    // 获取所有网络接口
    const QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();
    outputText->append("\n=== 网络接口信息 ===");
    for (const QNetworkInterface &netInterface : interfaceList) {
        if (!netInterface.isValid()) {
            continue;
        }

        outputText->append("********************");

        const QNetworkInterface::InterfaceFlags flags = netInterface.flags();
        if (flags.testFlag(QNetworkInterface::IsRunning) &&
            !flags.testFlag(QNetworkInterface::IsLoopBack)) {
            outputText->append("设备: " + netInterface.name());
            outputText->append("硬件地址: " + netInterface.hardwareAddress());
            outputText->append("人类可读名称: " + netInterface.humanReadableName());
        }
    }
}