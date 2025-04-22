#ifndef TABLEVIEWDELEGATE_H
#define TABLEVIEWDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QEvent>
#include <QMouseEvent>
#include <QAbstractItemModel>
#include <QStyleOptionButton> // 绘制按钮需要
#include <QPushButton> // 使用其 styleSheet 功能
#include <QApplication> // QStyle, QCursor
#include <QStyle>
#include <QScopedPointer> // 用于管理 QPushButton 内存
#include <QToolTip> // 显示提示
#include <QCursor> // 改变鼠标样式
#include <QRect>
#include <QSize>
#include <QStringList>
#include <QPoint>

#include "TableModel.h" // 包含模型头文件以访问列定义

// 按钮状态定义 (与你的代码片段一致)
#define BUTTON_TYPE_NORMAL   -1 // 正常状态
#define BUTTON_TYPE_HOVER     0 // 鼠标划过
#define BUTTON_TYPE_PRESSED   1 // 鼠标按下


class TableViewDelegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TableViewDelegate(QWidget *parent = nullptr); // 默认参数为 nullptr
    ~TableViewDelegate() override; // 使用 override

    // 重写 paint 方法进行绘制
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // 重写 editorEvent 响应鼠标事件
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override; // 使用 override

    QIcon iconForButtonState(const int buttonIndex, const QStyleOptionViewItem& option) const;
signals:
    // 委托发出的信号，通知外部按钮被点击
    void open(const QModelIndex &index);
    void deleteData(const QModelIndex &index);

private:
    // 鼠标位置和按钮状态需要在委托中存储，
    // 但请注意：同一个委托实例用于绘制和处理列中所有项的事件，
    // 这种方式存储鼠标状态在复杂场景下可能导致绘制状态不同步。
    // 然而，为了匹配你的代码片段并演示其逻辑，我们保留这种方式。
    // 一个更健壮的实现可能需要视图的帮助或更复杂的事件过滤。
    QPoint m_mousePoint;  // 鼠标位置 (相对于视图的 viewport 或委托接收事件的 widget)
    int m_nType;  // 按钮状态 -1：正常 0：划过 1：按下

    // 使用 QScopedPointer 管理 QPushButton 内存，只用于获取样式信息

    // 直接加载 QIcon 资源，在 paint 方法中设置给 buttonOption.icon
    QIcon m_openIcon;
    QIcon m_openHoverIcon;
    QIcon m_openPressedIcon;
    QIcon m_deleteIcon;
    QIcon m_deleteHoverIcon;
    QIcon m_deletePressedIcon;

    QStringList m_listButtonText; // 按钮文本列表 (这里用于提示文本和图标路径)
    int m_nSpacing;  // 按钮之间的间距
    int m_nButtonWidth;  // 按钮宽度
    int m_nButtonHeight;  // 按钮高度

    // 辅助函数：计算按钮绘制区域
    QRect calculateButtonRect(const QRect& itemRect, int buttonIndex) const;
};

#endif // TABLEVIEWDELEGATE_H