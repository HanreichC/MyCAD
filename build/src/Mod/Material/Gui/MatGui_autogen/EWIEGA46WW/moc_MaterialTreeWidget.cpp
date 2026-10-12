/****************************************************************************
** Meta object code from reading C++ file 'MaterialTreeWidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/Material/Gui/MaterialTreeWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MaterialTreeWidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN6MatGui18MaterialTreeWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto MatGui::MaterialTreeWidget::qt_create_metaobjectdata<qt_meta_tag_ZN6MatGui18MaterialTreeWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MatGui::MaterialTreeWidget",
        "materialSelected",
        "",
        "std::shared_ptr<Materials::Material>",
        "material",
        "onMaterial",
        "uuid",
        "onExpanded",
        "expanded",
        "expandClicked",
        "checked",
        "editorClicked",
        "onSelectMaterial",
        "QItemSelection",
        "selected",
        "deselected",
        "onDoubleClick",
        "QModelIndex",
        "index",
        "onFilter",
        "text",
        "treeSizeHint",
        "QSize"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'materialSelected'
        QtMocHelpers::SignalData<void(const std::shared_ptr<Materials::Material> &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'onMaterial'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'onExpanded'
        QtMocHelpers::SignalData<void(bool)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 8 },
        }}),
        // Slot 'expandClicked'
        QtMocHelpers::SlotData<void(bool)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 10 },
        }}),
        // Slot 'editorClicked'
        QtMocHelpers::SlotData<void(bool)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 10 },
        }}),
        // Slot 'onSelectMaterial'
        QtMocHelpers::SlotData<void(const QItemSelection &, const QItemSelection &)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 13, 14 }, { 0x80000000 | 13, 15 },
        }}),
        // Slot 'onDoubleClick'
        QtMocHelpers::SlotData<void(const QModelIndex &)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
        // Slot 'onFilter'
        QtMocHelpers::SlotData<void(const QString &)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 20 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'treeSizeHint'
        QtMocHelpers::PropertyData<QSize>(21, 0x80000000 | 22, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MaterialTreeWidget, qt_meta_tag_ZN6MatGui18MaterialTreeWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MatGui::MaterialTreeWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6MatGui18MaterialTreeWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6MatGui18MaterialTreeWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6MatGui18MaterialTreeWidgetE_t>.metaTypes,
    nullptr
} };

void MatGui::MaterialTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MaterialTreeWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->materialSelected((*reinterpret_cast<std::add_pointer_t<std::shared_ptr<Materials::Material>>>(_a[1]))); break;
        case 1: _t->onMaterial((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->onExpanded((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->expandClicked((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->editorClicked((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->onSelectMaterial((*reinterpret_cast<std::add_pointer_t<QItemSelection>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QItemSelection>>(_a[2]))); break;
        case 6: _t->onDoubleClick((*reinterpret_cast<std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 7: _t->onFilter((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< std::shared_ptr<Materials::Material> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QItemSelection >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MaterialTreeWidget::*)(const std::shared_ptr<Materials::Material> & )>(_a, &MaterialTreeWidget::materialSelected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MaterialTreeWidget::*)(const QString & )>(_a, &MaterialTreeWidget::onMaterial, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MaterialTreeWidget::*)(bool )>(_a, &MaterialTreeWidget::onExpanded, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QSize*>(_v) = _t->treeSizeHint(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTreeSizeHint(*reinterpret_cast<QSize*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *MatGui::MaterialTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MatGui::MaterialTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6MatGui18MaterialTreeWidgetE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Base::BaseClass"))
        return static_cast< Base::BaseClass*>(this);
    return QWidget::qt_metacast(_clname);
}

int MatGui::MaterialTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void MatGui::MaterialTreeWidget::materialSelected(const std::shared_ptr<Materials::Material> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void MatGui::MaterialTreeWidget::onMaterial(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void MatGui::MaterialTreeWidget::onExpanded(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN6MatGui22PrefMaterialTreeWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto MatGui::PrefMaterialTreeWidget::qt_create_metaobjectdata<qt_meta_tag_ZN6MatGui22PrefMaterialTreeWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MatGui::PrefMaterialTreeWidget",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefMaterialTreeWidget, qt_meta_tag_ZN6MatGui22PrefMaterialTreeWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MatGui::PrefMaterialTreeWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<MaterialTreeWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6MatGui22PrefMaterialTreeWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6MatGui22PrefMaterialTreeWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6MatGui22PrefMaterialTreeWidgetE_t>.metaTypes,
    nullptr
} };

void MatGui::PrefMaterialTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefMaterialTreeWidget *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *MatGui::PrefMaterialTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MatGui::PrefMaterialTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6MatGui22PrefMaterialTreeWidgetE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Gui::PrefWidget"))
        return static_cast< Gui::PrefWidget*>(this);
    return MaterialTreeWidget::qt_metacast(_clname);
}

int MatGui::PrefMaterialTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MaterialTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
