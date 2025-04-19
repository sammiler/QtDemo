#ifndef QCARDLAYOUT_H
#define QCARDLAYOUT_H

#include <QWidget>
#include <QLayout>
#include <QLayoutItem>
#include <QList>

class QCardLayout : public QLayout
{
    Q_OBJECT
public:
    explicit QCardLayout(QWidget *parent = nullptr);
    ~QCardLayout();

    void addItem(QLayoutItem *item) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    void setGeometry(const QRect &rect) override;

private:
    QList<QLayoutItem*> list;
};

#endif // QCARDLAYOUT_H