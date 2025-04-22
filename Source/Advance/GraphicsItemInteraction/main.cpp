//
// Created by sammiler on 2025/4/22.
//
// main.cpp
#include <QApplication>
#include <QGraphicsView>
// Include both custom item and scene headers as they are used here
#include "custom_item.h"
#include "custom_scene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create the custom scene
    CustomScene scene;
    // Set the scene's rectangular area in scene coordinates
    scene.setSceneRect(0, 0, 400, 300); // Defines the visible/interactive area of the scene

    // Create an initial item (optional, could just create on scene click)
    CustomItem *pItem = new CustomItem();
    // Set the item's internal rectangle relative to its local (0,0)
    pItem->setRect(20, 20, 60, 60);
    // Add the item to the scene. Its local (0,0) will be at scene (0,0) by default unless setPos is called.
    // Given setRect(20, 20, ...), the item's visible part will be from (20,20) relative to its local (0,0).
    // Since pos() defaults to (0,0), the item appears starting at scene (20,20).
    scene.addItem(pItem);


    // Create the view and set the scene
    QGraphicsView view;
    view.setScene(&scene);
    // Optional: Adjust view appearance
    // view.setStyleSheet("border: none;");
    view.setWindowTitle(QStringLiteral("Graphics Item Interaction Demo")); // Use QStringLiteral

    view.show();

    return QApplication::exec();
}