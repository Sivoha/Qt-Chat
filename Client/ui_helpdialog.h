/********************************************************************************
** Form generated from reading UI file 'helpdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPDIALOG_H
#define UI_HELPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_helpDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QLabel *authorPicture;
    QLabel *authorName;
    QLabel *buildDate;
    QLabel *buildVersion;
    QLabel *launchVersion;
    QPushButton *closeButton;

    void setupUi(QDialog *helpDialog)
    {
        if (helpDialog->objectName().isEmpty())
            helpDialog->setObjectName(QString::fromUtf8("helpDialog"));
        helpDialog->resize(555, 251);
        helpDialog->setMaximumSize(QSize(555, 300));
        verticalLayout = new QVBoxLayout(helpDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        authorPicture = new QLabel(helpDialog);
        authorPicture->setObjectName(QString::fromUtf8("authorPicture"));
        authorPicture->setMaximumSize(QSize(200, 200));
        authorPicture->setPixmap(QPixmap(QString::fromUtf8("image.jpg")));
        authorPicture->setScaledContents(true);

        gridLayout_3->addWidget(authorPicture, 0, 0, 4, 1);

        authorName = new QLabel(helpDialog);
        authorName->setObjectName(QString::fromUtf8("authorName"));
        QFont font;
        font.setPointSize(18);
        authorName->setFont(font);

        gridLayout_3->addWidget(authorName, 0, 1, 1, 1);

        buildDate = new QLabel(helpDialog);
        buildDate->setObjectName(QString::fromUtf8("buildDate"));
        buildDate->setFont(font);

        gridLayout_3->addWidget(buildDate, 1, 1, 1, 1);

        buildVersion = new QLabel(helpDialog);
        buildVersion->setObjectName(QString::fromUtf8("buildVersion"));
        buildVersion->setFont(font);

        gridLayout_3->addWidget(buildVersion, 2, 1, 1, 1);

        launchVersion = new QLabel(helpDialog);
        launchVersion->setObjectName(QString::fromUtf8("launchVersion"));
        launchVersion->setFont(font);

        gridLayout_3->addWidget(launchVersion, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        closeButton = new QPushButton(helpDialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        verticalLayout->addWidget(closeButton);


        retranslateUi(helpDialog);

        QMetaObject::connectSlotsByName(helpDialog);
    } // setupUi

    void retranslateUi(QDialog *helpDialog)
    {
        helpDialog->setWindowTitle(QCoreApplication::translate("helpDialog", "Dialog", nullptr));
        authorPicture->setText(QString());
        authorName->setText(QCoreApplication::translate("helpDialog", "Author name: Andrey Sivokho", nullptr));
        buildDate->setText(QCoreApplication::translate("helpDialog", "Build date: 10.11.2022", nullptr));
        buildVersion->setText(QCoreApplication::translate("helpDialog", "Build Qt version: 5.15.2", nullptr));
        launchVersion->setText(QCoreApplication::translate("helpDialog", "Launch Qt version: 10.10.10", nullptr));
        closeButton->setText(QCoreApplication::translate("helpDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class helpDialog: public Ui_helpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPDIALOG_H
