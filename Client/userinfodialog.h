#ifndef USERINFODIALOG_H
#define USERINFODIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class UserInfoDialog;
}

class UserInfoDialog : public QDialog
{
    Q_OBJECT

public:
    UserInfoDialog(QWidget *parent, QString username, QString userIP, QString userConnectionTime, QString userStatus);
    ~UserInfoDialog();

private:
    Ui::UserInfoDialog *ui;
};

#endif // USERINFODIALOG_H
