#include "default_escape_dialog.h"

DefaultEscapeDialog::DefaultEscapeDialog(QWidget *parent)
    : QDialog(parent)
{
    // 设置窗口大小
    resize(200, 100);

    // 添加一个标签和标准按钮盒
    QLabel *label = new QLabel("Press Escape or Cancel to Close", this);
    label->setAlignment(Qt::AlignCenter);

    // 添加标准按钮盒 (包含 OK 和 Cancel 按钮)
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // 连接标准按钮盒的信号到对话框的 accept() 和 reject() 槽
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject); // 这是默认行为，Escape 键会触发 reject()

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(buttonBox);
    setLayout(layout);

    qDebug() << "DefaultEscapeDialog created.";
}

DefaultEscapeDialog::~DefaultEscapeDialog()
{
    qDebug() << "DefaultEscapeDialog destroyed.";
}

// 注意：这个类没有重写 keyPressEvent 或 reject()，所以它会展示 QDialog 的默认行为：
// 按下 Escape 键会自动调用 reject() 并关闭对话框。
// 按下 Enter 键会自动点击 default 按钮 (如果有 default 按钮)。