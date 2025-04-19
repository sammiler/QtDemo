#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>

#include "TableModel.h" // 模型
#include "ProgressBarDelegate.h" // 进度条委托
#include "FileDownloadThread.h" // 线程

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QTableView *tableView;
    TableModel *fileModel;
    ProgressBarDelegate *progressBarDelegate; // 进度条委托
    FileDownloadThread *downloadThread; // 后台线程
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H