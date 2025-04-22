// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

// Forward declare our custom item class
class CustomSignalingItem;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  QGraphicsScene *scene;
  QGraphicsView *view;
};

#endif // MAINWINDOW_H