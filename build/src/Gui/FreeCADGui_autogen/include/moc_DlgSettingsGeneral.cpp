/****************************************************************************
** Meta object code from reading C++ file 'DlgSettingsGeneral.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/PreferencePages/DlgSettingsGeneral.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgSettingsGeneral.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui6Dialog18DlgSettingsGeneralE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::DlgSettingsGeneral::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog18DlgSettingsGeneralE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::DlgSettingsGeneral",
        "onLoadPreferencePackClicked",
        "",
        "std::string",
        "packName",
        "recreatePreferencePackMenu",
        "newPreferencePackDialogAccepted",
        "onManagePreferencePacksClicked",
        "onImportConfigClicked",
        "onThemeChanged",
        "index",
        "onLinkActivated",
        "link",
        "onUnitSystemIndexChanged"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onLoadPreferencePackClicked'
        QtMocHelpers::SlotData<void(const std::string &)>(1, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'recreatePreferencePackMenu'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'newPreferencePackDialogAccepted'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onManagePreferencePacksClicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onImportConfigClicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onThemeChanged'
        QtMocHelpers::SlotData<void(int)>(9, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::Int, 10 },
        }}),
        // Slot 'onLinkActivated'
        QtMocHelpers::SlotData<void(const QString &)>(11, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Slot 'onUnitSystemIndexChanged'
        QtMocHelpers::SlotData<void(int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DlgSettingsGeneral, qt_meta_tag_ZN3Gui6Dialog18DlgSettingsGeneralE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::DlgSettingsGeneral::staticMetaObject = { {
    QMetaObject::SuperData::link<PreferencePage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog18DlgSettingsGeneralE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog18DlgSettingsGeneralE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog18DlgSettingsGeneralE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::DlgSettingsGeneral::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DlgSettingsGeneral *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onLoadPreferencePackClicked((*reinterpret_cast<std::add_pointer_t<std::string>>(_a[1]))); break;
        case 1: _t->recreatePreferencePackMenu(); break;
        case 2: _t->newPreferencePackDialogAccepted(); break;
        case 3: _t->onManagePreferencePacksClicked(); break;
        case 4: _t->onImportConfigClicked(); break;
        case 5: _t->onThemeChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->onLinkActivated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onUnitSystemIndexChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *Gui::Dialog::DlgSettingsGeneral::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::DlgSettingsGeneral::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog18DlgSettingsGeneralE_t>.strings))
        return static_cast<void*>(this);
    return PreferencePage::qt_metacast(_clname);
}

int Gui::Dialog::DlgSettingsGeneral::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PreferencePage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
