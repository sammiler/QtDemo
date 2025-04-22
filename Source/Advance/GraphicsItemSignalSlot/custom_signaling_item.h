// custom_signaling_item.h
#ifndef CUSTOM_SIGNALING_ITEM_H
#define CUSTOM_SIGNALING_ITEM_H

#include <QObject>         // Inherit from QObject for signals/slots/properties
#include <QGraphicsRectItem> // Inherit from QGraphicsItem (via QGraphicsRectItem)
#include <QPainter>        // For paint method signature
#include <QStyleOptionGraphicsItem> // For paint method signature
#include <QWidget>         // For paint method signature
#include <QGraphicsSceneMouseEvent> // For mouse event signature (if overriding)


// Custom item inheriting from QObject and QGraphicsItem (via QGraphicsRectItem)
// QGraphicsRectItem itself inherits from QGraphicsItem, so this is effective multi-inheritance.
class CustomSignalingItem : public QObject, public QGraphicsRectItem
{
  Q_OBJECT // REQUIRED for signals, slots, and properties

public:
  explicit CustomSignalingItem(QGraphicsItem *parent = nullptr); // Constructor

  // --- Overridden QGraphicsItem methods (REQUIRED) ---
  // You still need to implement these, inherited from QGraphicsRectItem/QGraphicsItem
  // virtual QRectF boundingRect() const override; // Inherited from QGraphicsRectItem
  // virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override; // Inherited from QGraphicsRectItem

  // --- Optional: Override event handlers to emit signals ---
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;


  // --- Custom Signals ---
  Q_SIGNALS:
      // Signal emitted when the item is clicked
      void itemClicked();

  // --- Custom Slots ---
  public Q_SLOTS:
      // Slot to demonstrate receiving calls and potentially emitting signals
      void mySlot();

  // --- For runtime type identification (optional but good practice) ---
public:
  enum { Type = UserType + 4 }; // Use a unique type ID
  int type() const Q_DECL_OVERRIDE; // Implement type() for qgraphicsitem_cast
};

#endif // CUSTOM_SIGNALING_ITEM_H