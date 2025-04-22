#include "mainwindow.h"
#include <QWidget>
#include <QDebug>
#include <QAbstractButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *pLayout = new QHBoxLayout();
    m_pButtonGroup = new QButtonGroup(this);

    // 设置互斥（单选）
    m_pButtonGroup->setExclusive(true);

    for (int i = 0; i < 3; ++i) {
        QRadioButton *pButton = new QRadioButton(this);
        pButton->setText(QStringLiteral("切换%1").arg(i + 1));

        pLayout->addWidget(pButton);
        m_pButtonGroup->addButton(pButton);
    }

    pLayout->setSpacing(10);
    pLayout->setContentsMargins(10, 10, 10, 10);
    centralWidget->setLayout(pLayout);

    connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(onButtonClicked(QAbstractButton*)));
}

void MainWindow::onButtonClicked(QAbstractButton *button)
{
    // 当前点击的按钮
    qDebug() << QString("Clicked Button : %1").arg(button->text());

    // 遍历所有按钮并打印状态
    const auto buttonList = m_pButtonGroup->buttons();
    for (const auto &pButton : buttonList) {
        QString strStatus = pButton->isChecked() ? "Checked" : "Unchecked";
        qDebug() << QString("Button : %1 is %2").arg(pButton->text()).arg(strStatus);
    }
}
