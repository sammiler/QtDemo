#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <qmath.h>

class CoordinateWidget : public QWidget {
public:
    CoordinateWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setMinimumSize(600, 400); // 设置窗口最小尺寸
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿

        // 保存初始状态
        painter.save();

        // 1. 默认坐标系：直接绘制（逻辑坐标 = 物理坐标）
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::NoBrush);
        painter.drawText(10, 20, "1. Default Coordinate System");
        painter.drawRect(QRect(50, 30, 80, 60)); // 矩形
        painter.drawEllipse(QRect(50, 100, 80, 60)); // 椭圆

        // 2. 世界变换：平移 + 缩放
        painter.save();
        painter.translate(200, 0); // 平移到 (200, 0)
        painter.scale(1.5, 1.5); // 放大 1.5 倍
        painter.setPen(Qt::red);
        painter.drawText(10, 20, "2. Translated + Scaled");
        painter.drawRect(QRect(50, 30, 80, 60));
        painter.drawEllipse(QRect(50, 100, 80, 60));
        painter.restore();

        // 3. 世界变换：旋转 + 剪切
        painter.save();
        painter.translate(400, 0); // 平移到 (400, 0)
        painter.rotate(45); // 顺时针旋转 45 度
        painter.shear(0.2, 0.2); // 轻微剪切
        painter.setPen(Qt::green);
        painter.drawText(10, 20, "3. Rotated + Sheared");
        painter.drawRect(QRect(50, 30, 80, 60));
        painter.drawEllipse(QRect(50, 100, 80, 60));
        painter.restore();

        // 4. 窗口-视口转换：自定义逻辑坐标
        painter.save();
        // 设置窗口：逻辑坐标 (-50, -50, 100, 100)
        painter.setWindow(QRect(-50, -50, 100, 100));
        // 设置视口：物理坐标 (50, 200, 200, 200)，保持正方形
        int side = qMin(width(), height()) / 2;
        int x = 50;
        int y = 200;
        painter.setViewport(x, y, side, side);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::yellow);
        painter.drawText(-40, -40, "4. Window-Viewport");
        painter.drawRect(QRect(-25, -25, 50, 50)); // 逻辑坐标中的正方形
        painter.drawEllipse(QRect(-25, 25, 50, 50)); // 逻辑坐标中的圆
        painter.restore();

        // 5. 组合变换：窗口-视口 + 世界变换
        painter.save();
        painter.setWindow(QRect(-50, -50, 100, 100));
        painter.setViewport(0, 0, side, side);
        painter.translate(10, 10); // 逻辑坐标中的平移
        painter.rotate(30); // 逻辑坐标中的旋转
        painter.setPen(Qt::magenta);
        painter.setBrush(Qt::cyan);
        painter.drawText(-40, -40, "5. Window-Viewport + Transform");
        painter.drawRect(QRect(-25, -25, 50, 50));
        painter.drawEllipse(QRect(-25, 25, 50, 50));
        painter.restore();

        // 恢复初始状态
        painter.restore();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CoordinateWidget widget;
    widget.setWindowTitle("QPainter Coordinate Transformations");
    widget.show();
    return QApplication::exec();
}