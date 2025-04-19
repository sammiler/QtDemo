#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QVariant>
#include <QString>

// 列定义
#define FILE_NAME_COLUMN    0   // 文件名称
#define FILE_OPERATE_COLUMN 1   // 操作列 (将绘制按钮)

// 简单的数据结构
struct FileRecord
{
    QString strFileName; // 文件名称
    // 可以根据需要添加其他字段
};

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
    // data 提供数据
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // setData 不实现，因为本例不涉及编辑
    // bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    // headerData 提供表头文本
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // flags 设置单元格标志
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // 更新数据的方法
    void updateData(const QList<FileRecord> &recordList);

    // 获取指定源索引的原始记录（在处理委托信号时可能需要）
    FileRecord getRecord(int row) const;


private:
    QList<FileRecord> m_recordList;
};

#endif // TABLEMODEL_H