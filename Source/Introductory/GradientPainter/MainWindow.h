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
    QPushButton *linearButton;
    QPushButton *radialButton;
    QPushButton *conicalButton;
};

#endif // MAINWINDOW_H