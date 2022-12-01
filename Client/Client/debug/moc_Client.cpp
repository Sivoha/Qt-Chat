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
    QByteArrayData data[43];
    char stringdata0[1130];
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
QT_MOC_LITERAL(4, 60, 23), // "onSendFileButtonClicked"
QT_MOC_LITERAL(5, 84, 24), // "onSendButtonRightClicked"
QT_MOC_LITERAL(6, 109, 12), // "QMouseEvent*"
QT_MOC_LITERAL(7, 122, 28), // "onSendMessageActionTriggered"
QT_MOC_LITERAL(8, 151, 26), // "onSendPhotoActionTriggered"
QT_MOC_LITERAL(9, 178, 25), // "onSendFileActionTriggered"
QT_MOC_LITERAL(10, 204, 29), // "onNewMessageLineReturnPressed"
QT_MOC_LITERAL(11, 234, 32), // "onConnectToServerButtonTriggered"
QT_MOC_LITERAL(12, 267, 27), // "onDisconnectButtonTriggered"
QT_MOC_LITERAL(13, 295, 28), // "onSaveHistoryButtonTriggered"
QT_MOC_LITERAL(14, 324, 18), // "changePasswordView"
QT_MOC_LITERAL(15, 343, 21), // "onExitButtonTriggered"
QT_MOC_LITERAL(16, 365, 31), // "onServerSettingsButtonTriggered"
QT_MOC_LITERAL(17, 397, 33), // "onUsernameSettingsButtonTrigg..."
QT_MOC_LITERAL(18, 431, 34), // "onUserPhotoSettingsButtonTrig..."
QT_MOC_LITERAL(19, 466, 30), // "onChooseUserPhotoButtonClicked"
QT_MOC_LITERAL(20, 497, 31), // "onDefaultUserPhotoButtonClicked"
QT_MOC_LITERAL(21, 529, 29), // "onStatusOnlineButtonTriggered"
QT_MOC_LITERAL(22, 559, 27), // "onStatusIdleButtonTriggered"
QT_MOC_LITERAL(23, 587, 35), // "onStatusDoNotDisturbButtonTri..."
QT_MOC_LITERAL(24, 623, 28), // "onStatusOtherButtonTriggered"
QT_MOC_LITERAL(25, 652, 29), // "onShowSenderIPButtonTriggered"
QT_MOC_LITERAL(26, 682, 32), // "onShowMessageTimeButtonTriggered"
QT_MOC_LITERAL(27, 715, 40), // "onBackgroundColorSettingsButt..."
QT_MOC_LITERAL(28, 756, 37), // "onMessageColorSettingsButtonT..."
QT_MOC_LITERAL(29, 794, 38), // "onSenderInfoColorSettingsButt..."
QT_MOC_LITERAL(30, 833, 39), // "onMessageTextColorSettingsBut..."
QT_MOC_LITERAL(31, 873, 21), // "onHelpButtonTriggered"
QT_MOC_LITERAL(32, 895, 17), // "onUserItemClicked"
QT_MOC_LITERAL(33, 913, 16), // "onMessageClicked"
QT_MOC_LITERAL(34, 930, 31), // "onOpenInFullSizeActionTriggered"
QT_MOC_LITERAL(35, 962, 26), // "onSavePhotoActionTriggered"
QT_MOC_LITERAL(36, 989, 41), // "onOpenInDefaultApplicationAct..."
QT_MOC_LITERAL(37, 1031, 25), // "onSaveFileActionTriggered"
QT_MOC_LITERAL(38, 1057, 13), // "slotConnected"
QT_MOC_LITERAL(39, 1071, 13), // "slotReadyRead"
QT_MOC_LITERAL(40, 1085, 9), // "slotError"
QT_MOC_LITERAL(41, 1095, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(42, 1124, 5) // "error"

    },
    "Client\0onSendMessageButtonClicked\0\0"
    "onSendPhotoButtonClicked\0"
    "onSendFileButtonClicked\0"
    "onSendButtonRightClicked\0QMouseEvent*\0"
    "onSendMessageActionTriggered\0"
    "onSendPhotoActionTriggered\0"
    "onSendFileActionTriggered\0"
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
    "onSavePhotoActionTriggered\0"
    "onOpenInDefaultApplicationActionTriggered\0"
    "onSaveFileActionTriggered\0slotConnected\0"
    "slotReadyRead\0slotError\0"
    "QAbstractSocket::SocketError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  204,    2, 0x08 /* Private */,
       3,    0,  205,    2, 0x08 /* Private */,
       4,    0,  206,    2, 0x08 /* Private */,
       5,    1,  207,    2, 0x08 /* Private */,
       7,    0,  210,    2, 0x08 /* Private */,
       8,    0,  211,    2, 0x08 /* Private */,
       9,    0,  212,    2, 0x08 /* Private */,
      10,    0,  213,    2, 0x08 /* Private */,
      11,    0,  214,    2, 0x08 /* Private */,
      12,    0,  215,    2, 0x08 /* Private */,
      13,    0,  216,    2, 0x08 /* Private */,
      14,    1,  217,    2, 0x08 /* Private */,
      15,    0,  220,    2, 0x08 /* Private */,
      16,    0,  221,    2, 0x08 /* Private */,
      17,    0,  222,    2, 0x08 /* Private */,
      18,    0,  223,    2, 0x08 /* Private */,
      19,    0,  224,    2, 0x08 /* Private */,
      20,    0,  225,    2, 0x08 /* Private */,
      21,    0,  226,    2, 0x08 /* Private */,
      22,    0,  227,    2, 0x08 /* Private */,
      23,    0,  228,    2, 0x08 /* Private */,
      24,    0,  229,    2, 0x08 /* Private */,
      25,    0,  230,    2, 0x08 /* Private */,
      26,    0,  231,    2, 0x08 /* Private */,
      27,    0,  232,    2, 0x08 /* Private */,
      28,    0,  233,    2, 0x08 /* Private */,
      29,    0,  234,    2, 0x08 /* Private */,
      30,    0,  235,    2, 0x08 /* Private */,
      31,    0,  236,    2, 0x08 /* Private */,
      32,    1,  237,    2, 0x08 /* Private */,
      33,    1,  240,    2, 0x08 /* Private */,
      34,    0,  243,    2, 0x08 /* Private */,
      35,    0,  244,    2, 0x08 /* Private */,
      36,    0,  245,    2, 0x08 /* Private */,
      37,    0,  246,    2, 0x08 /* Private */,
      38,    0,  247,    2, 0x08 /* Private */,
      39,    0,  248,    2, 0x08 /* Private */,
      40,    1,  249,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
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
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 41,   42,

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
        case 2: _t->onSendFileButtonClicked(); break;
        case 3: _t->onSendButtonRightClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->onSendMessageActionTriggered(); break;
        case 5: _t->onSendPhotoActionTriggered(); break;
        case 6: _t->onSendFileActionTriggered(); break;
        case 7: _t->onNewMessageLineReturnPressed(); break;
        case 8: _t->onConnectToServerButtonTriggered(); break;
        case 9: _t->onDisconnectButtonTriggered(); break;
        case 10: _t->onSaveHistoryButtonTriggered(); break;
        case 11: _t->changePasswordView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->onExitButtonTriggered(); break;
        case 13: _t->onServerSettingsButtonTriggered(); break;
        case 14: _t->onUsernameSettingsButtonTriggered(); break;
        case 15: _t->onUserPhotoSettingsButtonTriggered(); break;
        case 16: _t->onChooseUserPhotoButtonClicked(); break;
        case 17: _t->onDefaultUserPhotoButtonClicked(); break;
        case 18: _t->onStatusOnlineButtonTriggered(); break;
        case 19: _t->onStatusIdleButtonTriggered(); break;
        case 20: _t->onStatusDoNotDisturbButtonTriggered(); break;
        case 21: _t->onStatusOtherButtonTriggered(); break;
        case 22: _t->onShowSenderIPButtonTriggered(); break;
        case 23: _t->onShowMessageTimeButtonTriggered(); break;
        case 24: _t->onBackgroundColorSettingsButtonTriggered(); break;
        case 25: _t->onMessageColorSettingsButtonTriggered(); break;
        case 26: _t->onSenderInfoColorSettingsButtonClicked(); break;
        case 27: _t->onMessageTextColorSettingsButtonClicked(); break;
        case 28: _t->onHelpButtonTriggered(); break;
        case 29: _t->onUserItemClicked((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 30: _t->onMessageClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 31: _t->onOpenInFullSizeActionTriggered(); break;
        case 32: _t->onSavePhotoActionTriggered(); break;
        case 33: _t->onOpenInDefaultApplicationActionTriggered(); break;
        case 34: _t->onSaveFileActionTriggered(); break;
        case 35: _t->slotConnected(); break;
        case 36: _t->slotReadyRead(); break;
        case 37: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 37:
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
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
