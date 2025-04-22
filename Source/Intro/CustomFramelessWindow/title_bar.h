#ifndef TITLE_BAR_H
#define TITLE_BAR_H

#include <QWidget>
#include <QLabel>      // 需要 QLabel
#include <QPushButton> // 需要 QPushButton
#include <QMouseEvent> // 需要 QMouseEvent
#include <QEvent>      // 需要 QEvent

class TitleBar : public QWidget
{
    Q_OBJECT // 启用 Qt 元对象系统

public:
    explicit TitleBar(QWidget *parent = nullptr); // 使用 nullptr
    ~TitleBar();

protected:
    // 双击标题栏进行界面的最大化/还原
    void mouseDoubleClickEvent(QMouseEvent *event) override; // 使用 override

    // 进行界面的拖动 (通过 Windows API)
    void mousePressEvent(QMouseEvent *event) override; // 使用 override

    // 设置界面标题与图标 (通过事件过滤器)
    bool eventFilter(QObject *obj, QEvent *event) override; // 使用 override

    private slots:
        // 进行最小化、最大化/还原、关闭操作
        void onClicked();

private:
    // 最大化/还原按钮状态更新
    void updateMaximize();

private:
    QLabel *m_pIconLabel;        // 显示窗口图标
    QLabel *m_pTitleLabel;       // 显示窗口标题
    QPushButton *m_pMinimizeButton; // 最小化按钮
    QPushButton *m_pMaximizeButton; // 最大化/还原按钮
    QPushButton *m_pCloseButton;    // 关闭按钮
};

#endif // TITLE_BAR