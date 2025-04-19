//
// Created by sammiler on 2025/4/19.
//
#include <QApplication>
#include <QFile> // 用于读取 QSS 文件
#include <QTextStream> // 用于读取文件内容
#include <QDebug> // 用于调试输出

#include "mainwindow.h"
#include "TableModel.h" // 包含模型头文件以确保结构体定义可用

// 在 main 函数开始时注册元类型，确保在 QApplication 对象创建之前完成
// 这样信号槽连接时才能识别这个自定义类型
static int recordListMetaTypeId = qRegisterMetaType<QList<FileDownloadRecord>>("QList<FileDownloadRecord>");


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载并应用 QSS 样式
    QFile styleFile("style.qss"); // 假设 style.qss 在可执行文件同一目录
    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream ts(&styleFile);
        qApp->setStyleSheet(ts.readAll());
        styleFile.close();
        qDebug() << "Applied style.qss";
    }
    else
    {
        qDebug() << "Could not open style.qss";
    }


    // 创建主窗口
    MainWindow w;

    // 显示主窗口
    w.show();

    // 启动应用程序事件循环
    return QApplication::exec();
}