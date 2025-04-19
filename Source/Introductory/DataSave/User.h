//
// Created by sammiler on 2025/4/17.
//

#ifndef USER_H
#define USER_H


#include <QObject>
#include <QString>
#include <utility>
struct User{
    User() {
        nID = 0;
    }
    User(const int nid,QString  strName):nID(nid),strName(std::move(strName)){
    }
    int nID;        // ID
    QString strName; // Username
};

typedef enum {
    UI_ZH, // Chinese
    UI_EN  // English
} LANGUAGE;
Q_DECLARE_METATYPE(User)
Q_DECLARE_METATYPE(LANGUAGE)

#endif //USER_H
