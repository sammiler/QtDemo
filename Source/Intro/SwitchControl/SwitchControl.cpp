#include "SwitchControl.h"
#include <QPainter>      // 需要 QPainter
#include <QMouseEvent>   // 需要 QMouseEvent (尽管 .h 已包含，这里也包含)
#include <QPainterPath>  // 需要 QPainterPath
#include <QRectF>        // 需要 QRectF
#include <QTimerEvent>   // 虽然用了 QTimer，但没有重写 timerEvent，这个 include 不是必需的
#include <QResizeEvent>  // 虽然用了 resizeEvent，但这个 include 不是必需的，已在 .h 中

// 构造函数
SwitchControl::SwitchControl(QWidget *parent)
    : QWidget(parent),
      m_nHeight(16), // 默认高度 16
      m_bChecked(false), // 默认关闭
      m_radius(m_nHeight / 2.0), // 半径是高度的一半
      m_nMargin(3), // 默认外边距 3
      m_checkedColor(0, 150, 136), // 默认选中颜色 (Qt 颜色)
      m_thumbColor(Qt::white), // 默认拇指颜色 (关闭状态)
      m_disabledColor(190, 190, 190), // 默认不可用颜色
      m_background(190, 190, 190) // 默认背景颜色 (关闭状态) - 修正：原始代码这里是 Qt::black，但通常关闭状态背景是灰色
{
    // 设置鼠标滑过时光标形状为手型
    setCursor(Qt::PointingHandCursor);

    // 初始化 x 坐标，在 resizeEvent 中会重新计算
    m_nX = m_radius; // 初始位置在左边圆的中心 x 坐标
    m_nY = m_radius; // 初始位置在高度中心 y 坐标

    // 设置定时器类型为精确定时器 (可选)
    // m_timer.setTimerType(Qt::PreciseTimer);

    // 连接内部定时器的 timeout 信号到自身的 onTimeout 槽
    // 使用新的信号槽语法
    connect(&m_timer, &QTimer::timeout, this, &SwitchControl::onTimeout);

    // 设置控件的尺寸策略，使其可以根据内容调整大小，并推荐大小
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // 尺寸固定，不随布局拉伸
}

// --- Getter 和 Setter 方法实现 ---

// 返回开关状态
bool SwitchControl::isToggled() const
{
    return m_bChecked;
}

// 设置开关状态并启动动画
void SwitchControl::setToggle(bool checked)
{
    // 只有状态发生改变时才执行
    if (m_bChecked != checked) {
        m_bChecked = checked;
        m_timer.start(10); // 启动定时器，间隔 10ms
        // 注意：这里设置状态会启动动画，但不会发射 toggled 信号。
        // toggled 信号在鼠标释放时发射。如果希望 setToggle 也发射信号，可以在这里添加 emit toggled(m_bChecked);
    }
}

// 设置背景颜色 (关闭状态)
void SwitchControl::setBackgroundColor(QColor color)
{
    m_background = color;
    update(); // 颜色改变后立即更新绘制
}

// 设置选中颜色 (打开状态)
void SwitchControl::setCheckedColor(QColor color)
{
    m_checkedColor = color;
    update(); // 颜色改变后立即更新绘制
}

// 设置不可用颜色 (注意拼写 DisbaledColor -> DisabledColor)
void SwitchControl::setDisabledColor(QColor color) // 修正函数名
{
    m_disabledColor = color;
    update(); // 颜色改变后立即更新绘制
}

// 添加 Q_PROPERTY 对应的 getter 实现
// bool isToggled() const 已在上面实现

// --- 事件处理函数实现 ---

// 绘制开关控件
void SwitchControl::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // 避免编译器警告

    QPainter painter(this); // 在当前控件上创建画家
    painter.setPen(Qt::NoPen); // 不使用画笔绘制轮廓
    painter.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿，使绘制更平滑

    QPainterPath path; // 用于绘制圆角矩形
    QColor background; // 存储绘制背景的颜色
    QColor thumbColor; // 存储绘制拇指的颜色
    qreal dOpacity;    // 存储绘制背景的透明度

    // 根据控件的可用状态 (isEnabled()) 和选中状态 (m_bChecked) 选择颜色和透明度
    if (isEnabled()) { // 可用状态
        if (m_bChecked) { // 打开状态
            background = m_checkedColor; // 背景色使用选中颜色
            thumbColor = m_thumbColor; // 拇指颜色使用默认拇指色 (通常是白色)
            dOpacity = 1.0; // 背景完全不透明
        } else { //关闭状态
            background = m_background; // 背景色使用关闭颜色
            thumbColor = m_thumbColor; // 拇指颜色使用默认拇指色
            dOpacity = 1.0; // 背景完全不透明
        }
    } else {  // 不可用状态
        background = m_background; // 背景色使用关闭颜色
        dOpacity = 0.5; // 不可用时背景半透明 (可调整)
        thumbColor = m_disabledColor; // 拇指颜色使用不可用颜色
    }

    // 绘制大椭圆 (实际上是圆角矩形作为背景)
    painter.setBrush(background); // 设置画刷颜色
    painter.setOpacity(dOpacity); // 设置透明度
    // 添加圆角矩形路径，尺寸为控件减去两倍外边距，圆角半径为 m_radius
    path.addRoundedRect(QRectF(m_nMargin, m_nMargin, width() - 2 * m_nMargin, height() - 2 * m_nMargin), m_radius, m_radius);
    painter.drawPath(path.simplified()); // 绘制路径

    // 绘制小椭圆 (作为可拖动的“拇指”)
    painter.setBrush(thumbColor); // 设置画刷颜色
    painter.setOpacity(1.0); // 拇指完全不透明
    // 绘制椭圆，中心为 (m_nX, m_nY)，宽度和高度都等于控件高度减去两倍外边距（即 m_nHeight）
    // 矩形尺寸为 (宽度, 高度)，左上角坐标为 (中心x - 宽度/2, 中心y - 高度/2)
    // 这里使用了 height() 作为椭圆的直径，这与 m_nHeight 的计算可能不一致，通常应该使用 m_nHeight
    // 修正：使用 m_nHeight 作为直径
    qreal thumbDiameter = m_nHeight; // 拇指直径等于控件设计高度
    painter.drawEllipse(QRectF(m_nX - (thumbDiameter / 2.0), m_nY - (thumbDiameter / 2.0), thumbDiameter, thumbDiameter));
}

// 鼠标按下事件
void SwitchControl::mousePressEvent(QMouseEvent *event)
{
    // 如果控件可用
    if (isEnabled()) {
        // 如果按下的是鼠标左键
        if (event->button() == Qt::LeftButton) {
            event->accept(); // 接受事件，阻止进一步传播
            // 注意：这里只接受事件，实际的状态切换在 mouseReleaseEvent 中处理
        } else {
            event->ignore(); // 忽略非左键事件
        }
    }
}

// 鼠标释放事件 - 切换开关状态、发射toggled()信号
void SwitchControl::mouseReleaseEvent(QMouseEvent *event)
{
    // 如果控件可用
    if (isEnabled()) {
        // 检查事件类型是否是鼠标释放事件，并且是左键释放
        if (event->button() == Qt::LeftButton) { // 检查 event->type() == QMouseEvent::MouseButtonRelease 是多余的
            event->accept(); // 接受事件
            m_bChecked = !m_bChecked; // 切换内部状态
            emit toggled(m_bChecked); // 发射状态改变信号
            m_timer.start(10); // 启动定时器，开始滑动动画
        } else {
            event->ignore(); // 忽略非左键释放事件
        }
    }
}

// 大小改变事件
void SwitchControl::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event); // 避免编译器警告
    // 重新计算拇指的中心坐标
    // m_nX 的初始位置 (关闭状态) 是左边圆的中心 x 坐标
    // m_nY 的位置是高度中心 y 坐标
    // 注意：这里的计算应该基于控件的当前高度，而不是固定的 m_nHeight
    // m_nX 的计算也应该考虑 margin
    qreal thumbDiameter = height() - 2 * m_nMargin; // 拇指直径等于控件高度减去两倍外边距
    m_radius = thumbDiameter / 2.0; // 更新圆角半径和拇指半径

    m_nX = m_bChecked ? (width() - m_radius - m_nMargin) : (m_radius + m_nMargin); // 根据状态计算初始 x 坐标
    m_nY = height() / 2.0; // y 坐标在高度中心

    // 调用基类方法处理大小改变
    // QWidget::resizeEvent(event); // 这里调用基类方法通常不是必需的，除非基类有特殊处理
     update(); // 大小改变后重绘控件
}

// 默认推荐大小
QSize SwitchControl::sizeHint() const
{
    // 返回一个推荐大小，基于设计高度和外边距
    // 推荐宽度是两倍的 (高度 + 外边距)，这样左右状态都有空间显示
    // 推荐高度是 高度 + 两倍外边距
    return QSize(2 * (m_nHeight + m_nMargin), m_nHeight + 2 * m_nMargin);
}

// 最小推荐大小
QSize SwitchControl::minimumSizeHint() const
{
    // 最小大小与推荐大小相同，或者可以设置一个更小的限制
    return sizeHint(); // 在这个控件中，最小大小和推荐大小相同
}

// 槽函数：定时器触发时，更新拇指位置产生滑动效果
void SwitchControl::onTimeout()
{
    qreal targetX = m_bChecked ? (width() - m_radius - m_nMargin) : (m_radius + m_nMargin); // 根据目标状态计算目标 x 坐标
    qreal step = (targetX - m_nX) / 10.0; // 计算每次移动的步长 (可以调整 10.0 控制速度)

    if (qFuzzyIsNull(step)) { // 如果步长非常小（已经接近目标位置）
         m_nX = targetX; // 直接设置为目标位置
         m_timer.stop(); // 停止定时器
    } else {
         m_nX += step; // 移动拇指位置
         // 如果移动超出目标位置，则直接设为目标位置并停止定时器
         if ((step > 0 && m_nX >= targetX) || (step < 0 && m_nX <= targetX)) {
              m_nX = targetX;
              m_timer.stop();
         }
    }

    update(); // 请求重绘控件，显示新的拇指位置
}

// --- Q_PROPERTY 对应的 getter 实现 (已在 .h 中声明，部分已实现) ---
// bool isToggled() const; // 已实现

// 其他 getter 已在 .h 中实现为内联函数或者上面实现
// QColor backgroundColor() const;
// QColor checkedColor() const;
// QColor disabledColor() const;
// QColor thumbColor() const;