#include "MainWindow.h"
#include "PathWidget.h"
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
    ellipseButton = new QPushButton("Ellipse", this);
    polygonButton = new QPushButton("Polygon", this);
    rectButton = new QPushButton("Rectangle", this);
    textButton = new QPushButton("Text", this);
    arcButton = new QPushButton("Arc", this);
    bezierButton = new QPushButton("Bezier Curve", this);

    buttonLayout->addWidget(ellipseButton);
    buttonLayout->addWidget(polygonButton);
    buttonLayout->addWidget(rectButton);
    buttonLayout->addWidget(textButton);
    buttonLayout->addWidget(arcButton);
    buttonLayout->addWidget(bezierButton);
    buttonLayout->addStretch();

    // 创建 QStackedWidget
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(new EllipseWidget(this));
    stackedWidget->addWidget(new PolygonWidget(this));
    stackedWidget->addWidget(new RectWidget(this));
    stackedWidget->addWidget(new TextWidget(this));
    stackedWidget->addWidget(new ArcWidget(this));
    stackedWidget->addWidget(new BezierWidget(this));

    // 添加到主布局
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(stackedWidget);

    // 连接按钮信号
    connect(ellipseButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(0); });
    connect(polygonButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(1); });
    connect(rectButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(2); });
    connect(textButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(3); });
    connect(arcButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(4); });
    connect(bezierButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(5); });
}