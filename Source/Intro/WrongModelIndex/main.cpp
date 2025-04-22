#include <QApplication>
#include "correctmainwindow.h"
#include "incorrectmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create the correct window
    CorrectMainWindow correctWin;
    correctWin.move(100, 100); // Position windows side-by-side
    correctWin.show();

    // Create the incorrect window
    IncorrectMainWindow incorrectWin;
    incorrectWin.move(900, 100); // Position windows side-by-side
    incorrectWin.show();


    return a.exec();
}