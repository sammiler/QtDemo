// mainwindow.cpp
#include "mainwindow.h"
#include "custom_signaling_item.h" // Include our custom item header
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>         // For item styling
#include <QColor>         // For colors
#include <QDebug>         // For qDebug() output
#include <QPushButton>    // Add a button to trigger a slot
#include <QVBoxLayout>    // For layout

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Graphics Item Signal Slot Demo (Multi-Inheritance)")); // Use QStringLiteral
    resize(600, 400);

    scene = new QGraphicsScene(this); // Scene needs a parent
    view = new QGraphicsView(scene, this); // View needs scene and parent
    // We'll use a layout to place the view and a button
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(view);

    // Add a button that will trigger a slot, which in turn emits a signal
    QPushButton *triggerButton = new QPushButton(QStringLiteral("Emit Item Signal"));
    layout->addWidget(triggerButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // --- Create our Custom Signaling Item ---
    CustomSignalingItem *myItem = new CustomSignalingItem();
    // Set its position in the scene
    myItem->setPos(100, 100);
    myItem->setRect(0, 0, 80, 80); // Give it a visible shape
    myItem->setBrush(Qt::cyan);
    scene->addItem(myItem);

    // --- Connect Signals and Slots ---
    // Connect the item's signal to a slot in MainWindow (for demonstration)
    connect(myItem, &CustomSignalingItem::itemClicked, this, [=]() {
        qDebug() << "MainWindow received itemClicked signal from CustomSignalingItem!";
        // You could change the item's color or do something else here
        myItem->setBrush(Qt::yellow); // Change color on click
    });

    // Connect the trigger button's clicked signal to the item's slot
    connect(triggerButton, &QPushButton::clicked, myItem, &CustomSignalingItem::mySlot);


    // Set scene rect to encompass content (optional but good for initial view)
    scene->setSceneRect(scene->itemsBoundingRect().normalized().adjusted(-20, -20, 20, 20));

    // Optional: Set render hints
    // view->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    // Qt's parent-child mechanism handles deleting scene, view, layout, button, and items
}