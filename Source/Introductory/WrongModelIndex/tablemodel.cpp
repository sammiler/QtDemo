#include "TableModel.h"

#include <QTime>
#include <QDebug>
#include <QString>
#include <QLocale>
#include <QRandomGenerator> // Added for sample data generation in windows


// Helper function for byte formatting (defined here for use by data and delegate)
// Note: It's also defined in SortDelegate.cpp. In a real project, put this in a common utility file.
QString bytesToGBMBKB(qint64 size); // Declare again here

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableModel::~TableModel()
{
}

void TableModel::updateData(const QList<FileRecord> &recordList)
{
    beginResetModel();
    m_recordList = recordList;
    endResetModel();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_recordList.count();
}

// Returns the number of columns (now 4 including the checkbox)
int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 4; // 3 original columns + 1 checkbox column
}

// Provides data for a given index and role
QVariant TableModel::data(const QModelIndex &index, const int role) const
{
    if (!index.isValid())
        return {};

    if (index.row() >= m_recordList.count() || index.column() >= 4) // Check against 4 columns
        return {};

    const FileRecord &record = m_recordList.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole: // Data for display or default sorting
    {
        if (index.column() == FILE_NAME_COLUMN)
        {
            return record.strFileName;
        }
        if (index.column() == DATE_TIME_COLUMN)
        {
            // Return QDateTime for default sorting
            return record.dateTime; // Or return formatted string if default QDateTime sort is not desired
        }
        if (index.column() == FILE_SIZE_COLUMN)
        {
            // Return raw qint64 size for sorting
            return record.nSize;
        }
        if (index.column() == CHECK_BOX_COLUMN)
        {
            // Although not typically displayed as text, returning a boolean
            // for DisplayRole can be useful for default sorting if needed,
            // or for debugging. The delegate/view uses CheckStateRole primarily.
            return record.bChecked;
        }
        break;
    }
    case Qt::CheckStateRole: // Role for checkbox state
    {
        if (index.column() == CHECK_BOX_COLUMN)
        {
            // Return Checked or Unchecked based on the boolean state
            return record.bChecked ? Qt::Checked : Qt::Unchecked;
        }
        break;
    }
    case Qt::TextAlignmentRole: // Role for text alignment
    {
        if (index.column() == FILE_SIZE_COLUMN) {
             return {Qt::AlignRight | Qt::AlignVCenter};
        } else if (index.column() == CHECK_BOX_COLUMN) {
             return {Qt::AlignCenter}; // Center the checkbox
        }
        else {
            return {Qt::AlignLeft | Qt::AlignVCenter};
        }
        break;
    }
     case Qt::ToolTipRole: {
        if (index.column() == FILE_SIZE_COLUMN) {
             qint64 size = record.nSize; // Get raw size directly from record
             return QString("%1 Bytes").arg(size);
        } else if (index.column() == CHECK_BOX_COLUMN) {
             return record.bChecked ? "Checked" : "Unchecked";
        }
        // For other columns, default tooltip usually shows DisplayRole string
        break;
    }

    default:
        break;
    }

    return {};
}

// Sets the data for a given index and role
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    // Check if the index is for the checkbox column and the role is editable/checkstate
    // A view typically uses Qt::CheckStateRole and Qt::EditRole for checkboxes
    if (index.column() == CHECK_BOX_COLUMN && (role == Qt::CheckStateRole || role == Qt::EditRole))
    {
         if (index.row() >= m_recordList.count())
            return false;

        FileRecord &record = m_recordList[index.row()];

        // Toggle the boolean state based on the new check state value
        bool newCheckedState = (value.toInt() == Qt::Checked); // value from view is int (Qt::CheckState)
        if (record.bChecked != newCheckedState)
        {
            record.bChecked = newCheckedState;
            // Emit dataChanged for the index and the CheckStateRole
            emit dataChanged(index, index, {role, Qt::CheckStateRole}); // Also notify CheckStateRole explicitly
            return true; // Indicate data was set
        }
         return false; // Indicate data did not change
    }
    // Handle setting data for other columns if they were editable (like name, date, size)
    // This part is similar to previous examples if you need editing
    // For this demo, we only need to handle the checkbox change
    else if (role == Qt::EditRole)
    {
        // Handle editing for other columns if flags() allows Qt::ItemIsEditable
         if (index.row() >= m_recordList.count() || index.column() >= 3) // Check against 3 original columns
            return false;

        FileRecord &record = m_recordList[index.row()];
        bool changed = false;

        switch (index.column()) {
            case FILE_NAME_COLUMN:
                 if (record.strFileName != value.toString()) { record.strFileName = value.toString(); changed = true; }
                 break;
            case DATE_TIME_COLUMN:
                 if (record.dateTime != value.toDateTime()) { record.dateTime = value.toDateTime(); changed = true; }
                 break;
            case FILE_SIZE_COLUMN:
                 if (record.nSize != value.toLongLong()) { record.nSize = value.toLongLong(); changed = true; }
                 break;
            default:
                break;
        }

        if (changed) {
             emit dataChanged(index, index, {role, Qt::DisplayRole});
            return true;
        }
        return false;
    }


    return false; // Indicate data was not set for other roles/columns
}

// Returns item flags for a given index
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractTableModel::flags(index);

    Qt::ItemFlags defaultFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    // Add the flag to make the checkbox column user-checkable
    if (index.column() == CHECK_BOX_COLUMN)
    {
        defaultFlags |= Qt::ItemIsUserCheckable;
    }
     // Add flag to make other columns editable if desired (needed for setData above)
     // else {
     //    defaultFlags |= Qt::ItemIsEditable;
     // }


    return defaultFlags;
}

// headerData implementation (kept from previous steps)
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == FILE_NAME_COLUMN)
            return QStringLiteral("名称");
        if (section == DATE_TIME_COLUMN)
            return QStringLiteral("修改日期");
        if (section == FILE_SIZE_COLUMN)
            return QStringLiteral("大小");
        if (section == CHECK_BOX_COLUMN)
            return QStringLiteral("选中");
        // Header for checkbox column
    }
     if (orientation == Qt::Horizontal && role == Qt::TextAlignmentRole)
    {
         // Default header alignment (centered for checkbox, left for others)
         if (section == CHECK_BOX_COLUMN) return QVariant(Qt::AlignCenter);
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }


    return QAbstractTableModel::headerData(section, orientation, role);
}