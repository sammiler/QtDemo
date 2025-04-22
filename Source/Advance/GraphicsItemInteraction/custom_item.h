// custom_item.h
#ifndef CUSTOM_ITEM_H
#define CUSTOM_ITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent> // For mouse event signatures
#include <QKeyEvent> // For key event signature (though not implemented here, good practice if overriding)
#include <QPointF> // For QPointF member
#include <cmath> // For sqrt, pow in the implementation

// 自定义 Item, inheriting from QGraphicsRectItem
class CustomItem : public QGraphicsRectItem
{
public:
    // Constructor, takes optional parent item
    explicit CustomItem(QGraphicsItem *parent = 0);

    // Overrides to handle mouse events
protected:
    // Called when a mouse button is pressed over the item
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    // Called when the mouse is moved while a button is pressed over the item
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    // Called when a mouse button is released over the item
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    // Overrides for type identification
public:
    // Used to identify this custom item type with qgraphicsitem_cast
    enum { Type = UserType + 1 }; // Define a unique type enum
    int type() const Q_DECL_OVERRIDE; // Implement the virtual type() method


private:
    QPointF m_centerPointF; // Stores the item's center in scene coordinates on mouse press
    bool m_bResizing; // Flag to indicate if currently resizing
};

#endif // CUSTOM_ITEM_H