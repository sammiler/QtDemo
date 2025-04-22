#include "mainwindow.h"
#include "worker.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , priorityCombo(new QComboBox(this))
    , workerObjectButton(new QPushButton("启动 Worker-Object 线程", this))
    , workerThreadButton(new QPushButton("启动 WorkerThread 线程", this))
    , outputText(new QTextEdit(this))
    , mainLayout(new QVBoxLayout)
    , workerThread(new WorkerThread(this))
    , innerThread(new QThread(this))
{
    // 创建中心部件
    const QPointer<QWidget> centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    // 设置优先级下拉框
    priorityCombo->addItem("IdlePriority", QThread::IdlePriority);
    priorityCombo->addItem("LowestPriority", QThread::LowestPriority);
    priorityCombo->addItem("LowPriority", QThread::LowPriority);
    priorityCombo->addItem("NormalPriority", QThread::NormalPriority);
    priorityCombo->addItem("HighPriority", QThread::HighPriority);
    priorityCombo->addItem("HighestPriority", QThread::HighestPriority);
    priorityCombo->addItem("TimeCriticalPriority", QThread::TimeCriticalPriority);
    priorityCombo->setCurrentIndex(3); // 默认 NormalPriority
    mainLayout->addWidget(priorityCombo);

    // 添加按钮
    mainLayout->addWidget(workerObjectButton);
    mainLayout->addWidget(workerThreadButton);

    // 设置输出文本框
    outputText->setReadOnly(true);
    mainLayout->addWidget(outputText);

    // 设置窗口标题和大小
    setWindowTitle("线程示例");
    resize(600, 400);

    // 连接信号和槽
    connect(workerObjectButton, &QPushButton::clicked, this, &MainWindow::onWorkerObjectButtonClicked);
    connect(workerThreadButton, &QPushButton::clicked, this, &MainWindow::onWorkerThreadButtonClicked);
}

MainWindow::~MainWindow() {
    // 确保 Worker-Object 线程安全退出
    if (innerThread) {
        innerThread->quit();
        innerThread->wait();
    }
    // 确保 WorkerThread 安全退出
    if (workerThread) {
        workerThread->quit();
        workerThread->wait();
    }
}

void MainWindow::onWorkerObjectButtonClicked()
{
    const QThread::Priority priority = static_cast<QThread::Priority>(priorityCombo->currentData().toInt());
    outputText->append("启动 Worker-Object 线程，优先级: " + priorityCombo->currentText());

    // 创建 Worker 和线程
    const QPointer<Worker> worker = new Worker;
    worker->moveToThread(innerThread);

    // 连接信号和槽
    connect(innerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::startWork, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &MainWindow::handleResult);
    connect(innerThread, &QThread::started, this, [=]() { emit startWork("Worker-Object 任务"); });

    // 设置优先级并启动线程
    innerThread->setPriority(priority);
    innerThread->start();
}

void MainWindow::onWorkerThreadButtonClicked()
{
    const QThread::Priority priority = static_cast<QThread::Priority>(priorityCombo->currentData().toInt());
    outputText->append("启动 WorkerThread 线程，优先级: " + priorityCombo->currentText());

    // 创建 WorkerThread
    connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResult);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);

    // 设置优先级并启动线程
    workerThread->setPriority(priority);
    workerThread->start();
}

void MainWindow::handleResult(const QString &result) const {
    outputText->append(result);
}

