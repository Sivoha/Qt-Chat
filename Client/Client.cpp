#include "Client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    this->setWindowTitle("Disconnected");
    ui->setupUi(this);

    connect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(onSendMessageButtonClicked()));
    connect(ui->newMessageLine, SIGNAL(returnPressed()), this, SLOT(onNewMessageLineReturnPressed()));
    connect(ui->connectToServerButton, SIGNAL(triggered()), this, SLOT(onConnectToServerButtonTriggered()));
    connect(ui->disconnectButton, SIGNAL(triggered()), this, SLOT(onDisconnectButtonTriggered()));
    connect(ui->exitButton, SIGNAL(triggered()), this, SLOT(onExitButtonTriggered()));
    connect(ui->usernameSettingsButton, SIGNAL(triggered()), this, SLOT(onUsernameSettingsButtonTriggered()));
    connect(ui->serverSettingsButton, SIGNAL(triggered()), this, SLOT(onServerSettingsButtonTriggered()));
    connect(ui->userListWidget, SIGNAL(rightClick(QPoint)), this, SLOT(onUserItemClicked(QPoint)));

    QAction* helpAction = new QAction("Help", ui->menubar);
    ui->menubar->addAction(helpAction);
    ui->menubar->connect(helpAction, SIGNAL(triggered()), this, SLOT(onHelpButtonTriggered()));

    QWidgetAction *statusOnlineButton, *statusIdleButton, *statusDoNotDisturbButton;
    addStatusButtonToMenu(&statusOnlineCheckBox, &statusOnlineButton, "Online", true);
    addStatusButtonToMenu(&statusIdleCheckBox, &statusIdleButton, "Idle", false);
    addStatusButtonToMenu(&statusDoNotDisturbCheckBox, &statusDoNotDisturbButton, "Do Not Disturb", false);

    connect(statusOnlineCheckBox, SIGNAL(clicked()), this, SLOT(onStatusOnlineButtonTriggered()));
    connect(statusIdleCheckBox, SIGNAL(clicked()), this, SLOT(onStatusIdleButtonTriggered()));
    connect(statusDoNotDisturbCheckBox, SIGNAL(clicked()), this, SLOT(onStatusDoNotDisturbButtonTriggered()));

    userSocket = new QSslSocket;
    userStatus = Status::Disconnected;
    userStatusBeforeDisconnect = Status::Online;
    nextBlockSize = 0;

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

void Client::connectToServer() {
    if (userStatus == Status::Disconnected) {
        userSocket->connectToHost(serverIP, serverPort);
        if (!username.isEmpty()) {
            sendToServer("USERNAME", username);
        }
    } else {
        ui->messageBrowser->append(boldCurrentTime() + " You are already connected to" + serverIP + " " + QString::number(serverPort));
    }
}

void Client::disconnectFromServer() {
    if (userStatus != Status::Disconnected) {
        userStatusBeforeDisconnect = userStatus;
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
    sendToServer("STATUS", statusToString[userStatus]);
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
    } else if (sendType == "USERNAME" || sendType == "STATUS" || sendType == "USERINFO") {
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
        qDebug() << "HERE " << inType;
        if (inType == "MESSAGE") {
            QString messageText;
            QString senderName;
            QTime messageTime;

            in >> messageTime >> senderName >> messageText;
            ui->messageBrowser->append("<b>" + messageTime.toString() + "</b> " + "<b>[" + senderName + "]</b> " + messageText);
            nextBlockSize = 0;
        } else if (inType == "USERLIST") {
            ui->userListWidget->clear();
            QString usernames;

            in >> usernames;
            QStringList userList = usernames.split(" ");

            for (auto user : userList) {
                if (!user.isEmpty()) {
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
            ui->messageBrowser->append("<b>" + actionTime.toString() + "</b> " + "<b>" + senderName + "</b> " + action);
            nextBlockSize = 0;
        } else if (inType == "USERNAME") {
            QString newUsername;
            in >> newUsername;
            if (username.isEmpty()) {
                username = newUsername;
            }
            nextBlockSize = 0;
        } else if (inType == "USERNAMECHANGE") {
            QTime changeTime;
            QString oldName;
            QString newName;

            in >> changeTime >> oldName >> newName;
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


void Client::onExitButtonTriggered() {
    QApplication::quit();
}

void Client::onHelpButtonTriggered() {
    helpDialog* help = new helpDialog();
    help->show();
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
        username = usernameLine->text();
        sendToServer("USERNAME", username);
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
            serverPort = portSpinBox->value();
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
    (*checkBox)->setChecked(isChecked);
    *widgetAction = new QWidgetAction(ui->menuStatus);
    (*widgetAction)->setDefaultWidget(*checkBox);
    ui->menuStatus->addAction(*widgetAction);
}

void Client::createUserInfoDialog(const QString& usernameInfo, const QString& userIPInfo, const QString& userConnectionTimeInfo, const QString& userStatusInfo) {
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    QLabel *IPLabel, *connectionLabel, *statusLabel;
    addLabelToUserInfoDialog(&IPLabel, 10, "IP: " + userIPInfo, boxLayout);
    addLabelToUserInfoDialog(&connectionLabel, 10, "Connection time: " + userConnectionTimeInfo, boxLayout);
    addLabelToUserInfoDialog(&statusLabel, 10, "Status: " + userStatusInfo, boxLayout);

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

void Client::addLabelToUserInfoDialog(QLabel** label, const int fontSize, const QString& labelText, QBoxLayout* boxLayout) {
    *label = new QLabel();
    QFont font = (*label)->font();
    font.setPointSize(fontSize);
    (*label)->setFont(font);
    (*label)->setText(labelText);
    boxLayout->addWidget(*label);
}
