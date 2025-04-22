#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    private slots:
        void onRefreshButtonClicked();

private:
    void displayNetworkInfo();

    const QPointer<QPushButton> refreshButton;
    const QPointer<QTextEdit> outputText;
    const QPointer<QVBoxLayout> mainLayout;
};

#endif // MAINWINDOW_H