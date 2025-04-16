#include "mainwindow.h"
#include "customdialog.h" // Include the dialog header

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QApplication> // Include for qApp->activeWindow() example

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // --- Basic Window Setup ---
    setWindowTitle(QStringLiteral("主界面 (Main Window)")); // "主界面"
    resize(400, 200);

    // --- Central Widget and Layout ---
    centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);

    // --- Buttons ---
    modalButton = new QPushButton(QStringLiteral("显示模式对话框 (Show Modal Dialog)"), centralWidget);
    nonModalButton = new QPushButton(QStringLiteral("显示非模式对话框 (Show Non-Modal Dialog)"), centralWidget);
    semiModalButton = new QPushButton(QStringLiteral("显示半模式对话框 (Show Semi-Modal Dialog)"), centralWidget);

    layout->addWidget(modalButton);
    layout->addWidget(nonModalButton);
    layout->addWidget(semiModalButton);
    layout->addStretch(); // Add space at the bottom

    setCentralWidget(centralWidget);

    // --- Connections ---
    connect(modalButton, &QPushButton::clicked, this, &MainWindow::showModalDialog);
    connect(nonModalButton, &QPushButton::clicked, this, &MainWindow::showNonModalDialog);
    connect(semiModalButton, &QPushButton::clicked, this, &MainWindow::showSemiModalDialog);

    qDebug() << "MainWindow created.";
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroyed.";
}

// --- Slot Implementations ---

void MainWindow::showModalDialog()
{
    qDebug() << "--- Showing Modal Dialog ---";
    // Modal dialogs are often created on the stack if their result is needed immediately.
    // Alternatively, create with 'new' if complex setup/lifetime management is required.
    CustomDialog dialog(QStringLiteral("这是一个模式对话框。\n它会阻塞父窗口以及其他窗口。\n(This is a Modal Dialog.\nIt blocks the parent and other windows.)"), this);
    dialog.setWindowTitle(QStringLiteral("模式对话框 (Modal Dialog)"));
    dialog.setObjectName("ModalDialogInstance"); // For debug identification

    // Set modality explicitly (though QDialog::exec() implies modality)
    // Qt::ApplicationModal blocks ALL windows in the application.
    dialog.setModal(true); // Or dialog.setWindowModality(Qt::ApplicationModal);

    qDebug() << "Calling dialog.exec()... Execution will pause here.";

    // *********************** KEY CODE ***********************
    // exec() shows the dialog and starts a local event loop.
    // It blocks execution of the calling code until the dialog is closed (accepted/rejected).
    int result = dialog.exec();
    // *********************************************************

    // This code ONLY runs AFTER the modal dialog is closed.
    qDebug() << "Modal dialog closed. Result:" << (result == QDialog::Accepted ? "Accepted" : "Rejected");
    this->setWindowTitle(QStringLiteral("主界面 - 模式对话框已关闭 (Main - Modal Closed)"));
    qDebug() << "可以继续向下执行 (Execution continues).";
    qDebug() << "------------------------------";
}

void MainWindow::showNonModalDialog()
{
    qDebug() << "--- Showing Non-Modal Dialog ---";
    // Non-modal dialogs MUST be created on the heap (using 'new')
    // because the function returns immediately after show(), and the object
    // needs to continue existing.
    CustomDialog *dialog = new CustomDialog(QStringLiteral("这是一个非模式对话框。\n你可以与主窗口或其他窗口交互。\n(This is a Non-Modal Dialog.\nYou can interact with the main window.)"), this); // Parent is still useful for positioning/management
    dialog->setWindowTitle(QStringLiteral("非模式对话框 (Non-Modal Dialog)"));
    dialog->setObjectName("NonModalDialogInstance"); // For debug identification

    // Explicitly set non-modal (this is the default for QDialog, but good practice)
    dialog->setModal(false); // Or dialog->setWindowModality(Qt::NonModal);

    // *********************** KEY CODE ***********************
    // IMPORTANT: For non-modal dialogs created with 'new', manage memory!
    // Qt::WA_DeleteOnClose tells Qt to delete the dialog object automatically
    // when the dialog window is closed (e.g., by clicking the 'X' button or calling close()/accept()/reject()).
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    // show() displays the dialog and returns immediately.
    // The application's main event loop keeps it alive and interactive.
    dialog->show();
    // *********************************************************

    qDebug() << "dialog->show() called. Execution continues immediately.";
    this->setWindowTitle(QStringLiteral("主界面 - 非模式对话框已显示 (Main - Non-Modal Shown)"));
    qDebug() << "---------------------------------";
}

void MainWindow::showSemiModalDialog()
{
    qDebug() << "--- Showing Semi-Modal (Window-Modal) Dialog ---";
    // Semi-modal dialogs also generally need to be created on the heap.
    CustomDialog *dialog = new CustomDialog(QStringLiteral("这是一个半模式(窗口模式)对话框。\n它只阻塞父窗口(主界面)。\n你可以与其他独立窗口(如果有)交互。\n(This is a Semi-Modal (Window-Modal) Dialog.\nIt only blocks its parent window (MainWindow).\nYou can interact with other independent windows if any.)"), this); // Parent is CRUCIAL here
    dialog->setWindowTitle(QStringLiteral("半模式对话框 (Semi-Modal Dialog)"));
    dialog->setObjectName("SemiModalDialogInstance"); // For debug identification

    // *********************** KEY CODE ***********************
    // Set window modality to WindowModal. This makes the dialog modal
    // ONLY with respect to its parent window (and the parent's ancestors).
    dialog->setWindowModality(Qt::WindowModal);

    // Again, manage memory for dialogs created with 'new' and shown with 'show()'.
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    // Use show() for window-modal dialogs, not exec().
    dialog->show();
    // *********************************************************

    qDebug() << "dialog->show() called. Execution continues immediately.";
    this->setWindowTitle(QStringLiteral("主界面 - 半模式对话框已显示 (Main - Semi-Modal Shown)"));
    qDebug() << "-------------------------------------";

    // Example: Try interacting with the main window - it should be blocked.
    // If you had another independent top-level window, it would remain interactive.
}