#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new Server();
    this->setWindowTitle("Server | IP: " + server->IP + " Port: " + QString::number(server->port)+ " Number of clients: 0");
    connect(server, SIGNAL(logEvent(QString)), this, SLOT(logConnection(QString)));
    connect(server, SIGNAL(updateWindowTitleEvent(QString)), this, SLOT(updateWindowTitle(QString)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::logConnection(QString newLog) {
    ui->clientLogBrowser->append(newLog);
}

void MainWindow::updateWindowTitle(QString newTitle) {
    this->setWindowTitle(newTitle);
}
