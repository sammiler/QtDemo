#include "serverwindow.h"
#include "../ipc_defs.h" // 包含服务器名称定义
#include <QLocalSocket>  // 需要 QLocalSocket
#include <QDataStream>   // 需要 QDataStream
#include <QtGlobal>      // 需要 qrand(), qsrand()
#include <QDateTime>     // 需要 QDateTime 用于随机数种子
#include <QRandomGenerator>

ServerWindow::ServerWindow(QWidget *parent)
    : QWidget(parent)
{
    // 创建 QLocalServer 实例
    server = new QLocalServer(this);

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    statusLabel = new QLabel("Server is not listening.", this);
    layout->addWidget(statusLabel);
    setLayout(layout);

    // 告诉服务器监听指定名称的连接
    // 如果服务器当前已经在监听 (可能是另一个实例)，则 listen 返回 false
    if (!server->listen(FORTUNE_SERVER_NAME)) { // FORTUNE_SERVER_NAME 来自 ipc_defs.h
        // 监听失败，显示错误信息并关闭窗口
        QMessageBox::critical(this, tr("Fortune Server"),
                            tr("Unable to start the server: %1.")
                            .arg(server->errorString()));
        statusLabel->setText("Server failed to start: " + server->errorString());
        // close(); // 或者根据需要选择是否关闭
        return;
    }

    statusLabel->setText("Server is listening on '" + FORTUNE_SERVER_NAME + "'");
    qDebug() << "Server is listening on" << FORTUNE_SERVER_NAME;


    // 初始化财富语录列表
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.")
             << tr("You will be surprised by a loud noise.")
             << tr("You will feel hungry again in another hour.")
             << tr("You might have mail.")
             << tr("You cannot kill time without injuring eternity.")
             << tr("Computers are not intelligent. They only think they are.");

    // 播种随机数生成器，以获得不同的随机数序列
    qsrand(QDateTime::currentMSecsSinceEpoch());
    // 当有新客户端连接时，连接 newConnection 信号到 sendFortune 槽
    // 使用新的信号槽语法
    connect(server, &QLocalServer::newConnection, this, &ServerWindow::sendFortune);
}

ServerWindow::~ServerWindow() = default;


// 槽函数：当有新客户端连接时被调用，发送一个随机的财富语录
void ServerWindow::sendFortune()
{
    // nextPendingConnection() 返回下一个待处理连接的 QLocalSocket 对象
    // 这个 socket 对象被创建时以 server 作为父对象，因此当 server 销毁时它也会销毁
    QLocalSocket *clientConnection = server->nextPendingConnection();

    // 当客户端连接断开时，使用 deleteLater 安全地删除 clientConnection 对象
    connect(clientConnection, &QLocalSocket::disconnected,
            clientConnection, &QLocalSocket::deleteLater);

    // 准备要发送的数据块
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly); // 关联到数据块，写入模式
    out.setVersion(QDataStream::Qt_4_0);           // 设置数据流版本 (客户端读取时也需要相同版本)

    // 数据协议：先写入数据块的大小 (quint16)，然后写入实际数据 (QString)
    // 先写入一个占位符 (0)，稍后再填充正确的大小
    out << (quint16)0;
    // 从 fortunes 列表中随机选择一个字符串并写入数据流
    out << fortunes.at(qrand() % fortunes.size());

    // 返回到数据块的开头，以填充正确的大小
    out.device()->seek(0);
    // 计算实际数据的大小 (整个 block 的大小减去 quint16 占位符的大小)
    out << (quint16)(block.size() - sizeof(quint16));

    // 将数据块写入客户端 socket
    clientConnection->write(block);
    // 刷新缓冲区，确保数据立即发送
    clientConnection->flush();

    // 发送完数据后断开连接 (对于这种一次性服务的协议)
    clientConnection->disconnectFromServer();

    qDebug() << "Server: Sent fortune to client. Block size:" << block.size();
}