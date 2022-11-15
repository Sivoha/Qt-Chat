/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *connectToServerButton;
    QAction *disconnectFromServerButton;
    QAction *saveHistoryToXMLButton;
    QAction *exitChatButton;
    QAction *serverSettings;
    QAction *userNameSettings;
    QAction *statusOnline;
    QAction *statusIdle;
    QAction *statusDoNotDisturb;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QListWidget *userList;
    QTextBrowser *messagesWindow;
    QPushButton *sendMessageButton;
    QLineEdit *newMessageLine;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuStatus;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 541);
        connectToServerButton = new QAction(MainWindow);
        connectToServerButton->setObjectName(QString::fromUtf8("connectToServerButton"));
        disconnectFromServerButton = new QAction(MainWindow);
        disconnectFromServerButton->setObjectName(QString::fromUtf8("disconnectFromServerButton"));
        saveHistoryToXMLButton = new QAction(MainWindow);
        saveHistoryToXMLButton->setObjectName(QString::fromUtf8("saveHistoryToXMLButton"));
        exitChatButton = new QAction(MainWindow);
        exitChatButton->setObjectName(QString::fromUtf8("exitChatButton"));
        serverSettings = new QAction(MainWindow);
        serverSettings->setObjectName(QString::fromUtf8("serverSettings"));
        userNameSettings = new QAction(MainWindow);
        userNameSettings->setObjectName(QString::fromUtf8("userNameSettings"));
        statusOnline = new QAction(MainWindow);
        statusOnline->setObjectName(QString::fromUtf8("statusOnline"));
        statusIdle = new QAction(MainWindow);
        statusIdle->setObjectName(QString::fromUtf8("statusIdle"));
        statusDoNotDisturb = new QAction(MainWindow);
        statusDoNotDisturb->setObjectName(QString::fromUtf8("statusDoNotDisturb"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        userList = new QListWidget(centralwidget);
        userList->setObjectName(QString::fromUtf8("userList"));
        userList->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(userList, 0, 1, 1, 1);

        messagesWindow = new QTextBrowser(centralwidget);
        messagesWindow->setObjectName(QString::fromUtf8("messagesWindow"));
        messagesWindow->setMinimumSize(QSize(650, 300));

        gridLayout->addWidget(messagesWindow, 0, 0, 1, 1);

        sendMessageButton = new QPushButton(centralwidget);
        sendMessageButton->setObjectName(QString::fromUtf8("sendMessageButton"));
        sendMessageButton->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(sendMessageButton, 1, 1, 1, 1);

        newMessageLine = new QLineEdit(centralwidget);
        newMessageLine->setObjectName(QString::fromUtf8("newMessageLine"));
        newMessageLine->setMinimumSize(QSize(650, 0));

        gridLayout->addWidget(newMessageLine, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuStatus = new QMenu(menuSettings);
        menuStatus->setObjectName(QString::fromUtf8("menuStatus"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(connectToServerButton);
        menuFile->addAction(disconnectFromServerButton);
        menuFile->addAction(saveHistoryToXMLButton);
        menuFile->addAction(exitChatButton);
        menuSettings->addAction(serverSettings);
        menuSettings->addAction(userNameSettings);
        menuSettings->addAction(menuStatus->menuAction());
        menuStatus->addAction(statusOnline);
        menuStatus->addAction(statusIdle);
        menuStatus->addAction(statusDoNotDisturb);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        connectToServerButton->setText(QCoreApplication::translate("MainWindow", "Connect to server", nullptr));
        disconnectFromServerButton->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        saveHistoryToXMLButton->setText(QCoreApplication::translate("MainWindow", "Save history to XML", nullptr));
        exitChatButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        serverSettings->setText(QCoreApplication::translate("MainWindow", "Server: ", nullptr));
        userNameSettings->setText(QCoreApplication::translate("MainWindow", "UserName", nullptr));
        statusOnline->setText(QCoreApplication::translate("MainWindow", "Online", nullptr));
        statusIdle->setText(QCoreApplication::translate("MainWindow", "Idle", nullptr));
        statusDoNotDisturb->setText(QCoreApplication::translate("MainWindow", "Do Not Disturb", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("MainWindow", "Send ", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuStatus->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
