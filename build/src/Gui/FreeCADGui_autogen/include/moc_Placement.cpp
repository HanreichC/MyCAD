/****************************************************************************
** Meta object code from reading C++ file 'Placement.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/Placement.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Placement.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui6Dialog16PlacementHandlerE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::PlacementHandler::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog16PlacementHandlerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::PlacementHandler",
        "openTransaction",
        ""
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'openTransaction'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlacementHandler, qt_meta_tag_ZN3Gui6Dialog16PlacementHandlerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::PlacementHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog16PlacementHandlerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog16PlacementHandlerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog16PlacementHandlerE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::PlacementHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlacementHandler *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->openTransaction(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Gui::Dialog::PlacementHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::PlacementHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog16PlacementHandlerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Gui::Dialog::PlacementHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
struct qt_meta_tag_ZN3Gui6Dialog9PlacementE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::Placement::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog9PlacementE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::Placement",
        "placementChanged",
        "",
        "QVariant",
        "onApplyButtonClicked",
        "onApplyIncrementalPlacementToggled",
        "onPlacementChanged",
        "onResetButtonClicked",
        "onCenterOfMassToggled",
        "onSelectedVertexClicked",
        "onApplyAxialClicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'placementChanged'
        QtMocHelpers::SignalData<void(const QVariant &, bool, bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { QMetaType::Bool, 2 }, { QMetaType::Bool, 2 },
        }}),
        // Slot 'onApplyButtonClicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onApplyIncrementalPlacementToggled'
        QtMocHelpers::SlotData<void(bool)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'onPlacementChanged'
        QtMocHelpers::SlotData<void(int)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Slot 'onResetButtonClicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCenterOfMassToggled'
        QtMocHelpers::SlotData<void(bool)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'onSelectedVertexClicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onApplyAxialClicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Placement, qt_meta_tag_ZN3Gui6Dialog9PlacementE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::Placement::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog9PlacementE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog9PlacementE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog9PlacementE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::Placement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Placement *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->placementChanged((*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3]))); break;
        case 1: _t->onApplyButtonClicked(); break;
        case 2: _t->onApplyIncrementalPlacementToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->onPlacementChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->onResetButtonClicked(); break;
        case 5: _t->onCenterOfMassToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->onSelectedVertexClicked(); break;
        case 7: _t->onApplyAxialClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Placement::*)(const QVariant & , bool , bool )>(_a, &Placement::placementChanged, 0))
            return;
    }
}

const QMetaObject *Gui::Dialog::Placement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::Placement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog9PlacementE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Gui::Dialog::Placement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Gui::Dialog::Placement::placementChanged(const QVariant & _t1, bool _t2, bool _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3);
}
namespace {
struct qt_meta_tag_ZN3Gui6Dialog17DockablePlacementE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::DockablePlacement::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog17DockablePlacementE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::DockablePlacement"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DockablePlacement, qt_meta_tag_ZN3Gui6Dialog17DockablePlacementE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::DockablePlacement::staticMetaObject = { {
    QMetaObject::SuperData::link<Placement::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog17DockablePlacementE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog17DockablePlacementE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog17DockablePlacementE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::DockablePlacement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DockablePlacement *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::Dialog::DockablePlacement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::DockablePlacement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog17DockablePlacementE_t>.strings))
        return static_cast<void*>(this);
    return Placement::qt_metacast(_clname);
}

int Gui::Dialog::DockablePlacement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Placement::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui6Dialog13TaskPlacementE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::TaskPlacement::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog13TaskPlacementE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::TaskPlacement",
        "placementChanged",
        "",
        "QVariant",
        "slotPlacementChanged"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'placementChanged'
        QtMocHelpers::SignalData<void(const QVariant &, bool, bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { QMetaType::Bool, 2 }, { QMetaType::Bool, 2 },
        }}),
        // Slot 'slotPlacementChanged'
        QtMocHelpers::SlotData<void(const QVariant &, bool, bool)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { QMetaType::Bool, 2 }, { QMetaType::Bool, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskPlacement, qt_meta_tag_ZN3Gui6Dialog13TaskPlacementE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::TaskPlacement::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog13TaskPlacementE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog13TaskPlacementE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog13TaskPlacementE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::TaskPlacement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskPlacement *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->placementChanged((*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3]))); break;
        case 1: _t->slotPlacementChanged((*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TaskPlacement::*)(const QVariant & , bool , bool )>(_a, &TaskPlacement::placementChanged, 0))
            return;
    }
}

const QMetaObject *Gui::Dialog::TaskPlacement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::TaskPlacement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog13TaskPlacementE_t>.strings))
        return static_cast<void*>(this);
    return Gui::TaskView::TaskDialog::qt_metacast(_clname);
}

int Gui::Dialog::TaskPlacement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Gui::Dialog::TaskPlacement::placementChanged(const QVariant & _t1, bool _t2, bool _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP
