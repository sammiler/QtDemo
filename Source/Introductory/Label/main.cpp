#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMovie>
#include <QStyle> // Required for standard icons
#include <QSize>  // Required for QSize
#include <QString>
#include <QHBoxLayout> // For number labels layout

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Main window widget
    QWidget mainWindow;
    mainWindow.setWindowTitle("QLabel Comprehensive Demo (Qt 6)");
    mainWindow.resize(450, 600); // Give it some initial size to see word wrap

    // Main vertical layout
    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWindow);

    // --- 1. Plain Text ---
    QLabel *plainTextLabel = new QLabel(&mainWindow);
    plainTextLabel->setText("1. Plain Text: Hello from QLabel!");
    mainLayout->addWidget(plainTextLabel);

    // --- 2. Rich Text ---
    QLabel *richTextLabel = new QLabel(&mainWindow);
    // Rich text uses HTML-like tags for formatting.
    // Supported tags include <b>, <i>, <u>, <font color='' size=''>, <a>, etc.
    // It allows formatting beyond simple plain text.
    richTextLabel->setText(
        "2. Rich Text: This text is <b>bold</b>, <i>italic</i>, "
        "<font color='blue'>blue</font>, and has a link: "
        "<a href='https://www.qt.io'>Qt Website</a>."
    );
    richTextLabel->setTextFormat(Qt::RichText); // Be explicit, though often auto-detected
    richTextLabel->setOpenExternalLinks(true); // Allow clicking links
    richTextLabel->setWordWrap(true); // Rich text can also wrap
    mainLayout->addWidget(richTextLabel);

    // --- 3. Image (using QPixmap) ---
    QLabel *imageDescriptionLabel = new QLabel("3. Image (using QPixmap - Standard Icon):", &mainWindow);
    mainLayout->addWidget(imageDescriptionLabel);

    QLabel *imageLabel = new QLabel(&mainWindow);
    // Use a standard Qt icon to avoid needing an external file for this demo
    QPixmap computerPixmap = mainWindow.style()->standardPixmap(QStyle::SP_ComputerIcon, nullptr);
    if (!computerPixmap.isNull()) {
        imageLabel->setPixmap(computerPixmap);
        imageLabel->setAlignment(Qt::AlignCenter); // Center the image in the label
    } else {
        imageLabel->setText("Standard icon not found.");
    }
    mainLayout->addWidget(imageLabel);


    // --- 4. Animation (using QMovie) ---
    QLabel *animDescriptionLabel = new QLabel("4. Animation (using QMovie - needs 'loading.gif'):", &mainWindow);
    mainLayout->addWidget(animDescriptionLabel);

    QLabel *animationLabel = new QLabel(&mainWindow);
    // NOTE: You MUST have a 'loading.gif' file in the directory
    // where the executable runs for this to work.
    QMovie *movie = new QMovie(":/gif/loading.gif"); // Provide path to your animation file
    if (movie->isValid()) {
        animationLabel->setMovie(movie);
        animationLabel->setAlignment(Qt::AlignCenter);
        movie->start(); // IMPORTANT: Start the animation!
    } else {
        animationLabel->setText("<i>'loading.gif' not found or invalid.</i>");
        animationLabel->setAlignment(Qt::AlignCenter);
        delete movie; // Clean up if invalid
        movie = nullptr;
    }
    // Make the label large enough for a potential animation
    animationLabel->setMinimumSize(64, 64);
    mainLayout->addWidget(animationLabel);


    // --- 5. Numbers (using setNum) ---
    QLabel *numberDescriptionLabel = new QLabel("5. Numbers (using setNum):", &mainWindow);
    mainLayout->addWidget(numberDescriptionLabel);

    // Use a horizontal layout for numbers for better alignment
    QWidget *numberContainer = new QWidget(&mainWindow);
    QHBoxLayout *numberLayout = new QHBoxLayout(numberContainer);
    numberLayout->setContentsMargins(0,0,0,0); // Remove margins for tighter packing

    QLabel *intLabel = new QLabel("Int:", numberContainer);
    QLabel *intNumLabel = new QLabel(numberContainer);
    int intValue = 123456;
    intNumLabel->setNum(intValue); // Set integer

    QLabel *doubleLabel = new QLabel("Double:", numberContainer);
    QLabel *doubleNumLabel = new QLabel(numberContainer);
    double doubleValue = 3.1415926535;
    doubleNumLabel->setNum(doubleValue); // Set double

    numberLayout->addWidget(intLabel);
    numberLayout->addWidget(intNumLabel);
    numberLayout->addStretch(); // Add space between number pairs
    numberLayout->addWidget(doubleLabel);
    numberLayout->addWidget(doubleNumLabel);
    numberContainer->setLayout(numberLayout);
    mainLayout->addWidget(numberContainer);


    // --- 6. Clearing Content (using clear) ---
    QLabel *clearDescriptionLabel = new QLabel("6. Clear Content (using clear):", &mainWindow);
    mainLayout->addWidget(clearDescriptionLabel);

    QLabel *labelToClear = new QLabel("This text was present before calling clear().", &mainWindow);
    mainLayout->addWidget(labelToClear);
    labelToClear->clear(); // Now it's empty! (Widget remains)
    // Add a label to show it's cleared
    QLabel *clearedIndicatorLabel = new QLabel("<i>&lt;-- The label above was cleared using clear()</i>", &mainWindow);
    mainLayout->addWidget(clearedIndicatorLabel);


    // --- 7. Word Wrap for Long Text ---
    QLabel *wordWrapDescriptionLabel = new QLabel("7. Word Wrap for Long Text:", &mainWindow);
    mainLayout->addWidget(wordWrapDescriptionLabel);

    QLabel *longTextLabel = new QLabel(&mainWindow);
    longTextLabel->setText(
        "This is a very long sentence designed specifically to demonstrate the "
        "word wrapping capability of QLabel when the text exceeds the available width. "
        "Make sure setWordWrap(true) is called and the label's width is constrained "
        "(e.g., by a layout or fixed width)."
    );
    longTextLabel->setWordWrap(true); // Enable word wrapping
    mainLayout->addWidget(longTextLabel);


    // Add stretch at the bottom to push content upwards
    mainLayout->addStretch();

    // Set the main layout for the window
    mainWindow.setLayout(mainLayout);

    // Show the window and start the application event loop
    mainWindow.show();
    return app.exec();
}