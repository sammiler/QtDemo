#include "QBorderLayout.h"

QBorderLayout::QBorderLayout(QWidget *parent, int margin, int spacing)
    : QLayout(parent)
{
    setContentsMargins(margin, margin, margin, margin);
    setSpacing(spacing);
}

QBorderLayout::QBorderLayout(int spacing)
{
    setSpacing(spacing);
}

QBorderLayout::~QBorderLayout()
{
    while (!list.isEmpty()) {
        ItemWrapper *wrapper = list.takeFirst();
        delete wrapper->item;
        delete wrapper;
    }
}

void QBorderLayout::addItem(QLayoutItem *item)
{
    add(item, West);
}

void QBorderLayout::addWidget(QWidget *widget, Position position)
{
    add(new QWidgetItem(widget), position);
}

Qt::Orientations QBorderLayout::expandingDirections() const
{
    return Qt::Horizontal | Qt::Vertical;
}

bool QBorderLayout::hasHeightForWidth() const
{
    return false;
}

int QBorderLayout::count() const
{
    return list.size();
}

QLayoutItem *QBorderLayout::itemAt(int index) const
{
    ItemWrapper *wrapper = list.value(index);
    return wrapper ? wrapper->item : nullptr;
}

QSize QBorderLayout::minimumSize() const
{
    return calculateSize(MinimumSize);
}

void QBorderLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);

    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(left, top, -right, -bottom);

    int northHeight = 0;
    int southHeight = 0;
    int westWidth = 0;
    int eastWidth = 0;

    // First pass: Calculate North and South heights
    for (ItemWrapper *wrapper : list) {
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == North) {
            QSize size = item->sizeHint();
            item->setGeometry(QRect(effectiveRect.x(), effectiveRect.y() + northHeight,
                                    effectiveRect.width(), size.height()));
            northHeight += size.height() + spacing();
        } else if (position == South) {
            QSize size = item->sizeHint();
            southHeight += size.height() + spacing();
            item->setGeometry(QRect(effectiveRect.x(),
                                    effectiveRect.y() + effectiveRect.height() - southHeight,
                                    effectiveRect.width(), size.height()));
        }
    }

    // Second pass: Calculate West, East, and Center
    int centerHeight = effectiveRect.height() - northHeight - southHeight;
    for (ItemWrapper *wrapper : list) {
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == West) {
            QSize size = item->sizeHint();
            item->setGeometry(QRect(effectiveRect.x() + westWidth,
                                    effectiveRect.y() + northHeight,
                                    size.width(), centerHeight));
            westWidth += size.width() + spacing();
        } else if (position == East) {
            QSize size = item->sizeHint();
            eastWidth += size.width() + spacing();
            item->setGeometry(QRect(effectiveRect.x() + effectiveRect.width() - eastWidth,
                                    effectiveRect.y() + northHeight,
                                    size.width(), centerHeight));
        } else if (position == Center) {
            item->setGeometry(QRect(effectiveRect.x() + westWidth,
                                    effectiveRect.y() + northHeight,
                                    effectiveRect.width() - westWidth - eastWidth,
                                    centerHeight));
        }
    }
}

QSize QBorderLayout::sizeHint() const
{
    return calculateSize(SizeHint);
}

QLayoutItem *QBorderLayout::takeAt(int index)
{
    if (index >= 0 && index < list.size()) {
        ItemWrapper *wrapper = list.takeAt(index);
        QLayoutItem *item = wrapper->item;
        delete wrapper;
        return item;
    }
    return nullptr;
}

void QBorderLayout::add(QLayoutItem *item, Position position)
{
    list.append(new ItemWrapper(item, position));
}

QSize QBorderLayout::calculateSize(SizeType sizeType) const
{
    QSize totalSize;
    int northHeight = 0;
    int southHeight = 0;
    int westWidth = 0;
    int eastWidth = 0;
    int centerWidth = 0;
    int centerHeight = 0;

    for (ItemWrapper *wrapper : list) {
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;
        QSize itemSize = (sizeType == MinimumSize) ? item->minimumSize() : item->sizeHint();

        if (position == North) {
            northHeight += itemSize.height() + spacing();
            totalSize.setWidth(qMax(totalSize.width(), itemSize.width()));
        } else if (position == South) {
            southHeight += itemSize.height() + spacing();
            totalSize.setWidth(qMax(totalSize.width(), itemSize.width()));
        } else if (position == West) {
            westWidth += itemSize.width() + spacing();
            totalSize.setHeight(qMax(totalSize.height(), itemSize.height()));
        } else if (position == East) {
            eastWidth += itemSize.width() + spacing();
            totalSize.setHeight(qMax(totalSize.height(), itemSize.height()));
        } else if (position == Center) {
            centerWidth = itemSize.width();
            centerHeight = itemSize.height();
        }
    }

    totalSize.setWidth(qMax(totalSize.width(), westWidth + centerWidth + eastWidth));
    totalSize.setHeight(qMax(totalSize.height(), northHeight + centerHeight + southHeight));

    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    totalSize += QSize(left + right, top + bottom);

    return totalSize;
}