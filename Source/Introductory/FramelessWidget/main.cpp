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
        qDebug("Warning: Could not open style.qss resource file!");
    }

    MainWindow window;
    window.setWindowTitle("Frameless Window (Helper Example)"); // 设置窗口标题
    // window.setWindowIcon(QIcon(":/Images/logo.png")); // 可选：设置窗口图标
    window.resize(500, 350); // 设置窗口初始大小
    window.show();

    return a.exec();
}