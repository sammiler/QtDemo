#include "writerwindow.h"
#include "../shared_defs.h" // 包含共享定义文件
#include <QBuffer>
#include <QDataStream>
#include <QDebug>
#include <QImage> // 需要 QImage
#include <QFileDialog> // 需要 QFileDialog
#include <QMessageBox> // 需要 QMessageBox (可选，用于错误提示)

WriterWindow::WriterWindow(QWidget *parent)
    : QWidget(parent),
      sharedMemory(SHARED_MEMORY_KEY) // 使用共享的键初始化 QSharedMemory
{
    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 创建按钮并添加到布局
    loadButton = new QPushButton("Load Image and Write to Shared Memory", this);
    layout->addWidget(loadButton);

    // 设置窗口布局
    setLayout(layout);

    // 连接按钮的点击信号到槽函数
    connect(loadButton, &QPushButton::clicked, this, &WriterWindow::loadFromFile);
}

WriterWindow::~WriterWindow()
{
    // 析构时 QSharedMemory 会自动 detach/destroy (如果它是最后一个 attached 的)
}

void WriterWindow::loadFromFile()
{
    // 如果已经附加到共享内存段，先分离
    // 分离是一个好习惯，特别是在尝试重新创建或附加时
    if (sharedMemory.isAttached())
    {
        // 尝试分离
        if (!sharedMemory.detach()) {
             qDebug() << "Writer: Unable to detach from shared memory:" << sharedMemory.errorString();
             // 即使分离失败，也尝试继续处理
        } else {
             qDebug() << "Writer: Successfully detached from shared memory.";
        }
    }

    // 打开文件对话框选择图片文件
    QString fileName = QFileDialog::getOpenFileName(this,            // 父窗口
                                        "Select an Image File",      // 对话框标题
                                        QString(),                   // 默认目录
                                        tr("Images (*.png *.xpm *.jpg)")); // 文件过滤器

    // 如果用户没有选择文件，则返回
    if (fileName.isEmpty()) {
        qDebug() << "Writer: No file selected.";
        return;
    }

    // 创建 QImage 对象并从文件中加载图片
    QImage image;
    if (!image.load(fileName))
    {
        qDebug() << "Writer: Selected file is not a valid image or failed to load:" << fileName;
        QMessageBox::warning(this, "Error Loading Image", "Selected file is not a valid image.");
        return;
    }

    // 将图片数据序列化到缓冲区
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << image;
    int size = buffer.size();

    // --- 重要的变化在这里 ---
    // 尝试创建指定大小的共享内存段
    // 如果同名段存在且大小不匹配，create 会失败，error() 为 AlreadyExists
    // 由于 remove() 已被移除，我们不能强制删除旧段并创建新段
    if (!sharedMemory.create(size, QSharedMemory::ReadWrite)) // 创建指定大小的共享内存段，并允许读写
    {
        // 如果创建失败 (通常是因为 AlreadyExists 且大小不匹配)，打印错误信息并提示用户
        qDebug() << "Writer: Failed to create or attach to shared memory segment:" << sharedMemory.errorString();
        QMessageBox::critical(this, "Shared Memory Error",
                               QString("Failed to create or attach to shared memory segment:\n%1\n\n"
                                       "Possible reasons:\n"
                                       "- A shared memory segment with the same name already exists but has a different size.\n"
                                       "  Please ensure all other instances of the reader or writer application using this shared memory are closed.\n"
                                       "- Insufficient system resources.")
                               .arg(sharedMemory.errorString()));
        return; // 直接返回，不再尝试移除或重试
    }
    qDebug() << "Writer: Shared memory created/attached successfully with size" << sharedMemory.size();


    // 锁定共享内存段，防止其他进程在写入时读取
    sharedMemory.lock();

    // 获取共享内存段的起始地址
    char *to = (char*)sharedMemory.data(); // data() 返回 char*
    const char *from = buffer.data().data(); // buffer.data() 返回 QByteArray，再调用 data() 获取 const char*

    // 将缓冲区中的数据复制到共享内存段中
    // 使用 qMin 确保不超过共享内存段的实际分配大小 (如果成功attach到已存在的段)
    memcpy(to, from, qMin(sharedMemory.size(), size));

    // 解锁共享内存段
    sharedMemory.unlock();

    qDebug() << "Writer: Image data written to shared memory.";

    // 此时，共享内存段保持附加状态。当这个 WriterApp 进程退出，并且它是最后一个附加的进程时，
    // 如果段是以 AutoRemove 标志创建的 (QSharedMemory::create 的默认行为)，段会被自动移除。
}