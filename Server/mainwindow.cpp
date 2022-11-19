#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new Server();

    updateWindowTitle();

    connect(ui->turnOnServerButton, SIGNAL(triggered()), this, SLOT(onTurnOnServerButtonTriggered()));
    connect(ui->turnOffServerButton, SIGNAL(triggered()), this, SLOT(onTurnOffServerButtonTriggered()));
    connect(ui->saveLogsButton, SIGNAL(triggered()), this, SLOT(onSaveLogsButtonTriggered()));
    connect(ui->exitButton, SIGNAL(triggered()), this, SLOT(onExitButtonTriggered()));
    connect(ui->networkSettingsButton, SIGNAL(triggered()), this, SLOT(onNetworkSettingsButtonTriggered()));
    connect(ui->changeKeyButton, SIGNAL(triggered()), this, SLOT(onChangeKeyButtonTriggered()));
    connect(server, SIGNAL(logEvent(QString)), this, SLOT(logConnection(QString)));
    connect(server, SIGNAL(updateWindowTitleEvent()), this, SLOT(updateWindowTitle()));

    document = new QDomDocument("log-history");
    domElement = document->createElement("log-history");
    document->appendChild(domElement);
}

MainWindow::~MainWindow() {
    delete ui;
}

QDomElement MainWindow::makeElement(QDomDocument* domDoc, const QString& strElementName, const QString& strText) {
    QDomElement domElement = domDoc->createElement(strElementName);

    if (!strText.isEmpty()) {
        QDomText domText = domDoc->createTextNode(strText);
        domElement.appendChild(domText);
    }

    return domElement;
}

QDomElement MainWindow::log(QDomDocument* domDoc, const QString& logText) {
    QDomElement domElement = makeElement(domDoc, "log", "");
    domElement.appendChild(makeElement(domDoc, "time", QTime::currentTime().toString()));
    domElement.appendChild(makeElement(domDoc, "text", logText));

    return domElement;
}

void MainWindow::onTurnOnServerButtonTriggered() {
    if (server->listen(QHostAddress(server->IP), server->port)) {
        updateWindowTitle();
    }
}

void MainWindow::onTurnOffServerButtonTriggered() {
    for (auto socket : server->userList.keys()) {
        socket->disconnectFromHost();
    }
    server->close();
    this->setWindowTitle("Server | Off");
}

void MainWindow::onSaveLogsButtonTriggered() {
    QBoxLayout* boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* fileNameLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* passwordLayout = new QBoxLayout(QBoxLayout::LeftToRight);


    QLabel *fileNameLabel = new QLabel();
    fileNameLabel->setText("File name:");
    fileNameLayout->addWidget(fileNameLabel);

    QLineEdit *fileNameLine = new QLineEdit();
    fileNameLine->setText("MessageHistory");
    fileNameLayout->addWidget(fileNameLine);

    QLabel *passwordLabel = new QLabel();
    passwordLabel->setText("Password:");
    passwordLayout->addWidget(passwordLabel);

    passwordLine = new QLineEdit();
    passwordLine->setEchoMode(QLineEdit::Password);
    passwordLayout->addWidget(passwordLine);

    QCheckBox *passwordCheckbox = new QCheckBox();
    passwordLayout->addWidget(passwordCheckbox);

    boxLayout->addLayout(fileNameLayout);
    boxLayout->addLayout(passwordLayout);

    QDialog *modalDialog = new QDialog(this);
    modalDialog->setModal(true);
    modalDialog->setWindowTitle("Save logs");
    modalDialog->setMinimumWidth(220);

    QPushButton *saveMessageHistoryButton = new QPushButton("Save");
    boxLayout->addWidget(saveMessageHistoryButton);
    connect(passwordCheckbox, SIGNAL(stateChanged(int)), this, SLOT(changePasswordView(int)));
    connect(saveMessageHistoryButton, SIGNAL(clicked()), modalDialog, SLOT(accept()));

    modalDialog->setLayout(boxLayout);

    if (modalDialog->exec() == QDialog::Accepted) {
        saveMessageHistory(fileNameLine->text());
    }

    delete modalDialog;
}

void MainWindow::saveMessageHistory(const QString& fileName) {
    QFile file(fileName + ".xml");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << document->toString();
        file.close();
    }
}

void MainWindow::onExitButtonTriggered() {
    QApplication::quit();
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
            for (auto socket : server->userList.keys()) {
                socket->disconnectFromHost();
            }
            updateWindowTitle();
        } else {
            onNetworkSettingsButtonTriggered();
        }
    }

    delete modalDialog;
}

void MainWindow::onChangeKeyButtonTriggered() {
    for (auto socket : server->userList.keys()) {
        socket->disconnectFromHost();
//        socket->connectToHost(QHostAddress(server->IP), server->port);
    }
    qDebug() << "change key";
}

void MainWindow::logConnection(QString newLogText) {
    ui->clientLogBrowser->append("<b>" + QTime::currentTime().toString() + "</b> " + newLogText);
    QDomElement newLog = log(document, newLogText);
    domElement.appendChild(newLog);
}

void MainWindow::updateWindowTitle() {
    this->setWindowTitle("Server | IP: " + server->IP + " Port: " + QString::number(server->port) + " Number of clients: " + QString::number(server->numberOfClients));
}
