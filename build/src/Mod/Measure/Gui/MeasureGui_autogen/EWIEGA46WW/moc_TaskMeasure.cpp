/****************************************************************************
** Meta object code from reading C++ file 'TaskMeasure.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/Measure/Gui/TaskMeasure.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskMeasure.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10MeasureGui11TaskMeasureE_t {};
} // unnamed namespace

template <> constexpr inline auto MeasureGui::TaskMeasure::qt_create_metaobjectdata<qt_meta_tag_ZN10MeasureGui11TaskMeasureE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MeasureGui::TaskMeasure"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskMeasure, qt_meta_tag_ZN10MeasureGui11TaskMeasureE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MeasureGui::TaskMeasure::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MeasureGui11TaskMeasureE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MeasureGui11TaskMeasureE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MeasureGui11TaskMeasureE_t>.metaTypes,
    nullptr
} };

void MeasureGui::TaskMeasure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskMeasure *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *MeasureGui::TaskMeasure::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeasureGui::TaskMeasure::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MeasureGui11TaskMeasureE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Gui::SelectionObserver"))
        return static_cast< Gui::SelectionObserver*>(this);
    return Gui::TaskView::TaskDialog::qt_metacast(_clname);
}

int MeasureGui::TaskMeasure::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskDialog::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN10MeasureGui19TaskMeasureTypeInfoE_t {};
} // unnamed namespace

template <> constexpr inline auto MeasureGui::TaskMeasureTypeInfo::qt_create_metaobjectdata<qt_meta_tag_ZN10MeasureGui19TaskMeasureTypeInfoE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MeasureGui::TaskMeasureTypeInfo"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskMeasureTypeInfo, qt_meta_tag_ZN10MeasureGui19TaskMeasureTypeInfoE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MeasureGui::TaskMeasureTypeInfo::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MeasureGui19TaskMeasureTypeInfoE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MeasureGui19TaskMeasureTypeInfoE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MeasureGui19TaskMeasureTypeInfoE_t>.metaTypes,
    nullptr
} };

void MeasureGui::TaskMeasureTypeInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskMeasureTypeInfo *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *MeasureGui::TaskMeasureTypeInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeasureGui::TaskMeasureTypeInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MeasureGui19TaskMeasureTypeInfoE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MeasureGui::TaskMeasureTypeInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN10MeasureGui23TaskMeasureDistanceInfoE_t {};
} // unnamed namespace

template <> constexpr inline auto MeasureGui::TaskMeasureDistanceInfo::qt_create_metaobjectdata<qt_meta_tag_ZN10MeasureGui23TaskMeasureDistanceInfoE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MeasureGui::TaskMeasureDistanceInfo"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskMeasureDistanceInfo, qt_meta_tag_ZN10MeasureGui23TaskMeasureDistanceInfoE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MeasureGui::TaskMeasureDistanceInfo::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskMeasureTypeInfo::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MeasureGui23TaskMeasureDistanceInfoE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MeasureGui23TaskMeasureDistanceInfoE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MeasureGui23TaskMeasureDistanceInfoE_t>.metaTypes,
    nullptr
} };

void MeasureGui::TaskMeasureDistanceInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskMeasureDistanceInfo *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *MeasureGui::TaskMeasureDistanceInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeasureGui::TaskMeasureDistanceInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MeasureGui23TaskMeasureDistanceInfoE_t>.strings))
        return static_cast<void*>(this);
    return TaskMeasureTypeInfo::qt_metacast(_clname);
}

int MeasureGui::TaskMeasureDistanceInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskMeasureTypeInfo::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
