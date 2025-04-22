#include <QApplication>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QDebug>

// 自定义托盘菜单类
class TrayMenu : public QMenu
{
    Q_OBJECT

public:
    explicit TrayMenu(QWidget *parent = nullptr)
        : QMenu(parent)
    {
        initActions();
    }

    ~TrayMenu() {}

signals:
    void showWindow();

private:
    void initActions()
    {
        // 创建菜单项
        m_pShowAction = new QAction(QIcon(":/icons/open.png"), QStringLiteral("显示"), this);
        m_pSettingAction = new QAction(QIcon(":/icons/setting.png"), QStringLiteral("设置"), this);
        m_pHomePageAction = new QAction(QIcon(":/icons/home.png"), QStringLiteral("登录网页"), this);
        m_pHelpAction = new QAction(QIcon(":/icons/help.png"), QStringLiteral("帮助"), this);
        m_pAboutAction = new QAction(QIcon(":/icons/about.png"), QStringLiteral("关于"), this);
        m_pUpgradeAction = new QAction(QIcon(":/icons/upgrade.png"), QStringLiteral("检查更新"), this);
        m_pQuitAction = new QAction(QIcon(":/icons/quit.png"), QStringLiteral("退出"), this);

        // 添加菜单项
        addAction(m_pShowAction);
        addAction(m_pSettingAction);
        addAction(m_pHomePageAction);
        addSeparator();
        addAction(m_pHelpAction);
        addAction(m_pAboutAction);
        addAction(m_pUpgradeAction);
        addSeparator();
        addAction(m_pQuitAction);

        // 连接信号
        connect(m_pShowAction, &QAction::triggered, this, &TrayMenu::showWindow);
        connect(m_pQuitAction, &QAction::triggered, qApp, &QApplication::quit);
    }

private:
    QAction *m_pShowAction;
    QAction *m_pSettingAction;
    QAction *m_pHomePageAction;
    QAction *m_pHelpAction;
    QAction *m_pAboutAction;
    QAction *m_pUpgradeAction;
    QAction *m_pQuitAction;
};

// 主窗口类
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        // 设置主窗口
        setWindowTitle(QStringLiteral("系统托盘示例"));
        resize(400, 300);

        // 创建系统托盘
        QSystemTrayIcon *pSystemTray = new QSystemTrayIcon(this);
        TrayMenu *pTrayMenu = new TrayMenu(this);

        // 设置系统托盘的上下文菜单
        pSystemTray->setContextMenu(pTrayMenu);

        // 设置系统托盘提示信息和图标
        pSystemTray->setToolTip(QStringLiteral("系统托盘示例"));
        pSystemTray->setIcon(QIcon(":/images/program.png"));

        // 连接信号槽
        connect(pTrayMenu, &TrayMenu::showWindow, this, &MainWindow::showWindow);
        connect(pSystemTray, &QSystemTrayIcon::activated, this, &MainWindow::onActivated);

        // 显示系统托盘
        pSystemTray->show();

        // 显示托盘提示信息
        pSystemTray->showMessage(QStringLiteral("托盘标题"), QStringLiteral("欢迎使用系统托盘！"));
    }

private slots:
    void showWindow()
    {
        showNormal();
        raise();
        activateWindow();
    }

    void onActivated(QSystemTrayIcon::ActivationReason reason)
    {
        switch (reason) {
        case QSystemTrayIcon::Trigger:
            showNormal();
            raise();
            activateWindow();
            break;
        case QSystemTrayIcon::DoubleClick:
            // 可添加双击行为
            break;
        default:
            break;
        }
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}