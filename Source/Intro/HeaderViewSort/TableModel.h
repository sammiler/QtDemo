#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QVariant>
#include <QDateTime>
#include <QColor>

// Column definitions (using your provided defines)
#define FILE_NAME_COLUMN 0   // 文件名
#define DATE_TIME_COLUMN 1   // 修改日期
#define FILE_SIZE_COLUMN 2   // 文件大小

// Data structure for file records
typedef struct FileRecord
{
    QString strFileName; // 文件名
    QDateTime dateTime;  // 修改日期
    qint64 nSize;        // 文件大小
} FileRecord; // Changed struct name to PascalCase for consistency

// Custom model inheriting QAbstractTableModel
class TableModel : public QAbstractTableModel
{
    Q_OBJECT // Required for signals/slots and other meta-object features

public:
    // Constructor
    explicit TableModel(QObject *parent = nullptr);

    // Destructor
    ~TableModel() override;

    // QAbstractTableModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override; // Added EditRole as common default
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Custom method to update the data in the model
    void updateData(const QList<FileRecord> &recordList); // Pass by const reference

private:
    QList<FileRecord> m_recordList; // List to store file records
};

#endif // TABLEMODEL_H