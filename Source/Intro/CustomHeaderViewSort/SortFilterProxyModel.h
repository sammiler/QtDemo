#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>

#include "TableModel.h" // Include TableModel.h to access column defines and roles

class SortFilterProxyModel final : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    // Constructor
    explicit SortFilterProxyModel(QObject *parent = nullptr);

    // Destructor
    ~SortFilterProxyModel() override;

protected:
    // Override lessThan for custom sorting logic
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // SORTFILTERPROXYMODEL_H