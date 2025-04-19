#include "HtmlDelegate.h"

#include <QLocale>
#include <QAbstractTextDocumentLayout> // 需要包含此头文件来使用 QAbstractTextDocumentLayout

#include "TableModel.h"


HtmlDelegate::HtmlDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

HtmlDelegate::~HtmlDelegate()
= default;

// paint 方法保持不变，因为它绘制逻辑是正确的，问题在于分配的空间不够
void HtmlDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);

    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    QStyle *pStyle = viewOption.widget ? viewOption.widget->style() : QApplication::style();

    viewOption.text = "";
    pStyle->drawControl(QStyle::CE_ItemViewItem, &viewOption, painter, viewOption.widget);

    QString html = index.data(Qt::DisplayRole).toString();

    QTextDocument doc;
    doc.setHtml(html);

    // 设置文档宽度以匹配绘制区域的宽度，这对于计算正确的高度至关重要
    // 使用 subElementRect 来获取文本应该绘制的区域宽度，更精确
    QRect textRect = pStyle->subElementRect(QStyle::SE_ItemViewItemText, &viewOption);
    doc.setTextWidth(textRect.width());

    QAbstractTextDocumentLayout::PaintContext paintContext;

    painter->save();
    painter->translate(textRect.topLeft());
    painter->setClipRect(textRect.translated(-textRect.topLeft()));

    doc.documentLayout()->draw(painter, paintContext);

    painter->restore();
}

// 完善 sizeHint 方法，计算单元格所需的高度
QSize HtmlDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 调用基类的 sizeHint 获取默认的宽度和高度建议
    const QSize baseSize = QStyledItemDelegate::sizeHint(option, index);

    // 我们只关心绘制 HTML 的列 (例如 FILE_NAME_COLUMN) 的高度
    if (index.column() == FILE_NAME_COLUMN) // 根据你的设计，HTML 在哪个列就在这里检查哪个列
    {
        // 获取模型提供的 HTML 字符串
        QString html = index.data(Qt::DisplayRole).toString();

        // 创建 QTextDocument 并设置 HTML
        QTextDocument doc;
        doc.setHtml(html);

        // 计算内容绘制区域的宽度
        // 这是计算文档高度的关键。使用 option.rect.width() 作为可用宽度。
        // 如果需要更精确，可以尝试根据样式计算文本区域宽度，但这在 sizeHint 中可能不方便。
        int contentWidth = option.rect.width();
        if (contentWidth <= 0) contentWidth = 1; // 避免宽度为0

        // 设置文档宽度以进行布局计算
        doc.setTextWidth(contentWidth);

        // 获取文档布局所需的最小高度
        qreal requiredHeight = doc.documentLayout()->documentSize().height();

        // 计算最终的行高建议
        // 通常需要一些垂直边距。QStyledItemDelegate 的默认高度已经包含了一些边距。
        // 我们取基类计算的高度和 HTML 内容所需高度的较大值，并额外增加一些像素作为填充。
        int verticalPadding = 4; // 增加一些额外的垂直填充

        // 最终的高度建议：基类高度和计算出的 HTML 高度加填充中的较大者
        int totalHeight = qMax(baseSize.height(), (int)requiredHeight + verticalPadding);

        // 返回 size hint。宽度通常由视图的 HeaderView 控制，所以通常返回基类的宽度即可。
        return QSize(baseSize.width(), totalHeight);
    }

    // 其他列使用基类的默认大小提示
    return baseSize;
}