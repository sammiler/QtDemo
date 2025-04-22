#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QFormLayout>

class FormWindow : public QMainWindow {
    Q_OBJECT
public:
    FormWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("QFormLayout Demo");
        resize(400, 200);

        // Create central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create form layout
        QFormLayout *layout = new QFormLayout();
        layout->setSpacing(10);
        layout->setContentsMargins(10, 10, 10, 10);

        // Create input fields
        QLineEdit *userLineEdit = new QLineEdit(centralWidget);
        QLineEdit *passwordLineEdit = new QLineEdit(centralWidget);
        QLineEdit *verifyLineEdit = new QLineEdit(centralWidget);

        // Configure input fields
        userLineEdit->setFixedWidth(200);
        userLineEdit->setPlaceholderText(QStringLiteral("请输入用户名"));
        passwordLineEdit->setFixedWidth(200);
        passwordLineEdit->setPlaceholderText(QStringLiteral("请输入密码"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        verifyLineEdit->setFixedWidth(200);
        verifyLineEdit->setPlaceholderText(QStringLiteral("请输入验证码"));

        // Add rows to layout
        layout->addRow(QStringLiteral("用户名："), userLineEdit);
        layout->addRow(QStringLiteral("密码："), passwordLineEdit);
        layout->addRow(QStringLiteral("验证码："), verifyLineEdit);

        // Apply layout to central widget
        centralWidget->setLayout(layout);

        // Ensure layout is applied
        layout->activate();
        centralWidget->update();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    FormWindow window;
    window.show();
    
    return app.exec();
}

#include "main.moc"