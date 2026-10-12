/****************************************************************************
** Meta object code from reading C++ file 'TaskThicknessParameters.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/PartDesign/Gui/TaskThicknessParameters.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskThicknessParameters.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13PartDesignGui23TaskThicknessParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskThicknessParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui23TaskThicknessParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskThicknessParameters",
        "onValueChanged",
        "",
        "angle",
        "onModeChanged",
        "mode",
        "onJoinTypeChanged",
        "join",
        "onReversedChanged",
        "on",
        "onIntersectionChanged",
        "onRefDeleted"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onValueChanged'
        QtMocHelpers::SlotData<void(double)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Slot 'onModeChanged'
        QtMocHelpers::SlotData<void(int)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Slot 'onJoinTypeChanged'
        QtMocHelpers::SlotData<void(int)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 7 },
        }}),
        // Slot 'onReversedChanged'
        QtMocHelpers::SlotData<void(bool)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Slot 'onIntersectionChanged'
        QtMocHelpers::SlotData<void(bool)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Slot 'onRefDeleted'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskThicknessParameters, qt_meta_tag_ZN13PartDesignGui23TaskThicknessParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskThicknessParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDressUpParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui23TaskThicknessParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui23TaskThicknessParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui23TaskThicknessParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskThicknessParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskThicknessParameters *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onValueChanged((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->onModeChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->onJoinTypeChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->onReversedChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->onIntersectionChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->onRefDeleted(); break;
        default: ;
        }
    }
}

const QMetaObject *PartDesignGui::TaskThicknessParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskThicknessParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui23TaskThicknessParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDressUpParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskThicknessParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDressUpParameters::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN13PartDesignGui26TaskDlgThicknessParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDlgThicknessParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui26TaskDlgThicknessParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDlgThicknessParameters"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDlgThicknessParameters, qt_meta_tag_ZN13PartDesignGui26TaskDlgThicknessParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDlgThicknessParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDlgDressUpParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui26TaskDlgThicknessParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui26TaskDlgThicknessParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui26TaskDlgThicknessParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDlgThicknessParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDlgThicknessParameters *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskDlgThicknessParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDlgThicknessParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui26TaskDlgThicknessParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDlgDressUpParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskDlgThicknessParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDlgDressUpParameters::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
