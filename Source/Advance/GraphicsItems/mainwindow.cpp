// mainwindow.cpp
#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QGraphicsPolygonItem>
#include "SmileItem.h" // Include SmileItem header
#include <QFont>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QLineF>
#include <QPixmap>
#include <QRectF>
#include <QPainterPath>
#include <QPolygonF>
#include <cmath>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Qt Graphics Items and SmileItem Demo")); // Use QStringLiteral for window title
    resize(900, 1600); // Increase window size to accommodate more items

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Add items and position them
    addGraphicsItems(scene);

    // Optional: Adjust the view to fit the scene's content
    // view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    // view->setSceneRect(scene->itemsBoundingRect().adjusted(-20, -20, 20, 20));
}

MainWindow::~MainWindow()
{
    // Children deleted by parent
}

void MainWindow::addGraphicsItems(QGraphicsScene *scene)
{
    qreal current_y = 10; // Starting Y position for the top of the description text
    qreal padding = 30; // Vertical padding between item blocks (description + item)
    qreal item_margin_left = 20; // Horizontal margin for items and description text

    // Helper lambda function to add an item, its description, and position them vertically
    auto addAndPositionItem = [&](QGraphicsItem *item, const QString &description) {
        // Add a descriptive text item above the graphic item
        QGraphicsSimpleTextItem *descText = new QGraphicsSimpleTextItem(description);
        QFont descFont;
        descFont.setPointSize(10);
        descText->setFont(descFont);
        descText->setPos(item_margin_left, current_y); // Position description text
        scene->addItem(descText);

        current_y += descText->boundingRect().height() + 5; // Move current_y below description text, add small gap

        scene->addItem(item);
        // Calculate the top-left corner of the item's bounding rectangle in its local coordinates
        QRectF bounds = item->boundingRect();
        qreal item_local_top = bounds.top();
        qreal item_local_left = bounds.left();

        // Calculate the scene position needed so that the bounding rect's top-left is aligned horizontally
        // with the description margin and vertically starting from the adjusted current_y
        qreal target_scene_x = item_margin_left;
        qreal target_scene_y = current_y; // This is the desired top of the item's bounding box in scene coordinates

        // Item's local origin (0,0) needs to be placed at (target_scene_x - item_local_left, target_scene_y - item_local_top) in scene coordinates
        item->setPos(target_scene_x - item_local_left, target_scene_y - item_local_top);

        // Update current_y for the next item block (description + item)
        current_y += bounds.height() + padding; // Space for the item itself (based on bounds height) + padding

    };

    // QGraphicsSimpleTextItem
    QGraphicsSimpleTextItem *simpleTextItem = new QGraphicsSimpleTextItem();
    simpleTextItem->setText(QStringLiteral("一去丶二三里")); // Use QStringLiteral
    QFont font = simpleTextItem->font();
    font.setPixelSize(20);
    font.setItalic(true);
    font.setUnderline(true);
    simpleTextItem->setFont(font);
    simpleTextItem->setBrush(QBrush(QColor(0, 160, 230)));
    addAndPositionItem(simpleTextItem, QStringLiteral("QGraphicsSimpleTextItem: 一去丶二三里"));

    // QGraphicsTextItem (Plain Text)
    QGraphicsTextItem *plainTextItem = new QGraphicsTextItem();
    plainTextItem->setPlainText(QStringLiteral("一去丶二三里")); // Use QStringLiteral
    plainTextItem->setDefaultTextColor(QColor(0, 160, 230));
    font = plainTextItem->font();
    font.setPixelSize(20);
    font.setItalic(true);
    font.setUnderline(true);
    plainTextItem->setFont(font);
    addAndPositionItem(plainTextItem, QStringLiteral("QGraphicsTextItem (Plain): 一去丶二三里"));

    // QGraphicsTextItem (Rich Text/HTML)
    QGraphicsTextItem *htmlTextItem = new QGraphicsTextItem();
    QString strHTML = QStringLiteral("<html><body><b>Rich Text Item:</b><br/>\
                               <span style='color:#00A0E6;'>I am a Qter</span> \
                               </body></html>");
    htmlTextItem->setHtml(strHTML);
    addAndPositionItem(htmlTextItem, QStringLiteral("QGraphicsTextItem (HTML)"));

    // QGraphicsLineItem
    QGraphicsLineItem *lineItem = new QGraphicsLineItem();
    QPen linePen = lineItem->pen();
    linePen.setColor(QColor(0, 160, 230));
    linePen.setWidth(5);
    lineItem->setPen(linePen);
    lineItem->setLine(QLineF(0, 0, 100, 100)); // Line from (0,0) to (100,100) in item coords
    addAndPositionItem(lineItem, QStringLiteral("QGraphicsLineItem (Line from 0,0 to 100,100)"));

    // QGraphicsPixmapItem
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem();
    QPixmap dummyPixmap(80, 80);
    dummyPixmap.fill(QColor(100, 100, 100));
    {
        QPainter painter(&dummyPixmap);
        painter.setPen(Qt::white);
        painter.drawText(10, 40, "Pixmap");
    }
    pixmapItem->setPixmap(dummyPixmap);
    addAndPositionItem(pixmapItem, QStringLiteral("QGraphicsPixmapItem (Dummy)"));

    // QGraphicsRectItem
    QGraphicsRectItem *rectItem = new QGraphicsRectItem();
    QPen rectPen = rectItem->pen();
    rectPen.setWidth(5);
    rectPen.setColor(Qt::white);
    rectItem->setPen(rectPen);
    rectItem->setBrush(QBrush(QColor(0, 160, 230)));
    rectItem->setRect(QRectF(50, 50, 100, 100)); // Rect from (50, 50) in item coords
    addAndPositionItem(rectItem, QStringLiteral("QGraphicsRectItem (Rect from 50,50)"));

    // QGraphicsEllipseItem
    QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem ();
    QPen ellipsePen = ellipseItem->pen();
    ellipsePen.setWidth(5);
    ellipsePen.setColor(Qt::white);
    ellipseItem->setPen(ellipsePen);
    ellipseItem->setBrush(QBrush(QColor(0, 160, 230)));
    ellipseItem->setRect(QRectF(50, 50, 200, 100)); // Ellipse in rect from (50, 50) in item coords
    addAndPositionItem(ellipseItem, QStringLiteral("QGraphicsEllipseItem (Ellipse in rect from 50,50)"));

    // QGraphicsPathItem (Star)
    QGraphicsPathItem *pathItem = new QGraphicsPathItem();
    const float Pi = 3.14159f;
    QPainterPath starPath;
    starPath.moveTo(90, 50); // Points in item coordinates
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(50 + 40 * std::cos(0.8 * i * Pi), 50 + 40 * std::sin(0.8 * i * Pi));
    }
    starPath.closeSubpath();
    pathItem->setPath(starPath);
    QPen pathPen = pathItem->pen();
    pathPen.setWidth(2);
    pathPen.setColor(Qt::white);
    pathItem->setPen(pathPen);
    pathItem->setBrush(QBrush(QColor(0, 160, 230)));
    addAndPositionItem(pathItem, QStringLiteral("QGraphicsPathItem (Star)"));

    // QGraphicsPolygonItem
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem();
    QPolygonF polygon;
    polygon << QPointF(200.0, 120.0) << QPointF(230.0, 130.0)
            << QPointF(260.0, 180.0) << QPointF(200.0, 200.0); // Points in item coordinates
    polygonItem->setPolygon(polygon);
    QPen polygonPen = polygonItem->pen();
    polygonPen.setWidth(2);
    polygonPen.setColor(Qt::white);
    polygonItem->setPen(polygonPen);
    polygonItem->setBrush(QBrush(QColor(0, 160, 230)));
    addAndPositionItem(polygonItem, QStringLiteral("QGraphicsPolygonItem (Polygon)"));

    // --------------------------------------------------------------------
    // Add SmileItems
    // Continue adding items from the current_y position

    current_y += padding; // Add some extra space before the new section

    // SmileItem 1
    SmileItem *pItem1 = new SmileItem();
    pItem1->setRect(QRectF(-25, -25, 50, 50)); // Define its internal rectangle and scaling base
    // Its bounding box is from (-25,-25) to (25,25) in its local coordinates.
    // We want its top-left (-25,-25) to be positioned relative to item_margin_left and current_y.
    addAndPositionItem(pItem1, QStringLiteral("SmileItem 1 (setRect(-25,-25,50,50))"));
    // The addAndPositionItem helper will calculate setPos based on boundingRect()

    // SmileItem 2
    SmileItem *pItem2 = new SmileItem();
    pItem2->setRect(QRectF(-50, -50, 100, 100)); // Define its internal rectangle and scaling base
    // Its bounding box is from (-50,-50) to (50,50) in its local coordinates.
    addAndPositionItem(pItem2, QStringLiteral("SmileItem 2 (setRect(-50,-50,100,100))"));

    // SmileItem 3
    SmileItem *pItem3 = new SmileItem();
    pItem3->setRect(QRectF(-75, -75, 150, 150)); // Define its internal rectangle and scaling base
    // Its bounding box is from (-75,-75) to (75,75) in its local coordinates.
    addAndPositionItem(pItem3, QStringLiteral("SmileItem 3 (setRect(-75,-75,150,150))"));

     // After adding all items, adjust the scene rect to encompass all items
     // Add some padding around the items' collective bounding rectangle.
     scene->setSceneRect(scene->itemsBoundingRect().normalized().adjusted(-item_margin_left, -padding, padding, padding)); // Adjust padding around the whole scene bounds
}