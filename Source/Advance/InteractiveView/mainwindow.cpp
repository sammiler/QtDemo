// mainwindow.cpp
#include "mainwindow.h"
#include "interactive_view.h" // Include the custom view header
#include <QGraphicsScene>
#include <QGraphicsEllipseItem> // Add some simple items
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QFont>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Interactive View Demo")); // Use QStringLiteral
    resize(800, 600);

    scene = new QGraphicsScene(this); // Scene needs a parent
    // No need to set sceneRect explicitly here if view set it to INT_MIN/MAX
    view = new InteractiveView(this); // Create the custom interactive view
    view->setScene(scene); // Set the scene on the custom view
    setCentralWidget(view); // Set the custom view as the central widget

    // --- Add some items to the scene to test interaction ---
    // Items will be positioned in the scene's coordinate system.
    // Since the view centers on scene (0,0) by default, place items around there.

    // Ellipse item
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(-50, -50, 100, 100); // Local rect centered at (0,0)
    ellipse->setPos(0, 0); // Item's local (0,0) is at scene (0,0)
    ellipse->setBrush(Qt::blue);
    ellipse->setPen(QPen(Qt::black, 2));
    scene->addItem(ellipse);

    // Rectangle item
    QGraphicsRectItem *rect = new QGraphicsRectItem(0, 0, 100, 50); // Local rect starts at (0,0)
    rect->setPos(150, 50); // Item's local (0,0) is at scene (150, 50)
    rect->setBrush(Qt::green);
    rect->setPen(QPen(Qt::darkGreen, 3));
    scene->addItem(rect);

    // Text item
    QGraphicsTextItem *text = new QGraphicsTextItem(QStringLiteral("Hello Interactive World!"));
    text->setPos(-100, -100);
    text->setDefaultTextColor(Qt::red);
    text->setFont(QFont("Arial", 20));
    scene->addItem(text);

    // Larger rectangle to test view bounds
    QGraphicsRectItem *largeRect = new QGraphicsRectItem(-2000, -2000, 4000, 4000);
    largeRect->setBrush(QColor(240, 240, 240)); // Light gray background
    largeRect->setPen(Qt::NoPen);
    largeRect->setZValue(-1); // Draw behind other items
    scene->addItem(largeRect);
    // The sceneRect is already set to INT_MIN/MAX in InteractiveView, so this large item
    // helps visualize the large scene area, though not strictly necessary if items are sparse.

    // The InteractiveView is set as the central widget and already calls centerOn(0,0)
    // and sets its own sceneRect in its constructor.
    // We don't need to call view->setSceneRect() or view->centerOn() here again.
}

MainWindow::~MainWindow()
{
    // Qt's parent-child mechanism handles deleting scene, view, and items
}