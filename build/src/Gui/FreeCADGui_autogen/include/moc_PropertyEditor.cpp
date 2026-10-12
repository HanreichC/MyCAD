/****************************************************************************
** Meta object code from reading C++ file 'PropertyEditor.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/propertyeditor/PropertyEditor.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertyEditor.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui14PropertyEditor14PropertyEditorE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyEditor::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor14PropertyEditorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyEditor",
        "onItemActivated",
        "",
        "QModelIndex",
        "index",
        "onItemExpanded",
        "onItemCollapsed",
        "onRowsMoved",
        "parent",
        "start",
        "end",
        "dst",
        "row",
        "onRowsRemoved",
        "groupBackground",
        "QBrush",
        "groupTextColor",
        "QColor",
        "itemBackground"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onItemActivated'
        QtMocHelpers::SlotData<void(const QModelIndex &)>(1, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'onItemExpanded'
        QtMocHelpers::SlotData<void(const QModelIndex &)>(5, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'onItemCollapsed'
        QtMocHelpers::SlotData<void(const QModelIndex &)>(6, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'onRowsMoved'
        QtMocHelpers::SlotData<void(const QModelIndex &, int, int, const QModelIndex &, int)>(7, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 3, 8 }, { QMetaType::Int, 9 }, { QMetaType::Int, 10 }, { 0x80000000 | 3, 11 },
            { QMetaType::Int, 12 },
        }}),
        // Slot 'onRowsRemoved'
        QtMocHelpers::SlotData<void(const QModelIndex &, int, int)>(13, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 3, 8 }, { QMetaType::Int, 9 }, { QMetaType::Int, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'groupBackground'
        QtMocHelpers::PropertyData<QBrush>(14, 0x80000000 | 15, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'groupTextColor'
        QtMocHelpers::PropertyData<QColor>(16, 0x80000000 | 17, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'itemBackground'
        QtMocHelpers::PropertyData<QBrush>(18, 0x80000000 | 15, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyEditor, qt_meta_tag_ZN3Gui14PropertyEditor14PropertyEditorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QTreeView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor14PropertyEditorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor14PropertyEditorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor14PropertyEditorE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyEditor *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onItemActivated((*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 1: _t->onItemExpanded((*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 2: _t->onItemCollapsed((*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 3: _t->onRowsMoved((*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5]))); break;
        case 4: _t->onRowsRemoved((*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QBrush*>(_v) = _t->groupBackground(); break;
        case 1: *reinterpret_cast<QColor*>(_v) = _t->groupTextColor(); break;
        case 2: *reinterpret_cast<QBrush*>(_v) = _t->itemBackground(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setGroupBackground(*reinterpret_cast<QBrush*>(_v)); break;
        case 1: _t->setGroupTextColor(*reinterpret_cast<QColor*>(_v)); break;
        case 2: _t->setItemBackground(*reinterpret_cast<QBrush*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor14PropertyEditorE_t>.strings))
        return static_cast<void*>(this);
    return QTreeView::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
