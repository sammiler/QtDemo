#ifndef KEY_PRESS_OVERRIDE_DIALOG_H
#define KEY_PRESS_OVERRIDE_DIALOG_H

#include <QDialog>     // 继承自 QDialog
#include <QKeyEvent>   // 需要 QKeyEvent
#include <QVBoxLayout> // 需要布局
#include <QLabel>      // 需要 QLabel

class KeyPressOverrideEscapeDialog : public QDialog
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit KeyPressOverrideEscapeDialog(QWidget *parent = nullptr);
    ~KeyPressOverrideEscapeDialog();

protected:
    // 重写 keyPressEvent 方法
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // KEY_PRESS_OVERRIDE_DIALOG_H