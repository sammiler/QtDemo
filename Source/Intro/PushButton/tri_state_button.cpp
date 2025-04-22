#include "tri_state_button.h"
#include <QStyle>
#include <QApplication>
#include <QMenu>

TriStateButton::TriStateButton(const QString &text, QWidget *parent)
    : QPushButton(parent)
{
    setText(text);
    setCheckable(true); // Make it checkable by default for tri-state behavior
    InitButtonMenu();
}

TriStateButton::TriStateButton(QWidget *parent)
    : QPushButton(parent)
{
     setCheckable(true); // Make it checkable by default for tri-state behavior
}


// --- Property Get/Set ---
Qt::CheckState TriStateButton::checkState() const {
    return currentCheckState;
}

void TriStateButton::setCheckState(Qt::CheckState state) {
    if (currentCheckState != state) {
        currentCheckState = state;
        updateBaseCheckedState(); // Sync with base class boolean state
        update(); // Trigger repaint
        emit checkStateChanged(currentCheckState); // Emit detailed state change
    }
}
// --- Required Reimplementations ---

QSize TriStateButton::sizeHint() const {
    ensurePolished(); // Make sure style options are calculated

    // --- Corrected Icon Size Calculation ---
    QSize actualIconSize(0, 0); // Default to 0x0 if no icon
    if (!icon().isNull()) {
        actualIconSize = iconSize(); // Get the iconSize property set on the button
        // If the property wasn't set or is invalid, fallback to style default
        if (!actualIconSize.isValid()) {
            int iconExtent = style()->pixelMetric(QStyle::PM_ButtonIconSize, nullptr, this);
            actualIconSize = QSize(iconExtent, iconExtent);
        }
    }
    // --- End Corrected Section ---

    // Size for the check indicator (approximated)
    int indicatorWidth = style()->pixelMetric(QStyle::PM_IndicatorWidth, nullptr, this);
    int indicatorHeight = style()->pixelMetric(QStyle::PM_IndicatorHeight, nullptr, this);
    int indicatorSpacing = style()->pixelMetric(QStyle::PM_CheckBoxLabelSpacing, nullptr, this);

    // Size for text
    QFontMetrics fm = fontMetrics();
    QSize textSize = fm.size(Qt::TextShowMnemonic, text()); // Calculate size respecting mnemonics

    // Combine sizes, adding margins and spacing
    int w = indicatorWidth + indicatorSpacing;
    if (!icon().isNull()) {
        w += actualIconSize.width() + indicatorSpacing; // Add actual icon width + spacing
    }
    w += textSize.width();

    int h = qMax(indicatorHeight, qMax(actualIconSize.height(), textSize.height()));

    // Add margins
    int mw = style()->pixelMetric(QStyle::PM_ButtonMargin, nullptr, this) * 2;
    int mh = style()->pixelMetric(QStyle::PM_ButtonMargin, nullptr, this) * 2;

    // Use style hint if possible, otherwise calculate based on contents
    QStyleOptionButton opt;
    // Initialize option using the *inherited* protected method from QAbstractButton
    initStyleOption(&opt);
    opt.iconSize = actualIconSize; // Make sure the option knows the icon size we used

    // Let the style calculate the final size based on contents
    QSize styleHintSize = style()->sizeFromContents(QStyle::CT_CheckBox, &opt, QSize(w, h).expandedTo(QSize(mw, mh)), this);

    return styleHintSize.expandedTo(QApplication::globalStrut()); // Ensure minimum size
}


void TriStateButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QStylePainter painter(this);
    QStyleOptionButton option;
    initStyleOption(&option); // Initialize with current button state

    // --- Crucial: Sync QStyleOption's check state with our tri-state ---
    switch(currentCheckState) {
        case Qt::Unchecked:
            option.state |= QStyle::State_Off;
            break;
        case Qt::Checked:
            option.state |= QStyle::State_On;
            break;
        case Qt::PartiallyChecked:
            option.state |= QStyle::State_NoChange; // Use this for partial state
            break;
    }

    // --- Let the current Application Style draw the button ---
    // 1. Draw the button bevel/background (optional)
    // painter.drawPrimitive(QStyle::PE_PanelButtonCommand, option);

    // 2. Draw the check indicator using the style
    QStyleOptionButton checkboxOpt = option; // Copy option

    // --- Position the checkbox indicator at the left ---
    int indicatorWidth = style()->pixelMetric(QStyle::PM_IndicatorWidth, nullptr, this);
    int indicatorHeight = style()->pixelMetric(QStyle::PM_IndicatorHeight, nullptr, this);

    // 3. Draw the icon and text (Label) using the style
    QRect labelRect = option.rect;
    int indicatorSpacing = style()->pixelMetric(QStyle::PM_CheckBoxLabelSpacing, nullptr, this);
    labelRect.setLeft(labelRect.left() + indicatorWidth + indicatorSpacing);

    QStyleOptionButton labelOpt = option; // Copy option again
    labelOpt.rect = labelRect; // Set the adjusted rect
    painter.drawControl(QStyle::CE_CheckBoxLabel, labelOpt); // Draw text and icon

  
    QRect indicatorRect(option.rect.right() - indicatorWidth, // Start at the left edge of the button
    option.rect.top() + (option.rect.height() - indicatorHeight) / 2, // Vertically center it
    indicatorWidth,
    indicatorHeight);
    checkboxOpt.rect = indicatorRect;
    painter.drawPrimitive(QStyle::PE_IndicatorCheckBox, checkboxOpt);



    // 4. Draw focus rectangle if needed
    if (option.state & QStyle::State_HasFocus) {
        QStyleOptionFocusRect focusOpt;
        focusOpt.QStyleOption::operator=(option);
        focusOpt.rect = style()->subElementRect(QStyle::SE_CheckBoxFocusRect, &option, this);
        painter.drawPrimitive(QStyle::PE_FrameFocusRect, focusOpt);
    }

    // Debugging: Print state
    // qDebug() << "Paint: isDown=" << isDown() << " isChecked=" << isChecked()
    //          << " State=" << currentCheckState << "isEnabled=" << isEnabled();
}

bool TriStateButton::hitButton(const QPoint &pos) const {
    // For a simple rectangular button, just check if the position is inside the bounds
    return rect().contains(pos);
}

// --- Checkable Behavior Implementation ---

void TriStateButton::checkStateSet() {
    // Called when setChecked() is used. Map the base boolean state
    // back to our tri-state if needed. Here, we assume setChecked(true) means
    // fully checked, and setChecked(false) means unchecked.
    // setCheckState() handles the update logic.
    if (isCheckable()) {
         setCheckState(QAbstractButton::isChecked() ? Qt::Checked : Qt::Unchecked);
    }
}

void TriStateButton::nextCheckState() {
    // This is the core logic for cycling through states on user click
    if (!isCheckable()) return; // Do nothing if not checkable

    switch(currentCheckState) {
        case Qt::Unchecked:
            setCheckState(Qt::PartiallyChecked);
            break;
        case Qt::PartiallyChecked:
            setCheckState(Qt::Checked);
            break;
        case Qt::Checked:
            setCheckState(Qt::Unchecked);
            break;
    }
    // Note: setCheckState calls updateBaseCheckedState, which emits toggled(bool)
}

// --- Helper ---
void TriStateButton::updateBaseCheckedState() {
    // Update the base QAbstractButton's checked property.
    // We consider PartiallyChecked and Checked as "checked" in the boolean sense.
    bool baseChecked = (currentCheckState != Qt::Unchecked);
    if (QAbstractButton::isChecked() != baseChecked) {
        // Use QAbstractButton::setChecked to ensure signals are emitted correctly
        QAbstractButton::setChecked(baseChecked);
        // toggled(bool) signal is emitted automatically by setChecked
    }
}

void TriStateButton::InitButtonMenu()
{
    QMenu *pMenu = new QMenu(this);
    pMenu->addAction(QStringLiteral("设置"));
    pMenu->addAction(QStringLiteral("版本检测"));
    pMenu->addSeparator();
    pMenu->addAction(QStringLiteral("关于我们"));
    pMenu->addAction(QStringLiteral("退出"));

    setMenu(pMenu);
}
