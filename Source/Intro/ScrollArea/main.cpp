//
// Created by sammiler on 2025/4/17.
//
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QPalette>
#include <QFile>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget mainWidget;
    mainWidget.setWindowTitle("QScrollArea 全功能示例");

    // 创建 QLabel 用于显示图片
    QLabel *imageLabel = new QLabel;
    QPixmap pixmap(":/Images/head");  // 图片来自资源文件
    if (pixmap.isNull()) {
        qDebug() << "图片加载失败，请检查资源路径是否正确";
        return -1;
    }

    pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio);  // 缩放图片
    imageLabel->setPixmap(pixmap);
    imageLabel->setStyleSheet("background: red;");  // 设置背景颜色
    imageLabel->setAlignment(Qt::AlignCenter);

    // 创建 QScrollArea 并设置
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);    // 设置背景角色颜色
    scrollArea->setWidget(imageLabel);                // 设置内容部件
    scrollArea->setAlignment(Qt::AlignCenter);        // 内容居中对齐
    scrollArea->setWidgetResizable(false);             // 非自动调整内容大小

    // 添加按钮操作
    QPushButton *resizeBtn = new QPushButton("手动调整大小");
    QPushButton *removeBtn = new QPushButton("移除图片");
    QPushButton *getInfoBtn = new QPushButton("获取图片信息");

    // 按钮功能实现
    QObject::connect(resizeBtn, &QPushButton::clicked, [&]() {
        if (scrollArea->widget()) {
            scrollArea->widget()->resize(260, 260);
            qDebug() << "已手动 resize 部件为 260x260";
        }
    });

    QObject::connect(removeBtn, &QPushButton::clicked, [&]() {
        QWidget *widget = scrollArea->takeWidget();
        QLabel *label = qobject_cast<QLabel *>(widget);
        if (label) {
            label->hide();  // 可以选择删除 delete label;
            qDebug() << "已移除 QLabel 图片";
        }
    });

    QObject::connect(getInfoBtn, &QPushButton::clicked, [&]() {
        QWidget *widget = scrollArea->widget();
        QLabel *label = qobject_cast<QLabel *>(widget);
        qDebug() << "scrollArea的大小" << scrollArea->size();
        if (label) {
            QSize size = label->size();
            qDebug() << "图片 QLabel 大小为：" << size;
        } else {
            qDebug() << "QScrollArea 当前没有 QLabel 部件";
        }
    });

    // 布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(scrollArea);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(resizeBtn);
    buttonLayout->addWidget(removeBtn);
    buttonLayout->addWidget(getInfoBtn);
    mainLayout->addLayout(buttonLayout);

    mainWidget.setLayout(mainLayout);
    mainWidget.resize(50, 100);
    mainWidget.show();

    return app.exec();
}
