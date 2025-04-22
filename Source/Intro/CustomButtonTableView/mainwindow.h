#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QSortFilterProxyModel> // 使用代理模型以便演示 mapToSource

#include "TableModel.h" // 模型
#include "TableViewDelegate.h" // 自定义按钮委托

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    private slots:
        // 委托发射信号后由主窗口接收并处理的槽函数
    void handleOpenButtonClicked(const QModelIndex &index);
    void handleDeleteButtonClicked(const QModelIndex &index);
    void onTableViewClicked(const QModelIndex &index);


private:
    QTableView *tableView;
    TableModel *fileModel;
    QSortFilterProxyModel *proxyModel; // 添加代理模型
    TableViewDelegate *buttonDelegate; // 自定义按钮委托
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H