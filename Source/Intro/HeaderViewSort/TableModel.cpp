#include "TableModel.h"

#include <QTime> // Needed for date/time handling in data()
#include <QDebug> // Useful for debugging (optional)

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    // Constructor implementation (can be empty if no initialization is needed)
}

TableModel::~TableModel()
{
    // Destructor implementation (can be empty if resources are managed by QObject parent)
}

// Update the internal data list and notify views to reset
void TableModel::updateData(const QList<FileRecord> &recordList)
{
    // beginResetModel and endResetModel are crucial for notifying views
    // that the underlying data structure is about to change dramatically.
    beginResetModel();
    m_recordList = recordList; // Copy the provided list
    endResetModel();
}

// Returns the number of rows in the model
int TableModel::rowCount(const QModelIndex &parent) const
{
    // If parent is valid, this is a tree model, but we have a flat table
    if (parent.isValid())
        return 0;

    return m_recordList.count(); // Number of rows is the number of records
}

// Returns the number of columns in the model
int TableModel::columnCount(const QModelIndex &parent) const
{
    // If parent is valid, this is a tree model
    if (parent.isValid())
        return 0;

    return 3; // We have 3 columns: File Name, Date/Time, Size
}

// Provides data for a given index and role
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    // Check if the index is valid
    if (!index.isValid())
        return QVariant();

    // Check if the row and column are within bounds
    if (index.row() >= m_recordList.count() || index.column() >= 3)
        return QVariant();

    // Get the record for the current row
    const FileRecord &record = m_recordList.at(index.row()); // Use const reference for efficiency

    // Handle different display roles
    switch (role)
    {
    case Qt::DisplayRole: // The primary role for displaying text
    {
        // Return data based on the column
        if (index.column() == FILE_NAME_COLUMN)
        {
            return record.strFileName;
        }
        else if (index.column() == DATE_TIME_COLUMN)
        {
            // You might want to format the datetime string here
            return record.dateTime.toString("yyyy-MM-dd HH:mm:ss"); // Format the datetime
        }
        else if (index.column() == FILE_SIZE_COLUMN)
        {
            // You might want to format the size (e.g., KB, MB) here
            return record.nSize; // Display raw size in bytes
        }
        break; // Break from DisplayRole case
    }
    case Qt::TextAlignmentRole: // Role for text alignment
    {
        if (index.column() == FILE_SIZE_COLUMN) {
             return QVariant(Qt::AlignRight | Qt::AlignVCenter); // Right align size
        } else {
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter); // Left align other columns
        }
    }
    case Qt::TextColorRole: // Role for text color
        // return QColor(Qt::black); // Or any color you want
        break; // Don't handle unless you need custom coloring
    // Add other roles like Qt::DecorationRole, Qt::ToolTipRole, etc., if needed
    default:
        break; // Return default QVariant for unhandled roles
    }

    return QVariant(); // Return invalid QVariant for unhandled roles
}

// Sets the data for a given index and role
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Check if the index is valid and the role is editable (or DisplayRole as used in your snippet)
    if (!index.isValid() || role != Qt::EditRole) // Typically check for Qt::EditRole
        return false;

    // Check if the row and column are within bounds
    if (index.row() >= m_recordList.count() || index.column() >= 3)
        return false;

    // Get a reference to the record to modify it directly
    FileRecord &record = m_recordList[index.row()]; // Use reference to modify in place

    bool changed = false;
    int nColumn = index.column();

    // Update the record based on the column and value
    if (nColumn == FILE_NAME_COLUMN)
    {
        if (record.strFileName != value.toString()) {
            record.strFileName = value.toString();
            changed = true;
        }
    }
    else if (nColumn == DATE_TIME_COLUMN)
    {
        if (record.dateTime != value.toDateTime()) {
            record.dateTime = value.toDateTime();
             changed = true;
        }
    }
    else if (nColumn == FILE_SIZE_COLUMN)
    {
         if (record.nSize != value.toLongLong()) {
            record.nSize = value.toLongLong();
            changed = true;
         }
    }

    // If data changed, emit dataChanged signal
    if (changed) {
        emit dataChanged(index, index, {role}); // Specify the role that changed
        return true; // Indicate success
    }

    return false; // Indicate data did not change or role was not handled
}

// Provides data for the header
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Only handle horizontal headers for now
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        // Return header text based on the section (column index)
        if (section == FILE_NAME_COLUMN)
            return QStringLiteral("名称");
        else if (section == DATE_TIME_COLUMN)
            return QStringLiteral("修改日期");
        else if (section == FILE_SIZE_COLUMN)
            return QStringLiteral("大小");
    }

    // Return default QVariant for other orientations or roles
    return QAbstractTableModel::headerData(section, orientation, role); // Call base class implementation
}

// Returns item flags for a given index
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    // If index is invalid, return default flags
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    // Default flags: enabled and selectable
    // Add Qt::ItemIsEditable if you want to allow editing via the view/delegate
    Qt::ItemFlags defaultFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    // If you want the cells to be editable, uncomment Qt::ItemIsEditable
    // return defaultFlags | Qt::ItemIsEditable;

    return defaultFlags;
}