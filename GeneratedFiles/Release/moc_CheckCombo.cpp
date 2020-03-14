/****************************************************************************
** Meta object code from reading C++ file 'CheckCombo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../Sources/CheckCombo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CheckCombo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CheckCombo_t {
    QByteArrayData data[5];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CheckCombo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CheckCombo_t qt_meta_stringdata_CheckCombo = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CheckCombo"
QT_MOC_LITERAL(1, 11, 18), // "checkedStateChange"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "index"
QT_MOC_LITERAL(4, 37, 8) // "bChecked"

    },
    "CheckCombo\0checkedStateChange\0\0index\0"
    "bChecked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CheckCombo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,

       0        // eod
};

void CheckCombo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CheckCombo *_t = static_cast<CheckCombo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checkedStateChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CheckCombo::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CheckCombo::checkedStateChange)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CheckCombo::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_CheckCombo.data,
      qt_meta_data_CheckCombo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CheckCombo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CheckCombo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CheckCombo.stringdata0))
        return static_cast<void*>(const_cast< CheckCombo*>(this));
    return QComboBox::qt_metacast(_clname);
}

int CheckCombo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CheckCombo::checkedStateChange(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
