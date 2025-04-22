#include "TableModel.h"

#include <QTime>
#include <QDebug>
#include <QString>
#include <QLocale> // For number formatting

// Helper function to format bytes into human-readable string
QString bytesToGBMBKB(qint64 size)
{
    if (size < 0) return "Invalid Size"; // Handle negative size case

    const qint64 GB = 1024LL * 1024 * 1024; // Use LL for long long literal
    const qint64 MB = 1024LL * 1024;
    const qint64 KB = 1024LL;

    QLocale locale; // Use locale for number formatting (e.g., decimal separator)

    if (size >= GB) {
        return locale.toString((double)size / GB, 'f', 2) + " GB";
    } else if (size >= MB) {
        return locale.toString((double)size / MB, 'f', 2) + " MB";
    } else if (size >= KB) {
        return locale.toString((double)size / KB, 'f', 2) + " KB";
    } else {
        return locale.toString(size) + " Bytes";
    }
}


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

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

// Modified data method to handle Qt::DisplayRole and RawDataRole
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    if (index.row() >= m_recordList.count() || index.column() >= 3)
        return {};

    const FileRecord &record = m_recordList.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole: // Data to be displayed
    {
        if (index.column() == FILE_NAME_COLUMN)
        {
            return record.strFileName;
        }
        if (index.column() == DATE_TIME_COLUMN)
        {
            // Format the datetime for display
            return record.dateTime.toString("yyyy-MM-dd HH:mm:ss");
        }
        if (index.column() == FILE_SIZE_COLUMN)
        {
            // Format the size for display
            return bytesToGBMBKB(record.nSize);
        }
        break; // Break from DisplayRole
    }
    case RawDataRole: // Raw data for sorting or other logic
    {
        if (index.column() == FILE_NAME_COLUMN)
        {
            return record.strFileName; // Return raw string
        }
        else if (index.column() == DATE_TIME_COLUMN)
        {
            return record.dateTime; // Return raw QDateTime
        }
        else if (index.column() == FILE_SIZE_COLUMN)
        {
            return record.nSize; // Return raw qint64 size
        }
        break; // Break from RawDataRole
    }
    case Qt::TextAlignmentRole: // Role for text alignment
    {
        if (index.column() == FILE_SIZE_COLUMN) {
             return QVariant(Qt::AlignRight | Qt::AlignVCenter); // Right align size
        } else {
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter); // Left align other columns
        }
    }
    // Add other roles if needed...
    default:
        break; // Return default QVariant for unhandled roles
    }

    return QVariant();
}

// setData implementation remains the same as it's not used for display/sorting logic here
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    if (index.row() >= m_recordList.count() || index.column() >= 3)
        return false;

    FileRecord &record = m_recordList[index.row()];

    bool changed = false;
    int nColumn = index.column();

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

    if (changed) {
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == FILE_NAME_COLUMN)
            return QStringLiteral("名称");
        else if (section == DATE_TIME_COLUMN)
            return QStringLiteral("修改日期");
        else if (section == FILE_SIZE_COLUMN)
            return QStringLiteral("大小");
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags defaultFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    // return defaultFlags | Qt::ItemIsEditable; // Uncomment to make cells editable

    return defaultFlags;
}