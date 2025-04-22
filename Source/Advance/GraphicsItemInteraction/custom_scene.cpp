// custom_scene.cpp
#include "custom_scene.h"
#include "custom_item.h" // To create CustomItem instances
#include <QDebug> // For qDebug()
#include <QGraphicsView> // Accessing views from scene (less common)
#include <QList> // For selectedItems()

// Implementation of CustomScene
CustomScene::CustomScene(QObject *parent)
    : QGraphicsScene(parent) // Inherit constructor
{
    // Scene specific setup if any
}

// Handle mouse button press events on the scene
void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Custom scene mousePressEvent at scene pos:" << event->scenePos();
    // First, let the base class handle the event. This is crucial!
    // The base class will attempt to deliver the event to any items under the cursor.
    // If an item accepts the event (e.g., for selection, movement, or its own custom handling),
    // the event's accepted() status will become true, and it won't propagate further up to our custom handling below.
    QGraphicsScene::mousePressEvent(event);

    // Check if the event was *not* accepted by any item under the cursor
    if (!event->isAccepted()) {
        qDebug() << "Event not accepted by item. Custom scene handling.";
        // Perform custom scene handling if no item handled the click
        if (event->button() == Qt::LeftButton) {
            qDebug() << "Adding item at scene pos:" << event->scenePos();
            // Add a new custom item centered around the click position
            QPointF point = event->scenePos();
            CustomItem *item = new CustomItem();
            // Set the item's internal rectangle. Let's make the item's local (0,0) its center.
            // setRect(-width/2, -height/2, width, height) makes (0,0) the center.
            // setPos then places the item's local (0,0) at the click point.
            qreal defaultItemSize = 60.0; // Define a size
            item->setRect(-defaultItemSize/2.0, -defaultItemSize/2.0, defaultItemSize, defaultItemSize);
            // Position the item's local center (0,0) at the scene click position
            item->setPos(point);
            addItem(item);

             // Deselect all other items when adding a new one with left click
             // (This is a common behavior, you can adjust based on requirements)
             // Iterate over items(event->scenePos()) to potentially select the newly created one,
             // or simply clear selection explicitly. Clearing selection is safer.
            foreach (QGraphicsItem *selectedItem, selectedItems()) {
                selectedItem->setSelected(false);
            }
             // The newly added item is not automatically selected. You could select it here if desired:
             // item->setSelected(true);

        } else if (event->button() == Qt::RightButton) {
            qDebug() << "Right click on scene background. Checking for item removal.";
            // Right click on scene background to remove the top-most item under the cursor
            // items(event->scenePos()) returns a list of items under the point, ordered from top to bottom
            QList<QGraphicsItem *> itemsUnderCursor = items(event->scenePos());

            // Find the first CustomItem (UserType + 1) in the list
            QGraphicsItem *itemToRemove = nullptr;
            foreach (QGraphicsItem *item, itemsUnderCursor) {
                 // Use qgraphicsitem_cast for safe type checking
                if (item->type() == CustomItem::Type) { // Use the defined enum value
                    itemToRemove = item;
                    break; // Found the top-most CustomItem, stop searching
                }
            }

            // If a CustomItem was found, remove it
            if (itemToRemove) {
                qDebug() << "Removing item at scene pos:" << event->scenePos();
                removeItem(itemToRemove);
                delete itemToRemove; // You are responsible for deleting items removed from the scene
            }
             // Do NOT accept the event here if you removed an item. This ensures the base
             // mousePressEvent (called earlier) could potentially handle clicks *over* items
             // that chose not to accept the event themselves.
             // If you DO accept here, clicks on items that ignored the event won't be propagated further up the chain.
             // Let's accept if we added an item (LeftButton case). For RightButton removal, it's often
             // better to leave it unaccepted unless you don't want context menus etc.
        }
    }
}

// Handle mouse move events on the scene
void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // This event handler is called for mouse moves only if no item is currently
    // "grabbing" the mouse (e.g., no item's mousePressEvent accepted the event
    // and started dragging).
    // If an item's mousePressEvent accepted the event, mouse move events will go
    // directly to that item's mouseMoveEvent until mouseReleaseEvent.

    // qDebug() << "Custom scene mouseMoveEvent."; // Can be very chatty
    // Let the base class handle any default scene mouse move behavior (which is minimal)
    QGraphicsScene::mouseMoveEvent(event);

    // Custom handling if needed, but usually not much here.
}

// Handle key press events
void CustomScene::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Custom scene keyPressEvent - Key:" << event->key();
    // Check if the Backspace key was pressed
    if (event->key() == Qt::Key_Backspace) {
        // Remove all currently selected items
        qDebug() << "Backspace pressed. Selected items count:" << selectedItems().size();
        // selectedItems() returns a QList of selected items.
        // Iterate and remove/delete. Removing from a list while iterating is tricky,
        // so iterate on a copy or remove from the end. Clearing the list is simpler.
        QList<QGraphicsItem *> itemsToRemove = selectedItems(); // Get a copy of the list
        foreach (QGraphicsItem *item, itemsToRemove) {
            qDebug() << "Removing selected item.";
            removeItem(item); // Remove from scene
            delete item;     // Delete the item object
        }
        // Accept the event so it doesn't propagate further (e.g., to a parent widget)
        event->accept();
    } else {
        // For other keys, let the base class handle them (e.g., focus navigation)
        QGraphicsScene::keyPressEvent(event);
    }
}