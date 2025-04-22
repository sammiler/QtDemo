// mainwindow.cpp
#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget> // Include QGraphicsProxyWidget header
#include <QLineEdit>         // Include headers for widgets you want to embed
#include <QGroupBox>
#include <QLabel>
#include <QFormLayout>
#include <QVBoxLayout> // Or other layouts if needed within the QGroupBox
#include <QPushButton> // Example of another simple widget
#include <QDebug> // Optional for debug output

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Qt Graphics Proxy Widget Demo"));
    resize(600, 500);

    scene = new QGraphicsScene(this); // Scene needs a parent (MainWindow)
    view = new QGraphicsView(scene, this); // View needs a scene and a parent (MainWindow)
    setCentralWidget(view); // Set the view as the main widget

    // --- Embed Widgets using QGraphicsProxyWidget ---

    // Example 1: Embedding a QLineEdit
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(QStringLiteral("Enter some text here"));
    // Use addWidget to embed the widget. It creates and returns a QGraphicsProxyWidget.
    QGraphicsProxyWidget *lineEditProxy = scene->addWidget(lineEdit);
    // Position the proxy widget in the scene
    lineEditProxy->setPos(50, 50);
    // Optional: Apply transformation to the proxy
    // lineEditProxy->setRotation(15);

    // Example 2: Embedding a QGroupBox with a layout and other widgets inside
    QGroupBox *groupBox = new QGroupBox();
    groupBox->setTitle(QStringLiteral("Contact Information"));

    QLabel *tellLabel = new QLabel(QStringLiteral("Phone Number:"));
    QLabel *addressLabel = new QLabel(QStringLiteral("Residential Address:"));
    QLineEdit *tellLineEdit = new QLineEdit();
    tellLineEdit->setPlaceholderText(QStringLiteral("Mobile/Landline"));
    QLineEdit *addressLineEdit = new QLineEdit();
    addressLineEdit->setPlaceholderText(QStringLiteral("Street address and number"));

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tellLabel, tellLineEdit);
    formLayout->addRow(addressLabel, addressLineEdit);
    formLayout->setSpacing(10);
    formLayout->setMargin(20); // Margin inside the group box
    groupBox->setLayout(formLayout);

    // Embed the group box using addWidget
    QGraphicsProxyWidget *groupBoxProxy = scene->addWidget(groupBox);
    // Position the group box proxy below the line edit proxy
    // We can get the size from the widget's sizeHint or the proxy's boundingRect
    // Let's estimate for simplicity or use previous item's bounds + padding
    qreal lineEditHeight = lineEditProxy->boundingRect().height();
    groupBoxProxy->setPos(50, 50 + lineEditHeight + 30); // Position with padding

    // Example 3: Embedding a QPushButton
    QPushButton *button = new QPushButton(QStringLiteral("Click Me!"));
    QGraphicsProxyWidget *buttonProxy = scene->addWidget(button);
    // Position the button proxy
    qreal groupBoxHeight = groupBoxProxy->boundingRect().height();
    buttonProxy->setPos(50, 50 + lineEditHeight + 30 + groupBoxHeight + 30); // Position below group box

    // --- Optional: Add a standard Graphics Item for comparison ---
    QGraphicsRectItem *rectItem = new QGraphicsRectItem(0, 0, 100, 50);
    rectItem->setBrush(Qt::cyan);
    rectItem->setPos(300, 50); // Position the standard item

    // --- Final Scene Setup ---
    // Adjust the scene rect to encompass all embedded widgets and graphics items
    // This helps the view automatically display all content.
    // Add some padding around the calculated bounds.
    QRectF bounds = scene->itemsBoundingRect();
    scene->setSceneRect(bounds.normalized().adjusted(-20, -20, 20, 20));

    // Optional: Adjust view behavior
    // view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio); // Fit the scene into the view initially
    // view->setRenderHint(QPainter::Antialiasing); // Improve rendering quality
}

MainWindow::~MainWindow()
{
    // Qt's parent-child mechanism handles deleting scene, view, and items/proxies within the scene
}