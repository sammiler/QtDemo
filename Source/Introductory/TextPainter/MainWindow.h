#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void setupUI();

    QStackedWidget *stackedWidget;
    QPushButton *basicButton;
    QPushButton *alignButton;
    QPushButton *wrapButton;
    QPushButton *elideButton;
    QPushButton *fontButton;
};

#endif // MAINWINDOW_H