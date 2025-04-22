#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QVariant>
#include <QDateTime>
#include <QColor>

// Column definitions
#define FILE_NAME_COLUMN 0   // 文件名
#define DATE_TIME_COLUMN 1   // 修改日期
#define FILE_SIZE_COLUMN 2   // 文件大小

// Custom role to get raw data for sorting
// QAbstractTableModel sorts based on DisplayRole by default,
// but we need raw numerical size for sorting, and parts of the filename string.
// User roles start from Qt::UserRole.
enum FileTableRoles {
    RawDataRole = Qt::UserRole + 1 // Role to get raw data for sorting
    // Add other custom roles here if needed
};


// Data structure for file records
typedef struct FileRecord
{
    QString strFileName; // 文件名
    QDateTime dateTime;  // 修改日期
    qint64 nSize;        // 文件大小
} FileRecord;

// Custom model inheriting QAbstractTableModel
class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel() override;

    // QAbstractTableModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // Modified data method to handle RawDataRole
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Custom method to update the data
    void updateData(const QList<FileRecord> &recordList);

private:
    QList<FileRecord> m_recordList;
};

#endif // TABLEMODEL_H