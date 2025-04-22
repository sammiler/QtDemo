//
// Created by sammiler on 2025/4/18.
//
#include <QApplication>
#include <QFile>       // 用于读取样式表文件
#include <QTextStream> // 用于读取样式表文件
#include "customwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载样式表文件
    QFile styleFile(":/style.qss"); // 从资源文件中加载 style.qss
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString style = QTextStream(&styleFile).readAll();
        a.setStyleSheet(style); // 应用样式表到整个应用程序
        styleFile.close();
    } else {
        qDebug("Warning: Could not open style.qss resource file!");
    }

    CustomWindow window;
    window.setWindowTitle("Custom Frameless Window"); // 设置窗口标题
    // window.setWindowIcon(QIcon(":/Images/logo.png")); // 可选：设置窗口图标 (如果资源文件中有)
    window.resize(400, 300); // 设置窗口初始大小
    window.show();

    return a.exec();
}