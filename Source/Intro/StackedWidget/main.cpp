#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>

class StackedWidgetWindow : public QMainWindow {
    Q_OBJECT
public:
    StackedWidgetWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("QStackedWidget Demo");
        resize(400, 300);

        // Create central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create main layout
        QVBoxLayout *layout = new QVBoxLayout();
        layout->setSpacing(10);
        layout->setContentsMargins(10, 10, 10, 10);

        // Create button
        QPushButton *button = new QPushButton(centralWidget);
        button->setText(QStringLiteral("点击切换"));

        // Create stacked widget and pages
        m_pStackedWidget = new QStackedWidget(centralWidget);
        QLabel *firstPage = new QLabel(centralWidget);
        QLabel *secondPage = new QLabel(centralWidget);
        QLabel *thirdPage = new QLabel(centralWidget);

        // Configure pages
        firstPage->setText(QStringLiteral("一去丶二三里"));
        firstPage->setStyleSheet("background-color: lightblue; padding: 10px;");
        firstPage->setAlignment(Qt::AlignCenter);
        secondPage->setText(QStringLiteral("青春不老，奋斗不止！"));
        secondPage->setStyleSheet("background-color: lightgreen; padding: 10px;");
        secondPage->setAlignment(Qt::AlignCenter);
        thirdPage->setText(QStringLiteral("纯正开源之美，有趣、好玩、靠谱。。。"));
        thirdPage->setStyleSheet("background-color: lightcoral; padding: 10px;");
        thirdPage->setAlignment(Qt::AlignCenter);

        // Add pages to stacked widget
        m_pStackedWidget->addWidget(firstPage);
        m_pStackedWidget->addWidget(secondPage);
        m_pStackedWidget->addWidget(thirdPage);

        // Add button and stacked widget to main layout
        layout->addWidget(button, 0, Qt::AlignLeft | Qt::AlignVCenter);
        layout->addWidget(m_pStackedWidget);

        // Apply layout to central widget
        centralWidget->setLayout(layout);

        // Connect button signal to slot
        connect(button, &QPushButton::clicked, this, &StackedWidgetWindow::switchPage);

        // Ensure layout is applied
        layout->activate();
        centralWidget->update();
    }

private slots:
    void switchPage() {
        int nCount = m_pStackedWidget->count();
        int nIndex = m_pStackedWidget->currentIndex();

        // Get next page index
        ++nIndex;

        // Loop back to first page if at the end
        if (nIndex >= nCount)
            nIndex = 0;

        m_pStackedWidget->setCurrentIndex(nIndex);
    }

private:
    QStackedWidget *m_pStackedWidget;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    StackedWidgetWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"