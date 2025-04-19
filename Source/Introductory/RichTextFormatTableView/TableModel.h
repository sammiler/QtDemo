#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QVariant>
#include <QDateTime>

// 列定义 (简单起见，只用文件名和大小，HTML 绘制在文件名列)
#define FILE_NAME_COLUMN 0   // 文件名 (将绘制 HTML)
#define FILE_SIZE_COLUMN 1   // 文件大小 (普通显示)

// 简单的数据结构
typedef struct FileRecord
{
    QString strFileName; // 原始文件名 (用于构造 HTML)
    qint64 nSize;        // 文件大小
} FileRecord;

// 基础模型
class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel() override;

    // QAbstractTableModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // columnCount 返回 2
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // data 提供数据，文件名列提供 HTML 字符串
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // setData 不实现，因为本例不涉及编辑
    // bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    // headerData 提供表头文本
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // flags 设置单元格标志
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // 更新数据的方法
    void updateData(const QList<FileRecord> &recordList);

private:
    QList<FileRecord> m_recordList;
};

#endif // TABLEMODEL_H