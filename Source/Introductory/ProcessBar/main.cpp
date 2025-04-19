//
// Created by sammiler on 2025/4/17.
//
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QTimer>

class ProgressBarDemo : public QWidget
{
public:
    ProgressBarDemo(QWidget *parent = nullptr) : QWidget(parent)
    {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // 标准进度条
        QProgressBar *normalBar = new QProgressBar(this);
        normalBar->setRange(0, 100);
        normalBar->setValue(50);
        layout->addWidget(normalBar);

        // 反向进度条
        QProgressBar *reverseBar = new QProgressBar(this);
        reverseBar->setRange(0, 100);
        reverseBar->setValue(50);
        reverseBar->setInvertedAppearance(true);
        layout->addWidget(reverseBar);

        // 自定义文本格式，带百分比精度
        QProgressBar *customTextBar = new QProgressBar(this);
        customTextBar->setRange(0, 4800);
        customTextBar->setValue(2000);
        double dProgress = (customTextBar->value() - customTextBar->minimum()) * 100.0
                         / (customTextBar->maximum() - customTextBar->minimum());
        customTextBar->setFormat(QStringLiteral("当前进度为：%1%").arg(QString::number(dProgress, 'f', 1)));
        customTextBar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        layout->addWidget(customTextBar);

        // 繁忙状态进度条（无限加载）
        QProgressBar *busyBar = new QProgressBar(this);
        busyBar->setRange(0, 0);  // 最小值和最大值相同，触发繁忙动画
        layout->addWidget(busyBar);

        setLayout(layout);
        setWindowTitle("QProgressBar 示例");
        resize(400, 200);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProgressBarDemo w;
    w.show();
    return a.exec();
}
