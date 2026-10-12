/****************************************************************************
** Meta object code from reading C++ file 'TaskTransform.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/TaskTransform.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskTransform.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui13TaskTransformE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TaskTransform::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui13TaskTransformE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TaskTransform",
        "onPlacementModeChange",
        "",
        "index",
        "onPickTransformOrigin",
        "onPickCoordinateSystemReference",
        "onTransformOriginReset",
        "onAlignRotationChanged",
        "onAlignToOtherObject",
        "onFlip",
        "onCoordinateSystemChange",
        "mode",
        "onPositionChange",
        "onRotationChange",
        "QuantitySpinBox*",
        "changed",
        "SelectionMode",
        "None",
        "SelectTransformOrigin",
        "SelectAlignTarget",
        "SelectCustomCS",
        "PlacementMode",
        "ObjectOrigin",
        "Centroid",
        "Custom",
        "PositionMode",
        "Local",
        "Global"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onPlacementModeChange'
        QtMocHelpers::SlotData<void(int)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'onPickTransformOrigin'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPickCoordinateSystemReference'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransformOriginReset'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAlignRotationChanged'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAlignToOtherObject'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onFlip'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCoordinateSystemChange'
        QtMocHelpers::SlotData<void(int)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Slot 'onPositionChange'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRotationChange'
        QtMocHelpers::SlotData<void(QuantitySpinBox *)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'SelectionMode'
        QtMocHelpers::EnumData<enum SelectionMode>(16, 16, QMC::EnumIsScoped).add({
            {   17, SelectionMode::None },
            {   18, SelectionMode::SelectTransformOrigin },
            {   19, SelectionMode::SelectAlignTarget },
            {   20, SelectionMode::SelectCustomCS },
        }),
        // enum 'PlacementMode'
        QtMocHelpers::EnumData<enum PlacementMode>(21, 21, QMC::EnumIsScoped).add({
            {   22, PlacementMode::ObjectOrigin },
            {   23, PlacementMode::Centroid },
            {   24, PlacementMode::Custom },
        }),
        // enum 'PositionMode'
        QtMocHelpers::EnumData<enum PositionMode>(25, 25, QMC::EnumIsScoped).add({
            {   26, PositionMode::Local },
            {   27, PositionMode::Global },
            {   24, PositionMode::Custom },
        }),
    };
    return QtMocHelpers::metaObjectData<TaskTransform, qt_meta_tag_ZN3Gui13TaskTransformE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TaskTransform::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui13TaskTransformE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui13TaskTransformE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui13TaskTransformE_t>.metaTypes,
    nullptr
} };

void Gui::TaskTransform::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskTransform *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onPlacementModeChange((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->onPickTransformOrigin(); break;
        case 2: _t->onPickCoordinateSystemReference(); break;
        case 3: _t->onTransformOriginReset(); break;
        case 4: _t->onAlignRotationChanged(); break;
        case 5: _t->onAlignToOtherObject(); break;
        case 6: _t->onFlip(); break;
        case 7: _t->onCoordinateSystemChange((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->onPositionChange(); break;
        case 9: _t->onRotationChange((*reinterpret_cast<std::add_pointer_t<QuantitySpinBox*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *Gui::TaskTransform::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TaskTransform::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui13TaskTransformE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Gui::SelectionObserver"))
        return static_cast< Gui::SelectionObserver*>(this);
    return Gui::TaskView::TaskBox::qt_metacast(_clname);
}

int Gui::TaskTransform::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui19TaskTransformDialogE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TaskTransformDialog::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui19TaskTransformDialogE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TaskTransformDialog"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskTransformDialog, qt_meta_tag_ZN3Gui19TaskTransformDialogE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TaskTransformDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui19TaskTransformDialogE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui19TaskTransformDialogE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui19TaskTransformDialogE_t>.metaTypes,
    nullptr
} };

void Gui::TaskTransformDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskTransformDialog *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::TaskTransformDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TaskTransformDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui19TaskTransformDialogE_t>.strings))
        return static_cast<void*>(this);
    return Gui::TaskView::TaskDialog::qt_metacast(_clname);
}

int Gui::TaskTransformDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskDialog::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
