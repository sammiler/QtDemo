#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QTableView>
#include <QVBoxLayout>

#include "TableModel.h"
// Include our custom sort filter proxy model header
#include "SortFilterProxyModel.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QTableView *tableView;
    TableModel *fileModel;
    // Use our custom proxy model class
    SortFilterProxyModel *proxyModel;
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H