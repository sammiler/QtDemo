#ifndef FILEDOWNLOADTHREAD_H
#define FILEDOWNLOADTHREAD_H

#include <QThread>
#include <QList>
#include <QRandomGenerator> // 用于生成随机数据
#include "TableModel.h" // 包含数据结构定义

// 注册 FileDownloadRecord 列表类型，以便通过信号槽跨线程传递
Q_DECLARE_METATYPE(QList<FileDownloadRecord>)

class FileDownloadThread : public QThread
{
    Q_OBJECT

public:
    explicit FileDownloadThread(QObject *parent = nullptr);
    ~FileDownloadThread() override;

    signals:
        // 信号，用于将更新后的下载记录列表发送给主线程
        void transfer(const QList<FileDownloadRecord> &recordList);

protected:
    // 线程的主要执行函数
    void run() override;

private:
    QList<FileDownloadRecord> m_records; // 线程内部维护的下载记录列表

    // 模拟更新进度和状态
    void updateProgress();
};

#endif // FILEDOWNLOADTHREAD_H