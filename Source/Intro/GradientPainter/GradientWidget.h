#ifndef GRADIENTWIDGET_H
#define GRADIENTWIDGET_H

#include <QWidget>
#include <QPainter>

class GradientWidget : public QWidget {
    Q_OBJECT

public:
    GradientWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    virtual void paintEvent(QPaintEvent *event) override = 0;
};

class LinearGradientWidget : public GradientWidget {
public:
    LinearGradientWidget(QWidget *parent = nullptr) : GradientWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class RadialGradientWidget : public GradientWidget {
public:
    RadialGradientWidget(QWidget *parent = nullptr) : GradientWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class ConicalGradientWidget : public GradientWidget {
public:
    ConicalGradientWidget(QWidget *parent = nullptr) : GradientWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // GRADIENTWIDGET_H