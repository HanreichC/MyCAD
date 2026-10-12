/****************************************************************************
** Meta object code from reading C++ file 'DlgSettingsMaterial.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/Material/Gui/DlgSettingsMaterial.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgSettingsMaterial.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN6MatGui19DlgSettingsMaterialE_t {};
} // unnamed namespace

template <> constexpr inline auto MatGui::DlgSettingsMaterial::qt_create_metaobjectdata<qt_meta_tag_ZN6MatGui19DlgSettingsMaterialE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MatGui::DlgSettingsMaterial"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DlgSettingsMaterial, qt_meta_tag_ZN6MatGui19DlgSettingsMaterialE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MatGui::DlgSettingsMaterial::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::Dialog::PreferencePage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6MatGui19DlgSettingsMaterialE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6MatGui19DlgSettingsMaterialE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6MatGui19DlgSettingsMaterialE_t>.metaTypes,
    nullptr
} };

void MatGui::DlgSettingsMaterial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DlgSettingsMaterial *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *MatGui::DlgSettingsMaterial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MatGui::DlgSettingsMaterial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6MatGui19DlgSettingsMaterialE_t>.strings))
        return static_cast<void*>(this);
    return Gui::Dialog::PreferencePage::qt_metacast(_clname);
}

int MatGui::DlgSettingsMaterial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::Dialog::PreferencePage::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
