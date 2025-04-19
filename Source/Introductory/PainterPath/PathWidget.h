#ifndef PATHWIDGET_H
#define PATHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class PathWidget : public QWidget {
    Q_OBJECT

public:
    PathWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    virtual void paintEvent(QPaintEvent *event) override = 0;
};

class EllipseWidget : public PathWidget {
public:
    EllipseWidget(QWidget *parent = nullptr) : PathWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class PolygonWidget : public PathWidget {
public:
    PolygonWidget(QWidget *parent = nullptr) : PathWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class RectWidget : public PathWidget {
public:
    RectWidget(QWidget *parent = nullptr) : PathWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class TextWidget : public PathWidget {
public:
    TextWidget(QWidget *parent = nullptr) : PathWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class ArcWidget : public PathWidget {
public:
    ArcWidget(QWidget *parent = nullptr) : PathWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class BezierWidget : public PathWidget {
public:
    BezierWidget(QWidget *parent = nullptr) : PathWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // PATHWIDGET_H