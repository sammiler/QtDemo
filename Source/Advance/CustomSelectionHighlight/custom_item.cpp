// custom_item.cpp
#include "custom_item.h"
#include <QDebug> // For optional debug output
#include <QColor>
#include <QBrush>

// Implementation of CustomItem
CustomItem::CustomItem(QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent) // Call base constructor
{
    QPen p = pen();
    p.setWidth(2);
    p.setColor(Qt::black); // Default border
    setPen(p);
    // Brush color set in mainwindow.cpp

    // Set Item flag to make it selectable
    setFlag(QGraphicsItem::ItemIsSelectable); // Item can be selected
    // setFlag(QGraphicsItem::ItemIsMovable); // You could make it movable too

    qDebug() << "CustomItem created.";
}

// Override the paint method
void CustomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Create a copy of the original option struct.
    // We do this because we might need to modify the state flag
    // when calling the base class paint method to prevent default drawing.
    QStyleOptionGraphicsItem op = *option;

    // Check if the item is currently in the QStyle::State_Selected state
    bool isSelected = option->state & QStyle::State_Selected;

    // If the item is selected, modify the *copy* of the option struct
    // to remove the State_Selected flag. This tells the base class's paint method
    // NOT to draw its default selection highlight (if any).
    if (isSelected) {
        op.state &= ~QStyle::State_Selected;
    }

    // --- Draw the standard ellipse shape ---
    // Call the base class paint method with the potentially modified option struct.
    // This draws the basic shape (the ellipse defined by setRect and brush/pen)
    // using the options provided, but without the default selection highlight
    // if we removed the flag from 'op'.
    QGraphicsEllipseItem::paint(painter, &op, widget);

    // --- Draw the custom selection highlight ONLY if the item was originally selected ---
    if (isSelected) { // Check the ORIGINAL option's state again
        // Calculate padding based on the item's OWN pen width.
        // The highlight is typically drawn just inside or around the item's pen border area.
        // Halving the item's pen width gives a good padding amount.
        qreal itemPenWidth = pen().widthF();
        const qreal pad = itemPenWidth / 2.0;

        // The highlight pen is usually cosmetic (width 0 in device-independent units, renders as 1 pixel)
        const qreal highlightPenWidth = 0;

        // Define the color for the custom highlight.
        // You can use a fixed color or colors from the style palette (like the standard highlight does).
        QColor highlightColor = Qt::yellow; // Using yellow as in your example

        // Draw the solid highlight rectangle
        painter->setPen(QPen(highlightColor, highlightPenWidth, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush); // Highlight usually has no fill
        // Draw a rectangle around the item's bounding rectangle, adjusted inwards by the padding.
        // This makes the highlight appear just inside the item's border.
        painter->drawRect(boundingRect().adjusted(pad, pad, -pad, -pad));

        // Draw the dashed highlight rectangle
        painter->setPen(QPen(highlightColor, highlightPenWidth, Qt::DashLine));
        // Brush is already NoBrush
        painter->drawRect(boundingRect().adjusted(pad, pad, -pad, -pad)); // Draw dashed line around the same adjusted rectangle
    }
}

// Optional: Implement type() method if needed for runtime casting/identification
// int CustomItem::type() const
// {
//     return Type;
// }