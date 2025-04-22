#include "title_bar.h"
#include <QHBoxLayout> // 需要 QHBoxLayout
#include <QApplication> // 需要 QApplication::style()
#include <QStyle>      // 需要 QStyle
#include <QDebug>      // 需要 qDebug
#include <QIcon>       // 需要 QIcon
#include <QPixmap>     // 需要 QPixmap

// 仅在 Windows 平台包含 Windows 特定头文件和链接库指令
#ifdef Q_OS_WIN
// #pragma comment 告诉 MSVC 编译器链接 user32.lib 库
#pragma comment(lib, "user32.lib")
// 包含 Qt 提供的 Windows 特定头文件包装器，它会包含 Windows.h
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    // 设置标题栏固定高度
    setFixedHeight(30); // 可以根据需要调整高度

    // 创建子控件，父对象都设置为 this (TitleBar)
    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    // 设置图标标签的固定大小和缩放内容属性
    m_pIconLabel->setFixedSize(20, 20);
    m_pIconLabel->setScaledContents(true);

    // 设置标题标签的尺寸策略，使其可以伸展占据可用空间
    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 设置按钮的固定大小
    m_pMinimizeButton->setFixedSize(27, 22);
    m_pMaximizeButton->setFixedSize(27, 22);
    m_pCloseButton->setFixedSize(27, 22);

    // 设置对象名称，用于在样式表中引用
    m_pTitleLabel->setObjectName("whiteLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton"); // 注意：QSS 中使用 #name 选择器

    // 设置按钮的工具提示
    m_pMinimizeButton->setToolTip(tr("Minimize"));
    m_pMaximizeButton->setToolTip(tr("Maximize"));
    m_pCloseButton->setToolTip(tr("Close"));
    m_pMinimizeButton->setText("-");
    m_pMaximizeButton->setText("[]");
    m_pCloseButton->setText("X");

    // 创建水平布局
    QHBoxLayout *pLayout = new QHBoxLayout(this); // 以当前控件为父对象创建布局

    // 将子控件添加到布局中
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(5); // 图标和标题之间的间距
    pLayout->addWidget(m_pTitleLabel);
    pLayout->addStretch(); // 在标题和按钮之间添加伸缩器，将按钮推到右边
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addWidget(m_pCloseButton);

    // 设置布局的间距和边距
    pLayout->setSpacing(0); // 按钮之间的间距为 0
    pLayout->setContentsMargins(5, 0, 5, 0); // 左、上、右、下边距

    // 将布局设置到 TitleBar 控件上
    setLayout(pLayout);

    // 连接按钮的点击信号到同一个槽函数 onClicked()
    // 使用新的信号槽语法
    connect(m_pMinimizeButton, &QPushButton::clicked, this, &TitleBar::onClicked);
    connect(m_pMaximizeButton, &QPushButton::clicked, this, &TitleBar::onClicked);
    connect(m_pCloseButton, &QPushButton::clicked, this, &TitleBar::onClicked);

    // 初始更新最大化按钮的状态
    updateMaximize();
}

TitleBar::~TitleBar()
{
    // QWidget 的子对象 (包括所有的 QLabel 和 QPushButton) 会自动销毁
}

// 重写鼠标双击事件
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event); // 避免编译器警告

    // 双击标题栏时，模拟点击最大化/还原按钮
    // 这会触发 onClicked() 槽函数，进而实现最大化/还原功能
    emit m_pMaximizeButton->clicked();

    // 不需要调用基类方法，因为我们已经处理了双击事件
    // QWidget::mouseDoubleClickEvent(event); // 如果调用基类，可能会有默认行为
}

// 重写鼠标按下事件，实现窗口拖动
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    // 仅在 Windows 平台上使用 Windows API 实现拖动
#ifdef Q_OS_WIN
    // 检查是否是鼠标左键按下
    if (event->button() == Qt::LeftButton)
    {
        // 释放当前窗口对鼠标的捕获 (如果之前有的话)
        if (ReleaseCapture())
        {
            // 获取 TitleBar 所在的顶级窗口 (通常是 CustomWindow)
            QWidget *pWindow = this->window(); // this->window() 向上查找第一个窗口类型的父对象
            // 确保是顶级窗口 (不是内嵌控件)
            if (pWindow && pWindow->isTopLevel())
            {
               // 发送 WM_SYSCOMMAND 消息给顶级窗口，模拟标题栏的拖动操作
               // HWND(pWindow->winId()) 获取顶级窗口的 Windows 句柄
               // WM_SYSCOMMAND 是系统命令消息
               // SC_MOVE + HTCAPTION 告诉系统执行移动操作，并将按下位置视为标题栏
               // 0 是 lparam，对于 SC_MOVE 来说，这个值通常是 0
               SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
               qDebug() << "TitleBar: Sent WM_SYSCOMMAND to initiate drag.";
            } else {
                qDebug() << "TitleBar: Could not find a top-level window to drag.";
            }
        }
        else
        {
             qDebug() << "TitleBar: ReleaseCapture() failed.";
        }

        // 忽略这个鼠标事件，阻止 Qt 进一步处理它
        // 因为 Windows API 调用已经接管了拖动过程
        event->ignore(); // 或者 event->accept()，取决于是否希望事件继续传播
    }
    else
    {
        // 如果不是左键按下，将事件传递给基类处理
        QWidget::mousePressEvent(event);
    }
#else
    // 在非 Windows 平台，如果需要拖动，可以使用 Qt 原生方法
    // 需要在 TitleBar 类中实现 mouseMoveEvent 和 mouseReleaseEvent，并跟踪鼠标位置
    // 这里由于只实现了 Windows API 方式，所以在非 Windows 平台只调用基类方法或忽略
    QWidget::mousePressEvent(event); // 调用基类处理
    qDebug() << "TitleBar: Mouse press event on non-Windows platform.";
#endif
}

// 事件过滤器
// 监听 TitleBar 所在的顶级窗口的事件
bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    // 检查事件类型
    switch (event->type())
    {
    // 窗口标题改变事件
    case QEvent::WindowTitleChange:
    {
        // 将事件发送者转换为 QWidget 指针
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            // 如果转换成功，获取窗口标题并设置到标题标签上
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true; // 事件已处理
        }
        break; // 继续默认处理
    }
    // 窗口图标改变事件
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            // 如果转换成功，获取窗口图标
            QIcon icon = pWidget->windowIcon();
            // 将图标转换为适用于标签尺寸的 QPixmap 并设置到图标标签上
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true; // 事件已处理
        }
        break; // 继续默认处理
    }
    // 窗口状态改变事件 (最大化、最小化等) 或窗口尺寸改变事件
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        // 当窗口状态或尺寸改变时，更新最大化按钮的图标和提示
        updateMaximize();
        // 返回 true 表示事件已由过滤器处理，但这些事件通常需要继续传递以更新窗口布局等
        // 返回 false 让事件继续传递给接收者 (主窗口 CustomWindow) 的 normal event handlers
        return false; // !!! 注意这里返回 false 让 CustomWindow 正常处理 Resize/WindowStateChange
    }

    // 对于其他所有事件，将事件传递给基类 QWidget::eventFilter 进行默认处理
    return QWidget::eventFilter(obj, event);
}

// 槽函数：处理最小化、最大化/还原、关闭按钮的点击
void TitleBar::onClicked()
{
    // 获取发送信号的按钮
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    // 获取 TitleBar 所在的顶级窗口
    QWidget *pWindow = this->window();

    // 确保找到了顶级窗口
    if (pWindow && pWindow->isTopLevel())
    {
        // 判断是哪个按钮被点击，并执行相应的窗口操作
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized(); // 最小化窗口
        }
        else if (pButton == m_pMaximizeButton)
        {
            // 如果窗口当前是最大化的，则还原；否则最大化
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close(); // 关闭窗口
        }
    } else {
         qDebug() << "TitleBar: onClicked - Could not find a top-level window to operate on.";
    }
}

// 更新最大化按钮的状态 (图标/提示)
void TitleBar::updateMaximize()
{
    // 获取 TitleBar 所在的顶级窗口
    QWidget *pWindow = this->window();
    // 确保找到了顶级窗口
    if (pWindow && pWindow->isTopLevel())
    {
        // 检查窗口是否处于最大化状态
        bool bMaximize = pWindow->isMaximized();

        // 根据窗口的最大化状态设置最大化按钮的工具提示和样式属性
        if (bMaximize)
        {
            m_pMaximizeButton->setToolTip(tr("Restore")); // 提示“还原”
            // 设置样式属性，用于 QSS 中根据属性值改变样式 (如图标)
            m_pMaximizeButton->setProperty("maximizeProperty", "restore");
             qDebug() << "TitleBar: Window is maximized, setting button property 'restore'.";
        }
        else
        {
            m_pMaximizeButton->setProperty("maximizeProperty", "maximize"); // 提示“最大化”
            m_pMaximizeButton->setToolTip(tr("Maximize"));
            qDebug() << "TitleBar: Window is normal, setting button property 'maximize'.";
        }

        // 重新应用样式，使根据属性值改变的样式生效
        m_pMaximizeButton->setStyle(QApplication::style());
    } else {
         qDebug() << "TitleBar: updateMaximize - Could not find a top-level window.";
    }
}