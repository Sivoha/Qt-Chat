#ifndef USER_H
#define USER_H

#include <QString>
#include <QSslSocket>
#include <QTime>
#include <QMap>

enum class Status {
    Online,
    Idle,
    DoNotDisturb,
    Disconnected
};

static QMap<QString, Status> stringToStatus{{"ONLINE", Status::Online}, {"IDLE", Status::Idle}, {"DONOTDISTURB", Status::DoNotDisturb}};

typedef struct {
    QTime userConnectionTime;
    QString username;
    Status userStatus;
    QString userIP;
} User;

#endif // USER_H
