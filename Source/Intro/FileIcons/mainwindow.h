#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>     // 继承自 QWidget
#include <QListWidget> // 需要 QListWidget
#include <QVBoxLayout> // 需要布局
#include <QIcon>       // 需要 QIcon
#include <QString>     // 需要 QString, QStringList

// 需要的类的前向声明或包含
#include <QFileIconProvider> // 需要 QFileIconProvider
#include <QFileInfo>         // 需要 QFileInfo
#include <QTemporaryFile>    // 需要 QTemporaryFile
#include <QDir>              // 需要 QDir
#include <QCoreApplication>  // 需要 QCoreApplication
#include <QDebug>            // 需要 qDebug
#include <QListView>         // 需要 QListView (用于设置视图模式等枚举值)

class MainWindow : public QWidget
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit MainWindow(QWidget *parent = nullptr); // 使用 nullptr
    ~MainWindow();

private:
    // 根据扩展名获取对应的文件图标
    QIcon getFileIcon(const QString &extension) const;

    // 根据扩展名获取对应的文件类型描述
    QString getFileType(const QString &extension) const;

private:
    QListWidget *m_listWidget; // 显示图标和类型的列表控件
};

#endif // MAINWINDOW_H