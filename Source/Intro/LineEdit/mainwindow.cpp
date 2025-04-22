//
// Created by sammiler on 2025/4/17.
//

#include "mainwindow.h"

#include <QHBoxLayout>
#include <QAction>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // ========== 1. Echo 模式 ==========
    QGroupBox *echoGroup = new QGroupBox("Echo Mode 示例");
    QVBoxLayout *echoLayout = new QVBoxLayout(echoGroup);

    QLineEdit *pNormalLineEdit = new QLineEdit(this);
    QLineEdit *pNoEchoLineEdit = new QLineEdit(this);
    QLineEdit *pPasswordLineEdit = new QLineEdit(this);
    QLineEdit *pPasswordEchoOnEditLineEdit = new QLineEdit(this);

    pNormalLineEdit->setPlaceholderText("Normal");
    pNoEchoLineEdit->setPlaceholderText("NoEcho");
    pPasswordLineEdit->setPlaceholderText("Password");
    pPasswordEchoOnEditLineEdit->setPlaceholderText("PasswordEchoOnEdit");

    pNormalLineEdit->setEchoMode(QLineEdit::Normal);
    pNoEchoLineEdit->setEchoMode(QLineEdit::NoEcho);
    pPasswordLineEdit->setEchoMode(QLineEdit::Password);
    pPasswordEchoOnEditLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    echoLayout->addWidget(pNormalLineEdit);
    echoLayout->addWidget(pNoEchoLineEdit);
    echoLayout->addWidget(pPasswordLineEdit);
    echoLayout->addWidget(pPasswordEchoOnEditLineEdit);

    mainLayout->addWidget(echoGroup);

    // ========== 2. 搜索框 ==========
    QGroupBox *searchGroup = new QGroupBox("搜索框示例");
    QVBoxLayout *searchLayout = new QVBoxLayout(searchGroup);

    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setPlaceholderText(QStringLiteral("请输入搜索内容"));

    QAction *pLeadingAction = new QAction(this);
    pLeadingAction->setIcon(QIcon(":/Images/leading"));  // 可替换为本地路径
    m_pLineEdit->addAction(pLeadingAction, QLineEdit::LeadingPosition);

    QAction *pTrailingAction = m_pLineEdit->addAction(QIcon(":/Images/trailing"), QLineEdit::TrailingPosition);
    connect(pTrailingAction, &QAction::triggered, this, &MainWindow::onSearch);

    m_pLabel = new QLabel(this);

    searchLayout->addWidget(m_pLineEdit);
    searchLayout->addWidget(m_pLabel);

    mainLayout->addWidget(searchGroup);

    // ========== 3. 验证器 ==========
    QGroupBox *validatorGroup = new QGroupBox("验证器示例");
    QVBoxLayout *validatorLayout = new QVBoxLayout(validatorGroup);

    QLineEdit *pIntLineEdit = new QLineEdit(this);
    QLineEdit *pDoubleLineEdit = new QLineEdit(this);
    QLineEdit *pValidatorLineEdit = new QLineEdit(this);

    pIntLineEdit->setPlaceholderText("整形 (1-99)");
    pDoubleLineEdit->setPlaceholderText("浮点型 (-360 ~ 360)");
    pValidatorLineEdit->setPlaceholderText("字母和数字");

    QIntValidator *pIntValidator = new QIntValidator(1, 99, this);
    QDoubleValidator *pDoubleValidator = new QDoubleValidator(-360, 360, 2, this);
    QRegExpValidator *pRegExpValidator = new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$"), this);

    pIntLineEdit->setValidator(pIntValidator);
    pDoubleLineEdit->setValidator(pDoubleValidator);
    pValidatorLineEdit->setValidator(pRegExpValidator);

    validatorLayout->addWidget(pIntLineEdit);
    validatorLayout->addWidget(pDoubleLineEdit);
    validatorLayout->addWidget(pValidatorLineEdit);

    mainLayout->addWidget(validatorGroup);

    // ========== 4. 输入掩码 ==========
    QGroupBox *maskGroup = new QGroupBox("输入掩码示例");
    QVBoxLayout *maskLayout = new QVBoxLayout(maskGroup);

    QLineEdit *pIPLineEdit = new QLineEdit(this);
    QLineEdit *pMACLineEdit = new QLineEdit(this);
    QLineEdit *pDateLineEdit = new QLineEdit(this);
    QLineEdit *pLicenseLineEdit = new QLineEdit(this);

    pIPLineEdit->setInputMask("000.000.000.000;_");
    pMACLineEdit->setInputMask("HH:HH:HH:HH:HH:HH;_");
    pDateLineEdit->setInputMask("0000-00-00");
    pLicenseLineEdit->setInputMask(">AAAAA-AAAAA-AAAAA-AAAAA-AAAAA;#");

    pIPLineEdit->setPlaceholderText("IP 地址");
    pMACLineEdit->setPlaceholderText("MAC 地址");
    pDateLineEdit->setPlaceholderText("日期");
    pLicenseLineEdit->setPlaceholderText("License 密钥");

    maskLayout->addWidget(pIPLineEdit);
    maskLayout->addWidget(pMACLineEdit);
    maskLayout->addWidget(pDateLineEdit);
    maskLayout->addWidget(pLicenseLineEdit);

    mainLayout->addWidget(maskGroup);

    // 设置主窗口
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("QLineEdit 用法大全");
    resize(500, 700);
}

void MainWindow::onSearch(bool)
{
    QString strText = m_pLineEdit->text();
    m_pLabel->setText(QStringLiteral("输入内容为：%1").arg(strText));
}

