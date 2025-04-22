#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSettings>
#include <QColor>

struct Login {
    QString userName;
    QString password;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    private slots:
        void onSaveLoginClicked();
    void onChangeColorClicked();

private:
    void readSettings();
    void writeSettings();
    void closeEvent(QCloseEvent *event) override;

    const QPointer<QLineEdit> userNameEdit;
    const QPointer<QLineEdit> passwordEdit;
    const QPointer<QPushButton> saveLoginButton;
    const QPointer<QPushButton> changeColorButton;
    const QPointer<QVBoxLayout> mainLayout;
    QList<Login> logins;
    QColor backgroundColor;
};

#endif // MAINWINDOW_H