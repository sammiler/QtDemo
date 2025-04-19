#ifndef PASSWORD_EVENT_FILTER_H
#define PASSWORD_EVENT_FILTER_H

#include <QObject> // 继承自 QObject
#include <QEvent>  // 需要 QEvent
#include <QLineEdit> // 需要 QLineEdit (前向声明或包含)
#include <QKeyEvent> // 需要 QKeyEvent
#include <QKeySequence> // 需要 QKeySequence

// 前向声明 QLineEdit，如果只在 .cpp 中用到 QLineEdit 指针
// class QLineEdit;

class PasswordEventFilter : public QObject
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit PasswordEventFilter(QObject *parent = nullptr); // 使用 nullptr
    ~PasswordEventFilter();

protected:
    // 重写 eventFilter 方法来处理被观察对象的事件
    bool eventFilter(QObject *obj, QEvent *event) override; // 使用 override 关键字
};

#endif // PASSWORD_EVENT_FILTER_H