#ifndef WRITERWINDOW_H
#define WRITERWINDOW_H

#include <QWidget>
#include <QSharedMemory>
#include <QPushButton>
#include <QVBoxLayout> // 需要布局
#include <QFileDialog> // 需要文件对话框

class WriterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WriterWindow(QWidget *parent = nullptr);
    ~WriterWindow();

    private slots:
        void loadFromFile(); // 选择文件并写入共享内存

private:
    QSharedMemory sharedMemory; // 共享内存对象
    QPushButton *loadButton;   // 加载并写入按钮
};

#endif // WRITERWINDOW_H