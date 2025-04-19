#include "mainwindow.h"
#include <QColor>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口标志：无边框和保留现有标志 (如果 Parent 不为 nullptr)
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());



    // 设置窗口背景颜色 (可选，如果 QSS 没有完全覆盖背景)
    // setAutoFillBackground(true);
    // QPalette pal = palette();
    // pal.setColor(QPalette::Window, QColor(60, 60, 60)); // 默认背景色
    // setPalette(pal);

    // 创建一个 FramelessHelper 实例，父对象为当前窗口
    m_framelessHelper = new FramelessHelper(this);

    // 激活 FramelessHelper，使其对当前窗口生效
    m_framelessHelper->activateOn(this);

    // 可选：配置 FramelessHelper 的行为
    m_framelessHelper->setWidgetMovable(true);      // 允许移动 (默认 true)
    m_framelessHelper->setWidgetResizable(true);    // 允许缩放 (默认 true)
    m_framelessHelper->setRubberBandOnMove(false);  // 移动时不显示橡皮筋 (默认 false)
    m_framelessHelper->setRubberBandOnResize(false); // 缩放时不显示橡皮筋 (默认 false)
    FramelessHelper::setBorderWidth(5);          // 缩放边框宽度 (默认 5)
    FramelessHelper::setTitleHeight(30);         // 拖动区域高度 (默认 30)

    // 添加一些示例内容到窗口
    m_contentLabel = new QLabel("Drag or resize this window!", this);
    m_contentLabel->setAlignment(Qt::AlignCenter);
    m_contentLabel->setStyleSheet("color: white;"); // 设置文字颜色

    // 设置主布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_contentLabel);
    layout->setContentsMargins(FramelessHelper::borderWidth(), // 左边距
                               FramelessHelper::titleHeight(), // 上边距 (模拟标题栏区域)
                               FramelessHelper::borderWidth(), // 右边距
                               FramelessHelper::borderWidth());// 下边距

    setLayout(layout);

    // 设置窗口的 Object Name，用于在 QSS 中引用
    setObjectName("mainFramelessWindow");
}

MainWindow::~MainWindow()
{
    // m_framelessHelper 的父对象是 this，会自动销毁
}