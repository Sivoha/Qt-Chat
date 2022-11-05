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

static QMap<Status, QString> statusToString{{Status::Online, "ONLINE"}, {Status::Idle, "IDLE"}, {Status::DoNotDisturb, "DONOTDISTURB"}};

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

    void connectToServer();
    void disconnectFromServer();
    void sendToServer(const QString&, const QString&);

    void updateWindowStatus();
    void updateUserStatus(Status);
    void updateStatusCheckBoxes(Status);
    void setDisconnectedStatus();

    void addStatusButtonToMenu(QCheckBox**, QWidgetAction**, const QString&, bool);
    void createUserInfoDialog(const QString&, const QString&, const QString&, const QString&);
    void addLabelToUserInfoDialog(QLabel**, const int, const QString&, QBoxLayout*);

    QString boldCurrentTime();

    QSslSocket *userSocket;
    QString username = "";
    Status userStatus;
    Status userStatusBeforeDisconnect;

    QByteArray messageData;
    quint16 nextBlockSize;

    QString serverIP = "127.0.0.5";
    qint16 serverPort = 27910;
};

#endif // CLIENT_H
