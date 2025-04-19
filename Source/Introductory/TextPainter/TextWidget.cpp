#include "TextWidget.h"
#include <QPaintEvent>
#include <QTextOption>
#include <QFontMetrics>

void BasicTextWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QColor(0, 160, 230));

    painter.drawText(rect(), QStringLiteral("一去丶二三里"));
    painter.drawText(100, 100, QStringLiteral("青春不老，奋斗不止！"));
    painter.drawText(QPoint(20, 200), QStringLiteral("纯正开源之美，有趣、好玩、靠谱。。。"));
}

void AlignedTextWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QColor(0, 160, 230));

    painter.drawText(rect(), Qt::AlignCenter, QStringLiteral("一去丶二三里"));
}

void WrappedTextWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QColor(0, 160, 230));

    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WordWrap);

    painter.drawText(rect(), QStringLiteral("青春不老，奋斗不止！-纯正开源之美，有趣、好玩、靠谱。。。"), option);
}

void ElidedTextWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QColor(0, 160, 230));

    const QFontMetrics fm = painter.fontMetrics();
    const QString strText = QStringLiteral("青春不老，奋斗不止！-纯正开源之美，有趣、好玩、靠谱。。。");
    const QString strElidedText = fm.elidedText(strText, Qt::ElideRight, 200, Qt::TextShowMnemonic);

    painter.drawText(rect(), Qt::AlignCenter, strElidedText);
}

void StyledTextWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    QTransform transform;
    transform.rotate(45);

    painter.setPen(QColor(0, 160, 230));

    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(16);
    font.setItalic(true);
    font.setUnderline(true);
    font.setOverline(true);
    font.setCapitalization(QFont::SmallCaps);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 20);

    painter.setFont(font);
    painter.setTransform(transform);

    painter.drawText(rect(), QStringLiteral("一去丶二三里"));
}