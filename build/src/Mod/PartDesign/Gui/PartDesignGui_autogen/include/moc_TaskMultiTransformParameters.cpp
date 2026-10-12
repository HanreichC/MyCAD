/****************************************************************************
** Meta object code from reading C++ file 'TaskMultiTransformParameters.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/PartDesign/Gui/TaskMultiTransformParameters.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskMultiTransformParameters.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13PartDesignGui28TaskMultiTransformParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskMultiTransformParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui28TaskMultiTransformParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskMultiTransformParameters",
        "onSubTaskButtonOK",
        "",
        "onTransformDelete",
        "onTransformEdit",
        "onTransformActivated",
        "QModelIndex",
        "index",
        "onTransformAddMirrored",
        "onTransformAddLinearPattern",
        "onTransformAddCircularPattern",
        "onTransformAddPathPattern",
        "onTransformAddPointPattern",
        "onTransformAddPolarPattern",
        "onTransformAddScaled",
        "onMoveUp",
        "onMoveDown",
        "onUpdateView"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onSubTaskButtonOK'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformDelete'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformEdit'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformActivated'
        QtMocHelpers::SlotData<void(const QModelIndex &)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'onTransformAddMirrored'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformAddLinearPattern'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformAddCircularPattern'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformAddPathPattern'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformAddPointPattern'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformAddPolarPattern'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformAddScaled'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMoveUp'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMoveDown'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onUpdateView'
        QtMocHelpers::SlotData<void(bool)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskMultiTransformParameters, qt_meta_tag_ZN13PartDesignGui28TaskMultiTransformParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskMultiTransformParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskTransformedParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui28TaskMultiTransformParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui28TaskMultiTransformParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui28TaskMultiTransformParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskMultiTransformParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskMultiTransformParameters *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onSubTaskButtonOK(); break;
        case 1: _t->onTransformDelete(); break;
        case 2: _t->onTransformEdit(); break;
        case 3: _t->onTransformActivated((*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 4: _t->onTransformAddMirrored(); break;
        case 5: _t->onTransformAddLinearPattern(); break;
        case 6: _t->onTransformAddCircularPattern(); break;
        case 7: _t->onTransformAddPathPattern(); break;
        case 8: _t->onTransformAddPointPattern(); break;
        case 9: _t->onTransformAddPolarPattern(); break;
        case 10: _t->onTransformAddScaled(); break;
        case 11: _t->onMoveUp(); break;
        case 12: _t->onMoveDown(); break;
        case 13: _t->onUpdateView((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *PartDesignGui::TaskMultiTransformParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskMultiTransformParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui28TaskMultiTransformParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskTransformedParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskMultiTransformParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskTransformedParameters::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN13PartDesignGui31TaskDlgMultiTransformParametersE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDlgMultiTransformParameters::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui31TaskDlgMultiTransformParametersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDlgMultiTransformParameters"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDlgMultiTransformParameters, qt_meta_tag_ZN13PartDesignGui31TaskDlgMultiTransformParametersE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDlgMultiTransformParameters::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskDlgTransformedParameters::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui31TaskDlgMultiTransformParametersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui31TaskDlgMultiTransformParametersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui31TaskDlgMultiTransformParametersE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDlgMultiTransformParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDlgMultiTransformParameters *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskDlgMultiTransformParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDlgMultiTransformParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui31TaskDlgMultiTransformParametersE_t>.strings))
        return static_cast<void*>(this);
    return TaskDlgTransformedParameters::qt_metacast(_clname);
}

int PartDesignGui::TaskDlgMultiTransformParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskDlgTransformedParameters::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
