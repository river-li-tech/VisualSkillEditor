/****************************************************************************
** Meta object code from reading C++ file 'ParamWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../Sources/ParamWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ParamWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParamWidget_t {
    QByteArrayData data[15];
    char stringdata0[311];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParamWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParamWidget_t qt_meta_stringdata_ParamWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ParamWidget"
QT_MOC_LITERAL(1, 12, 34), // "onNodeTypeComboCurrentIndexCh..."
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 5), // "index"
QT_MOC_LITERAL(4, 54, 36), // "onActionTypeComboCurrentIndex..."
QT_MOC_LITERAL(5, 91, 29), // "onArgComboCurrentIndexChanged"
QT_MOC_LITERAL(6, 121, 32), // "onArgRefComboCurrentIndexChanged"
QT_MOC_LITERAL(7, 154, 5), // "state"
QT_MOC_LITERAL(8, 160, 36), // "onArgCheckedComboCurrentIndex..."
QT_MOC_LITERAL(9, 197, 9), // "isChecked"
QT_MOC_LITERAL(10, 207, 21), // "onArgSpinValueChanged"
QT_MOC_LITERAL(11, 229, 5), // "value"
QT_MOC_LITERAL(12, 235, 22), // "onArgDSpinValueChanged"
QT_MOC_LITERAL(13, 258, 27), // "onArgEditTxtEditingFinished"
QT_MOC_LITERAL(14, 286, 24) // "onArgRevertButtonClicked"

    },
    "ParamWidget\0onNodeTypeComboCurrentIndexChanged\0"
    "\0index\0onActionTypeComboCurrentIndexChanged\0"
    "onArgComboCurrentIndexChanged\0"
    "onArgRefComboCurrentIndexChanged\0state\0"
    "onArgCheckedComboCurrentIndexChanged\0"
    "isChecked\0onArgSpinValueChanged\0value\0"
    "onArgDSpinValueChanged\0"
    "onArgEditTxtEditingFinished\0"
    "onArgRevertButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParamWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       4,    1,   62,    2, 0x08 /* Private */,
       5,    1,   65,    2, 0x08 /* Private */,
       6,    1,   68,    2, 0x08 /* Private */,
       8,    2,   71,    2, 0x08 /* Private */,
      10,    1,   76,    2, 0x08 /* Private */,
      12,    1,   79,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ParamWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParamWidget *_t = static_cast<ParamWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNodeTypeComboCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onActionTypeComboCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onArgComboCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onArgRefComboCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onArgCheckedComboCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->onArgSpinValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onArgDSpinValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->onArgEditTxtEditingFinished(); break;
        case 8: _t->onArgRevertButtonClicked(); break;
        default: ;
        }
    }
}

const QMetaObject ParamWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ParamWidget.data,
      qt_meta_data_ParamWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ParamWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParamWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ParamWidget.stringdata0))
        return static_cast<void*>(const_cast< ParamWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ParamWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
