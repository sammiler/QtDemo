#include "SortDelegate.h"

#include <QLocale> // For number formatting

// Define the helper function here
QString bytesToGBMBKB(qint64 size)
{
    if (size < 0) return "Invalid Size";

    const qint64 GB = 1024LL * 1024 * 1024;
    const qint64 MB = 1024LL * 1024;
    const qint64 KB = 1024LL;

    QLocale locale;

    if (size >= GB) {
        return locale.toString((double)size / GB, 'f', 2) + " GB";
    } else if (size >= MB) {
        return locale.toString((double)size / MB, 'f', 2) + " MB";
    } else if (size >= KB) {
        return locale.toString((double)size / KB, 'f', 2) + " KB";
    } else {
        return locale.toString(size) + " Bytes";
    }
}

SortDelegate::SortDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

SortDelegate::~SortDelegate()
{
}

// Custom paint method
void SortDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);

    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    // Check if this is the size column
    if (index.column() == FILE_SIZE_COLUMN)
    {
        // Get the raw qint64 data from the model's DisplayRole
        qint64 bytes = index.data(Qt::DisplayRole).toLongLong(); // Explicitly get DisplayRole

        // Format the bytes into a string for drawing
        viewOption.text = bytesToGBMBKB(bytes) ;

        // Draw the item using the style
        QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &viewOption, painter, viewOption.widget);
    }
    // Check if this is the checkbox column (optional, base delegate handles checkboxes well)
    // else if (index.column() == CHECK_BOX_COLUMN) {
    //     // Let base class draw the checkbox
    //     QStyledItemDelegate::paint(painter, viewOption, index);
    // }
    else
    {
        // For other columns, let the base class delegate handle the painting
        QStyledItemDelegate::paint(painter, viewOption, index);
    }
}