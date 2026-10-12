/****************************************************************************
** Meta object code from reading C++ file 'Tree.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/Tree.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Tree.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui10TreeWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TreeWidget::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui10TreeWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TreeWidget",
        "emitSearchObjects",
        "",
        "onCreateGroup",
        "onRelabelObject",
        "onActivateDocument",
        "QAction*",
        "onStartEditing",
        "onFinishEditing",
        "onSelectDependents",
        "onSkipRecompute",
        "on",
        "onAllowPartialRecompute",
        "onReloadDoc",
        "onCloseDoc",
        "onMarkRecompute",
        "onRecomputeObject",
        "onPreSelectTimer",
        "onSelectTimer",
        "onShowHidden",
        "onToggleVisibilityInTree",
        "onSearchObjects",
        "onOpenFileLocation",
        "onItemSelectionChanged",
        "onItemChanged",
        "QTreeWidgetItem*",
        "onItemEntered",
        "item",
        "onItemCollapsed",
        "onItemExpanded",
        "onUpdateStatus"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'emitSearchObjects'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onCreateGroup'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onRelabelObject'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onActivateDocument'
        QtMocHelpers::SlotData<void(QAction *)>(5, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 6, 2 },
        }}),
        // Slot 'onStartEditing'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onFinishEditing'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onSelectDependents'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onSkipRecompute'
        QtMocHelpers::SlotData<void(bool)>(10, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::Bool, 11 },
        }}),
        // Slot 'onAllowPartialRecompute'
        QtMocHelpers::SlotData<void(bool)>(12, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::Bool, 11 },
        }}),
        // Slot 'onReloadDoc'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onCloseDoc'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onMarkRecompute'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onRecomputeObject'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onPreSelectTimer'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onSelectTimer'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onShowHidden'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onToggleVisibilityInTree'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onSearchObjects'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onOpenFileLocation'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onItemSelectionChanged'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onItemChanged'
        QtMocHelpers::SlotData<void(QTreeWidgetItem *, int)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 25, 2 }, { QMetaType::Int, 2 },
        }}),
        // Slot 'onItemEntered'
        QtMocHelpers::SlotData<void(QTreeWidgetItem *)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 25, 27 },
        }}),
        // Slot 'onItemCollapsed'
        QtMocHelpers::SlotData<void(QTreeWidgetItem *)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 25, 27 },
        }}),
        // Slot 'onItemExpanded'
        QtMocHelpers::SlotData<void(QTreeWidgetItem *)>(29, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 25, 27 },
        }}),
        // Slot 'onUpdateStatus'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TreeWidget, qt_meta_tag_ZN3Gui10TreeWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TreeWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QTreeWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10TreeWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10TreeWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui10TreeWidgetE_t>.metaTypes,
    nullptr
} };

void Gui::TreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TreeWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->emitSearchObjects(); break;
        case 1: _t->onCreateGroup(); break;
        case 2: _t->onRelabelObject(); break;
        case 3: _t->onActivateDocument((*reinterpret_cast<std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 4: _t->onStartEditing(); break;
        case 5: _t->onFinishEditing(); break;
        case 6: _t->onSelectDependents(); break;
        case 7: _t->onSkipRecompute((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->onAllowPartialRecompute((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->onReloadDoc(); break;
        case 10: _t->onCloseDoc(); break;
        case 11: _t->onMarkRecompute(); break;
        case 12: _t->onRecomputeObject(); break;
        case 13: _t->onPreSelectTimer(); break;
        case 14: _t->onSelectTimer(); break;
        case 15: _t->onShowHidden(); break;
        case 16: _t->onToggleVisibilityInTree(); break;
        case 17: _t->onSearchObjects(); break;
        case 18: _t->onOpenFileLocation(); break;
        case 19: _t->onItemSelectionChanged(); break;
        case 20: _t->onItemChanged((*reinterpret_cast<std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 21: _t->onItemEntered((*reinterpret_cast<std::add_pointer_t<QTreeWidgetItem*>>(_a[1]))); break;
        case 22: _t->onItemCollapsed((*reinterpret_cast<std::add_pointer_t<QTreeWidgetItem*>>(_a[1]))); break;
        case 23: _t->onItemExpanded((*reinterpret_cast<std::add_pointer_t<QTreeWidgetItem*>>(_a[1]))); break;
        case 24: _t->onUpdateStatus(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TreeWidget::*)()>(_a, &TreeWidget::emitSearchObjects, 0))
            return;
    }
}

const QMetaObject *Gui::TreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10TreeWidgetE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "SelectionObserver"))
        return static_cast< SelectionObserver*>(this);
    return QTreeWidget::qt_metacast(_clname);
}

int Gui::TreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void Gui::TreeWidget::emitSearchObjects()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN3Gui9TreePanelE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TreePanel::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui9TreePanelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TreePanel",
        "accept",
        "",
        "showEditor",
        "hideEditor",
        "itemSearch",
        "text"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'accept'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showEditor'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'hideEditor'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'itemSearch'
        QtMocHelpers::SlotData<void(const QString &)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TreePanel, qt_meta_tag_ZN3Gui9TreePanelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TreePanel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui9TreePanelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui9TreePanelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui9TreePanelE_t>.metaTypes,
    nullptr
} };

void Gui::TreePanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TreePanel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->showEditor(); break;
        case 2: _t->hideEditor(); break;
        case 3: _t->itemSearch((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *Gui::TreePanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TreePanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui9TreePanelE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Gui::TreePanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_tag_ZN3Gui14TreeDockWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TreeDockWidget::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14TreeDockWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TreeDockWidget"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TreeDockWidget, qt_meta_tag_ZN3Gui14TreeDockWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TreeDockWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::DockWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14TreeDockWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14TreeDockWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14TreeDockWidgetE_t>.metaTypes,
    nullptr
} };

void Gui::TreeDockWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TreeDockWidget *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::TreeDockWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TreeDockWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14TreeDockWidgetE_t>.strings))
        return static_cast<void*>(this);
    return Gui::DockWindow::qt_metacast(_clname);
}

int Gui::TreeDockWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::DockWindow::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
