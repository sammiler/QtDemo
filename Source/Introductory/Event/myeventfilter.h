#ifndef MYEVENTFILTER_H
#define MYEVENTFILTER_H

#include <QObject>
#include <QEvent>
#include <QVariant>

class MyEventFilter : public QObject
{
    Q_OBJECT
public:
    MyEventFilter(QObject *parent = nullptr);
    ~MyEventFilter() override;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void customEventReceived(const QVariant& data);

private:
};

#endif // MYEVENTFILTER_H