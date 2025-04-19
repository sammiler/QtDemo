#include <QApplication>
#include <QMainWindow>
#include <QTextBrowser>
#include <QLabel>
#include "QBorderLayout.h"

class BorderWindow : public QMainWindow {
    Q_OBJECT
public:
    BorderWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("QBorderLayout Demo");
        resize(600, 400);

        // Create central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create border layout
        QBorderLayout *borderLayout = new QBorderLayout(centralWidget, 10, 10);
        borderLayout->setSpacing(10);

        // Create and add widgets
        QTextBrowser *textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setPlainText(tr("Central Widget"));
        textBrowser->setStyleSheet("background-color: lightgray;");

        borderLayout->addWidget(textBrowser, QBorderLayout::Center);
        borderLayout->addWidget(createLabel("North", centralWidget), QBorderLayout::North);
        borderLayout->addWidget(createLabel("West", centralWidget), QBorderLayout::West);
        borderLayout->addWidget(createLabel("East 1", centralWidget), QBorderLayout::East);
        borderLayout->addWidget(createLabel("East 2", centralWidget), QBorderLayout::East);
        borderLayout->addWidget(createLabel("South", centralWidget), QBorderLayout::South);

        // // Ensure layout is applied
        borderLayout->activate();
        centralWidget->update();
    }

private:
    QLabel *createLabel(const QString &text, QWidget *parent) {
        QLabel *label = new QLabel(text, parent);
        label->setFrameStyle(QFrame::Box | QFrame::Raised);
        label->setStyleSheet("background-color: lightblue; padding: 5px;");
        label->setAlignment(Qt::AlignCenter);
        return label;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    BorderWindow window;
    window.show();
    
    return app.exec();
}

#include "main.moc"