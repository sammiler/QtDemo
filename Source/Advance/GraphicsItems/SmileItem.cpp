// SmileItem.cpp
#include <QPainter>
#include <QPainterPath> // Needed for drawing the smile arc
#include <QStyleOptionGraphicsItem> // Required for paint signature
#include <QWidget> // Required for paint signature
#include <QDebug> // Optional for debugging
#include "SmileItem.h"

SmileItem::SmileItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    // Default rectangle in item coordinates
    setRect(QRectF(-50, -50, 100, 100));
}

SmileItem::SmileItem(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setRect(rect);
}

SmileItem::SmileItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setRect(x, y, w, h);
}

SmileItem::~SmileItem()
{
}

QRectF SmileItem::rect() const
{
    return m_rect;
}

void SmileItem::setRect(const QRectF &rect)
{
    if (m_rect == rect)
        return;

    prepareGeometryChange(); // Notify the framework that the item's geometry is about to change
    m_rect = rect;
    m_boundingRect = QRectF(); // Invalidate cached bounding rect
    updateRect(); // Recalculate drawing parameters based on the new rect
    update(); // Request a repaint
}

QRectF SmileItem::boundingRect() const
{
    // Return the bounding rectangle in item's local coordinates
    // The base class implementation would return m_rect if no pen width is involved.
    // If a pen is used for the border of the face, the bounding rect should be m_rect extended by half the pen width.
    // For simplicity, we'll return m_rect as the blog post's code does,
    // assuming the outer face ellipse uses Qt::NoPen or a thin pen not significantly affecting layout.
    if (m_boundingRect.isNull()) {
        // If face ellipse had a pen, calculate bounds including pen:
        // QPen facePen = Qt::NoPen; // Assume NoPen from your paint method
        // qreal penWidth = 0; //facePen.widthF();
        // m_boundingRect = m_rect.normalized().adjusted(-penWidth/2, -penWidth/2, penWidth/2, penWidth/2);

        // Based on your paint code which draws the face ellipse using m_rect with NoPen,
        // and internal features relative to the item's origin (0,0),
        // the bounding rect should encompass *all* drawn elements.
        // A safe bounding rect would be the union of m_rect and the bounds of the eyes/mouth features.
        // However, your blog post's example uses m_rect directly in boundingRect,
        // implying the face ellipse defined by m_rect *is* considered the main bounding box.
        // Let's stick to the original logic for now:
        m_boundingRect = m_rect.normalized();
    }

    return m_boundingRect;
}

void SmileItem::updateRect()
{
    // This function calculates the positions and sizes of facial features
    // relative to the item's local origin (0,0), based on the current m_rect.

    // Scaling factor based on the width of m_rect compared to a reference size (100)
    m_dScale = m_rect.width() / 100.0;

    // Left eye center: Calculated relative to item's (0,0)
    // Original example values (-15, -25) are scaled
    m_leftEyeCenter.setX(-15 * m_dScale);
    m_leftEyeCenter.setY(-25 * m_dScale);

    // Right eye center: Calculated relative to item's (0,0)
    // Original example values (15, -25) are scaled
    m_rightEyecenter.setX(15 * m_dScale);
    m_rightEyecenter.setY(-25 * m_dScale);

    // Smile center: Calculated relative to item's (0,0)
    // Original example values (0, 10) are scaled
    m_smileCenter.setX(0);
    m_smileCenter.setY(10 * m_dScale);

    // Eye dimensions: Calculated relative to item's (0,0), based on m_rect.width() and a ratio (12/100)
    m_dEyeWidth = m_rect.width() * (12.0 / 100.0); // Correct interpretation of width / (100.0 / 12)
    m_dEyeHeight = m_dEyeWidth * 2; // Height is 2 times width

    // Eye ball dimension: Calculated based on eye width
    m_dEyeBallWidth = m_dEyeWidth / 4;

    // Smile dimensions: Calculated relative to item's (0,0), based on m_rect dimensions and ratios
    m_dSmileWidth = m_rect.width() * (66.0 / 100.0); // Correct interpretation of width / (100.0 / 66)
    m_dSmileHeight = m_rect.height() * (50.0 / 100.0); // Correct interpretation of height / (100.0 / 50)
}

void SmileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // All drawing in the paint method is done in the item's local coordinates.
    // The item's local origin (0,0) is where the item is positioned in the scene (via setPos).

    // Anti-aliasing for smoother shapes
    painter->setRenderHint(QPainter::Antialiasing, true);

    // Face (Ellipse): Drawn using m_rect in item coordinates
    painter->setPen(Qt::NoPen); // Face has no outline
    painter->setBrush(Qt::yellow); // Face is yellow
    painter->drawEllipse(m_rect); // Draw the face ellipse based on the m_rect passed to setRect

    // Left eye (Ellipse): Drawn relative to m_leftEyeCenter in item coordinates
    painter->setPen(QPen(Qt::black)); // Eye outline
    painter->setBrush(Qt::white); // Eye fill
    // The ellipse is defined by a rectangle whose top-left is calculated
    // relative to m_leftEyeCenter, in item coordinates.
    painter->drawEllipse(QRectF(m_leftEyeCenter.x() - m_dEyeWidth / 2,
                                m_leftEyeCenter.y() - m_dEyeHeight / 2,
                                m_dEyeWidth, m_dEyeHeight));

    // Left eyeball (Ellipse): Drawn relative to m_leftEyeCenter in item coordinates
    painter->setPen(QPen(Qt::black)); // Eyeball outline
    painter->setBrush(Qt::black); // Eyeball fill
    // The ellipse is defined by a rectangle whose top-left is calculated
    // relative to m_leftEyeCenter, in item coordinates. Note the size is m_dEyeBallWidth / 2, which seems like a typo
    // in the original code - usually size should be just m_dEyeBallWidth for width and height.
    // Sticking to original code's calculation:
    painter->drawEllipse(QRectF(m_leftEyeCenter.x() - m_dEyeBallWidth / 2,
                                m_leftEyeCenter.y() - m_dEyeBallWidth / 2,
                                m_dEyeBallWidth, m_dEyeBallWidth)); // Uses width/2, height/2

    // Right eye (Ellipse): Drawn relative to m_rightEyecenter in item coordinates
    painter->setPen(QPen(Qt::black));
    painter->setBrush(Qt::white);
     painter->drawEllipse(QRectF(m_rightEyecenter.x() - m_dEyeWidth / 2,
                                m_rightEyecenter.y() - m_dEyeHeight / 2,
                                m_dEyeWidth, m_dEyeHeight));

    // Right eyeball (Ellipse): Drawn relative to m_rightEyecenter in item coordinates
    painter->setPen(QPen(Qt::black));
    painter->setBrush(Qt::black);
     painter->drawEllipse(QRectF(m_rightEyecenter.x() - m_dEyeBallWidth / 2,
                                m_rightEyecenter.y() - m_dEyeBallWidth / 2,
                                m_dEyeBallWidth , m_dEyeBallWidth )); // Uses width/2, height/2

    // Mouth (Arc): Drawn relative to m_smileCenter in item coordinates
    painter->setPen(QPen(Qt::red)); // Mouth outline
    painter->setBrush(Qt::NoBrush); // Mouth has no fill

    QPainterPath path;
    // arcMoveTo and arcTo define an arc based on a bounding rectangle and angles.
    // The bounding rectangle is centered around m_smileCenter in item coordinates.
    // Original calculation for bounding rect top-left in item coords:
    // x: - m_dSmileWidth / 2
    // y: - (m_dSmileHeight / 2 - m_smileCenter.y()) --- This looks like it's trying to center the arc bounding box vertically,
    // but adjusted by m_smileCenter.y(). Let's trace: if m_smileCenter.y() is positive (below origin),
    // this moves the top of the arc bounding box *down* compared to just - m_dSmileHeight / 2.
    // This math positions the arc's conceptual bounding box.
    const QRectF smileBoundingRect(- m_dSmileWidth / 2, - m_smileCenter.y(),
                             m_dSmileWidth, m_dSmileHeight);

    path.arcMoveTo(smileBoundingRect, 0); // Start angle (0 degrees)
    path.arcTo(smileBoundingRect, 0, -180); // Sweep angle (-180 degrees counter-clockwise)
    painter->drawPath(path);
}