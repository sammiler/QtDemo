#include "SortFilterProxyModel.h"
#include "TableModel.h" // Include again for explicit access to defines

#include <QVariant>
#include <QString>
#include <QStringList>
#include <QDebug> // For debugging (optional)

SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    // By default, QSortFilterProxyModel sorts using Qt::DisplayRole.
    // When overriding lessThan, we control specific columns.
    // For columns not handled here, it falls back to the base class lessThan,
    // which *will* use the data from Qt::DisplayRole. This is exactly what
    // we want for the size (raw qint64) and date/time (QDateTime) columns
    // in this delegate-based approach.
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
    // This is the data the model provides for display and default sorting.
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

            // Find the last space to separate potential name prefix and number
            int leftLastSpace = strLeft.lastIndexOf(' ');
            int rightLastSpace = strRight.lastIndexOf(' ');

            QString leftStringPart = strLeft;
            int leftNumPart = -1; // Default if no number found or parsing fails

            QString rightStringPart = strRight;
            int rightNumPart = -1;

            // Attempt to extract string and number parts from the left string
            if (leftLastSpace != -1 && leftLastSpace < strLeft.length() - 1) {
                 leftStringPart = strLeft.left(leftLastSpace);
                 // Try converting the part after the last space (and before the extension, if any) to an integer
                 bool ok;
                 int num = strLeft.mid(leftLastSpace + 1).section('.', 0, 0).toInt(&ok);
                 if (ok) {
                     leftNumPart = num;
                 }
            }

            // Attempt to extract string and number parts from the right string
            if (rightLastSpace != -1 && rightLastSpace < strRight.length() - 1) {
                 rightStringPart = rightData.toString().left(rightLastSpace); // Use rightData string
                  bool ok;
                 int num = rightData.toString().mid(rightLastSpace + 1).section('.', 0, 0).toInt(&ok); // Use rightData string
                  if (ok) {
                     rightNumPart = num;
                 }
            }

            // 1. Compare the string parts case-insensitively
            int stringCompareResult = QString::compare(leftStringPart, rightStringPart, Qt::CaseInsensitive);

            if (stringCompareResult == 0)
            {
                // 2. If string parts are the same, compare the number parts
                // Items without a number part (-1) sort before items with a number part.
                // If both have numbers, compare the numbers.
                if (leftNumPart == -1 && rightNumPart != -1) return true; // Left (no num) < Right (has num)
                if (leftNumPart != -1 && rightNumPart == -1) return false; // Left (has num) > Right (no num)
                if (leftNumPart != -1 && rightNumPart != -1) {
                     return leftNumPart < rightNumPart; // Both have numbers, compare them numerically
                }
                 // If both have no number part, or parsing failed for both,
                 // fall back to a simple case-insensitive comparison of the *original* full strings as a tie-breaker
                 return QString::compare(strLeft, strRight, Qt::CaseInsensitive) < 0;
            }
            else
            {
                // If string parts are different, the string comparison result determines the order
                return stringCompareResult < 0; // stringCompareResult is < 0 if left < right
            }
        }
        // If data isn't a string for some reason, fall back to default comparison
    }
    // For Size (FILE_SIZE_COLUMN) and Date/Time (DATE_TIME_COLUMN),
    // we don't add specific cases here. The base class QSortFilterProxyModel::lessThan
    // will be called. Since our TableModel returns qint64 and QDateTime
    // for DisplayRole for these columns, the default comparison of QVariants
    // containing these types will work correctly.
    // This implements the "QSortFilterProxyModel default sort... can meet our requirements" idea for size.
    return QSortFilterProxyModel::lessThan(source_left, source_right);
}