#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>

#include "TableModel.h" // Include TableModel.h for column defines

class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT // Required for signals/slots

public:
    explicit SortFilterProxyModel(QObject *parent = nullptr);
    ~SortFilterProxyModel() override;

protected:
    // Override lessThan for custom sorting logic (specifically for name column)
    // For size and date/time columns, we'll use the base class default comparison
    // on the data from Qt::DisplayRole (raw qint64 or QDateTime).
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // SORTFILTERPROXYModel_H