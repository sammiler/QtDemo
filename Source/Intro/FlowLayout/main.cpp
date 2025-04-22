#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "QFlowLayout.h"

class FlowWindow : public QMainWindow {
    Q_OBJECT
public:
    FlowWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("QFlowLayout Demo");
        resize(600, 400);

        // Create central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create flow layout
        QFlowLayout *flowLayout = new QFlowLayout(centralWidget, 10, 10, 10);
        flowLayout->setSpacing(10);

        // Add buttons to demonstrate flow layout
        createItems(centralWidget, flowLayout);

        // Ensure layout is applied
        flowLayout->activate();
        centralWidget->update();
    }

private:
    void createItems(QWidget *parent, QFlowLayout *layout) {
        // Add several buttons with different sizes
        QPushButton *button1 = new QPushButton("Button 1", parent);
        button1->setStyleSheet("background-color: lightblue;");
        layout->addItem(new QWidgetItem(button1));

        QPushButton *button2 = new QPushButton("Long Button 2", parent);
        button2->setStyleSheet("background-color: lightgreen;");
        layout->addItem(new QWidgetItem(button2));

        QPushButton *button3 = new QPushButton("Button 3", parent);
        button3->setStyleSheet("background-color: lightcoral;");
        layout->addItem(new QWidgetItem(button3));

        QPushButton *button4 = new QPushButton("Very Long Button 4", parent);
        button4->setStyleSheet("background-color: lightyellow;");
        layout->addItem(new QWidgetItem(button4));

        QPushButton *button5 = new QPushButton("Button 5", parent);
        button5->setStyleSheet("background-color: lightpink;");
        layout->addItem(new QWidgetItem(button5));

        // Add a label to show mixed widget types
        QLabel *label = new QLabel("Flow Layout Demo", parent);
        label->setStyleSheet("background-color: lightgray; padding: 5px;");
        layout->addItem(new QWidgetItem(label));
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    FlowWindow window;
    window.show();
    
    return app.exec();
}

#include "main.moc"