#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QCoreApplication>
#include "myeventfilter.h"
#include "mycustomevent.h"

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = nullptr);
    ~MyWindow() override;

private slots:
    void sendCustomEvent();
    void handleCustomEventData(const QVariant& data);

protected:
    bool event(QEvent *event) override; // 可选：在窗口自身处理自定义事件
private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QLabel *label;
    QPushButton *button;
    MyEventFilter *eventFilter;
};

#endif // MYWINDOW_H