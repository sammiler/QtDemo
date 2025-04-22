#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>
#include <QPainter>

class TextWidget : public QWidget {
    Q_OBJECT

public:
    TextWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    virtual void paintEvent(QPaintEvent *event) override = 0;
};

class BasicTextWidget : public TextWidget {
public:
    BasicTextWidget(QWidget *parent = nullptr) : TextWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class AlignedTextWidget : public TextWidget {
public:
    AlignedTextWidget(QWidget *parent = nullptr) : TextWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class WrappedTextWidget : public TextWidget {
public:
    WrappedTextWidget(QWidget *parent = nullptr) : TextWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class ElidedTextWidget : public TextWidget {
public:
    ElidedTextWidget(QWidget *parent = nullptr) : TextWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class StyledTextWidget : public TextWidget {
public:
    StyledTextWidget(QWidget *parent = nullptr) : TextWidget(parent) {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // TEXTWIDGET_H