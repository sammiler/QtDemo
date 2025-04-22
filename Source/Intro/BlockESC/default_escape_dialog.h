#ifndef DEFAULT_ESCAPE_DIALOG_H
#define DEFAULT_ESCAPE_DIALOG_H

#include <QDialog>          // 继承自 QDialog
#include <QDialogButtonBox> // 需要 QDialogButtonBox
#include <QVBoxLayout>      // 需要布局
#include <QLabel>           // 需要 QLabel
#include <QDebug>
class DefaultEscapeDialog : public QDialog
{
    Q_OBJECT // 需要 Q_OBJECT 宏

public:
    explicit DefaultEscapeDialog(QWidget *parent = nullptr);
    ~DefaultEscapeDialog();
};

#endif // DEFAULT_ESCAPE_DIALOG_H