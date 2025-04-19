#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QStyle>

class GridWindow : public QMainWindow {
    Q_OBJECT
public:
    GridWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("QGridLayout Demo");
        resize(400, 300);

        // Create central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create grid layout
        QGridLayout *layout = new QGridLayout();
        layout->setHorizontalSpacing(10);
        layout->setVerticalSpacing(10);
        layout->setContentsMargins(10, 10, 10, 10);

        // Create widgets
        QLabel *imageLabel = new QLabel(centralWidget);
        QLineEdit *userLineEdit = new QLineEdit(centralWidget);
        QLineEdit *passwordLineEdit = new QLineEdit(centralWidget);
        QCheckBox *rememberCheckBox = new QCheckBox(centralWidget);
        QCheckBox *autoLoginCheckBox = new QCheckBox(centralWidget);
        QPushButton *loginButton = new QPushButton(centralWidget);
        QPushButton *registerButton = new QPushButton(centralWidget);
        QPushButton *forgotButton = new QPushButton(centralWidget);

        // Configure widgets
        loginButton->setFixedHeight(30);
        userLineEdit->setFixedWidth(200);
        passwordLineEdit->setFixedWidth(200);

        // Set icon using Qt built-in icon
        QPixmap pixmap = style()->standardPixmap(QStyle::SP_MessageBoxInformation);
        imageLabel->setFixedSize(90, 90);
        imageLabel->setPixmap(pixmap);
        imageLabel->setScaledContents(true);

        // Set text and properties
        userLineEdit->setPlaceholderText(QStringLiteral("QQ号码/手机/邮箱"));
        passwordLineEdit->setPlaceholderText(QStringLiteral("密码"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        rememberCheckBox->setText(QStringLiteral("记住密码"));
        autoLoginCheckBox->setText(QStringLiteral("自动登录"));
        loginButton->setText(QStringLiteral("登录"));
        registerButton->setText(QStringLiteral("注册账号"));
        forgotButton->setText(QStringLiteral("找回密码"));

        // Add widgets to layout
        layout->addWidget(imageLabel, 0, 0, 3, 1); // Avatar: 3 rows, 1 column
        layout->addWidget(userLineEdit, 0, 1, 1, 2); // Username: 1 row, 2 columns
        layout->addWidget(registerButton, 0, 4); // Register button
        layout->addWidget(passwordLineEdit, 1, 1, 1, 2); // Password: 1 row, 2 columns
        layout->addWidget(forgotButton, 1, 4); // Forgot button
        layout->addWidget(rememberCheckBox, 2, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter); // Remember: left aligned
        layout->addWidget(autoLoginCheckBox, 2, 2, 1, 1, Qt::AlignRight | Qt::AlignVCenter); // Auto-login: right aligned
        layout->addWidget(loginButton, 3, 1, 1, 2); // Login button: 1 row, 2 columns

        // Apply layout to central widget
        centralWidget->setLayout(layout);

        // Ensure layout is applied
        layout->activate();
        centralWidget->update();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GridWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"