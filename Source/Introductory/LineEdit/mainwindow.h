//
// Created by sammiler on 2025/4/17.
//

#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H



#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    private slots:
        void onSearch(bool);

private:
    QLineEdit *m_pLineEdit;
    QLabel *m_pLabel;
};




#endif //MAINWINDOWS_H
