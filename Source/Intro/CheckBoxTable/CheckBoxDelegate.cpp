#include "CheckBoxDelegate.h"
// #include <QDebug> // 已在 .h 中包含

// 构造函数
CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    qDebug() << "CheckBoxDelegate created.";
}

// 析构函数
CheckBoxDelegate::~CheckBoxDelegate()
{
    qDebug() << "CheckBoxDelegate destroyed.";
}

// 绘制单元项内容，特别是复选框
void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 创建一个 QStyleOptionViewItem 的副本，用于自定义绘制
    QStyleOptionViewItem viewOption(option);
    // 根据模型索引初始化样式选项 (会设置文本、图标等)
    initStyleOption(&viewOption, index);

    // 如果单元项有焦点，移除焦点状态，以便我们只绘制复选框，焦点的绘制由基类处理或 QTableView 的 QSS 处理
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state &= ~QStyle::State_HasFocus; // 使用按位操作移除标志

    // 先调用基类的 paint 方法，绘制单元项的其他内容 (如文本、背景、选中状态、默认焦点框等)
    // 基类会自动处理根据模型数据中的 Qt::DisplayRole, Qt::DecorationRole 等来绘制
    QStyledItemDelegate::paint(painter, viewOption, index);

    // 如果是复选框列，则在绘制完基本内容后再绘制复选框指示器
    if (index.column() == CHECK_BOX_COLUMN)
    {
        // 从模型中获取复选框的布尔状态，使用 Qt::UserRole
        bool checked = index.model()->data(index, Qt::UserRole).toBool();

        // 创建一个 QStyleOptionButton 来控制复选框的绘制样式
        QStyleOptionButton checkBoxStyle;
        // 设置复选框的状态 (选中/未选中/不确定)
        checkBoxStyle.state = checked ? QStyle::State_On : QStyle::State_Off;
        // 添加可用状态 (委托只处理可用项，因为 flags 没有 ItemIsUserCheckable)
        checkBoxStyle.state |= QStyle::State_Enabled;
        // 如果需要处理不确定状态，需要从模型获取 Qt::CheckStateRole 并判断 Qt::PartiallyChecked，然后设置 QStyle::State_NoChange

        // !!! 关键：添加鼠标交互状态 (Hover, Pressed) !!!
        // 检查传递给 paint 方法的 option.state 中是否包含 Hover 或 Pressed 标志
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            checkBoxStyle.state |= QStyle::State_MouseOver; // 设置 Hover 状态
        }
        if (option.state.testFlag(QStyle::State_Sunken)) {
            checkBoxStyle.state |= QStyle::State_Sunken; // 设置 Pressed 状态
        }


        // 提供一个临时的 QCheckBox 控件作为样式上下文
        QCheckBox tempCheckBox;

        // 设置复选框在当前单元格内的绘制区域
        // 默认居中绘制
        int checkboxWidth = 20; // 假设复选框图标的实际绘制宽度是 20px (与 iconSize 配合 QSS)
        int checkboxHeight = 20; // 假设复选框图标的实际绘制高度是 20px
        int x = option.rect.x() + (option.rect.width() - checkboxWidth) / 2; // 在单元格中水平居中
        int y = option.rect.y() + (option.rect.height() - checkboxHeight) / 2; // 在单元格中垂直居中
        checkBoxStyle.rect = QRect(x, y, checkboxWidth, checkboxHeight); // 设置绘制区域

        // 获取应用程序样式，并绘制复选框指示器
        // PE_IndicatorCheckBox 是 QStyle 原语，用于绘制复选框的图形部分
        // &checkBoxStyle 是样式选项
        // painter 是绘制目标
        // &QCheckBox() 是提供样式上下文的临时 QCheckBox 控件 (用于 QSS)
        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &checkBoxStyle, painter, &tempCheckBox);
    }
}

// 处理单元项上的鼠标事件
bool CheckBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    // 检查是否是复选框列，以及索引是否有效
    if (index.column() == CHECK_BOX_COLUMN && index.isValid())
    {
        // 将事件转换为鼠标事件
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        // 检查事件类型是否是鼠标按下事件
        if (event->type() == QEvent::MouseButtonPress)
        {
             // 检查鼠标点击位置是否在单元格的绘制区域内
             // 注意：更精确的做法是检查鼠标位置是否在复选框图标本身的绘制区域内
             if (option.rect.contains(mouseEvent->pos()))
             {
                // 获取当前复选框的布尔状态，使用 Qt::UserRole
                bool checked = model->data(index, Qt::UserRole).toBool();
                // 切换状态并使用模型更新数据，角色为 Qt::UserRole
                // 调用模型 setData 方法会触发 dataChanged 信号，进而触发视图重绘
                // TableModel 的 setData 收到 UserRole 改变后，会调用 updateHeaderState() 更新表头
                model->setData(index, !checked, Qt::UserRole);
                qDebug() << "CheckBoxDelegate: Toggled checkbox at row" << index.row() << "to" << !checked;
                // 返回 true 表示这个事件已经被我们处理，阻止进一步传递给模型的 flags() 或视图的其他处理
                event->accept(); // 接受事件
                return true; // 事件已处理
             }
        }
        // 可以添加对 QEvent::HoverMove 的处理，如果需要更精确的指示器 Hover 反馈而不仅仅是单元格 Hover
        // 但对于 PE_IndicatorCheckBox 原语，QStyleOptionViewItem 的 State_MouseOver 通常已足够触发 QSS Hover 样式

    }

    // 对于其他事件类型，或者不是复选框列的事件，或者事件未被处理（例如点击位置不在单元格内）
    // 将事件传递给基类的 editorEvent 方法进行默认处理
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}