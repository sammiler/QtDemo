// mainwindow.cpp
#include "mainwindow.h"
#include "custom_rect_item.h" // Include our custom item header
#include <QGraphicsEllipseItem> // Standard item types
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget> // For proxying QWidgets
#include <QPushButton>         // Example QWidget to embed
#include <QLabel>              // Another QWidget example
#include <QPen>                // For item styling
#include <QBrush>              // For item styling
#include <QColor>              // For colors
#include <QLineF>              // For lines
#include <QFont>               // For text font
#include <QDebug>              // For qDebug() output
#include <QList>               // For QList

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Graphics Item Type Checking Demo")); // Use QStringLiteral
    resize(800, 600);

    scene = new QGraphicsScene(this); // Scene needs a parent
    view = new QGraphicsView(scene, this); // View needs scene and parent
    setCentralWidget(view);

    // Populate the scene with various item types
    populateSceneAndCheckTypes();

    // Set scene rect to encompass content (optional but good for initial view)
    scene->setSceneRect(scene->itemsBoundingRect().normalized().adjusted(-20, -20, 20, 20));

    // Optional: Set render hints or drag mode
    // view->setRenderHint(QPainter::Antialiasing);
    // view->setDragMode(QGraphicsView::ScrollHandDrag);
}

MainWindow::~MainWindow()
{
    // Qt's parent-child mechanism handles deleting scene, view, and items
}

// Method to add items and demonstrate type checking/casting
void MainWindow::populateSceneAndCheckTypes()
{
    qreal currentY = 20; // Starting Y position for items

    // --- Add different types of items ---

    // 1. QGraphicsRectItem
    QGraphicsRectItem *stdRectItem = new QGraphicsRectItem(0, 0, 100, 50);
    stdRectItem->setPos(50, currentY);
    stdRectItem->setBrush(Qt::blue);
    scene->addItem(stdRectItem);
    currentY += stdRectItem->boundingRect().height() + 20;

    // 2. QGraphicsEllipseItem
    QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem(0, 0, 80, 80);
    ellipseItem->setPos(50, currentY);
    ellipseItem->setBrush(Qt::green);
    scene->addItem(ellipseItem);
    currentY += ellipseItem->boundingRect().height() + 20;

    // 3. QGraphicsLineItem
    QGraphicsLineItem *lineItem = new QGraphicsLineItem(0, 0, 150, 100);
    lineItem->setPos(50, currentY);
    lineItem->setPen(QPen(Qt::red, 3));
    scene->addItem(lineItem);
    currentY += lineItem->boundingRect().height() + 20;

    // 4. QGraphicsTextItem
    QGraphicsTextItem *textItem = new QGraphicsTextItem(QStringLiteral("Hello World!"));
    textItem->setPos(50, currentY);
    textItem->setDefaultTextColor(Qt::black);
    textItem->setFont(QFont("Arial", 12));
    scene->addItem(textItem);
     currentY += textItem->boundingRect().height() + 20;

    // 5. QGraphicsProxyWidget (embedding a QPushButton)
    QPushButton *button = new QPushButton(QStringLiteral("Click Me!"));
    QGraphicsProxyWidget *buttonProxy = scene->addWidget(button);
    buttonProxy->setPos(50, currentY);
    // Note: addWidget handles adding the proxy to the scene
    currentY += buttonProxy->boundingRect().height() + 20;

    // 6. QGraphicsProxyWidget (embedding a QLabel)
    QLabel *label = new QLabel(QStringLiteral("This is a Label"));
    QGraphicsProxyWidget *labelProxy = scene->addWidget(label);
    labelProxy->setPos(50, currentY);
    currentY += labelProxy->boundingRect().height() + 20;

    // 7. Our CustomRectItem
    CustomRectItem *customItem = new CustomRectItem();
    customItem->setRect(0, 0, 120, 60); // Define its local rect
    customItem->setPos(50, currentY); // Position in scene
    customItem->setBrush(Qt::yellow);
    customItem->setPen(QPen(Qt::darkYellow, 2));
    scene->addItem(customItem);
    currentY += customItem->boundingRect().height() + 20;


    // --- Iterate through items and perform type checking/casting ---

    qDebug() << "\n--- Checking Item Types ---";
    QList<QGraphicsItem *> allItems = scene->items(); // Get list of all items in the scene
    qDebug() << "Total items in scene:" << allItems.size();

    foreach (QGraphicsItem *item, allItems) {
        qDebug() << "Processing item at scene pos:" << item->pos();

        // Method 1: Using item->type()
        int itemType = item->type();
        qDebug() << "  Raw type value:" << itemType;

        if (itemType == QGraphicsRectItem::Type) {
            qDebug() << "  This is a QGraphicsRectItem (Standard Type)";
            // Safely cast using qgraphicsitem_cast
            const auto rect = qgraphicsitem_cast<QGraphicsRectItem*>(item);
            if (rect) { // Always check if the cast was successful
                 qDebug() << "    Successfully cast to QGraphicsRectItem. Rect (local):" << rect->rect();
            }
        } else if (itemType == QGraphicsEllipseItem::Type) {
            qDebug() << "  This is a QGraphicsEllipseItem (Standard Type)";
            QGraphicsEllipseItem *ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            if (ellipse) {
                 qDebug() << "    Successfully cast to QGraphicsEllipseItem. Rect (local):" << ellipse->rect();
            }
        } else if (itemType == QGraphicsLineItem::Type) {
            qDebug() << "  This is a QGraphicsLineItem (Standard Type)";
            QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem*>(item);
            if (line) {
                 qDebug() << "    Successfully cast to QGraphicsLineItem. Line (local):" << line->line();
            }
        } else if (itemType == QGraphicsTextItem::Type) {
             qDebug() << "  This is a QGraphicsTextItem (Standard Type)";
             QGraphicsTextItem *text = qgraphicsitem_cast<QGraphicsTextItem*>(item);
             if (text) {
                 qDebug() << "    Successfully cast to QGraphicsTextItem. Plain text:" << text->toPlainText();
             }
        } else if (itemType == QGraphicsProxyWidget::Type) {
            qDebug() << "  This is a QGraphicsProxyWidget (Standard Type)";
            QGraphicsProxyWidget *proxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
            if (proxyWidget) {
                 qDebug() << "    Successfully cast to QGraphicsProxyWidget.";
                 // To get the embedded widget, use widget() method
                 QWidget *embeddedWidget = proxyWidget->widget();
                 qDebug() << "    Embedded widget type:" << embeddedWidget->metaObject()->className();

                 // Now, you can cast the embedded QWidget using qobject_cast
                 // qobject_cast works on objects inheriting QObject (like QWidget, QPushButton, QLabel)
                 QPushButton *btn = qobject_cast<QPushButton *>(embeddedWidget);
                 if (btn) {
                     qDebug() << "      Embedded widget is a QPushButton. Text:" << btn->text();
                 } else {
                     QLabel *lbl = qobject_cast<QLabel *>(embeddedWidget);
                     if (lbl) {
                         qDebug() << "      Embedded widget is a QLabel. Text:" << lbl->text();
                     }
                 }
            }
        } else if (itemType == CustomRectItem::Type) { // Check against our custom type value
            qDebug() << "  This is a CustomRectItem (User Type)";
            // Safely cast to our custom item type
            CustomRectItem *customRect = qgraphicsitem_cast<CustomRectItem*>(item);
            if (customRect) { // Always check if the cast was successful
                 qDebug() << "    Successfully cast to CustomRectItem. Rect (local):" << customRect->rect();
                 // You could call custom methods of CustomRectItem here
                 // customRect->myCustomMethod(); // If such a method existed
            }
        }
        // Note: item->type() will NOT return QGraphicsItem::Type for base QGraphicsItem objects
        // unless it's a pure QGraphicsItem with no further specialization (rare).
        // All concrete item classes (standard or custom) override type().

        // Method 2: Using qgraphicsitem_cast directly in if/else if chain
        // QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem*>(item);
        // if (rect) { /* ... */ }
        // else {
        //     QGraphicsEllipseItem *ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        //     if (ellipse) { /* ... */ }
        //     // ... and so on
        // }
        // This method is also valid, but checking type() first can sometimes be slightly
        // more explicit about which types you are expecting.

        qDebug() << "---------------------------";
    }
     qDebug() << "--- Type Checking Complete ---";
}