#ifndef CLIENT_H
#define CLIENT_H

#include <helpdialog.h>
#include <userinfodialog.h>
#include <UserListWidget.h>
#include <includes.h>

enum class Status {
    Online,
    Idle,
    DoNotDisturb,
    Disconnected
};

//static QSettings settings("D:/Documents/C++/Qt/Chat/Client/settings.ini", QSettings::IniFormat);

static QMap<Status, QString> statusToString{{Status::Online, "ONLINE"}, {Status::Idle, "IDLE"}, {Status::DoNotDisturb, "DONOTDISTURB"}, {Status::Disconnected, "DISCONNECTED"}};
static QMap<QString, Status> stringToStatus{{"ONLINE", Status::Online}, {"IDLE", Status::Idle}, {"DONOTDISTURB", Status::DoNotDisturb}, {"DISCONNECTED", Status::Disconnected}};

namespace Ui {
class Client;
}

class Client : public QMainWindow {
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void onSendMessageButtonClicked();
    void onNewMessageLineReturnPressed();
    void onConnectToServerButtonTriggered();
    void onDisconnectButtonTriggered();
    void onSaveHistoryButtonTriggered();
    void onExitButtonTriggered();
    void onHelpButtonTriggered();
    void onUsernameSettingsButtonTriggered();
    void onServerSettingsButtonTriggered();
    void onStatusOnlineButtonTriggered();
    void onStatusIdleButtonTriggered();
    void onStatusDoNotDisturbButtonTriggered();
    void onUserItemClicked(QPoint);

    void slotConnected();
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError error);

private:
    Ui::Client *ui;
    QCheckBox *statusOnlineCheckBox;
    QCheckBox *statusIdleCheckBox;
    QCheckBox *statusDoNotDisturbCheckBox;

    QSettings* settings;

    QDomDocument* document;
    QDomElement domElement;

    QDomElement message(QDomDocument*, const QString&, const QString&, const QString&, const QString&);
    QDomElement makeElement(QDomDocument*, const QString&, const QString&);

    void setUpSocket();
    void connectToServer();
    void disconnectFromServer();
    void sendToServer(const QString&, const QString&);

    void updateWindowStatus();
    void updateUserStatus(Status);
    void updateStatusCheckBoxes(Status);
    void setDisconnectedStatus();

    void addStatusButtonToMenu(QCheckBox**, QWidgetAction**, const QString&, bool);
    void createUserInfoDialog(const QString&, const QString&, const QString&, const QString&);
    void addLabelToDialog(QLabel**, const int, const QString&, QBoxLayout*);

    void saveMessageHistory(const QString&);

    QString boldCurrentTime();

    QSslSocket *userSocket;
    QString username = "";
    Status userStatus;
    Status userStatusBeforeDisconnect;

    QSet<QString> activeUsernames;

    QByteArray messageData;
    quint16 nextBlockSize;

    QSound* newMessageSound;

    QString serverIP = "127.0.0.1";
    quint16 serverPort = (quint16)45678;
};

#endif // CLIENT_H
