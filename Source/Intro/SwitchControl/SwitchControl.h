#ifndef SWITCH_CONTROL
#define SWITCH_CONTROL

#include <QWidget>
#include <QTimer>
#include <QColor>     // 需要 QColor
#include <QSize>      // 需要 QSize
#include <QMouseEvent> // 需要 QMouseEvent
#include <QPaintEvent> // 需要 QPaintEvent
#include <QResizeEvent>// 需要 QResizeEvent

class SwitchControl : public QWidget
{
    Q_OBJECT // 需要 Q_OBJECT 宏

    // 使用 Q_PROPERTY 定义属性，方便在 QSS 中使用或使用 Qt 的元对象系统访问
    Q_PROPERTY(bool checked READ isToggled WRITE setToggle NOTIFY toggled)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor) // 添加 getter for backgroundColor
    Q_PROPERTY(QColor checkedColor READ checkedColor WRITE setCheckedColor)     // 添加 getter for checkedColor
    Q_PROPERTY(QColor disabledColor READ disabledColor WRITE setDisabledColor)   // 添加 getter for disabledColor (注意拼写 DisbaledColor -> DisabledColor)
    // 可以添加 Q_PROPERTY 用于 m_thumbColor, m_radius, m_nHeight 等，如果需要在外部访问或样式化

public:
    explicit SwitchControl(QWidget *parent = nullptr); // 使用 nullptr

    // 返回开关状态 - 打开：true 关闭：false
    bool isToggled() const;

    // 设置开关状态 (带动画)
    void setToggle(bool checked);

    // 设置背景颜色
    void setBackgroundColor(QColor color);
    QColor backgroundColor() const { return m_background; } // 添加 getter

    // 设置选中颜色
    void setCheckedColor(QColor color);
    QColor checkedColor() const { return m_checkedColor; } // 添加 getter

    // 设置不可用颜色
    void setDisabledColor(QColor color); // 注意函数名 DisbaledColor -> DisabledColor
    QColor disabledColor() const { return m_disabledColor; } // 添加 getter

    // 设置拇指颜色 (可选，如果想在外部设置)
    void setThumbColor(QColor color) { m_thumbColor = color; update(); }
    QColor thumbColor() const { return m_thumbColor; }

protected:
    // 绘制开关
    void paintEvent(QPaintEvent *event) override; // 使用 override

    // 鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override; // 使用 override

    // 鼠标释放事件 - 切换开关状态、发射toggled()信号
    void mouseReleaseEvent(QMouseEvent *event) override; // 使用 override

    // 大小改变事件
    void resizeEvent(QResizeEvent *event) override; // 使用 override

    // 缺省大小
    QSize sizeHint() const override; // 使用 override
    QSize minimumSizeHint() const override; // 使用 override

signals:
    // 状态改变时，发射信号
    void toggled(bool checked);

private slots:
    // 状态切换时，用于产生滑动效果
    void onTimeout();

private:
    bool m_bChecked;         // 是否选中
    QColor m_background;     // 背景颜色 (关闭状态)
    QColor m_checkedColor;   // 选中颜色 (打开状态)
    QColor m_disabledColor;  // 不可用状态颜色 (通常只影响背景或整体透明度，但代码中也用于拇指颜色)
    QColor m_thumbColor;     // 拇指颜色 (关闭状态)
    qreal m_radius;          // 圆角半径，也是拇指的半径 (高度的一半)
    qreal m_nX;              // 拇指中心 x 坐标，动画时改变
    qreal m_nY;              // 拇指中心 y 坐标，通常是高度中心
    qint16 m_nHeight;        // 开关的建议高度 (也是拇指直径)
    qint16 m_nMargin;        // 外边距
    QTimer m_timer;          // 定时器，用于滑动动画

    // 添加 getter 用于 Q_PROPERTY
    QColor backgroundColor() { return m_background; }
    QColor checkedColor() { return m_checkedColor; }
    QColor disabledColor() { return m_disabledColor; }
};

#endif // SWITCH_CONTROL