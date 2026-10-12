/****************************************************************************
** Meta object code from reading C++ file 'TaskFeaturePick.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/PartDesign/Gui/TaskFeaturePick.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskFeaturePick.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13PartDesignGui15TaskFeaturePickE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskFeaturePick::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui15TaskFeaturePickE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskFeaturePick",
        "onUpdate",
        "",
        "onSelectionChanged",
        "Gui::SelectionChanges",
        "msg",
        "onItemSelectionChanged",
        "onDoubleClick",
        "QListWidgetItem*",
        "item"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onUpdate'
        QtMocHelpers::SlotData<void(bool)>(1, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'onSelectionChanged'
        QtMocHelpers::SlotData<void(const Gui::SelectionChanges &)>(3, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'onItemSelectionChanged'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onDoubleClick'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(7, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskFeaturePick, qt_meta_tag_ZN13PartDesignGui15TaskFeaturePickE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskFeaturePick::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui15TaskFeaturePickE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui15TaskFeaturePickE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui15TaskFeaturePickE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskFeaturePick::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskFeaturePick *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onUpdate((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->onSelectionChanged((*reinterpret_cast<std::add_pointer_t<Gui::SelectionChanges>>(_a[1]))); break;
        case 2: _t->onItemSelectionChanged(); break;
        case 3: _t->onDoubleClick((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *PartDesignGui::TaskFeaturePick::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskFeaturePick::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui15TaskFeaturePickE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Gui::SelectionObserver"))
        return static_cast< Gui::SelectionObserver*>(this);
    if (!strcmp(_clname, "Gui::DocumentObserver"))
        return static_cast< Gui::DocumentObserver*>(this);
    return Gui::TaskView::TaskBox::qt_metacast(_clname);
}

int PartDesignGui::TaskFeaturePick::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskBox::qt_metacall(_c, _id, _a);
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
struct qt_meta_tag_ZN13PartDesignGui18TaskDlgFeaturePickE_t {};
} // unnamed namespace

template <> constexpr inline auto PartDesignGui::TaskDlgFeaturePick::qt_create_metaobjectdata<qt_meta_tag_ZN13PartDesignGui18TaskDlgFeaturePickE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartDesignGui::TaskDlgFeaturePick"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskDlgFeaturePick, qt_meta_tag_ZN13PartDesignGui18TaskDlgFeaturePickE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartDesignGui::TaskDlgFeaturePick::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui18TaskDlgFeaturePickE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui18TaskDlgFeaturePickE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PartDesignGui18TaskDlgFeaturePickE_t>.metaTypes,
    nullptr
} };

void PartDesignGui::TaskDlgFeaturePick::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskDlgFeaturePick *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartDesignGui::TaskDlgFeaturePick::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartDesignGui::TaskDlgFeaturePick::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PartDesignGui18TaskDlgFeaturePickE_t>.strings))
        return static_cast<void*>(this);
    return Gui::TaskView::TaskDialog::qt_metacast(_clname);
}

int PartDesignGui::TaskDlgFeaturePick::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskDialog::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
