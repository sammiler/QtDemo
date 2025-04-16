#include "mainwindow.h"
#include <QApplication>
#include <QLocale> // For locale-specific strings if needed
#include <QTranslator> // For translation if needed
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Optional: Setup for translations if you were using them
    // QTranslator translator;
    // const QStringList uiLanguages = QLocale::system().uiLanguages();
    // for (const QString &locale : uiLanguages) {
    //     const QString baseName = "DialogModes_" + QLocale(locale).name();
    //     if (translator.load(":/i18n/" + baseName)) {
    //         a.installTranslator(&translator);
    //         break;
    //     }
    // }

    qDebug() << "Creating MainWindow...";
    MainWindow w;
    w.show();
    qDebug() << "Starting application event loop...";
    int result = a.exec();
    qDebug() << "Application event loop finished. Exiting.";
    return result;
}