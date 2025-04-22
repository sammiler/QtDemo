#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>

// Forward declarations
class QLabel;
class QPushButton;
class QVBoxLayout;

class CustomDialog final : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDialog(const QString &message, QWidget *parent = nullptr);
    ~CustomDialog() override;

private slots:
    void onCloseButtonClicked(); // Optional: Custom close logic if needed

private:
    QLabel *messageLabel;
    QPushButton *closeButton;
    QVBoxLayout *mainLayout;
};

#endif // CUSTOMDIALOG_H