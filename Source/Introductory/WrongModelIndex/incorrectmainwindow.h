#ifndef INCORRECTMAINWINDOW_H
#define INCORRECTMAINWINDOW_H

#include <QWidget>

#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QToolTip>

#include "tablemodel.h"
#include "SortFilterProxyModel.h"
#include "SortDelegate.h"
#include "correctmainwindow.h" // Include CorrectMainWindow header to access shared data

class IncorrectMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit IncorrectMainWindow(QWidget *parent = nullptr);
    ~IncorrectMainWindow() override;

    private slots:
        // Slot to handle clicks on the table view (DOES NOT use mapToSource)
        void onTableViewClicked(const QModelIndex &index);

private:
    QTableView *tableView;
    TableModel *fileModel;
    SortFilterProxyModel *proxyModel;
    SortDelegate *sizeDelegate;
    QVBoxLayout *mainLayout;
};

#endif // INCORRECTMAINWINDOW_H