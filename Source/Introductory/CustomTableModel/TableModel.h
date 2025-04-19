#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <QAbstractTableModel> // 继承自 QAbstractTableModel
#include <QList>             // 需要 QList
#include <QVariant>          // 需要 QVariant
#include <QColor>            // 需要 QColor
#include <QModelIndex>       // 需要 QModelIndex
#include <QSize>             // 需要 QSize
#include <Qt>                // 需要 Qt::

// 定义 FileRecord 结构体，用于存储一行数据
struct FileRecord
{
    bool bChecked;       // 复选框状态
    QString strFilePath; // 文件路径字符串
    // 如果需要，可以在这里添加其他字段，如文件大小、修改日期等
};

// 定义列的枚举或常量，提高代码可读性
#define CHECK_BOX_COLUMN 0 // 复选框列的索引
#define File_PATH_COLUMN 1 // 文件路径列的索引


class TableModel : public QAbstractTableModel
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel() override;

    // --- 必须重写的 QAbstractItemModel 纯虚函数 ---
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;     // 返回行数
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;  // 返回列数
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override; // 提供单元项数据
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override; // 设置单元项数据
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override; // 提供表头数据
    Qt::ItemFlags flags(const QModelIndex &index) const override; // 提供单元项标志 (如是否可选中、可复选等)

    // --- 自定义方法 ---
    void updateData(QList<FileRecord> recordList); // 更新模型数据并通知视图刷新

private:
    QList<FileRecord> m_recordList; // 存储表格数据的列表
};

#endif // TABLE_MODEL_H