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
    userList[socket].userStatus = "Online";
    userList[socket].userIP = socket->peerAddress().toString();
    userList[socket].username = "User" + QString::number(qrand() % 100000 + 1);
    userList[socket].userPhoto = QPixmap("userphoto.png");
    qDebug() << userList[socket].userConnectionTime.toString() << userList[socket].userIP << userList[socket].username;
    numberOfClients++;

    emit updateWindowTitleEvent();
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
    numberOfClients--;
    emit updateWindowTitleEvent();
    sendUserListToClient();
}

void Server::slotReadyRead() {
    socket = (QSslSocket*)sender();
//    QByteArray test2 = socket->readAll();
//    qDebug() << "HERE " << test2.size();
    QDataStream in(socket);
    while (true) {
        if (nextBlockSize == 0) {
            if ((quint16)socket->bytesAvailable() < sizeof(quint16)) {
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
            userList[socket].userStatus = newUserStatus;
            nextBlockSize = 0;
        } else if (sendType == "USERNAME&STATUS") {
            QString strData;
            in >> strData;
            QStringList data = strData.split(" ");
            userList[socket].username = data[0];
            userList[socket].userStatus = data[1];
            nextBlockSize = 0;
            sendUserListToClient();
        } else if (sendType == "USERINFO") {
            QString username;
            in >> username;
            nextBlockSize = 0;
            sendUserInfoToClient(username);
        } else if (sendType == "USERPHOTO") {
            QPixmap newUserPhoto = QPixmap();
            in >> newUserPhoto;
            qDebug() << newUserPhoto.size();
            userList[socket].userPhoto = newUserPhoto;
            nextBlockSize = 0;
            sendUserListToClient();
        }
        break;
    }
}

void Server::test() {
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    QLabel *userPhotoLabel = new QLabel();
    userPhotoLabel->setPixmap(userList[socket].userPhoto);
    userPhotoLabel->setFixedSize(250, 250);
    userPhotoLabel->setScaledContents(true);
    boxLayout->addWidget(userPhotoLabel);

    QPushButton *saveUserPhotoButton = new QPushButton("Save");
    boxLayout->addWidget(saveUserPhotoButton);

    QDialog *modalDialog = new QDialog();
    modalDialog->setModal(false);
    modalDialog->setWindowTitle("Photo settings");
    modalDialog->setLayout(boxLayout);
    connect(saveUserPhotoButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));
    if (modalDialog->exec() == QDialog::Accepted) {
        delete modalDialog;
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

//    QString usernames = "";
//    foreach(User user, userList) {
//        usernames += user.username + " ";
//    }
//    out << quint16(0) << sendType << usernames;
    out << quint16(0) << sendType << userList.size();
    foreach(User user, userList) {
        out << user.username << user.userPhoto;
    }

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
            out << quint16(0) << sendType << username << userList[userSocket].userIP << userList[userSocket].userConnectionTime << userList[userSocket].userStatus << userList[userSocket].userPhoto;
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

