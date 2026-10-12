/****************************************************************************
** Meta object code from reading C++ file 'PropertyPage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/PropertyPage.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertyPage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui6Dialog12PropertyPageE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::PropertyPage::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog12PropertyPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::PropertyPage",
        "loadSettings",
        "",
        "saveSettings"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'loadSettings'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'saveSettings'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessProtected, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyPage, qt_meta_tag_ZN3Gui6Dialog12PropertyPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::PropertyPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog12PropertyPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog12PropertyPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog12PropertyPageE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::PropertyPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->loadSettings(); break;
        case 1: _t->saveSettings(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Gui::Dialog::PropertyPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::PropertyPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog12PropertyPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Gui::Dialog::PropertyPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui6Dialog14PreferencePageE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::PreferencePage::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog14PreferencePageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::PreferencePage",
        "loadSettings",
        "",
        "saveSettings",
        "resetSettingsToDefaults"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'loadSettings'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveSettings'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'resetSettingsToDefaults'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PreferencePage, qt_meta_tag_ZN3Gui6Dialog14PreferencePageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::PreferencePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog14PreferencePageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog14PreferencePageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog14PreferencePageE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::PreferencePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PreferencePage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->loadSettings(); break;
        case 1: _t->saveSettings(); break;
        case 2: _t->resetSettingsToDefaults(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Gui::Dialog::PreferencePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::PreferencePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog14PreferencePageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Gui::Dialog::PreferencePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui6Dialog16PreferenceUiFormE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::PreferenceUiForm::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog16PreferenceUiFormE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::PreferenceUiForm"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PreferenceUiForm, qt_meta_tag_ZN3Gui6Dialog16PreferenceUiFormE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::PreferenceUiForm::staticMetaObject = { {
    QMetaObject::SuperData::link<PreferencePage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog16PreferenceUiFormE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog16PreferenceUiFormE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog16PreferenceUiFormE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::PreferenceUiForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PreferenceUiForm *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::Dialog::PreferenceUiForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::PreferenceUiForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog16PreferenceUiFormE_t>.strings))
        return static_cast<void*>(this);
    return PreferencePage::qt_metacast(_clname);
}

int Gui::Dialog::PreferenceUiForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PreferencePage::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui6Dialog19CustomizeActionPageE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::CustomizeActionPage::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog19CustomizeActionPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::CustomizeActionPage",
        "onAddMacroAction",
        "",
        "onRemoveMacroAction",
        "onModifyMacroAction"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onAddMacroAction'
        QtMocHelpers::SlotData<void(const QByteArray &)>(1, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QByteArray, 2 },
        }}),
        // Slot 'onRemoveMacroAction'
        QtMocHelpers::SlotData<void(const QByteArray &)>(3, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QByteArray, 2 },
        }}),
        // Slot 'onModifyMacroAction'
        QtMocHelpers::SlotData<void(const QByteArray &)>(4, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QByteArray, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CustomizeActionPage, qt_meta_tag_ZN3Gui6Dialog19CustomizeActionPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::CustomizeActionPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog19CustomizeActionPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog19CustomizeActionPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog19CustomizeActionPageE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::CustomizeActionPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CustomizeActionPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onAddMacroAction((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 1: _t->onRemoveMacroAction((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 2: _t->onModifyMacroAction((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *Gui::Dialog::CustomizeActionPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::CustomizeActionPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog19CustomizeActionPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Gui::Dialog::CustomizeActionPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
