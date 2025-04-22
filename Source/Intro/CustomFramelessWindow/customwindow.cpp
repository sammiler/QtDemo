#include "customwindow.h"
#include "title_bar.h" // 包含自定义标题栏头文件
#include <QIcon>       // 需要 QIcon (如果设置图标)
#include <QColor>      // 需要 QColor
#include <QPalette>    // 需要 QPalette

CustomWindow::CustomWindow(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口标志：无边框和保留现有标志 (如果 Parent 不为 nullptr)
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    // 创建自定义标题栏，并将其父对象设置为当前窗口 (this)
    TitleBar *pTitleBar = new TitleBar(this);

    // !!! 重要 !!! 为当前窗口安装事件过滤器，使用自定义标题栏作为过滤器对象
    // 这使得 TitleBar 的 eventFilter 方法可以在当前窗口接收事件之前处理这些事件
    // TitleBar 的 eventFilter 将监听 WindowTitleChange, WindowIconChange, WindowStateChange, Resize 等事件
    installEventFilter(pTitleBar);

    // 设置窗口的初始大小
    // resize(400, 300); // 已在 main.cpp 中设置，这里可以省略或作为默认值

    // 设置窗口标题和图标 (这些会触发 eventFilter，由 TitleBar 更新显示)
    // setWindowTitle("Custom Window"); // 已在 main.cpp 中设置
    // setWindowIcon(QIcon(":/Images/logo.png")); // 如果资源文件中有图标，可以取消注释

    // 设置窗口背景颜色 (可选，为了更好地看到无边框效果)
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(50, 50, 50)); // 一个深灰色背景
    setPalette(pal);

    // 创建主布局 (垂直布局)
    QVBoxLayout *pLayout = new QVBoxLayout(this); // 以当前窗口为父对象创建布局

    // 将标题栏添加到布局顶部
    pLayout->addWidget(pTitleBar);

    // 添加一个伸缩器 (stretch)，将标题栏推到顶部，占据剩余垂直空间
    pLayout->addStretch();

    // 设置布局的间距和边距为 0
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0); // 通常无边框窗口的主布局边距设为 0

    // 将布局设置到窗口上
    setLayout(pLayout);

    // 注意：如果需要添加其他控件到窗口主体部分，可以将它们添加到 pLayout 的 stretch 上方
    // 例如：pLayout->addWidget(new QLabel("Hello World", this));
}

CustomWindow::~CustomWindow()
{
    // QWidget 的子对象 (包括 pTitleBar) 会自动销毁，无需手动 delete
    // QLayout 的父对象也是 QWidget，也会自动销毁
}