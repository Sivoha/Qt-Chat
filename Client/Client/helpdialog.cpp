#include "helpdialog.h"
#include "ui_helpdialog.h"

helpDialog::helpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Help");
    ui->launchVersion->setText("Launch Qt version: " + QString(qVersion()));
}

helpDialog::~helpDialog() {
    delete ui;
}

void helpDialog::on_closeButton_clicked() {
    this->close();
}

