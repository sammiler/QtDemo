//
// Created by sammiler on 2025/4/17.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H




#include <QMainWindow>
#include <QButtonGroup>
#include <QRadioButton>
#include <QHBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

    private slots:
        void onButtonClicked(QAbstractButton *button);

private:
    QButtonGroup *m_pButtonGroup;
};



#endif //MAINWINDOW_H
