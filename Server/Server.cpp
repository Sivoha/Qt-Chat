#include "ui_mainwindow.h"
#include <Server.h>

Server::Server() {
    if (this->listen(QHostAddress(IP), port)) {
        qDebug() << "start";
    } else {
        qDebug() << "error";
    }

    nextBlockSize = 0;
}

Server::~Server() {}

void Server::setUpServer() {
    QByteArray key;
    QByteArray cert;

    QFile file_key("D:/Documents/C++/Qt/Chat/Server/server.key");
    if(file_key.open(QIODevice::ReadOnly)) {
        key = file_key.readAll();
        file_key.close();
    }
    else{
        qDebug() << file_key.errorString();
    }

    QFile file_cert("D:/Documents/C++/Qt/Chat/Server/server.crt");
    if(file_cert.open(QIODevice::ReadOnly)){
        cert = file_cert.readAll();
        file_cert.close();
    }
    else{
        qDebug() << file_cert.errorString();
    }

    QSslKey ssl_key(key, QSsl::Rsa,QSsl::Pem,QSsl::PrivateKey,"localhost");
    QSslCertificate ssl_cert(cert);

    QList<QSslError> l;
    l << QSslError(QSslError::SelfSignedCertificate,ssl_cert);
    socket->ignoreSslErrors(l);

    socket->setLocalCertificate(ssl_cert);
    socket->setPrivateKey(ssl_key);
//    connect(&socket, SIGNAL(encrypted()), this, SLOT(ready()));
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, true );
}

void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QSslSocket;
    socket->setSocketDescriptor(socketDescriptor);
//    setUpServer();
//    socket->startServerEncryption();

    connect(socket, &QSslSocket::readyRead, this, &Server::slotReadyRead);
//    connect(socket, &QSslSocket::disconnected, socket, &QSslSocket::deleteLater);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectEvent()));

    userList[socket].userConnectionTime = QTime::currentTime();
    userList[socket].userStatus = Status::Online;
    userList[socket].userIP = socket->peerAddress().toString();
    userList[socket].username = "User" + QString::number(qrand() % 100000 + 1);
    qDebug() << userList[socket].userConnectionTime.toString() << userList[socket].userIP << userList[socket].username;

    emit updateWindowTitleEvent("Server | IP: " + IP + " Port: " + QString::number(port) + " Number of clients: " + QString::number(userList.size()));
    emit logEvent("<b>" + QTime::currentTime().toString() + "</b> " + userList[socket].username + " connected");

    sendToClient(true);
    sendUsernameToClient(userList[socket].username);
    sendUserListToClient();
}

void Server::disconnectEvent() {
    socket = qobject_cast<QSslSocket*>(sender());
    sendToClient(false);
    emit logEvent("<b>" + QTime::currentTime().toString() + "</b> " + userList[socket].username + " disconnected");
    userList.remove(socket);
    emit updateWindowTitleEvent("Server | IP: " + IP + " Port: " + QString::number(port) + " Number of clients: " + QString::number(userList.size()));
    sendUserListToClient();
}

void Server::slotReadyRead() {
    socket = (QSslSocket*)sender();
    QDataStream in(socket);
    while (true) {
        if (nextBlockSize == 0) {
            if (socket->bytesAvailable() < 2) {
                break;
            }
            in >> nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize) {
            break;
        }
        QString sendType;
        in >> sendType;
        if (sendType == "MESSAGE") {
            QString messageText;
            QTime messageTime;
            in >> messageTime >> messageText;
            nextBlockSize = 0;
            sendToClient(messageText);
        } else if (sendType == "USERNAME") {
            QString newUsername;
            in >> newUsername;
            sendUsernameChangeLog(userList[socket].username, newUsername);
            userList[socket].username = newUsername;
            nextBlockSize = 0;
            sendUserListToClient();
        } else if (sendType == "STATUS") {
            QString newUserStatus;
            in >> newUserStatus;
            userList[socket].userStatus = stringToStatus[newUserStatus];
            nextBlockSize = 0;
        } else if (sendType == "USERNAME&STATUS") {
            QString strData;
            in >> strData;
            QStringList data = strData.split(" ");
            userList[socket].username = data[0];
            userList[socket].userStatus = stringToStatus[data[1]];
            nextBlockSize = 0;
            sendUserListToClient();
        } else if (sendType == "USERINFO") {
            QString username;
            in >> username;
            nextBlockSize = 0;
            sendUserInfoToClient(username);
        }
        break;
    }
}

void Server::sendToClient(const QString &str) {
    QString sendType = "MESSAGE";
    sendData.clear();
    QDataStream out(&sendData, QIODevice::WriteOnly);
    out << quint16(0) << sendType << QTime::currentTime() << userList[socket].userIP << userList[socket].username << str;
    out.device()->seek(0);
    out << quint16(sendData.size() - sizeof(quint16));
    for (const auto& userSocket : userList.keys()) {
        userSocket->write(sendData);
    }
}

void Server::sendUserListToClient() {
    QString sendType = "USERLIST";
    sendData.clear();
    QDataStream out(&sendData, QIODevice::WriteOnly);

    QString usernames = "";
    foreach(User user, userList) {
        usernames += user.username + " ";
    }
    out << quint16(0) << sendType << usernames;
    out.device()->seek(0);
    out << quint16(sendData.size() - sizeof(quint16));

    for (const auto& userSocket : userList.keys()) {
        userSocket->write(sendData);
    }
}

void Server::sendUserInfoToClient(const QString& username) {
    QString sendType = "USERINFO";
    sendData.clear();
    QDataStream out(&sendData, QIODevice::WriteOnly);
    for (const auto& userSocket : userList.keys()) {
        if (userList[userSocket].username == username) {
            out << quint16(0) << sendType << username << userList[userSocket].userIP << userList[userSocket].userConnectionTime;
            QString userStatus;
            if (userList[userSocket].userStatus == Status::Online) {
                userStatus = "Online";
            } else if (userList[userSocket].userStatus == Status::Idle) {
                userStatus = "Idle";
            } else if (userList[userSocket].userStatus == Status::DoNotDisturb) {
                userStatus = "Do Not Disturb";
            }
            out << userStatus;
            break;
        }
    }
    out.device()->seek(0);
    out << quint16(sendData.size() - sizeof(quint16));

    socket->write(sendData);
}

void Server::sendUsernameToClient(const QString& newUsername) {
    QString sendType = "USERNAME";

    sendData.clear();
    QDataStream out(&sendData, QIODevice::WriteOnly);
    out << quint16(0) << sendType << newUsername;
    out.device()->seek(0);
    out << quint16(sendData.size() - sizeof(quint16));

    socket->write(sendData);
}

void Server::sendUsernameChangeLog(const QString& oldName, const QString& newName) {
    QString sendType = "USERNAMECHANGE";

    sendData.clear();
    QDataStream out(&sendData, QIODevice::WriteOnly);
    out << quint16(0) << sendType << QTime::currentTime() << oldName << newName;
    out.device()->seek(0);
    out << quint16(sendData.size() - sizeof(quint16));

    for (const auto& userSocket : userList.keys()) {
        if (userSocket != socket) {
            userSocket->write(sendData);
        }
    }
}

void Server::sendToClient(bool action) {
    QString sendType = "ACTION";
    QString strAction = action ? "connected" : "disconnected";
    sendData.clear();
    QDataStream out(&sendData, QIODevice::WriteOnly);
    out << quint16(0) << sendType << QTime::currentTime() << userList[socket].username << strAction;
    out.device()->seek(0);
    out << quint16(sendData.size() - sizeof(quint16));

    for (const auto& userSocket : userList.keys()) {
        if (userSocket != socket) {
            userSocket->write(sendData);
        }
    }
}

