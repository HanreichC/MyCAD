/****************************************************************************
** Meta object code from reading C++ file 'TaskSketcherConstraints.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/Sketcher/Gui/TaskSketcherConstraints.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskSketcherConstraints.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11SketcherGui14ConstraintViewE_t {};
} // unnamed namespace

template <> constexpr inline auto SketcherGui::ConstraintView::qt_create_metaobjectdata<qt_meta_tag_ZN11SketcherGui14ConstraintViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SketcherGui::ConstraintView",
        "onUpdateDrivingStatus",
        "",
        "QListWidgetItem*",
        "item",
        "status",
        "onUpdateActiveStatus",
        "emitCenterSelectedItems",
        "emitHideSelection3DVisibility",
        "emitShowSelection3DVisibility",
        "emitDeleteAllConstraints",
        "emitDeleteConstraints",
        "QList<int>",
        "modifyCurrentItem",
        "renameCurrentItem",
        "centerSelectedItems",
        "deleteSelectedItems",
        "deleteAllItems",
        "deleteFilterItems",
        "doSelectConstraints",
        "updateDrivingStatus",
        "updateActiveStatus",
        "swapNamedOfSelectedItems",
        "showConstraints",
        "hideConstraints"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'onUpdateDrivingStatus'
        QtMocHelpers::SignalData<void(QListWidgetItem *, bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::Bool, 5 },
        }}),
        // Signal 'onUpdateActiveStatus'
        QtMocHelpers::SignalData<void(QListWidgetItem *, bool)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::Bool, 5 },
        }}),
        // Signal 'emitCenterSelectedItems'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'emitHideSelection3DVisibility'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'emitShowSelection3DVisibility'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'emitDeleteAllConstraints'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'emitDeleteConstraints'
        QtMocHelpers::SignalData<void(const QList<int> &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 2 },
        }}),
        // Slot 'modifyCurrentItem'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'renameCurrentItem'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'centerSelectedItems'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'deleteSelectedItems'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'deleteAllItems'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'deleteFilterItems'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'doSelectConstraints'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'updateDrivingStatus'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'updateActiveStatus'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'swapNamedOfSelectedItems'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'showConstraints'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'hideConstraints'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessProtected, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ConstraintView, qt_meta_tag_ZN11SketcherGui14ConstraintViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SketcherGui::ConstraintView::staticMetaObject = { {
    QMetaObject::SuperData::link<QListWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui14ConstraintViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui14ConstraintViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11SketcherGui14ConstraintViewE_t>.metaTypes,
    nullptr
} };

void SketcherGui::ConstraintView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ConstraintView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onUpdateDrivingStatus((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 1: _t->onUpdateActiveStatus((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 2: _t->emitCenterSelectedItems(); break;
        case 3: _t->emitHideSelection3DVisibility(); break;
        case 4: _t->emitShowSelection3DVisibility(); break;
        case 5: _t->emitDeleteAllConstraints(); break;
        case 6: _t->emitDeleteConstraints((*reinterpret_cast<std::add_pointer_t<QList<int>>>(_a[1]))); break;
        case 7: _t->modifyCurrentItem(); break;
        case 8: _t->renameCurrentItem(); break;
        case 9: _t->centerSelectedItems(); break;
        case 10: _t->deleteSelectedItems(); break;
        case 11: _t->deleteAllItems(); break;
        case 12: _t->deleteFilterItems(); break;
        case 13: _t->doSelectConstraints(); break;
        case 14: _t->updateDrivingStatus(); break;
        case 15: _t->updateActiveStatus(); break;
        case 16: _t->swapNamedOfSelectedItems(); break;
        case 17: _t->showConstraints(); break;
        case 18: _t->hideConstraints(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ConstraintView::*)(QListWidgetItem * , bool )>(_a, &ConstraintView::onUpdateDrivingStatus, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ConstraintView::*)(QListWidgetItem * , bool )>(_a, &ConstraintView::onUpdateActiveStatus, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ConstraintView::*)()>(_a, &ConstraintView::emitCenterSelectedItems, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ConstraintView::*)()>(_a, &ConstraintView::emitHideSelection3DVisibility, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ConstraintView::*)()>(_a, &ConstraintView::emitShowSelection3DVisibility, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ConstraintView::*)()>(_a, &ConstraintView::emitDeleteAllConstraints, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ConstraintView::*)(const QList<int> & )>(_a, &ConstraintView::emitDeleteConstraints, 6))
            return;
    }
}

const QMetaObject *SketcherGui::ConstraintView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SketcherGui::ConstraintView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui14ConstraintViewE_t>.strings))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int SketcherGui::ConstraintView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void SketcherGui::ConstraintView::onUpdateDrivingStatus(QListWidgetItem * _t1, bool _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void SketcherGui::ConstraintView::onUpdateActiveStatus(QListWidgetItem * _t1, bool _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void SketcherGui::ConstraintView::emitCenterSelectedItems()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SketcherGui::ConstraintView::emitHideSelection3DVisibility()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SketcherGui::ConstraintView::emitShowSelection3DVisibility()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SketcherGui::ConstraintView::emitDeleteAllConstraints()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SketcherGui::ConstraintView::emitDeleteConstraints(const QList<int> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN11SketcherGui20ConstraintFilterListE_t {};
} // unnamed namespace

template <> constexpr inline auto SketcherGui::ConstraintFilterList::qt_create_metaobjectdata<qt_meta_tag_ZN11SketcherGui20ConstraintFilterListE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SketcherGui::ConstraintFilterList"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ConstraintFilterList, qt_meta_tag_ZN11SketcherGui20ConstraintFilterListE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SketcherGui::ConstraintFilterList::staticMetaObject = { {
    QMetaObject::SuperData::link<QListWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui20ConstraintFilterListE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui20ConstraintFilterListE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11SketcherGui20ConstraintFilterListE_t>.metaTypes,
    nullptr
} };

void SketcherGui::ConstraintFilterList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ConstraintFilterList *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *SketcherGui::ConstraintFilterList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SketcherGui::ConstraintFilterList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui20ConstraintFilterListE_t>.strings))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int SketcherGui::ConstraintFilterList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN11SketcherGui23TaskSketcherConstraintsE_t {};
} // unnamed namespace

template <> constexpr inline auto SketcherGui::TaskSketcherConstraints::qt_create_metaobjectdata<qt_meta_tag_ZN11SketcherGui23TaskSketcherConstraintsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SketcherGui::TaskSketcherConstraints",
        "deferredUpdateList",
        ""
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'deferredUpdateList'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskSketcherConstraints, qt_meta_tag_ZN11SketcherGui23TaskSketcherConstraintsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SketcherGui::TaskSketcherConstraints::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui23TaskSketcherConstraintsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui23TaskSketcherConstraintsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11SketcherGui23TaskSketcherConstraintsE_t>.metaTypes,
    nullptr
} };

void SketcherGui::TaskSketcherConstraints::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskSketcherConstraints *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->deferredUpdateList(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *SketcherGui::TaskSketcherConstraints::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SketcherGui::TaskSketcherConstraints::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SketcherGui23TaskSketcherConstraintsE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Gui::SelectionObserver"))
        return static_cast< Gui::SelectionObserver*>(this);
    if (!strcmp(_clname, "ParameterGrp::ObserverType"))
        return static_cast< ParameterGrp::ObserverType*>(this);
    return Gui::TaskView::TaskBox::qt_metacast(_clname);
}

int SketcherGui::TaskSketcherConstraints::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskBox::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
