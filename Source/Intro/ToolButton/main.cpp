//
// Created by sammiler on 2025/4/17.
//
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QStyle>
#include <QHBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;

    // 创建工具栏
    const auto toolBar = new QToolBar("ToolBar");
    mainWindow.addToolBar(toolBar);

    // 创建一个工具按钮
    const auto toolButton = new QToolButton();
    toolButton->setText("工具按钮");
    toolButton->setIcon(QIcon::fromTheme("document-open")); // 使用主题图标，也可以用本地路径
    toolButton->setToolTip("这是一个带图标和菜单的工具按钮");

    // 设置按钮样式：图标+文字在旁边
    toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    // 设置图标大小
    toolButton->setIconSize(QSize(24, 24));

    // 设置自动浮起
    toolButton->setAutoRaise(true);

    // 设置弹出菜单
    QMenu *menu = new QMenu(toolButton);
    menu->addAction("菜单项 1");
    menu->addAction("菜单项 2");
    toolButton->setMenu(menu);

    // 设置弹出模式
    toolButton->setPopupMode(QToolButton::MenuButtonPopup);

    // 设置箭头图标（覆盖原图标）
    toolButton->setArrowType(Qt::DownArrow);

    // 将这个按钮放入工具栏
    toolBar->addWidget(toolButton);

    // 再添加几个不同模式的 QToolButton 以展示全部样式
    auto makeToolButton = [](const QString &text, Qt::ToolButtonStyle style, QToolButton::ToolButtonPopupMode popupMode) {
        QToolButton *btn = new QToolButton();
        btn->setText(text);
        btn->setIcon(QIcon::fromTheme("edit-paste"));
        btn->setIconSize(QSize(24, 24));
        btn->setToolButtonStyle(style);
        btn->setPopupMode(popupMode);
        btn->setAutoRaise(true);

        QMenu *menu = new QMenu(btn);
        menu->addAction("菜单项 A");
        menu->addAction("菜单项 B");
        btn->setMenu(menu);

        return btn;
    };

    toolBar->addWidget(makeToolButton("延迟弹出", Qt::ToolButtonTextUnderIcon, QToolButton::DelayedPopup));
    toolBar->addWidget(makeToolButton("即时弹出", Qt::ToolButtonIconOnly, QToolButton::InstantPopup));
    toolBar->addWidget(makeToolButton("只文本", Qt::ToolButtonTextOnly, QToolButton::MenuButtonPopup));

    mainWindow.resize(600, 150);
    mainWindow.show();
    return QApplication::exec();
}
