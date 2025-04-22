#include "customdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

CustomDialog::CustomDialog(const QString &message, QWidget *parent)
    : QDialog(parent)
{
    // Basic setup
    messageLabel = new QLabel(message, this);
    closeButton = new QPushButton(tr("Close"), this); // "关闭"
    mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(messageLabel);
    mainLayout->addWidget(closeButton);
    setLayout(mainLayout);

    // Connect the close button to the dialog's accept() slot
    // accept() closes the dialog and returns QDialog::Accepted from exec()
    // reject() closes the dialog and returns QDialog::Rejected from exec()
    // close() also works for closing non-modal dialogs shown with show()
    connect(closeButton, &QPushButton::clicked, this, &CustomDialog::accept);

    qDebug() << "CustomDialog created:" << objectName();
}

CustomDialog::~CustomDialog()
{
    qDebug() << "CustomDialog destroyed:" << objectName();
}

void CustomDialog::onCloseButtonClicked()
{
    // You could add custom logic here before closing
    qDebug() << "Close button clicked, accepting dialog:" << objectName();
    accept(); // Or reject(), or close()
}