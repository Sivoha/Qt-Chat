#ifndef CLIENT_H
#define CLIENT_H

#include <helpdialog.h>
#include <userinfodialog.h>
#include <UserListWidget.h>
#include <includes.h>

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
    void onSendPhotoButtonClicked();
    void onSendMessageButtonRightClicked(QMouseEvent*);
    void onSendPhotoButtonRightClicked(QMouseEvent*);
    void onNewMessageLineReturnPressed();
    void onConnectToServerButtonTriggered();
    void onDisconnectButtonTriggered();
    void onSaveHistoryButtonTriggered();
    void onExitButtonTriggered();
    void onHelpButtonTriggered();
    void onUsernameSettingsButtonTriggered();
    void onUserPhotoSettingsButtonTriggered();
    void onChooseUserPhotoButtonClicked();
    void onDefaultUserPhotoButtonClicked();
    void onServerSettingsButtonTriggered();
    void onStatusOnlineButtonTriggered();
    void onStatusIdleButtonTriggered();
    void onStatusDoNotDisturbButtonTriggered();
    void onStatusOtherButtonTriggered();
    void onUserItemClicked(QPoint);
    void onMessageClicked(QMouseEvent*);
    void onOpenInFullSizeActionTriggered();
    void onSavePhotoActionTriggered();

    void onSendMessageActionTriggered();
    void onSendPhotoActionTriggered();

    void slotConnected();
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError error);

private:
    Ui::Client *ui;
    QCheckBox *statusOnlineCheckBox;
    QCheckBox *statusIdleCheckBox;
    QCheckBox *statusDoNotDisturbCheckBox;
    QCheckBox *statusOtherCheckBox;
    QLabel *userPhotoLabel;

    QLabel* selectedMessageLabel;

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
    void updateUserStatus(QString);
    void updateStatusCheckBoxes(QString);
    void setDisconnectedStatus();

    void addMessageToMessageListWidget(const QString&);
    void addPhotoToMessageListWidget(QPixmap);
    void addStatusButtonToMenu(QCheckBox**, QWidgetAction**, const QString&, bool);
    void createUserInfoDialog(const QString&, const QString&, const QString&, const QString&, const QPixmap&);
    void addLabelToDialog(QLabel**, const int, const QString&, QBoxLayout*);

    void saveMessageHistory(const QString&);

    QString boldCurrentTime();

    QSslSocket *userSocket;

    QString username = "";
    bool isNewUsernameActive;

    QPixmap userPhoto;
    QString newUserPhotoPath;
    QString userPhotoPath;
    QString defaultUserPhotoPath = "userphoto.png";

    QString userStatus;
    QString customUserStatus;
    QString userStatusBeforeDisconnect;

    QByteArray messageData;
    quint16 nextBlockSize;

    QSound* newMessageSound;

    QString serverIP = "127.0.0.1";
    quint16 serverPort = (quint16)45678;
};

#endif // CLIENT_H
