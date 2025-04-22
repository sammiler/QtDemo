#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QComboBox>
#include <QThread>

#include "worker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


Q_SIGNALS:
    void startWork(const QString &parameter);
private slots:
        void onWorkerObjectButtonClicked();
    void onWorkerThreadButtonClicked();
    void handleResult(const QString &result) const;

private:
    const QPointer<QComboBox> priorityCombo;
    const QPointer<QPushButton> workerObjectButton;
    const QPointer<QPushButton> workerThreadButton;
    const QPointer<QTextEdit> outputText;
    const QPointer<QVBoxLayout> mainLayout;
    const QPointer<WorkerThread> workerThread;
    const QPointer<QThread> innerThread;
};

#endif // MAINWINDOW_H