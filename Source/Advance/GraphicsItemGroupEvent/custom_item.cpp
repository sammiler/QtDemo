// custom_item.cpp
#include "custom_item.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent> // Ensure these includes are here
#include <QKeyEvent>
#include <QEvent>
#include <QPen>

// Implementation of CustomItem
CustomItem::CustomItem(QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent) // Call base constructor
{
    QPen p = pen();
    p.setWidth(2);
    p.setColor(Qt::black); // Default border
    setPen(p);
    setBrush(Qt::blue); // Default fill (will be overridden in mainwindow)

    // Set Item flags
    setFlag(QGraphicsItem::ItemIsSelectable); // Can be selected
    setFlag(QGraphicsItem::ItemIsMovable);     // Can be moved
    setFlag(QGraphicsItem::ItemIsFocusable);   // Can receive keyboard focus

    qDebug() << "CustomItem created.";
}

// --- Standard Event Handlers Implementation ---

void CustomItem::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "CustomItem keyPressEvent: Key =" << event->key();
    // Let base class handle default key events (e.g., focus change)
    QGraphicsEllipseItem::keyPressEvent(event);
    // Accept the event if you handled it completely and want to stop propagation
    // event->accept(); // Uncomment if you fully handle a specific key
}

void CustomItem::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "CustomItem keyReleaseEvent: Key =" << event->key();
    QGraphicsEllipseItem::keyReleaseEvent(event);
}

void CustomItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "CustomItem mousePressEvent: Button =" << event->button() << "Pos (Item) =" << event->pos() << "Pos (Scene) =" << event->scenePos();
    // Let base class handle default mouse press (e.g., selection, start drag)
    QGraphicsEllipseItem::mousePressEvent(event);
    // Accept the event to stop it from propagating further up (to parent item/group or scene)
    event->accept();
}

void CustomItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
     // This is only called if mousePressEvent accepted the event and the mouse moves.
    // qDebug() << "CustomItem mouseMoveEvent: Pos (Item) =" << event->pos(); // Can be chatty
    QGraphicsEllipseItem::mouseMoveEvent(event); // Handle default drag movement
    // event->accept(); // Base class mouseMoveEvent usually accepts if moving
}

void CustomItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "CustomItem mouseReleaseEvent: Button =" << event->button();
     // This is called after a corresponding mousePressEvent on this item.
    QGraphicsEllipseItem::mouseReleaseEvent(event); // Handle default drag end/selection change
    // event->accept(); // Base class mouseReleaseEvent usually accepts if it finishes interaction
}

void CustomItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "CustomItem mouseDoubleClickEvent: Button =" << event->button();
    QGraphicsEllipseItem::mouseDoubleClickEvent(event);
    // event->accept();
}


// --- Event Interception Handler Implementation (Method 2) ---
// This method intercepts all events before they reach the specialized handlers above.
// The code from the user's example is implemented here.
// IMPORTANT: If this function returns true, the specialized handlers (mousePressEvent etc.) are *not* called.
bool CustomItem::sceneEvent(QEvent *event)
{
    // Uncommenting the switch block below demonstrates Method 2:
    // Manually dispatching events within sceneEvent.
    // If you do this, you must handle the events here and return true.
    // The default implementation of sceneEvent() calls the specialized handlers,
    // so if you want the specialized handlers to be called, either don't override
    // sceneEvent, or override it and return false for events you don't handle here,
    // or explicitly call the base class sceneEvent() for unhandled types.


      qDebug() << "CustomItem sceneEvent: Type =" << event->type(); // Useful for seeing what events arrive

      switch (event->type()) {
      case QEvent::GraphicsSceneMousePress:
          // Cast the event to the correct type and call the specialized handler
          mousePressEvent(static_cast<QGraphicsSceneMouseEvent *>(event));
          event->accept(); // Explicitly accept if handled here
          return true; // Indicate that we handled the event
      case QEvent::GraphicsSceneMouseRelease:
          mouseReleaseEvent(static_cast<QGraphicsSceneMouseEvent *>(event));
          event->accept();
          return true;
      case QEvent::GraphicsSceneMouseMove:
          mouseMoveEvent(static_cast<QGraphicsSceneMouseEvent *>(event));
           // Decide whether to accept move events based on interaction state (e.g., dragging)
           // For simple demo, rely on specialized handler's base class accepting.
           // If you handle move entirely here, you might need to manage acceptance.
           // event->accept(); // Potentially accept here
          return true; // Indicate we processed the event type
      case QEvent::KeyPress:
          keyPressEvent(static_cast<QKeyEvent *>(event));
          event->accept(); // Assume key press handling is complete here
          return true;
      case QEvent::KeyRelease:
          keyReleaseEvent(static_cast<QKeyEvent *>(event));
          event->accept(); // Assume key release handling is complete here
          return true;
      case QEvent::GraphicsSceneMouseDoubleClick:
           mouseDoubleClickEvent(static_cast<QGraphicsSceneMouseEvent *>(event));
           event->accept();
           return true;
      // Add other event types if needed
      default:
          // For event types we don't handle here, call the base class implementation.
          // This is crucial so that other default event handling (like focus, hover, etc.) works.
          return QGraphicsEllipseItem::sceneEvent(event);
      }


    // By default, call the base class implementation.
    // The base class sceneEvent handles dispatching events to the specialized handlers
    // (mousePressEvent, keyPressEvent, etc.) if they are overridden and the event
    // hasn't been accepted already.
    // Returning the result of the base class call ensures proper propagation.
    return QGraphicsEllipseItem::sceneEvent(event);

    // To demonstrate that events arrive here *before* specialized handlers,
    // you can add a qDebug statement at the beginning of this function.
    // To demonstrate Method 2, uncomment the switch block above.
}

// Implementation of type() method
int CustomItem::type() const
{
    return Type; // Return the unique type ID
}