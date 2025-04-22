// custom_group.cpp
#include "custom_group.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

// Implementation of CustomGroup
CustomGroup::CustomGroup(QGraphicsItem *parent)
    : QGraphicsItemGroup(parent) // Call base constructor
{
    qDebug() << "CustomGroup created. Default handlesChildEvents =" << handlesChildEvents();
    // Note: QGraphicsItemGroup constructor defaults handlesChildEvents to true.
    // To let children handle events first (Method 1), you MUST call:
    // setHandlesChildEvents(false); // <-- Uncomment this line in mainwindow.cpp AFTER creating the group
}

// Optional: Implement group's own mousePressEvent
void CustomGroup::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "CustomGroup mousePressEvent: Button =" << event->button() << "Pos (Group) =" << event->pos() << "Pos (Scene) =" << event->scenePos();
    // Let the base class handle the event. This is where default group behavior happens (like moving the group).
    QGraphicsItemGroup::mousePressEvent(event);

    // Check if the event was *not* accepted by the base class (or any child if handlesChildEvents was false
    // and the event propagated up).
    if (!event->isAccepted()) {
         qDebug() << "Group base class did not accept the mouse press.";
        // Add custom group-level handling here if needed
        // For instance, you could select the group: setSelected(true); event->accept();
    }
    // If the base class accepted (e.g., started a drag), event->isAccepted() will be true.
    // If you handle something here, call event->accept();
}

// Optional: Implement group's own keyPressEvent
void CustomGroup::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "CustomGroup keyPressEvent: Key =" << event->key();
    // Let the base class handle default group key events (minimal usually)
    QGraphicsItemGroup::keyPressEvent(event);
    // Check if the event was not accepted by the base class.
    if (!event->isAccepted()) {
        qDebug() << "Group base class did not accept the key press.";
        // Add custom group-level handling here if needed
    }
    // If you handle something here, call event->accept();
}

// Optional: Implement group's own sceneEvent
// bool CustomGroup::sceneEvent(QEvent *event)
// {
//     qDebug() << "CustomGroup sceneEvent: Type =" << event->type();
//     // Call base class implementation.
//     return QGraphicsItemGroup::sceneEvent(event);
// }