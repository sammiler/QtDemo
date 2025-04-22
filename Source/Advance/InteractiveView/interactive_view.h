// interactive_view.h
#ifndef INTERACTIVE_VIEW_H
#define INTERACTIVE_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent> // Need QMouseEvent for mouse event overrides
#include <QWheelEvent> // Need QWheelEvent for wheel event override
#include <QKeyEvent> // Need QKeyEvent for key event override
#include <QPointF> // Need QPointF for translate method
#include <QPainter> // Need QPainter for render hints

// Define macros used in the .cpp (good practice to define them where used or in a common header)
// Although these are specific to the view's viewport, defining them here or just in the cpp is fine.
// Let's keep them in the cpp as they are view-internal.

class InteractiveView : public QGraphicsView
{
    Q_OBJECT // Q_OBJECT macro is required for signals/slots and other meta-object features

public:
    explicit InteractiveView(QWidget *parent = nullptr); // Use nullptr instead of 0

    // Translate speed
    void setTranslateSpeed(qreal speed);
    qreal translateSpeed() const;

    // Zoom delta
    void setZoomDelta(qreal delta);
    qreal zoomDelta() const;

protected:
    // Overridden event handlers from QWidget/QGraphicsView
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

public Q_SLOTS: // Slots accessible via signal/slot connections or QMetaObject
    void zoomIn();  // Zoom in
    void zoomOut();  // Zoom out
    void zoom(float scaleFactor); // Zoom by scaleFactor
    void translate(QPointF delta);  // Translate the view

private:
    Qt::MouseButton m_translateButton;  // Mouse button for panning
    qreal m_translateSpeed;  // Panning speed factor
    qreal m_zoomDelta;  // Zoom step size
    bool m_bMouseTranslate;  // Flag for active mouse panning
    QPoint m_lastMousePos;  // Last mouse position in view coordinates during pan
    qreal m_scale;  // Current view scale factor (accumulated)
};

#endif // INTERACTIVE_VIEW_H