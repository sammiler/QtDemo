#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include <QWidget> // 继承自 QWidget
#include <QMouseEvent> // 需要 QMouseEvent

class FramelessWidget final : public QWidget
{
    Q_OBJECT // 启用 Qt 元对象系统

public:
    explicit FramelessWidget(QWidget *parent = nullptr);
    ~FramelessWidget() override;

protected:
    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override; // 使用 override 关键字
};

#endif // FRAMELESSWIDGET_H