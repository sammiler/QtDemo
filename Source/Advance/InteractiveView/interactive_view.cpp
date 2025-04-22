// interactive_view.cpp
#include "interactive_view.h"
#include <QWheelEvent>
#include <QKeyEvent>
#include <QMouseEvent> // Include QMouseEvent
#include <QPointF>     // Include QPointF
#include <QPainter>    // Include QPainter
#include <QDebug>      // Include qDebug
#include <QGraphicsScene> // Include QGraphicsScene for scene() and itemAt()
#include <QRect>       // Include QRect
#include <QTransform>  // Include QTransform for transform()

// Define macros used internally in this view's implementation
#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()

// Constructor
InteractiveView::InteractiveView(QWidget *parent)
    : QGraphicsView(parent), // Call base constructor
      m_translateButton(Qt::LeftButton), // Default pan button is Left
      m_scale(1.0), // Initial scale is 1.0
      m_zoomDelta(0.1), // Default zoom step
      m_translateSpeed(1.0), // Default pan speed
      m_bMouseTranslate(false) // Not panning initially
{
    // Hide scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Set cursor appearance when not panning
    setCursor(Qt::PointingHandCursor);

    // Enable anti-aliasing for smoother rendering
    setRenderHint(QPainter::Antialiasing);

    // Set the scene rectangle to a very large area.
    // This allows panning freely without hitting scene boundaries.
    // Using INT_MIN/2 and INT_MAX is a common way to create a practically infinite scene.
    setSceneRect(INT_MIN/2.0, INT_MIN/2.0, INT_MAX, INT_MAX);
    // Center the view on the scene's origin (0,0) initially
    centerOn(100, 100);
    // This is useful for centering zoom operations.
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

// Setter for translation speed
void InteractiveView::setTranslateSpeed(qreal speed)
{
    // Assert speed is within a reasonable range
    Q_ASSERT_X(speed >= 0.0 && speed <= 2.0,
               "InteractiveView::setTranslateSpeed", "Speed should be in range [0.0, 2.0].");
    m_translateSpeed = speed;
}

// Getter for translation speed
qreal InteractiveView::translateSpeed() const
{
    return m_translateSpeed;
}

// Setter for zoom delta
void InteractiveView::setZoomDelta(qreal delta)
{
    // Assert delta is within a reasonable range
    Q_ASSERT_X(delta >= 0.0 && delta <= 1.0,
               "InteractiveView::setZoomDelta", "Delta should be in range [0.0, 1.0].");
    m_zoomDelta = delta;
}

// Getter for zoom delta
qreal InteractiveView::zoomDelta() const
{
    return m_zoomDelta;
}

// Handle key press events for navigation and transformation
void InteractiveView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        translate(QPointF(0, -2));  // Translate up
        break;
    case Qt::Key_Down:
        translate(QPointF(0, 2));  // Translate down
        break;
    case Qt::Key_Left:
        translate(QPointF(-2, 0));  // Translate left
        break;
    case Qt::Key_Right:
        translate(QPointF(2, 0));  // Translate right
        break;
    case Qt::Key_Plus:  // Zoom in
        zoomIn();
        break;
    case Qt::Key_Minus:  // Zoom out
        zoomOut();
        break;
    case Qt::Key_Space:  // Rotate counter-clockwise
        rotate(-5); // rotate is a base class method
        break;
    case Qt::Key_Enter:  // Rotate clockwise (Enter and Return)
    case Qt::Key_Return:
        rotate(5); // rotate is a base class method
        break;
    default:
        // For any other keys, let the base class handle them (e.g., Tab for focus)
        QGraphicsView::keyPressEvent(event);
    }
}

// Handle mouse move events for panning
void InteractiveView::mouseMoveEvent(QMouseEvent *event)
{
    // If mouse panning is active
    if (m_bMouseTranslate){
        // Calculate the delta in scene coordinates
        // mapToScene converts a point from view coordinates to scene coordinates
        QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(m_lastMousePos);
        translate(mouseDelta); // Apply translation
    }

    // Update the last mouse position for the next move event
    m_lastMousePos = event->pos();

    // Let the base class handle other mouse move events (e.g., hover, rubber band drag)
    QGraphicsView::mouseMoveEvent(event);
}

// Handle mouse press events to start panning
void InteractiveView::mousePressEvent(QMouseEvent *event)
{
    // If the designated translation button is pressed
    if (event->button() == m_translateButton) {
        // Check if there is any item directly under the cursor at the current scale/transform.
        // We only start panning if the click is on the scene background.
        // itemAt(point, transform()) is the correct way to check for items at a view coordinate.
        QPointF point = mapToScene(event->pos()); // Get scene position of the click
        if (scene() && scene()->itemAt(point, transform()) == nullptr)  { // Check if scene exists and no item at the point
            m_bMouseTranslate = true; // Activate panning
            m_lastMousePos = event->pos(); // Store starting mouse position in view coordinates
            // Set cursor to indicate dragging
            setCursor(Qt::ClosedHandCursor);
            // Accept the event to prevent item selection/other base class handling if the click was on background
            // event->accept(); // Accepting here might interfere with base class if it has default behavior on empty space
            // Let's NOT accept here and rely on the base class mousePressEvent handling the click on empty space.
        }
    }

    // Let the base class handle the mouse press event.
    // This is important for standard features like item selection, starting rubber band drag, etc.
    QGraphicsView::mousePressEvent(event);
}

// Handle mouse release events to stop panning
void InteractiveView::mouseReleaseEvent(QMouseEvent *event)
{
    // If the translation button is released and panning was active
    if (event->button() == m_translateButton) {
        m_bMouseTranslate = false; // Deactivate panning
        // Restore cursor
        setCursor(Qt::PointingHandCursor);
    }

    // Let the base class handle other mouse release events
    QGraphicsView::mouseReleaseEvent(event);
}

// Handle mouse wheel events for zooming
void InteractiveView::wheelEvent(QWheelEvent *event)
{
    // Get the scroll amount in degrees (standard for QWheelEvent)
    QPoint scrollAmount = event->angleDelta();
    // Determine zoom direction based on the Y component
    // Positive Y means wheel rolled forward (zoom in)
    // Negative Y means wheel rolled backward (zoom out)
    scrollAmount.y() > 0 ? zoomIn() : zoomOut();

    // Accept the event to prevent it from propagating further (e.g., to parent widgets)
    event->accept();
}

// Slot to zoom in
void InteractiveView::zoomIn()
{
    zoom(1.0 + m_zoomDelta); // Call zoom with a factor greater than 1
}

// Slot to zoom out
void InteractiveView::zoomOut()
{
    zoom(1.0 - m_zoomDelta); // Call zoom with a factor less than 1
}

// Slot to apply a zoom factor
void InteractiveView::zoom(float scaleFactor)
{
    // Check for valid scaleFactor
    if (scaleFactor <= 0) {
        qDebug() << "Invalid scale factor:" << scaleFactor;
        return;
    }

    // Check if the resulting scale is within a reasonable range to prevent extreme zooming.
    // transform().scale(scaleFactor, scaleFactor) gets the potential new transformation matrix.
    // mapRect(QRectF(0, 0, 1, 1)) maps a 1x1 unit square using this new transform.
    // The width/height of the mapped rectangle gives the effective scale factor.
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    // Define min and max scale factors
    if (factor < 0.01 || factor > 100) { // Adjusted min factor slightly
        qDebug() << "Zoom level limit reached. Current factor:" << factor;
        return;
    }

    // Apply the scale transformation to the view
    scale(scaleFactor, scaleFactor);

    // Update the accumulated scale value (useful if you need the total scale)
    m_scale *= scaleFactor;
}

// Slot to translate the view (pan)
void InteractiveView::translate(QPointF delta)
{
    // Adjust the translation delta based on the current scale and speed factor.
    // Multiplying by m_scale makes the translation speed relative to the zoomed level.
    // Multiplying by m_translateSpeed applies the user-defined speed factor.
    delta *= m_scale; // Note: multiplying delta by scale here might feel counter-intuitive depending on desired behavior.
                      // Often, you want the *visual* pan speed to be constant regardless of zoom,
                      // in which case you might divide by scale or adjust speed based on scale.
                      // Sticking to original code's logic.
    delta *= m_translateSpeed;

    // Temporarily set the transformation anchor to the point under the mouse.
    // When centerOn is called, the view will try to keep the scene point at the anchor
    // in the same position relative to the viewport. Setting AnchorUnderMouse before
    // centerOn(mapToScene(newCenter)) allows recalculating the center based on the desired pan.
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Calculate the new desired center position in *view* coordinates.
    // Start from the current view center (VIEW_WIDTH/2, VIEW_HEIGHT/2) and subtract the delta.
    QPoint newCenterView(VIEW_WIDTH / 2 - delta.x(),  VIEW_HEIGHT / 2 - delta.y());

    // Convert the new desired view center point to its corresponding scene coordinate.
    QPointF newCenterScene = mapToScene(newCenterView);

    // Call centerOn with the new scene coordinate. This updates the view's translation
    // so that the point newCenterScene appears at the AnchorUnderMouse position (which was the mouse pos).
    // Effectively, this moves the view so that the content under the mouse moves by 'delta' in view coordinates.
    centerOn(newCenterScene);

    // Reset the transformation anchor back to the view's center for standard operations (like zoom).
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}