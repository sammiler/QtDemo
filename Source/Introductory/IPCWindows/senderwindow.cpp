#include <QVBoxLayout> // 垂直布局
#include <QMessageBox> // 消息框
#include "senderwindow.h"
#include "ipc_defs.h" // 包含 IPC 定义和 Windows 头文件

SenderWindow::SenderWindow(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口标题
    setWindowTitle("Sender Window");

    // 创建 UI 元素
    messageLineEdit = new QLineEdit(this);
    messageLineEdit->setPlaceholderText("Enter message to send...");
    sendButton = new QPushButton("Send WM_COPYDATA", this);

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(messageLineEdit);
    layout->addWidget(sendButton);
    setLayout(layout);

    // 连接信号和槽
    connect(sendButton, &QPushButton::clicked, this, &SenderWindow::onSendMessage);
}

SenderWindow::~SenderWindow()
{
    // QWidget 的子控件会自动销毁，无需在这里手动 delete
}

// 槽函数：发送 WM_COPYDATA 消息
void SenderWindow::onSendMessage()
{
    // 仅在 Windows 平台上执行发送逻辑
#ifdef Q_OS_WIN
    // 获取要发送的消息文本
    QString message = messageLineEdit->text();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Message cannot be empty.");
        return;
    }

    // 使用 FindWindowW 查找接收窗口
    // 第一个参数是窗口类名 (NULL 表示任意类)
    // 第二个参数是窗口标题 (LPWSTR 是宽字符指针)
    HWND hwnd = ::FindWindowW(NULL, (LPWSTR)RECEIVER_WINDOW_TITLE.utf16());

    // 如果找到了窗口并且它是一个有效的窗口句柄
    if (hwnd && ::IsWindow(hwnd))
    {
        // 将 QString 转换为 UTF-8 字节数组
        QByteArray data = message.toUtf8();

        // 准备 COPYDATASTRUCT 结构体
        COPYDATASTRUCT copydata;
        copydata.dwData = CUSTOM_TYPE;          // 设置自定义数据类型
        copydata.cbData = data.size();          // 设置数据大小 (字节)
        copydata.lpData = data.data();          // 设置指向数据的指针

        // 获取发送窗口的句柄 (用于 WM_COPYDATA 的 wParam)
        HWND sender = (HWND)effectiveWinId();

        // 发送 WM_COPYDATA 消息
        // 第一个参数是接收窗口句柄
        // 第二个参数是消息类型 WM_COPYDATA
        // 第三个参数是发送窗口句柄 (作为 WPARAM)
        // 第四个参数是指向 COPYDATASTRUCT 结构体的指针 (作为 LPARAM)
        // ::SendMessage 会阻塞直到消息被处理
        LRESULT result = ::SendMessage(hwnd, WM_COPYDATA, reinterpret_cast<WPARAM>(sender), reinterpret_cast<LPARAM>(&copydata));

        // 可选：检查 SendMessage 的返回值
        if (result == 1) { // 如果接收方处理了消息并返回了 1
            qDebug("Message sent and processed successfully.");
        } else {
            qDebug("Message sent, but receiver might not have processed it (returned %lld).", (long long)result);
        }

    }
    else
    {
        QMessageBox::warning(this, "Error", QString("Receiver window '%1' not found.").arg(RECEIVER_WINDOW_TITLE));
    }
#else
    // 在非 Windows 平台给出提示
    QMessageBox::information(this, "Info", "WM_COPYDATA is a Windows-specific mechanism.");
#endif
}