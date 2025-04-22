#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget> // Using QWidget for a simple window

#include <QTableView>
#include <QSortFilterProxyModel>
#include <QVBoxLayout> // Layout to manage widgets

#include "TableModel.h" // Include our custom model header

class MainWindow : public QWidget // Inherit from QWidget
{
    Q_OBJECT // Required for meta-object features

public:
    // Constructor
    explicit MainWindow(QWidget *parent = nullptr);

    // Destructor
    ~MainWindow() override;

private:
    // Widgets and models
    QTableView *tableView;
    TableModel *fileModel;
    QSortFilterProxyModel *proxyModel;
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H