#include "ProgressBarDelegate.h"
#include "TableModel.h" // 确保包含了，以便使用列定义和 Qt::UserRole

ProgressBarDelegate::ProgressBarDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

ProgressBarDelegate::~ProgressBarDelegate()
{
}

void ProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Standard item painting (draws background, selection, focus border etc.)
    // It's often good practice to let the base class draw the standard stuff first.
    // However, if you want to draw *only* the progress bar covering the whole cell,
    // you might skip this or modify viewOption significantly.
    // Let's draw the base first, then overlay the progress bar within bounds.

    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);

    // Remove focus state for base painting, will draw focus later if needed
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

     // Let base delegate draw the standard item (background, selection, default text if any)
     // For the progress column, we might set text to empty in viewOption before this call
     // if we don't want the default text over the progress bar.
     // Let's rely on the model returning int for DisplayRole, base delegate draws the number.
     // The progress bar will then overlay it. If you want NO text under the bar,
     // set viewOption.text = "" before calling base paint for this column.
    QStyledItemDelegate::paint(painter, viewOption, index);


    // *** 绘制进度条 ***
    if (index.column() == FILE_DOWNLOAD_PROGRESS_COLUMN)
    {
        // 从模型获取进度值 (使用 Qt::UserRole)
        // 如果模型在 Qt::DisplayRole 返回 int 进度，这里也可以用 Qt::DisplayRole
        int nProgress = index.model()->data(index, Qt::UserRole).toInt();

        // 设置进度条的绘制区域 (在单元格 option.rect 内部留出边距)
        int margin = 4; // 进度条边距
        QRect progressBarRect = option.rect.adjusted(margin, margin, -margin, -margin);


        // 设置进度条的风格选项
        QStyleOptionProgressBar progressBarOption;
        progressBarOption.initFrom(option.widget); // 初始化选项来自 widget 的风格、palettes等
        progressBarOption.rect = progressBarRect; // 设置绘制区域
        progressBarOption.minimum = 0;          // 进度条最小值
        progressBarOption.maximum = 100;        // 进度条最大值
        progressBarOption.progress = nProgress; // 当前进度值
        progressBarOption.textAlignment = Qt::AlignCenter; // 文本对齐方式 (如百分比)
        progressBarOption.textVisible = true;   // 文本可见
        progressBarOption.text = QString("%1%").arg(nProgress); // 设置显示的文本

        // 获取当前样式对象
        QStyle *pStyle = option.widget ? option.widget->style() : QApplication::style();

        // 绘制进度条控件
        // 第四个参数可以是一个 QWidget 指针，用于获取 palette 和 style。
        // 在委托中，可以使用 option.widget。如果 option.widget 为 nullptr，则使用主样式 QApplication::style()。
        // 我们这里绘制的是一个 "Control Element"，不是一个完整的 Widget。
        // 传递 option.widget 可以让进度条继承父 widget 的样式和 palatte。
        pStyle->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter, option.widget);

        // 如果需要，在进度条绘制完成后，再绘制焦点框
        if (option.state.testFlag(QStyle::State_HasFocus)) {
             // 重新初始化一个 option 来绘制焦点框，确保包含焦点状态
            QStyleOptionViewItem focusOption;
            initStyleOption(&focusOption, index);
            focusOption.rect = option.rect; // 焦点框通常画在整个项的矩形上
             // 绘制焦点框
            pStyle->drawPrimitive(QStyle::PE_FrameFocusRect, &focusOption, painter, focusOption.widget);
        }
    }
     // else { // 对于非进度条列， base delegate 已经在上面绘制过了
     //    QStyledItemDelegate::paint(painter, viewOption, index);
     // }
}