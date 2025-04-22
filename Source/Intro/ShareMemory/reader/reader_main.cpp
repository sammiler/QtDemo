#include <QApplication>
#include "readerwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ReaderWindow reader;
    reader.setWindowTitle("Image Reader (Shared Memory)");
    reader.show();

    return a.exec();
}