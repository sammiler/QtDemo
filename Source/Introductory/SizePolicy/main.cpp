#include <QApplication>
#include <QMainWindow>
#include <QTreeWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QDebug>

class TreeTableWindow : public QMainWindow {
    Q_OBJECT
public:
    TreeTableWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("TreeTableLayout Demo");
        resize(800, 400);

        // Create central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create tree and table widgets
        QTreeWidget *treeWidget = new QTreeWidget(centralWidget);
        QTableWidget *tableWidget = new QTableWidget(centralWidget);

        // Configure tree widget
        treeWidget->setHeaderLabel("Tree Items");
        QTreeWidgetItem *item1 = new QTreeWidgetItem(treeWidget, QStringList("Parent 1"));
        new QTreeWidgetItem(item1, QStringList("Child 1.1"));
        new QTreeWidgetItem(item1, QStringList("Child 1.2"));
        QTreeWidgetItem *item2 = new QTreeWidgetItem(treeWidget, QStringList("Parent 2"));
        new QTreeWidgetItem(item2, QStringList("Child 2.1"));
        new QTreeWidgetItem(item2, QStringList("Child 2.2"));
        treeWidget->expandAll();

        // Configure table widget
        tableWidget->setRowCount(3);
        tableWidget->setColumnCount(3);
        tableWidget->setHorizontalHeaderLabels({"Column 1", "Column 2", "Column 3"});
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(QString("Cell %1,%2").arg(row + 1).arg(col + 1));
                tableWidget->setItem(row, col, item);
            }
        }

        // Create horizontal layout
        QHBoxLayout *layout = new QHBoxLayout();
        layout->addWidget(tableWidget);
        layout->addWidget(treeWidget);
        layout->setSpacing(10);
        layout->setContentsMargins(10, 10, 10, 10);

        // Apply layout to central widget
        centralWidget->setLayout(layout);

        // Get default size policies
        QSizePolicy treeSizePolicy = treeWidget->sizePolicy();
        QSizePolicy tableSizePolicy = tableWidget->sizePolicy();
        qDebug() << "Default Tree Size Policy (Horizontal):" << treeSizePolicy.horizontalPolicy();
        qDebug() << "Default Table Size Policy (Horizontal):" << tableSizePolicy.horizontalPolicy();
        qDebug() << "Default Policy Value (7 = Expanding):" << QSizePolicy::Expanding;

        // Set size policies
        treeSizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
        tableSizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
        treeWidget->setSizePolicy(treeSizePolicy);
        tableWidget->setSizePolicy(tableSizePolicy);

        // Set stretch factors
        treeSizePolicy.setHorizontalStretch(1);
        tableSizePolicy.setHorizontalStretch(2);
        treeWidget->setSizePolicy(treeSizePolicy);
        tableWidget->setSizePolicy(tableSizePolicy);

        // Verify modified size policies
        qDebug() << "Modified Tree Size Policy (Horizontal):" << treeWidget->sizePolicy().horizontalPolicy();
        qDebug() << "Modified Table Size Policy (Horizontal):" << tableWidget->sizePolicy().horizontalPolicy();
        qDebug() << "Tree Horizontal Stretch:" << treeWidget->sizePolicy().horizontalStretch();
        qDebug() << "Table Horizontal Stretch:" << tableWidget->sizePolicy().horizontalStretch();

        // Ensure layout is applied
        layout->activate();
        centralWidget->update();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    TreeTableWindow window;
    window.show();
    
    return app.exec();
}

#include "main.moc"