#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include<QDebug>
#include <QHBoxLayout>
#include "QCardLayout.h"

class CardWindow : public QMainWindow {
    Q_OBJECT
public:
    CardWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("QCardLayout Demo");
        resize(400, 300);

        // Create central widget and main layout
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        // QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

        // Create card layout
        cardLayout = new QCardLayout(centralWidget);
        cardLayout->setSpacing(50);
        // Create some example cards
        createCards();
        // Add layouts to main layout
        // mainLayout->addLayout(cardLayout);
        centralWidget->update();
    }

private:
    QCardLayout *cardLayout;

    void createCards() {
        QPushButton *button = new QPushButton("Click Me 1!",centralWidget());
        cardLayout->addItem(new QWidgetItem(button));
        QPushButton *button1 = new QPushButton("Click Me 2!",centralWidget());
        cardLayout->addItem(new QWidgetItem(button1));
        QPushButton *button2 = new QPushButton("Click Me 3!",centralWidget());
        cardLayout->addItem(new QWidgetItem(button2));
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    CardWindow window;
    window.show();
    
    return app.exec();
}

#include "main.moc"