#include "GradientWidget.h"
#include <QPaintEvent>

void LinearGradientWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient linear(QPointF(80, 80), QPointF(150, 150));
    linear.setColorAt(0, Qt::black);
    linear.setColorAt(1, Qt::white);
    linear.setSpread(QGradient::PadSpread);

    painter.setPen(QPen(QColor(0, 160, 230), 2));
    painter.setBrush(linear);
    painter.drawRect(QRect(40, 40, 180, 180));
}

void RadialGradientWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRadialGradient radial(110, 110, 50, 130, 130);
    radial.setColorAt(0, Qt::black);
    radial.setColorAt(1, Qt::white);
    radial.setSpread(QGradient::ReflectSpread);

    painter.setPen(QPen(QColor(0, 160, 230), 2));
    painter.setBrush(radial);
    painter.drawRect(QRect(40, 40, 180, 180));
}

void ConicalGradientWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QConicalGradient conical(110, 110, 45);
    conical.setColorAt(0, Qt::black);
    conical.setColorAt(1, Qt::white);

    painter.setPen(QPen(QColor(0, 160, 230), 2));
    painter.setBrush(conical);
    painter.drawRect(QRect(40, 40, 180, 180));
}