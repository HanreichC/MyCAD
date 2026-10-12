/****************************************************************************
** Meta object code from reading C++ file 'DlgSettingsViewColor.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/PreferencePages/DlgSettingsViewColor.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgSettingsViewColor.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui6Dialog20DlgSettingsViewColorE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::DlgSettingsViewColor::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog20DlgSettingsViewColorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::DlgSettingsViewColor",
        "onSwitchGradientColorsPressed",
        "",
        "onRadioButtonSimpleToggled",
        "val",
        "onRadioButtonGradientToggled",
        "onRadioButtonRadialGradientToggled",
        "onCheckMidColorToggled"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onSwitchGradientColorsPressed'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onRadioButtonSimpleToggled'
        QtMocHelpers::SlotData<void(bool)>(3, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::Bool, 4 },
        }}),
        // Slot 'onRadioButtonGradientToggled'
        QtMocHelpers::SlotData<void(bool)>(5, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::Bool, 4 },
        }}),
        // Slot 'onRadioButtonRadialGradientToggled'
        QtMocHelpers::SlotData<void(bool)>(6, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::Bool, 4 },
        }}),
        // Slot 'onCheckMidColorToggled'
        QtMocHelpers::SlotData<void(bool)>(7, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::Bool, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DlgSettingsViewColor, qt_meta_tag_ZN3Gui6Dialog20DlgSettingsViewColorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::DlgSettingsViewColor::staticMetaObject = { {
    QMetaObject::SuperData::link<PreferencePage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog20DlgSettingsViewColorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog20DlgSettingsViewColorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog20DlgSettingsViewColorE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::DlgSettingsViewColor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DlgSettingsViewColor *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onSwitchGradientColorsPressed(); break;
        case 1: _t->onRadioButtonSimpleToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->onRadioButtonGradientToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->onRadioButtonRadialGradientToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->onCheckMidColorToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *Gui::Dialog::DlgSettingsViewColor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::DlgSettingsViewColor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog20DlgSettingsViewColorE_t>.strings))
        return static_cast<void*>(this);
    return PreferencePage::qt_metacast(_clname);
}

int Gui::Dialog::DlgSettingsViewColor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PreferencePage::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_WARNING_POP
