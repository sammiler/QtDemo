// custom_rect_item.cpp
#include "custom_rect_item.h"
#include <QDebug>

// Implementation of CustomRectItem
CustomRectItem::CustomRectItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent) // Call base constructor
{
  qDebug() << "CustomRectItem created.";
  // You can add default properties here if needed
  // setPen(QPen(Qt::black, 1));
  // setBrush(Qt::gray);
}

// Implement the type() method
int CustomRectItem::type() const
{
  // Return the unique type ID defined in the header
  return Type;
}

// Optional: Implement custom methods
// void CustomRectItem::myCustomMethod() const
// {
//     qDebug() << "Hello from my CustomRectItem!";
// }