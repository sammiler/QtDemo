#include "myeventfilter.h"
#include "mycustomevent.h"
#include <QDebug>

MyEventFilter::MyEventFilter(QObject *parent)
    : QObject(parent)
{
}

MyEventFilter::~MyEventFilter()
= default;

bool MyEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == MyCustomEvent::Type) {
        const auto customEvent = dynamic_cast<MyCustomEvent*>(event);
        const QVariant data = customEvent->getData();
        qDebug() << "事件过滤器捕获到自定义事件，数据:" << data;
        emit customEventReceived(data); // 发送信号，通知接收者
        return QObject::eventFilter(watched, event); // 返回 true 表示该事件已被处理，不再传递给目标对象
    }
    return QObject::eventFilter(watched, event); // 调用父类的 eventFilter 方法，让其他事件继续传递
}