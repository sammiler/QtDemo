#include "mainwindow.h"
#include <QDebug>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto pLayout = new QHBoxLayout();
    m_pButtonGroup = new QButtonGroup(this);

    // 设置按钮组为非互斥（即多选）
    m_pButtonGroup->setExclusive(true);

    for (int i = 0; i < 3; ++i) {
        QCheckBox *pCheckBox = new QCheckBox(this);
        pCheckBox->setText(QStringLiteral("切换%1").arg(i + 1));

        pLayout->addWidget(pCheckBox);
        m_pButtonGroup->addButton(pCheckBox);
    }

    pLayout->setSpacing(10);
    pLayout->setContentsMargins(10, 10, 10, 10);
    centralWidget->setLayout(pLayout);

    // 连接信号槽
    connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(onButtonClicked(QAbstractButton*)));
}

void MainWindow::onButtonClicked(QAbstractButton *button)
{
    // 当前点击的按钮
    qDebug() << QString("Clicked Button : %1").arg(button->text());

    // 遍历按钮组中的按钮，输出选中状态
    const auto list = m_pButtonGroup->buttons();
    for (const auto &pCheckBox : list) {
        QString strStatus = pCheckBox->isChecked() ? "Checked" : "Unchecked";
        qDebug() << QString("Button : %1 is %2").arg(pCheckBox->text()).arg(strStatus);
    }
}
