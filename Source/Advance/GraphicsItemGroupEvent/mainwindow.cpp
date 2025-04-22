// mainwindow.cpp
#include "mainwindow.h"
#include "custom_item.h"   // Include custom item header
#include "custom_group.h"  // Include custom group header
#include <QGraphicsEllipseItem> // Base class for CustomItem
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug> // For debug output
#include <QPainter> // For Antialiasing

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Graphics Group Event Handling Demo"));
    resize(800, 600);

    scene = new QGraphicsScene(this); // Scene needs a parent
    view = new QGraphicsView(scene, this); // View needs scene and parent
    setCentralWidget(view);

    // --- Create Custom Items ---
    // Create items. Give them parent=0 for now.
    CustomItem *item1 = new CustomItem(nullptr);
    item1->setRect(-40, -40, 80, 80); // Centered at its local (0,0)
    item1->setPos(100, 100); // Position in scene initially (before grouping)
    item1->setBrush(Qt::red); // Give distinct colors
    item1->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true); // Useful for tracking pos changes
    item1->setFlag(QGraphicsItem::ItemIsMovable, true); // Make it movable

    CustomItem *item2 = new CustomItem(nullptr);
    item2->setRect(-40, -40, 80, 80);
    item2->setPos(250, 100);
    item2->setBrush(Qt::green);
    item2->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    item2->setFlag(QGraphicsItem::ItemIsMovable, true);


    // --- Create Custom Group ---
    CustomGroup *myGroup = new CustomGroup(); // Create the custom group item

    // --- Add Items to the Group ---
    // Using addToGroup sets the group as the item's parent.
    // The item's setPos() will now be interpreted relative to the group's local coordinate system.
    myGroup->addToGroup(item1);
    myGroup->addToGroup(item2);

    // At this point, item1's pos (100,100) and item2's pos (250,100) are now relative
    // to myGroup's local (0,0). If myGroup's scene pos is (0,0), item1 will be at
    // scene (100,100) and item2 at scene (250,100).

    // --- Add the Group to the Scene ---
    scene->addItem(myGroup);
    // You can set the group's position in the scene if you want the whole group to be moved
    // myGroup->setPos(50, 50); // This would move the entire group and its content


    // --- Configure Group Event Handling (Method 1) ---
    // By default, QGraphicsItemGroup::setHandlesChildEvents(true) is called in its constructor.
    // To allow children (CustomItem) to receive events *first*, set this to false.
    // If set to true (default for QGraphicsItemGroup), mouse/key events that would go to a child
    // are instead sent directly to the group's sceneEvent, skipping the child's handlers.
    // myGroup->setHandlesChildEvents(false); // <--- UNCOMMENT THIS LINE to let children handle events first

    // When setHandlesChildEvents(false), events first try to go to the child item.
    // If the child item accepts the event (e.g., in mousePressEvent by calling event->accept()),
    // the event stops there and does not reach the group's event handlers.
    // If the child item ignores the event or doesn't accept it, the event may propagate up
    // to the parent item (the group) and then to the scene.

    // --- Final Scene/View Setup ---
    // Set scene rect to encompass content (optional but good)
    scene->setSceneRect(scene->itemsBoundingRect().normalized().adjusted(-20, -20, 20, 20));

    // Set render hint for smoother graphics
    view->setRenderHint(QPainter::Antialiasing);

    // Set initial focus to the first item so key events go there if handlesChildEvents(false)
    item1->setFocus();
}

MainWindow::~MainWindow()
{
    // Qt's parent-child mechanism handles deleting scene, view, group, and items
}