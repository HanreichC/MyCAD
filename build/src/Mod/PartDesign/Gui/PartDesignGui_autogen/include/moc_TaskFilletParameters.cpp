/****************************************************************************
** Meta object code from reading C++ file 'TaskFilletParameters.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/PartDesign/Gui/TaskFilletParameters.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskFilletParameters.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13PartDesignGui20TaskFilletParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskFilletParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui20TaskFilletParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskFilletParameters",
        "onLengthChanged",
        "",
        "onRefDeleted",
        "onAddAllEdges",
        "onCheckBoxUseAllEdgesToggled",
        "checked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onLengthChanged'
        QtMocHelpers::SlotData<void(double)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 2 },
        }}),
        // Slot 'onRefDeleted'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddAllEdges'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCheckBoxUseAllEdgesToggled'
        QtMocHelpers::SlotData<void(bool)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskFilletParameters, qt_meta_tag_ZN13PartDesignGui20TaskFilletParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskFilletParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDressUpParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui20TaskFilletParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui20TaskFilletParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui20TaskFilletParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskFilletParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskFilletParameters *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onLengthChanged((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->onRefDeleted(); break;
        case 2: _t->onAddAllEdges(); break;
        case 3: _t->onCheckBoxUseAllEdgesToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *PartDesignGui::TaskFilletParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskFilletParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui20TaskFilletParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDressUpParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskFilletParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDressUpParameters::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN13PartDesignGui23TaskDlgFilletParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDlgFilletParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui23TaskDlgFilletParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDlgFilletParameters"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDlgFilletParameters, qt_meta_tag_ZN13PartDesignGui23TaskDlgFilletParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDlgFilletParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDlgDressUpParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui23TaskDlgFilletParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui23TaskDlgFilletParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui23TaskDlgFilletParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDlgFilletParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDlgFilletParameters *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskDlgFilletParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDlgFilletParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui23TaskDlgFilletParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDlgDressUpParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskDlgFilletParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDlgDressUpParameters::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
