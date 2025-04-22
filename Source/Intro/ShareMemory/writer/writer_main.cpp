#include <QApplication>
#include "writerwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WriterWindow writer;
    writer.setWindowTitle("Image Writer (Shared Memory)");
    writer.show();

    return a.exec();
}