#include "PaintWidget.h"
#include <QPaintEvent>

void TextWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QColor(0, 160, 230));
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(50);
    font.setItalic(true);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, "Qt");
}

void LineWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor(0, 160, 230));
    painter.drawLine(QPointF(0, height()), QPointF(width() / 2, height() / 2));
}

void RectWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 160, 230), 2));
    painter.setBrush(QColor(255, 160, 90));
    painter.drawRect(50, 50, 160, 100);
}

void ArcWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    constexpr QRectF rect(90.0, 90.0, 80.0, 90.0);
    constexpr int startAngle = 90 * 16;
    constexpr int spanAngle = 120 * 16;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 160, 230), 2));
    painter.drawRect(rect);
    painter.drawArc(rect, startAngle, spanAngle);
}

void EllipseWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 160, 230), 2));
    painter.drawEllipse(QPointF(120, 60), 50, 20);
    painter.setBrush(QColor(255, 160, 90));
    painter.drawEllipse(QPointF(120, 140), 40, 40);
}

void PolygonWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor(0, 160, 230));
    static constexpr QPointF points[4] = {
        QPointF(30, 40), QPointF(60, 150), QPointF(150, 160), QPointF(220, 100)
    };
    painter.drawPolygon(points, 4);
}

void ImageWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(rect(), QPixmap(":/Images/logo"));
}