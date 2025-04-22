#ifndef REJECT_OVERRIDE_DIALOG_H
#define REJECT_OVERRIDE_DIALOG_H

#include <QDialog>     // 继承自 QDialog
#include <QVBoxLayout> // 需要布局
#include <QLabel>      // 需要 QLabel

class RejectOverrideDialog : public QDialog
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit RejectOverrideDialog(QWidget *parent = nullptr);
    ~RejectOverrideDialog();

    // 重写 reject() 方法
    void reject() override;

private:
    bool m_bClosed; // 控制是否允许关闭的标志
};

#endif // REJECT_OVERRIDE_DIALOG_H