#ifndef HTMLDELEGATE_H
#define HTMLDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QStyle>
#include <QWidget> // For QStyleOptionViewItem::widget


class HtmlDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit HtmlDelegate(QObject *parent = nullptr);
    ~HtmlDelegate() override;

    // 重写 paint 方法来实现自定义绘制
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // 重写 sizeHint 方法，以便委托可以告诉视图它需要多少空间
    // 这对于包含图片或复杂布局的 HTML 很重要
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // HTMLDELEGATE_H