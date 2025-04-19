//
// Created by sammiler on 2025/4/18.
//
#include <QApplication>
#include "mainwindow.h"
#include <QDebug> // 需要 qDebug

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 可选：设置应用程序名称，用于 QTemporaryFile 的文件名模板
    QCoreApplication::setApplicationName("FileIconsExample");

    MainWindow window;
    window.setWindowTitle("File Icons by Extension Example"); // 设置窗口标题
    window.resize(400, 500); // 设置窗口初始大小
    window.show();

    return a.exec();
}