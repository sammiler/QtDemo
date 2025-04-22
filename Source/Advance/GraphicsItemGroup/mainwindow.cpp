// mainwindow.cpp
#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemGroup>    // Include QGraphicsItemGroup header
#include <QGraphicsEllipseItem>  // Include headers for item types used in group
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QPen>                  // For QPen
#include <QBrush>                // For QBrush
#include <QColor>                // For QColor
#include <QRectF>                // For QRectF
#include <QLineF>                // For QLineF
#include <QPainter>              // For QPainter::Antialiasing
#include <QDebug>                // Optional for debugging

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Qt Graphics Item Group Demo")); // Use QStringLiteral
    resize(400, 300); // Adjust window size

    scene = new QGraphicsScene(this); // Scene needs a parent (MainWindow)
    view = new QGraphicsView(scene, this); // View needs a scene and a parent (MainWindow)
    setCentralWidget(view); // Set the view as the main widget

    // --- Create and configure the QGraphicsItemGroup and its children ---

    // Create group, ellipse, line, rectangle items
    // Give the group children a parent (the group itself) where appropriate for memory management,
    // OR add them to the group via addToGroup() which also sets the parent.
    QGraphicsItemGroup *pGroup = new QGraphicsItemGroup();
    // Adding to group below will set the parent, so passing 0 here is fine
    QGraphicsEllipseItem *pFrom = new QGraphicsEllipseItem(0);
    QGraphicsLineItem *pLink = new QGraphicsLineItem(0);
    QGraphicsRectItem *pTo = new QGraphicsRectItem(0);

    // Set group flags to make the whole group selectable and movable
    // Interactions (like clicking, dragging) on any child item will be handled by the group if children don't accept the event.
    pGroup->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

    // Set styles (Pen - border color, Brush - background color)
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0, 160, 230));

    pFrom->setPen(pen);
    pLink->setPen(pen);
    pTo->setPen(pen);

    pFrom->setBrush(QColor(247, 160, 57));
    pTo->setBrush(QColor(247, 160, 57));

    // Add items to the group
    // addToGroup sets the parent of the item to the group
    pGroup->addToGroup(pFrom);
    pGroup->addToGroup(pTo);
    pGroup->addToGroup(pLink);

    // Set ellipse and rectangle areas in their *local* coordinate systems.
    // Using (-length/2.0, -length/2.0, length, length) makes the item's local origin (0,0) the center of the shape.
    constexpr double length = 50;
    pFrom->setRect(QRectF(-length/2.0, -length/2.0, length, length)); // Ellipse is 50x50, centered at its local (0,0)
    pTo->setRect(QRectF(-length/2.0, -length/2.0, length, length));   // Rect is 50x50, centered at its local (0,0)

    // Set positions of ellipse, rectangle, and line in the *group's local* coordinate system.
    // Since pFrom and pTo are children of pGroup, setPos() is relative to pGroup's origin.
    pFrom->setPos(80, 80);    // Ellipse's local (0,0) is at group's (80, 80)
    pTo->setPos(200, 150);   // Rectangle's local (0,0) is at group's (200, 150)

    // Set the line in the *group's local* coordinate system.
    // pFrom->pos() and pTo->pos() return the positions of the ellipse and rectangle *relative to their parent* (the group).
    // So, QLineF(pFrom->pos(), pTo->pos()) correctly creates a line connecting the ellipse's center (pFrom's local origin)
    // and the rectangle's center (pTo's local origin) *within the group's coordinate space*.
    pLink->setLine(QLineF(pFrom->pos(), pTo->pos()));

    // Add the group to the scene.
    // Since the group is a top-level item in the scene, its setPos() (defaulting to (0,0))
    // determines where the group's local coordinate system is placed in the scene.
    // The children's positions (80,80) and (200,150) are offsets from the group's scene position.
    scene->addItem(pGroup);
    // Optional: Set the group's position in the scene if you don't want it at scene (0,0)
    // pGroup->setPos(100, 100);

    // Set the scene's rectangular area in scene coordinates.
    scene->setSceneRect(0, 0, 300, 200);

    // Set view render hint for smoother graphics.
    view->setRenderHint(QPainter::Antialiasing);

    // Optional: Fit the scene content into the view.
    // view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

MainWindow::~MainWindow()
{
    // Qt's parent-child mechanism handles deleting scene, view, and items/groups within the scene
}