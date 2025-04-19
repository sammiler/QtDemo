#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget> // 继承自 QWidget
#include <QVBoxLayout> // 需要布局
#include <QDebug>      // 需要 qDebug

#include "SwitchControl.h" // 包含自定义控件头文件

class MainWindow : public QWidget
{
    Q_OBJECT // 需要 Q_OBJECT 宏，因为声明了槽函数 onToggled

public:
    explicit MainWindow(QWidget *parent = nullptr); // 使用 nullptr
    ~MainWindow();

    private slots:
        // 示例槽函数，接收 SwitchControl 的 toggled 信号
        void onToggled(bool checked);

private:
    // 示例 SwitchControl 实例指针
    SwitchControl *m_switchControl1;
    SwitchControl *m_switchControl2;
    SwitchControl *m_switchControl3;
};

#endif // MAINWINDOW_H