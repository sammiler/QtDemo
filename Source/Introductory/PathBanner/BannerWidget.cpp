#include <QPainter>
#include <QTimerEvent>
#include <QFont>
#include <QFontMetrics> // Explicitly include QFontMetrics
#include <QPaintEvent> // Explicitly include QPaintEvent
#include "BannerWidget.h"

BannerWidget::BannerWidget(QWidget *parent)
    : QWidget(parent),
      m_nStep(0),
      m_strText(QStringLiteral("一去丶二三里")) // Using fromLocal8Bit for potentially non-ASCII text
{
    setAutoFillBackground(true);

    // 设置文字大小
    QFont newFont = font();
    newFont.setPointSize(newFont.pointSize() + 20);
    setFont(newFont);

    // 启动定时器，每100ms触发一次timerEvent
    m_timer.start(100, this);
}

BannerWidget::~BannerWidget()
{
    // 定时器在对象销毁时通常会自动停止，但显式停止也是安全的
    m_timer.stop();
}

void BannerWidget::setText(const QString &text)
{
    m_strText = text;
    // 文本改变后立即刷新显示
    update();
}

void BannerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 计算文本绘制的起始坐标，使其居中
    QFontMetrics metrics(font());
    int textWidth = metrics.horizontalAdvance(m_strText);
    // 计算文本绘制区域的高度中心
    int textHeightCenter = (height() + metrics.ascent() - metrics.descent()) / 2;

    // 计算第一个字符的起始 x 坐标，使整个文本居中
    int startX = (width() - textWidth) / 2;

    QColor color;
    QPainter painter(this);

    // 设置高质量抗锯齿渲染
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);


    for (int i = 0; i < m_strText.size(); ++i)
    {
        // 根据步长和字符索引计算颜色
        // 使用HSV颜色模型，只改变色调 (Hue)，创造彩虹效果
        int nIndex = (m_nStep + i) % 16; // 16 步长循环色调
        // 色调值范围 0-359，这里映射到 (15-nIndex)*16 的范围
        color.setHsv((15 - nIndex) * 16, 255, 191); // 色调，饱和度，亮度
        painter.setPen(color);

        // 单个字符绘制
        // 使用 drawText(int x, int y, const QString &text) 绘制文本，y 是基线位置
        painter.drawText(startX, textHeightCenter, QString(m_strText[i]));

        // 计算下一个字符的 x 坐标起始点
        startX += metrics.horizontalAdvance(m_strText[i]); // 使用 horizontalAdvance 获取字符宽度
    }
}

void BannerWidget::timerEvent(QTimerEvent *event)
{
    // 检查是否是 m_timer 触发的事件
    if (event->timerId() == m_timer.timerId())
    {
        // 步长加一，用于控制颜色动画
        ++m_nStep;
        // 请求重绘窗口，这将触发 paintEvent
        update();
    }
    else
    {
        // 如果不是我们的定时器事件，传递给基类处理
        QWidget::timerEvent(event);
    }
}