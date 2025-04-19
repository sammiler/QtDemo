#include "SortFilterProxyModel.h"
#include "TableModel.h" // Include again for explicit access to defines

#include <QVariant>
#include <QString>
#include <QStringList>
#include <QDebug>

SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    // Default sorting uses Qt::DisplayRole.
    // Our overridden lessThan handles Name.
    // For Size, Date/Time, and Checkbox, it falls back to base class lessThan,
    // which compares DisplayRole data (qint64, QDateTime, bool respectively), which is correct.
}

SortFilterProxyModel::~SortFilterProxyModel()
{
}

// Custom comparison logic for sorting
// Handles custom name sorting. Uses default base class comparison for others.
bool SortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if (!source_left.isValid() || !source_right.isValid())
        return false;

    int column = source_left.column();

    // Get the data from the source model using Qt::DisplayRole
    QVariant leftData = sourceModel()->data(source_left, Qt::DisplayRole);
    QVariant rightData = sourceModel()->data(source_right, Qt::DisplayRole);

    // Implement custom logic based on the column
    if (column == FILE_NAME_COLUMN)
    {
        // Custom sorting for file names (string part then optional integer part)
        if (leftData.canConvert<QString>() && rightData.canConvert<QString>())
        {
            QString strLeft = leftData.toString();
            QString strRight = rightData.toString();

            int leftLastSpace = strLeft.lastIndexOf(' ');
            int rightLastSpace = strRight.lastIndexOf(' ');

            QString leftStringPart = strLeft;
            int leftNumPart = -1;

            QString rightStringPart = strRight;
            int rightNumPart = -1;

            if (leftLastSpace != -1 && leftLastSpace < strLeft.length() - 1) {
                 leftStringPart = strLeft.left(leftLastSpace);
                 bool ok;
                 int num = strLeft.mid(leftLastSpace + 1).section('.', 0, 0).toInt(&ok);
                 if (ok) {
                     leftNumPart = num;
                 }
            }

            if (rightLastSpace != -1 && rightLastSpace < rightData.toString().length() - 1) {
                 rightStringPart = rightData.toString().left(rightLastSpace);
                  bool ok;
                 int num = rightData.toString().mid(rightLastSpace + 1).section('.', 0, 0).toInt(&ok);
                  if (ok) {
                     rightNumPart = num;
                 }
            }

            int stringCompareResult = QString::compare(leftStringPart, rightStringPart, Qt::CaseInsensitive);

            if (stringCompareResult == 0)
            {
                if (leftNumPart == -1 && rightNumPart != -1) return true;
                if (leftNumPart != -1 && rightNumPart == -1) return false;
                if (leftNumPart != -1 && rightNumPart != -1) {
                     return leftNumPart < rightNumPart;
                }
                 return QString::compare(strLeft, strRight, Qt::CaseInsensitive) < 0;
            }
            else
            {
                return stringCompareResult < 0;
            }
        }
    }
    // For other columns (Size, Date/Time, Checkbox), the base class lessThan is called
    // which compares the QVariant data from Qt::DisplayRole.
    // TableModel returns qint64, QDateTime, and bool for DisplayRole respectively,
    // and QVariant comparison works correctly for these types.
    return QSortFilterProxyModel::lessThan(source_left, source_right);
}