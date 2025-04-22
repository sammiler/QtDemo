// custom_item.h
#ifndef CUSTOM_ITEM_H
#define CUSTOM_ITEM_H

#include <QGraphicsEllipseItem> // Inherit from QGraphicsEllipseItem
#include <QPainter>             // For QPainter
#include <QStyleOptionGraphicsItem> // For QStyleOptionGraphicsItem
#include <QWidget>              // For QWidget in paint signature
#include <QPen>                 // For QPen::widthF()
#include <QStyle>               // For QStyle::State_Selected

class CustomItem : public QGraphicsEllipseItem // Inherit from QGraphicsEllipseItem
{
public:
    explicit CustomItem(QGraphicsItem *parent = nullptr); // Use nullptr constructor

protected:
    // Override the paint method to draw the item's shape and custom highlight
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) Q_DECL_OVERRIDE;

    // For runtime type identification (useful but not strictly needed for this specific demo)
    // enum { Type = UserType + 3 }; // Use a unique type ID
    // int type() const Q_DECL_OVERRIDE;
};

#endif // CUSTOM_ITEM_H