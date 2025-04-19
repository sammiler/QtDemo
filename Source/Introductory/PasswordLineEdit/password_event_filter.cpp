#include "password_event_filter.h"
#include <QDebug> // 需要 qDebug

// 构造函数
PasswordEventFilter::PasswordEventFilter(QObject *parent)
    : QObject(parent)
{
    qDebug() << "PasswordEventFilter created.";
}

// 析构函数
PasswordEventFilter::~PasswordEventFilter()
{
    qDebug() << "PasswordEventFilter destroyed.";
}

// 事件过滤方法
bool PasswordEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    // 将事件的接收者尝试转换为 QLineEdit 指针
    QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(obj);

    // 检查转换是否成功 (确保事件是发给 QLineEdit 的)
    if (pLineEdit != nullptr) // 使用 nullptr
    {
        // 根据事件类型进行过滤判断
        switch (event->type())
        {
            // 过滤鼠标移动事件和鼠标双击事件
            case QEvent::MouseMove:          // 鼠标移动事件
            case QEvent::MouseButtonDblClick: // 鼠标双击事件
                // 返回 true 表示这个事件已经被过滤器处理，不再传递给目标对象 (pLineEdit)
                return true;

            // 过滤键盘按下事件
            case QEvent::KeyPress:
            {
                // 将 QEvent 转换为 QKeyEvent 指针
                QKeyEvent *pKeyEvent = static_cast<QKeyEvent*>(event);

                // 检查按键事件是否匹配“全选”、“复制”、“粘贴”这三个标准的 QKeySequence
                if(pKeyEvent->matches(QKeySequence::SelectAll) // Ctrl+A 或 Cmd+A
                   || pKeyEvent->matches(QKeySequence::Copy)     // Ctrl+C 或 Cmd+C
                   || pKeyEvent->matches(QKeySequence::Paste))   // Ctrl+V 或 Cmd+V
                {
                    // 如果匹配，返回 true 表示过滤掉这些按键事件
                    qDebug() << "Filtered key event:" << pKeyEvent->key();
                    return true;
                }
                // 如果是其他按键事件，不返回 true，继续默认处理 (输入字符等)
                break; // 跳出 switch，让事件继续传递
            }
            // 其他事件类型 (如 MouseButtonPress, MouseButtonRelease, FocusIn, FocusOut 等) 不在这里过滤
            default:
                break; // 跳出 switch，让事件继续传递
        }
    }

    // 对于未被过滤的事件，或者事件不是发给 QLineEdit 的，
    // 调用基类 QObject::eventFilter 方法，将事件继续传递到事件链中的下一个过滤器，
    // 或者最终传递给目标对象 obj (这里是 pLineEdit) 的 normal event handlers。
    return QObject::eventFilter(obj, event);
}