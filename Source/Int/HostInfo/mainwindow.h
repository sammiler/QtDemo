#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostInfo>
#include <QHostAddress>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
        void onLookupButtonClicked();
    void onAbortButtonClicked();
    void lookedUp(const QHostInfo &host);

private:
    QLineEdit *inputLineEdit;
    QPushButton *lookupButton;
    QPushButton *abortButton;
    QTextEdit *outputText;
    int lookupId;
};

#endif // MAINWINDOW_H