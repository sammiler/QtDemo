#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>

#include "TableModel.h" // 包含模型头文件
#include "HtmlDelegate.h" // 包含委托头文件

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
public slots:
    void adjustRowHeights() const;

private:
    QTableView *tableView;
    TableModel *fileModel;
    HtmlDelegate *htmlDelegate; // 自定义 HTML 委托
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H