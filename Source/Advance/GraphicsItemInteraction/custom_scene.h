// custom_scene.h
#ifndef CUSTOM_SCENE_H
#define CUSTOM_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent> // For mouse event signatures
#include <QKeyEvent> // For key event signature
#include <QPointF> // For QPointF

// 自定义 Scene, inheriting from QGraphicsScene
class CustomScene : public QGraphicsScene
{
    Q_OBJECT // Scenes can also have signals/slots, though not used in this example

public:
    // Constructor
    explicit CustomScene(QObject *parent = nullptr); // Inherit constructor

protected:
    // Overrides to handle mouse and key events when they are NOT handled by items
    // Called when a mouse button is pressed in the scene's area and NO item under the cursor accepted the event
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    // Called when the mouse is moved in the scene's area and NO item currently under the cursor is handling move events
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    // Called when a key is pressed and the scene or an item in the scene has focus
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
};

#endif // CUSTOM_SCENE_H