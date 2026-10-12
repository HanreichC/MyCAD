/****************************************************************************
** Meta object code from reading C++ file 'TaskDraftParameters.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/PartDesign/Gui/TaskDraftParameters.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskDraftParameters.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13PartDesignGui19TaskDraftParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDraftParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui19TaskDraftParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDraftParameters",
        "onAngleChanged",
        "",
        "angle",
        "onReversedChanged",
        "reversed",
        "onButtonPlane",
        "checked",
        "onButtonLine",
        "onRefDeleted"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onAngleChanged'
        QtMocHelpers::SlotData<void(double)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Slot 'onReversedChanged'
        QtMocHelpers::SlotData<void(bool)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Slot 'onButtonPlane'
        QtMocHelpers::SlotData<void(bool)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 7 },
        }}),
        // Slot 'onButtonLine'
        QtMocHelpers::SlotData<void(bool)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 7 },
        }}),
        // Slot 'onRefDeleted'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDraftParameters, qt_meta_tag_ZN13PartDesignGui19TaskDraftParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDraftParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDressUpParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui19TaskDraftParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui19TaskDraftParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui19TaskDraftParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDraftParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDraftParameters *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onAngleChanged((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->onReversedChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->onButtonPlane((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->onButtonLine((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->onRefDeleted(); break;
        default: ;
        }
    }
}

const QMetaObject *PartDesignGui::TaskDraftParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDraftParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui19TaskDraftParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDressUpParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskDraftParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDressUpParameters::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN13PartDesignGui22TaskDlgDraftParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDlgDraftParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui22TaskDlgDraftParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDlgDraftParameters"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDlgDraftParameters, qt_meta_tag_ZN13PartDesignGui22TaskDlgDraftParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDlgDraftParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDlgDressUpParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui22TaskDlgDraftParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui22TaskDlgDraftParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui22TaskDlgDraftParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDlgDraftParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDlgDraftParameters *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskDlgDraftParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDlgDraftParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui22TaskDlgDraftParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDlgDressUpParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskDlgDraftParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDlgDressUpParameters::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
