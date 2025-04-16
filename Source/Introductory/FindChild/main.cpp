#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Creates the application instance
    Widget w; // Creates the main window instance
    w.show(); // Shows the main window
    return a.exec(); // Starts the application event loop
}