#include <QApplication>
#include "mainwindow.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap testPixmap(":/Images/open"); // 使用你在 QSS 中应该用的那个资源路径
    if (testPixmap.isNull()) {
        qDebug() << "错误：无法加载资源图片！路径可能不对或资源未编译：:/Images/open.png";
    } else {
        qDebug() << "成功加载资源图片：:/Images/open.png";
    }
    // 对其他图片也进行类似测试
    QPixmap testHoverPixmap(":/Images/openHover"); // 使用对应的资源路径
    if (testHoverPixmap.isNull()) {
        qDebug() << "错误：无法加载资源图片！路径可能不对或资源未编译：:/Images/openHover.png";
    } else {
        qDebug() << "成功加载资源图片：:/Images/openHover.png";
    }
    // ..
    MainWindow w;
    w.show();

    return QApplication::exec();
}