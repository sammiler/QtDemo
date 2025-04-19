#ifndef READERWINDOW_H
#define READERWINDOW_H

#include <QWidget>
#include <QSharedMemory>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout> // 需要布局

class ReaderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderWindow(QWidget *parent = nullptr);
    ~ReaderWindow();

    private slots:
        void loadFromMemory(); // 从共享内存读取数据并显示

private:
    QSharedMemory sharedMemory; // 共享内存对象
    QPushButton *loadButton;   // 从内存读取按钮
    QLabel *imageLabel;        // 显示图片的标签
};

#endif // READERWINDOW_H