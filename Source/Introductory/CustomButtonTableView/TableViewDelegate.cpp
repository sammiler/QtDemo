//
// Created by sammiler on 2025/4/19.
//

#include <QDebug>
#include "TableViewDelegate.h"
#include <QMouseEvent> // 需要包含 QMouseEvent 头文件

// 构造函数，初始化按钮样式和参数
TableViewDelegate::TableViewDelegate(QWidget *parent)
    : QStyledItemDelegate(parent),
      m_nSpacing(5), // 按钮间距
      m_nButtonWidth(25), // 按钮宽度
      m_nButtonHeight(20), // 按钮高度
      m_nType(BUTTON_TYPE_NORMAL) // 初始状态为正常
{
    // 设置按钮的样式表，用于定义不同状态下的图标
    // 注意：这里设置样式表是为了让 drawControl 在使用这个 button 作为 widget 参数时，
    // 能够获取到样式信息（特别是图片）。实际并不会创建可见的按钮控件。
    m_openIcon        = QIcon(":/Images/open");
    m_openHoverIcon   = QIcon(":/Images/openHover");
    m_openPressedIcon = QIcon(":/Images/openPressed");
    m_deleteIcon      = QIcon(":/Images/delete");
    m_deleteHoverIcon = QIcon(":/Images/deleteHover");
    m_deletePressedIcon = QIcon(":/Images/deletePressed");
    if (m_deleteIcon.isNull()) {
        qDebug() << "m_deleteIcon is null";
    }


    // 按钮对应的文本/标识 (用于提示信息和索引)
    m_listButtonText << QStringLiteral("打开") << QStringLiteral("删除");

    // 委托需要启用鼠标跟踪才能收到 MouseMove 事件
    // 但是委托本身没有 setMouseTracking 方法。通常是在视图的 viewport 上启用鼠标跟踪。
    // 我们会在 MainWindow 中设置 tableView->setMouseTracking(true);
}

TableViewDelegate::~TableViewDelegate()
{
    // QScopedPointer 会自动删除 m_pOpenButton 和 m_pDeleteButton
}

// 计算按钮在给定单元格矩形内的绘制区域
QRect TableViewDelegate::calculateButtonRect(const QRect& itemRect, int buttonIndex) const
{
    int totalButtonWidth = m_nButtonWidth * m_listButtonText.count() + m_nSpacing * (m_listButtonText.count() - 1);
    int nHalf = (itemRect.width() - totalButtonWidth) / 2; // 水平居中偏移
    int nTop = (itemRect.height() - m_nButtonHeight) / 2; // 垂直居中偏移

    return QRect(itemRect.left() + nHalf + m_nButtonWidth * buttonIndex + m_nSpacing * buttonIndex,
                 itemRect.top() + nTop,
                 m_nButtonWidth,
                 m_nButtonHeight);
}

// 绘制按钮
// 绘制按钮，使用 buttonOption.icon
void TableViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 绘制默认项的背景、选中状态等
    QStyleOptionViewItem viewOption(option); // 这是包含项状态的 QStyleOptionViewItem
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    QStyledItemDelegate::paint(painter, viewOption, index); // 先绘制背景和文本

    // 如果当前列是操作列
    if (index.column() == FILE_OPERATE_COLUMN)
    {
        QStyle *pStyle = viewOption.widget ? viewOption.widget->style() : QApplication::style();

        for (int i = 0; i < m_listButtonText.count(); ++i)
        {
            QRect buttonRect = calculateButtonRect(option.rect, i);

            // 设置按钮的风格选项
            QStyleOptionButton buttonOption; // 这是用于绘制按钮的 QStyleOptionButton
            buttonOption.initFrom(viewOption.widget);
            buttonOption.rect = buttonRect;
            // 将项的状态复制到按钮选项中 (例如 Enabled, Selected)
            buttonOption.state = viewOption.state;
            buttonOption.state |= QStyle::State_Enabled; // 确保按钮是可用的

            // *** 根据鼠标位置和项状态设置按钮的伪状态 ***
            // option.state 中可能包含 State_MouseOver 和 State_Sunken，
            // 这是由 editorEvent 返回 true 并由视图处理的结果
            if (buttonRect.contains(m_mousePoint) &&
                (m_mousePoint.y() >= option.rect.top() && m_mousePoint.y() < option.rect.bottom()) &&
                 (viewOption.state & QStyle::State_Enabled)) // 只有项可用时按钮才响应
            {
                 if (QApplication::mouseButtons() & Qt::LeftButton) {
                      buttonOption.state |= QStyle::State_Sunken; // 鼠标左键在按钮上按下
                 } else {
                     buttonOption.state |= QStyle::State_MouseOver; // 鼠标在按钮上悬停
                 }
            } else {
                 // 如果鼠标不在按钮区域内，明确移除 hover 和 sunken 状态，
                 // 以防止在鼠标移开后绘制状态残留。
                 buttonOption.state &= ~QStyle::State_MouseOver;
                 buttonOption.state &= ~QStyle::State_Sunken;
            }


            // *** 修正这里：传递 viewOption 给 iconForButtonState ***
            buttonOption.icon = iconForButtonState(i, viewOption); // 使用 iconForButtonState 根据 viewOption 的状态获取图标
            // *** 设置 icon size ***
            buttonOption.iconSize = QSize(m_nButtonWidth, m_nButtonHeight); // 设置图标绘制尺寸


            // 绘制按钮控件
            pStyle->drawControl(QStyle::CE_PushButton, &buttonOption, painter, viewOption.widget);
        }

         // 绘制焦点框
        if (option.state.testFlag(QStyle::State_HasFocus)) {
             QStyleOptionViewItem focusOption;
             initStyleOption(&focusOption, index);
             focusOption.rect = option.rect;
             pStyle->drawPrimitive(QStyle::PE_FrameFocusRect, &focusOption, painter, viewOption.widget);
        }
    }
}

// 响应按钮事件 - 划过、按下、释放
// 负责更新 m_mousePoint 并触发重绘，发射信号
bool TableViewDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    // 只处理操作列且项可用时的事件
    if (index.column() != FILE_OPERATE_COLUMN || !(option.state & QStyle::State_Enabled))
        return QStyledItemDelegate::editorEvent(event, model, option, index);

    // 只处理鼠标事件
    if (event->type() != QEvent::MouseMove && event->type() != QEvent::MouseButtonPress && event->type() != QEvent::MouseButtonRelease)
         return QStyledItemDelegate::editorEvent(event, model, option, index);


    const QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);
    // 更新鼠标位置 (相对于视图的 viewport)
    m_mousePoint = pEvent->pos();

    bool consumed = false; // 事件是否被委托完全处理

    // 还原鼠标样式和提示信息
    QApplication::restoreOverrideCursor();
    QToolTip::hideText();

    // 遍历所有按钮，检查鼠标位置和事件类型
    for (int i = 0; i < m_listButtonText.count(); ++i)
    {
        QRect buttonRect = calculateButtonRect(option.rect, i);

        // 检查鼠标是否在当前按钮的区域内，并且在当前行的垂直范围内
        if (!buttonRect.contains(m_mousePoint) ||
            (m_mousePoint.y() < option.rect.top() || m_mousePoint.y() >= option.rect.bottom()))
            continue; // 鼠标不在当前按钮区域或当前行，检查下一个按钮


        // *** 鼠标在当前按钮区域内 (并且在当前行内) ***

        // 设置鼠标样式为手型
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        // 显示提示信息
        QToolTip::showText(pEvent->globalPos(), m_listButtonText.at(i));
        consumed = true; // 事件至少触发了高亮或提示，视为已处理


        if (event->type() == QEvent::MouseButtonPress)
        {
            if (pEvent->button() == Qt::LeftButton) {
                 // 鼠标左键按下，标记状态为按下，需要重绘
                 m_nType = BUTTON_TYPE_PRESSED; // Update delegate state (less critical now, paint checks option.state)
                 // 触发当前项重绘以显示按下状态
                 // model->dataChanged(index, index, {Qt::ItemDataRole::Invalid}); // Invalid role forces full repaint (less efficient)
                 // A more specific role could be used if defined, but view often repaints on MouseButtonPress anyway.
                 // Let's rely on the return true to trigger a repaint.
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            if (pEvent->button() == Qt::LeftButton) {
                 // 鼠标左键释放，如果在按钮区域内释放
                 m_nType = BUTTON_TYPE_HOVER; // 释放后鼠标还在上面，状态回到 Hover
                 // 发射对应的信号
                if (i == 0) // “打开”按钮
                {
                    emit open(index);
                }
                else // “删除”按钮
                {
                    emit deleteData(index);
                }
                 // 事件被完全处理，不再传播
                 return true;
            }
        }
         // 如果是 MouseMove 事件，或者 MouseButtonPress 但不是左键，或者 MouseButtonRelease 但不是左键/不在区域内，
         // 只需要设置手型光标和提示，然后返回 true 即可，不需要特殊状态更新。
         // 鼠标移出按钮区域后，后续 MouseMove 会进入外层 if，不进入内层 if， consumed 会变回 false，
         // 然后恢复默认光标和隐藏提示。
    }

    // *** 事件处理的结尾 ***

    // 如果事件被某个按钮区域包含并处理了一部分 (consumed == true)，则返回 true，
    // 告诉视图事件已处理，并可能需要重绘 (特别是 MouseMove 进入/离开按钮时)。
    // 如果事件不在任何按钮区域内 (consumed == false)，则让基类处理事件。
    if (consumed) {
        // 当鼠标移动，进入或离开一个按钮区域时，需要请求视图重绘当前项
        // This makes hover state update visible.
        if (event->type() == QEvent::MouseMove) {
             // The view often handles repainting on mouse move if editorEvent returns true,
             // but explicitly notifying dataChanged can ensure it. Use an invalid role
             // or a custom role if you don't want to affect cached data.
             // model->dataChanged(index, index, {Qt::ItemDataRole::Invalid});
             // Let's rely on returning true to trigger repaint for now.
        }
        return true;
    } else {
         // Mouse moved out of all buttons in this item, restore cursor/tooltip (already done above)
         // and potentially reset internal state if not relying on paint's option.state
         m_nType = BUTTON_TYPE_NORMAL; // Reset delegate state when mouse leaves the item's buttons area

        // 如果事件不在任何按钮区域内，让基类处理（例如选中项）
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }
}

QIcon TableViewDelegate::iconForButtonState(const int buttonIndex, const QStyleOptionViewItem &option) const {
    bool isHover = option.state.testFlag(QStyle::State_MouseOver);
    bool isPressed = option.state.testFlag(QStyle::State_Sunken);

    if (buttonIndex == 0) { // 打开按钮
        if (isPressed) return m_openPressedIcon;
        if (isHover) return m_openHoverIcon;
        return m_openIcon;
    } else { // 删除按钮 (buttonIndex == 1)
        if (isPressed) return m_deletePressedIcon;
        if (isHover) return m_deleteHoverIcon;
        return m_deleteIcon;
    }
}
