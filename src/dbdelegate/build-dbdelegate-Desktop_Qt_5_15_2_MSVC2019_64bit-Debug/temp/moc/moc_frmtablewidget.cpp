/****************************************************************************
** Meta object code from reading C++ file 'frmtablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../dbdelegate/form/frmtablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmtablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmTableWidget_t {
    QByteArrayData data[15];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmTableWidget_t qt_meta_stringdata_frmTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "frmTableWidget"
QT_MOC_LITERAL(1, 15, 8), // "initForm"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "initData"
QT_MOC_LITERAL(4, 34, 12), // "valueChanged"
QT_MOC_LITERAL(5, 47, 5), // "value"
QT_MOC_LITERAL(6, 53, 13), // "buttonClicked"
QT_MOC_LITERAL(7, 67, 8), // "btnIndex"
QT_MOC_LITERAL(8, 76, 11), // "QModelIndex"
QT_MOC_LITERAL(9, 88, 5), // "index"
QT_MOC_LITERAL(10, 94, 12), // "stateChanged"
QT_MOC_LITERAL(11, 107, 4), // "arg1"
QT_MOC_LITERAL(12, 112, 7), // "pressed"
QT_MOC_LITERAL(13, 120, 7), // "setData"
QT_MOC_LITERAL(14, 128, 7) // "getData"

    },
    "frmTableWidget\0initForm\0\0initData\0"
    "valueChanged\0value\0buttonClicked\0"
    "btnIndex\0QModelIndex\0index\0stateChanged\0"
    "arg1\0pressed\0setData\0getData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmTableWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    1,   56,    2, 0x08 /* Private */,
       6,    2,   59,    2, 0x08 /* Private */,
      10,    1,   64,    2, 0x08 /* Private */,
      12,    1,   67,    2, 0x08 /* Private */,
      13,    0,   70,    2, 0x08 /* Private */,
      14,    0,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8,    7,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void frmTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<frmTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initForm(); break;
        case 1: _t->initData(); break;
        case 2: _t->valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->buttonClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 4: _t->stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->setData(); break;
        case 7: _t->getData(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject frmTableWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_frmTableWidget.data,
    qt_meta_data_frmTableWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *frmTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_frmTableWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int frmTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
