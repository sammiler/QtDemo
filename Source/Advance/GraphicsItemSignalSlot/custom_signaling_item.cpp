// custom_signaling_item.cpp
#include "custom_signaling_item.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent> // Include if overriding mouse events

// Implementation of CustomSignalingItem
CustomSignalingItem::CustomSignalingItem(QGraphicsItem *parent)
    // Call constructors of BOTH base classes.
    // QObject constructor takes parent QObject. QGraphicsRectItem takes parent QGraphicsItem.
    // Since a QGraphicsItem is NOT a QObject, you cannot pass the QGraphicsRectItem parent to QObject.
    // Pass 'this' to the QObject parent constructor, or nullptr if it shouldn't be part of a QObject tree.
    // Pass the QGraphicsItem parent to QGraphicsRectItem constructor.
    : QObject(nullptr), // This item is a top-level QObject (not part of another QObject's ownership tree)
      QGraphicsRectItem(parent) // This item IS a child of a QGraphicsItem (if parent is provided)
{
    qDebug() << "CustomSignalingItem created.";
    // You can set item flags or default properties here
    setFlag(QGraphicsItem::ItemIsSelectable); // Example: Make it selectable

    // Note: boundingRect() and paint() are inherited from QGraphicsRectItem
    // and automatically handle drawing the rectangle defined by setRect().
    // You can override them if you need custom drawing or bounds calculation.
}

// Optional: Override mousePressEvent to emit a signal on click
void CustomSignalingItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Call base class first for default behavior (like selection)
    QGraphicsRectItem::mousePressEvent(event);

    // If the left button was pressed
    if (event->button() == Qt::LeftButton) {
        qDebug() << "CustomSignalingItem clicked!";
        // Emit our custom signal
        emit itemClicked(); // Emit the signal

        // Accept the event to indicate we handled the click
        event->accept();
    } else {
        // For other buttons, let the event propagate (optional)
        event->ignore(); // Or QGraphicsRectItem::mousePressEvent(event); which might accept/ignore
    }
}

// Implementation of the custom slot
void CustomSignalingItem::mySlot()
{
    qDebug() << "CustomSignalingItem slot triggered!";
    // You could emit a signal here, or change the item's state, etc.
    // Example: Emit the signal again from the slot
    // emit itemClicked();
}

// Implementation of type() method for qgraphicsitem_cast
int CustomSignalingItem::type() const
{
    // Return the unique type ID defined in the header
    return Type;
}