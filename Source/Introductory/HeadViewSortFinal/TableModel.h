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
    Q_OBJECT // Required for signals/slots

public:
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel() override;

    // QAbstractTableModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // data method now returns raw qint64 for size column's DisplayRole
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Custom method to update the data in the model
    void updateData(const QList<FileRecord> &recordList);

private:
    QList<FileRecord> m_recordList; // List to store file records
};

#endif // TABLEMODEL_H