#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>     // 继承自 QWidget
#include <QPushButton> // 需要 QPushButton
#include <QVBoxLayout> // 需要布局

// 声明我们将要创建的对话框类，避免在头文件中包含它们的完整定义
class DefaultEscapeDialog;
class EventFilterEscapeDialog;
class KeyPressOverrideEscapeDialog;
class RejectOverrideDialog;

class MainWindow : public QWidget
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
        // 启动不同对话框的槽函数
        void onLaunchDefault();
    void onLaunchEventFilter();
    void onLaunchKeyPressOverride();
    void onLaunchRejectOverride();

private:
    // 按钮
    QPushButton *m_btnDefault;
    QPushButton *m_btnEventFilter;
    QPushButton *m_btnKeyPressOverride;
    QPushButton *m_btnRejectOverride;
};

#endif // MAINWINDOW_H