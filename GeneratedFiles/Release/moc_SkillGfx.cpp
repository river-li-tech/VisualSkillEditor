/****************************************************************************
** Meta object code from reading C++ file 'SkillGfx.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../Sources/SkillGfx.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SkillGfx.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SkillGfxData_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SkillGfxData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SkillGfxData_t qt_meta_stringdata_SkillGfxData = {
    {
QT_MOC_LITERAL(0, 0, 12) // "SkillGfxData"

    },
    "SkillGfxData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SkillGfxData[] = {

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

void SkillGfxData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject SkillGfxData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SkillGfxData.data,
      qt_meta_data_SkillGfxData,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SkillGfxData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkillGfxData::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SkillGfxData.stringdata0))
        return static_cast<void*>(const_cast< SkillGfxData*>(this));
    return QObject::qt_metacast(_clname);
}

int SkillGfxData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_SkillGfx_t {
    QByteArrayData data[9];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SkillGfx_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SkillGfx_t qt_meta_stringdata_SkillGfx = {
    {
QT_MOC_LITERAL(0, 0, 8), // "SkillGfx"
QT_MOC_LITERAL(1, 9, 12), // "tableChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "pool"
QT_MOC_LITERAL(4, 28, 17), // "SkillNotifyReason"
QT_MOC_LITERAL(5, 46, 6), // "reason"
QT_MOC_LITERAL(6, 53, 11), // "dataChanged"
QT_MOC_LITERAL(7, 65, 12), // "SkillGfxData"
QT_MOC_LITERAL(8, 78, 4) // "data"

    },
    "SkillGfx\0tableChanged\0\0pool\0"
    "SkillNotifyReason\0reason\0dataChanged\0"
    "SkillGfxData\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SkillGfx[] = {

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

void SkillGfx::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SkillGfx *_t = static_cast<SkillGfx *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tableChanged((*reinterpret_cast< const SkillGfx(*)>(_a[1])),(*reinterpret_cast< SkillNotifyReason(*)>(_a[2]))); break;
        case 1: _t->dataChanged((*reinterpret_cast< const SkillGfxData(*)>(_a[1])),(*reinterpret_cast< SkillNotifyReason(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SkillGfx::*_t)(const SkillGfx & , SkillNotifyReason );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SkillGfx::tableChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SkillGfx::*_t)(const SkillGfxData & , SkillNotifyReason );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SkillGfx::dataChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SkillGfx::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SkillGfx.data,
      qt_meta_data_SkillGfx,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SkillGfx::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkillGfx::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SkillGfx.stringdata0))
        return static_cast<void*>(const_cast< SkillGfx*>(this));
    return QObject::qt_metacast(_clname);
}

int SkillGfx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SkillGfx::tableChanged(const SkillGfx & _t1, SkillNotifyReason _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SkillGfx::dataChanged(const SkillGfxData & _t1, SkillNotifyReason _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
