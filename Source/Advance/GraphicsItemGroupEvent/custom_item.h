// custom_item.h
#ifndef CUSTOM_ITEM_H
#define CUSTOM_ITEM_H

#include <QGraphicsEllipseItem> // Using ellipse for shape
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QEvent> // Needed for sceneEvent signature
#include <QDebug> // Needed if debug statements are in header (not recommended)

class CustomItem : public QGraphicsEllipseItem // Inherit from QGraphicsEllipseItem
{
public:
    explicit CustomItem(QGraphicsItem *parent = nullptr); // Use nullptr instead of 0

protected:
    // --- Standard Event Handlers ---
    // These are called IF the event reaches this item AND is not consumed by sceneEvent first.
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    // --- Event Interception Handler ---
    // This method receives ALL events directed at this item BEFORE the specialized handlers above.
    // If it returns true, the event stops here (specialized handlers are NOT called).
    // If it returns false, the event continues to the specialized handlers.
    bool sceneEvent(QEvent *event) Q_DECL_OVERRIDE;

public:
    // For runtime type identification
    enum { Type = UserType + 2 }; // Use a unique type ID (UserType + 1 was used before)
    int type() const Q_DECL_OVERRIDE;
};

#endif // CUSTOM_ITEM_H