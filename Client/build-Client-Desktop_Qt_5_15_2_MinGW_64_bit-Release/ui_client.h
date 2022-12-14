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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
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
    QAction *actionbebra;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextBrowser *messageBrowser;
    UserListWidget *userListWidget;
    QLineEdit *newMessageLine;
    QPushButton *sendMessageButton;
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
        actionbebra = new QAction(Client);
        actionbebra->setObjectName(QString::fromUtf8("actionbebra"));
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        messageBrowser = new QTextBrowser(centralwidget);
        messageBrowser->setObjectName(QString::fromUtf8("messageBrowser"));
        messageBrowser->setMinimumSize(QSize(650, 0));

        gridLayout->addWidget(messageBrowser, 0, 0, 1, 1);

        userListWidget = new UserListWidget(centralwidget);
        userListWidget->setObjectName(QString::fromUtf8("userListWidget"));
        userListWidget->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(userListWidget, 0, 1, 1, 1);

        newMessageLine = new QLineEdit(centralwidget);
        newMessageLine->setObjectName(QString::fromUtf8("newMessageLine"));
        newMessageLine->setMinimumSize(QSize(650, 0));

        gridLayout->addWidget(newMessageLine, 1, 0, 1, 1);

        sendMessageButton = new QPushButton(centralwidget);
        sendMessageButton->setObjectName(QString::fromUtf8("sendMessageButton"));
        sendMessageButton->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(sendMessageButton, 1, 1, 1, 1);

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
        actionbebra->setText(QCoreApplication::translate("Client", "bebra", nullptr));
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
