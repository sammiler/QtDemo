#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QVariant>
#include <QString>
#include <QDateTime> // 虽然下载记录没有时间，模型可能需要

// 列定义
#define FILE_DOWNLOAD_FILE_NAME_COLUMN	         0 // 文件名称
#define FILE_DOWNLOAD_SIZE_COLUMN	             1 // 大小
#define FILE_DOWNLOAD_STATUS_COLUMN	             2 // 状态
#define FILE_DOWNLOAD_PROGRESS_COLUMN	         3 // 进度条列

// 下载记录结构体
struct FileDownloadRecord
{
    QString strFileName;         //文件名称
    qint64 nSize;                //大小
    int nStatus;                 //状态 (例如: 0=等待, 1=下载中, 2=暂停, 3=完成, 4=错误)
    int nProgress;               //进度 (0-100)

    // Constructor for convenience
    FileDownloadRecord(QString name = "", qint64 size = 0, int status = 0, int progress = 0)
        : strFileName(name), nSize(size), nStatus(status), nProgress(progress) {}
};

// 自定义模型
class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel() override;

    // QAbstractTableModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // setData 不需要，因为数据由线程更新
    // bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // 更新数据的方法 (槽函数，由线程信号触发)
    public slots:
        void updateData(const QList<FileDownloadRecord> &recordList); // 接收线程发送的更新数据

private:
    QList<FileDownloadRecord> m_recordList; // 存储下载记录列表

    // 辅助函数，将状态码转换为字符串
    QString statusToString(int status) const;
};

#endif // TABLEMODEL_H