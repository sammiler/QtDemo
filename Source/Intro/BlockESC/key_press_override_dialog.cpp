#include "key_press_override_dialog.h"
#include <QDebug> // 需要 qDebug

KeyPressOverrideEscapeDialog::KeyPressOverrideEscapeDialog(QWidget *parent)
    : QDialog(parent)
{
    // 设置窗口大小
    resize(200, 100);

    // 添加一个标签
    QLabel *label = new QLabel("Escape Key Filtered by\nKeyPressEvent Override.\nDialog will NOT close on Escape.", this);
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    setLayout(layout);

    qDebug() << "KeyPressOverrideEscapeDialog created.";
}

KeyPressOverrideEscapeDialog::~KeyPressOverrideEscapeDialog()
{
    qDebug() << "KeyPressOverrideEscapeDialog destroyed.";
}

// 重写 keyPressEvent 方法
void KeyPressOverrideEscapeDialog::keyPressEvent(QKeyEvent *event)
{
    // 检查按下的键是否是 Escape 键
    if (event->key() == Qt::Key_Escape)
    {
        qDebug() << "KeyPressOverrideDialog: Overridden keyPressEvent, ignoring Escape.";
        // 如果是 Escape 键，直接返回，不调用基类方法。
        // 这屏蔽了 QDialog::keyPressEvent 对 Escape 键的默认处理。
        // return; // 可以直接返回，或者使用 event->accept() / event->ignore()
        event->accept(); // 接受事件，表示已处理
    }
    else
    {
        // 对于其他按键，调用基类 QDialog 的 keyPressEvent 方法进行默认处理
        // 例如：处理 Enter 键点击 default 按钮，处理箭头键移动焦点等。
        QDialog::keyPressEvent(event);
    }
}

// 注意：这个对话框重写了 keyPressEvent 来处理 Escape 键。
// reject() 方法本身没有被重写。