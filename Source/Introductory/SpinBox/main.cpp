//
// Created by sammiler on 2025/4/17.
//
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDebug>
#include <QWidget>
#include <QRegExp>

// 自定义 IconSizeSpinBox
class IconSizeSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit IconSizeSpinBox(QWidget *parent = nullptr) : QSpinBox(parent) {}

protected:
    int valueFromText(const QString &text) const override {
        QRegExp regExp(tr("(\\d+)(\\s*[xX]\\s*\\d+)?"));
        if (regExp.exactMatch(text)) {
            return regExp.cap(1).toInt();
        }
        return 0;
    }

    QString textFromValue(const int value) const override {
        return tr("%1 x %1").arg(value);
    }
};

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // 基本 SpinBox 使用
        QSpinBox *pSpinBox = new QSpinBox(this);
        pSpinBox->setRange(20, 200);
        pSpinBox->setSingleStep(10);
        pSpinBox->setValue(150);
        pSpinBox->setPrefix("$ ");
        pSpinBox->setSuffix(" %");
        pSpinBox->setWrapping(true);
        layout->addWidget(new QLabel("基本 QSpinBox 示例:"));
        layout->addWidget(pSpinBox);

        connect(pSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=](int value){
                qDebug() << "Value:" << value;
                qDebug() << "Text:" << pSpinBox->text();
            });

        connect(pSpinBox, static_cast<void(QSpinBox::*)(const QString &)>(&QSpinBox::valueChanged),
            [=](const QString &text){
                qDebug() << "Text Value:" << text;
                qDebug() << "Clean Text:" << pSpinBox->cleanText();
            });

        // 特殊文本值
        QSpinBox *zoomSpinBox = new QSpinBox(this);
        zoomSpinBox->setRange(0, 1000);
        zoomSpinBox->setSingleStep(10);
        zoomSpinBox->setSuffix("%");
        zoomSpinBox->setSpecialValueText(tr("Automatic"));
        zoomSpinBox->setValue(0);
        layout->addWidget(new QLabel("特殊文本值 (最小值显示 Automatic):"));
        layout->addWidget(zoomSpinBox);

        // 自定义文本转换
        IconSizeSpinBox *iconSizeSpinBox = new IconSizeSpinBox(this);
        iconSizeSpinBox->setRange(16, 128);
        iconSizeSpinBox->setSingleStep(16);
        iconSizeSpinBox->setValue(32);
        layout->addWidget(new QLabel("自定义文本转换 (例如 64 x 64):"));
        layout->addWidget(iconSizeSpinBox);

        // QDoubleSpinBox 精度设置
        QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(this);
        doubleSpinBox->setRange(0, 20);
        doubleSpinBox->setDecimals(3);
        doubleSpinBox->setSingleStep(0.005);
        layout->addWidget(new QLabel("QDoubleSpinBox (精度 3，小步长 0.005):"));
        layout->addWidget(doubleSpinBox);

        connect(doubleSpinBox, static_cast<void(QDoubleSpinBox::*)(const QString &)>(&QDoubleSpinBox::valueChanged),
            [=](const QString &text){
                qDebug() << "Double SpinBox Text:" << text;
            });

        setLayout(layout);
        setWindowTitle("QSpinBox/QDoubleSpinBox 示例");
        resize(300, 300);
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
