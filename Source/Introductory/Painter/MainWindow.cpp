#include "MainWindow.h"
#include "PaintWidget.h"
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
    textButton = new QPushButton("Text", this);
    lineButton = new QPushButton("Line", this);
    rectButton = new QPushButton("Rectangle", this);
    arcButton = new QPushButton("Arc", this);
    ellipseButton = new QPushButton("Ellipse", this);
    polygonButton = new QPushButton("Polygon", this);
    imageButton = new QPushButton("Image", this);

    buttonLayout->addWidget(textButton);
    buttonLayout->addWidget(lineButton);
    buttonLayout->addWidget(rectButton);
    buttonLayout->addWidget(arcButton);
    buttonLayout->addWidget(ellipseButton);
    buttonLayout->addWidget(polygonButton);
    buttonLayout->addWidget(imageButton);
    buttonLayout->addStretch();

    // 创建 QStackedWidget
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(new TextWidget(this));
    stackedWidget->addWidget(new LineWidget(this));
    stackedWidget->addWidget(new RectWidget(this));
    stackedWidget->addWidget(new ArcWidget(this));
    stackedWidget->addWidget(new EllipseWidget(this));
    stackedWidget->addWidget(new PolygonWidget(this));
    stackedWidget->addWidget(new ImageWidget(this));

    // 添加到主布局
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(stackedWidget);

    // 连接按钮信号
    connect(textButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(0); });
    connect(lineButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(1); });
    connect(rectButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(2); });
    connect(arcButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(3); });
    connect(ellipseButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(4); });
    connect(polygonButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(5); });
    connect(imageButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(6); });
}