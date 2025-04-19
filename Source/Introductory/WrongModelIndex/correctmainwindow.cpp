#include "correctmainwindow.h"

#include <QRandomGenerator>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QCursor>

// Initialize the static members (outside the class definition)
QList<FileRecord> CorrectMainWindow::sharedRecordList;
bool CorrectMainWindow::dataInitialized = false;


void CorrectMainWindow::initializeData()
{
    if (dataInitialized) return; // Only initialize once

    QRandomGenerator *rng = QRandomGenerator::global();

    // Generate sample data, including random checkbox states
    sharedRecordList.append({"Doc 1.txt", QDateTime(QDate(2024, 1, 1), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Report 10.pdf", QDateTime(QDate(2024, 1, 2), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Doc 2.txt", QDateTime(QDate(2024, 1, 3), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Image 5.png", QDateTime(QDate(2024, 1, 4), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Doc 10.txt", QDateTime(QDate(2024, 1, 5), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Report 2.pdf", QDateTime(QDate(2024, 1, 6), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Doc 3.txt", QDateTime(QDate(2024, 1, 7), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Backup.zip", QDateTime(QDate(2024, 1, 8), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(1000000, 100000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Image 1.png", QDateTime(QDate(2024, 1, 9), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Report 1.pdf", QDateTime(QDate(2024, 1, 10), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"Doc.txt", QDateTime(QDate(2024, 1, 11), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"another.txt", QDateTime(QDate(2024, 1, 12), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"test 9.zip", QDateTime(QDate(2024, 1, 13), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});
    sharedRecordList.append({"test 11.zip", QDateTime(QDate(2024, 1, 14), QTime(rng->bounded(0,24), rng->bounded(0,60), rng->bounded(0,60))), rng->bounded(100, 1000001), rng->generate() % 2 == 0});

    dataInitialized = true;
}


CorrectMainWindow::CorrectMainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Correct Window (using mapToSource)");

    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    tableView = new QTableView(this);

    fileModel = new TableModel(this); // This instance of TableModel manages the data
    initializeData(); // Generate data if not already done
    fileModel->updateData(sharedRecordList); // Provide the shared data to the model

    proxyModel = new SortFilterProxyModel(this);
    proxyModel->setSourceModel(fileModel);

    tableView->setModel(proxyModel);

    sizeDelegate = new SortDelegate(this);
    tableView->setItemDelegateForColumn(FILE_SIZE_COLUMN, sizeDelegate);

    tableView->setSortingEnabled(true);
    tableView->horizontalHeader()->setSectionResizeMode(FILE_NAME_COLUMN, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(DATE_TIME_COLUMN, QHeaderView::Interactive);
    tableView->horizontalHeader()->setSectionResizeMode(FILE_SIZE_COLUMN, QHeaderView::Interactive);
    tableView->horizontalHeader()->setSectionResizeMode(CHECK_BOX_COLUMN, QHeaderView::ResizeToContents); // Checkbox column fits content

    tableView->sortByColumn(FILE_NAME_COLUMN, Qt::AscendingOrder); // Initial sort

    mainLayout->addWidget(tableView);

    // Connect the clicked signal to our slot
    connect(tableView, &QTableView::clicked, this, &CorrectMainWindow::onTableViewClicked);

    resize(750, 450);
}

CorrectMainWindow::~CorrectMainWindow()
{
    // Widgets/models parented to 'this' are cleaned up automatically.
}

// Correct implementation of click handling using mapToSource
void CorrectMainWindow::onTableViewClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    // We only care about clicks on the checkbox column
    if (index.column() == CHECK_BOX_COLUMN)
    {
        // *** CORRECT LOGIC: Map the proxy index to the source index ***
        QModelIndex sourceIndex = proxyModel->mapToSource(index);

        // Now use the row from the source index to get the correct data/set data
        // The column should still be CHECK_BOX_COLUMN in the source model
        QModelIndex checkIndexInSource = fileModel->index(sourceIndex.row(), CHECK_BOX_COLUMN);

        // Get the current state using CheckStateRole from the source model
        bool bChecked = (fileModel->data(checkIndexInSource, Qt::CheckStateRole).toInt() == Qt::Checked);

        // Toggle the state using setData on the source model
        // The value passed to setData for CheckStateRole should be Qt::Checked or Qt::Unchecked
        fileModel->setData(checkIndexInSource, !bChecked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);

        // Note: If the column's flags include Qt::ItemIsUserCheckable, clicking
        // usually automatically toggles the state and calls setData with Qt::CheckStateRole.
        // Explicitly calling setData here is redundant if the flag is set,
        // but serves to clearly show how you *would* modify the source data
        // after getting the correct source index. For demonstration, let's keep it explicit.
        // In a real app, you might just rely on the flag for simple toggling.
    }
}