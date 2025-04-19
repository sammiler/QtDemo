#ifndef PARA_BANNER_H
#define PARA_BANNER_H

#include <QWidget>
#include <QBasicTimer>
#include <QString> // Explicitly include QString

class BannerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BannerWidget(QWidget *parent = nullptr); // Use nullptr instead of 0
    ~BannerWidget();

    public slots:
        void setText(const QString &text);

protected:
    // 绘制文本
    void paintEvent(QPaintEvent *event) override; // Use override
    // 定时刷新
    void timerEvent(QTimerEvent *event) override; // Use override

private:
    QBasicTimer m_timer;
    QString m_strText;
    int m_nStep;
};

#endif