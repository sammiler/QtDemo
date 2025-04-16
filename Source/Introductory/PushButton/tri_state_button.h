#ifndef TRISTATEBUTTON_H
#define TRISTATEBUTTON_H

#include <QAbstractButton>
#include <QStyleOptionButton> // Needed for painting states
#include <QPainter>
#include <QStylePainter>
#include <QStyle>
#include <QDebug>
#include <QPushButton>
class A {
    public:
        virtual void a() {}
        virtual void a1() {}
        virtual void a2() {}
    };
    
    class B : public A {
    public:
        using A::a1;  // 显式引入祖父类虚函数
        using A::a2;
        void a() override {}
    };
    
    class C : public B {
    public:
    };
    
class TriStateButton : public QPushButton
{
    Q_OBJECT
    // Custom property to hold the specific check state
    Q_PROPERTY(Qt::CheckState checkState READ checkState WRITE setCheckState NOTIFY checkStateChanged)

public:
    explicit TriStateButton(const QString &text, QWidget *parent = nullptr);
    explicit TriStateButton(QWidget *parent = nullptr); // Constructor without text

    // --- Required Reimplementations ---

    QSize sizeHint() const override;
    // Get/Set the specific tri-state
    Qt::CheckState checkState() const;
    void setCheckState(Qt::CheckState state);

signals:
    // Emitted when the detailed check state changes
    void checkStateChanged(Qt::CheckState newState);

protected:
    virtual void checkStateSet() override;
    // // Called on user click to cycle through states
    virtual void nextCheckState() override;
    void paintEvent(QPaintEvent *) override;
    bool hitButton(const QPoint &pos) const override;


private:
    Qt::CheckState currentCheckState = Qt::Unchecked; // Holds the actual tri-state

    // Helper to update the base class's checked state based on our tri-state
    void updateBaseCheckedState();

    void InitButtonMenu();

};

#endif // TRISTATEBUTTON_H