#include "userinfodialog.h"
#include "ui_userinfodialog.h"

UserInfoDialog::UserInfoDialog(QWidget *parent, QString username, QString userIP, QString userConnectionTime, QString userStatus) :
    QDialog(parent),
    ui(new Ui::UserInfoDialog) {
    this->setWindowTitle(username);
    ui->setupUi(this);
}

UserInfoDialog::~UserInfoDialog()
{
    delete ui;
}
