#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QVariant>
#include <QDateTime>
#include <QColor>
#include <Qt> // For Qt::CheckStateRole

// Column definitions
#define FILE_NAME_COLUMN 0   // 文件名
#define DATE_TIME_COLUMN 1   // 修改日期
#define FILE_SIZE_COLUMN 2   // 文件大小
#define CHECK_BOX_COLUMN 3   // 复选框列 // New column

// Data structure for file records
typedef struct FileRecord
{
    QString strFileName; // 文件名
    QDateTime dateTime;  // 修改日期
    qint64 nSize;        // 文件大小
    bool bChecked;       // 复选框状态 // New member
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
    // columnCount now returns 4
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // data handles CheckStateRole and provides bool for DisplayRole (or UserRole)
    QVariant data(const QModelIndex &index, int role) const override;
    // setData handles toggling checkbox state
    bool setData(const QModelIndex &index, const QVariant &value, int role ) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    // flags adds ItemIsUserCheckable for the checkbox column
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void updateData(const QList<FileRecord> &recordList);

private:
    QList<FileRecord> m_recordList;
};

#endif // TABLEMODEL_H