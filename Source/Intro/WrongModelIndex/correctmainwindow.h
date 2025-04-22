#ifndef CORRECTMAINWINDOW_H
#define CORRECTMAINWINDOW_H

#include <QWidget>

#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QToolTip>

#include "tablemodel.h"
#include "SortFilterProxyModel.h"
#include "SortDelegate.h"

class CorrectMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CorrectMainWindow(QWidget *parent = nullptr);
    ~CorrectMainWindow() override;

    private slots:
        // Slot to handle clicks on the table view (uses mapToSource)
        void onTableViewClicked(const QModelIndex &index);
public:
    // Need access to the data list to initialize both windows with the same data
    static QList<FileRecord> sharedRecordList;
private:
    QTableView *tableView;
    TableModel *fileModel;
    SortFilterProxyModel *proxyModel;
    SortDelegate *sizeDelegate;
    QVBoxLayout *mainLayout;


    static bool dataInitialized; // Flag to initialize data only once

    void initializeData(); // Method to generate sample data
};

#endif // CORRECTMAINWINDOW_H