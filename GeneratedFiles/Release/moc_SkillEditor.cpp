/****************************************************************************
** Meta object code from reading C++ file 'SkillEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../Sources/SkillEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SkillEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SkillEditor_t {
    QByteArrayData data[69];
    char stringdata0[1062];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SkillEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SkillEditor_t qt_meta_stringdata_SkillEditor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SkillEditor"
QT_MOC_LITERAL(1, 12, 13), // "doNewInstFile"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "doOpenInstFile"
QT_MOC_LITERAL(4, 42, 14), // "doSaveInstFile"
QT_MOC_LITERAL(5, 57, 16), // "doSaveInstFileAs"
QT_MOC_LITERAL(6, 74, 13), // "doOpenGfxFile"
QT_MOC_LITERAL(7, 88, 13), // "doSaveGfxFile"
QT_MOC_LITERAL(8, 102, 15), // "doSaveGfxFileAs"
QT_MOC_LITERAL(9, 118, 15), // "doNewScriptFile"
QT_MOC_LITERAL(10, 134, 16), // "doOpenScriptFile"
QT_MOC_LITERAL(11, 151, 16), // "doSaveScriptFile"
QT_MOC_LITERAL(12, 168, 18), // "doSaveScriptFileAs"
QT_MOC_LITERAL(13, 187, 18), // "doSelectScriptFile"
QT_MOC_LITERAL(14, 206, 9), // "doSaveAll"
QT_MOC_LITERAL(15, 216, 10), // "doSettings"
QT_MOC_LITERAL(16, 227, 6), // "doExit"
QT_MOC_LITERAL(17, 234, 10), // "doAddSkill"
QT_MOC_LITERAL(18, 245, 13), // "doDeleteSkill"
QT_MOC_LITERAL(19, 259, 14), // "doAddChildNode"
QT_MOC_LITERAL(20, 274, 13), // "doAddPrevNode"
QT_MOC_LITERAL(21, 288, 13), // "doAddNextNode"
QT_MOC_LITERAL(22, 302, 12), // "doMoveNodeUp"
QT_MOC_LITERAL(23, 315, 14), // "doMoveNodeDown"
QT_MOC_LITERAL(24, 330, 16), // "doMoveNodeParent"
QT_MOC_LITERAL(25, 347, 15), // "doMoveNodeChild"
QT_MOC_LITERAL(26, 363, 12), // "doDeleteNode"
QT_MOC_LITERAL(27, 376, 10), // "doCopyNode"
QT_MOC_LITERAL(28, 387, 9), // "doCutNode"
QT_MOC_LITERAL(29, 397, 11), // "doPasteNode"
QT_MOC_LITERAL(30, 409, 11), // "doSkillHelp"
QT_MOC_LITERAL(31, 421, 12), // "doEditorHelp"
QT_MOC_LITERAL(32, 434, 12), // "doScriptHelp"
QT_MOC_LITERAL(33, 447, 11), // "doShowIcons"
QT_MOC_LITERAL(34, 459, 12), // "doSerialText"
QT_MOC_LITERAL(35, 472, 7), // "doAbout"
QT_MOC_LITERAL(36, 480, 18), // "onSkillInstChanged"
QT_MOC_LITERAL(37, 499, 9), // "SkillInst"
QT_MOC_LITERAL(38, 509, 4), // "pool"
QT_MOC_LITERAL(39, 514, 17), // "SkillNotifyReason"
QT_MOC_LITERAL(40, 532, 6), // "reason"
QT_MOC_LITERAL(41, 539, 22), // "onSkillInstDataChanged"
QT_MOC_LITERAL(42, 562, 13), // "SkillInstData"
QT_MOC_LITERAL(43, 576, 3), // "cfg"
QT_MOC_LITERAL(44, 580, 20), // "onSkillScriptChanged"
QT_MOC_LITERAL(45, 601, 11), // "SkillScript"
QT_MOC_LITERAL(46, 613, 4), // "inst"
QT_MOC_LITERAL(47, 618, 24), // "onSkillScriptNodeChanged"
QT_MOC_LITERAL(48, 643, 15), // "SkillScriptNode"
QT_MOC_LITERAL(49, 659, 4), // "node"
QT_MOC_LITERAL(50, 664, 29), // "onSkillScriptNodeParamChanged"
QT_MOC_LITERAL(51, 694, 20), // "SkillScriptNodeParam"
QT_MOC_LITERAL(52, 715, 5), // "param"
QT_MOC_LITERAL(53, 721, 22), // "onTableInstItemChanged"
QT_MOC_LITERAL(54, 744, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(55, 762, 4), // "item"
QT_MOC_LITERAL(56, 767, 27), // "onTableInstSelectionChanged"
QT_MOC_LITERAL(57, 795, 14), // "QItemSelection"
QT_MOC_LITERAL(58, 810, 8), // "selected"
QT_MOC_LITERAL(59, 819, 10), // "deselected"
QT_MOC_LITERAL(60, 830, 27), // "onTableInstParamItemChanged"
QT_MOC_LITERAL(61, 858, 36), // "onTableInstParamItemSelection..."
QT_MOC_LITERAL(62, 895, 32), // "onTreeScriptItemSelectionChanged"
QT_MOC_LITERAL(63, 928, 27), // "onEditNodeRemarkTextChanged"
QT_MOC_LITERAL(64, 956, 26), // "onEditRefRemarkTextChanged"
QT_MOC_LITERAL(65, 983, 24), // "onTreeScriptItemExpanded"
QT_MOC_LITERAL(66, 1008, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(67, 1025, 25), // "onTreeScriptItemCollapsed"
QT_MOC_LITERAL(68, 1051, 10) // "onTimerOut"

    },
    "SkillEditor\0doNewInstFile\0\0doOpenInstFile\0"
    "doSaveInstFile\0doSaveInstFileAs\0"
    "doOpenGfxFile\0doSaveGfxFile\0doSaveGfxFileAs\0"
    "doNewScriptFile\0doOpenScriptFile\0"
    "doSaveScriptFile\0doSaveScriptFileAs\0"
    "doSelectScriptFile\0doSaveAll\0doSettings\0"
    "doExit\0doAddSkill\0doDeleteSkill\0"
    "doAddChildNode\0doAddPrevNode\0doAddNextNode\0"
    "doMoveNodeUp\0doMoveNodeDown\0"
    "doMoveNodeParent\0doMoveNodeChild\0"
    "doDeleteNode\0doCopyNode\0doCutNode\0"
    "doPasteNode\0doSkillHelp\0doEditorHelp\0"
    "doScriptHelp\0doShowIcons\0doSerialText\0"
    "doAbout\0onSkillInstChanged\0SkillInst\0"
    "pool\0SkillNotifyReason\0reason\0"
    "onSkillInstDataChanged\0SkillInstData\0"
    "cfg\0onSkillScriptChanged\0SkillScript\0"
    "inst\0onSkillScriptNodeChanged\0"
    "SkillScriptNode\0node\0onSkillScriptNodeParamChanged\0"
    "SkillScriptNodeParam\0param\0"
    "onTableInstItemChanged\0QTableWidgetItem*\0"
    "item\0onTableInstSelectionChanged\0"
    "QItemSelection\0selected\0deselected\0"
    "onTableInstParamItemChanged\0"
    "onTableInstParamItemSelectionChanged\0"
    "onTreeScriptItemSelectionChanged\0"
    "onEditNodeRemarkTextChanged\0"
    "onEditRefRemarkTextChanged\0"
    "onTreeScriptItemExpanded\0QTreeWidgetItem*\0"
    "onTreeScriptItemCollapsed\0onTimerOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SkillEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      49,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  259,    2, 0x08 /* Private */,
       3,    0,  260,    2, 0x08 /* Private */,
       4,    0,  261,    2, 0x08 /* Private */,
       5,    0,  262,    2, 0x08 /* Private */,
       6,    0,  263,    2, 0x08 /* Private */,
       7,    0,  264,    2, 0x08 /* Private */,
       8,    0,  265,    2, 0x08 /* Private */,
       9,    0,  266,    2, 0x08 /* Private */,
      10,    0,  267,    2, 0x08 /* Private */,
      11,    0,  268,    2, 0x08 /* Private */,
      12,    0,  269,    2, 0x08 /* Private */,
      13,    0,  270,    2, 0x08 /* Private */,
      14,    0,  271,    2, 0x08 /* Private */,
      15,    0,  272,    2, 0x08 /* Private */,
      16,    0,  273,    2, 0x08 /* Private */,
      17,    0,  274,    2, 0x08 /* Private */,
      18,    0,  275,    2, 0x08 /* Private */,
      19,    0,  276,    2, 0x08 /* Private */,
      20,    0,  277,    2, 0x08 /* Private */,
      21,    0,  278,    2, 0x08 /* Private */,
      22,    0,  279,    2, 0x08 /* Private */,
      23,    0,  280,    2, 0x08 /* Private */,
      24,    0,  281,    2, 0x08 /* Private */,
      25,    0,  282,    2, 0x08 /* Private */,
      26,    0,  283,    2, 0x08 /* Private */,
      27,    0,  284,    2, 0x08 /* Private */,
      28,    0,  285,    2, 0x08 /* Private */,
      29,    0,  286,    2, 0x08 /* Private */,
      30,    0,  287,    2, 0x08 /* Private */,
      31,    0,  288,    2, 0x08 /* Private */,
      32,    0,  289,    2, 0x08 /* Private */,
      33,    0,  290,    2, 0x08 /* Private */,
      34,    0,  291,    2, 0x08 /* Private */,
      35,    0,  292,    2, 0x08 /* Private */,
      36,    2,  293,    2, 0x08 /* Private */,
      41,    2,  298,    2, 0x08 /* Private */,
      44,    2,  303,    2, 0x08 /* Private */,
      47,    2,  308,    2, 0x08 /* Private */,
      50,    2,  313,    2, 0x08 /* Private */,
      53,    1,  318,    2, 0x08 /* Private */,
      56,    2,  321,    2, 0x08 /* Private */,
      60,    1,  326,    2, 0x08 /* Private */,
      61,    0,  329,    2, 0x08 /* Private */,
      62,    0,  330,    2, 0x08 /* Private */,
      63,    0,  331,    2, 0x08 /* Private */,
      64,    0,  332,    2, 0x08 /* Private */,
      65,    1,  333,    2, 0x08 /* Private */,
      67,    1,  336,    2, 0x08 /* Private */,
      68,    0,  339,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 37, 0x80000000 | 39,   38,   40,
    QMetaType::Void, 0x80000000 | 42, 0x80000000 | 39,   43,   40,
    QMetaType::Void, 0x80000000 | 45, 0x80000000 | 39,   46,   40,
    QMetaType::Void, 0x80000000 | 48, 0x80000000 | 39,   49,   40,
    QMetaType::Void, 0x80000000 | 51, 0x80000000 | 39,   52,   40,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 57, 0x80000000 | 57,   58,   59,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 66,   55,
    QMetaType::Void, 0x80000000 | 66,   55,
    QMetaType::Void,

       0        // eod
};

void SkillEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SkillEditor *_t = static_cast<SkillEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doNewInstFile(); break;
        case 1: _t->doOpenInstFile(); break;
        case 2: { bool _r = _t->doSaveInstFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->doSaveInstFileAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->doOpenGfxFile(); break;
        case 5: { bool _r = _t->doSaveGfxFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->doSaveGfxFileAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->doNewScriptFile(); break;
        case 8: _t->doOpenScriptFile(); break;
        case 9: { bool _r = _t->doSaveScriptFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->doSaveScriptFileAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: _t->doSelectScriptFile(); break;
        case 12: { bool _r = _t->doSaveAll();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->doSettings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->doExit();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = _t->doAddSkill();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: { bool _r = _t->doDeleteSkill();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 17: { bool _r = _t->doAddChildNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: { bool _r = _t->doAddPrevNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: { bool _r = _t->doAddNextNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 20: { bool _r = _t->doMoveNodeUp();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 21: { bool _r = _t->doMoveNodeDown();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 22: { bool _r = _t->doMoveNodeParent();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 23: { bool _r = _t->doMoveNodeChild();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 24: { bool _r = _t->doDeleteNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 25: { bool _r = _t->doCopyNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 26: { bool _r = _t->doCutNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 27: { bool _r = _t->doPasteNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 28: _t->doSkillHelp(); break;
        case 29: _t->doEditorHelp(); break;
        case 30: _t->doScriptHelp(); break;
        case 31: _t->doShowIcons(); break;
        case 32: _t->doSerialText(); break;
        case 33: _t->doAbout(); break;
        case 34: _t->onSkillInstChanged((*reinterpret_cast< const SkillInst(*)>(_a[1])),(*reinterpret_cast< SkillNotifyReason(*)>(_a[2]))); break;
        case 35: _t->onSkillInstDataChanged((*reinterpret_cast< const SkillInstData(*)>(_a[1])),(*reinterpret_cast< SkillNotifyReason(*)>(_a[2]))); break;
        case 36: _t->onSkillScriptChanged((*reinterpret_cast< const SkillScript(*)>(_a[1])),(*reinterpret_cast< SkillNotifyReason(*)>(_a[2]))); break;
        case 37: _t->onSkillScriptNodeChanged((*reinterpret_cast< const SkillScriptNode(*)>(_a[1])),(*reinterpret_cast< SkillNotifyReason(*)>(_a[2]))); break;
        case 38: _t->onSkillScriptNodeParamChanged((*reinterpret_cast< const SkillScriptNodeParam(*)>(_a[1])),(*reinterpret_cast< SkillNotifyReason(*)>(_a[2]))); break;
        case 39: _t->onTableInstItemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 40: _t->onTableInstSelectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 41: _t->onTableInstParamItemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 42: _t->onTableInstParamItemSelectionChanged(); break;
        case 43: _t->onTreeScriptItemSelectionChanged(); break;
        case 44: _t->onEditNodeRemarkTextChanged(); break;
        case 45: _t->onEditRefRemarkTextChanged(); break;
        case 46: _t->onTreeScriptItemExpanded((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 47: _t->onTreeScriptItemCollapsed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 48: _t->onTimerOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 40:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    }
}

const QMetaObject SkillEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SkillEditor.data,
      qt_meta_data_SkillEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SkillEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkillEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SkillEditor.stringdata0))
        return static_cast<void*>(const_cast< SkillEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SkillEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
