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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *networkSettingsButton;
    QAction *changeKeyButton;
    QAction *turnOnServerButton;
    QAction *turnOffServerButton;
    QAction *saveLogsButton;
    QAction *exitButton;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextBrowser *clientLogBrowser;
    QMenuBar *menubar;
    QMenu *menuSettings;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(512, 393);
        networkSettingsButton = new QAction(MainWindow);
        networkSettingsButton->setObjectName(QString::fromUtf8("networkSettingsButton"));
        changeKeyButton = new QAction(MainWindow);
        changeKeyButton->setObjectName(QString::fromUtf8("changeKeyButton"));
        turnOnServerButton = new QAction(MainWindow);
        turnOnServerButton->setObjectName(QString::fromUtf8("turnOnServerButton"));
        turnOffServerButton = new QAction(MainWindow);
        turnOffServerButton->setObjectName(QString::fromUtf8("turnOffServerButton"));
        saveLogsButton = new QAction(MainWindow);
        saveLogsButton->setObjectName(QString::fromUtf8("saveLogsButton"));
        exitButton = new QAction(MainWindow);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        clientLogBrowser = new QTextBrowser(centralwidget);
        clientLogBrowser->setObjectName(QString::fromUtf8("clientLogBrowser"));

        gridLayout->addWidget(clientLogBrowser, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 512, 21));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menuSettings->addAction(networkSettingsButton);
        menuSettings->addAction(changeKeyButton);
        menuFile->addAction(turnOnServerButton);
        menuFile->addAction(turnOffServerButton);
        menuFile->addAction(saveLogsButton);
        menuFile->addAction(exitButton);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        networkSettingsButton->setText(QCoreApplication::translate("MainWindow", "Network", nullptr));
        changeKeyButton->setText(QCoreApplication::translate("MainWindow", "Change key", nullptr));
        turnOnServerButton->setText(QCoreApplication::translate("MainWindow", "Turn On", nullptr));
        turnOffServerButton->setText(QCoreApplication::translate("MainWindow", "Turn Off", nullptr));
        saveLogsButton->setText(QCoreApplication::translate("MainWindow", "Save logs to XML file", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
