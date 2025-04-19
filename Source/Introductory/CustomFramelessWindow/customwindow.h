#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H

#include <QWidget> // 继承自 QWidget
#include <QVBoxLayout> // 需要布局

class CustomWindow : public QWidget // Q_OBJECT 可选，如果不需要自定义信号槽
{
    // Q_OBJECT // 如果不添加自定义信号槽，这里可以不加 Q_OBJECT

public:
    explicit CustomWindow(QWidget *parent = nullptr);
    ~CustomWindow();

private:
    // 你可以在这里添加主窗口的其他控件和布局
};

#endif // CUSTOMWINDOW_H