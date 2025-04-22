#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("QPainterPath Demo");
    window.resize(800, 600);
    window.show();
    return app.exec();
}