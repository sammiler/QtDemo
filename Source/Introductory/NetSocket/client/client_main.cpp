#include <QApplication>
#include "clientwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ClientWindow clientWindow;
    clientWindow.setWindowTitle("Fortune Client");
    clientWindow.show(); // 显示客户端窗口

    return a.exec();
}