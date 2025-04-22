#ifndef PROGRESSBARDELEGATE_H
#define PROGRESSBARDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QStyleOptionProgressBar>
#include <QProgressBar> // 虽然不创建 QProgressBar 对象，但需要其定义
#include <QApplication> // 需要 QApplication::style()
#include <QStyle> // 需要 QStyle

#include "TableModel.h" // 包含模型头文件以访问列定义和可能需要的角色 (Qt::UserRole)

class ProgressBarDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ProgressBarDelegate(QObject *parent = nullptr);
    ~ProgressBarDelegate() override;

    // 重写 paint 方法来绘制进度条
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // 对于进度条，通常不需要自定义 sizeHint，除非你想改变行的默认高度来适应进度条
    // QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // PROGRESSBARDELEGATE_H