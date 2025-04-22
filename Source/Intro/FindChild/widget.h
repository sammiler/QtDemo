#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

// Forward declarations to reduce include dependencies in header
class QGroupBox;
class QCheckBox;
class QVBoxLayout;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT // Necessary for signals and slots

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onFindDirectChildrenClicked();
    void onFindRecursiveChildrenClicked();

private:
    QGroupBox *parentWidget;
    // We need pointers to the buttons to connect signals/slots
    QPushButton *findDirectButton;
    QPushButton *findRecursiveButton;
};
#endif // WIDGET_H