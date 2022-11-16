#include "Client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    this->setWindowTitle("Disconnected");
    ui->setupUi(this);

    settings = new QSettings("settings.ini", QSettings::IniFormat);

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
        settings->setValue("USER/STATUS", "Online");
    }

    if (!settings->contains("USER/CUSTOMSTATUS")) {
        settings->setValue("USER/CUSTOMSTATUS", "Other");
    }

    if (!settings->contains("USER/USERNAME")) {
        settings->setValue("USER/USERNAME", "");
    }

    if (!settings->contains("USER/USERPHOTOPATH")) {
        settings->setValue("USER/USERPHOTOPATH", defaultUserPhotoPath);
    }

    serverIP = settings->value("SERVER/IP", "").toString();
    serverPort = settings->value("SERVER/PORT", "").toUInt();
    userStatusBeforeDisconnect = settings->value("USER/STATUS", "").toString();
    userStatus = "Disconnected";
    customUserStatus = settings->value("USER/CUSTOMSTATUS", "").toString();
    username = settings->value("USER/USERNAME", "").toString();
    userPhotoPath = settings->value("USER/USERPHOTOPATH").toString();
    userPhoto = QPixmap(userPhotoPath);

    ui->serverSettingsButton->setText("Server: " + serverIP + " " + QString::number(serverPort));

    connect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(onSendMessageButtonClicked()));
    connect(ui->sendMessageButton, SIGNAL(rightClick(QMouseEvent*)), this, SLOT(onSendMessageButtonRightClicked(QMouseEvent*)));
    connect(ui->newMessageLine, SIGNAL(returnPressed()), this, SLOT(onNewMessageLineReturnPressed()));
    connect(ui->connectToServerButton, SIGNAL(triggered()), this, SLOT(onConnectToServerButtonTriggered()));
    connect(ui->disconnectButton, SIGNAL(triggered()), this, SLOT(onDisconnectButtonTriggered()));
    connect(ui->saveHistoryButton, SIGNAL(triggered()), this, SLOT(onSaveHistoryButtonTriggered()));
    connect(ui->exitButton, SIGNAL(triggered()), this, SLOT(onExitButtonTriggered()));
    connect(ui->usernameSettingsButton, SIGNAL(triggered()), this, SLOT(onUsernameSettingsButtonTriggered()));
    connect(ui->actionUser_photo, SIGNAL(triggered()), this, SLOT(onUserPhotoSettingsButtonTriggered()));
    connect(ui->serverSettingsButton, SIGNAL(triggered()), this, SLOT(onServerSettingsButtonTriggered()));
    connect(ui->messageListWidget, SIGNAL(rightClickOnMessage(QMouseEvent*)), this, SLOT(onMessageClicked(QMouseEvent*)));
    connect(ui->userListWidget, SIGNAL(rightClick(QPoint)), this, SLOT(onUserItemClicked(QPoint)));

    QAction* helpAction = new QAction("Help", ui->menubar);
    ui->menubar->addAction(helpAction);
    ui->menubar->connect(helpAction, SIGNAL(triggered()), this, SLOT(onHelpButtonTriggered()));

    QWidgetAction *statusOnlineButton, *statusIdleButton, *statusDoNotDisturbButton, *statusOtherButton;
    addStatusButtonToMenu(&statusOnlineCheckBox, &statusOnlineButton, "Online", userStatusBeforeDisconnect == "Online");
    addStatusButtonToMenu(&statusIdleCheckBox, &statusIdleButton, "Idle", userStatusBeforeDisconnect == "Idle");
    addStatusButtonToMenu(&statusDoNotDisturbCheckBox, &statusDoNotDisturbButton, "Do Not Disturb", userStatusBeforeDisconnect == "Do Not Disturb");
    addStatusButtonToMenu(&statusOtherCheckBox, &statusOtherButton, customUserStatus, userStatusBeforeDisconnect == customUserStatus);
    connect(statusOnlineCheckBox, SIGNAL(clicked()), this, SLOT(onStatusOnlineButtonTriggered()));
    connect(statusIdleCheckBox, SIGNAL(clicked()), this, SLOT(onStatusIdleButtonTriggered()));
    connect(statusDoNotDisturbCheckBox, SIGNAL(clicked()), this, SLOT(onStatusDoNotDisturbButtonTriggered()));
    connect(statusOtherCheckBox, SIGNAL(clicked()), this, SLOT(onStatusOtherButtonTriggered()));

    userSocket = new QSslSocket;

    nextBlockSize = 0;

    newMessageSound = new QSound("newmessagesound.wav");

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
    if (userStatus == "Disconnected") {
//        setUpSocket();
//
        userStatus = userStatusBeforeDisconnect;
        userSocket->connectToHost(serverIP, serverPort);
//        userSocket->connectToHostEncrypted(serverIP, serverPort);
//        if (!username.isEmpty()) {
//            sendToServer("USERNAME", username);
//        }
    } else {
        addMessageToMessageListWidget(boldCurrentTime() + " You are already connected to" + serverIP + " " + QString::number(serverPort));
    }
}

void Client::disconnectFromServer() {
    if (userStatus != "Disconnected") {
        userStatusBeforeDisconnect = userStatus;
        settings->setValue("USER/STATUS", userStatus);
        userSocket->disconnectFromHost();
        setDisconnectedStatus();
        addMessageToMessageListWidget(boldCurrentTime() + " Disconnected from" + serverIP + " " + QString::number(serverPort));
        ui->userListWidget->clear();
    } else {
        addMessageToMessageListWidget(boldCurrentTime() + " You are not connected to server");
    }
}

void Client::slotConnected() {
    ui->sendMessageButton->setEnabled(true);
    ui->newMessageLine->setReadOnly(false);

    userStatus = userStatusBeforeDisconnect;
    settings->setValue("USER/STATUS", userStatus);

    if (!username.isEmpty()) {
        sendToServer("USERNAME", username);
        userSocket->waitForBytesWritten(100000);
        userSocket->waitForReadyRead(100000);
    }

    sendToServer("STATUS", userStatus);
    userSocket->waitForBytesWritten(100000);

    if (userPhotoPath != defaultUserPhotoPath) {
        sendToServer("USERPHOTO", "");
    }

    updateWindowStatus();
    ui->serverSettingsButton->setText("Server: " + serverIP + " " + QString::number(serverPort));
    addMessageToMessageListWidget(boldCurrentTime() + " Connected to" + serverIP + " " + QString::number(serverPort));
}

void Client::slotError(QAbstractSocket::SocketError /*error*/) {
    if (userStatus != "Disconnected") {
        userStatusBeforeDisconnect = userStatus;
        ui->userListWidget->clear();
    }
    setDisconnectedStatus();
    addMessageToMessageListWidget(boldCurrentTime() + " Connection failed: " + userSocket->errorString());
    userSocket->disconnectFromHost();
}

void Client::setDisconnectedStatus() {
    ui->sendMessageButton->setEnabled(false);
    ui->newMessageLine->setReadOnly(true);
    userStatus = "Disconnected";
    this->setWindowTitle("Client | Status: Disconnected");
}

void Client::updateWindowStatus() {
    this->setWindowTitle("Client | IP:" + serverIP + " Port: " + QString::number(serverPort) + " Status: " + userStatus);
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
    } else if (sendType == "USERNAME" || sendType == "STATUS" || sendType == "USERINFO" || sendType == "ISNEWUSERNAMEACTIVE") {
        out << quint16(0) << sendType << message;
        out.device()->seek(0);
        out << quint16(messageData.size() - sizeof(quint16));
        userSocket->write(messageData);
    } else if (sendType == "USERPHOTO") {
        out << quint16(0) << sendType << userPhoto;
        qDebug() << userPhoto.size();
        out.device()->seek(0);
        out << quint16(messageData.size() - sizeof(quint16));
        userSocket->write(messageData);
    } else if (sendType == "PHOTO") {
        qDebug() << "Sending photo";
        QPixmap photo = QPixmap(message);
        out << quint16(0) << sendType << photo;
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
            if (userStatus != "Do Not Disturb" && senderName != username) {
                newMessageSound->play();
            }
            addMessageToMessageListWidget("<b>" + messageTime.toString() + "</b> " + "<b>[" + senderIP + " : " + senderName + "]</b> " + messageText);
            nextBlockSize = 0;

            QDomElement newMessage = message(document, messageTime.toString(), senderIP, senderName, messageText);
            domElement.appendChild(newMessage);
        } else if (inType == "USERLIST") {
            ui->userListWidget->clear();
            int userListSize;
            in >> userListSize;
            QString tempUserName;
            QPixmap tempUserPhoto = QPixmap();
            for (int i = 0; i < userListSize; ++i) {
                in >> tempUserName >> tempUserPhoto;
                QListWidgetItem* userItem = new QListWidgetItem(tempUserPhoto, tempUserName);
                ui->userListWidget->addItem(userItem);
            }
            nextBlockSize = 0;
        } else if (inType == "ACTION") {
            QString senderName;
            QString action;
            QTime actionTime;

            in >> actionTime >> senderName >> action;
            addMessageToMessageListWidget("<b>" + actionTime.toString() + "</b> " + "<b>" + senderName + "</b> " + action);
            nextBlockSize = 0;
        } else if (inType == "USERNAME") {
            QString newUsername;
            in >> newUsername;
            if (username.isEmpty()) {
                username = newUsername;
                settings->setValue("USER/USERNAME", username);
            }
            nextBlockSize = 0;
        } else if (inType == "USERNAMECHANGE") {
            QTime changeTime;
            QString oldName;
            QString newName;

            in >> changeTime >> oldName >> newName;
            addMessageToMessageListWidget("<b>" + changeTime.toString() + "</b> " + "<b>" + oldName + "</b> " + "changed name to " + "<b>" + newName + "</b>");
            nextBlockSize = 0;
        } else if (inType == "USERINFO") {
            QString usernameInfo;
            QString userIPInfo;
            QTime userConnectionTimeInfo;
            QString userStatusInfo;
            QPixmap userPhotoInfo;

            in >> usernameInfo >> userIPInfo >> userConnectionTimeInfo >> userStatusInfo >> userPhotoInfo;
            createUserInfoDialog(usernameInfo, userIPInfo, userConnectionTimeInfo.toString(), userStatusInfo, userPhotoInfo);

            nextBlockSize = 0;
        } else if (inType == "ISNEWUSERNAMEACTIVE") {
            in >> isNewUsernameActive;
            nextBlockSize = 0;
        } else if (inType == "PHOTO") {
            QPixmap sendedPhoto = QPixmap();
            in >> sendedPhoto;
            addPhotoToMessageListWidget(sendedPhoto);
            nextBlockSize = 0;
            QPixmap photoCopy = sendedPhoto.scaled(240, 320);
            QDomElement newPhoto = photo(document, photoCopy);
            domElement.appendChild(newPhoto);
        }
    }
}

void Client::addMessageToMessageListWidget(const QString& messageText) {
    QListWidgetItem* messageItem = new QListWidgetItem();
    QTextEdit *messageLabel = new QTextEdit(messageText);
    messageLabel->setAlignment(Qt::AlignVCenter);
    messageItem->setSizeHint(QSize(0, 30));
    ui->messageListWidget->addItem(messageItem);
    ui->messageListWidget->setItemWidget(messageItem, messageLabel);
    ui->messageListWidget->scrollToBottom();

//    QString str = "";
//    for (int i = 0; i < messageText.length() + 120; ++i) {
//        str += " ";
//    }
//    QListWidgetItem* messageItem = new QListWidgetItem();
//    QLabel *messageLabel = new QLabel(messageText);
//    ui->messageListWidget->addItem(messageItem);
//    ui->messageListWidget->setItemWidget(messageItem, messageLabel);
//    ui->messageListWidget->scrollToBottom();
}

void Client::addPhotoToMessageListWidget(QPixmap photo) {
    QLabel *messageLabel = new QLabel();
    messageLabel->setPixmap(photo);
    messageLabel->setFixedSize(photo.width() > 240 ? 240 : photo.width(), photo.height() > 320 ? 320 : photo.height());
    messageLabel->setScaledContents(true);
    QListWidgetItem* messageItem = new QListWidgetItem();
    messageItem->setSizeHint(QSize(messageLabel->width(), messageLabel->height()));
    ui->messageListWidget->addItem(messageItem);
    ui->messageListWidget->setItemWidget(messageItem, messageLabel);
    ui->messageListWidget->scrollToBottom();
}

QDomElement Client::message(QDomDocument* domDoc, const QString& strTime, const QString& strIP, const QString& strName, const QString& strMessage) {
    QDomElement domElement = makeElement(domDoc, "message", "");
    domElement.appendChild(makeElement(domDoc, "time", strTime));
    domElement.appendChild(makeElement(domDoc, "IP", strIP));
    domElement.appendChild(makeElement(domDoc, "name", strName));
    domElement.appendChild(makeElement(domDoc, "text", strMessage));

    return domElement;
}

QDomElement Client::photo(QDomDocument* domDoc, QPixmap sendedPhoto) {
    QDomElement domElement = makeElement(domDoc, "photo", "");
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    sendedPhoto.save(&buffer, "PNG");
    domElement.appendChild(makeElement(domDoc, "Base64", QString(buffer.data().toBase64())));
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
    if (!ui->newMessageLine->text().isEmpty()) {
       sendToServer("MESSAGE", ui->newMessageLine->text());
    }
}

void Client::onSendMessageButtonRightClicked(QMouseEvent* event) {
    QMenu actionMenu(this);
    QAction* sendPhoto = new QAction("Send Photo", &actionMenu);
    actionMenu.addAction(sendPhoto);
    actionMenu.connect(sendPhoto, SIGNAL(triggered()), this, SLOT(onSendPhotoActionTriggered()));
    actionMenu.exec(event->globalPos());
}

void Client::onSendPhotoButtonRightClicked(QMouseEvent* event) {
    QMenu actionMenu(this);
    QAction* sendMessage = new QAction("Send Message", &actionMenu);
    actionMenu.addAction(sendMessage);
    actionMenu.connect(sendMessage, SIGNAL(triggered()), this, SLOT(onSendMessageActionTriggered()));
    actionMenu.exec(event->globalPos());
}

void Client::onSendMessageActionTriggered() {
    disconnect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(onSendPhotoButtonClicked()));
    ui->newMessageLine->setDisabled(false);
    disconnect(ui->sendMessageButton, SIGNAL(rightClick(QMouseEvent*)), this, SLOT(onSendPhotoButtonRightClicked(QMouseEvent*)));
    connect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(onSendMessageButtonClicked()));
    connect(ui->sendMessageButton, SIGNAL(rightClick(QMouseEvent*)), this, SLOT(onSendMessageButtonRightClicked(QMouseEvent*)));
    ui->sendMessageButton->setText("Send message");
}

void Client::onSendPhotoActionTriggered() {
    disconnect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(onSendMessageButtonClicked()));
    ui->newMessageLine->setDisabled(true);
    disconnect(ui->sendMessageButton, SIGNAL(rightClick(QMouseEvent*)), this, SLOT(onSendMessageButtonRightClicked(QMouseEvent*)));
    connect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(onSendPhotoButtonClicked()));
    connect(ui->sendMessageButton, SIGNAL(rightClick(QMouseEvent*)), this, SLOT(onSendPhotoButtonRightClicked(QMouseEvent*)));
    ui->sendMessageButton->setText("Send photo");
}

void Client::onSendPhotoButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose Photo"), "/home", tr("Images (*.png)"));
    if (!fileName.isEmpty()) {
        sendToServer("PHOTO", fileName);
    }
}

void Client::onNewMessageLineReturnPressed() {
    if (!ui->newMessageLine->text().isEmpty()) {
       sendToServer("MESSAGE", ui->newMessageLine->text());
    }
}


void Client::onConnectToServerButtonTriggered() {
    connectToServer();
}


void Client::onDisconnectButtonTriggered() {
    disconnectFromServer();
}

void Client::onSaveHistoryButtonTriggered() {
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

    QPixmap authorPicture("authorphoto.jpg");
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
        sendToServer("ISNEWUSERNAMEACTIVE", usernameLine->text());
        userSocket->waitForReadyRead(100000);
        if (!isNewUsernameActive && !usernameLine->text().isEmpty()) {
            username = usernameLine->text();
            sendToServer("USERNAME", username);
            settings->setValue("USER/USERNAME", username);
        } else if ((username != usernameLine->text() && isNewUsernameActive) || usernameLine->text().isEmpty()) {
            onUsernameSettingsButtonTriggered();
        }
    }

    delete modalDialog;
}

void Client::onUserPhotoSettingsButtonTriggered() {
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* photoLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* buttonLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    userPhotoLabel = new QLabel();
    userPhotoLabel->setPixmap(userPhoto);
    userPhotoLabel->setFixedSize(250, 250);
    userPhotoLabel->setScaledContents(true);
    photoLayout->addWidget(userPhotoLabel);

    QPushButton *defaultUserPhotoButton = new QPushButton("Default");
    QPushButton *chooseUserPhotoButton = new QPushButton("Choose");
    QPushButton *saveUserPhotoButton = new QPushButton("Save");
    buttonLayout->addWidget(chooseUserPhotoButton);
    buttonLayout->addWidget(defaultUserPhotoButton);
    buttonLayout->addWidget(saveUserPhotoButton);

    boxLayout->addLayout(photoLayout);
    boxLayout->addLayout(buttonLayout);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setModal(true);
    modalDialog->setWindowTitle("Photo settings");
    modalDialog->setLayout(boxLayout);

    connect(defaultUserPhotoButton, SIGNAL(clicked()), this, SLOT(onDefaultUserPhotoButtonClicked()));
    connect(chooseUserPhotoButton, SIGNAL(clicked()), this, SLOT(onChooseUserPhotoButtonClicked()));
    connect(saveUserPhotoButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));

    if (modalDialog->exec() == QDialog::Accepted) {
        userPhotoPath = newUserPhotoPath;
        userPhoto = QPixmap(userPhotoPath);
        settings->setValue("USER/USERPHOTOPATH", userPhotoPath);
        sendToServer("USERPHOTO", "");
    }

    delete modalDialog;
}

void Client::onChooseUserPhotoButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose Photo"), "/home", tr("Images (*.png)"));
    if (!fileName.isEmpty()) {
        newUserPhotoPath = fileName;
        userPhotoLabel->setPixmap(QPixmap(fileName));
    }
}

void Client::onDefaultUserPhotoButtonClicked() {
    newUserPhotoPath = defaultUserPhotoPath;
    userPhotoLabel->setPixmap(QPixmap(newUserPhotoPath));
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
    updateStatusCheckBoxes("Online");
    updateUserStatus("Online");
}

void Client::onStatusIdleButtonTriggered() {
    updateStatusCheckBoxes("Idle");
    updateUserStatus("Idle");
}

void Client::onStatusDoNotDisturbButtonTriggered() {
    updateStatusCheckBoxes("Do Not Disturb");
    updateUserStatus("Do Not Disturb");
}

void Client::onStatusOtherButtonTriggered() {
    QString newCustomStatus = customUserStatus;
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QLineEdit *customStatusLine = new QLineEdit();

    customStatusLine->setText(newCustomStatus);
    boxLayout->addWidget(customStatusLine);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setModal(true);
    modalDialog->setWindowTitle("Other status");
    modalDialog->setMinimumWidth(220);

    QPushButton *saveUsernameButton = new QPushButton("Save");
    boxLayout->addWidget(saveUsernameButton);
    connect(saveUsernameButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));

    modalDialog->setLayout(boxLayout);
    if (modalDialog->exec() == QDialog::Accepted) {
        customUserStatus = customStatusLine->text();
        if (customUserStatus.length() > 16) {
            QString statusOtherCheckBoxText = "";
            for (int i = 0; i < 16; ++i) {
                statusOtherCheckBoxText += customUserStatus[i];
            }
            statusOtherCheckBoxText += "...";
            statusOtherCheckBox->setText(statusOtherCheckBoxText);
        } else {
           statusOtherCheckBox->setText(customUserStatus);
        }

        updateStatusCheckBoxes(customUserStatus);
        updateUserStatus(customUserStatus);
        settings->setValue("USER/CUSTOMSTATUS", customUserStatus);
    }

    delete modalDialog;
}

void Client::updateStatusCheckBoxes(QString newStatus) {
    statusOnlineCheckBox->setChecked(newStatus == "Online");
    statusIdleCheckBox->setChecked(newStatus == "Idle");
    statusDoNotDisturbCheckBox->setChecked(newStatus == "Do Not Disturb");
    statusOtherCheckBox->setChecked(newStatus == customUserStatus);
}

void Client::updateUserStatus(QString newStatus) {
    userStatusBeforeDisconnect = newStatus;
    settings->setValue("USER/STATUS", newStatus);
    if (userStatus != "Disconnected") {
        userStatus = newStatus;
        updateWindowStatus();
        sendToServer("STATUS", newStatus);
    }
}

void Client::onMessageClicked(QMouseEvent* event) {
    QListWidgetItem* selectedMessage = ui->messageListWidget->itemAt(event->pos());
    selectedMessageLabel = dynamic_cast<QLabel*>(ui->messageListWidget->itemWidget(selectedMessage));
    if (selectedMessageLabel->text().isEmpty()) {
        QMenu actionMenu(this);
        QAction* openInFullSizeAction = new QAction("Open in full size", &actionMenu);
        QAction* savePhotoAction = new QAction("Save photo", &actionMenu);
        actionMenu.addAction(openInFullSizeAction);
        actionMenu.addAction(savePhotoAction);
        actionMenu.connect(openInFullSizeAction, SIGNAL(triggered()), this, SLOT(onOpenInFullSizeActionTriggered()));
        actionMenu.connect(savePhotoAction, SIGNAL(triggered()), this, SLOT(onSavePhotoActionTriggered()));
        actionMenu.exec(event->globalPos());
    }
}

void Client::onOpenInFullSizeActionTriggered() {
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    const QPixmap *photo = selectedMessageLabel->pixmap();
    QLabel* photoLabel = new QLabel();
    photoLabel->setPixmap(*photo);
    photoLabel->setScaledContents(true);
    boxLayout->addWidget(photoLabel);

    QPushButton *closeFullSizePhotoButton = new QPushButton("Close");
    boxLayout->addWidget(closeFullSizePhotoButton);

    QDialog *modalDialog = new QDialog();
    modalDialog->setModal(false);
    modalDialog->setWindowTitle("Photo");
    modalDialog->setLayout(boxLayout);
    connect(closeFullSizePhotoButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));
    if (modalDialog->exec() == QDialog::Accepted) {
        delete modalDialog;
    }
}

void Client::onSavePhotoActionTriggered() {
    const QPixmap *photo = selectedMessageLabel->pixmap();
    QString strFilter = "*.png";
    QString savePhotoPath = QFileDialog::getSaveFileName(0, "Save photo", "/home", "*.png", &strFilter);
    if (!savePhotoPath.isEmpty()) {
        photo->save(savePhotoPath, "PNG");
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
    if (checkBoxText.length() > 16) {
        QString newCheckBoxText = "";
        for (int i = 0; i < 16; ++i) {
            newCheckBoxText += checkBoxText[i];
        }
        newCheckBoxText += "...";
        (*checkBox)->setText(newCheckBoxText);
    } else {
       (*checkBox)->setText(checkBoxText);
    }
    (*checkBox)->setChecked(isChecked);
    *widgetAction = new QWidgetAction(ui->menuStatus);
    (*widgetAction)->setDefaultWidget(*checkBox);
    ui->menuStatus->addAction(*widgetAction);
}

void Client::createUserInfoDialog(const QString& usernameInfo, const QString& userIPInfo, const QString& userConnectionTimeInfo, const QString& userStatusInfo, const QPixmap& userPhotoInfo) {
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* infoLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* photoLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* dataLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    QLabel *IPLabel, *connectionLabel, *statusLabel;
    addLabelToDialog(&IPLabel, 10, "IP: " + userIPInfo, dataLayout);
    addLabelToDialog(&connectionLabel, 10, "Connection time: " + userConnectionTimeInfo, dataLayout);
    addLabelToDialog(&statusLabel, 10, "Status: " + userStatusInfo, dataLayout);

    QLabel *userPhotoLabel = new QLabel();
    userPhotoLabel->setPixmap(userPhotoInfo);
    userPhotoLabel->setFixedSize(150, 150);
    userPhotoLabel->setScaledContents(true);
    photoLayout->addWidget(userPhotoLabel);

    infoLayout->addLayout(photoLayout);
    infoLayout->addSpacing(10);
    infoLayout->addLayout(dataLayout);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setMinimumWidth(200);
    modalDialog->setWindowTitle(usernameInfo);

    QPushButton *closeButton = new QPushButton("Close");
    boxLayout->addLayout(infoLayout);
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
