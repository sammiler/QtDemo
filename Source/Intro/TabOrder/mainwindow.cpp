#include "mainwindow.h"
#include <QDebug> // 需要 qDebug

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 创建控件，以当前窗口为父对象
    m_button1 = new QPushButton(this);
    m_button2 = new QPushButton(this);
    m_button3 = new QPushButton(this);

    m_lineEdit1 = new QLineEdit(this); // 用于显示 "6"
    m_lineEdit2 = new QLineEdit(this); // 用于显示 "4"
    m_lineEdit3 = new QLineEdit(this); // 用于显示 "2"

    // 设置控件上的文本，以对应示例中的数字顺序
    m_button1->setText("1"); // 第一个焦点
    m_lineEdit3->setText("2"); // 第二个焦点
    m_button2->setText("3"); // 第三个焦点
    m_lineEdit2->setText("4"); // 第四个焦点
    m_button3->setText("5"); // 第五个焦点
    m_lineEdit1->setText("6"); // 第六个焦点

    // 创建网格布局
    m_layout = new QGridLayout(this); // 以当前窗口为父对象

    // 将控件添加到布局中，使其视觉上排列
    // 为了与示例效果图和焦点顺序对应，我们将它们按行/列排列：
    // Row 0: Button 1, LineEdit 3
    // Row 1: Button 2, LineEdit 2
    // Row 2: Button 3, LineEdit 1
    m_layout->addWidget(m_button1, 0, 0);   // Row 0, Col 0
    m_layout->addWidget(m_lineEdit3, 0, 1); // Row 0, Col 1

    m_layout->addWidget(m_button2, 1, 0);   // Row 1, Col 0
    m_layout->addWidget(m_lineEdit2, 1, 1); // Row 1, Col 1

    m_layout->addWidget(m_button3, 2, 0);   // Row 2, Col 0
    m_layout->addWidget(m_lineEdit1, 2, 1); // Row 2, Col 1

    // 设置布局到窗口上
    setLayout(m_layout);

    // --- 设置焦点切换顺序 ---
    // 使用 QWidget 的静态方法 setTabOrder
    // setTabOrder(first, second); // 设置 first -> second 的顺序
    // 要形成链条：a -> b -> c -> d，需要调用 setTabOrder(a, b); setTabOrder(b, c); setTabOrder(c, d);

    qDebug() << "Setting tab order: 1 -> 2 -> 3 -> 4 -> 5 -> 6";

    // 1 (pButton1) -> 2 (m_lineEdit3)
    QWidget::setTabOrder(m_button1, m_lineEdit3);

    // 2 (m_lineEdit3) -> 3 (m_button2)  --- 链条现在是 1 -> 2 -> 3
    QWidget::setTabOrder(m_lineEdit3, m_button2);

    // 3 (m_button2) -> 4 (m_lineEdit2) --- 链条现在是 1 -> 2 -> 3 -> 4
    QWidget::setTabOrder(m_button2, m_lineEdit2);

    // 4 (m_lineEdit2) -> 5 (m_button3) --- 链条现在是 1 -> 2 -> 3 -> 4 -> 5
    QWidget::setTabOrder(m_lineEdit2, m_button3);

    // 5 (m_button3) -> 6 (m_lineEdit1) --- 链条现在是 1 -> 2 -> 3 -> 4 -> 5 -> 6
    QWidget::setTabOrder(m_button3, m_lineEdit1);

    // 最终的 Tab 顺序是: m_button1 -> m_lineEdit3 -> m_button2 -> m_lineEdit2 -> m_button3 -> m_lineEdit1

    // --- 扩展示例：使部分控件不可获得焦点 (可选，取消注释查看效果) ---
    // m_button2->setFocusPolicy(Qt::NoFocus);
    // m_lineEdit2->setFocusPolicy(Qt::NoFocus);
    // 如果取消上面两行的注释，Tab 顺序将跳过 Button 2 和 LineEdit 2：
    // 1 -> 2 -> (跳过3) -> (跳过4) -> 5 -> 6
    // setTabOrder 仍然会设置这些控件之间的链条，但因为它们不会接收焦点，所以 Tab 键会直接跳到链条中的下一个可获得焦点的控件。

    // 设置窗口大小，以便看到所有控件
    resize(300, 150);
}

MainWindow::~MainWindow()
{
    // 控件和布局的父对象是当前窗口 (this)，窗口销毁时它们会自动销毁
}