#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);

    public slots:
        void doWork(const QString &parameter);

    signals:
        void resultReady(const QString &result);
};

class WorkerThread final : public QThread
{
    Q_OBJECT

public:
    explicit WorkerThread(QObject *parent = nullptr);
    void run() override;
    ~WorkerThread() override;
    signals:
        void resultReady(const QString &result) const;
};

#endif // WORKER_H