#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget> // 继承自 QWidget
#include <QPushButton> // 需要 QPushButton
#include <QLineEdit>   // 需要 QLineEdit
#include <QGridLayout> // 需要布局

class MainWindow : public QWidget
{
    Q_OBJECT // 需要 Q_OBJECT 宏，因为它是顶级窗口

public:
    explicit MainWindow(QWidget *parent = nullptr); // 使用 nullptr
    ~MainWindow();

private:
    // 声明控件指针
    QPushButton *m_button1;
    QPushButton *m_button2;
    QPushButton *m_button3;

    QLineEdit *m_lineEdit1; // 这是文本为 "6" 的输入框
    QLineEdit *m_lineEdit2; // 这是文本为 "4" 的输入框
    QLineEdit *m_lineEdit3; // 这是文本为 "2" 的输入框

    QGridLayout *m_layout; // 布局
};

#endif // MAINWINDOW_H