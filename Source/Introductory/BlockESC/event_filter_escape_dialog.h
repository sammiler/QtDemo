#ifndef EVENT_FILTER_ESCAPE_DIALOG_H
#define EVENT_FILTER_ESCAPE_DIALOG_H

#include <QDialog>          // 继承自 QDialog
#include <QVBoxLayout>      // 需要布局
#include <QLabel>           // 需要 QLabel
#include "escape_filter.h"  // 需要事件过滤器头文件
#include <QDebug>
class EventFilterEscapeDialog : public QDialog
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit EventFilterEscapeDialog(QWidget *parent = nullptr);
    ~EventFilterEscapeDialog();

private:
    // 事件过滤器实例
    EscapeFilter *m_escapeFilter;
};

#endif // EVENT_FILTER_ESCAPE_DIALOG_H