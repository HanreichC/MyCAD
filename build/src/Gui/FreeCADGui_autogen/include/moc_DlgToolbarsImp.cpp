/****************************************************************************
** Meta object code from reading C++ file 'DlgToolbarsImp.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/Dialogs/DlgToolbarsImp.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgToolbarsImp.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui6Dialog17DlgCustomToolbarsE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::DlgCustomToolbars::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog17DlgCustomToolbarsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::DlgCustomToolbars",
        "onAddMacroAction",
        "",
        "onRemoveMacroAction",
        "onModifyMacroAction"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onAddMacroAction'
        QtMocHelpers::SlotData<void(const QByteArray &)>(1, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QByteArray, 2 },
        }}),
        // Slot 'onRemoveMacroAction'
        QtMocHelpers::SlotData<void(const QByteArray &)>(3, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QByteArray, 2 },
        }}),
        // Slot 'onModifyMacroAction'
        QtMocHelpers::SlotData<void(const QByteArray &)>(4, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QByteArray, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DlgCustomToolbars, qt_meta_tag_ZN3Gui6Dialog17DlgCustomToolbarsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::DlgCustomToolbars::staticMetaObject = { {
    QMetaObject::SuperData::link<CustomizeActionPage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog17DlgCustomToolbarsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog17DlgCustomToolbarsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog17DlgCustomToolbarsE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::DlgCustomToolbars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DlgCustomToolbars *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onAddMacroAction((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 1: _t->onRemoveMacroAction((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 2: _t->onModifyMacroAction((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *Gui::Dialog::DlgCustomToolbars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::DlgCustomToolbars::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog17DlgCustomToolbarsE_t>.strings))
        return static_cast<void*>(this);
    return CustomizeActionPage::qt_metacast(_clname);
}

int Gui::Dialog::DlgCustomToolbars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CustomizeActionPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui6Dialog20DlgCustomToolbarsImpE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::DlgCustomToolbarsImp::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog20DlgCustomToolbarsImpE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::DlgCustomToolbarsImp"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DlgCustomToolbarsImp, qt_meta_tag_ZN3Gui6Dialog20DlgCustomToolbarsImpE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::DlgCustomToolbarsImp::staticMetaObject = { {
    QMetaObject::SuperData::link<DlgCustomToolbars::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog20DlgCustomToolbarsImpE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog20DlgCustomToolbarsImpE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog20DlgCustomToolbarsImpE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::DlgCustomToolbarsImp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DlgCustomToolbarsImp *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::Dialog::DlgCustomToolbarsImp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::DlgCustomToolbarsImp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog20DlgCustomToolbarsImpE_t>.strings))
        return static_cast<void*>(this);
    return DlgCustomToolbars::qt_metacast(_clname);
}

int Gui::Dialog::DlgCustomToolbarsImp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DlgCustomToolbars::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui6Dialog23DlgCustomToolBoxbarsImpE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::DlgCustomToolBoxbarsImp::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog23DlgCustomToolBoxbarsImpE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::DlgCustomToolBoxbarsImp"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DlgCustomToolBoxbarsImp, qt_meta_tag_ZN3Gui6Dialog23DlgCustomToolBoxbarsImpE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::DlgCustomToolBoxbarsImp::staticMetaObject = { {
    QMetaObject::SuperData::link<DlgCustomToolbars::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog23DlgCustomToolBoxbarsImpE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog23DlgCustomToolBoxbarsImpE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog23DlgCustomToolBoxbarsImpE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::DlgCustomToolBoxbarsImp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DlgCustomToolBoxbarsImp *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::Dialog::DlgCustomToolBoxbarsImp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::DlgCustomToolBoxbarsImp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog23DlgCustomToolBoxbarsImpE_t>.strings))
        return static_cast<void*>(this);
    return DlgCustomToolbars::qt_metacast(_clname);
}

int Gui::Dialog::DlgCustomToolBoxbarsImp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DlgCustomToolbars::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
