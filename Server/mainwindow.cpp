#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new Server();

    updateWindowTitle();

    connect(ui->networkSettingsButton, SIGNAL(triggered()), this, SLOT(onNetworkSettingsButtonTriggered()));
    connect(ui->changeKeyButton, SIGNAL(triggered()), this, SLOT(onChangeKeyButtonTriggered()));
    connect(server, SIGNAL(logEvent(QString)), this, SLOT(logConnection(QString)));
    connect(server, SIGNAL(updateWindowTitleEvent()), this, SLOT(updateWindowTitle()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onNetworkSettingsButtonTriggered() {
    QRegExp regex("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])");
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* IPLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* portLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    QLabel *IPLabel = new QLabel();
    IPLabel->setText("IP:     ");
    IPLayout->addWidget(IPLabel);
    QLineEdit *IPLine = new QLineEdit();
    IPLine->setText(server->IP);
    IPLayout->addWidget(IPLine);

    QLabel *portLabel = new QLabel();
    portLabel->setText("Port: ");
    portLayout->addWidget(portLabel);
    QSpinBox *portSpinBox = new QSpinBox();
    portSpinBox->setRange(1, 65535);
    portSpinBox->setValue(server->port);
    portSpinBox->setMinimumWidth(100);
    portLayout->addWidget(portSpinBox);

    boxLayout->addLayout(IPLayout);
    boxLayout->addLayout(portLayout);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setModal(true);
    modalDialog->setWindowTitle("Network settings");
    modalDialog->setMinimumWidth(220);
    QPushButton *saveUsernameButton = new QPushButton("Save");
    boxLayout->addWidget(saveUsernameButton);
    connect(saveUsernameButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));

    modalDialog->setLayout(boxLayout);
    if (modalDialog->exec() == QDialog::Accepted) {
        if (regex.exactMatch(IPLine->text())) {
            server->IP = IPLine->text();
            server->port = (quint16)portSpinBox->value();
            server->close();
            server->listen(QHostAddress(server->IP), server->port);
            updateWindowTitle();
        } else {
            onNetworkSettingsButtonTriggered();
        }
    }

    delete modalDialog;
}

void MainWindow::onChangeKeyButtonTriggered() {
    qDebug() << "change key";
}

void MainWindow::logConnection(QString newLog) {
    ui->clientLogBrowser->append(newLog);
}

void MainWindow::updateWindowTitle() {
    this->setWindowTitle("Server | IP: " + server->IP + " Port: " + QString::number(server->port) + " Number of clients: " + QString::number(server->numberOfClients));
}
