/****************************************************************************
** Meta object code from reading C++ file 'TaskDefeaturingParameters.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/PartDesign/Gui/TaskDefeaturingParameters.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskDefeaturingParameters.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13PartDesignGui25TaskDefeaturingParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDefeaturingParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui25TaskDefeaturingParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDefeaturingParameters",
        "onRefDeleted",
        ""
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onRefDeleted'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDefeaturingParameters, qt_meta_tag_ZN13PartDesignGui25TaskDefeaturingParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDefeaturingParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDressUpParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui25TaskDefeaturingParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui25TaskDefeaturingParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui25TaskDefeaturingParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDefeaturingParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDefeaturingParameters *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onRefDeleted(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskDefeaturingParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDefeaturingParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui25TaskDefeaturingParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDressUpParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskDefeaturingParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDressUpParameters::qt_metacall(_c, _id, _a);
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
struct qt_meta_tag_ZN13PartDesignGui28TaskDlgDefeaturingParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDlgDefeaturingParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui28TaskDlgDefeaturingParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDlgDefeaturingParameters"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDlgDefeaturingParameters, qt_meta_tag_ZN13PartDesignGui28TaskDlgDefeaturingParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDlgDefeaturingParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDlgDressUpParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui28TaskDlgDefeaturingParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui28TaskDlgDefeaturingParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui28TaskDlgDefeaturingParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDlgDefeaturingParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDlgDefeaturingParameters *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskDlgDefeaturingParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDlgDefeaturingParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui28TaskDlgDefeaturingParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDlgDressUpParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskDlgDefeaturingParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDlgDressUpParameters::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
