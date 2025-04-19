#include "mainwindow.h"
#include <QColor>
#include <QDebug>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 创建不同类型的输入框
    m_standardLineEdit = new QLineEdit(this); // 普通输入框
    m_lineEditWithFilter = new QLineEdit(this); // 使用事件过滤器的输入框
    m_eventFilter = new PasswordEventFilter(this); // 创建事件过滤器对象，父对象为当前窗口
    m_customLineEdit = new PasswordLineEdit(this); // 继承实现的输入框

    // --- 对所有密码框应用基础设置 ---
    // (标准输入框不应用，用于对比)

    // 设置无右键菜单
    m_lineEditWithFilter->setContextMenuPolicy(Qt::NoContextMenu);
    m_customLineEdit->setContextMenuPolicy(Qt::NoContextMenu);

    // 设置无输入时提示信息
    m_standardLineEdit->setPlaceholderText("Standard Input");
    m_lineEditWithFilter->setPlaceholderText("Filtered Password");
    m_customLineEdit->setPlaceholderText("Custom Password");

    // 设置密码效果模式 (字符掩码)
    m_lineEditWithFilter->setEchoMode(QLineEdit::Password);
    m_customLineEdit->setEchoMode(QLineEdit::Password);

    // 设置最大输入长度16位
    m_lineEditWithFilter->setMaxLength(16);
    m_customLineEdit->setMaxLength(16);

    // 可选：设置固定宽度或尺寸策略
    // m_standardLineEdit->setFixedWidth(200);
    // m_lineEditWithFilter->setFixedWidth(200);
    // m_customLineEdit->setFixedWidth(200);

    // 可选：设置字体以避免中文乱码（如果需要，通常在 QApplication 层面设置）
    // QFont font = this->font();
    // font.setFamily("Arial");
    // this->setFont(font);


    // --- 为使用事件过滤器的输入框安装过滤器 ---
    m_lineEditWithFilter->installEventFilter(m_eventFilter);

    // --- 设置布局 ---
    QVBoxLayout *layout = new QVBoxLayout(this); // 以当前窗口为父对象创建垂直布局

    layout->addWidget(new QLabel("Standard:", this));
    layout->addWidget(m_standardLineEdit);

    layout->addWidget(new QLabel("Using Event Filter:", this));
    layout->addWidget(m_lineEditWithFilter);

    layout->addWidget(new QLabel("Using Class Inheritance:", this));
    layout->addWidget(m_customLineEdit);

    layout->addStretch(); // 添加一个伸缩器，将控件推到顶部

    setLayout(layout); // 将布局设置到窗口上

    // 设置窗口大小
    resize(350, 250);

    qDebug() << "MainWindow created with password fields.";
}

MainWindow::~MainWindow()
{
    // 控件、布局和事件过滤器的父对象是当前窗口 (this)，窗口销毁时它们会自动销毁
}