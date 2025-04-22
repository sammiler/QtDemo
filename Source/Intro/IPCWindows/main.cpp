//
// Created by sammiler on 2025/4/18.
//
#include <QApplication>
#include "senderwindow.h"
#include "receiverwindow.h"

int main(int argc, char *argv[])
{
    // 创建Qt应用程序对象
    QApplication a(argc, argv);

    // 创建发送窗口实例
    SenderWindow sender;
    sender.show(); // 显示发送窗口

    // 创建接收窗口实例
    ReceiverWindow receiver;
    receiver.show(); // 显示接收窗口

    // 启动应用程序事件循环
    return a.exec();
}