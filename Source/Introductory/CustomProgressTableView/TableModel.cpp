#include "TableModel.h"
#include "ProgressBarDelegate.h" // 需要包含委托头文件以便访问其需要的角色定义 (如果委托需要自定义角色)

#include <QLocale> // 用于大小格式化
#include <QDebug> // 可选，用于调试

// 辅助函数：格式化字节大小 (与之前的例子相同)
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

// 槽函数：接收线程发送的数据并更新模型
void TableModel::updateData(const QList<FileDownloadRecord> &recordList)
{
    // 如果记录数量变化，需要通知视图重置
    if (m_recordList.count() != recordList.count()) {
        beginResetModel();
        m_recordList = recordList;
        endResetModel();
    } else {
        // 如果记录数量不变，只需更新数据并通知视图改变了哪些项
        m_recordList = recordList;
        // 通知视图所有数据都可能改变了，强制重绘
        // 这样简单，效率不如只通知改变的项，但对于小数据集和演示足够
        emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
    }
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_recordList.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return 4; // 文件名, 大小, 状态, 进度
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (index.row() >= m_recordList.count() || index.column() >= 4) return QVariant();

    const FileDownloadRecord &record = m_recordList.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole: // 用于显示和默认排序
    {
        if (index.column() == FILE_DOWNLOAD_FILE_NAME_COLUMN)
        {
            return record.strFileName;
        }
        else if (index.column() == FILE_DOWNLOAD_SIZE_COLUMN)
        {
            return bytesToGBMBKB(record.nSize); // 显示格式化大小
        }
        else if (index.column() == FILE_DOWNLOAD_STATUS_COLUMN)
        {
            return statusToString(record.nStatus); // 显示状态字符串
        }
        else if (index.column() == FILE_DOWNLOAD_PROGRESS_COLUMN)
        {
             // 进度列的 DisplayRole 可以返回进度值本身，
             // 或者返回进度文本，但通常委托会自己格式化文本。
             // 返回 int 可以用于默认排序 (按进度值排序)。
            return record.nProgress;
        }
        break;
    }
    case Qt::UserRole: // 用于委托获取原始进度值
    {
        if (index.column() == FILE_DOWNLOAD_PROGRESS_COLUMN)
        {
            return record.nProgress; // 返回原始进度 int
        }
        break;
    }
     case Qt::TextAlignmentRole: // 文本对齐
    {
        if (index.column() == FILE_DOWNLOAD_SIZE_COLUMN || index.column() == FILE_DOWNLOAD_PROGRESS_COLUMN)
             return QVariant(Qt::AlignRight | Qt::AlignVCenter);
        if (index.column() == FILE_DOWNLOAD_STATUS_COLUMN)
             return QVariant(Qt::AlignCenter);
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }
    // 可以添加其他角色如 Qt::DecorationRole (图标), Qt::ToolTipRole 等
    default:
        break;
    }

    return QVariant();
}

// setData 不需要实现，因为数据来自线程

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
        if (section == FILE_DOWNLOAD_FILE_NAME_COLUMN) return QStringLiteral("文件名");
        if (section == FILE_DOWNLOAD_SIZE_COLUMN) return QStringLiteral("大小");
        if (section == FILE_DOWNLOAD_STATUS_COLUMN) return QStringLiteral("状态");
        if (section == FILE_DOWNLOAD_PROGRESS_COLUMN) return QStringLiteral("进度");
    }
     if (orientation == Qt::Horizontal && role == Qt::TextAlignmentRole)
    {
        // 表头对齐
         if (section == FILE_DOWNLOAD_SIZE_COLUMN || section == FILE_DOWNLOAD_PROGRESS_COLUMN)
             return QVariant(Qt::AlignRight | Qt::AlignVCenter);
         if (section == FILE_DOWNLOAD_STATUS_COLUMN)
             return QVariant(Qt::AlignCenter);
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

// 将状态码转换为字符串
QString TableModel::statusToString(int status) const
{
    switch (status) {
        case 0: return QStringLiteral("等待");
        case 1: return QStringLiteral("下载中");
        case 2: return QStringLiteral("暂停");
        case 3: return QStringLiteral("完成");
        case 4: return QStringLiteral("错误");
        default: return QStringLiteral("未知");
    }
}