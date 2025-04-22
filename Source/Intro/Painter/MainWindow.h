#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupUI();

    QStackedWidget *stackedWidget;
    QPushButton *textButton;
    QPushButton *lineButton;
    QPushButton *rectButton;
    QPushButton *arcButton;
    QPushButton *ellipseButton;
    QPushButton *polygonButton;
    QPushButton *imageButton;
};

#endif // MAINWINDOW_H