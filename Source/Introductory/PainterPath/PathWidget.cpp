#include "PathWidget.h"
#include <QPaintEvent>
#include <QLinearGradient>
#include <QPolygonF>

void EllipseWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient gradient(50, 50, 150, 150);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);

    QPen pen(QColor(0, 160, 230), 2);
    QRectF boundingRectangle(50, 50, 100, 80);

    QPainterPath path;
    path.addEllipse(boundingRectangle);

    painter.setBrush(gradient);
    painter.setPen(pen);
    painter.drawPath(path);
}

void PolygonWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient gradient(50, 50, 150, 150);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);

    const QPen pen(QColor(0, 160, 230), 2);
    QPolygonF polygon;
    polygon << QPointF(50, 50) << QPointF(150, 50)
            << QPointF(150, 150) << QPointF(50, 150);
    polygon << QPointF(50, 50); // 手动闭合

    QPainterPath path;
    path.addPolygon(polygon);

    painter.setBrush(gradient);
    painter.setPen(pen);
    painter.drawPath(path);
}

void RectWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient gradient(50, 50, 150, 150);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);

    const QPen pen(QColor(0, 160, 230), 2);
    constexpr QRectF rectangle(50, 50, 120, 80);

    QPainterPath path;
    path.addRect(rectangle);

    painter.setBrush(gradient);
    painter.setPen(pen);
    painter.drawPath(path);
}

void TextWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient gradient(50, 50, 150, 150);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);

    QPen pen(QColor(0, 160, 230), 2);
    QFont font("Microsoft YaHei", 20);
    QPointF baseline(50, 100);

    QPainterPath path;
    path.addText(baseline, font, tr("Qt"));

    painter.setBrush(gradient);
    painter.setPen(pen);
    painter.drawPath(path);
}

void ArcWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient gradient(50, 50, 150, 150);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);

    QPen pen(QColor(0, 160, 230), 2);
    QRectF boundingRect(50, 50, 100, 100);
    painter.drawRect(boundingRect);
    qreal startAngle = 30;
    qreal sweepLength = 180;

    QPainterPath path;
    path.moveTo(QPointF(100, 50)); // 移动到弧的起点
    path.arcTo(boundingRect, startAngle, sweepLength);

    painter.setBrush(gradient);
    painter.setPen(pen);
    painter.drawPath(path);
}

void BezierWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient gradient(50, 50, 150, 150);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);

    QPen pen(QColor(0, 160, 230), 2);
    QPointF start(50, 150);
    QPointF c1(100, 50);
    QPointF c2(150, 50);
    QPointF end(200, 150);

    QPainterPath path;
    path.moveTo(start);
    path.cubicTo(c1, c2, end);

    painter.setBrush(gradient);
    painter.setPen(pen);
    painter.drawPath(path);
}