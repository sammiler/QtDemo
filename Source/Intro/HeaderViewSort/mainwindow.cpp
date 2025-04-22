#include "mainwindow.h"

#include <QHeaderView> // Needed to configure table view headers
#include <QRandomGenerator> // Modern way to get random numbers
#include <QDateTime>
#include <QDate>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) // Initialize QWidget base class
{
    // Create main layout
    mainLayout = new QVBoxLayout(this); // 'this' sets the layout on the window

    // Create the table view
    tableView = new QTableView(this);

    // Create the custom model
    fileModel = new TableModel(this);

    // Create the proxy model for sorting and filtering (if needed later)
    proxyModel = new QSortFilterProxyModel(this);
    // Set the source model for the proxy
    proxyModel->setSourceModel(fileModel);

    // Set the proxy model on the table view
    tableView->setModel(proxyModel);

    // Enable sorting via clicking header
    tableView->setSortingEnabled(true);

    // Optional: Configure table view appearance
    // tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch columns

    // Set initial sort order (e.g., by file name ascending)
    tableView->sortByColumn(FILE_NAME_COLUMN, Qt::AscendingOrder);

    // Add the table view to the layout
    mainLayout->addWidget(tableView);

    // Set window title
    setWindowTitle("File Table Example");

    // Generate some sample data
    QList<FileRecord> recordList;
    // Using QRandomGenerator::global() is preferred over qrand/qsrand
    QRandomGenerator *rng = QRandomGenerator::global();

    for (int i = 0; i < 10; ++i) // Generate 10 sample records
    {
        int nIndex = rng->bounded(1, 21); // Random number between 1 and 20
        int nYear = 2023 + rng->bounded(0, 3); // Year 2023-2025
        int nMonth = rng->bounded(1, 13);   // Month 1-12
        int nDay = rng->bounded(1, 29);     // Day 1-28 (simple range)
        int nHour = rng->bounded(0, 24);    // Hour 0-23
        int nMinute = rng->bounded(0, 60);  // Minute 0-59
        int nSecond = rng->bounded(0, 60);  // Second 0-59
        qint64 nBytes = rng->bounded(100, 1000001); // Size between 100 bytes and 1MB

        QDate date(nYear, nMonth, nDay);
        QTime time(nHour, nMinute, nSecond);
        QDateTime dateTime(date, time);

        FileRecord record;
        record.strFileName = QString("Document_%1.txt").arg(nIndex);
        record.dateTime = dateTime;
        record.nSize = nBytes;

        recordList.append(record);
    }

    // Update the model with the generated data
    fileModel->updateData(recordList);

    // Optional: Resize window to a reasonable size
    resize(600, 400);
}

MainWindow::~MainWindow()
{
    // Widgets and layouts parented to 'this' will be automatically deleted
    // when the MainWindow is destroyed. Models parented to 'this' also.
}