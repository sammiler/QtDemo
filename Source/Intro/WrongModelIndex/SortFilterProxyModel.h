#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>

#include "tablemodel.h" // Include TableModel.h for column defines

class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit SortFilterProxyModel(QObject *parent = nullptr);
    ~SortFilterProxyModel() override;

protected:
    // Override lessThan for custom sorting logic (specifically for name column)
    // Default comparison used for Date/Time, Size (on raw value), and Checkbox columns.
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // SORTFILTERPROXYModel_H