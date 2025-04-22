//
// Created by sammiler on 2025/4/17.
//
#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QDebug>

class SliderSpinDemo : public QWidget
{
    Q_OBJECT
public:
    SliderSpinDemo(QWidget *parent = nullptr) : QWidget(parent)
    {
        int nMin = 0;
        int nMax = 200;
        int nSingleStep = 10;

        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *label = new QLabel("QSpinBox 与 QSlider 联动示例：");
        layout->addWidget(label);

        // 微调框
        QSpinBox *pSpinBox = new QSpinBox(this);
        pSpinBox->setMinimum(nMin);
        pSpinBox->setMaximum(nMax);
        pSpinBox->setSingleStep(nSingleStep);

        // 滑动条
        QSlider *pSlider = new QSlider(Qt::Horizontal, this);
        pSlider->setMinimum(nMin);
        pSlider->setMaximum(nMax);
        pSlider->setSingleStep(nSingleStep);
        pSlider->setTickInterval(40);  // 刻度间隔
        pSlider->setTickPosition(QSlider::TicksAbove); // 刻度位置

        // 设置初始值
        pSpinBox->setValue(10);

        // 信号槽连接（双向）
        connect(pSpinBox, SIGNAL(valueChanged(int)), pSlider, SLOT(setValue(int)));
        connect(pSlider, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));

        // 打印调试
        connect(pSlider, &QSlider::valueChanged, this, [](int val){
            qDebug() << "Slider Value:" << val;
        });

        layout->addWidget(pSpinBox);
        layout->addWidget(pSlider);

        // 设置样式表
        QString sliderStyle = R"(
            QSlider::groove:horizontal {
                height: 6px;
                background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                                            stop: 0 rgb(124, 124, 124),
                                            stop: 1.0 rgb(72, 71, 71));
            }
            QSlider::handle:horizontal {
                width: 1px;
                background: rgb(0, 160, 230);
                margin: -6px 0px -6px 0px;
                border-radius: 9px;
            }
        )";
        pSlider->setStyleSheet(sliderStyle);

        setLayout(layout);
        setWindowTitle("SpinBox + Slider 联动示例");
        resize(400, 120);
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SliderSpinDemo window;
    window.show();
    return app.exec();
}
