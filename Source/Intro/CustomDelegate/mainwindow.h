#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>     // 继承自 QWidget
#include <QTableView> // 需要 QTableView
#include <QVBoxLayout> // 需要布局

#include "TableModel.h"       // 包含自定义模型头文件
#include "CheckBoxDelegate.h" // 包含自定义委托头文件

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
};

#endif // MAINWINDOW_H