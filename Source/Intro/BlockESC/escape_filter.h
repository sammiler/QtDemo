#ifndef ESCAPE_FILTER_H
#define ESCAPE_FILTER_H

#include <QObject>    // 继承自 QObject
#include <QEvent>     // 需要 QEvent
#include <QKeyEvent>  // 需要 QKeyEvent
#include <QDialog>    // 需要 QDialog (qobject_cast)

class EscapeFilter : public QObject
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit EscapeFilter(QObject *parent = nullptr);
    ~EscapeFilter();

protected:
    // 重写 eventFilter 方法来处理被观察对象的事件
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // ESCAPE_FILTER_H