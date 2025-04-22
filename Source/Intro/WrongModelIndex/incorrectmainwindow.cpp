#include "incorrectmainwindow.h"

#include <QRandomGenerator>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QCursor>

IncorrectMainWindow::IncorrectMainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Incorrect Window (NOT using mapToSource)");

    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    tableView = new QTableView(this);

    fileModel = new TableModel(this);
     // Access the shared data initialized by CorrectMainWindow
    fileModel->updateData(CorrectMainWindow::sharedRecordList);


    proxyModel = new SortFilterProxyModel(this);
    proxyModel->setSourceModel(fileModel);

    tableView->setModel(proxyModel);

    sizeDelegate = new SortDelegate(this);
    tableView->setItemDelegateForColumn(FILE_SIZE_COLUMN, sizeDelegate);


    tableView->setSortingEnabled(true);
    tableView->horizontalHeader()->setSectionResizeMode(FILE_NAME_COLUMN, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(DATE_TIME_COLUMN, QHeaderView::Interactive);
    tableView->horizontalHeader()->setSectionResizeMode(FILE_SIZE_COLUMN, QHeaderView::Interactive);
    tableView->horizontalHeader()->setSectionResizeMode(CHECK_BOX_COLUMN, QHeaderView::ResizeToContents);

    tableView->sortByColumn(FILE_NAME_COLUMN, Qt::AscendingOrder);

    mainLayout->addWidget(tableView);

    // Connect the clicked signal to our slot
    connect(tableView, &QTableView::clicked, this, &IncorrectMainWindow::onTableViewClicked);


    resize(750, 450);
}

IncorrectMainWindow::~IncorrectMainWindow()
{
    // Widgets/models parented to 'this' are cleaned up automatically.
}

// Incorrect implementation of click handling - uses proxy index row directly on source model
void IncorrectMainWindow::onTableViewClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

     // We only care about clicks on the checkbox column
    if (index.column() == CHECK_BOX_COLUMN)
    {
        // *** INCORRECT LOGIC: Using the proxy row (index.row()) directly on the source model ***

        // Get the checkbox index *in the source model* using the *proxy* row. This is wrong!
        // If the table is sorted, index.row() is the row in the sorted view,
        // NOT the row in the unsorted source data.
        QModelIndex checkIndexInSource = fileModel->index(index.row(), CHECK_BOX_COLUMN); // !!! ERROR HERE !!!

        // Get the current state using CheckStateRole from the source model
        // This gets the state of the item at the *wrong* source row.
        bool bChecked = (fileModel->data(checkIndexInSource, Qt::CheckStateRole).toInt() == Qt::Checked);

        // Toggle the state using setData on the source model at the wrong row
        fileModel->setData(checkIndexInSource, !bChecked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);

         // You'll see the checkbox toggle in the view (because the model emits dataChanged
         // for the affected source index, and the proxy updates the view),
         // BUT it will be a checkbox on a DIFFERENT ROW in the original unsorted data!
         // Sort the "Correct" window to original order (or sort the "Incorrect" window)
         // to see which row *actually* got modified.
    }
}