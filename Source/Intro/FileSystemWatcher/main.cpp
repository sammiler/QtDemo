#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

#include "FileSystemWatcher.h"

class WatcherWindow : public QMainWindow {
    Q_OBJECT
public:
    WatcherWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("FileSystemWatcher Demo");
        resize(600, 400);

        // Create central widget
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create layout
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setSpacing(10);
        layout->setContentsMargins(10, 10, 10, 10);

        // Create input field and button
        QLineEdit* pathInput = new QLineEdit(centralWidget);
        pathInput->setText("E:/Test");
        pathInput->setPlaceholderText("Enter path to watch (e.g., E:/Test)");
        QPushButton* watchButton = new QPushButton("Start Watching", centralWidget);

        // Create text edit for logs
        QTextEdit* logOutput = new QTextEdit(centralWidget);
        logOutput->setReadOnly(true);

        // Add widgets to layout
        layout->addWidget(pathInput);
        layout->addWidget(watchButton);
        layout->addWidget(logOutput, 1); // Stretch to fill space

        // Apply layout
        centralWidget->setLayout(layout);

        // Connect button to start watching
        connect(watchButton, &QPushButton::clicked, this, [=]() {
            QString path = pathInput->text().trimmed();
            if (!path.isEmpty()) {
                FileSystemWatcher::instance()->addWatchPath(path);
                logOutput->append(QString("Started watching: %1").arg(path));
            } else {
                logOutput->append("Error: Please enter a valid path.");
            }
        });

        // Connect FileSystemWatcher signals to log output
        connect(FileSystemWatcher::instance(), &FileSystemWatcher::directoryUpdated, this, [=](const QString& path) {
            QString log = QString("Directory updated: %1").arg(path);
            logOutput->append(log);
            // Log detailed changes
            QStringList currEntryList = FileSystemWatcher::instance()->getContentsMap()[path];
            QDir dir(path);
            QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
            QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
            QSet<QString> currentDirSet = QSet<QString>::fromList(currEntryList);
            QSet<QString> newFiles = newDirSet - currentDirSet;
            QSet<QString> deletedFiles = currentDirSet - newDirSet;
            QStringList newFile = newFiles.toList();
            QStringList deleteFile = deletedFiles.toList();
            if (!newFile.isEmpty() && !deleteFile.isEmpty() && newFile.count() == 1 && deleteFile.count() == 1) {
                logOutput->append(QString("File Renamed from %1 to %2").arg(deleteFile.first(), newFile.first()));
            } else {
                if (!newFile.isEmpty()) {
                    logOutput->append("New Files/Dirs added: " + newFile.join(", "));
                }
                if (!deleteFile.isEmpty()) {
                    logOutput->append("Files/Dirs deleted: " + deleteFile.join(", "));
                }
            }
        });

        connect(FileSystemWatcher::instance(), &FileSystemWatcher::fileUpdated, this, [=](const QString& path) {
            QFileInfo file(path);
            QString log = QString("The file %1 at path %2 is updated").arg(file.fileName(), file.absolutePath());
            logOutput->append(log);
        });

        // Ensure layout is applied
        layout->activate();
        centralWidget->update();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    WatcherWindow window;
    window.show();
    
    // Add default watch path
    FileSystemWatcher::instance()->addWatchPath("E:/Test");
    
    return app.exec();
}

#include "main.moc"