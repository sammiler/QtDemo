#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget> // 继承自 QWidget
#include <QVBoxLayout> // 需要布局
#include <QLabel>      // 添加一个标签作为内容示例
#include "frameless_helper.h" // 包含无边框助手头文件

class MainWindow : public QWidget
{
    Q_OBJECT // QObject 是必需的，因为它是顶级窗口且 good practice

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    FramelessHelper *m_framelessHelper; // 无边框助手对象
    QLabel *m_contentLabel;           // 示例内容标签
};

#endif // MAINWINDOW_H