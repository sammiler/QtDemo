#ifndef CHECKBOX_DELEGATE_H
#define CHECKBOX_DELEGATE_H

#include <QStyledItemDelegate> // 继承自 QStyledItemDelegate
#include <QPainter>          // 需要 QPainter
#include <QStyleOptionViewItem> // 需要 QStyleOptionViewItem
#include <QModelIndex>       // 需要 QModelIndex
#include <QEvent>            // 需要 QEvent
#include <QAbstractItemModel> // 需要 QAbstractItemModel
#include <QMouseEvent>       // 需要 QMouseEvent
#include <QStyleOptionButton> // 需要 QStyleOptionButton
#include <QCheckBox>         // 需要 QCheckBox (用于获取样式绘制参数)
#include <QApplication>      // 需要 QApplication::style()
#include <QStyle>            // 需要 QStyle::PE_IndicatorCheckBox 等
#include <QRect>             // 需要 QRect (用于 RectF 转 Rect)

// 需要 TableModel 中定义的列常量
#include "TableModel.h"


class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit CheckBoxDelegate(QObject *parent = nullptr);
    ~CheckBoxDelegate();

    // 重写 paint 方法来绘制复选框
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // 重写 editorEvent 方法来处理鼠标点击等事件，更新模型数据
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

#endif // CHECKBOX_DELEGATE_H