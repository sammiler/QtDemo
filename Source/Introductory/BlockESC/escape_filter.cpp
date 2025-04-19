#include "escape_filter.h"
#include <QDebug> // 需要 qDebug

// 构造函数
EscapeFilter::EscapeFilter(QObject *parent)
    : QObject(parent)
{
    qDebug() << "EscapeFilter created.";
}

// 析构函数
EscapeFilter::~EscapeFilter()
{
    qDebug() << "EscapeFilter destroyed.";
}

// 事件过滤方法
bool EscapeFilter::eventFilter(QObject *obj, QEvent *event)
{
    // 将事件的接收者尝试转换为 QDialog 指针
    QDialog *pDialog = qobject_cast<QDialog *>(obj);

    // 检查转换是否成功 (确保事件是发给 QDialog 的)
    if (pDialog != nullptr)
    {
        // 检查事件类型是否是键盘按下事件
        if (event->type() == QEvent::KeyPress)
        {
            // 将 QEvent 转换为 QKeyEvent 指针
            QKeyEvent *pKeyEvent = static_cast<QKeyEvent*>(event);

            // 检查按键是否是 Escape 键
            if (pKeyEvent->key() == Qt::Key_Escape)
            {
                qDebug() << "EscapeFilter: Filtered Escape key press on" << pDialog->windowTitle();
                // 返回 true 表示这个 Escape 按键事件已经被过滤器处理，不再传递给目标对象 (QDialog)
                // 这阻止了 QDialog 默认的 keyPressEvent 处理 Escape 键
                return true;
            }
        }
    }

    // 对于未被过滤的事件，或者事件不是发给 QDialog 的，
    // 调用基类 QObject::eventFilter 方法，将事件继续传递
    return QObject::eventFilter(obj, event);
}