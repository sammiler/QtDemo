#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

class HBoxWindow : public QMainWindow {
    Q_OBJECT
public:
    HBoxWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("QHBoxLayout Demo");
        resize(600, 100);

        // Create central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create buttons
        QPushButton *button1 = new QPushButton("One", centralWidget);
        QPushButton *button2 = new QPushButton("Two", centralWidget);
        QPushButton *button3 = new QPushButton("Three", centralWidget);
        QPushButton *button4 = new QPushButton("Four", centralWidget);
        QPushButton *button5 = new QPushButton("Five", centralWidget);

        // Create horizontal layout
        QHBoxLayout *layout = new QHBoxLayout();
        layout->addWidget(button1);
        layout->addSpacerItem(new QSpacerItem(20, 20)); // 20px spacing
        layout->addWidget(button2);
        layout->addSpacing(10); // 10px spacing
        layout->addWidget(button3);
        layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Fixed)); // 20px expandable spacing
        layout->addWidget(button4);
        layout->addSpacing(2); // 2px spacing
        layout->addWidget(button5);

        // Set spacing and margin to 0
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);

        // Apply layout to central widget
        centralWidget->setLayout(layout);

        // Output default spacing and margin
        qDebug() << "Spacing:" << layout->spacing();
        qDebug() << "Margin:" << layout->contentsMargins();

        // Ensure layout is applied
        layout->activate();
        centralWidget->update();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    HBoxWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"