#include "mainwindow.h"
#include <QCloseEvent>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , userNameEdit(new QLineEdit(this))
    , passwordEdit(new QLineEdit(this))
    , saveLoginButton(new QPushButton("保存登录信息", this))
    , changeColorButton(new QPushButton("更改背景颜色", this))
    , mainLayout(new QVBoxLayout)
    , backgroundColor(Qt::white)
{
    // 创建中心部件
    const QPointer<QWidget> centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    // 设置输入框
    userNameEdit->setPlaceholderText("请输入用户名");
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(userNameEdit);
    mainLayout->addWidget(passwordEdit);

    // 添加按钮
    mainLayout->addWidget(saveLoginButton);
    mainLayout->addWidget(changeColorButton);

    // 设置窗口标题和大小
    setWindowTitle("设置示例");
    resize(400, 300);

    // 连接信号和槽
    connect(saveLoginButton, &QPushButton::clicked, this, &MainWindow::onSaveLoginClicked);
    connect(changeColorButton, &QPushButton::clicked, this, &MainWindow::onChangeColorClicked);

    // 读取设置
    readSettings();
}

MainWindow::~MainWindow() = default;

void MainWindow::onSaveLoginClicked()
{
    const QString userName = userNameEdit->text().trimmed();
    const QString password = passwordEdit->text().trimmed();
    if (!userName.isEmpty() && !password.isEmpty()) {
        logins.append({userName, password});
        writeSettings();
        userNameEdit->clear();
        passwordEdit->clear();
    }
}

void MainWindow::onChangeColorClicked()
{
    backgroundColor = backgroundColor == Qt::white ? Qt::lightGray : Qt::white;
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, backgroundColor);
    setPalette(palette);
    writeSettings();
}

void MainWindow::readSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    backgroundColor = settings.value("backgroundColor", QColor(Qt::white)).value<QColor>();
    settings.endGroup();

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, backgroundColor);
    setPalette(palette);

    settings.beginGroup("Logins");
    const int size = settings.beginReadArray("logins");
    logins.clear();
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        Login login;
        login.userName = settings.value("userName").toString();
        login.password = settings.value("password").toString();
        logins.append(login);
    }
    settings.endArray();
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("backgroundColor", backgroundColor);
    settings.endGroup();

    settings.beginGroup("Logins");
    settings.beginWriteArray("logins");
    for (int i = 0; i < logins.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("userName", logins.at(i).userName);
        settings.setValue("password", logins.at(i).password);
    }
    settings.endArray();
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}