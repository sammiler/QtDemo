#include "SortDelegate.h"

#include <QLocale> // For number formatting in bytesToGBMBKB

// Define the helper function here so the delegate can use it
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
    // Create a copy of the option to modify
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index); // Initialize with model data and state

    // Remove focus state from the viewOption if present before drawing,
    // so we can draw the background/selection first without the focus rect.
    // The style will draw focus later if needed based on the original 'option'.
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;


    // Check if this is the size column
    if (index.column() == FILE_SIZE_COLUMN)
    {
        // Get the raw data from the model (which provides qint64 for DisplayRole)
        qint64 bytes = index.data(Qt::DisplayRole).toLongLong(); // Explicitly get DisplayRole

        // Format the bytes into a human-readable string
        viewOption.text = bytesToGBMBKB(bytes) ;

        // Draw the item using the current style with the formatted text
        // Use the original 'option' which still has the focus state if needed by the style
        QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &viewOption, painter, viewOption.widget);
    }
    else
    {
        // For other columns, let the base class delegate handle the painting
        QStyledItemDelegate::paint(painter, viewOption, index);
    }
}