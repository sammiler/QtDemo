#include "mainwindow.h"

#include <QHeaderView>
#include <QRandomGenerator>
#include <QDateTime>
#include <QDate>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);

    tableView = new QTableView(this);

    fileModel = new TableModel(this);

    // Use our custom SortFilterProxyModel instead of the base QSortFilterProxyModel
    proxyModel = new SortFilterProxyModel(this);
    proxyModel->setSourceModel(fileModel);

    tableView->setModel(proxyModel);

    tableView->setSortingEnabled(true);

    // Optional: Configure table view appearance
    tableView->horizontalHeader()->setSectionResizeMode(FILE_NAME_COLUMN, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(DATE_TIME_COLUMN, QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(FILE_SIZE_COLUMN, QHeaderView::ResizeToContents);
    // Set the alignment for the header sections
    tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    // Set initial sort order (e.g., by file name ascending)
    tableView->sortByColumn(FILE_NAME_COLUMN, Qt::AscendingOrder);

    mainLayout->addWidget(tableView);

    setWindowTitle("File Table with Custom Sorting Example");

    // Generate some sample data (slightly varied names for testing sorting)
    QList<FileRecord> recordList;
    QRandomGenerator *rng = QRandomGenerator::global();

    // Add records to test the custom sorting
    recordList.append({"Doc 1.txt", QDateTime(QDate(2024, 1, 1), QTime(10, 0, 0)), rng->bounded(100, 1000001)});
    recordList.append({"Report 10.pdf", QDateTime(QDate(2024, 1, 2), QTime(10, 1, 0)), rng->bounded(100, 1000001)});
    recordList.append({"Doc 2.txt", QDateTime(QDate(2024, 1, 3), QTime(10, 2, 0)), rng->bounded(100, 1000001)});
    recordList.append({"Image 5.png", QDateTime(QDate(2024, 1, 4), QTime(10, 3, 0)), rng->bounded(100, 1000001)});
    recordList.append({"Doc 10.txt", QDateTime(QDate(2024, 1, 5), QTime(10, 4, 0)), rng->bounded(100, 1000001)});
    recordList.append({"Report 2.pdf", QDateTime(QDate(2024, 1, 6), QTime(10, 5, 0)), rng->bounded(100, 1000001)});
    recordList.append({"Doc 3.txt", QDateTime(QDate(2024, 1, 7), QTime(10, 6, 0)), rng->bounded(100, 1000001)});
    recordList.append({"Backup.zip", QDateTime(QDate(2024, 1, 8), QTime(10, 7, 0)), rng->bounded(1000000, 100000001)}); // Larger size
    recordList.append({"Image 1.png", QDateTime(QDate(2024, 1, 9), QTime(10, 8, 0)), rng->bounded(100, 1000001)});
    recordList.append({"Report 1.pdf", QDateTime(QDate(2024, 1, 10), QTime(10, 9, 0)), rng->bounded(100, 1000001)});
     recordList.append({"Doc.txt", QDateTime(QDate(2024, 1, 11), QTime(10, 10, 0)), rng->bounded(100, 1000001)}); // File without number


    // Update the model with the generated data
    fileModel->updateData(recordList);

    resize(700, 400); // Adjust size to fit columns better
}

MainWindow::~MainWindow()
{
}