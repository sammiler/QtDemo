#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

class PushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit PushButton(QWidget *parent = nullptr)
        : QPushButton(parent), m_nID(-1), m_strName("")
    {
    }

    void setID(int id) {
        m_nID = id;
    }

    void setName(const QString &name) {
        m_strName = name;
    }

    int id() const {
        return m_nID;
    }

    QString name() const {
        return m_strName;
    }

private:
    int m_nID;
    QString m_strName;
};

#endif // PUSHBUTTON_H