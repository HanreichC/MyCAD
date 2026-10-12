/****************************************************************************
** Meta object code from reading C++ file 'TaskPatternParameters.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/PartDesign/Gui/TaskPatternParameters.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskPatternParameters.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13PartDesignGui21TaskPatternParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskPatternParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui21TaskPatternParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskPatternParameters",
        "onUpdateView",
        "",
        "on"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onUpdateView'
        QtMocHelpers::SlotData<void(bool)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskPatternParameters, qt_meta_tag_ZN13PartDesignGui21TaskPatternParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskPatternParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskTransformedParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui21TaskPatternParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui21TaskPatternParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui21TaskPatternParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskPatternParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskPatternParameters *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onUpdateView((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *PartDesignGui::TaskPatternParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskPatternParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui21TaskPatternParametersE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PartGui::TaskPatternParameters"))
        return static_cast< PartGui::TaskPatternParameters*>(this);
    return TaskTransformedParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskPatternParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskTransformedParameters::qt_metacall(_c, _id, _a);
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
struct qt_meta_tag_ZN13PartDesignGui30TaskDlgLinearPatternParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDlgLinearPatternParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui30TaskDlgLinearPatternParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDlgLinearPatternParameters"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDlgLinearPatternParameters, qt_meta_tag_ZN13PartDesignGui30TaskDlgLinearPatternParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDlgLinearPatternParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDlgTransformedParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui30TaskDlgLinearPatternParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui30TaskDlgLinearPatternParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui30TaskDlgLinearPatternParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDlgLinearPatternParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDlgLinearPatternParameters *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskDlgLinearPatternParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDlgLinearPatternParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui30TaskDlgLinearPatternParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDlgTransformedParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskDlgLinearPatternParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDlgTransformedParameters::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
