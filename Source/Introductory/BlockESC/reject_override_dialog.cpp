#include "reject_override_dialog.h"
#include <QDebug> // 需要 qDebug
#include <QPushButton> // 添加一个按钮作为示例

RejectOverrideDialog::RejectOverrideDialog(QWidget *parent)
    : QDialog(parent),
      m_bClosed(false) // 初始设置为 false，不允许关闭
{
    // 设置窗口大小
    resize(250, 150);

    // 添加标签和按钮
    QLabel *label = new QLabel("Escape Key Calls reject(), but it's overridden.\nDialog will NOT close unless 'Allow Close' is clicked first.", this);
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);

    QPushButton *allowCloseButton = new QPushButton("Allow Close", this);

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(allowCloseButton);
    setLayout(layout);

    // 连接按钮，点击后设置 m_bClosed 为 true
    connect(allowCloseButton, &QPushButton::clicked, this, [this](){
        m_bClosed = true;
        qDebug() << "RejectOverrideDialog: m_bClosed set to true.";
        // 你甚至可以在这里调用 reject() 尝试关闭
        // reject();
    });


    qDebug() << "RejectOverrideDialog created.";
}

RejectOverrideDialog::~RejectOverrideDialog()
{
    qDebug() << "RejectOverrideDialog destroyed.";
}

// 重写 reject() 方法
void RejectOverrideDialog::reject()
{
    qDebug() << "RejectOverrideDialog: reject() called. m_bClosed =" << m_bClosed;
    // 检查关闭条件 m_bClosed 标志
    if (m_bClosed)
    {
        qDebug() << "RejectOverrideDialog: m_bClosed is true, calling QDialog::reject()";
        // 如果条件满足，调用基类 QDialog 的 reject() 方法，实际关闭对话框
        QDialog::reject();
    }
    else
    {
        // 如果条件不满足，不做任何事情，对话框不会关闭
        qDebug() << "RejectOverrideDialog: m_bClosed is false, blocking reject().";
    }
}

// 注意：这个对话框重写了 reject()。
// QDialog 的默认 keyPressEvent 会在按下 Escape 时调用 reject()。
// 但因为 reject() 被重写并添加了条件，只有当 m_bClosed 为 true 时，对话框才会真正关闭。