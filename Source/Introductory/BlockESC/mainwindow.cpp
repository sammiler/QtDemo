#include "mainwindow.h"
#include "default_escape_dialog.h"       // 包含对话框头文件
#include "event_filter_escape_dialog.h"  // 包含对话框头文件
#include "key_press_override_dialog.h"   // 包含对话框头文件
#include "reject_override_dialog.h"      // 包含对话框头文件
#include <QDebug> // 需要 qDebug

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 创建按钮
    m_btnDefault = new QPushButton("Show Default Behavior", this);
    m_btnEventFilter = new QPushButton("Show Event Filter Method", this);
    m_btnKeyPressOverride = new QPushButton("Show KeyPressEvent Override Method", this);
    m_btnRejectOverride = new QPushButton("Show Reject() Override Method", this);

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this); // 垂直布局
    layout->addWidget(m_btnDefault);
    layout->addWidget(m_btnEventFilter);
    layout->addWidget(m_btnKeyPressOverride);
    layout->addWidget(m_btnRejectOverride);
    layout->addStretch(); // 伸缩器推到底部

    setLayout(layout); // 应用布局

    // 设置窗口大小
    resize(300, 250);

    // 连接信号槽 (使用新的信号槽语法)
    connect(m_btnDefault, &QPushButton::clicked, this, &MainWindow::onLaunchDefault);
    connect(m_btnEventFilter, &QPushButton::clicked, this, &MainWindow::onLaunchEventFilter);
    connect(m_btnKeyPressOverride, &QPushButton::clicked, this, &MainWindow::onLaunchKeyPressOverride);
    connect(m_btnRejectOverride, &QPushButton::clicked, this, &MainWindow::onLaunchRejectOverride);

    qDebug() << "MainWindow created.";
}

MainWindow::~MainWindow()
{
    // 按钮和布局的父对象是 this，会自动销毁
}

// 启动默认行为对话框
void MainWindow::onLaunchDefault()
{
    DefaultEscapeDialog dialog(this); // 创建对话框实例，以主窗口为父对象
    dialog.setWindowTitle("Default Escape Behavior");
    qDebug() << "Launching Default Escape Behavior Dialog...";
    dialog.exec(); // 以模态方式显示对话框
    qDebug() << "Default Escape Behavior Dialog closed.";
}

// 启动事件过滤器方法对话框
void MainWindow::onLaunchEventFilter()
{
    EventFilterEscapeDialog dialog(this); // 创建对话框实例
    dialog.setWindowTitle("Event Filter Method");
     qDebug() << "Launching Event Filter Dialog...";
    dialog.exec(); // 以模态方式显示对话框
     qDebug() << "Event Filter Dialog closed.";
}

// 启动重写 KeyPressEvent 方法对话框
void MainWindow::onLaunchKeyPressOverride()
{
    KeyPressOverrideEscapeDialog dialog(this); // 创建对话框实例
    dialog.setWindowTitle("KeyPressEvent Override Method");
    qDebug() << "Launching KeyPressEvent Override Dialog...";
    dialog.exec(); // 以模态方式显示对话框
    qDebug() << "KeyPressEvent Override Dialog closed.";
}

// 启动重写 Reject() 方法对话框
void MainWindow::onLaunchRejectOverride()
{
    RejectOverrideDialog dialog(this); // 创建对话框实例
    dialog.setWindowTitle("Reject() Override Method");
    qDebug() << "Launching Reject() Override Dialog...";
    dialog.exec(); // 以模态方式显示对话框
    qDebug() << "Reject() Override Dialog closed.";
}