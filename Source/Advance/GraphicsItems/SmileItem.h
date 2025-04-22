// SmileItem.h
#ifndef SMILE_ITEM_H
#define SMILE_ITEM_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPointF>
#include <QPainterPath> // Include if using QPainterPath inside item

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

class SmileItem : public QGraphicsItem
{
public:
    explicit SmileItem(QGraphicsItem *parent = Q_NULLPTR);
    explicit SmileItem(const QRectF &rect, QGraphicsItem *parent = Q_NULLPTR);
    explicit SmileItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = Q_NULLPTR);
    ~SmileItem();

    QRectF rect() const;
    void setRect(const QRectF &rect);
    inline void setRect(qreal x, qreal y, qreal w, qreal h);

    // QGraphicsItem overrides
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:
    void updateRect();

private:
    QRectF m_rect; // Defines the logical rectangle of the smiley, used for scaling and bounding
    mutable QRectF m_boundingRect; // Cached bounding rect

    // 缩放比例
    double m_dScale;

    // 左眼、右眼、嘴的中点 (Calculated relative to item's local origin (0,0))
    QPointF m_leftEyeCenter;
    QPointF m_rightEyecenter;
    QPointF m_smileCenter;

    // 眼睛的宽度、高度 (Calculated based on m_rect and scale)
    double m_dEyeWidth;
    double m_dEyeHeight;

    // 眼球宽度（高和宽相同）(Calculated based on eye size)
    double m_dEyeBallWidth;

    // 嘴的高度、宽度 (Calculated based on m_rect and scale)
    double m_dSmileWidth;
    double m_dSmileHeight;
};

inline void SmileItem::setRect(qreal ax, qreal ay, qreal w, qreal h)
{
    setRect(QRectF(ax, ay, w, h));
}

#endif  //SMILE_ITEM_H