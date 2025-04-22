#include "mytimerwindow.h"
#include <QDebug>

MyTimerWindow::MyTimerWindow(QWidget *parent)
    : QMainWindow(parent), timer(new QTimer(this)), counter(0)
{
    setWindowTitle("初始标题");

    // 连接定时器的 timeout() 信号到 updateCaption() 槽
    connect(timer, &QTimer::timeout, this, &MyTimerWindow::updateCaption);

    // 设置定时器间隔为 1000 毫秒 (1秒) 并启动
    timer->start(1000);
}

MyTimerWindow::~MyTimerWindow()
{
    delete timer;
}

void MyTimerWindow::updateCaption()
{
    counter++;
    QString newCaption = QString("当前时间: %1 | 计数器: %2")
                         .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                         .arg(counter);
    setWindowTitle(newCaption);
    // 可以添加更多的功能，例如在特定计数器值时执行某些操作
    if (counter % 5 == 0) {
        qDebug() << "计数器达到" << counter;
    }
}