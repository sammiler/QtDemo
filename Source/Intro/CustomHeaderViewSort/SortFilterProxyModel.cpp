#include "SortFilterProxyModel.h"
#include "TableModel.h" // Include TableModel.h again to ensure defines are available

#include <QVariant>
#include <QString>
#include <QStringList>
#include <QDebug> // For debugging (optional)

SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

SortFilterProxyModel::~SortFilterProxyModel()
{
}

// Custom comparison logic for sorting
bool SortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    // Ensure valid indices
    if (!source_left.isValid() || !source_right.isValid())
        return false;

    // Get the column being sorted
    const int column = source_left.column();

    // Use the RawDataRole to get the underlying data for comparison
    const QVariant leftData = sourceModel()->data(source_left, RawDataRole);
    const QVariant rightData = sourceModel()->data(source_right, RawDataRole);

    // Implement custom logic based on the column
    if (column == FILE_NAME_COLUMN)
    {
        // Custom sorting for file names (string part then integer part)
        if (leftData.canConvert<QString>() && rightData.canConvert<QString>())
        {
            const QString strLeft = leftData.toString();
            const QString strRight = rightData.toString();

            // Remove common suffixes like ".cpp" if they exist, though the sample data uses ".txt"
            // This part of the original snippet's logic seems specific to ".cpp".
            // Let's refine it slightly to be more general, assuming the format is "String Number.Extension"
            // or "String.Extension" or just "String".
            // We'll split by the *last* space.
            int leftLastSpace = strLeft.lastIndexOf(' ');
            int rightLastSpace = strRight.lastIndexOf(' ');

            QString leftStringPart = strLeft;
            int leftNumPart = -1; // Use -1 to indicate no number found

            QString rightStringPart = strRight;
            int rightNumPart = -1;

            // Attempt to extract string and number parts if a space exists
            if (leftLastSpace != -1 && leftLastSpace < strLeft.length() - 1) {
                 leftStringPart = strLeft.left(leftLastSpace);
                 // Try converting the part after the last space to an integer
                 bool ok;
                 const int num = strLeft.mid(leftLastSpace + 1).section('.', 0, 0).toInt(&ok);
                 if (ok) {
                     leftNumPart = num;
                 }
            }

            if (rightLastSpace != -1 && rightLastSpace < strRight.length() - 1) {
                 rightStringPart = strRight.left(rightLastSpace);
                  bool ok;
                 const int num = strRight.mid(rightLastSpace + 1).section('.', 0, 0).toInt(&ok);
                  if (ok) {
                     rightNumPart = num;
                 }
            }


            // 1. Compare the string parts (case-insensitive)
            const int stringCompareResult = QString::compare(leftStringPart, rightStringPart, Qt::CaseInsensitive);

            if (stringCompareResult == 0)
            {
                // 2. If string parts are the same, compare the number parts
                // Items without a number part (-1) come before items with a number part.
                // If both have numbers, compare the numbers.
                if (leftNumPart == -1 && rightNumPart != -1) return true; // Left (no num) < Right (has num)
                if (leftNumPart != -1 && rightNumPart == -1) return false; // Left (has num) > Right (no num)
                if (leftNumPart != -1 && rightNumPart != -1) {
                     return leftNumPart < rightNumPart; // Both have numbers, compare them
                }
                 // If both have no number part, or if the part after space wasn't a number,
                 // fall back to a simple string comparison of the *original* full strings as a tie-breaker
                 return QString::compare(strLeft, strRight, Qt::CaseInsensitive) < 0;
            }
            else
            {
                // If string parts are different, the string comparison result determines the order
                return stringCompareResult < 0;
            }
        }
         // If not convertable to QString, fall back to default comparison
         // Or handle appropriately based on expected data types
    }
    else if (column == FILE_SIZE_COLUMN)
    {
        // Custom sorting for file size (compare as qint64)
        if (leftData.canConvert<qint64>() && rightData.canConvert<qint64>())
        {
            return leftData.toLongLong() < rightData.toLongLong();
        }
         // If not convertable to qint64, fall back to default comparison
    }
    // For other columns (like Date/Time), use the default comparison provided by QSortFilterProxyModel
    // The default lessThan will use Qt::DisplayRole by default, but since we provided RawDataRole for
    // Date/Time in TableModel::data, and QDateTime has a built-in comparison that works
    // with QVariant, the base class method should work correctly here.
    // If the base class default still used DisplayRole for other columns, you might need to
    // explicitly get data using DisplayRole for those columns if RawDataRole returns something different.
    // In our case, for Date/Time, RawDataRole and the default comparison of QDateTime variants works.
    return QSortFilterProxyModel::lessThan(source_left, source_right);
}