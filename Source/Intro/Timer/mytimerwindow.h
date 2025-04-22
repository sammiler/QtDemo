#ifndef MYTIMERWINDOW_H
#define MYTIMERWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <QDateTime>

class MyTimerWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyTimerWindow(QWidget *parent = nullptr);
    ~MyTimerWindow() override;

private slots:
    void updateCaption();

private:
    QTimer *timer;
    int counter;
};

#endif // MYTIMERWINDOW_H