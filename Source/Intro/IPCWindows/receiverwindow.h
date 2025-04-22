#ifndef RECEIVERWINDOW_H
#define RECEIVERWINDOW_H

#include <QWidget>
#include <QLabel>

class ReceiverWindow : public QWidget
{
    Q_OBJECT // 启用 Qt 元对象系统

public:
    explicit ReceiverWindow(QWidget *parent = nullptr); // 构造函数
    ~ReceiverWindow(); // 析构函数

protected:
    // 重写 nativeEvent 方法来处理原生窗口事件 (如 Windows 消息)
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override; // 使用 override 关键字

private:
    QLabel *receivedMessageLabel; // 显示接收到消息的标签
};

#endif // RECEIVERWINDOW_H