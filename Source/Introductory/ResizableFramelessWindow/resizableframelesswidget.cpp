#include "resizableframelesswidget.h"
#include <QDebug>     // 需要 qDebug
#include <QRect>      // geometry() 返回 QRect
#include <QChildEvent>// childAt() 检查

// 仅在 Windows 平台包含 Windows 特定头文件和链接库指令
#ifdef Q_OS_WIN
// #pragma comment 告诉 MSVC 编译器链接 user32.lib 库
#pragma comment(lib, "user32.lib")
// 包含 Windows.h 和 Windowsx.h (已在 .h 中处理)
// #include <qt_windows.h>
// #include <Windowsx.h>
#endif

ResizableFramelessWidget::ResizableFramelessWidget(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口标志为无边框
    setWindowFlags(Qt::FramelessWindowHint);

    // 设置窗口属性，背景透明
    // 这通常用于需要圆角或阴影等自定义边框的情况
    // 如果只是想设置一个纯色背景，可以不设置这个属性，直接用 QPalette


    // 可以设置一个最小尺寸，防止缩放到过小
    // setMinimumSize(100, 100);

    qDebug() << "ResizableFramelessWidget created.";
}

ResizableFramelessWidget::~ResizableFramelessWidget()
{
    // QWidget 的子对象会自动销毁
}

// 重写 nativeEvent 来处理原生窗口消息
bool ResizableFramelessWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType) // 避免编译器警告，因为我们只处理 Windows 消息

    // 仅在 Windows 平台上处理 Windows 消息
#ifdef Q_OS_WIN
    // 检查事件类型是否是 Windows 原生事件
    // Qt on Windows 通常将原生事件类型报告为 "windows_generic_MSG"
    // 或者更简单地，直接检查 param->message，因为 message 结构体是通用的
    // if (eventType == "windows_generic_MSG")
    {
        // 将 message 指针转换为 Windows 的 MSG 结构体指针
        MSG *param = static_cast<MSG *>(message);

        // 检查消息类型是否是 WM_NCHITTEST
        // 这个消息在鼠标移动、点击时发送，用于确定鼠标光标“命中”了窗口的哪个非客户区部分
        if (param->message == WM_NCHITTEST)
        {
            // 获取鼠标光标的屏幕坐标 (从 lParam 中提取)
            // GET_X_LPARAM 和 GET_Y_LPARAM 宏需要 Windowsx.h
            int nScreenX = GET_X_LPARAM(param->lParam);
            int nScreenY = GET_Y_LPARAM(param->lParam);

            // 将屏幕坐标转换为窗口的客户区坐标
            // (鼠标的屏幕X - 窗口左上角的屏幕X) = 鼠标相对于窗口客户区左上角的X坐标
            int nX = nScreenX - this->geometry().x(); // 或者 this->x()
            int nY = nScreenY - this->geometry().y(); // 或者 this->y()

            // 检查鼠标是否位于任何子控件的上面
            // 如果是，则将命中测试结果设置为 HTCLIENT，并让 Qt 的默认处理来决定子控件的行为
            if (childAt(nX, nY) != nullptr) { // childAt 返回给定坐标的子控件，没有则返回 nullptr
                 *result = HTCLIENT; // 命中客户区，交给子控件处理
                 return false; // 返回 false 让 Qt 将事件继续传递给子控件
            }

            // !!! 如果鼠标不在子控件上，则进行自定义的边框命中测试 !!!

            // 默认情况下，将结果设置为 HTCAPTION，这意味着如果鼠标不在边框上，
            // 点击时将模拟点击标题栏，这允许在没有标题栏时拖动窗口（如果启用了拖动）
            // 如果你想让非边框区域不可拖动，可以将默认结果设为 HTCLIENT
            *result = HTCAPTION; // 默认命中标题栏区域 (可拖动)


            // 检查鼠标是否在窗口边框的缩放区域内
            // m_nBorder 是我们定义的边框宽度

            // 位于左边框
            if ((nX > 0) && (nX < m_nBorder))
                *result = HTLEFT;
            // 位于右边框
            else if ((nX > this->width() - m_nBorder) && (nX < this->width())) // 注意这里用 else if 确保只匹配一个区域
                *result = HTRIGHT;
            // 位于上边框
            else if ((nY > 0) && (nY < m_nBorder))
                *result = HTTOP;
            // 位于下边框
            else if ((nY > this->height() - m_nBorder) && (nY < this->height()))
                *result = HTBOTTOM;

            // 位于左上角
            if ((nX > 0) && (nX < m_nBorder) && (nY > 0) && (nY < m_nBorder)) // 注意这里不用 else if，因为它可能同时满足左边和上边
                *result = HTTOPLEFT;
            // 位于右上角
            else if ((nX > this->width() - m_nBorder) && (nX < this->width()) && (nY > 0) && (nY < m_nBorder))
                *result = HTTOPRIGHT;
            // 位于左下角
            else if ((nX > 0) && (nX < m_nBorder) && (nY > this->height() - m_nBorder) && (nY < this->height()))
                *result = HTBOTTOMLEFT;
            // 位于右下角
            else if ((nX > this->width() - m_nBorder) && (nX < this->width()) && (nY > this->height() - m_nBorder) && (nY < this->height()))
                *result = HTBOTTOMRIGHT;

            // 如果我们设置了 *result 为非 HTCLIENT 的值 (即命中非客户区，如边框或标题栏)，
            // Windows 会根据这个值接管后续的鼠标事件来执行相应的操作 (如缩放或移动)。
            // 返回 true 告诉 Qt 这个事件已经被原生事件处理器完全处理了。
            if (*result != HTCLIENT) {
                 // 可选：在这里打印命中的区域，方便调试
                 // qDebug() << "WM_NCHITTEST -> Hit Test Result:" << *result;
                 return true;
            }
        }
    }
#endif // Q_OS_WIN

    // 对于非 WM_NCHITTEST 消息，或者在非 Windows 平台，
    // 将事件传递给基类进行默认处理
    return QWidget::nativeEvent(eventType, message, result);
}