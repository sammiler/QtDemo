#include <QApplication>
#include "mywindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWindow w;
    w.show();
    return a.exec();
}