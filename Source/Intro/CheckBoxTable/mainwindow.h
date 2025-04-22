#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>     // 继承自 QWidget
#include <QTableView> // 需要 QTableView
#include <QVBoxLayout> // 需要布局

// 包含自定义组件的头文件
#include "TableModel.h"
#include "CheckBoxDelegate.h"
#include "TableHeaderView.h"

class MainWindow : public QWidget
{
    Q_OBJECT // 需要 Q_OBJECT 宏，因为是顶级窗口

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTableView *m_tableView;     // 表格视图
    TableModel *m_tableModel;    // 自定义表格模型
    CheckBoxDelegate *m_checkBoxDelegate; // 自定义复选框委托
    TableHeaderView *m_tableHeaderView; // 自定义表头视图
};

#endif // MAINWINDOW_H