#include <QApplication>
#include <QColor>
#include <QPalette>
#include "resizableframelesswidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ResizableFramelessWidget widget;
    widget.setWindowTitle("Resizable Frameless Window");
    widget.resize(400, 300); // 设置窗口初始大小

    // 设置一个背景颜色，使其可见 (特别是如果使用了 Qt::WA_TranslucentBackground)
    widget.setAutoFillBackground(true);
    QPalette pal = widget.palette();
    pal.setColor(QPalette::Window, QColor(70, 70, 70)); // 深灰色背景
    widget.setPalette(pal);

    widget.show();

    return a.exec();
}