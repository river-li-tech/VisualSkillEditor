/****************************************************************************
** Meta object code from reading C++ file 'SkillInst.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../Sources/SkillInst.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SkillInst.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SkillInstData_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SkillInstData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SkillInstData_t qt_meta_stringdata_SkillInstData = {
    {
QT_MOC_LITERAL(0, 0, 13) // "SkillInstData"

    },
    "SkillInstData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SkillInstData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void SkillInstData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject SkillInstData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SkillInstData.data,
      qt_meta_data_SkillInstData,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SkillInstData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkillInstData::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SkillInstData.stringdata0))
        return static_cast<void*>(const_cast< SkillInstData*>(this));
    return QObject::qt_metacast(_clname);
}

int SkillInstData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_SkillInst_t {
    QByteArrayData data[9];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SkillInst_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SkillInst_t qt_meta_stringdata_SkillInst = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SkillInst"
QT_MOC_LITERAL(1, 10, 11), // "instChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "pool"
QT_MOC_LITERAL(4, 28, 17), // "SkillNotifyReason"
QT_MOC_LITERAL(5, 46, 6), // "reason"
QT_MOC_LITERAL(6, 53, 11), // "dataChanged"
QT_MOC_LITERAL(7, 65, 13), // "SkillInstData"
QT_MOC_LITERAL(8, 79, 4) // "data"

    },
    "SkillInst\0instChanged\0\0pool\0"
    "SkillNotifyReason\0reason\0dataChanged\0"
    "SkillInstData\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SkillInst[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       6,    2,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 0, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 4,    8,    5,

       0        // eod
};

void SkillInst::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SkillInst *_t = static_cast<SkillInst *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->instChanged((*reinterpret_cast< const SkillInst(*)>(_a[1])),(*reinterpret_cast< SkillNotifyReason(*)>(_a[2]))); break;
        case 1: _t->dataChanged((*reinterpret_cast< const SkillInstData(*)>(_a[1])),(*reinterpret_cast< SkillNotifyReason(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SkillInst::*_t)(const SkillInst & , SkillNotifyReason );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SkillInst::instChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SkillInst::*_t)(const SkillInstData & , SkillNotifyReason );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SkillInst::dataChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SkillInst::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SkillInst.data,
      qt_meta_data_SkillInst,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SkillInst::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkillInst::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SkillInst.stringdata0))
        return static_cast<void*>(const_cast< SkillInst*>(this));
    return QObject::qt_metacast(_clname);
}

int SkillInst::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SkillInst::instChanged(const SkillInst & _t1, SkillNotifyReason _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SkillInst::dataChanged(const SkillInstData & _t1, SkillNotifyReason _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
