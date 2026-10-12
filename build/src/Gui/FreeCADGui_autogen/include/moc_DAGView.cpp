/****************************************************************************
** Meta object code from reading C++ file 'DAGView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/DAGView/DAGView.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DAGView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN3Gui3DAG4ViewE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::DAG::View::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui3DAG4ViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::DAG::View",
        "awakeSlot",
        ""
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'awakeSlot'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<View, qt_meta_tag_ZN3Gui3DAG4ViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::DAG::View::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui3DAG4ViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui3DAG4ViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui3DAG4ViewE_t>.metaTypes,
    nullptr
} };

void Gui::DAG::View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<View *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->awakeSlot(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Gui::DAG::View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::DAG::View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui3DAG4ViewE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "SelectionObserver"))
        return static_cast< SelectionObserver*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int Gui::DAG::View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui3DAG10DockWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::DAG::DockWindow::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui3DAG10DockWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::DAG::DockWindow"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DockWindow, qt_meta_tag_ZN3Gui3DAG10DockWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::DAG::DockWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::DockWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui3DAG10DockWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui3DAG10DockWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui3DAG10DockWindowE_t>.metaTypes,
    nullptr
} };

void Gui::DAG::DockWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DockWindow *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::DAG::DockWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::DAG::DockWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui3DAG10DockWindowE_t>.strings))
        return static_cast<void*>(this);
    return Gui::DockWindow::qt_metacast(_clname);
}

int Gui::DAG::DockWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::DockWindow::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
