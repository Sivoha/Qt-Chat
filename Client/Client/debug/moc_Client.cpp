/****************************************************************************
** Meta object code from reading C++ file 'Client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Client.h"
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
    QByteArrayData data[40];
    char stringdata0[1049];
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
QT_MOC_LITERAL(3, 35, 24), // "onSendPhotoButtonClicked"
QT_MOC_LITERAL(4, 60, 31), // "onSendMessageButtonRightClicked"
QT_MOC_LITERAL(5, 92, 12), // "QMouseEvent*"
QT_MOC_LITERAL(6, 105, 29), // "onSendPhotoButtonRightClicked"
QT_MOC_LITERAL(7, 135, 28), // "onSendMessageActionTriggered"
QT_MOC_LITERAL(8, 164, 26), // "onSendPhotoActionTriggered"
QT_MOC_LITERAL(9, 191, 29), // "onNewMessageLineReturnPressed"
QT_MOC_LITERAL(10, 221, 32), // "onConnectToServerButtonTriggered"
QT_MOC_LITERAL(11, 254, 27), // "onDisconnectButtonTriggered"
QT_MOC_LITERAL(12, 282, 28), // "onSaveHistoryButtonTriggered"
QT_MOC_LITERAL(13, 311, 18), // "changePasswordView"
QT_MOC_LITERAL(14, 330, 21), // "onExitButtonTriggered"
QT_MOC_LITERAL(15, 352, 31), // "onServerSettingsButtonTriggered"
QT_MOC_LITERAL(16, 384, 33), // "onUsernameSettingsButtonTrigg..."
QT_MOC_LITERAL(17, 418, 34), // "onUserPhotoSettingsButtonTrig..."
QT_MOC_LITERAL(18, 453, 30), // "onChooseUserPhotoButtonClicked"
QT_MOC_LITERAL(19, 484, 31), // "onDefaultUserPhotoButtonClicked"
QT_MOC_LITERAL(20, 516, 29), // "onStatusOnlineButtonTriggered"
QT_MOC_LITERAL(21, 546, 27), // "onStatusIdleButtonTriggered"
QT_MOC_LITERAL(22, 574, 35), // "onStatusDoNotDisturbButtonTri..."
QT_MOC_LITERAL(23, 610, 28), // "onStatusOtherButtonTriggered"
QT_MOC_LITERAL(24, 639, 29), // "onShowSenderIPButtonTriggered"
QT_MOC_LITERAL(25, 669, 32), // "onShowMessageTimeButtonTriggered"
QT_MOC_LITERAL(26, 702, 40), // "onBackgroundColorSettingsButt..."
QT_MOC_LITERAL(27, 743, 37), // "onMessageColorSettingsButtonT..."
QT_MOC_LITERAL(28, 781, 38), // "onSenderInfoColorSettingsButt..."
QT_MOC_LITERAL(29, 820, 39), // "onMessageTextColorSettingsBut..."
QT_MOC_LITERAL(30, 860, 21), // "onHelpButtonTriggered"
QT_MOC_LITERAL(31, 882, 17), // "onUserItemClicked"
QT_MOC_LITERAL(32, 900, 16), // "onMessageClicked"
QT_MOC_LITERAL(33, 917, 31), // "onOpenInFullSizeActionTriggered"
QT_MOC_LITERAL(34, 949, 26), // "onSavePhotoActionTriggered"
QT_MOC_LITERAL(35, 976, 13), // "slotConnected"
QT_MOC_LITERAL(36, 990, 13), // "slotReadyRead"
QT_MOC_LITERAL(37, 1004, 9), // "slotError"
QT_MOC_LITERAL(38, 1014, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(39, 1043, 5) // "error"

    },
    "Client\0onSendMessageButtonClicked\0\0"
    "onSendPhotoButtonClicked\0"
    "onSendMessageButtonRightClicked\0"
    "QMouseEvent*\0onSendPhotoButtonRightClicked\0"
    "onSendMessageActionTriggered\0"
    "onSendPhotoActionTriggered\0"
    "onNewMessageLineReturnPressed\0"
    "onConnectToServerButtonTriggered\0"
    "onDisconnectButtonTriggered\0"
    "onSaveHistoryButtonTriggered\0"
    "changePasswordView\0onExitButtonTriggered\0"
    "onServerSettingsButtonTriggered\0"
    "onUsernameSettingsButtonTriggered\0"
    "onUserPhotoSettingsButtonTriggered\0"
    "onChooseUserPhotoButtonClicked\0"
    "onDefaultUserPhotoButtonClicked\0"
    "onStatusOnlineButtonTriggered\0"
    "onStatusIdleButtonTriggered\0"
    "onStatusDoNotDisturbButtonTriggered\0"
    "onStatusOtherButtonTriggered\0"
    "onShowSenderIPButtonTriggered\0"
    "onShowMessageTimeButtonTriggered\0"
    "onBackgroundColorSettingsButtonTriggered\0"
    "onMessageColorSettingsButtonTriggered\0"
    "onSenderInfoColorSettingsButtonClicked\0"
    "onMessageTextColorSettingsButtonClicked\0"
    "onHelpButtonTriggered\0onUserItemClicked\0"
    "onMessageClicked\0onOpenInFullSizeActionTriggered\0"
    "onSavePhotoActionTriggered\0slotConnected\0"
    "slotReadyRead\0slotError\0"
    "QAbstractSocket::SocketError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  189,    2, 0x08 /* Private */,
       3,    0,  190,    2, 0x08 /* Private */,
       4,    1,  191,    2, 0x08 /* Private */,
       6,    1,  194,    2, 0x08 /* Private */,
       7,    0,  197,    2, 0x08 /* Private */,
       8,    0,  198,    2, 0x08 /* Private */,
       9,    0,  199,    2, 0x08 /* Private */,
      10,    0,  200,    2, 0x08 /* Private */,
      11,    0,  201,    2, 0x08 /* Private */,
      12,    0,  202,    2, 0x08 /* Private */,
      13,    1,  203,    2, 0x08 /* Private */,
      14,    0,  206,    2, 0x08 /* Private */,
      15,    0,  207,    2, 0x08 /* Private */,
      16,    0,  208,    2, 0x08 /* Private */,
      17,    0,  209,    2, 0x08 /* Private */,
      18,    0,  210,    2, 0x08 /* Private */,
      19,    0,  211,    2, 0x08 /* Private */,
      20,    0,  212,    2, 0x08 /* Private */,
      21,    0,  213,    2, 0x08 /* Private */,
      22,    0,  214,    2, 0x08 /* Private */,
      23,    0,  215,    2, 0x08 /* Private */,
      24,    0,  216,    2, 0x08 /* Private */,
      25,    0,  217,    2, 0x08 /* Private */,
      26,    0,  218,    2, 0x08 /* Private */,
      27,    0,  219,    2, 0x08 /* Private */,
      28,    0,  220,    2, 0x08 /* Private */,
      29,    0,  221,    2, 0x08 /* Private */,
      30,    0,  222,    2, 0x08 /* Private */,
      31,    1,  223,    2, 0x08 /* Private */,
      32,    1,  226,    2, 0x08 /* Private */,
      33,    0,  229,    2, 0x08 /* Private */,
      34,    0,  230,    2, 0x08 /* Private */,
      35,    0,  231,    2, 0x08 /* Private */,
      36,    0,  232,    2, 0x08 /* Private */,
      37,    1,  233,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 38,   39,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSendMessageButtonClicked(); break;
        case 1: _t->onSendPhotoButtonClicked(); break;
        case 2: _t->onSendMessageButtonRightClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->onSendPhotoButtonRightClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->onSendMessageActionTriggered(); break;
        case 5: _t->onSendPhotoActionTriggered(); break;
        case 6: _t->onNewMessageLineReturnPressed(); break;
        case 7: _t->onConnectToServerButtonTriggered(); break;
        case 8: _t->onDisconnectButtonTriggered(); break;
        case 9: _t->onSaveHistoryButtonTriggered(); break;
        case 10: _t->changePasswordView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onExitButtonTriggered(); break;
        case 12: _t->onServerSettingsButtonTriggered(); break;
        case 13: _t->onUsernameSettingsButtonTriggered(); break;
        case 14: _t->onUserPhotoSettingsButtonTriggered(); break;
        case 15: _t->onChooseUserPhotoButtonClicked(); break;
        case 16: _t->onDefaultUserPhotoButtonClicked(); break;
        case 17: _t->onStatusOnlineButtonTriggered(); break;
        case 18: _t->onStatusIdleButtonTriggered(); break;
        case 19: _t->onStatusDoNotDisturbButtonTriggered(); break;
        case 20: _t->onStatusOtherButtonTriggered(); break;
        case 21: _t->onShowSenderIPButtonTriggered(); break;
        case 22: _t->onShowMessageTimeButtonTriggered(); break;
        case 23: _t->onBackgroundColorSettingsButtonTriggered(); break;
        case 24: _t->onMessageColorSettingsButtonTriggered(); break;
        case 25: _t->onSenderInfoColorSettingsButtonClicked(); break;
        case 26: _t->onMessageTextColorSettingsButtonClicked(); break;
        case 27: _t->onHelpButtonTriggered(); break;
        case 28: _t->onUserItemClicked((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 29: _t->onMessageClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 30: _t->onOpenInFullSizeActionTriggered(); break;
        case 31: _t->onSavePhotoActionTriggered(); break;
        case 32: _t->slotConnected(); break;
        case 33: _t->slotReadyRead(); break;
        case 34: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 34:
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
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
