#include "MainWindow.h"
#include "TextWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
}

void MainWindow::setupUI() {
    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 创建导航按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    basicButton = new QPushButton("Basic Text", this);
    alignButton = new QPushButton("Aligned Text", this);
    wrapButton = new QPushButton("Wrapped Text", this);
    elideButton = new QPushButton("Elided Text", this);
    fontButton = new QPushButton("Styled Text", this);

    buttonLayout->addWidget(basicButton);
    buttonLayout->addWidget(alignButton);
    buttonLayout->addWidget(wrapButton);
    buttonLayout->addWidget(elideButton);
    buttonLayout->addWidget(fontButton);
    buttonLayout->addStretch();

    // 创建 QStackedWidget
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(new BasicTextWidget(this));
    stackedWidget->addWidget(new AlignedTextWidget(this));
    stackedWidget->addWidget(new WrappedTextWidget(this));
    stackedWidget->addWidget(new ElidedTextWidget(this));
    stackedWidget->addWidget(new StyledTextWidget(this));

    // 添加到主布局
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(stackedWidget);

    // 连接按钮信号
    connect(basicButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(0); });
    connect(alignButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(1); });
    connect(wrapButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(2); });
    connect(elideButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(3); });
    connect(fontButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(4); });
}