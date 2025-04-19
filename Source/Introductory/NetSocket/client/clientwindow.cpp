#include "clientwindow.h"
#include "../ipc_defs.h" // 包含服务器名称定义
#include <QTimer>        // 需要 QTimer 用于单次定时器
#include <QDebug>        // 需要 qDebug
#include <QPointer>

ClientWindow::ClientWindow(QWidget *parent)
    : QWidget(parent)
{
    // 创建 QLocalSocket 实例
    socket = new QLocalSocket(this);

    // 创建 UI 元素
    hostLineEdit = new QLineEdit(this);
    // 默认服务器名称使用 ipc_defs.h 中定义的常量
    hostLineEdit->setText(FORTUNE_SERVER_NAME);
    hostLineEdit->setPlaceholderText("Server name (e.g., fortune)");

    statusLabel = new QLabel("Ready to request fortune", this);
    statusLabel->setWordWrap(true); // 允许文本换行
    statusLabel->setAlignment(Qt::AlignCenter); // 文本居中

    getFortuneButton = new QPushButton("Get Fortune", this);

    // 设置布局
    const QPointer<QVBoxLayout> layout = new QVBoxLayout(this);
    layout->addWidget(hostLineEdit);
    layout->addWidget(statusLabel);
    layout->addWidget(getFortuneButton);
    setLayout(layout);

    // 设置窗口大小
    resize(300, 200); // 可以根据需要调整大小

    // 连接信号和槽 (使用新的信号槽语法)
    // 按钮点击信号连接到请求槽
    connect(getFortuneButton, &QPushButton::clicked, this, &ClientWindow::requestNewFortune);
    // socket 准备好读取数据信号连接到读取槽
    connect(socket, &QLocalSocket::readyRead, this, &ClientWindow::readFortune);
    // socket 错误信号连接到错误处理槽 (使用 QOverload 处理 error 信号的重载)
    connect(socket, QOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error),
            this, &ClientWindow::displayError);

    // 初始化数据块大小为 0
    blockSize = 0;
}

ClientWindow::~ClientWindow()
{
    // QLocalSocket 的父对象是 this，会自动销毁
}

// 槽函数：请求新的财富语录
void ClientWindow::requestNewFortune()
{
    // 禁用按钮，防止重复点击
    getFortuneButton->setEnabled(false);
    // 重置数据块大小
    blockSize = 0;
    // 如果 socket 当前已连接，先断开并重置
    socket->abort();
    // 连接到服务器，使用 hostLineEdit 中的名称
    socket->connectToServer(hostLineEdit->text());

    statusLabel->setText("Connecting to server...");
    qDebug() << "Client: Requesting new fortune from" << hostLineEdit->text();
}

// 槽函数：读取服务器发送的数据
void ClientWindow::readFortune()
{
    // 创建 QDataStream，关联到 socket
    QDataStream in(socket);
    // 设置数据流版本，必须与服务器端写入时的版本一致
    in.setVersion(QDataStream::Qt_4_0);

    // 如果 blockSize 还没有读取，先尝试读取它
    if (blockSize == 0) {
        // 检查是否有足够的数据来读取 quint16 (数据块大小)
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return; // 数据不足，等待更多数据
        // 读取数据块大小
        in >> blockSize;
        qDebug() << "Client: Read block size:" << blockSize;
    }

    // 检查是否已接收到整个数据块
    // socket->bytesAvailable() 是当前缓冲区中可读的总字节数
    // 如果可读字节数小于整个数据块的大小 (除了已读取的 size 本身)，则等待更多数据
    if (socket->bytesAvailable() < blockSize) {
         // 检查流是否已经到达末尾（不应该发生，除非连接异常）
         if (in.atEnd()) {
              qDebug() << "Client: Data stream ended prematurely.";
              return; // 异常情况
         }
        return; // 数据不足，等待更多数据
    }

    // 如果数据已完整接收
    QString nextFortune;
    // 从数据流中读取 QString (财富语录)
    in >> nextFortune;
    qDebug() << "Client: Read fortune:" << nextFortune;

    // 检查是否收到了与当前显示相同的财富语录
    if (nextFortune == currentFortune) {
        // 如果相同，立即再次请求一个新的 (避免重复显示)
        qDebug() << "Client: Received same fortune, requesting again.";
        // 使用单次定时器，延时0毫秒调用 requestNewFortune，避免递归调用过深
        QTimer::singleShot(0, this, &ClientWindow::requestNewFortune);
        return; // 等待新的财富语录
    }

    // 更新当前显示的财富语录
    currentFortune = nextFortune;
    // 在状态标签中显示接收到的财富语录
    statusLabel->setText(currentFortune);
    // 重新启用按钮
    getFortuneButton->setEnabled(true);

    // 注意：QLocalSocket 的 readyRead 信号可能会在接收到部分数据时多次触发。
    // 我们的协议处理逻辑 (先读 size，再读 data) 确保只有在接收到完整数据块后才会处理数据。
    // 在处理完一个完整块后，如果 socket 缓冲区还有剩余数据（例如，服务器连续发送了多个块），
    // readyRead 信号会再次触发，允许我们处理下一个块。
}

// 槽函数：处理 socket 错误
void ClientWindow::displayError(QLocalSocket::LocalSocketError socketError)
{
    // 根据错误类型显示不同的提示信息
    switch (socketError) {
    case QLocalSocket::ServerNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please ensure the server name is correct."));
        break;
    case QLocalSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running and listening on '%1'.")
                                 .arg(hostLineEdit->text()));
        break;
    case QLocalSocket::PeerClosedError:
        // 服务器正常断开连接时会收到这个错误，通常在读取完数据后
        // 如果在等待数据时收到，说明连接异常断开
        if (blockSize > 0) { // 如果已经开始读取数据块
             qDebug() << "Client: Peer closed connection unexpectedly during data transfer.";
             statusLabel->setText("Connection closed by server unexpectedly.");
        } else {
             qDebug() << "Client: Peer closed connection.";
             statusLabel->setText("Connection closed by server.");
        }
        break;
    case QLocalSocket::UnknownSocketError: // 处理 Qt 5.15+ 的 SocketError 枚举
    default:
        // 显示其他未知错误信息
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(socket->errorString()));
        qDebug() << "Client: Socket error:" << socket->errorString();
    }

    // 无论何种错误，重新启用按钮，允许用户再次尝试
    getFortuneButton->setEnabled(true);
    // 重置数据块大小
    blockSize = 0;
}