/****************************************************************************
** Meta object code from reading C++ file 'TaskSketcherElements.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/Sketcher/Gui/TaskSketcherElements.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskSketcherElements.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11SketcherGui11ElementViewE_t {};
} // unnamed namespace

template <> constexpr inline auto SketcherGui::ElementView::qt_create_metaobjectdata<qt_meta_tag_ZN11SketcherGui11ElementViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SketcherGui::ElementView",
        "onItemHovered",
        "",
        "QListWidgetItem*",
        "doPointCoincidence",
        "doPointOnObjectConstraint",
        "doVerticalDistance",
        "doHorizontalDistance",
        "doParallelConstraint",
        "doPerpendicularConstraint",
        "doTangentConstraint",
        "doEqualConstraint",
        "doSymmetricConstraint",
        "doBlockConstraint",
        "doGroupConstraint",
        "doConvertToGeometries",
        "doLockConstraint",
        "doHorizontalConstraint",
        "doVerticalConstraint",
        "doLengthConstraint",
        "doRadiusConstraint",
        "doDiameterConstraint",
        "doRadiamConstraint",
        "doAngleConstraint",
        "doToggleConstruction",
        "doSelectConstraints",
        "doSelectOrigin",
        "doSelectHAxis",
        "doSelectVAxis",
        "deleteSelectedItems",
        "onIndexHovered",
        "QModelIndex",
        "index",
        "onIndexChecked",
        "Qt::CheckState",
        "state"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'onItemHovered'
        QtMocHelpers::SignalData<void(QListWidgetItem *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Slot 'doPointCoincidence'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doPointOnObjectConstraint'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doVerticalDistance'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doHorizontalDistance'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doParallelConstraint'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doPerpendicularConstraint'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doTangentConstraint'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doEqualConstraint'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doSymmetricConstraint'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doBlockConstraint'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doGroupConstraint'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doConvertToGeometries'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doLockConstraint'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doHorizontalConstraint'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doVerticalConstraint'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doLengthConstraint'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doRadiusConstraint'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doDiameterConstraint'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doRadiamConstraint'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doAngleConstraint'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doToggleConstruction'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doSelectConstraints'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doSelectOrigin'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doSelectHAxis'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doSelectVAxis'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'deleteSelectedItems'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onIndexHovered'
        QtMocHelpers::SlotData<void(QModelIndex)>(30, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 31, 32 },
        }}),
        // Slot 'onIndexChecked'
        QtMocHelpers::SlotData<void(QModelIndex, Qt::CheckState)>(33, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 31, 2 }, { 0x80000000 | 34, 35 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ElementView, qt_meta_tag_ZN11SketcherGui11ElementViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SketcherGui::ElementView::staticMetaObject = { {
    QMetaObject::SuperData::link<QListWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui11ElementViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui11ElementViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11SketcherGui11ElementViewE_t>.metaTypes,
    nullptr
} };

void SketcherGui::ElementView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ElementView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onItemHovered((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 1: _t->doPointCoincidence(); break;
        case 2: _t->doPointOnObjectConstraint(); break;
        case 3: _t->doVerticalDistance(); break;
        case 4: _t->doHorizontalDistance(); break;
        case 5: _t->doParallelConstraint(); break;
        case 6: _t->doPerpendicularConstraint(); break;
        case 7: _t->doTangentConstraint(); break;
        case 8: _t->doEqualConstraint(); break;
        case 9: _t->doSymmetricConstraint(); break;
        case 10: _t->doBlockConstraint(); break;
        case 11: _t->doGroupConstraint(); break;
        case 12: _t->doConvertToGeometries(); break;
        case 13: _t->doLockConstraint(); break;
        case 14: _t->doHorizontalConstraint(); break;
        case 15: _t->doVerticalConstraint(); break;
        case 16: _t->doLengthConstraint(); break;
        case 17: _t->doRadiusConstraint(); break;
        case 18: _t->doDiameterConstraint(); break;
        case 19: _t->doRadiamConstraint(); break;
        case 20: _t->doAngleConstraint(); break;
        case 21: _t->doToggleConstruction(); break;
        case 22: _t->doSelectConstraints(); break;
        case 23: _t->doSelectOrigin(); break;
        case 24: _t->doSelectHAxis(); break;
        case 25: _t->doSelectVAxis(); break;
        case 26: _t->deleteSelectedItems(); break;
        case 27: _t->onIndexHovered((*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 28: _t->onIndexChecked((*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Qt::CheckState>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ElementView::*)(QListWidgetItem * )>(_a, &ElementView::onItemHovered, 0))
            return;
    }
}

const QMetaObject *SketcherGui::ElementView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SketcherGui::ElementView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui11ElementViewE_t>.strings))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int SketcherGui::ElementView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void SketcherGui::ElementView::onItemHovered(QListWidgetItem * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN11SketcherGui20TaskSketcherElementsE_t {};
} // unnamed namespace

template <> constexpr inline auto SketcherGui::TaskSketcherElements::qt_create_metaobjectdata<qt_meta_tag_ZN11SketcherGui20TaskSketcherElementsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SketcherGui::TaskSketcherElements",
        "onListWidgetElementsItemPressed",
        "",
        "QListWidgetItem*",
        "item",
        "onListWidgetElementsItemEntered",
        "onListWidgetElementsMouseMoveOnItem",
        "onListWidgetItemActivated",
        "onSettingsExtendedInformationChanged",
        "onFilterBoxStateChanged",
        "val",
        "onListMultiFilterItemChanged"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onListWidgetElementsItemPressed'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'onListWidgetElementsItemEntered'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'onListWidgetElementsMouseMoveOnItem'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'onListWidgetItemActivated'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'onSettingsExtendedInformationChanged'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onFilterBoxStateChanged'
        QtMocHelpers::SlotData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 },
        }}),
        // Slot 'onListMultiFilterItemChanged'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskSketcherElements, qt_meta_tag_ZN11SketcherGui20TaskSketcherElementsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SketcherGui::TaskSketcherElements::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui20TaskSketcherElementsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui20TaskSketcherElementsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11SketcherGui20TaskSketcherElementsE_t>.metaTypes,
    nullptr
} };

void SketcherGui::TaskSketcherElements::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskSketcherElements *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onListWidgetElementsItemPressed((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 1: _t->onListWidgetElementsItemEntered((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 2: _t->onListWidgetElementsMouseMoveOnItem((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 3: _t->onListWidgetItemActivated((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 4: _t->onSettingsExtendedInformationChanged(); break;
        case 5: _t->onFilterBoxStateChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->onListMultiFilterItemChanged((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *SketcherGui::TaskSketcherElements::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SketcherGui::TaskSketcherElements::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui20TaskSketcherElementsE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Gui::SelectionObserver"))
        return static_cast< Gui::SelectionObserver*>(this);
    return Gui::TaskView::TaskBox::qt_metacast(_clname);
}

int SketcherGui::TaskSketcherElements::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
