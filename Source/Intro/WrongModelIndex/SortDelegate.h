#ifndef SORTDELEGATE_H
#define SORTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>

#include "tablemodel.h" // Include TableModel.h for column defines
#include <QApplication>
#include <QStyle>

// Function definition for byte formatting (needs to be accessible by delegate)
extern QString bytesToGBMBKB(qint64 size); // Declared here

class SortDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit SortDelegate(QObject *parent = nullptr);
    ~SortDelegate() override;

    // Override the paint method to custom draw items
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // SORTDELEGATE_H