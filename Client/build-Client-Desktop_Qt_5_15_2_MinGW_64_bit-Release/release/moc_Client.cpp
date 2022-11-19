/****************************************************************************
** Meta object code from reading C++ file 'Client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "C:/Users/sivoh/Desktop/lab5/Qt-Chat-0778f13d6377039b870e5bbf429178b5164c9769/Client/Client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[20];
    char stringdata0[450];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 26), // "onSendMessageButtonClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 29), // "onNewMessageLineReturnPressed"
QT_MOC_LITERAL(4, 65, 32), // "onConnectToServerButtonTriggered"
QT_MOC_LITERAL(5, 98, 27), // "onDisconnectButtonTriggered"
QT_MOC_LITERAL(6, 126, 28), // "onSaveHistoryButtonTriggered"
QT_MOC_LITERAL(7, 155, 21), // "onExitButtonTriggered"
QT_MOC_LITERAL(8, 177, 21), // "onHelpButtonTriggered"
QT_MOC_LITERAL(9, 199, 33), // "onUsernameSettingsButtonTrigg..."
QT_MOC_LITERAL(10, 233, 31), // "onServerSettingsButtonTriggered"
QT_MOC_LITERAL(11, 265, 29), // "onStatusOnlineButtonTriggered"
QT_MOC_LITERAL(12, 295, 27), // "onStatusIdleButtonTriggered"
QT_MOC_LITERAL(13, 323, 35), // "onStatusDoNotDisturbButtonTri..."
QT_MOC_LITERAL(14, 359, 17), // "onUserItemClicked"
QT_MOC_LITERAL(15, 377, 13), // "slotConnected"
QT_MOC_LITERAL(16, 391, 13), // "slotReadyRead"
QT_MOC_LITERAL(17, 405, 9), // "slotError"
QT_MOC_LITERAL(18, 415, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(19, 444, 5) // "error"

    },
    "Client\0onSendMessageButtonClicked\0\0"
    "onNewMessageLineReturnPressed\0"
    "onConnectToServerButtonTriggered\0"
    "onDisconnectButtonTriggered\0"
    "onSaveHistoryButtonTriggered\0"
    "onExitButtonTriggered\0onHelpButtonTriggered\0"
    "onUsernameSettingsButtonTriggered\0"
    "onServerSettingsButtonTriggered\0"
    "onStatusOnlineButtonTriggered\0"
    "onStatusIdleButtonTriggered\0"
    "onStatusDoNotDisturbButtonTriggered\0"
    "onUserItemClicked\0slotConnected\0"
    "slotReadyRead\0slotError\0"
    "QAbstractSocket::SocketError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    1,  106,    2, 0x08 /* Private */,
      15,    0,  109,    2, 0x08 /* Private */,
      16,    0,  110,    2, 0x08 /* Private */,
      17,    1,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSendMessageButtonClicked(); break;
        case 1: _t->onNewMessageLineReturnPressed(); break;
        case 2: _t->onConnectToServerButtonTriggered(); break;
        case 3: _t->onDisconnectButtonTriggered(); break;
        case 4: _t->onSaveHistoryButtonTriggered(); break;
        case 5: _t->onExitButtonTriggered(); break;
        case 6: _t->onHelpButtonTriggered(); break;
        case 7: _t->onUsernameSettingsButtonTriggered(); break;
        case 8: _t->onServerSettingsButtonTriggered(); break;
        case 9: _t->onStatusOnlineButtonTriggered(); break;
        case 10: _t->onStatusIdleButtonTriggered(); break;
        case 11: _t->onStatusDoNotDisturbButtonTriggered(); break;
        case 12: _t->onUserItemClicked((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 13: _t->slotConnected(); break;
        case 14: _t->slotReadyRead(); break;
        case 15: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Client.data,
    qt_meta_data_Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
