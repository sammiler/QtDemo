#include "framelesswidget.h"
#include <QDebug> // 用于调试输出

// 仅在 Windows 平台包含 Windows 特定头文件和链接库指令
#ifdef Q_OS_WIN
// #pragma comment 告诉 MSVC 编译器链接 user32.lib 库，其中包含 ReleaseCapture 和 SendMessage 等函数
#pragma comment(lib, "user32.lib")
// 包含 Qt 提供的 Windows 特定头文件包装器，它会包含 Windows.h
#include <qt_windows.h>
#endif

FramelessWidget::FramelessWidget(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口标志为无边框
    // 这将移除标准的窗口边框、标题栏和控制按钮
    setWindowFlags(Qt::FramelessWindowHint);

    // 可选：设置窗口背景，使其可见 (无边框窗口默认可能是透明的)
    // setAutoFillBackground(true);
    // QPalette palette = this->palette();
    // palette.setColor(QPalette::Window, Qt::blue); // 设置一个背景颜色
    // setPalette(palette);
}


FramelessWidget::~FramelessWidget()
{
    // QWidget 的子对象会自动销毁，无需在这里手动清理
}

// 重写鼠标按下事件
void FramelessWidget::mousePressEvent(QMouseEvent *event)
{
    // 检查是否是鼠标左键按下
    if (event->button() == Qt::LeftButton)
    {
        // 仅在 Windows 平台上使用 Windows API 调用实现拖动
#ifdef Q_OS_WIN
        // 释放当前窗口对鼠标的捕获 (如果之前有的话)
        // 这一步对于让 SendMessage 正确启动拖动是必要的
        if (ReleaseCapture())
        {
            // 发送 WM_SYSCOMMAND 消息给窗口，模拟标题栏的拖动操作
            // HWND(winId()) 获取窗口的 Windows 句柄
            // WM_SYSCOMMAND 是系统命令消息
            // SC_MOVE + HTCAPTION 告诉系统执行移动操作，并将按下位置视为标题栏 (即使没有标题栏)
            // 0 是 lparam，对于 SC_MOVE 来说，这个值通常是 0
            SendMessage(reinterpret_cast<HWND>(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
            qDebug() << "Sent WM_SYSCOMMAND to initiate drag.";
        }
        else
        {
             qDebug() << "ReleaseCapture() failed.";
        }

        // 忽略这个鼠标事件，阻止 Qt 进一步处理它 (例如默认的事件传播或尝试启动 Qt 自带的拖动)
        // 因为 Windows API 调用已经接管了拖动过程
        event->ignore();
#else
        // 在非 Windows 平台，如果需要拖动，可以使用 Qt 原生方法 (如下面的注释所示)
        // 或者什么都不做，取决于需求
        qDebug() << "Ignoring mouse press on non-Windows platform for WinAPI drag example.";
        // 如果需要 Qt 原生拖动，请移除 #ifdef Q_OS_WIN 并实现 mouseMoveEvent/mouseReleaseEvent
        // 示例 Qt 原生拖动逻辑 (需要 FramelessWidget 类中添加成员变量 m_bPressed 和 m_point)
        // m_bPressed = true;
        // m_point = event->pos();
        QWidget::mousePressEvent(event); // 调用基类处理，如果不需要 Qt 原生拖动则移除
#endif
    }
    else
    {
        // 如果不是左键按下，将事件传递给基类处理
        QWidget::mousePressEvent(event);
    }
}

