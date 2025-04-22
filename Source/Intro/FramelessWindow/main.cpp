//
// Created by sammiler on 2025/4/18.
//
#include <QApplication>
#include "framelesswidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FramelessWidget widget;
    widget.setWindowTitle("Frameless Movable Window (WinAPI)");
    widget.resize(300, 200); // 设置窗口初始大小
    widget.show();

    return a.exec();
}