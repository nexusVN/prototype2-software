/****************************************************************************
** Meta object code from reading C++ file 'lcddisplay.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lcddisplay.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lcddisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_lcddisplay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      36,   11,   11,   11, 0x08,
      74,   11,   11,   11, 0x08,
     108,  100,   11,   11, 0x08,
     137,   11,   11,   11, 0x08,
     162,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_lcddisplay[] = {
    "lcddisplay\0\0on_loadButton_clicked()\0"
    "on_listItem_clicked(QListWidgetItem*)\0"
    "on_removeButton_clicked()\0checked\0"
    "on_printButton_clicked(bool)\0"
    "on_resetButton_clicked()\0"
    "on_cancelButton_clicked()\0"
};

void lcddisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        lcddisplay *_t = static_cast<lcddisplay *>(_o);
        switch (_id) {
        case 0: _t->on_loadButton_clicked(); break;
        case 1: _t->on_listItem_clicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->on_removeButton_clicked(); break;
        case 3: _t->on_printButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_resetButton_clicked(); break;
        case 5: _t->on_cancelButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData lcddisplay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject lcddisplay::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_lcddisplay,
      qt_meta_data_lcddisplay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &lcddisplay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *lcddisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *lcddisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_lcddisplay))
        return static_cast<void*>(const_cast< lcddisplay*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int lcddisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
