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
    QPushButton *ellipseButton;
    QPushButton *polygonButton;
    QPushButton *rectButton;
    QPushButton *textButton;
    QPushButton *arcButton;
    QPushButton *bezierButton;
};

#endif // MAINWINDOW_H