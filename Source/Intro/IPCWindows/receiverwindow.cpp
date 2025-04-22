#include <QVBoxLayout>
#include <QMessageBox> // 消息框
#include "receiverwindow.h"
#include "ipc_defs.h" // 包含 IPC 定义和 Windows 头文件

// 仅在 Windows 平台上包含 Windows 特定头文件 (已在 ipc_defs.h 中处理)
#ifdef Q_OS_WIN
// 如果没有 ipc_defs.h，这里需要 #include <qt_windows.h>
#endif

ReceiverWindow::ReceiverWindow(QWidget *parent)
    : QWidget(parent)
{
    // !! 重要 !! 设置窗口标题，必须与发送方查找的标题一致
    setWindowTitle(RECEIVER_WINDOW_TITLE); // RECEIVER_WINDOW_TITLE 来自 ipc_defs.h

    // 创建 UI 元素
    receivedMessageLabel = new QLabel("Waiting for messages...", this);
    receivedMessageLabel->setWordWrap(true); // 允许换行

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(receivedMessageLabel);
    setLayout(layout);

    // 设置窗口大小
    resize(300, 150); // 可以调整大小
}

ReceiverWindow::~ReceiverWindow()
{
    // QWidget 的子控件会自动销毁
}

// 重写 nativeEvent 来处理原生窗口消息
bool ReceiverWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    // 仅在 Windows 平台上处理 Windows 消息
#ifdef Q_OS_WIN
    // 检查事件类型是否是 Windows 原生事件
    // Qt on Windows 通常将原生事件类型报告为 "windows_generic_MSG"
    if (eventType == "windows_generic_MSG")
    {
        // 将 message 指针转换为 Windows 的 MSG 结构体指针
        MSG *param = static_cast<MSG *>(message);

        // 检查消息类型是否是 WM_COPYDATA
        if (param->message == WM_COPYDATA)
        {
            // 将 lParam 转换为指向 COPYDATASTRUCT 结构体的指针
            const auto cds = reinterpret_cast<COPYDATASTRUCT*>(param->lParam);

            // 检查自定义数据类型是否匹配，以过滤掉其他 WM_COPYDATA 消息
            if (cds->dwData == CUSTOM_TYPE) // CUSTOM_TYPE 来自 ipc_defs.h
            {
                // 从 COPYDATASTRUCT 中提取数据
                // lpData 指向数据，cbData 是数据大小
                // 使用 QString::fromUtf8 将 UTF-8 字节数据转换为 QString
                QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);

                // 在 QLabel 中显示接收到的消息
                receivedMessageLabel->setText("Received: " + strMessage);

                // 弹出消息框提示收到消息 (可选)
                // QMessageBox::information(this, QStringLiteral("Message Received"), strMessage);

                // 根据 WM_COPYDATA 协议，如果成功处理消息，应该设置 *result 为非零值 (通常是 1)
                *result = 1;
                // 返回 true 表示这个事件已经被处理，Qt 不需要进一步处理它
                return true;
            }
        }
    }
#endif // Q_OS_WIN

    // 如果不是我们关心的 Windows 消息，或者在非 Windows 平台，
    // 将事件传递给基类进行默认处理
    return QWidget::nativeEvent(eventType, message, result);
}