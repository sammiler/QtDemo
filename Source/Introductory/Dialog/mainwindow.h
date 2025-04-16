#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declarations
class QPushButton;
class QVBoxLayout;
class QWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showModalDialog();
    void showNonModalDialog();
    void showSemiModalDialog();

private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QPushButton *modalButton;
    QPushButton *nonModalButton;
    QPushButton *semiModalButton;
};
#endif // MAINWINDOW_H