#ifndef SENDERWINDOW_H
#define SENDERWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class SenderWindow final : public QWidget
{
    Q_OBJECT // 启用 Qt 元对象系统，支持信号槽等

public:
    explicit SenderWindow(QWidget *parent = nullptr); // 构造函数
    ~SenderWindow() override; // 析构函数

    private slots:
        void onSendMessage(); // 发送消息的槽函数

private:
    QLineEdit *messageLineEdit; // 文本输入框
    QPushButton *sendButton;    // 发送按钮
};

#endif // SENDERWINDOW_H