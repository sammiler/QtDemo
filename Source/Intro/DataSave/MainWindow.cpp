#include "MainWindow.h"
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Initialize QListWidget with individual and overall storage
    m_listWidget = new QListWidget(this);
    for (int i = 0; i < 5; ++i) {
        QListWidgetItem *item = new QListWidgetItem(m_listWidget);
        // Individual storage
        item->setData(Qt::UserRole, i + 1);
        item->setData(Qt::UserRole + 1, QString("Qter %1").arg(i + 1));
        // Overall storage (commented out, enable to test)
        /*
        User user;
        user.nID = i + 1;
        user.strName = QString("Qter %1").arg(i + 1);
        item->setData(Qt::UserRole, QVariant::fromValue(user));
        */
        item->setText(QString("Item %1").arg(i + 1));
        m_listWidget->addItem(item);
    }
    connect(m_listWidget, &QListWidget::itemClicked, this, &MainWindow::onListItemClicked);
    layout->addWidget(m_listWidget);

    // Initialize QComboBox for language selection
    m_comboBox = new QComboBox(this);
    m_comboBox->addItem("Chinese");
    m_comboBox->addItem("English");
    m_comboBox->setItemData(0, QVariant::fromValue(UI_ZH));
    m_comboBox->setItemData(1, QVariant::fromValue(UI_EN));
    connect(m_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onComboBoxIndexChanged);
    layout->addWidget(m_comboBox);

    // Initialize QPushButton with userData
    m_button = new QPushButton("Standard Button", this);
    User user;
    user.nID = 1;
    user.strName = "User Name";
    m_button->setProperty("userData",QVariant::fromValue(user));
    connect(m_button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    layout->addWidget(m_button);

    // Initialize custom PushButton
    m_customButton = new PushButton(this);
    m_customButton->setText("Custom Button");
    m_customButton->setID(2);
    m_customButton->setName("Custom Qter");
    connect(m_customButton, &PushButton::clicked, this, &MainWindow::onCustomButtonClicked);
    layout->addWidget(m_customButton);
}

void MainWindow::onListItemClicked(QListWidgetItem *item)
{
    // Individual storage
    int id = item->data(Qt::UserRole).toInt();
    QString name = item->data(Qt::UserRole + 1).toString();
    qDebug() << "List Item - ID:" << id << "Name:" << name;

    // Overall storage (uncomment to test)
    /*
    QVariant variant = item->data(Qt::UserRole);
    User user = variant.value<User>();
    qDebug() << "List Item - ID:" << user.nID << "Name:" << user.strName;
    */
}

void MainWindow::onComboBoxIndexChanged(int index)
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(sender());
    QVariant variant = comboBox->itemData(index);
    LANGUAGE language = variant.value<LANGUAGE>();
    qDebug() << "ComboBox - Language:" << (language == UI_ZH ? "Chinese" : "English");
}

void MainWindow::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    User user = button->property("userData").value<User>();
    qDebug() << "Standard Button - ID:" << user.nID << "Name:" << user.strName;
}

void MainWindow::onCustomButtonClicked()
{
    PushButton *button = qobject_cast<PushButton *>(sender());
    qDebug() << "Custom Button - ID:" << button->id() << "Name:" << button->name();
}