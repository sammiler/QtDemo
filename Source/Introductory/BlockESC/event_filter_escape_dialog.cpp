#include "event_filter_escape_dialog.h"

EventFilterEscapeDialog::EventFilterEscapeDialog(QWidget *parent)
    : QDialog(parent)
{
    // 设置窗口大小
    resize(200, 100);

    // 添加一个标签
    QLabel *label = new QLabel("Escape Key Filtered by Event Filter.\nDialog will NOT close on Escape.", this);
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    setLayout(layout);

    // !!! 创建并安装事件过滤器 !!!
    m_escapeFilter = new EscapeFilter(this); // 以对话框为父对象创建过滤器
    installEventFilter(m_escapeFilter);      // 在当前对话框上安装过滤器

    qDebug() << "EventFilterEscapeDialog created.";
}

EventFilterEscapeDialog::~EventFilterEscapeDialog()
{
    // m_escapeFilter 的父对象是 this，会自动销毁
    qDebug() << "EventFilterEscapeDialog destroyed.";
}

// 注意：这个对话框没有重写 keyPressEvent 或 reject()。
// Escape 键行为的改变完全依赖于安装的 EventFilter。
// EventFilter 捕获并过滤掉了 Escape 键按下事件，阻止了它到达 QDialog 的默认 keyPressEvent 处理。