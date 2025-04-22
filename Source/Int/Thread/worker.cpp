#include "worker.h"
#include <QDebug>

Worker::Worker(QObject *parent)
    : QObject(parent)
{
}

void Worker::doWork(const QString &parameter)
{
    QString result = parameter + " 执行中...";
    qDebug() << result;

    // 模拟耗时任务
    for (int i = 0; i < 5; ++i) {
        if (QThread::currentThread()->isInterruptionRequested()) {
            result = parameter + " 被中断";
            emit resultReady(result);
            return;
        }
        QThread::msleep(500); // 模拟 500ms 耗时
        result = parameter + " 进度: " + QString::number((i + 1) * 20) + "%";
        qDebug() << result;
    }

    result = parameter + " 完成";
    emit resultReady(result);
}

WorkerThread::WorkerThread(QObject *parent)
    : QThread(parent)
{
}

void WorkerThread::run()
{
    QString result = "WorkerThread 任务 执行中...";
    qDebug() << result;

    // 模拟耗时任务
    for (int i = 0; i < 5; ++i) {
        if (isInterruptionRequested()) {
            result = "WorkerThread 任务 被中断";
            emit resultReady(result);
            return;
        }
        msleep(500); // 模拟 500ms 耗时
        result = "WorkerThread 任务 进度: " + QString::number((i + 1) * 20) + "%";
        qDebug() << result;
    }

    result = "WorkerThread 任务 完成";
    emit resultReady(result);
}

WorkerThread::~WorkerThread() {

}
