#include "tri_state_button.h" // Include our custom button header
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton> // For standard buttons to control state
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QDebug>
#include <QCheckBox> // To control AutoRepeat
#include <QKeySequence> // For setShortcut

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowTitle("QAbstractButton Inheritance Demo");
    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);

    // --- Create the Custom TriStateButton ---
    TriStateButton *triButton = new TriStateButton("Ro&ck && Roll (Tri-State)", &mainWindow);
    triButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);

    // --- Demonstrate Features ---

    // 1. Icon
    // Use a standard icon for simplicity, otherwise provide your own path
    QIcon okIcon = mainWindow.style()->standardIcon(QStyle::SP_DialogOkButton);
    triButton->setIcon(okIcon);
    triButton->setIconSize(QSize(24, 24)); // Set specific icon size

    // 2. Shortcut (Ctrl+T)
    triButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
    QLabel *shortcutLabel = new QLabel("Custom Shortcut: Ctrl+T", &mainWindow);

    // 3. AutoRepeat Control
    QCheckBox *autoRepeatCheck = new QCheckBox("Enable AutoRepeat", &mainWindow);
    QObject::connect(autoRepeatCheck, &QCheckBox::toggled, triButton, &TriStateButton::setAutoRepeat);

    // 4. Enable/Disable Control
    QPushButton *toggleEnableButton = new QPushButton("Toggle Enabled State", &mainWindow);
    QObject::connect(toggleEnableButton, &QPushButton::clicked, [&]() {
        triButton->setEnabled(!triButton->isEnabled());
        toggleEnableButton->setText(triButton->isEnabled() ? "Disable Button" : "Enable Button");
    });


    // 5. Labels to show state (updated via signals)
    QLabel *downLabel = new QLabel("isDown: false", &mainWindow);
    QLabel *checkedLabel = new QLabel("isChecked (base): false", &mainWindow); // Shows base bool state
    QLabel *enabledLabel = new QLabel("isEnabled: true", &mainWindow);
    QLabel *triStateLabel = new QLabel("Actual State: Unchecked", &mainWindow);

    // --- Connect Signals to Lambda Functions for Logging/Updating ---
    QObject::connect(triButton, &TriStateButton::pressed, [&]() {
        qDebug() << "Signal: pressed()";
        downLabel->setText("isDown: true");
    });

    QObject::connect(triButton, &TriStateButton::released, [&]() {
        qDebug() << "Signal: released()";
        downLabel->setText("isDown: false");
        // Update other states on release too, as they might change
         enabledLabel->setText(QString("isEnabled: %1").arg(triButton->isEnabled() ? "true" : "false"));
         checkedLabel->setText(QString("isChecked (base): %1").arg(triButton->isChecked() ? "true" : "false"));
    });

    QObject::connect(triButton, &TriStateButton::clicked, [&](bool checked) {
        // clicked(bool) argument reflects the base 'checked' state *after* the click
        qDebug() << "Signal: clicked(bool=" << checked << ")";
    });

     QObject::connect(triButton, &TriStateButton::toggled, [&](bool checked) {
        // toggled(bool) signal reflects the base 'checked' state change
        qDebug() << "Signal: toggled(bool=" << checked << ")";
        checkedLabel->setText(QString("isChecked (base): %1").arg(checked ? "true" : "false"));
        // This signal fires *after* the state change, so update triStateLabel here too
        switch (triButton->checkState()) {
           case Qt::Unchecked: triStateLabel->setText("Actual State: Unchecked"); break;
           case Qt::PartiallyChecked: triStateLabel->setText("Actual State: PartiallyChecked"); break;
           case Qt::Checked: triStateLabel->setText("Actual State: Checked"); break;
        }
    });

    // Connect to our custom signal for the detailed state
     QObject::connect(triButton, &TriStateButton::checkStateChanged, [&](Qt::CheckState newState) {
         qDebug() << "Signal: checkStateChanged(" << newState << ")";
         switch (newState) {
           case Qt::Unchecked: triStateLabel->setText("Actual State: Unchecked"); break;
           case Qt::PartiallyChecked: triStateLabel->setText("Actual State: PartiallyChecked"); break;
           case Qt::Checked: triStateLabel->setText("Actual State: Checked"); break;
        }
     });

    // --- Add Widgets to Layout ---
    layout->addWidget(triButton);
    layout->addWidget(shortcutLabel);
    layout->addWidget(autoRepeatCheck);
    layout->addWidget(toggleEnableButton);
    layout->addSpacing(10);
    layout->addWidget(new QLabel("--- Current State ---"));
    layout->addWidget(downLabel);
    layout->addWidget(checkedLabel);
    layout->addWidget(enabledLabel);
    layout->addWidget(triStateLabel);
    layout->addStretch(); // Push widgets to the top


    mainWindow.resize(400, 400);
    mainWindow.show();

    // Set initial label states
    enabledLabel->setText(QString("isEnabled: %1").arg(triButton->isEnabled() ? "true" : "false"));
    checkedLabel->setText(QString("isChecked (base): %1").arg(triButton->isChecked() ? "true" : "false"));
    triStateLabel->setText("Actual State: Unchecked");


    return app.exec();
}