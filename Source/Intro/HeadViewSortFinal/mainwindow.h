#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView> // For header settings
#include <QToolTip> // For tooltip example

#include "TableModel.h"
#include "SortFilterProxyModel.h" // Our custom proxy model
#include "SortDelegate.h" // Our custom delegate

class MainWindow : public QWidget
{
    Q_OBJECT // Required for signals/slots

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    private slots:
        // Slot to show a tooltip when mouse enters an item
        void showToolTip(const QModelIndex &index);


private:
    QTableView *tableView;
    TableModel *fileModel;
    SortFilterProxyModel *proxyModel; // Our custom proxy model
    SortDelegate *sizeDelegate; // Our custom delegate for size column
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H