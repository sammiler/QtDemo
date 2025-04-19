//
// Created by sammiler on 2025/4/18.
//
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;
    window.setWindowTitle("Switch Control Example"); // 设置窗口标题
    window.setMinimumSize(QSize(300, 300));
    window.show();

    return a.exec();
}