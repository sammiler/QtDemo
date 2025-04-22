#include "widget.h"
#include <QGroupBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug> // For console output
#include <QList> // For the result of findChildren

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // --- Start: Code from your snippet ---
    // 构建部件
    parentWidget = new QGroupBox(this); // parentWidget is now a child of the main Widget
    QGroupBox *subWidget = new QGroupBox(parentWidget); // subWidget is a child of parentWidget

    QCheckBox *pCheckBox1 = new QCheckBox(parentWidget);
    QCheckBox *pCheckBox2 = new QCheckBox(parentWidget);
    QCheckBox *pCheckBox3 = new QCheckBox(subWidget);
    QCheckBox *pCheckBox4 = new QCheckBox(subWidget);

    //设置标题
    parentWidget->setTitle("Parent GroupBox (Search Root)");
    subWidget->setTitle("Child GroupBox");

    // 设置文本
    pCheckBox1->setText("CheckBox1 (Direct Child)");
    pCheckBox2->setText("CheckBox2 (Direct Child)");
    pCheckBox3->setText("CheckBox3 (Grandchild)");
    pCheckBox4->setText("CheckBox4 (Grandchild)");

    // 设置objectName
    pCheckBox1->setObjectName("name"); // Found by both searches
    pCheckBox2->setObjectName("name1");
    pCheckBox3->setObjectName("name"); // Found only by recursive search
    pCheckBox4->setObjectName("name2");

    // 为subWidget设置布局，这时pCheckBox3、pCheckBox4均为它的孩子
    QVBoxLayout *pSubLayout = new QVBoxLayout();
    pSubLayout->addWidget(pCheckBox3);
    pSubLayout->addWidget(pCheckBox4);
    pSubLayout->setSpacing(10);
    pSubLayout->setContentsMargins(10, 10, 10, 10);
    subWidget->setLayout(pSubLayout);

    // 为parentWidget设置布局，这时pCheckBox1、pCheckBox2、以及subWidget均为它的孩子。
    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pCheckBox1);
    pLayout->addWidget(pCheckBox2);
    pLayout->addWidget(subWidget); // Add subWidget (which contains CheckBox3 and CheckBox4)
    pLayout->setSpacing(10);
    pLayout->setContentsMargins(10, 10, 10, 10);
    parentWidget->setLayout(pLayout);
    // --- End: Code from your snippet ---

    // --- Create Buttons to trigger search ---
    findDirectButton = new QPushButton("Find Direct Children ('name')", this);
    findRecursiveButton = new QPushButton("Find Recursive Children ('name')", this);

    // --- Create main layout for the Window ---
    QVBoxLayout *mainLayout = new QVBoxLayout(this); // Layout for the main Widget
    mainLayout->addWidget(parentWidget); // Add the groupbox containing checkboxes
    mainLayout->addWidget(findDirectButton); // Add the first button
    mainLayout->addWidget(findRecursiveButton); // Add the second button
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    setLayout(mainLayout); // Set the main layout for this window

    // --- Connect button clicks to slots ---
    connect(findDirectButton, &QPushButton::clicked, this, &Widget::onFindDirectChildrenClicked);
    connect(findRecursiveButton, &QPushButton::clicked, this, &Widget::onFindRecursiveChildrenClicked);

    setWindowTitle("Qt FindChildren Demo");
}

Widget::~Widget()
{
    // Qt's parent-child relationship handles deletion of child widgets automatically.
}

// Slot executed when the "Find Direct Children" button is clicked
void Widget::onFindDirectChildrenClicked()
{
    qDebug() << "\n--- Searching for QCheckBox with objectName='name' using Qt::FindDirectChildrenOnly ---";

    // Find only immediate children of parentWidget that are QCheckBox and have objectName "name"
    QList<QCheckBox*> foundCheckBoxes = parentWidget->findChildren<QCheckBox*>("name", Qt::FindDirectChildrenOnly);

    if (foundCheckBoxes.isEmpty()) {
        qDebug() << "No direct children found matching the criteria.";
    } else {
        qDebug() << "Found" << foundCheckBoxes.size() << "direct child checkbox(es):";
        for (QCheckBox* cb : foundCheckBoxes) {
            // Output objectName and the text of the found checkbox
            qDebug() << " - ObjectName:" << cb->objectName() << ", Text:" << cb->text();
        }
    }
     qDebug() << "-------------------------------------------------------------------------------";
}

// Slot executed when the "Find Recursive Children" button is clicked
void Widget::onFindRecursiveChildrenClicked()
{
    qDebug() << "\n--- Searching for QCheckBox with objectName='name' using Qt::FindChildrenRecursively ---";

    // Find children of parentWidget (including grandchildren, etc.) that are QCheckBox and have objectName "name"
    QList<QCheckBox*> foundCheckBoxes = parentWidget->findChildren<QCheckBox*>("name", Qt::FindChildrenRecursively); // Default is recursive

    // Note: Qt::FindChildrenRecursively is the default, so you could also write:
    // QList<QCheckBox*> foundCheckBoxes = parentWidget->findChildren<QCheckBox*>("name");

    if (foundCheckBoxes.isEmpty()) {
        qDebug() << "No recursive children found matching the criteria.";
    } else {
        qDebug() << "Found" << foundCheckBoxes.size() << "recursive child checkbox(es):";
        for (QCheckBox* cb : foundCheckBoxes) {
            // Output objectName and the text of the found checkbox
            qDebug() << " - ObjectName:" << cb->objectName() << ", Text:" << cb->text() << ", Parent:" << cb->parent()->objectName() << "(" << cb->parent()->metaObject()->className() << ")";
        }
    }
    qDebug() << "-------------------------------------------------------------------------------------";
}