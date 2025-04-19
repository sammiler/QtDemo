#include "TableModel.h"

#include <QString>
#include <QLocale> // 用于大小格式化

// 辅助函数：格式化字节大小 (这里简单实现，或从之前例子复制)
QString bytesToGBMBKB(qint64 size)
{
    if (size < 0) return "Invalid Size";
    const qint64 GB = 1024LL * 1024 * 1024;
    const qint64 MB = 1024LL * 1024;
    const qint64 KB = 1024LL;
    QLocale locale;
    if (size >= GB) return locale.toString((double)size / GB, 'f', 2) + " GB";
    else if (size >= MB) return locale.toString((double)size / MB, 'f', 2) + " MB";
    else if (size >= KB) return locale.toString((double)size / KB, 'f', 2) + " KB";
    else return locale.toString(size) + " Bytes";
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
    if (parent.isValid()) return 0;
    return m_recordList.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return 2; // 文件名 (HTML) 和 大小
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
            // 为文件名列构造 HTML 字符串
            // 包含一些样式和图片
            QString html = QString(
                "<html><body>"
                "<span style='color: blue;'>Name: </span>"
                "<span style='font-weight: bold;'>%1</span>"
                "<br>" // 换行
                "<img src=':/Images/logo.png' width='40' height='40'>" // 引用资源文件中的图片
                "</body></html>"
            ).arg(record.strFileName);
            return html;
        }
        else if (index.column() == FILE_SIZE_COLUMN)
        {
            // 大小列返回 qint64 或格式化字符串，本例不使用委托绘制大小，直接返回格式化字符串方便展示
            return bytesToGBMBKB(record.nSize);
        }
        break;
    }
    case Qt::TextAlignmentRole: // 文本对齐
    {
        if (index.column() == FILE_SIZE_COLUMN)
            return QVariant(Qt::AlignRight | Qt::AlignVCenter);
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }
    // 可以根据需要添加其他角色，如 Qt::ToolTipRole 等
    default:
        break;
    }

    return QVariant();
}

// bool TableModel::setData(...) 不实现

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return QAbstractItemModel::flags(index);
    // 单元格是可用和可选中的
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == FILE_NAME_COLUMN) return QStringLiteral("文件信息 (HTML)");
        if (section == FILE_SIZE_COLUMN) return QStringLiteral("大小");
    }
    // 表头对齐
    if (orientation == Qt::Horizontal && role == Qt::TextAlignmentRole)
    {
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}