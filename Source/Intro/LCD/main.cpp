#include <QApplication>
#include <QWidget>
#include <QLCDNumber>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>

// Define a custom QWidget class to handle signals/slots cleanly
class LcdDemoWidget : public QWidget
{
    Q_OBJECT // Required for signals and slots

public:
    LcdDemoWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        // --- Create Widgets ---
        lcd = new QLCDNumber(this);
        lcd->setSegmentStyle(QLCDNumber::Filled); // Default style
        lcd->setDigitCount(5); // Default digit count

        slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(-5000, 15000); // Range covering normal and potential overflow
        slider->setValue(1234);         // Initial value

        digitSpinBox = new QSpinBox(this);
        digitSpinBox->setRange(1, 16); // Min/Max number of digits
        digitSpinBox->setValue(lcd->digitCount());
        digitSpinBox->setPrefix("Digits: ");

        modeComboBox = new QComboBox(this);
        modeComboBox->addItem("Decimal", QLCDNumber::Dec);
        modeComboBox->addItem("Hexadecimal", QLCDNumber::Hex);
        modeComboBox->addItem("Octal", QLCDNumber::Oct);
        modeComboBox->addItem("Binary", QLCDNumber::Bin);

        styleComboBox = new QComboBox(this);
        styleComboBox->addItem("Filled", QLCDNumber::Filled);
        styleComboBox->addItem("Outline", QLCDNumber::Outline);
        styleComboBox->addItem("Flat", QLCDNumber::Flat);

        smallDecimalCheckBox = new QCheckBox("Small Decimal Point", this);
        smallDecimalCheckBox->setChecked(lcd->smallDecimalPoint());

        specialCharsButton = new QPushButton("Display 'HELP'", this);
        overflowTestButton = new QPushButton("Test Overflow (Display 99999)", this);

        statusLabel = new QLabel("Status: OK", this);
        statusLabel->setStyleSheet("color: green;"); // Initial status color

        // --- Layout ---
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // LCD Display
        mainLayout->addWidget(lcd);

        // Value Slider
        QGroupBox *valueGroup = new QGroupBox("Value Control", this);
        QHBoxLayout *valueLayout = new QHBoxLayout(valueGroup);
        valueLayout->addWidget(slider);
        mainLayout->addWidget(valueGroup);

        // Settings Grid
        QGroupBox *settingsGroup = new QGroupBox("Settings", this);
        QGridLayout *settingsLayout = new QGridLayout(settingsGroup);
        settingsLayout->addWidget(new QLabel("Mode:", settingsGroup), 0, 0);
        settingsLayout->addWidget(modeComboBox, 0, 1);
        settingsLayout->addWidget(new QLabel("Style:", settingsGroup), 0, 2);
        settingsLayout->addWidget(styleComboBox, 0, 3);
        settingsLayout->addWidget(digitSpinBox, 1, 0, 1, 2); // Span 2 columns
        settingsLayout->addWidget(smallDecimalCheckBox, 1, 2, 1, 2); // Span 2 columns
        mainLayout->addWidget(settingsGroup);

         // Test Buttons
        QGroupBox *testGroup = new QGroupBox("Tests", this);
        QHBoxLayout *testLayout = new QHBoxLayout(testGroup);
        testLayout->addWidget(specialCharsButton);
        testLayout->addWidget(overflowTestButton);
        mainLayout->addWidget(testGroup);


        // Status Label
        mainLayout->addWidget(statusLabel);

        setLayout(mainLayout);
        setWindowTitle("QLCDNumber Demo");
        resize(450, 400);

        // --- Connections ---
        // Update LCD when slider changes
        connect(slider, &QSlider::valueChanged, this, &LcdDemoWidget::updateLcdDisplay);

        // Update LCD settings
        connect(digitSpinBox, qOverload<int>(&QSpinBox::valueChanged), lcd, &QLCDNumber::setDigitCount);
        connect(modeComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &LcdDemoWidget::changeMode);
        connect(styleComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &LcdDemoWidget::changeStyle);
        connect(smallDecimalCheckBox, &QCheckBox::toggled, lcd, &QLCDNumber::setSmallDecimalPoint);

        // Update display immediately when settings change that might affect appearance/overflow
        connect(digitSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &LcdDemoWidget::redisplayCurrentValue);
        connect(modeComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &LcdDemoWidget::redisplayCurrentValue);
        connect(smallDecimalCheckBox, &QCheckBox::toggled, this, &LcdDemoWidget::redisplayCurrentValue);


        // Test buttons
        connect(specialCharsButton, &QPushButton::clicked, this, &LcdDemoWidget::displaySpecialChars);
        connect(overflowTestButton, &QPushButton::clicked, this, &LcdDemoWidget::testOverflow);

        // Handle overflow signal from LCD
        connect(lcd, &QLCDNumber::overflow, this, &LcdDemoWidget::handleOverflowSignal);

        // Initial display
        updateLcdDisplay(slider->value());
    }

private slots:
    // Updates the LCD with the current slider value and checks overflow
    void updateLcdDisplay(int value) {
        lcd->display(value);
        checkAndReportOverflow(value);
    }

    // Slot to handle mode changes from combo box
    void changeMode(int index) {
        QLCDNumber::Mode mode = static_cast<QLCDNumber::Mode>(modeComboBox->itemData(index).toInt());
        lcd->setMode(mode);
        // Note: value() returns double, might not be useful if Hex/Oct/Bin was intended.
        // redisplayCurrentValue(); // Called by separate connection now
    }

    // Slot to handle style changes from combo box
    void changeStyle(int index) {
        QLCDNumber::SegmentStyle style = static_cast<QLCDNumber::SegmentStyle>(styleComboBox->itemData(index).toInt());
        lcd->setSegmentStyle(style);
    }

    // Display predefined special characters
    void displaySpecialChars() {
        // Cycle through a few examples
        static int charIndex = 0;
        QString charsToShow;
        switch(charIndex++ % 4) {
            case 0: charsToShow = "HELP"; break; // H, E, L, P are displayable
            case 1: charsToShow = "A C E"; break; // A, C, E, space
            case 2: charsToShow = "O' - "; break; // O (or 0), degree ('), space, minus
            case 3: charsToShow = "Error"; break; // E, r, o, r are displayable
        }
        // Displaying strings directly works for displayable chars, replaces others with space
        lcd->display(charsToShow);
        statusLabel->setText("Status: Displayed string");
        statusLabel->setStyleSheet("color: blue;");
    }

    // Test overflow by trying to display a large number
    void testOverflow() {
        double testValue = 999999.0; // A value likely to cause overflow
        // Use checkOverflow FIRST to see if it *will* overflow
        bool willOverflow = lcd->checkOverflow(testValue);
        statusLabel->setText(QString("Status: checkOverflow(999999) returned %1")
                             .arg(willOverflow ? "true (Overflow expected)" : "false"));
        statusLabel->setStyleSheet(willOverflow ? "color: orange;" : "color: blue;");

        // Now actually display it, which will trigger the overflow signal if checkOverflow was true
        lcd->display(testValue);
         // Note: handleOverflowSignal will likely update the status label again if overflow occurs
    }

    // Slot connected directly to the lcd->overflow() signal
    void handleOverflowSignal() {
        statusLabel->setText("Status: Overflow signal detected!");
        statusLabel->setStyleSheet("color: red; font-weight: bold;");
    }

    // Helper to re-display the current slider value (useful after mode/digit changes)
    void redisplayCurrentValue() {
       updateLcdDisplay(slider->value());
    }

    // Helper function to manually check overflow and update status
    void checkAndReportOverflow(double value) {
        // Don't override explicit signal message immediately
        if (!statusLabel->text().contains("signal detected")) {
             if (lcd->checkOverflow(value)) {
                // This check happens *after* display, confirming overflow state
                statusLabel->setText("Status: Overflow occurred");
                statusLabel->setStyleSheet("color: red;");
            } else {
                statusLabel->setText("Status: OK");
                statusLabel->setStyleSheet("color: green;");
            }
        }
    }


private:
    QLCDNumber *lcd;
    QSlider *slider;
    QSpinBox *digitSpinBox;
    QComboBox *modeComboBox;
    QComboBox *styleComboBox;
    QCheckBox *smallDecimalCheckBox;
    QPushButton *specialCharsButton;
    QPushButton *overflowTestButton;
    QLabel *statusLabel;
};

// Include the moc file generated by Qt's build process
#include "main.moc" // Make sure filename matches source file


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LcdDemoWidget demoWidget;
    demoWidget.show();

    return app.exec();
}