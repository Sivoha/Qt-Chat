#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDebug>
#include <QDataStream>
#include <QTime>
#include <QFile>
#include <QSslKey>
#include <QSslSocket>
#include <QSslCertificate>
#include <QSslConfiguration>

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server();
    QSslSocket *socket;
private:
    QVector<QSslSocket*> Sockets;

    QByteArray Data;

    void SendToClient(QString str);
    quint16 nextBlockSize;
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H
