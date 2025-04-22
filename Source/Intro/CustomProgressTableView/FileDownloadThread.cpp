#include "FileDownloadThread.h"
#include <QTime> // 需要用于模拟随机数种子 (虽然 QRandomGenerator 是现代方式)
#include <QDebug> // 可选，用于调试输出
#include <QCoreApplication> // 用于 msleep

FileDownloadThread::FileDownloadThread(QObject *parent)
    : QThread(parent)
{
    // 在线程创建时注册元类型 (也可以在 main 函数中注册)
    // qRegisterMetaType<QList<FileDownloadRecord>>("QList<FileDownloadRecord>"); // 在 main 注册更保险
    qDebug() << "FileDownloadThread created";

    // 初始化一些模拟的下载记录
    m_records.append(FileDownloadRecord("/downloads/file_a.zip", 1024 * 1024 * 50)); // 50 MB
    m_records.append(FileDownloadRecord("/downloads/doc_b.pdf", 1024 * 800)); // 800 KB
    m_records.append(FileDownloadRecord("/downloads/image_c.png", 1024 * 1024 * 2)); // 2 MB
    m_records.append(FileDownloadRecord("/downloads/video_d.mp4", 1024 * 1024 * 1024 * 1.5)); // 1.5 GB
    m_records.append(FileDownloadRecord("/downloads/archive_e.tar.gz", 1024 * 1024 * 100)); // 100 MB

    // 初始状态为等待
    for(auto &record : m_records) {
        record.nStatus = 0; // Waiting
        record.nProgress = 0;
    }
}

FileDownloadThread::~FileDownloadThread()
{
    qDebug() << "FileDownloadThread destroying, requesting interruption";
    requestInterruption(); // 请求中断 run 循环
    wait(); // 等待 run 方法结束
    qDebug() << "FileDownloadThread destroyed";
}

void FileDownloadThread::run()
{
    qDebug() << "FileDownloadThread started";
    QRandomGenerator *rng = QRandomGenerator::global(); // 使用现代随机数生成器

    // 模拟一些记录开始下载
    m_records[0].nStatus = 1; // Downloading
    m_records[2].nStatus = 1; // Downloading
    m_records[4].nStatus = 1; // Downloading


    while (!isInterruptionRequested()) // 循环直到请求中断
    {
        updateProgress(); // 模拟更新进度

        // 发送更新后的数据列表给主线程
        emit transfer(m_records);

        // 休眠一段时间
        msleep(200); // 模拟更快更新，可以调整
    }
    qDebug() << "FileDownloadThread run loop finished";
}

// 模拟更新进度和状态
void FileDownloadThread::updateProgress()
{
    QRandomGenerator *rng = QRandomGenerator::global();

    for(auto &record : m_records) {
        // 只更新下载中的记录
        if (record.nStatus == 1) { // Downloading
            // 模拟进度增加
            record.nProgress += rng->bounded(1, 10); // 每次增加1-9%
            if (record.nProgress >= 100) {
                record.nProgress = 100;
                record.nStatus = 3; // 完成
            }
        } else if (record.nStatus == 0) { // Waiting
            // 模拟少量记录开始下载
            if (rng->generate() % 100 < 5) { // 5% 的几率开始下载
                record.nStatus = 1; // Downloading
            }
        }
        // 可以添加暂停/错误状态的模拟
    }
}