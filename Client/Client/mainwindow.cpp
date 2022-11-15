#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pushButton_clicked() {
    socket->connectToHost("127.0.0.1", 2323);
}

void MainWindow::SendToServer(QString str) {
    qDebug() << "budem otpravlyat";
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    qDebug() << "HERE 1";
    if (!socket->isOpen()) {
        qDebug() << "NE ZAEBIS";
    }
    socket->write(Data);
    qDebug() << "HERE 2";
    ui->lineEdit->clear();
}

void MainWindow::slotReadyRead() {
    QDataStream in(socket);
    while (true) {
        if (nextBlockSize == 0) {
            if (socket->bytesAvailable() < 2) {
                break;
            }
            in >> nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize) {
            break;
        }

        QString str;
        QTime time;
        in >> time >> str;
        nextBlockSize = 0;
        ui->textBrowser->append(time.toString() + " " + str);
    }
}

void MainWindow::on_lineEdit_returnPressed() {
    SendToServer(ui->lineEdit->text());
}

void MainWindow::on_pushButton_2_clicked() {
    SendToServer(ui->lineEdit->text());
}

