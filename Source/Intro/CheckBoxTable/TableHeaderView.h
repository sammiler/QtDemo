#ifndef TABLE_HEADER_VIEW_H
#define TABLE_HEADER_VIEW_H

#include <QHeaderView> // 继承自 QHeaderView
#include <QMouseEvent> // 需要 QMouseEvent
#include <QPainter>    // 需要 QPainter
#include <QStyleOptionButton> // 需要 QStyleOptionButton
#include <QCheckBox>   // 需要 QCheckBox (用于获取样式绘制参数)
#include <QApplication>// 需要 QApplication::style()
#include <QStyle>      // 需要 QStyle::PE_IndicatorCheckBox 等
#include <QSize>       // 需要 QSize
#include <QRect>       // 需要 QRect
#include <QEvent>      // 需要 QEvent
#include <Qt>          // 需要 Qt::

// 需要 TableModel 中定义的列常量
#include "TableModel.h"


class TableHeaderView : public QHeaderView
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit TableHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~TableHeaderView();

    signals:
        // 当表头主复选状态改变时，发射此信号通知模型更新行项状态
        void stateChanged(int state); // state 使用 Qt::CheckState 枚举值 (会被转换为 int)

    public slots:
        // 接收来自模型的信号，更新表头的主复选状态
        void onStateChanged(int state); // state 使用 Qt::CheckState 枚举值 (会被转换为 int)

protected:
    // 重写 paintSection 方法来绘制表头内容，特别是复选框
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

    // 重写鼠标事件，处理表头复选框的点击
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    // 重写 event 方法，处理 Enter/Leave 等事件以更新 Hover 状态
    bool event(QEvent *event) override;

private:
    // 内部状态标志
    bool m_bPressed;  // 鼠标左键是否按下在复选框区域
    bool m_bChecked;  // 当前主复选框是否为选中状态 (完全选中)
    bool m_bTristate; // 当前主复选框是否为不确定状态
    bool m_bNoChange; // 用于处理不确定状态下的点击逻辑 (根据您提供的代码保留此标志)
    bool m_bMoving;   // 鼠标是否悬停在复选框区域 (用于 Hover 样式)

    // 计算复选框的绘制区域 (可选，如果 paintSection 中计算更方便可以不在这里)
    // QRect checkBoxRect(const QRect &sectionRect) const;
};

#endif // TABLE_HEADER_VIEW_H