//
// Created by sammiler on 2025/4/18.
//
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;
    window.setWindowTitle("Secure Password Fields Example"); // 设置窗口标题
    window.show();

    return a.exec();
}