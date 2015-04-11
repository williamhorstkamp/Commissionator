/****************************************************************************
** Meta object code from reading C++ file 'ComModelTest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/ComModelTest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ComModelTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Commissionator__ComModelTest_t {
    QByteArrayData data[13];
    char stringdata[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Commissionator__ComModelTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Commissionator__ComModelTest_t qt_meta_stringdata_Commissionator__ComModelTest = {
    {
QT_MOC_LITERAL(0, 0, 28), // "Commissionator::ComModelTest"
QT_MOC_LITERAL(1, 29, 12), // "initTestCase"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 4), // "init"
QT_MOC_LITERAL(4, 48, 22), // "insertCommissionerTest"
QT_MOC_LITERAL(5, 71, 17), // "insertContactTest"
QT_MOC_LITERAL(6, 89, 17), // "insertProductTest"
QT_MOC_LITERAL(7, 107, 17), // "insertPaymentTest"
QT_MOC_LITERAL(8, 125, 20), // "insertCommissionTest"
QT_MOC_LITERAL(9, 146, 21), // "insertPaymentTypeTest"
QT_MOC_LITERAL(10, 168, 21), // "insertContactTypeTest"
QT_MOC_LITERAL(11, 190, 7), // "cleanup"
QT_MOC_LITERAL(12, 198, 15) // "cleanupTestCase"

    },
    "Commissionator::ComModelTest\0initTestCase\0"
    "\0init\0insertCommissionerTest\0"
    "insertContactTest\0insertProductTest\0"
    "insertPaymentTest\0insertCommissionTest\0"
    "insertPaymentTypeTest\0insertContactTypeTest\0"
    "cleanup\0cleanupTestCase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Commissionator__ComModelTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

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

       0        // eod
};

void Commissionator::ComModelTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComModelTest *_t = static_cast<ComModelTest *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->init(); break;
        case 2: _t->insertCommissionerTest(); break;
        case 3: _t->insertContactTest(); break;
        case 4: _t->insertProductTest(); break;
        case 5: _t->insertPaymentTest(); break;
        case 6: _t->insertCommissionTest(); break;
        case 7: _t->insertPaymentTypeTest(); break;
        case 8: _t->insertContactTypeTest(); break;
        case 9: _t->cleanup(); break;
        case 10: _t->cleanupTestCase(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Commissionator::ComModelTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Commissionator__ComModelTest.data,
      qt_meta_data_Commissionator__ComModelTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Commissionator::ComModelTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Commissionator::ComModelTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Commissionator__ComModelTest.stringdata))
        return static_cast<void*>(const_cast< ComModelTest*>(this));
    return QObject::qt_metacast(_clname);
}

int Commissionator::ComModelTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
