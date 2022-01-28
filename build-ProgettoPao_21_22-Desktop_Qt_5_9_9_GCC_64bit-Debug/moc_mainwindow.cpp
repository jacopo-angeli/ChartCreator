/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ProgettoPao_21_22/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "UpperInsert"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "LowerInsert"
QT_MOC_LITERAL(4, 36, 11), // "RightInsert"
QT_MOC_LITERAL(5, 48, 10), // "LeftInsert"
QT_MOC_LITERAL(6, 59, 15), // "TableResetAlert"
QT_MOC_LITERAL(7, 75, 15), // "OpenGraphWindow"
QT_MOC_LITERAL(8, 91, 14), // "ClearSelection"
QT_MOC_LITERAL(9, 106, 8), // "ClearRow"
QT_MOC_LITERAL(10, 115, 11), // "ClearColumn"
QT_MOC_LITERAL(11, 127, 12), // "DeleteColumn"
QT_MOC_LITERAL(12, 140, 9), // "DeleteRow"
QT_MOC_LITERAL(13, 150, 13), // "CellValidator"
QT_MOC_LITERAL(14, 164, 12), // "NewWorkSheet"
QT_MOC_LITERAL(15, 177, 11), // "SaveCsvCopy"
QT_MOC_LITERAL(16, 189, 9), // "LeftAlign"
QT_MOC_LITERAL(17, 199, 11), // "CenterAlign"
QT_MOC_LITERAL(18, 211, 10), // "RightAlign"
QT_MOC_LITERAL(19, 222, 11), // "SetTextSize"
QT_MOC_LITERAL(20, 234, 14) // "SpinBoxRefresh"

    },
    "MainWindow\0UpperInsert\0\0LowerInsert\0"
    "RightInsert\0LeftInsert\0TableResetAlert\0"
    "OpenGraphWindow\0ClearSelection\0ClearRow\0"
    "ClearColumn\0DeleteColumn\0DeleteRow\0"
    "CellValidator\0NewWorkSheet\0SaveCsvCopy\0"
    "LeftAlign\0CenterAlign\0RightAlign\0"
    "SetTextSize\0SpinBoxRefresh"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x0a /* Public */,
       3,    0,  110,    2, 0x0a /* Public */,
       4,    0,  111,    2, 0x0a /* Public */,
       5,    0,  112,    2, 0x0a /* Public */,
       6,    0,  113,    2, 0x0a /* Public */,
       7,    0,  114,    2, 0x0a /* Public */,
       8,    0,  115,    2, 0x0a /* Public */,
       9,    0,  116,    2, 0x0a /* Public */,
      10,    0,  117,    2, 0x0a /* Public */,
      11,    0,  118,    2, 0x0a /* Public */,
      12,    0,  119,    2, 0x0a /* Public */,
      13,    2,  120,    2, 0x0a /* Public */,
      14,    0,  125,    2, 0x0a /* Public */,
      15,    0,  126,    2, 0x0a /* Public */,
      16,    0,  127,    2, 0x0a /* Public */,
      17,    0,  128,    2, 0x0a /* Public */,
      18,    0,  129,    2, 0x0a /* Public */,
      19,    0,  130,    2, 0x0a /* Public */,
      20,    0,  131,    2, 0x0a /* Public */,

 // slots: parameters
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
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpperInsert(); break;
        case 1: _t->LowerInsert(); break;
        case 2: _t->RightInsert(); break;
        case 3: _t->LeftInsert(); break;
        case 4: _t->TableResetAlert(); break;
        case 5: _t->OpenGraphWindow(); break;
        case 6: _t->ClearSelection(); break;
        case 7: _t->ClearRow(); break;
        case 8: _t->ClearColumn(); break;
        case 9: _t->DeleteColumn(); break;
        case 10: _t->DeleteRow(); break;
        case 11: _t->CellValidator((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->NewWorkSheet(); break;
        case 13: _t->SaveCsvCopy(); break;
        case 14: _t->LeftAlign(); break;
        case 15: _t->CenterAlign(); break;
        case 16: _t->RightAlign(); break;
        case 17: _t->SetTextSize(); break;
        case 18: _t->SpinBoxRefresh(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
