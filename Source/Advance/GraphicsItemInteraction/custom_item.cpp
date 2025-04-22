// custom_item.cpp
#include "custom_item.h"
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug> // For qDebug()
#include <QRectF> // For QRectF
#include <QGraphicsScene> // For accessing scene in mouse events (optional but sometimes needed)
#include <QGraphicsView> // For accessing view (less common in item events)

// Implementation of CustomItem
CustomItem::CustomItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent) // Inherit constructor
{
    // Configure the item's appearance
    QPen p = pen();
    p.setWidth(2);
    p.setColor(QColor(0, 160, 230));
    setPen(p);

    setBrush(QColor(247, 160, 57));

    // Set item flags to enable interactions
    setFlags(QGraphicsItem::ItemIsSelectable | // Item can be selected
             QGraphicsItem::ItemIsMovable);     // Item can be moved by dragging
             // ItemIsFocusable might be useful if you need keyboard input directly on the item
}

// Handle mouse button press events
void CustomItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Check if the left mouse button was pressed
    if (event->button() == Qt::LeftButton) {
        // Check modifier keys (Shift, Alt)
        if (event->modifiers() == Qt::ShiftModifier) {
            qDebug() << "Custom item left clicked with shift key.";
            // Select the item using Shift+Left Click
            setSelected(true);
            // Accept the event to prevent further propagation (e.g., to scene's mouse press)
            event->accept();
        } else if (event->modifiers() == Qt::AltModifier) {
            qDebug() << "Custom item left clicked with alt key. Checking for resize.";
            // Attempt to resize using Alt+Left Click drag
            // Calculate the item's center in scene coordinates at the start of the press
            QRectF bounds = boundingRect(); // Get the item's bounding rect in its local coordinates
            QPointF topLeftInScene = mapToScene(bounds.topLeft()); // Map its local top-left to scene coordinates
            m_centerPointF = QPointF(topLeftInScene.x() + bounds.width() / 2.0,
                                     topLeftInScene.y() + bounds.height() / 2.0); // Calculate center in scene coordinates

            double radius = bounds.width() / 2.0; // Approximate radius based on current width
            QPointF pos = event->scenePos(); // Mouse position in scene coordinates

            // Check if the mouse click is near the edge (for resizing)
            double dist = std::sqrt(std::pow(m_centerPointF.x() - pos.x(), 2) + std::pow(m_centerPointF.y() - pos.y(), 2));
            // If distance from center is > 80% of the radius, consider it a resize gesture
            if (radius > 0 && dist / radius > 0.8) { // Avoid division by zero if radius is 0
                 qDebug() << "Starting resize:" << "dist from center =" << dist << "radius =" << radius << "ratio =" << dist / radius;
                m_bResizing = true;
                 // Do NOT accept the event immediately if resizing. This allows mouseMoveEvent to receive the event.
                 // event->accept(); // Don't accept yet
            } else {
                m_bResizing = false;
                 qDebug() << "Not near edge for resizing.";
                 // If not resizing, let the base class handle potential movement
                 QGraphicsRectItem::mousePressEvent(event);
                 // If base class didn't accept (e.g., not movable), accept it here to stop propagation if needed
                 // event->accept(); // Decide based on desired behavior if not moving/resizing
            }
            // Accept the event anyway if Alt is pressed, so the item handles the gesture
            event->accept(); // Accept the event for Alt+Click scenarios
             qDebug() << "BoundingRect (local):" << bounds << "Radius:" << radius << "Item Pos (scene):" << this->pos() << "Mouse Pos (scene):" << pos << "Mouse Pos (item):" << event->pos() << "Center Pos (scene, calculated):" << m_centerPointF;

        } else {
            qDebug() << "Custom item left clicked (standard).";
            // For standard left click, let the base class handle selection/movement start
            QGraphicsRectItem::mousePressEvent(event);
            // Always accept the event after handling to stop further processing by parent items or scene
            event->accept();
        }
    } else if (event->button() == Qt::RightButton) {
        qDebug() << "Custom item right clicked.";
        // Ignore right click for now, or you could add a context menu
        event->ignore(); // Ignore allows event to pass to parent items or scene if they accept it
    }
}

// Handle mouse move events
void CustomItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Check if Alt key is held and we started a resize
    if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
        QPointF pos = event->scenePos(); // Current mouse position in scene coordinates
        // Calculate the distance from the original center (in scene coords) to the current mouse position
        const double dist = std::sqrt(std::pow(m_centerPointF.x() - pos.x(), 2) + std::pow(m_centerPointF.y() - pos.y(), 2));

        // Calculate the new size (diameter) based on the distance
        double newSize = dist * 2.0;
        if (newSize < 10) newSize = 10; // Prevent item from becoming too small (optional min size)

        // Calculate the new top-left corner of the rectangle *in item's local coordinates*
        // The goal is to redefine the rect so its center in scene coords stays near m_centerPointF.
        // The new local top-left X will be m_centerPointF.x() - this->pos().x() (center relative to item origin) - newSize / 2
        // The new local top-left Y will be m_centerPointF.y() - this->pos().y() (center relative to item origin) - newSize / 2
        const qreal newLocalX = m_centerPointF.x() - this->pos().x() - newSize / 2.0;
        const qreal newLocalY = m_centerPointF.y() - this->pos().y() - newSize / 2.0;

        // Update the item's rectangle
        setRect(newLocalX, newLocalY, newSize, newSize);

        // Accept the event to continue resizing and prevent movement
        event->accept();
    } else if (event->modifiers() != Qt::AltModifier) {
        // If Alt is not pressed, let the base class handle movement
        // This is only needed if ItemIsMovable flag is set.
        // The base class mouseMoveEvent handles dragging initiated in mousePressEvent.
        // If the item wasn't selected/picked up in press (e.g., shift-clicked), base move won't happen.
        // However, if ItemIsMovable is set and press was handled by base, move will work here.
        QGraphicsRectItem::mouseMoveEvent(event); // Call base class for standard movement

        // Optional: Debug item position after movement
        // qDebug() << "Item moved to scene pos:" << pos();

        // Accept the event if the base class handled movement or if you want to stop propagation
        // The base mouseMoveEvent usually accepts if it moves the item.
        // If base didn't move (e.g., no button pressed), you might still want to accept/ignore.
        // Let's rely on base class acceptance for simplicity of standard move.
    }
    // If neither resizing nor standard move happened (e.g. Alt was pressed but not resizing),
    // the event might be implicitly ignored or handled by something else.
}

// Handle mouse button release events
void CustomItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // If we were in resizing mode with Alt, stop resizing
    if ((event->modifiers() == Qt::AltModifier || !event->modifiers().testFlag(Qt::AltModifier)) && m_bResizing) {
         // Alt might be released before the mouse button, so check m_bResizing flag
        m_bResizing = false;
         qDebug() << "Stopped resizing.";
        // Accept the event if it was consumed by the resize gesture
        event->accept();
    } else {
        // Otherwise, let the base class handle standard release (e.g., finishing movement, triggering selection change)
        QGraphicsRectItem::mouseReleaseEvent(event);
        // Base class usually accepts if it did something.
        // Ensure event is accepted if the item fully handled the interaction
        event->accept(); // Assume item handles click/release
    }
}

// Implement the type() method for qgraphicsitem_cast
int CustomItem::type() const
{
    // Return the unique type ID
    return Type; // Or return UserType + 1;
}