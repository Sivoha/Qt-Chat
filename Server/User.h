#ifndef USER_H
#define USER_H

#include <QString>
#include <QSslSocket>
#include <QTime>
#include <QMap>
#include <QPixmap>

typedef struct {
    QTime userConnectionTime;
    QString username;
    QString userStatus;
    QString userIP;
    QPixmap userPhoto;
} User;

#endif // USER_H
