#include <QApplication>
#include "mainwindow.h" // 包含主窗口头文件

int main(int argc, char *argv[])
{
    // 创建应用程序对象
    QApplication a(argc, argv);

    // 创建主窗口
    MainWindow w;

    // 显示主窗口
    w.show();

    // 启动应用程序事件循环
    return a.exec();
}