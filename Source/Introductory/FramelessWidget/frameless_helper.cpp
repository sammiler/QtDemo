#include "frameless_helper.h"

#include <QList>
#include <QPoint>
#include <QRubberBand>
#include <QHoverEvent>
#include <QEvent>
#include <QWidget>
#include <QApplication>
#include <QDebug>
#include <QtGlobal> // For Q_ASSERT_X

#include "CursorPosCalculator.h"

// --- FramelessHelperPrivate 类定义 ---
/*****
 * FramelessHelperPrivate
 * 存储界面对应的数据集合，以及是否可移动、可缩放属性
*****/


// --- CursorPosCalculator 类声明和定义 ---
/*****
 * CursorPosCalculator
 * 计算鼠标是否位于左、上、右、下、左上角、左下角、右上角、右下角
*****/



// --- WidgetData 类声明和定义 ---
/*****
 * WidgetData
 * 存储单个被管理界面的状态，并处理该界面的鼠标事件，更新鼠标样式、移动或缩放窗体
*****/



// --- FramelessHelper 实现 ---
/*****FramelessHelper 实现 *****/
FramelessHelper::FramelessHelper(QObject *parent)
    : QObject(parent),
      d(new FramelessHelperPrivate()) // 创建私有实现类的实例
{
    // 初始化 FramelessHelper 的默认属性
    d->m_bWidgetMovable = true;
    d->m_bWidgetResizable = true;
    d->m_bRubberBandOnResize = false;
    d->m_bRubberBandOnMove = false;

    qDebug() << "FramelessHelper created.";
}

FramelessHelper::~FramelessHelper()
{
    qDebug() << "FramelessHelper destroying...";
    // 销毁所有管理的 WidgetData 对象
    QList<QWidget*> keys = d->m_widgetDataHash.keys();
    int size = keys.size();
    for (int i = 0; i < size; ++i)
    {
        // take(key) 会移除键值对并返回 Value (WidgetData*), 然后我们 delete 这个指针
        delete d->m_widgetDataHash.take(keys[i]);
        // 在 take 后，这个 QWidget* 应该已经被 removeEventFilter 了 (在 removeFrom 中实现)
    }

    delete d; // 销毁私有实现类的实例
    qDebug() << "FramelessHelper destroyed.";
}

// 事件过滤器，接收被管理窗口的所有事件
bool FramelessHelper::eventFilter(QObject *obj, QEvent *event)
{
    // 根据事件类型分发处理
    switch (event->type())
    {
    // 我们关心的鼠标和悬停事件类型
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::Leave:
    {
        // 将事件的接收者转换为 QWidget 指针
        QWidget *widget = static_cast<QWidget*>(obj);
        // 在哈希表中查找对应的 WidgetData
        WidgetData *data = d->m_widgetDataHash.value(widget);
        if (data) // 如果找到了对应的 WidgetData
        {
            data->handleWidgetEvent(event); // 将事件交给 WidgetData 处理
            // 注意：这里不返回 true/false，而是让 WidgetData 内部的 handleWidgetEvent 处理后，
            // 事件会继续通过 QObject::eventFilter(obj, event) 传递给下一个过滤器或最终的目标对象。
            // 这种设计允许 FramelessHelper 处理拖动/缩放相关的鼠标逻辑，
            // 同时不阻止 Widget 接收正常的 MouseMove, MouseButtonPress/Release 等事件用于其自身的逻辑 (比如按钮点击)。
            // 只有当 WidgetData 内部逻辑导致需要忽略事件时 (比如在 handleWidgetEvent 中调用 event->ignore())，才会影响事件的进一步传播。
        }
    } // 这种情况不 return true 或 false
    default:
        // 其他事件类型，如 ResizeEvent, MoveEvent, PaintEvent 等，都不在这里处理
        // 它们会直接通过 QObject::eventFilter 传递给下一个过滤器或目标对象
        break;
    }

    // 将事件传递给基类的事件过滤器，如果 FramelessHelper 还有父对象或安装了其他过滤器，会继续处理
    // 然后事件会传递给目标对象 obj 的 normal event handlers
    return QObject::eventFilter(obj, event);
}

// 在一个顶级窗口上激活 FramelessHelper
void FramelessHelper::activateOn(QWidget *topLevelWidget)
{
    // 确保被激活的是一个有效的 QWidget
    if (!topLevelWidget) {
         Q_ASSERT_X(false, "FramelessHelper::activateOn", "Cannot activate on a null widget");
         return;
    }
    // 确保被激活的是一个顶级窗口 (FramelessHelper 通常用于管理没有父对象的窗口)
    if (topLevelWidget->parentWidget() != nullptr) {
         qWarning() << "FramelessHelper::activateOn - Activating on a widget with a parent. This helper is typically for top-level windows.";
         // 仍然可以激活，但行为可能不是预期的
    }


    // 如果该窗口还没有被 FramelessHelper 管理
    if (!d->m_widgetDataHash.contains(topLevelWidget))
    {
        // 创建一个 WidgetData 对象来存储和处理该窗口的数据和事件
        WidgetData *data = new WidgetData(d, topLevelWidget);
        // 将窗口和其对应的数据添加到哈希表中
        d->m_widgetDataHash.insert(topLevelWidget, data);

        // !!! 为该窗口安装 FramelessHelper 作为事件过滤器 !!!
        // 这样该窗口接收到的所有事件都会先经过 FramelessHelper 的 eventFilter 方法
        topLevelWidget->installEventFilter(this);

        qDebug() << "FramelessHelper activated on widget" << topLevelWidget;
    }
}

// 从 FramelessHelper 的管理中移除一个窗口
void FramelessHelper::removeFrom(QWidget *topLevelWidget)
{
    // 从哈希表中移除窗口和其对应的数据，并获取 WidgetData 指针
    WidgetData *data = d->m_widgetDataHash.take(topLevelWidget);
    if (data) // 如果找到了对应的 WidgetData
    {
        // 从该窗口上移除 FramelessHelper 的事件过滤器
        topLevelWidget->removeEventFilter(this);
        // 销毁 WidgetData 对象，释放资源
        delete data;
        qDebug() << "FramelessHelper removed from widget" << topLevelWidget;
    }
}

// 设置是否允许移动窗口
void FramelessHelper::setWidgetMovable(const bool movable) const {
    d->m_bWidgetMovable = movable;
}

// 设置是否允许缩放窗口
void FramelessHelper::setWidgetResizable(const bool resizable) const {
    d->m_bWidgetResizable = resizable;
}

// 设置移动时是否显示橡皮筋
void FramelessHelper::setRubberBandOnMove(const bool movable) const {
    d->m_bRubberBandOnMove = movable;
    // 更新所有当前管理的 WidgetData 对象的橡皮筋状态
    QList<WidgetData*> list = d->m_widgetDataHash.values();
    foreach (WidgetData *data, list)
    {
        data->updateRubberBandStatus();
    }
}

// 设置缩放时是否显示橡皮筋
void FramelessHelper::setRubberBandOnResize(const bool resizable) const {
    d->m_bRubberBandOnResize = resizable;
    // 更新所有当前管理的 WidgetData 对象的橡皮筋状态
    QList<WidgetData*> list = d->m_widgetDataHash.values();
    foreach (WidgetData *data, list)
    {
        data->updateRubberBandStatus();
    }
}

// 设置缩放边框的宽度 (静态成员)
void FramelessHelper::setBorderWidth(int width)
{
    if (width > 0)
    {
        CursorPosCalculator::m_nBorderWidth = width;
    } else {
         qWarning() << "FramelessHelper::setBorderWidth - Border width must be positive.";
    }
}

// 设置标题栏高度阈值 (用于判断可拖动区域) (静态成员)
void FramelessHelper::setTitleHeight(int height)
{
    if (height > 0)
    {
        CursorPosCalculator::m_nTitleHeight = height;
    } else {
         qWarning() << "FramelessHelper::setTitleHeight - Title height must be positive.";
    }
}

// --- Const Getter 方法实现 ---
bool FramelessHelper::widgetMovable() const
{
    return d->m_bWidgetMovable;
}

bool FramelessHelper::widgetResizable() const
{
    return d->m_bWidgetResizable;
}

bool FramelessHelper::rubberBandOnMove() const
{
    return d->m_bRubberBandOnMove;
}

bool FramelessHelper::rubberBandOnResisze() const // 注意拼写错误，应为 Resize
{
    return d->m_bRubberBandOnResize;
}

int FramelessHelper::borderWidth()
{
    return CursorPosCalculator::m_nBorderWidth;
}

int FramelessHelper::titleHeight()
{
    return CursorPosCalculator::m_nTitleHeight;
}