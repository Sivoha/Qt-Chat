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
    QAction *backgroundColorSettingsButton;
    QAction *messageColorSettingsButton;
    QAction *userPhotoSettingsButton;
    QAction *viewMessageHistoryButton;
    QAction *backToChatButton;
    QAction *openFileButton;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    SendButton *sendMessageButton;
    UserListWidget *userListWidget;
    QLineEdit *newMessageLine;
    MessageListWidget *messageListWidget;
    MessageListWidget *messageHistoryWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuStatus;
    QMenu *menuView;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(757, 303);
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
        backgroundColorSettingsButton = new QAction(Client);
        backgroundColorSettingsButton->setObjectName(QString::fromUtf8("backgroundColorSettingsButton"));
        messageColorSettingsButton = new QAction(Client);
        messageColorSettingsButton->setObjectName(QString::fromUtf8("messageColorSettingsButton"));
        userPhotoSettingsButton = new QAction(Client);
        userPhotoSettingsButton->setObjectName(QString::fromUtf8("userPhotoSettingsButton"));
        viewMessageHistoryButton = new QAction(Client);
        viewMessageHistoryButton->setObjectName(QString::fromUtf8("viewMessageHistoryButton"));
        backToChatButton = new QAction(Client);
        backToChatButton->setObjectName(QString::fromUtf8("backToChatButton"));
        openFileButton = new QAction(Client);
        openFileButton->setObjectName(QString::fromUtf8("openFileButton"));
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sendMessageButton = new SendButton(centralwidget);
        sendMessageButton->setObjectName(QString::fromUtf8("sendMessageButton"));
        sendMessageButton->setEnabled(false);
        sendMessageButton->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(sendMessageButton, 2, 1, 1, 1);

        userListWidget = new UserListWidget(centralwidget);
        userListWidget->setObjectName(QString::fromUtf8("userListWidget"));
        userListWidget->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(userListWidget, 0, 1, 1, 1);

        newMessageLine = new QLineEdit(centralwidget);
        newMessageLine->setObjectName(QString::fromUtf8("newMessageLine"));
        newMessageLine->setMinimumSize(QSize(650, 0));
        newMessageLine->setReadOnly(true);

        gridLayout->addWidget(newMessageLine, 2, 0, 1, 1);

        messageListWidget = new MessageListWidget(centralwidget);
        messageListWidget->setObjectName(QString::fromUtf8("messageListWidget"));
        messageListWidget->setMinimumSize(QSize(650, 0));
        messageListWidget->setAutoScroll(true);
        messageListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        messageListWidget->setMovement(QListView::Static);

        gridLayout->addWidget(messageListWidget, 0, 0, 1, 1);

        messageHistoryWidget = new MessageListWidget(centralwidget);
        messageHistoryWidget->setObjectName(QString::fromUtf8("messageHistoryWidget"));

        gridLayout->addWidget(messageHistoryWidget, 1, 0, 1, 1);

        Client->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Client);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 757, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuStatus = new QMenu(menuSettings);
        menuStatus->setObjectName(QString::fromUtf8("menuStatus"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        Client->setMenuBar(menubar);
        statusBar = new QStatusBar(Client);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Client->setStatusBar(statusBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(openFileButton);
        menuFile->addAction(connectToServerButton);
        menuFile->addAction(disconnectButton);
        menuFile->addAction(saveHistoryButton);
        menuFile->addAction(exitButton);
        menuSettings->addAction(serverSettingsButton);
        menuSettings->addAction(usernameSettingsButton);
        menuSettings->addAction(userPhotoSettingsButton);
        menuSettings->addAction(menuStatus->menuAction());
        menuView->addAction(backgroundColorSettingsButton);
        menuView->addAction(messageColorSettingsButton);
        menuView->addAction(viewMessageHistoryButton);
        menuView->addAction(backToChatButton);

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
        backgroundColorSettingsButton->setText(QCoreApplication::translate("Client", "Background color", nullptr));
        messageColorSettingsButton->setText(QCoreApplication::translate("Client", "Messages color", nullptr));
        userPhotoSettingsButton->setText(QCoreApplication::translate("Client", "User photo", nullptr));
        viewMessageHistoryButton->setText(QCoreApplication::translate("Client", "View message history", nullptr));
        backToChatButton->setText(QCoreApplication::translate("Client", "Back to chat", nullptr));
        openFileButton->setText(QCoreApplication::translate("Client", "Open", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("Client", "Send message", nullptr));
        menuFile->setTitle(QCoreApplication::translate("Client", "File", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("Client", "Settings", nullptr));
        menuStatus->setTitle(QCoreApplication::translate("Client", "Status", nullptr));
        menuView->setTitle(QCoreApplication::translate("Client", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
