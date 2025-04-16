#ifndef _mycustomevent_H_
#define _mycustomevent_H_
#include <QEvent>
#include <QVariant>

class MyCustomEvent : public QEvent
{
public:
    enum { Type = QEvent::User + 1 }; // 确保类型唯一

    explicit MyCustomEvent(const QVariant& data);
    ~MyCustomEvent() override;

     QVariant getData() const;

private:
    QVariant m_data;
};


#endif // _mycustomevent_H_