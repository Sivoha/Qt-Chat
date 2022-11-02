#include <Server.h>

Server::Server() {
    if (this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "start";
    } else {
        qDebug() << "error";
    }
    nextBlockSize = 0;
}

void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QSslSocket;
//    qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();

//    QFile* keyfile = new QFile("serv_pri.key");
//    keyfile->open(QIODevice::ReadOnly);
//    QSslKey sslKey(keyfile, QSsl::Rsa);

//    socket->setPrivateKey(sslKey);

//    QFile* certfile = new QFile("serv_ca.pem");
//    if (!certfile->open(QIODevice::ReadOnly)) {
//        qDebug() << "can't open ssl serificate";
//    }
////    QByteArray cert = certfile.readAll();
//    QSslCertificate sslCert(certfile);
//    socket->setLocalCertificate(sslCert);

//    QSslConfiguration cfg;
//    cfg.setCaCertificates(QSslCertificate::fromDevice(certfile));
//    cfg.setPrivateKey(sslKey);

//    socket->setSslConfiguration(cfg);
//    socket->setSocketDescriptor(socketDescriptor);
//    socket->setPeerVerifyMode(QSslSocket::VerifyNone);
//    socket->startServerEncryption();
//    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QSslSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QSslSocket::disconnected, socket, &QSslSocket::deleteLater);
    Sockets.push_back(socket);
//    qDebug() << "client connected" << socketDescriptor;
}

void Server::slotReadyRead() {
    qDebug() << "budem otpravlyat";
    socket = (QSslSocket*)sender();
    QDataStream in(socket);
    while (true) {
        if (nextBlockSize == 0) {
            qDebug() << "nextBlockSize = 0";
            if (socket->bytesAvailable() < 2) {
                break;
            }
            in >> nextBlockSize;
            qDebug() << "nextBlockSize = " << nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize) {
            qDebug() << "data  not full";
            break;
        }

        QString str;
        QTime time;
        in >> time >> str;
        nextBlockSize = 0;
        SendToClient(str);
        qDebug() << str;
        break;
    }
}

void Server::SendToClient(QString str) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    for (auto sock : Sockets) {
        sock->write(Data);
    }
}

