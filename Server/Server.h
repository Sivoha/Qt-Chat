#ifndef SERVER_H
#define SERVER_H

#include <includes.h>
#include <User.h>

class Server : public QTcpServer {
    Q_OBJECT
    friend class MainWindow;
public:
    Server();
    ~Server();
    QSslSocket *socket;
private:
    QMap<QSslSocket*, User> userList;

    QByteArray sendData;

    void setUpServer();

    void sendToClient(const QString&);
    void sendUserListToClient();
    void sendUserInfoToClient(const QString&);
    void sendUsernameChangeLog(const QString&, const QString&);
    void sendUsernameToClient(const QString&);
    void sendToClient(bool);

    quint16 nextBlockSize;

    QString IP = "127.0.0.1";
    quint16 port = (quint16)45678;
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void disconnectEvent();
    void slotReadyRead();

signals:
    void updateWindowTitleEvent(QString);
    void logEvent(QString);
};

#endif // SERVER_H
