#include "mainwindow.h"

#include <QRandomGenerator>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QCursor> // For QCursor::pos()

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // Set up main layout
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout); // Set the layout on the window

    // Create the table view
    tableView = new QTableView(this);

    // Create the custom model
    fileModel = new TableModel(this);

    // Create our custom proxy model
    proxyModel = new SortFilterProxyModel(this);
    // Set the custom model as the source for the proxy
    proxyModel->setSourceModel(fileModel);

    // Set the proxy model on the table view
    tableView->setModel(proxyModel);

    // Create the custom delegate for the size column
    sizeDelegate = new SortDelegate(this);
    // Set the delegate for the specific size column
    tableView->setItemDelegateForColumn(FILE_SIZE_COLUMN, sizeDelegate);


    // Enable sorting via clicking the header
    tableView->setSortingEnabled(true);

    // Optional: Configure table view appearance
    tableView->horizontalHeader()->setSectionResizeMode(FILE_NAME_COLUMN, QHeaderView::Interactive);
    tableView->horizontalHeader()->setSectionResizeMode(DATE_TIME_COLUMN, QHeaderView::Interactive);
    tableView->horizontalHeader()->setSectionResizeMode(FILE_SIZE_COLUMN, QHeaderView::Stretch );
    // tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter); // Alignment handled in model headerData

    // Set initial sort order (e.g., by file name ascending)
    tableView->sortByColumn(FILE_NAME_COLUMN, Qt::AscendingOrder);

    // Add the table view to the layout
    mainLayout->addWidget(tableView);

    // Set window title
    setWindowTitle("File Table with Delegate Display & Custom Sorting");

    // --- Setup Tooltip ---
    tableView->setMouseTracking(true); // Enable mouse tracking to get 'entered' signal
    connect(tableView, &QTableView::entered, this, &MainWindow::showToolTip);

    // --- Generate Sample Data ---
    QList<FileRecord> recordList;
    QRandomGenerator *rng = QRandomGenerator::global();

    // Add records to test the custom sorting
    recordList.append({"Doc 1.txt", QDateTime(QDate(2024, 1, 1), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"Report 10.pdf", QDateTime(QDate(2024, 1, 2), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"Doc 2.txt", QDateTime(QDate(2024, 1, 3), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"Image 5.png", QDateTime(QDate(2024, 1, 4), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"Doc 10.txt", QDateTime(QDate(2024, 1, 5), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"Report 2.pdf", QDateTime(QDate(2024, 1, 6), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"Doc 3.txt", QDateTime(QDate(2024, 1, 7), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"Backup.zip", QDateTime(QDate(2024, 1, 8), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(1000000, 100000001)}); // Larger size
    recordList.append({"Image 1.png", QDateTime(QDate(2024, 1, 9), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"Report 1.pdf", QDateTime(QDate(2024, 1, 10), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"Doc.txt", QDateTime(QDate(2024, 1, 11), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)}); // File without number
    recordList.append({"another.txt", QDateTime(QDate(2024, 1, 12), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"test 9.zip", QDateTime(QDate(2024, 1, 13), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});
    recordList.append({"test 11.zip", QDateTime(QDate(2024, 1, 14), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001)});


    // Update the model with the generated data
    fileModel->updateData(recordList);

    // Adjust window size
    resize(700, 400);
}

MainWindow::~MainWindow()
{
    // Widgets, models, and delegates parented to 'this' will be automatically deleted.
}

// Slot to show a tooltip
void MainWindow::showToolTip(const QModelIndex &index)
{
    if (!index.isValid()) {
         QToolTip::hideText(); // Hide tooltip if mouse leaves items
        return;
    }

    int nColumn = index.column();
    // Show tooltip for the size column
    if (nColumn == FILE_SIZE_COLUMN) {
        // When using the delegate approach, index.data() for any role (including DisplayRole)
        // will give the raw qint64. Convert it to string for the tooltip.
        QToolTip::showText(QCursor::pos(), QString("%1 Bytes").arg(index.data(Qt::DisplayRole).toLongLong()));
    } else {
         QToolTip::hideText(); // Hide tooltip for other columns
    }
}