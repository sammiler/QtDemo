#ifndef PASSWORD_LINE_EDIT_H
#define PASSWORD_LINE_EDIT_H

#include <QLineEdit> // 继承自 QLineEdit
#include <QKeyEvent> // 需要 QKeyEvent
#include <QMouseEvent> // 需要 QMouseEvent

class PasswordLineEdit : public QLineEdit
{
    Q_OBJECT // 需要 Q_OBJECT 宏，因为继承自 QLineEdit

public:
    explicit PasswordLineEdit(QWidget *parent = nullptr); // 使用 nullptr
    ~PasswordLineEdit();

protected:
    // 重写 keyPressEvent 方法来屏蔽全选、复制、粘贴
    void keyPressEvent(QKeyEvent *event) override; // 使用 override 关键字

    // 重写 mouseMoveEvent 方法来屏蔽鼠标移动的默认行为 (如改变光标)
    void mouseMoveEvent(QMouseEvent *event) override; // 使用 override 关键字

    // 重写 mouseDoubleClickEvent 方法来屏蔽双击的默认行为 (如全选文本)
    void mouseDoubleClickEvent(QMouseEvent *event) override; // 使用 override 关键字

    // 可选：重写 contextMenuEvent 来确保右键菜单被屏蔽
    // void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // PASSWORD_LINE_EDIT_H