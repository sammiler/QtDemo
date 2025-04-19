#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>

class PaintWidget : public QWidget {
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    virtual void paintEvent(QPaintEvent *event) override = 0;
};

class TextWidget : public PaintWidget {
public:
    TextWidget(QWidget *parent = nullptr) : PaintWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class LineWidget : public PaintWidget {
public:
    LineWidget(QWidget *parent = nullptr) : PaintWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class RectWidget : public PaintWidget {
public:
    RectWidget(QWidget *parent = nullptr) : PaintWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class ArcWidget : public PaintWidget {
public:
    ArcWidget(QWidget *parent = nullptr) : PaintWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class EllipseWidget : public PaintWidget {
public:
    EllipseWidget(QWidget *parent = nullptr) : PaintWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class PolygonWidget : public PaintWidget {
public:
    PolygonWidget(QWidget *parent = nullptr) : PaintWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class ImageWidget : public PaintWidget {
public:
    ImageWidget(QWidget *parent = nullptr) : PaintWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // PAINTWIDGET_H