// mainwindow.cpp
#include "mainwindow.h"
#include "custom_item.h"   // Include custom item header
#include <QGraphicsEllipseItem> // Base class for CustomItem
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QPainter> // For Antialiasing

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Custom Selection Highlight Demo")); // Use QStringLiteral
    resize(600, 400);

    scene = new QGraphicsScene(this); // Scene needs a parent
    view = new QGraphicsView(scene, this); // View needs scene and parent
    setCentralWidget(view);

    // --- Create Custom Items ---

    // Item 1
    CustomItem *item1 = new CustomItem(nullptr);
    // Set the item's bounding rectangle in its local coordinates
    // We'll make it 80x80 centered around local (0,0)
    item1->setRect(-40, -40, 80, 80);
    // Set the item's position in the scene (its local (0,0) will be at scene (100,100))
    item1->setPos(100, 100);
    item1->setBrush(Qt::cyan); // Fill color
    // Add to scene
    scene->addItem(item1);

    // Item 2
    CustomItem *item2 = new CustomItem(nullptr);
    item2->setRect(-50, -50, 100, 100); // A larger item
    item2->setPos(300, 150);
    item2->setBrush(Qt::magenta);
    scene->addItem(item2);

    // Item 3
     CustomItem *item3 = new CustomItem(nullptr);
     item3->setRect(-30, -30, 60, 60); // A smaller item
     item3->setPos(200, 250);
     item3->setBrush(Qt::lightGray);
     scene->addItem(item3);


    // --- Final Scene/View Setup ---
    // Set scene rect to encompass content (optional but good)
    scene->setSceneRect(scene->itemsBoundingRect().normalized().adjusted(-20, -20, 20, 20));

    // Set render hint for smoother graphics
    view->setRenderHint(QPainter::Antialiasing);

    // Enable rubber band selection in the view
    view->setDragMode(QGraphicsView::RubberBandDrag);
}

MainWindow::~MainWindow()
{
    // Qt's parent-child mechanism handles deleting scene, view, and items
}