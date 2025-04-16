#include <QApplication>
#include "mytimerwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTimerWindow w;
    w.show();
    return a.exec();
}