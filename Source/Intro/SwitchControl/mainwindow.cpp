#include "mainwindow.h"
#include <QColor> // 需要 QColor

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 创建 SwitchControl 实例，以当前窗口为父对象
    m_switchControl1 = new SwitchControl(this);
    m_switchControl2 = new SwitchControl(this);
    m_switchControl3 = new SwitchControl(this);

    // 按照示例代码设置不同开关的状态和样式
    // m_switchControl1 保持默认状态和样式

    m_switchControl2->setToggle(true); // 设置为打开状态
    m_switchControl2->setCheckedColor(QColor(0, 160, 230)); // 设置选中时的颜色

    m_switchControl3->setDisabled(true); // 设置为不可用状态
    m_switchControl3->setToggle(true); // 设置为打开状态 (即使不可用也可以设置状态)
    // 不可用时的颜色由 SwitchControl 内部处理，也可以通过 setDisaledColor 设置

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this); // 以当前窗口为父对象创建垂直布局
    layout->addWidget(m_switchControl1); // 添加第一个开关
    layout->addWidget(m_switchControl2); // 添加第二个开关
    layout->addWidget(m_switchControl3); // 添加第三个开关
    layout->addStretch(); // 添加一个伸缩器，将开关推到顶部

    setLayout(layout); // 将布局设置到窗口上

    // 设置窗口大小，以便看到所有控件
    resize(200, 200);

    // 连接信号槽
    // 连接第一个开关的 toggled 信号到当前窗口的 onToggled 槽
    // 使用新的信号槽语法
    connect(m_switchControl1, &SwitchControl::toggled, this, &MainWindow::onToggled);

    qDebug() << "MainWindow created with SwitchControls.";
}

MainWindow::~MainWindow()
{
    // m_switchControl1, m_switchControl2, m_switchControl3 的父对象是 this，会自动销毁
}

// 示例槽函数：当第一个开关状态改变时被调用
void MainWindow::onToggled(bool checked)
{
    // 打印当前开关的状态到控制台
    qDebug() << "SwitchControl 1 State Changed: " << (checked ? "ON" : "OFF");
}