//
// Created by sammiler on 2025/4/18.
//
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载样式表文件 (需要 style.qss 和 resources.qrc)
    QFile styleFile(":/style.qss"); // 从资源文件中加载 style.qss
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString style = QTextStream(&styleFile).readAll();
        a.setStyleSheet(style); // 应用样式表到整个应用程序
        styleFile.close();
        qDebug("Style sheet loaded successfully.");
    } else {
        qDebug("Warning: Could not open style.qss resource file! Ensure style.qss is in resources.qrc");
        // 如果 QSS 加载失败，表格和控件会使用默认样式
    }

    MainWindow window;
    window.setWindowTitle("Custom Delegate Example"); // 设置窗口标题
    window.show();

    return a.exec();
}