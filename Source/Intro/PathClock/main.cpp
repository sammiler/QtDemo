#include "ClockWidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ClockWidget window;
    window.show();
    return app.exec();
}