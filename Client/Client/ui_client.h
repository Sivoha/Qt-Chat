/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "messagelistwidget.h"
#include "sendbutton.h"
#include "userlistwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QAction *connectToServerButton;
    QAction *disconnectButton;
    QAction *saveHistoryButton;
    QAction *exitButton;
    QAction *serverSettingsButton;
    QAction *usernameSettingsButton;
    QAction *userPhotoSettingsButton;
    QAction *actionUser_photo;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    UserListWidget *userListWidget;
    QLineEdit *newMessageLine;
    SendButton *sendMessageButton;
    MessageListWidget *messageListWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuStatus;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(754, 359);
        connectToServerButton = new QAction(Client);
        connectToServerButton->setObjectName(QString::fromUtf8("connectToServerButton"));
        disconnectButton = new QAction(Client);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));
        saveHistoryButton = new QAction(Client);
        saveHistoryButton->setObjectName(QString::fromUtf8("saveHistoryButton"));
        exitButton = new QAction(Client);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        serverSettingsButton = new QAction(Client);
        serverSettingsButton->setObjectName(QString::fromUtf8("serverSettingsButton"));
        usernameSettingsButton = new QAction(Client);
        usernameSettingsButton->setObjectName(QString::fromUtf8("usernameSettingsButton"));
        userPhotoSettingsButton = new QAction(Client);
        userPhotoSettingsButton->setObjectName(QString::fromUtf8("userPhotoSettingsButton"));
        actionUser_photo = new QAction(Client);
        actionUser_photo->setObjectName(QString::fromUtf8("actionUser_photo"));
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        userListWidget = new UserListWidget(centralwidget);
        userListWidget->setObjectName(QString::fromUtf8("userListWidget"));
        userListWidget->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(userListWidget, 0, 1, 1, 1);

        newMessageLine = new QLineEdit(centralwidget);
        newMessageLine->setObjectName(QString::fromUtf8("newMessageLine"));
        newMessageLine->setMinimumSize(QSize(650, 0));
        newMessageLine->setReadOnly(true);

        gridLayout->addWidget(newMessageLine, 1, 0, 1, 1);

        sendMessageButton = new SendButton(centralwidget);
        sendMessageButton->setObjectName(QString::fromUtf8("sendMessageButton"));
        sendMessageButton->setEnabled(false);
        sendMessageButton->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(sendMessageButton, 1, 1, 1, 1);

        messageListWidget = new MessageListWidget(centralwidget);
        messageListWidget->setObjectName(QString::fromUtf8("messageListWidget"));
        messageListWidget->setMinimumSize(QSize(650, 0));
        messageListWidget->setAutoScroll(true);
        messageListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        messageListWidget->setMovement(QListView::Static);

        gridLayout->addWidget(messageListWidget, 0, 0, 1, 1);

        Client->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Client);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 754, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuStatus = new QMenu(menuSettings);
        menuStatus->setObjectName(QString::fromUtf8("menuStatus"));
        Client->setMenuBar(menubar);
        statusbar = new QStatusBar(Client);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Client->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menuFile->addAction(connectToServerButton);
        menuFile->addAction(disconnectButton);
        menuFile->addAction(saveHistoryButton);
        menuFile->addAction(exitButton);
        menuSettings->addAction(serverSettingsButton);
        menuSettings->addAction(usernameSettingsButton);
        menuSettings->addAction(actionUser_photo);
        menuSettings->addAction(menuStatus->menuAction());

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "MainWindow", nullptr));
        connectToServerButton->setText(QCoreApplication::translate("Client", "Connect to server", nullptr));
        disconnectButton->setText(QCoreApplication::translate("Client", "Disconnect", nullptr));
        saveHistoryButton->setText(QCoreApplication::translate("Client", "Save history to XML file", nullptr));
        exitButton->setText(QCoreApplication::translate("Client", "Exit", nullptr));
        serverSettingsButton->setText(QCoreApplication::translate("Client", "Server: ", nullptr));
        usernameSettingsButton->setText(QCoreApplication::translate("Client", "Username", nullptr));
        userPhotoSettingsButton->setText(QCoreApplication::translate("Client", "User photo", nullptr));
        actionUser_photo->setText(QCoreApplication::translate("Client", "User photo", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("Client", "Send", nullptr));
        menuFile->setTitle(QCoreApplication::translate("Client", "File", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("Client", "Settings", nullptr));
        menuStatus->setTitle(QCoreApplication::translate("Client", "Status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
