#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QComboBox>
#include <QPushButton>
#include "PushButton.h"
#include "User.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    private slots:
        void onListItemClicked(QListWidgetItem *item);
    void onComboBoxIndexChanged(int index);
    void onButtonClicked();
    void onCustomButtonClicked();

private:
    QListWidget *m_listWidget;
    QComboBox *m_comboBox;
    QPushButton *m_button;
    PushButton *m_customButton;
};

#endif // MAINWINDOW_H