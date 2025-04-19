#include "MainWindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setMinimumSize(400, 400);

    // Set up timer for rotation
    pTimer = new QTimer(this);
    pTimer->setInterval(100);
    connect(pTimer, &QTimer::timeout, this, &MainWindow::updatePaint);
    pTimer->start();
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int radius = 150;
    int arcHeight = 30;

    // Center the painter
    painter.translate(width() >> 1, height() >> 1);

    // Apply rotation
    painter.rotate(m_nRotationAngle);

    // Draw arcs with different colors and angles
    gradientArc(&painter, radius, 0, 45, arcHeight, qRgb(200, 200, 0));
    gradientArc(&painter, radius, 45, 45, arcHeight, qRgb(200, 0, 200));
    gradientArc(&painter, radius, 90, 45, arcHeight, qRgb(0, 200, 200));
    gradientArc(&painter, radius, 135, 45, arcHeight, qRgb(200, 0, 0));
    gradientArc(&painter, radius, 225, 45, arcHeight, qRgb(0, 200, 0));
    gradientArc(&painter, radius, 180, 45, arcHeight, qRgb(0, 0, 200));
    gradientArc(&painter, radius, 270, 45, arcHeight, qRgb(0, 0, 0));
    gradientArc(&painter, radius, 315, 45, arcHeight, qRgb(150, 150, 150));
}

void MainWindow::gradientArc(QPainter *painter, int radius, int startAngle, int angleLength, int arcHeight, QRgb color) {
    // Set up radial gradient
    QRadialGradient gradient(0, 0, radius);
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1.0, color);
    painter->setBrush(gradient);

    // Define the outer rectangle for the arc
    const QRectF rect(-radius, -radius, radius << 1, radius << 1);
    QPainterPath path;
    path.arcTo(rect, startAngle, angleLength);

    // Define the inner ellipse to subtract for arc effect
    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));

    // Subtract to create the arc
    path -= subPath;

    // Set up font for text
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(14);

    // Add text at the midpoint of the arc
    painter->setPen(Qt::NoPen);
    path.addText(path.pointAtPercent(0.5), font, QStringLiteral("一去丶二三里"));
    painter->drawPath(path);
}

void MainWindow::updatePaint() {
    m_nRotationAngle++;
    if (m_nRotationAngle > 360) {
        m_nRotationAngle = 0;
    }
    update();
}