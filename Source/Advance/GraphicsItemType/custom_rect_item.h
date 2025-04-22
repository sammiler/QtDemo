// custom_rect_item.h
#ifndef CUSTOM_RECT_ITEM_H
#define CUSTOM_RECT_ITEM_H

#include <QGraphicsRectItem> // Inherit from QGraphicsRectItem
#include <QObject> // Q_OBJECT is not needed unless you add signals/slots/properties

class CustomRectItem : public QGraphicsRectItem // Inherit from QGraphicsRectItem
{
public:
  explicit CustomRectItem(QGraphicsItem *parent = nullptr); // Constructor

  // Override the type() method to provide a unique type identifier
  // This allows qgraphicsitem_cast<CustomRectItem*>(item) to work correctly
  enum { Type = UserType + 1 }; // Define a unique type ID starting from UserType + 1
  int type() const Q_DECL_OVERRIDE; // Declare the overridden method

  // You could add custom methods here if needed
  // void myCustomMethod() const;
};

#endif // CUSTOM_RECT_ITEM_H