#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

    private slots:
        void updatePaint();

private:
    void gradientArc(QPainter *painter, int radius, int startAngle, int angleLength, int arcHeight, QRgb color);

    int m_nRotationAngle = 0;
    QTimer *pTimer;
};

#endif // MAINWINDOW_H