//
// Created by sammiler on 2025/4/18.
//
#include <QApplication>
#include "mainwindow.h" // Include the main window header

int main(int argc, char *argv[])
{
    // Create the application object
    QApplication a(argc, argv);

    // Create the main window
    MainWindow w;

    // Show the main window
    w.show();

    // Start the application event loop
    return a.exec();
}