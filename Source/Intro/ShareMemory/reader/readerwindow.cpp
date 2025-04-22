#include "readerwindow.h"
#include "../shared_defs.h" // 包含共享定义文件
#include <QBuffer>
#include <QDataStream>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>

ReaderWindow::ReaderWindow(QWidget *parent)
    : QWidget(parent),
      sharedMemory(SHARED_MEMORY_KEY) // 使用共享的键初始化 QSharedMemory
{
    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 创建按钮
    loadButton = new QPushButton("Load Image From Shared Memory", this);
    layout->addWidget(loadButton);

    // 创建标签用于显示图片
    imageLabel = new QLabel("Image will appear here...", this);
    imageLabel->setAlignment(Qt::AlignCenter); // 图片居中显示
    imageLabel->setMinimumSize(200, 150); // 设置最小尺寸，防止布局崩溃
    imageLabel->setScaledContents(true); // 允许图片缩放到标签大小
    layout->addWidget(imageLabel);

    // 设置窗口布局
    setLayout(layout);

    // 连接按钮的点击信号到槽函数
    connect(loadButton, &QPushButton::clicked, this, &ReaderWindow::loadFromMemory);

    // 启动时尝试自动加载一次 (可选)
    // QTimer::singleShot(0, this, &ReaderWindow::loadFromMemory);
}

ReaderWindow::~ReaderWindow()
{
    // 析构时 QSharedMemory 会自动 detach
}

// 槽函数：从共享内存读取数据并显示
void ReaderWindow::loadFromMemory()
{
    // 将共享内存与该进程绑定 (如果尚未绑定)
    if (!sharedMemory.attach(QSharedMemory::ReadOnly)) // 以只读模式附加
    {
        // 如果绑定失败，通常是因为写入者还没有创建共享内存段
        qDebug() << "Reader: Unable to attach to shared memory segment:" << sharedMemory.errorString();
        imageLabel->setText("Waiting for image data in shared memory...");
        // 可以考虑使用定时器重试 attach
        return;
    }
    qDebug() << "Reader: Successfully attached to shared memory with size" << sharedMemory.size();


    // 从共享内存中读取数据到缓冲区
    QBuffer buffer; // 使用 QBuffer 作为内存中的文件
    QDataStream in(&buffer); // 创建 QDataStream，关联到 buffer
    QImage image;           // 用于存储读取到的图片

    // 锁定共享内存段，确保数据一致性
    sharedMemory.lock();

    // 将共享内存的数据设置到 QBuffer 中
    // constData() 返回 const void* 或 const char*，setData 接受 const char*
    buffer.setData((const char*)sharedMemory.constData(), sharedMemory.size());
    buffer.open(QBuffer::ReadOnly); // 以只读模式打开缓冲区

    // 从 QDataStream 读取 QImage 对象 (反序列化)
    in >> image;

    // 解锁共享内存段
    sharedMemory.unlock();

    // 将共享内存与该进程分离
    // 注意：QSharedMemory::detach() 不会删除共享内存段本身，除非该进程是最后一个 attached 的进程，
    // 并且共享内存段是以 QSharedMemory::AutoRemove 设置创建的 (这是默认行为)。
    sharedMemory.detach();
     qDebug() << "Reader: Successfully detached from shared memory.";


    // 检查图片是否有效
    if (image.isNull()) {
        qDebug() << "Reader: Failed to load image from shared memory (image is null).";
        imageLabel->setText("Failed to load image from memory.");
    } else {
        // 将 QImage 转换为 QPixmap 并设置到标签上显示
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->setText(""); // 清空文本
        qDebug() << "Reader: Image successfully loaded from shared memory.";
    }
}