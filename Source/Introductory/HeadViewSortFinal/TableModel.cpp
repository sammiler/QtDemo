#include "TableModel.h"

#include <QTime>
#include <QDebug>
#include <QString>
// QLocale is not strictly needed here anymore as formatting is in the delegate
// #include <QLocale>

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

    return 3; // We have 3 columns
}

// Provides data for a given index and role
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_recordList.count() || index.column() >= 3)
        return QVariant();

    const FileRecord &record = m_recordList.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole: // Data to be displayed in the view (raw size for sorting)
    {
        if (index.column() == FILE_NAME_COLUMN)
        {
            return record.strFileName; // Raw string for name sorting
        }
        else if (index.column() == DATE_TIME_COLUMN)
        {
            // Raw QDateTime for date sorting (QVariant handles QDateTime comparison)
            return record.dateTime;
        }
        else if (index.column() == FILE_SIZE_COLUMN)
        {
	        // Return the raw qint64 size for sorting
            return record.nSize;
        }
        break;
    }
    // RawDataRole is removed in this approach
    // case RawDataRole: { ... } break;

    case Qt::TextAlignmentRole: // Role for text alignment (still applies)
    {
        if (index.column() == FILE_SIZE_COLUMN) {
             // Size column text will be right-aligned
             return QVariant(Qt::AlignRight | Qt::AlignVCenter);
        } else {
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }
    // Add other roles like Qt::ToolTipRole here if needed, accessing DisplayRole data
    case Qt::ToolTipRole: {
        if (index.column() == FILE_SIZE_COLUMN) {
             // When using this delegate approach, index.data() for ToolTipRole
             // will still give the raw qint64 from DisplayRole. Format it here.
             return QString("%1 Bytes").arg(record.nSize);
        }
         // For other columns, tooltip would show DisplayRole string representation
        return QVariant(); // Default tooltip handling
    }
    default:
        break;
    }

    return QVariant();
}

// setData implementation (kept from previous steps)
// If cells were editable, a delegate would be needed to convert the input string
// back to qint64, QDateTime, etc., and call setData with the correct type.
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
        // Emit dataChanged for the DisplayRole index
        // The delegate will pick up the change and repaint
        emit dataChanged(index, index, {role, Qt::DisplayRole}); // Notify DisplayRole change
        return true;
    }

    return false;
}

// headerData implementation (kept from previous steps)
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
     if (orientation == Qt::Horizontal && role == Qt::TextAlignmentRole)
    {
         // Default header alignment
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }


    return QAbstractTableModel::headerData(section, orientation, role);
}

// flags implementation (kept from previous steps)
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags defaultFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    // Uncomment if you want to make cells editable via the view/delegate
    // defaultFlags |= Qt::ItemIsEditable;

    return defaultFlags;
}