#include <QApplication>
#include "serverwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ServerWindow serverWindow;
    serverWindow.setWindowTitle("Fortune Server");
    serverWindow.show(); // 显示服务器窗口，可选，但方便知道服务器是否运行

    return a.exec();
}