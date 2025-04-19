#include "MainWindow.h"
#include <QPainter>
#include <QPainterPath>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setMinimumSize(400, 400);
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    /*****屁股*****/
    QPainterPath path;
    path.addRoundedRect(QRect(200, 60, 150, 150), 75, 75); // Replaced addRoundRect
    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);
    painter.drawPath(path);

    /*****肚子*****/
    // 腿
    path = QPainterPath();
    path.moveTo(170, 180);
    path.lineTo(120, 260);
    path.moveTo(185, 180);
    path.lineTo(145, 280);
    path.moveTo(200, 180);
    path.lineTo(180, 290);

    path.moveTo(200, 180);
    path.lineTo(220, 290);
    path.moveTo(215, 180);
    path.lineTo(250, 280);
    path.moveTo(230, 180);
    path.lineTo(280, 260);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::red);
    painter.drawPath(path);

    // 肚子
    path = QPainterPath();
    path.addRoundedRect(QRect(150, 130, 100, 100), 50, 50); // Replaced addRoundRect
    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);
    painter.drawPath(path);

    /*****头*****/
    // 犄角
    path = QPainterPath();
    path.moveTo(80, 100);
    path.lineTo(60, 20);
    path.moveTo(140, 100);
    path.lineTo(160, 20);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::red);
    painter.drawPath(path);

    // 头
    path = QPainterPath();
    path.addRoundedRect(QRect(50, 80, 120, 120), 60, 60); // Replaced addRoundRect
    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);
    painter.drawPath(path);

    // 左眼
    path = QPainterPath();
    path.addRoundedRect(QRect(70, 120, 25, 25), 12.5, 12.5); // Replaced addRoundRect
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);
    painter.drawPath(path);

    path = QPainterPath();
    path.addRoundedRect(QRect(75, 126, 10, 10), 5, 5); // Replaced addRoundRect
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawPath(path);

    // 右眼
    path = QPainterPath();
    path.addRoundedRect(QRect(120, 110, 25, 25), 12.5, 12.5); // Replaced addRoundRect
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);
    painter.drawPath(path);

    path = QPainterPath();
    path.addRoundedRect(QRect(125, 118, 10, 10), 5, 5); // Replaced addRoundRect
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawPath(path);

    // 嘴
    path = QPainterPath();
    path.moveTo(160, 108);
    path.arcTo(QRect(130, 48, 60, 60), 270, 90);
    painter.rotate(30);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);
    painter.drawPath(path);
}