#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget> // 继承自 QWidget
#include <QLineEdit>       // 需要 QLineEdit
#include <QVBoxLayout>     // 需要布局
#include <QLabel>          // 需要 QLabel
#include "password_event_filter.h" // 需要事件过滤器头文件
#include "password_line_edit.h"    // 需要自定义输入框头文件

class MainWindow : public QWidget
{
    Q_OBJECT // 需要 Q_OBJECT 宏，因为是顶级窗口

public:
    explicit MainWindow(QWidget *parent = nullptr); // 使用 nullptr
    ~MainWindow();

private:
    // 声明不同类型的密码输入框实例指针
    QLineEdit *m_standardLineEdit;        // 普通输入框 (用于对比)
    QLineEdit *m_lineEditWithFilter;    // 应用事件过滤器的输入框
    PasswordEventFilter *m_eventFilter;   // 事件过滤器对象
    PasswordLineEdit *m_customLineEdit; // 继承 QLineEdit 实现的输入框
};

#endif // MAINWINDOW_H