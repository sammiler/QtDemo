#include "TableModel.h"

#include <QDebug> // 可选

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
    if (parent.isValid()) return 0;
    return m_recordList.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return 2; // 文件名 和 操作列
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (index.row() >= m_recordList.count() || index.column() >= 2) return QVariant();

    const FileRecord &record = m_recordList.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole: // 提供显示数据
    {
        if (index.column() == FILE_NAME_COLUMN)
        {
            return record.strFileName;
        }
        else if (index.column() == FILE_OPERATE_COLUMN)
        {
            // 操作列可以返回空字符串或一个标识，委托不依赖这个值绘制按钮
            return "";
        }
        break;
    }
    // 可以添加其他角色如 Qt::ToolTipRole 等
     case Qt::TextAlignmentRole: // 文本对齐
    {
         if (index.column() == FILE_OPERATE_COLUMN)
             return QVariant(Qt::AlignCenter); // 操作列居中
         return QVariant(Qt::AlignLeft | Qt::AlignVCenter); // 文件名左对齐
    }
    default:
        break;
    }

    return QVariant();
}

// bool TableModel::setData(...) 不实现

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return QAbstractItemModel::flags(index);
    // 所有项都是可用和可选中的
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == FILE_NAME_COLUMN) return QStringLiteral("文件名");
        if (section == FILE_OPERATE_COLUMN) return QStringLiteral("操作");
    }
    // 表头对齐
    if (orientation == Qt::Horizontal && role == Qt::TextAlignmentRole)
    {
        if (section == FILE_OPERATE_COLUMN) return QVariant(Qt::AlignCenter);
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

// 获取指定源索引的原始记录
FileRecord TableModel::getRecord(int row) const
{
    if (row >= 0 && row < m_recordList.count()) {
        return m_recordList.at(row);
    }
    return FileRecord(); // 返回空记录或适当的错误指示
}