// custom_group.h
#ifndef CUSTOM_GROUP_H
#define CUSTOM_GROUP_H

#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent> // Optional: if overriding group's mouse events
#include <QKeyEvent> // Optional: if overriding group's key events
#include <QEvent> // Optional: if overriding group's sceneEvent

class CustomGroup : public QGraphicsItemGroup
{
public:
    explicit CustomGroup(QGraphicsItem *parent = nullptr); // Use nullptr

protected:
    // Optional: Override group's own event handlers to see when the group processes events
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

    // Optional: Override group's sceneEvent to intercept events directed at the group
    // bool sceneEvent(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // CUSTOM_GROUP_H