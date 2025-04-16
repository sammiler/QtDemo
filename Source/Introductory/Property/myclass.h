#ifndef _myclass_H_
#define __myclass_H__


#include <QObject>
#include <QMetaClassInfo>
#include <QDebug>

class MyClass : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Version", "3.0.0")
    Q_PROPERTY(Priority priority READ  priority WRITE setPriority NOTIFY priorityChanged)
public:
    explicit MyClass(QObject * parent = 0)
    {
        connect(this, &MyClass::priorityChanged, this,&MyClass::priorityChangedSlot);
    }
    ~MyClass(){}

    enum Priority {
        High,
        Low,
        VeryHigh,
        VeryLow
    };

    Q_ENUM(Priority)

    void setPriority(Priority priority)
    {
        m_priority = priority;
    }
    Priority priority()const
    {
        return m_priority;
    }
    signals:
        void priorityChanged(Priority);
    public slots:
        void priorityChangedSlot(Priority)
        {
            qDebug() << "Changed!!";
        }
    private:
        Priority m_priority;
};

#endif // __myclass_H__