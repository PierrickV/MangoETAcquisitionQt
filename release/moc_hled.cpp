/****************************************************************************
** Meta object code from reading C++ file 'hled.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hled.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hled.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HLed_t {
    QByteArrayData data[9];
    char stringdata[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_HLed_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_HLed_t qt_meta_stringdata_HLed = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 8),
QT_MOC_LITERAL(2, 14, 0),
QT_MOC_LITERAL(3, 15, 5),
QT_MOC_LITERAL(4, 21, 6),
QT_MOC_LITERAL(5, 28, 6),
QT_MOC_LITERAL(6, 35, 2),
QT_MOC_LITERAL(7, 38, 7),
QT_MOC_LITERAL(8, 46, 3)
    },
    "HLed\0setColor\0\0color\0toggle\0turnOn\0"
    "on\0turnOff\0off\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HLed[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a,
       4,    0,   47,    2, 0x0a,
       5,    1,   48,    2, 0x0a,
       5,    0,   51,    2, 0x2a,
       7,    1,   52,    2, 0x0a,
       7,    0,   55,    2, 0x2a,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,

       0        // eod
};

void HLed::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HLed *_t = static_cast<HLed *>(_o);
        switch (_id) {
        case 0: _t->setColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 1: _t->toggle(); break;
        case 2: _t->turnOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->turnOn(); break;
        case 4: _t->turnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->turnOff(); break;
        default: ;
        }
    }
}

const QMetaObject HLed::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HLed.data,
      qt_meta_data_HLed,  qt_static_metacall, 0, 0}
};


const QMetaObject *HLed::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HLed::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HLed.stringdata))
        return static_cast<void*>(const_cast< HLed*>(this));
    return QWidget::qt_metacast(_clname);
}

int HLed::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
