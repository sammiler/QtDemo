#include "MainWindow.h"
#include "GradientWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 创建导航按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    linearButton = new QPushButton("Linear Gradient", this);
    radialButton = new QPushButton("Radial Gradient", this);
    conicalButton = new QPushButton("Conical Gradient", this);

    buttonLayout->addWidget(linearButton);
    buttonLayout->addWidget(radialButton);
    buttonLayout->addWidget(conicalButton);
    buttonLayout->addStretch();

    // 创建 QStackedWidget
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(new LinearGradientWidget(this));
    stackedWidget->addWidget(new RadialGradientWidget(this));
    stackedWidget->addWidget(new ConicalGradientWidget(this));

    // 添加到主布局
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(stackedWidget);

    // 连接按钮信号
    connect(linearButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(0); });
    connect(radialButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(1); });
    connect(conicalButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(2); });
}