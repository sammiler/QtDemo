#include "MainWindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QTime>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setMinimumSize(400, 400);
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPainterPath path;

    // 起始点（矩形左上角坐标）
    constexpr QPoint startPoint(50, 10);
    // 外部矩形宽度的1/2（外部圆半径）
    int nOuterRadius = 150;
    // 内部矩形宽度的1/2（内部圆半径）
    int nInnerRadius = 150;
    int nInnerHeightRadius = 120;
    // 间距
    int nSpacing = nOuterRadius - nInnerHeightRadius;

    QPointF rightPoint(startPoint.x() + nOuterRadius * 2, startPoint.y() + nOuterRadius);
    QRect outerRect(startPoint.x(), startPoint.y(), nOuterRadius * 2, nOuterRadius * 2);
    QPointF leftPoint(startPoint.x(), startPoint.y() + nInnerHeightRadius + nSpacing);
    QRect innerRect(startPoint.x(), startPoint.y() + nSpacing, nInnerRadius * 2, nInnerHeightRadius * 2);

    // 1.绘制外圆（绿色部分）
    path.moveTo(rightPoint);
    path.arcTo(outerRect, 180, 180);
    path.closeSubpath();
    painter.setPen(Qt::black);
    painter.setBrush(QColor(5, 150, 60));
    painter.drawPath(path);

    path = QPainterPath();
    // 2.绘制内圆（红色部分）
    path.moveTo(leftPoint);
    path.arcTo(innerRect, 180, 180);
    path.closeSubpath();
    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);
    painter.drawPath(path);

    // 3.生成椭圆（西瓜子）
    QPainterPath seedsPath = QPainterPath();

    // 随机种子
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // 在内圆区域内随机放置西瓜子
    for (int i = innerRect.left(); i < innerRect.left() + innerRect.width(); i += 30) {
        for (int j = innerRect.top() + nInnerHeightRadius; j < innerRect.top() + nInnerHeightRadius * 2; j += 20) {
            // 随机偏移
            int nX = qrand() % 30;
            int nY = qrand() % 30;
            // 确保西瓜子在内圆路径内
            QRect rect(i + nX, j + nY, 6, 10);
            if (path.contains(rect)) {
                seedsPath.addEllipse(rect);
            }
        }
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawPath(seedsPath);
}