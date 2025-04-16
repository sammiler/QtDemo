#include <QApplication>
#include <QWidget>
#include <QShortcut>
#include <QKeySequence>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>

// 一个简单的自定义窗口类
class MyWindow : public QWidget {
    Q_OBJECT // 必须包含 Q_OBJECT 宏以支持信号和槽等元对象特性

public:
    MyWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("QObject Parent-Child Example");
        resize(300, 200);

        QVBoxLayout *layout = new QVBoxLayout(this); // 将布局设置为窗口的子对象

        QPushButton *button = new QPushButton("Close Window", this); // 将按钮设置为窗口的子对象
        layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, &MyWindow::close); // 点击按钮关闭窗口

        // --- QShortcut 示例 ---
        // 创建一个快捷键 Ctrl+P
        // *** 关键点：将 'this' (即 MyWindow 实例) 作为 QShortcut 的父对象 ***
        QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+P"), this);

        // 连接快捷键的 activated() 信号到一个槽函数 (这里使用 lambda 表达式)
        connect(shortcut, &QShortcut::activated, this, [=]() {
            qDebug() << "Shortcut Ctrl+P activated! The shortcut object is:" << shortcut;
            // 你可以在这里执行快捷键对应的操作
        });

        // (可选) 连接快捷键的 destroyed() 信号，以便观察它何时被销毁
        connect(shortcut, &QObject::destroyed, [=](QObject *obj) {
            qDebug() << "Shortcut object" << obj << "is being destroyed because its parent (the window) is being destroyed.";
        });

         qDebug() << "Window and shortcut created. Shortcut's parent:" << shortcut->parent();
    }

    ~MyWindow() override {
        qDebug() << "MyWindow destructor called. Window is being destroyed.";
        // 注意：我们不需要在这里手动 delete shortcut，Qt会处理
    }
};

#include "main.moc" // 如果使用 MOC (Meta-Object Compiler)，需要包含 moc 文件

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWindow *window = new MyWindow(); // 在堆上创建窗口
    window->setAttribute(Qt::WA_DeleteOnClose); // 设置窗口关闭时自动删除 window 对象
    window->show();

    qDebug() << "Starting event loop...";
    int result = app.exec(); // 进入 Qt 事件循环
    qDebug() << "Event loop finished.";

    // 当 app.exec() 返回后，如果窗口设置了 WA_DeleteOnClose 并且已被关闭，
    // window 对象会被删除。由于 shortcut 是 window 的子对象，它也会被自动删除。
    // 如果没有设置 WA_DeleteOnClose，程序退出时 QApplication 的析构函数
    // 也可能触发顶层窗口的删除，进而删除子对象。

    return result;
}