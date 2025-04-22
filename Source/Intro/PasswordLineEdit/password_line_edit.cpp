#include "password_line_edit.h"
#include <QKeySequence> // 需要 QKeySequence
#include <QDebug>       // 需要 qDebug

// 构造函数
PasswordLineEdit::PasswordLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    qDebug() << "PasswordLineEdit created.";
    // 注意：基础设置如 setEchoMode, setMaxLength, setContextMenuPolicy
    // 在 mainwindow.cpp 中统一设置，也可以在这里设置。
    // 如果希望它是天生具备这些属性的“密码框”，在这里设置更合适。
    // 例如：
    // setEchoMode(QLineEdit::Password);
    // setMaxLength(16);
    // setContextMenuPolicy(Qt::NoContextMenu);
}

// 析构函数
PasswordLineEdit::~PasswordLineEdit()
{
    qDebug() << "PasswordLineEdit destroyed.";
}

// 重写 keyPressEvent 方法
void PasswordLineEdit::keyPressEvent(QKeyEvent *event)
{
    // 检查按键事件是否匹配“全选”、“复制”、“粘贴”这三个标准的 QKeySequence
    if(event->matches(QKeySequence::SelectAll)
       || event->matches(QKeySequence::Copy)
       || event->matches(QKeySequence::Paste))
    {
        // 如果匹配，直接返回，不调用基类方法，从而屏蔽这些按键功能
        qDebug() << "Blocked key event by override:" << event->key();
        return;
    }

    // 对于其他按键事件，调用基类 QLineEdit 的 keyPressEvent 方法进行默认处理 (输入字符等)
    QLineEdit::keyPressEvent(event);
}

// 重写 mouseMoveEvent 方法
void PasswordLineEdit::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event); // 避免编译器警告

    // 直接返回，不调用基类 QLineEdit 的 mouseMoveEvent 方法。
    // 这会屏蔽鼠标在输入框上移动时的默认行为，例如改变光标形状或触发某些内部状态更新。
    // 但是，用户仍然可以点击输入框。
    // QLineEdit::mouseMoveEvent(event); // 如果调用基类，默认行为会发生
    qDebug() << "Blocked mouse move event by override.";
}

// 重写 mouseDoubleClickEvent 方法
void PasswordLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event); // 避免编译器警告

    // 直接返回，不调用基类 QLineEdit 的 mouseDoubleClickEvent 方法。
    // 这会屏蔽双击输入框时的默认行为，例如全选输入框中的文本。
    // QLineEdit::mouseDoubleClickEvent(event); // 如果调用基类，默认行为会发生 (全选)
    qDebug() << "Blocked mouse double click event by override.";
}

// 可选：重写 contextMenuEvent 方法，更彻底地屏蔽右键菜单
/*
void PasswordLineEdit::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event); // 避免编译器警告
    // 直接返回，不调用基类方法，阻止显示默认的右键菜单
    // 如果想显示一个自定义的空菜单，可以在这里创建并执行一个空 QMenu
    // event->accept(); // 或者接受事件，阻止传播
    qDebug() << "Blocked context menu event by override.";
}
*/