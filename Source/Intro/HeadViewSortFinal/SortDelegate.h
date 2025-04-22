#ifndef SORTDELEGATE_H
#define SORTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>

#include "TableModel.h" // Include TableModel.h for column defines
#include <QApplication> // For QApplication::style()
#include <QStyle> // For QStyle

// Function definition for byte formatting (needs to be accessible by delegate)
// We'll define it in SortDelegate.cpp
extern QString bytesToGBMBKB(qint64 size);


class SortDelegate : public QStyledItemDelegate
{
    Q_OBJECT // Required for signals/slots

public:
    explicit SortDelegate(QObject *parent = nullptr);
    ~SortDelegate() override;

    // Override the paint method to custom draw items
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // Optional: override sizeHint if custom size is needed for painted items
    // QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // SORTDELEGATE_H