#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include <QFile>
#include <QSslKey>
#include <QSslSocket>
#include <QSslCertificate>
#include <QSslConfiguration>
#include <QSsl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QSslSocket *socket;
    QByteArray Data;
    void SendToServer(QString str);

    quint16 nextBlockSize;
public slots:
    void slotReadyRead();
};
#endif // MAINWINDOW_H
