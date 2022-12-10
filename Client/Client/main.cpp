#include "Client.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Client client1;
    Client client2;
//    Client client3;
    client1.show();
    client2.show();
//    client3.show();
    return a.exec();
}
