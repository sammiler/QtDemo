#ifndef FRAMELESS_HELPER_H
#define FRAMELESS_HELPER_H

#include <QObject>

#include "FramelessHelperPrivate.h"

class QWidget;


class FramelessHelper : public QObject
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit FramelessHelper(QObject *parent = nullptr); // 使用 nullptr
    ~FramelessHelper() override;
    // 激活窗体
    void activateOn(QWidget *topLevelWidget);
    // 移除窗体
    void removeFrom(QWidget *topLevelWidget);
    // 设置窗体移动
    void setWidgetMovable(bool movable) const;
    // 设置窗体缩放
    void setWidgetResizable(bool resizable) const;
    // 设置橡皮筋移动
    void setRubberBandOnMove(bool movable) const;
    // 设置橡皮筋缩放
    void setRubberBandOnResize(bool resizable) const;
    // 设置边框的宽度
    static void setBorderWidth(int width);
    // 设置标题栏高度 (作为可拖动区域的高度阈值)
    static void setTitleHeight(int height);
    bool widgetResizable() const; // 添加 const
    bool widgetMovable() const; // 添加 const
    bool rubberBandOnMove() const; // 添加 const
    bool rubberBandOnResisze() const; // 添加 const (注意函数名 Resisze -> Resize)
    static int borderWidth() ; // 添加 const
    static int titleHeight() ; // 添加 const

protected:
    // 事件过滤，进行移动、缩放等
    bool eventFilter(QObject *obj, QEvent *event) override; // 使用 override

private:
    FramelessHelperPrivate *d; // 指向私有实现类的指针
};

#endif //FRAMELESS_HELPER_H