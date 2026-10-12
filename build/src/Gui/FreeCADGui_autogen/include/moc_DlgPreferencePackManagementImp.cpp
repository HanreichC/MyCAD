/****************************************************************************
** Meta object code from reading C++ file 'DlgPreferencePackManagementImp.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/Dialogs/DlgPreferencePackManagementImp.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgPreferencePackManagementImp.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui6Dialog30DlgPreferencePackManagementImpE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::DlgPreferencePackManagementImp::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog30DlgPreferencePackManagementImpE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::DlgPreferencePackManagementImp",
        "packVisibilityChanged",
        "",
        "deleteUserPack",
        "std::string",
        "prefPackName",
        "hideBuiltInPack",
        "hideInstalledPack",
        "addonName",
        "showAddonManager"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'packVisibilityChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'deleteUserPack'
        QtMocHelpers::SlotData<void(const std::string &)>(3, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'hideBuiltInPack'
        QtMocHelpers::SlotData<void(const std::string &)>(6, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'hideInstalledPack'
        QtMocHelpers::SlotData<void(const std::string &, const std::string &)>(7, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 4, 8 }, { 0x80000000 | 4, 5 },
        }}),
        // Slot 'showAddonManager'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessProtected, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DlgPreferencePackManagementImp, qt_meta_tag_ZN3Gui6Dialog30DlgPreferencePackManagementImpE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::Dialog::DlgPreferencePackManagementImp::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog30DlgPreferencePackManagementImpE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog30DlgPreferencePackManagementImpE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog30DlgPreferencePackManagementImpE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::DlgPreferencePackManagementImp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DlgPreferencePackManagementImp *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->packVisibilityChanged(); break;
        case 1: _t->deleteUserPack((*reinterpret_cast<std::add_pointer_t<std::string>>(_a[1]))); break;
        case 2: _t->hideBuiltInPack((*reinterpret_cast<std::add_pointer_t<std::string>>(_a[1]))); break;
        case 3: _t->hideInstalledPack((*reinterpret_cast<std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<std::string>>(_a[2]))); break;
        case 4: _t->showAddonManager(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DlgPreferencePackManagementImp::*)()>(_a, &DlgPreferencePackManagementImp::packVisibilityChanged, 0))
            return;
    }
}

const QMetaObject *Gui::Dialog::DlgPreferencePackManagementImp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::DlgPreferencePackManagementImp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog30DlgPreferencePackManagementImpE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Gui::Dialog::DlgPreferencePackManagementImp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Gui::Dialog::DlgPreferencePackManagementImp::packVisibilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
