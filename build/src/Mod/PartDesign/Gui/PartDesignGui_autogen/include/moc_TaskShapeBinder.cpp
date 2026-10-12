/****************************************************************************
** Meta object code from reading C++ file 'TaskShapeBinder.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/PartDesign/Gui/TaskShapeBinder.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskShapeBinder.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13PartDesignGui15TaskShapeBinderE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskShapeBinder::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui15TaskShapeBinderE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskShapeBinder"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskShapeBinder, qt_meta_tag_ZN13PartDesignGui15TaskShapeBinderE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskShapeBinder::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui15TaskShapeBinderE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui15TaskShapeBinderE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui15TaskShapeBinderE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskShapeBinder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskShapeBinder *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskShapeBinder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskShapeBinder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui15TaskShapeBinderE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Gui::SelectionObserver"))
        return static_cast< Gui::SelectionObserver*>(this);
    return Gui::TaskView::TaskBox::qt_metacast(_clname);
}

int PartDesignGui::TaskShapeBinder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskBox::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN13PartDesignGui18TaskDlgShapeBinderE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDlgShapeBinder::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui18TaskDlgShapeBinderE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDlgShapeBinder"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDlgShapeBinder, qt_meta_tag_ZN13PartDesignGui18TaskDlgShapeBinderE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDlgShapeBinder::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui18TaskDlgShapeBinderE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui18TaskDlgShapeBinderE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui18TaskDlgShapeBinderE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDlgShapeBinder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDlgShapeBinder *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskDlgShapeBinder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDlgShapeBinder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui18TaskDlgShapeBinderE_t>.strings))
        return static_cast<void*>(this);
    return Gui::TaskView::TaskDialog::qt_metacast(_clname);
}

int PartDesignGui::TaskDlgShapeBinder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskDialog::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
