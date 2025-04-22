#include <QApplication>
#include "BannerWidget.h"

int main(int argc, char *argv[])
{
    // 创建Qt应用程序对象
    QApplication a(argc, argv);

    // 创建BannerWidget实例
    BannerWidget banner;

    // 设置窗口标题
    banner.setWindowTitle("Colorful Banner Example");

    // 设置窗口大小
    banner.resize(400, 100); // 可以根据需要调整大小

    // 显示窗口
    banner.show();

    // 启动应用程序事件循环
    return a.exec();
}