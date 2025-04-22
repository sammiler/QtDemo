#include "TableHeaderView.h"
#include <QDebug> // 需要 qDebug

// 构造函数
TableHeaderView::TableHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent),
      m_bPressed(false),
      m_bChecked(false), // 初始未选中
      m_bTristate(false), // 初始非不确定状态
      m_bNoChange(false), // 初始无变化标志
      m_bMoving(false)    // 初始鼠标不在移动
{
    // setStretchLastSection(true); // 可在 QTableView 中设置
    setHighlightSections(false); // 表头选中时不高亮
    setMouseTracking(true);      // 启用鼠标跟踪，即使没有按下鼠标也能收到 MouseMove/Hover 事件

    // 响应鼠标点击表头区域
    setSectionsClickable(true);

    // 启用 Hover 事件属性，以便 event 方法能收到 Enter/Leave 事件
    setAttribute(Qt::WA_Hover, true);

    qDebug() << "TableHeaderView created.";
}

// 析构函数
TableHeaderView::~TableHeaderView()
{
    qDebug() << "TableHeaderView destroyed.";
}

// 槽函数，用于更新表头主复选框状态 (接收来自模型的信号)
// state 使用 Qt::CheckState 枚举值 (会被转换为 int)
void TableHeaderView::onStateChanged(int state)
{
    qDebug() << "TableHeaderView::onStateChanged received state:" << state;
    // 根据模型传来的总状态，更新表头的内部标志
    if (state == Qt::PartiallyChecked) {
        m_bTristate = true;
        m_bChecked = false; // 不确定状态时，setChecked 通常为 false
        m_bNoChange = true; // 进入不确定状态的特殊处理标志 (根据您提供的代码保留)
    } else {
        m_bTristate = false;
        m_bNoChange = false;
        m_bChecked = (state == Qt::Checked); // 根据模型状态设置为选中或未选中
    }

    // 请求重绘表头，以便显示更新后的复选框状态
    update();
}

// 绘制表头内容，特别是复选框
void TableHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    // 先调用基类方法绘制表头文本、背景、分隔线等
    // 注意：这里不能简单地用 painter->save()/restore() 包裹基类调用，因为基类可能修改 painter 的状态
    // 正确的做法是创建一个 QStyleOptionHeader 的副本并传递给基类，或者在绘制复选框之前保存/恢复 painter 的状态
    // 我们在绘制复选框时需要 painter 的原始状态，所以在这里保存/恢复 painter
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex); // 绘制默认表头内容
    painter->restore(); // 恢复 painter 状态

    // 如果是需要绘制复选框的列 (通常是第一列)
    if (logicalIndex == CHECK_BOX_COLUMN)
    {
        // 创建一个 QStyleOptionButton 来控制复选框的绘制样式
        QStyleOptionButton option;
        option.initFrom(this); // 从此控件 (TableHeaderView) 初始化选项

        // --- 设置复选框的状态 ---
        // 1. 设置选中/未选中/不确定状态 (State_On, State_Off, State_NoChange)
        if (m_bTristate) { // 如果是不确定状态
            option.state |= QStyle::State_NoChange; // 设置不确定状态标志
        } else { // 如果是确定状态 (选中或未选中)
            option.state |= m_bChecked ? QStyle::State_On : QStyle::State_Off; // 根据 m_bChecked 设置选中或未选中状态
        }

        // 2. 添加可用状态 (表头通常是可用的)
        option.state |= QStyle::State_Enabled;

        // 3. 添加鼠标交互状态 (Hover, Pressed)
        // 检查鼠标是否悬停在整个表头控件上，以及是否是我们正在绘制的这一段表头
        // 并结合内部的 m_bMoving 标志（通过 event 方法跟踪）和 m_bPressed 标志（通过 mousePressEvent 跟踪）来判断瞬时状态
        // option.rect 是当前表头段的绘制区域
        // underMouse() 检查鼠标是否在整个 TableHeaderView 控件内
        // mapFromGlobal(QCursor::pos()) - 将全局鼠标位置映射到 TableHeaderView 的局部坐标
        // rect.contains(...) - 检查鼠标局部坐标是否在当前表头段区域内

        // 更准确的 Hover 检查是：鼠标在整个表头控件内 并且 鼠标在当前绘制的表头段区域内
        if (underMouse() && rect.contains(mapFromGlobal(QCursor::pos()))) {
             option.state |= QStyle::State_MouseOver; // 设置 Hover 状态
        }

        // 检查鼠标是否在当前表头段区域内并且左键被按下 (Pressed 状态)
        if (m_bPressed && rect.contains(mapFromGlobal(QCursor::pos()))) {
             option.state |= QStyle::State_Sunken; // 设置 Pressed 状态
        }


        // 4. 根据您提供的代码，有一个特殊的 m_bMoving 标志（用于 Hover 样式？）和 m_bChecked 设置 State_Sunken 的逻辑。
        // 这是非标准的样式状态设置，但为了复现您提供的代码，我们将其放在这里（可能需要根据 QSS 调整逻辑）
        // if (m_bChecked) // 这个条件设置 State_Sunken 看起来不对，State_Sunken 通常表示 pressed
        //     option.state |= QStyle::State_Sunken; // 原始代码
        // if (testAttribute(Qt::WA_Hover) && underMouse()) { // 原始代码中对 Hover 的奇怪处理
        //     if (m_bMoving)
        //         option.state |= QStyle::State_MouseOver;
        //     else
        //         option.state &= ~QStyle::State_MouseOver;
        // }
        // 按照标准的样式状态设置，上面的判断已经包含了 Hover 和 Pressed。


        // 提供一个临时的 QCheckBox 控件作为样式上下文
        QCheckBox tempCheckBox;

        // 设置复选框指示器的推荐尺寸 (会影响样式表中 image 的缩放)
        option.iconSize = QSize(20, 20);

        // 设置复选框在当前表头段内的绘制区域
        // 默认居中绘制
        int checkboxWidth = 20; // 假设复选框图标的实际绘制宽度
        int checkboxHeight = 20; // 假设复选框图标的实际绘制高度
        int x = rect.x() + (rect.width() - checkboxWidth) / 2;
        int y = rect.y() + (rect.height() - checkboxHeight) / 2;
        option.rect = QRect(x, y, checkboxWidth, checkboxHeight);

        // 获取应用程序样式，并绘制复选框指示器
        // 使用 QStyle::PE_IndicatorCheckBox 原语绘制复选框图标部分
        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter, &tempCheckBox);

        // 以下是您提供的其他绘制选项 (注释掉的)
        // style()->drawItemPixmap(painter, rect, Qt::AlignCenter, QPixmap(":/images/checkBoxChecked")); // 直接绘制图片
        // style()->drawControl(QStyle::CE_CheckBox, &option, painter, this); // 绘制整个 CheckBox 控件 (包含文本和指示器)，如果只想要指示器则不合适
    }
}

// 处理鼠标按下表头事件
void TableHeaderView::mousePressEvent(QMouseEvent *event)
{
    // 获取鼠标按下位置对应的逻辑列索引
    int nColumn = logicalIndexAt(event->pos());

    // 如果按下的是鼠标左键，并且在复选框列
    if ((event->button() == Qt::LeftButton) && (nColumn == CHECK_BOX_COLUMN))
    {
        m_bPressed = true; // 设置鼠标按下标志
        // 接受事件，阻止进一步传播
        event->accept();
        // 请求重绘当前表头段，以便显示按下状态样式 (可选，如果 QSS 定义了 :pressed 样式)
        updateSection(nColumn);
    }
    else
    {
        // 其他情况（非左键或不在复选框列），调用基类方法处理
        QHeaderView::mousePressEvent(event);
    }
}

// 处理鼠标从表头释放事件
void TableHeaderView::mouseReleaseEvent(QMouseEvent *event)
{
    auto nColumn = 0;
    // 如果鼠标按下标志为 true (说明之前在复选框列按下了左键)
    if (m_bPressed)
    {
        // 检查鼠标释放时是否仍在复选框列区域内 (或者根据需要检查是否在按下时的同一列等)
        nColumn = logicalIndexAt(event->pos());
        if (event->button() == Qt::LeftButton && nColumn == CHECK_BOX_COLUMN)
        {
             // !!! 处理复选框状态切换逻辑 !!!
             Qt::CheckState newState;
             if (m_bTristate && m_bNoChange) // 如果当前是不确定状态 (且处于特殊变化模式)
             {
                 // 从不确定状态点击，通常会切换到完全选中状态
                 newState = Qt::Checked;
                 m_bNoChange = false; // 退出特殊变化模式
             }
             else // 如果当前是确定状态 (选中或未选中)
             {
                 // 切换选中状态
                 newState = m_bChecked ? Qt::Unchecked : Qt::Checked;
             }

             // 更新内部标志
             m_bChecked = (newState != Qt::Unchecked); // 完全选中 或 不确定 都是 true for m_bChecked
             m_bTristate = (newState == Qt::PartiallyChecked);

             // 请求重绘表头以显示新状态
             updateSection(nColumn); // 或者 update() 重绘整个表头

             // !!! 发射信号通知模型更新行项状态 !!!
             emit stateChanged(newState); // 发射 Qt::CheckState 值


             event->accept(); // 接受事件
        }
        else {
             // 鼠标在复选框列按下，但在其他地方释放，可能视为取消操作，调用基类处理
             QHeaderView::mouseReleaseEvent(event);
        }
    }
    else
    {
        // 如果鼠标按下标志为 false，调用基类方法处理释放事件 (处理默认的选择段等)
        QHeaderView::mouseReleaseEvent(event);
    }

    m_bPressed = false; // 重置鼠标按下标志
    // 请求重绘，以便显示非按下状态样式 (可选)
    if (nColumn == CHECK_BOX_COLUMN) updateSection(nColumn);
}

// 重写 event 方法，处理 Enter/Leave 事件以更新 Hover 状态
bool TableHeaderView::event(QEvent *event)
{
    // 检查事件类型是否是鼠标进入或离开事件
    if (event->type() == QEvent::Enter || event->type() == QEvent::Leave)
    {
        // 将事件转换为鼠标事件以便获取位置
        QMouseEvent *pEvent = static_cast<QMouseEvent *>(event);
        // 获取鼠标当前位置对应的逻辑列索引
        int nColumn = logicalIndexAt(pEvent->pos()); // Use pEvent->pos() for local position

        // 如果事件发生在复选框列
        if (nColumn == CHECK_BOX_COLUMN)
        {
            // 更新内部标志 m_bMoving (表示鼠标是否悬停在复选框列)
            m_bMoving = (event->type() == QEvent::Enter);

            // 请求重绘复选框列，以便显示 Hover 状态样式
            updateSection(nColumn);
            // 返回 true 表示事件已被处理，阻止进一步传播 (例如阻止基类处理 Enter/Leave 影响段高亮等)
            return true;
        }
    }
    // 检查 MouseMove 事件是否需要特殊处理以更新 Hover/Pressed 状态 (如果只依赖 event 方法可能不足够)
    // 依赖于 paintSection 中的 rect.contains(mapFromGlobal(QCursor::pos())) 检查 Hover/Pressed 通常是可行的。

    // 对于其他事件类型，或事件不在复选框列，调用基类方法处理
    return QHeaderView::event(event);
}