#ifndef CLIENT_H
#define CLIENT_H

#include <helpdialog.h>
#include <userinfodialog.h>
#include <UserListWidget.h>
#include <MessageListWidget.h>
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
    void onSendFileButtonClicked();
    void onSendButtonRightClicked(QMouseEvent*);
    void onSendMessageActionTriggered();
    void onSendPhotoActionTriggered();
    void onSendFileActionTriggered();
    void onNewMessageLineReturnPressed();

    void onConnectToServerButtonTriggered();
    void onDisconnectButtonTriggered();
    void onSaveHistoryButtonTriggered();
    void changePasswordView(int);
    void onExitButtonTriggered();

    void onServerSettingsButtonTriggered();
    void onUsernameSettingsButtonTriggered();
    void onUserPhotoSettingsButtonTriggered();
    void onChooseUserPhotoButtonClicked();
    void onDefaultUserPhotoButtonClicked();
    void onStatusOnlineButtonTriggered();
    void onStatusIdleButtonTriggered();
    void onStatusDoNotDisturbButtonTriggered();
    void onStatusOtherButtonTriggered();

    void onShowSenderIPButtonTriggered();
    void onShowMessageTimeButtonTriggered();
    void onBackgroundColorSettingsButtonTriggered();
    void onMessageColorSettingsButtonTriggered();
    void onSenderInfoColorSettingsButtonClicked();
    void onMessageTextColorSettingsButtonClicked();

    void onHelpButtonTriggered();

    void onUserItemClicked(QPoint);

    void onMessageClicked(QMouseEvent*);
    void onOpenInFullSizeActionTriggered();
    void onSavePhotoActionTriggered();
    void onOpenInDefaultApplicationActionTriggered();
    void onSaveFileActionTriggered();

    void slotConnected();
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError error);

private:
    Ui::Client *ui;

    QCheckBox *statusOnlineCheckBox;
    QCheckBox *statusIdleCheckBox;
    QCheckBox *statusDoNotDisturbCheckBox;
    QCheckBox *statusOtherCheckBox;

    QCheckBox *showSenderIPCheckBox;
    QCheckBox *showMessageTimeCheckBox;
    bool isSenderIPEnabled = true;
    bool isMessageTimeEnabled = true;

    QColor messageListBackgroundColor = QColor(255, 255, 255);
    QColor senderInfoColor = QColor(0, 0, 0);
    QColor messageTextColor = QColor(0, 0, 0);
    QList<Message> messageList;
    QList<QLabel*> messageLabelList;

    QLabel *userPhotoLabel;

    QLineEdit *passwordLine;

    QListWidgetItem* selectedMessage;
    QLabel* selectedMessageLabel;

    QSettings* settings;

    QDomDocument* document;
    QDomElement domElement;

    QDomElement photo(QDomDocument*, const QString&, const QString&, const QString&, QPixmap);
    QDomElement file(QDomDocument*, const QString&, const QString&, const QString&, QFile*, const QString&);
    QDomElement message(QDomDocument*, const QString&, const QString&, const QString&, const QString&);
    QDomElement makeElement(QDomDocument*, const QString&, const QString&);
    QByteArray fileChecksum(QFile*);

    void setUpSocket();
    void connectToServer();
    void disconnectFromServer();
    void sendToServer(const QString&, const QString&);

    void updateWindowStatus();
    void updateUserStatus(QString);
    QString getShortStatus(QString);
    void updateStatusCheckBoxes(QString);
    void setDisconnectedStatus();
    void disconnectSendButton();

    void addMessageToMessageListWidget(Message);
    QString constructMessage(Message);
    void addMessageToMessageListWidget(const QString&);
    void updateMessages();
    void addPhotoToMessageListWidget(QPixmap);
    void addFileToMessageListWidget(const QString&, QFile*);
    QMap<QListWidgetItem*, QFile*> receivedFilesList;

    void addStatusButtonToMenu(QCheckBox**, QWidgetAction**, const QString&, bool);
    void addButtonToViewMenu(QCheckBox**, QWidgetAction**, const QString&);
    void createUserInfoDialog(const QString&, const QString&, const QString&, const QString&, const QPixmap&);
    void addLabelToDialog(QLabel**, const int, const QString&, QBoxLayout*);

    void saveMessageHistory(const QString&);

    QString boldCurrentTime();

    QSslSocket *userSocket;

    QString username = "";
    bool isNewUsernameActive;

    QPixmap userPhoto;
    QPixmap fileIcon;
    QString newUserPhotoPath;
    QString userPhotoPath;
    QString defaultUserPhotoPath = "userphoto.png";
    QString fileIconPath = "fileicon.png";

    QString userStatus;
    QString customUserStatus;
    QString userStatusBeforeDisconnect;

    QByteArray messageData;
    quint16 nextBlockSize;

    QSound* newMessageSound;

    QString serverIP = "127.0.0.1";
    quint16 serverPort = (quint16)45678;

    QString date;
};

#endif // CLIENT_H
