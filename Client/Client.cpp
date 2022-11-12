#include "Client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    this->setWindowTitle("Disconnected");
    ui->setupUi(this);

    settings = new QSettings("D:/Documents/C++/Qt/Chat/Client/settings.ini", QSettings::IniFormat);

    document = new QDomDocument("message-history");
    domElement = document->createElement("message-history");
    document->appendChild(domElement);

    if (!settings->contains("SERVER/IP")) {
        settings->setValue("SERVER/IP", "127.0.0.1");
    }

    if (!settings->contains("SERVER/PORT")) {
        settings->setValue("SERVER/PORT", 45678);
    }

    if (!settings->contains("USER/STATUS")) {
        settings->setValue("USER/STATUS", "ONLINE");
    }

    if (!settings->contains("USER/USERNAME")) {
        settings->setValue("USER/USERNAME", "");
    }

    serverIP = settings->value("SERVER/IP", "").toString();
    serverPort = settings->value("SERVER/PORT", "").toUInt();
    userStatusBeforeDisconnect = stringToStatus[settings->value("USER/STATUS", "").toString()];
    userStatus = Status::Disconnected;
    username = settings->value("USER/USERNAME", "").toString();

    ui->serverSettingsButton->setText("Server: " + serverIP + " " + QString::number(serverPort));

    connect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(onSendMessageButtonClicked()));
    connect(ui->newMessageLine, SIGNAL(returnPressed()), this, SLOT(onNewMessageLineReturnPressed()));
    connect(ui->connectToServerButton, SIGNAL(triggered()), this, SLOT(onConnectToServerButtonTriggered()));
    connect(ui->disconnectButton, SIGNAL(triggered()), this, SLOT(onDisconnectButtonTriggered()));
    connect(ui->saveHistoryButton, SIGNAL(triggered()), this, SLOT(onSaveHistoryButtonTriggered()));
    connect(ui->exitButton, SIGNAL(triggered()), this, SLOT(onExitButtonTriggered()));
    connect(ui->usernameSettingsButton, SIGNAL(triggered()), this, SLOT(onUsernameSettingsButtonTriggered()));
    connect(ui->serverSettingsButton, SIGNAL(triggered()), this, SLOT(onServerSettingsButtonTriggered()));
    connect(ui->userListWidget, SIGNAL(rightClick(QPoint)), this, SLOT(onUserItemClicked(QPoint)));

    QAction* helpAction = new QAction("Help", ui->menubar);
    ui->menubar->addAction(helpAction);
    ui->menubar->connect(helpAction, SIGNAL(triggered()), this, SLOT(onHelpButtonTriggered()));

    QWidgetAction *statusOnlineButton, *statusIdleButton, *statusDoNotDisturbButton;
    addStatusButtonToMenu(&statusOnlineCheckBox, &statusOnlineButton, "Online", userStatusBeforeDisconnect == Status::Online);
    addStatusButtonToMenu(&statusIdleCheckBox, &statusIdleButton, "Idle", userStatusBeforeDisconnect == Status::Idle);
    addStatusButtonToMenu(&statusDoNotDisturbCheckBox, &statusDoNotDisturbButton, "Do Not Disturb", userStatusBeforeDisconnect == Status::DoNotDisturb);

    connect(statusOnlineCheckBox, SIGNAL(clicked()), this, SLOT(onStatusOnlineButtonTriggered()));
    connect(statusIdleCheckBox, SIGNAL(clicked()), this, SLOT(onStatusIdleButtonTriggered()));
    connect(statusDoNotDisturbCheckBox, SIGNAL(clicked()), this, SLOT(onStatusDoNotDisturbButtonTriggered()));

    userSocket = new QSslSocket;

    nextBlockSize = 0;

    newMessageSound = new QSound("D:/Documents/C++/Qt/Chat/Client/newmessagesound.wav");

    connect(userSocket, &QSslSocket::readyRead, this, &Client::slotReadyRead);
    connect(userSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(userSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

    connectToServer();
}

Client::~Client() {
    delete ui;
}

QString Client::boldCurrentTime() {
    return "<b>" + QTime::currentTime().toString() + "</b>";
}

void Client::setUpSocket() {
    QByteArray cert;

    QFile file_cert("D:/Documents/C++/Qt/Chat/Client/server.crt");
    if(file_cert.open(QIODevice::ReadOnly)){
        cert = file_cert.readAll();
        file_cert.close();
    }
    else{
        qDebug() << file_cert.errorString();
    }
    QSslCertificate ssl_cert(cert);
    QList<QSslError> l;
    l << QSslError(QSslError::SelfSignedCertificate, ssl_cert);
    userSocket->ignoreSslErrors(l);
    QList<QSslCertificate> listCA;
    listCA.append(ssl_cert);
    QSslConfiguration conf;
    conf.setCaCertificates(listCA);
    userSocket->setSslConfiguration(conf);

}

void Client::connectToServer() {
    if (userStatus == Status::Disconnected) {
//        setUpSocket();
//
        userStatus = userStatusBeforeDisconnect;
        userSocket->connectToHost(serverIP, serverPort);
//        userSocket->connectToHostEncrypted(serverIP, serverPort);
//        if (!username.isEmpty()) {
//            sendToServer("USERNAME", username);
//        }
    } else {
        ui->messageBrowser->append(boldCurrentTime() + " You are already connected to" + serverIP + " " + QString::number(serverPort));
    }
}

void Client::disconnectFromServer() {
    if (userStatus != Status::Disconnected) {
        userStatusBeforeDisconnect = userStatus;
        settings->setValue("USER/STATUS", statusToString[userStatus]);
        userSocket->disconnectFromHost();
        setDisconnectedStatus();
        ui->messageBrowser->append(boldCurrentTime() + " Disconnected from" + serverIP + " " + QString::number(serverPort));
        ui->userListWidget->clear();
    } else {
        ui->messageBrowser->append(boldCurrentTime() + " You are not connected to server");
    }
}

void Client::slotConnected() {
    userStatus = userStatusBeforeDisconnect;
    settings->setValue("USER/STATUS", statusToString[userStatus]);
    if (!username.isEmpty()) {
        sendToServer("USERNAME&STATUS", username + " " + statusToString[userStatus]);
    } else {
       sendToServer("STATUS", statusToString[userStatus]);
    }

    updateWindowStatus();
    ui->serverSettingsButton->setText("Server: " + serverIP + " " + QString::number(serverPort));
    ui->messageBrowser->append(boldCurrentTime() + " Connected to" + serverIP + " " + QString::number(serverPort));
}

void Client::slotError(QAbstractSocket::SocketError /*error*/) {
    if (userStatus != Status::Disconnected) {
        userStatusBeforeDisconnect = userStatus;
        ui->userListWidget->clear();
    }
    setDisconnectedStatus();
    ui->messageBrowser->append(boldCurrentTime() + " Connection failed: " + userSocket->errorString());
    userSocket->disconnectFromHost();
}

void Client::setDisconnectedStatus() {
    userStatus = Status::Disconnected;
    this->setWindowTitle("Client | Status: Disconnected");
}

void Client::updateWindowStatus() {
    if (userStatus == Status::Online) {
        this->setWindowTitle("Client | IP:" + serverIP + " Port: " + QString::number(serverPort) + " Status: Online");
    } else if (userStatus == Status::Idle) {
        this->setWindowTitle("Client | IP:" + serverIP + " Port: " + QString::number(serverPort) + " Status: Idle");
    } else if (userStatus == Status::DoNotDisturb) {
        this->setWindowTitle("Client | IP:" + serverIP + " Port: " + QString::number(serverPort) + " Status: Do Not Disturb");
    }
}

void Client::sendToServer(const QString& sendType, const QString& message) {
    messageData.clear();
    QDataStream out(&messageData, QIODevice::WriteOnly);
    if (sendType == "MESSAGE") {
        out << quint16(0) << sendType << QTime::currentTime() << message;
        out.device()->seek(0);
        out << quint16(messageData.size() - sizeof(quint16));
        userSocket->write(messageData);
        ui->newMessageLine->clear();
    } else if (sendType == "USERNAME" || sendType == "STATUS" || sendType == "USERINFO" || sendType == "USERNAME&STATUS") {
        out << quint16(0) << sendType << message;
        out.device()->seek(0);
        out << quint16(messageData.size() - sizeof(quint16));
        userSocket->write(messageData);
    }
}

void Client::slotReadyRead() {
    QDataStream in(userSocket);
    while (true) {
        if (nextBlockSize == 0) {
            if ((quint16)userSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> nextBlockSize;
        }

        if (userSocket->bytesAvailable() < nextBlockSize) {
            break;
        }

        QString inType;
        in >> inType;
        if (inType == "MESSAGE") {
            QString messageText;
            QString senderIP;
            QString senderName;
            QTime messageTime;

            in >> messageTime >> senderIP >> senderName >> messageText;
            if (userStatus != Status::DoNotDisturb && senderName != username) {
                newMessageSound->play();
            }

            ui->messageBrowser->append("<b>" + messageTime.toString() + "</b> " + "<b>[" + senderIP + " : " + senderName + "]</b> " + messageText);
            nextBlockSize = 0;

            QDomElement newMessage = message(document, messageTime.toString(), senderIP, senderName, messageText);
            domElement.appendChild(newMessage);
        } else if (inType == "USERLIST") {
            ui->userListWidget->clear();
            QString usernames;

            in >> usernames;
            QStringList userList = usernames.split(" ");

            for (const auto& user : userList) {
                if (!user.isEmpty()) {
                    activeUsernames.insert(user);
                    QListWidgetItem* userItem = new QListWidgetItem(user);
                    ui->userListWidget->addItem(userItem);
                }
            }
            nextBlockSize = 0;
        } else if (inType == "ACTION") {
            QString senderName;
            QString action;
            QTime actionTime;

            in >> actionTime >> senderName >> action;
            activeUsernames.insert(senderName);

            ui->messageBrowser->append("<b>" + actionTime.toString() + "</b> " + "<b>" + senderName + "</b> " + action);
            nextBlockSize = 0;
        } else if (inType == "USERNAME") {
            QString newUsername;
            in >> newUsername;
            if (username.isEmpty()) {
                username = newUsername;
                settings->setValue("USER/USERNAME", username);
                activeUsernames.insert(username);
            }
            nextBlockSize = 0;
        } else if (inType == "USERNAMECHANGE") {
            QTime changeTime;
            QString oldName;
            QString newName;

            in >> changeTime >> oldName >> newName;
            if (activeUsernames.contains(oldName)) {
                activeUsernames.remove(oldName);
                activeUsernames.insert(newName);
            }

            ui->messageBrowser->append("<b>" + changeTime.toString() + "</b> " + "<b>" + oldName + "</b> " + "changed name to " + "<b>" + newName + "</b>");
            nextBlockSize = 0;
        } else if (inType == "USERINFO") {
            QString usernameInfo;
            QString userIPInfo;
            QTime userConnectionTimeInfo;
            QString userStatusInfo;

            in >> usernameInfo >> userIPInfo >> userConnectionTimeInfo >> userStatusInfo;
            createUserInfoDialog(usernameInfo, userIPInfo, userConnectionTimeInfo.toString(), userStatusInfo);

            nextBlockSize = 0;
        }
    }
}

QDomElement Client::message(QDomDocument* domDoc, const QString& strTime, const QString& strIP, const QString& strName, const QString& strMessage) {
    QDomElement domElement = makeElement(domDoc, "message", "");
    domElement.appendChild(makeElement(domDoc, "time", strTime));
    domElement.appendChild(makeElement(domDoc, "IP", strIP));
    domElement.appendChild(makeElement(domDoc, "name", strName));
    domElement.appendChild(makeElement(domDoc, "text", strMessage));

    return domElement;
}

QDomElement Client::makeElement(QDomDocument* domDoc, const QString& strElementName, const QString& strText) {
    QDomElement domElement = domDoc->createElement(strElementName);

    if (!strText.isEmpty()) {
        QDomText domText = domDoc->createTextNode(strText);
        domElement.appendChild(domText);
    }

    return domElement;
}

void Client::saveMessageHistory(const QString& fileName) {
    QFile file(fileName + ".xml");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << document->toString();
        file.close();
    }
}

void Client::onSendMessageButtonClicked() {
    sendToServer("MESSAGE", ui->newMessageLine->text());
}

void Client::onNewMessageLineReturnPressed() {
    sendToServer("MESSAGE", ui->newMessageLine->text());
}


void Client::onConnectToServerButtonTriggered() {
    connectToServer();
}


void Client::onDisconnectButtonTriggered() {
    disconnectFromServer();
}

void Client::   onSaveHistoryButtonTriggered() {
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* fileNameLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    QLabel *fileNameLabel = new QLabel();
    fileNameLabel->setText("File name:");
    fileNameLayout->addWidget(fileNameLabel);

    QLineEdit *fileNameLine = new QLineEdit();
    fileNameLine->setText("MessageHistory");
    fileNameLayout->addWidget(fileNameLine);

    boxLayout->addLayout(fileNameLayout);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setModal(true);
    modalDialog->setWindowTitle("Save history");
    modalDialog->setMinimumWidth(220);

    QPushButton *saveMessageHistoryButton = new QPushButton("Save");
    boxLayout->addWidget(saveMessageHistoryButton);
    connect(saveMessageHistoryButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));

    modalDialog->setLayout(boxLayout);

    if (modalDialog->exec() == QDialog::Accepted) {
        saveMessageHistory(fileNameLine->text());
    }

    delete modalDialog;
}

void Client::onExitButtonTriggered() {
    QApplication::quit();
}

void Client::onHelpButtonTriggered() {
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* dataLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* infoLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    QPixmap authorPicture("D:/Documents/C++/Qt/Chat/Client/image.jpg");
    QLabel *authorPictureLabel, *authorName, *buildDate, *buildVersion, *launchVersion;

    authorPictureLabel = new QLabel();
    authorPictureLabel->setPixmap(authorPicture);
    authorPictureLabel->setFixedSize(200, 200);
    authorPictureLabel->setScaledContents(true);

    addLabelToDialog(&authorName, 18, "Author name: Andrey Sivokho", infoLayout);
    addLabelToDialog(&buildDate, 18, "Build date: 10.11.2022", infoLayout);
    addLabelToDialog(&buildVersion, 18, "Build Qt version: 5.15.2", infoLayout);
    addLabelToDialog(&launchVersion, 18, "Launch Qt version: " + QString(qVersion()), infoLayout);

    dataLayout->addWidget(authorPictureLabel);
    dataLayout->addSpacing(20);
    dataLayout->addLayout(infoLayout);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setMinimumWidth(200);
    modalDialog->setWindowTitle("Help");

    QPushButton *closeButton = new QPushButton("Close");
    boxLayout->addLayout(dataLayout);
    boxLayout->addWidget(closeButton);
    connect(closeButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));

    modalDialog->setLayout(boxLayout);
    modalDialog->setFixedSize(570, 250);
    modalDialog->exec();
    delete modalDialog;
}

void Client::onUsernameSettingsButtonTriggered() {
    QString newUsername = username;
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QLineEdit *usernameLine = new QLineEdit();

    usernameLine->setText(newUsername);
    boxLayout->addWidget(usernameLine);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setModal(true);
    modalDialog->setWindowTitle("Username settings");
    modalDialog->setMinimumWidth(220);

    QPushButton *saveUsernameButton = new QPushButton("Save");
    boxLayout->addWidget(saveUsernameButton);
    connect(saveUsernameButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));

    modalDialog->setLayout(boxLayout);
    if (modalDialog->exec() == QDialog::Accepted) {
        if (!activeUsernames.contains(usernameLine->text()) && !usernameLine->text().isEmpty()) {
            activeUsernames.remove(username);
            activeUsernames.insert(usernameLine->text());
            username = usernameLine->text();
            sendToServer("USERNAME", username);
            settings->setValue("USER/USERNAME", username);
        } else if ((username != usernameLine->text() && activeUsernames.contains(usernameLine->text())) || usernameLine->text().isEmpty()) {
            onUsernameSettingsButtonTriggered();
        }
    }

    delete modalDialog;
}

void Client::onServerSettingsButtonTriggered() {
    QRegExp regex("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])");
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* IPLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* portLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    QLabel *IPLabel = new QLabel();
    IPLabel->setText("IP:     ");
    IPLayout->addWidget(IPLabel);
    QLineEdit *IPLine = new QLineEdit();
    IPLine->setText(serverIP);
    IPLayout->addWidget(IPLine);

    QLabel *portLabel = new QLabel();
    portLabel->setText("Port: ");
    portLayout->addWidget(portLabel);
    QSpinBox *portSpinBox = new QSpinBox();
    portSpinBox->setRange(1, 65535);
    portSpinBox->setValue(serverPort);
    portSpinBox->setMinimumWidth(100);
    portLayout->addWidget(portSpinBox);

    boxLayout->addLayout(IPLayout);
    boxLayout->addLayout(portLayout);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setModal(true);
    modalDialog->setWindowTitle("Server settings");
    modalDialog->setMinimumWidth(150);
    QPushButton *saveUsernameButton = new QPushButton("Save");
    boxLayout->addWidget(saveUsernameButton);
    connect(saveUsernameButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));

    modalDialog->setLayout(boxLayout);
    if (modalDialog->exec() == QDialog::Accepted) {
        if (regex.exactMatch(IPLine->text())) {
            serverIP = IPLine->text();
            serverPort = (quint16)portSpinBox->value();
            settings->setValue("SERVER/IP", serverIP);
            settings->setValue("SERVER/PORT", QString::number(serverPort));
            ui->serverSettingsButton->setText("Server: " + serverIP + " " + QString::number(serverPort));
        } else {
            onServerSettingsButtonTriggered();
        }
    }

    delete modalDialog;
}

void Client::onStatusOnlineButtonTriggered() {
    updateStatusCheckBoxes(Status::Online);
    updateUserStatus(Status::Online);
}

void Client::onStatusIdleButtonTriggered() {
    updateStatusCheckBoxes(Status::Idle);
    updateUserStatus(Status::Idle);
}

void Client::onStatusDoNotDisturbButtonTriggered() {
    updateStatusCheckBoxes(Status::DoNotDisturb);
    updateUserStatus(Status::DoNotDisturb);
}

void Client::updateStatusCheckBoxes(Status newStatus) {
    statusOnlineCheckBox->setChecked(newStatus == Status::Online);
    statusIdleCheckBox->setChecked(newStatus == Status::Idle);
    statusDoNotDisturbCheckBox->setChecked(newStatus == Status::DoNotDisturb);
}

void Client::updateUserStatus(Status newStatus) {
    userStatusBeforeDisconnect = newStatus;
    settings->setValue("USER/STATUS", statusToString[newStatus]);
    if (userStatus != Status::Disconnected) {
        userStatus = newStatus;
        updateWindowStatus();
        sendToServer("STATUS", statusToString[newStatus]);
    }
}

void Client::onUserItemClicked(QPoint pos) {
    QListWidgetItem* item = ui->userListWidget->itemAt(pos);
    if (item != nullptr) {
        sendToServer("USERINFO", item->text());
    }
}

void Client::addStatusButtonToMenu(QCheckBox** checkBox, QWidgetAction** widgetAction, const QString& checkBoxText, bool isChecked) {
    *checkBox = new QCheckBox(ui->menuStatus);
    (*checkBox)->setText(checkBoxText);
//    (*checkBox)->setIcon(QPixmap(checkBoxIcon));
    (*checkBox)->setChecked(isChecked);
    *widgetAction = new QWidgetAction(ui->menuStatus);
    (*widgetAction)->setDefaultWidget(*checkBox);
    ui->menuStatus->addAction(*widgetAction);
//    ui->menuStatus->setIcon(QPixmap(checkBoxIcon));
}

void Client::createUserInfoDialog(const QString& usernameInfo, const QString& userIPInfo, const QString& userConnectionTimeInfo, const QString& userStatusInfo) {
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    QLabel *IPLabel, *connectionLabel, *statusLabel;
    addLabelToDialog(&IPLabel, 10, "IP: " + userIPInfo, boxLayout);
    addLabelToDialog(&connectionLabel, 10, "Connection time: " + userConnectionTimeInfo, boxLayout);
    addLabelToDialog(&statusLabel, 10, "Status: " + userStatusInfo, boxLayout);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setMinimumWidth(200);
    modalDialog->setWindowTitle(usernameInfo);

    QPushButton *closeButton = new QPushButton("Close");
    boxLayout->addWidget(closeButton);
    connect(closeButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));

    modalDialog->setLayout(boxLayout);
    modalDialog->exec();
    delete modalDialog;
}

void Client::addLabelToDialog(QLabel** label, const int fontSize, const QString& labelText, QBoxLayout* boxLayout) {
    *label = new QLabel();
    QFont font = (*label)->font();
    font.setPointSize(fontSize);
    (*label)->setFont(font);
    (*label)->setText(labelText);
    boxLayout->addWidget(*label);
}
