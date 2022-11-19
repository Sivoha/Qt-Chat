#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Server.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class Server;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Server* server;
    QDomDocument* document;
    QDomElement domElement;
    QLineEdit* passwordLine;

    QDomElement log(QDomDocument*, const QString&);
    QDomElement makeElement(QDomDocument*, const QString&, const QString&);

    void saveMessageHistory(const QString&);

private slots:
    void onTurnOnServerButtonTriggered();
    void onTurnOffServerButtonTriggered();
    void onSaveLogsButtonTriggered();
    void onNetworkSettingsButtonTriggered();
    void onExitButtonTriggered();
    void onChangeKeyButtonTriggered();
    void logConnection(QString);
    void updateWindowTitle();
};
#endif // MAINWINDOW_H
