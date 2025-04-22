#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>

class ClockWidget : public QWidget {
    Q_OBJECT

public:
    ClockWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    QRectF textRectF(double radius, int pointSize, double angle);
};

#endif // CLOCKWIDGET_H