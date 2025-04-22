#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedLayout>

class StackedWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit StackedWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("QStackedLayout Demo");
        resize(400, 300);

        // Create central widget
        const auto centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create main layout
        QVBoxLayout *layout = new QVBoxLayout();
        layout->setSpacing(10);
        layout->setContentsMargins(10, 10, 10, 10);

        // Create button
        QPushButton *button = new QPushButton(centralWidget);
        button->setText(QStringLiteral("点击切换"));

        // Create stacked layout and pages
        m_pStackedLayout = new QStackedLayout();
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

        // Add pages to stacked layout
        m_pStackedLayout->addWidget(firstPage);
        m_pStackedLayout->addWidget(secondPage);
        m_pStackedLayout->addWidget(thirdPage);

        // Add button and stacked layout to main layout
        layout->addWidget(button, 0, Qt::AlignLeft | Qt::AlignVCenter);
        layout->addLayout(m_pStackedLayout);

        // Apply layout to central widget
        centralWidget->setLayout(layout);

        // Connect button signal to slot
        connect(button, &QPushButton::clicked, this, &StackedWindow::switchPage);

        // Ensure layout is applied
        layout->activate();
        centralWidget->update();
    }
private slots:
    void switchPage() const {
        const int nCount = m_pStackedLayout->count();
        int nIndex = m_pStackedLayout->currentIndex();

        // Get next page index
        ++nIndex;

        // Loop back to first page if at the end
        if (nIndex >= nCount)
            nIndex = 0;

        m_pStackedLayout->setCurrentIndex(nIndex);
    }

private:
    QStackedLayout *m_pStackedLayout;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    StackedWindow window;
    window.show();
    
    return app.exec();
}

#include "main.moc"