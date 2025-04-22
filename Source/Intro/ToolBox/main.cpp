#include <QApplication>
#include <QToolBox>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPixmap>

class ToolBox : public QToolBox
{
    Q_OBJECT

public:
    ToolBox(QWidget *parent = nullptr)
        : QToolBox(parent)
    {
        initUI();

        // 连接信号槽
        connect(this, &QToolBox::currentChanged, this, &ToolBox::onCurrentChanged);
    }

private:
    void initUI() {
        struct User {
            bool bVIP;        // 会员
            QString strName;  // 名字
            QString strIcon;  // 图像
            QString strDesc;  // 个人说明
        } user[3][5] = {
            {
                {true, QStringLiteral("香香公主"), ":/images/1.jpg", QStringLiteral("金庸笔下的第一美女")},
                {true, QStringLiteral("小龙女"), ":/images/2.jpg", QStringLiteral("玉女心经")},
                {true, QStringLiteral("王语嫣"), ":/images/3.jpg", QStringLiteral("熟读各派武学秘笈")},
                {false, QStringLiteral("赵敏"), ":/images/4.jpg", QStringLiteral("大元第一美人")},
                {false, QStringLiteral("周芷若"), ":/images/5.jpg", QStringLiteral("光复汉家河山，光大峨嵋")}
            },
            {
                {true, QStringLiteral("萧峰"), ":/images/6.jpg", QStringLiteral("丐帮帮主 - 智勇双全、胆略过人、豪迈飒爽")},
                {true, QStringLiteral("令狐冲"), ":/images/8.jpg", QStringLiteral("独孤九剑")},
                {true, QStringLiteral("杨过"), ":/images/9.jpg", QStringLiteral("黯然销魂掌")},
                {false, QStringLiteral("郭靖"), ":/images/7.jpg", QStringLiteral("降龙十八掌")},
                {false, QStringLiteral("胡一刀"), ":/images/10.jpg", QStringLiteral("辽东大侠")}
            },
            {
                {true, QStringLiteral("金轮法王"), ":/images/11.jpg", QStringLiteral("龙象般若功")},
                {true, QStringLiteral("丁春秋"), ":/images/13.jpg", QStringLiteral("星宿老仙，法力无边")},
                {false, QStringLiteral("裘千仞"), ":/images/12.jpg", QStringLiteral("铁掌水上飘")},
                {false, QStringLiteral("成昆"), ":/images/14.jpg", QStringLiteral("混元霹雳手")},
                {false, QStringLiteral("李莫愁"), ":/images/15.jpg", QStringLiteral("冰魄银针，杀人如麻")}
            }
        };

        QStringList groupList;
        groupList << QStringLiteral("大美女") << QStringLiteral("大英雄") << QStringLiteral("大恶人");

        // 初始化列表
        for (int i = 0; i < 3; ++i) {
            QGroupBox *pGroupBox = new QGroupBox(this);
            QVBoxLayout *pLayout = new QVBoxLayout(pGroupBox);

            // 添加好友
            for (int j = 0; j < 5; ++j) {
                QWidget *pWidget = initWidget(user[i][j].bVIP, user[i][j].strName,
                                              user[i][j].strIcon, user[i][j].strDesc);
                pLayout->addWidget(pWidget);
            }
            pLayout->addStretch();
            pLayout->setSpacing(10);
            pLayout->setContentsMargins(10, 10, 10, 10);

            // 添加分组
            addItem(pGroupBox, groupList.at(i));
        }
    }

    QWidget* initWidget(bool bVIP, const QString &name, const QString &icon, const QString &desc) {
        QWidget *pWidget = new QWidget(this);
        QLabel *pPixmapLabel = new QLabel(this);
        QLabel *pNameLabel = new QLabel(this);
        QLabel *pDescLabel = new QLabel(this);

        // 图像 名称 描述
        QPixmap pixmap(icon);
        if (pixmap.isNull()) {
            pPixmapLabel->setText("[Image Missing]");
        } else {
            pPixmapLabel->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio));
        }
        pNameLabel->setText(name);
        pDescLabel->setText(desc);

        // VIP名字为红色；否则，黑色
        pNameLabel->setStyleSheet(QString("color: %1;").arg(bVIP ? "rgb(240, 30, 40)" : "black"));
        pDescLabel->setStyleSheet("color: gray;");

        QVBoxLayout *pVLayout = new QVBoxLayout();
        pVLayout->addStretch();
        pVLayout->addWidget(pNameLabel);
        pVLayout->addWidget(pDescLabel);
        pVLayout->addStretch();
        pVLayout->setSpacing(5);
        pVLayout->setContentsMargins(0, 0, 0, 0);

        QHBoxLayout *pHLayout = new QHBoxLayout();
        pHLayout->addWidget(pPixmapLabel);
        pHLayout->addLayout(pVLayout);
        pHLayout->addStretch();
        pHLayout->setContentsMargins(0, 0, 0, 0);

        pWidget->setLayout(pHLayout);

        return pWidget;
    }

private slots:
    void onCurrentChanged(int index) {
        QString strGroup = itemText(index);
        qDebug() << "Current group changed to:" << strGroup;
    }
};

#include "main.moc" // 必要时包含moc文件

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ToolBox toolBox;
    toolBox.setWindowTitle("金庸武侠人物");
    toolBox.resize(400, 600);
    toolBox.show();

    return app.exec();
}