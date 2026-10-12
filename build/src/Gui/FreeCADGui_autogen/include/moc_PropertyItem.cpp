/****************************************************************************
** Meta object code from reading C++ file 'PropertyItem.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/propertyeditor/PropertyItem.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertyItem.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui14PropertyEditor12PropertyItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor12PropertyItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyItem, qt_meta_tag_ZN3Gui14PropertyEditor12PropertyItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor12PropertyItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor12PropertyItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor12PropertyItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor12PropertyItemE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ExpressionBinding"))
        return static_cast< ExpressionBinding*>(this);
    return QObject::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor18PropertyStringItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyStringItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyStringItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyStringItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyStringItem, qt_meta_tag_ZN3Gui14PropertyEditor18PropertyStringItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyStringItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyStringItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyStringItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyStringItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyStringItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyStringItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyStringItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyStringItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyStringItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyStringItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFontItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyFontItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFontItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyFontItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyFontItem, qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFontItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyFontItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFontItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFontItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFontItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyFontItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyFontItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyFontItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyFontItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFontItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyFontItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor21PropertySeparatorItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertySeparatorItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor21PropertySeparatorItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertySeparatorItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertySeparatorItem, qt_meta_tag_ZN3Gui14PropertyEditor21PropertySeparatorItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertySeparatorItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertySeparatorItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertySeparatorItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertySeparatorItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertySeparatorItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertySeparatorItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertySeparatorItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertySeparatorItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertySeparatorItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertySeparatorItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor19PropertyIntegerItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyIntegerItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor19PropertyIntegerItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyIntegerItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyIntegerItem, qt_meta_tag_ZN3Gui14PropertyEditor19PropertyIntegerItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyIntegerItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor19PropertyIntegerItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor19PropertyIntegerItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor19PropertyIntegerItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyIntegerItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyIntegerItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyIntegerItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyIntegerItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor19PropertyIntegerItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyIntegerItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor29PropertyIntegerConstraintItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyIntegerConstraintItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor29PropertyIntegerConstraintItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyIntegerConstraintItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyIntegerConstraintItem, qt_meta_tag_ZN3Gui14PropertyEditor29PropertyIntegerConstraintItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyIntegerConstraintItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor29PropertyIntegerConstraintItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor29PropertyIntegerConstraintItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor29PropertyIntegerConstraintItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyIntegerConstraintItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyIntegerConstraintItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyIntegerConstraintItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyIntegerConstraintItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor29PropertyIntegerConstraintItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyIntegerConstraintItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor17PropertyFloatItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyFloatItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyFloatItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyFloatItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyFloatItem, qt_meta_tag_ZN3Gui14PropertyEditor17PropertyFloatItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyFloatItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyFloatItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyFloatItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyFloatItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyFloatItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyFloatItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyFloatItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyFloatItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyFloatItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyFloatItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor16PropertyUnitItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyUnitItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyUnitItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyUnitItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyUnitItem, qt_meta_tag_ZN3Gui14PropertyEditor16PropertyUnitItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyUnitItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyUnitItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyUnitItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyUnitItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyUnitItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyUnitItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyUnitItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyUnitItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyUnitItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyUnitItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor26PropertyUnitConstraintItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyUnitConstraintItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyUnitConstraintItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyUnitConstraintItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyUnitConstraintItem, qt_meta_tag_ZN3Gui14PropertyEditor26PropertyUnitConstraintItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyUnitConstraintItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyUnitItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyUnitConstraintItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyUnitConstraintItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyUnitConstraintItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyUnitConstraintItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyUnitConstraintItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyUnitConstraintItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyUnitConstraintItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyUnitConstraintItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyUnitItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyUnitConstraintItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyUnitItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor27PropertyFloatConstraintItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyFloatConstraintItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor27PropertyFloatConstraintItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyFloatConstraintItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyFloatConstraintItem, qt_meta_tag_ZN3Gui14PropertyEditor27PropertyFloatConstraintItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyFloatConstraintItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor27PropertyFloatConstraintItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor27PropertyFloatConstraintItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor27PropertyFloatConstraintItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyFloatConstraintItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyFloatConstraintItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyFloatConstraintItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyFloatConstraintItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor27PropertyFloatConstraintItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyFloatConstraintItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPrecisionItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyPrecisionItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPrecisionItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyPrecisionItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyPrecisionItem, qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPrecisionItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyPrecisionItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyFloatConstraintItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPrecisionItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPrecisionItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPrecisionItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyPrecisionItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyPrecisionItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyPrecisionItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyPrecisionItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPrecisionItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyFloatConstraintItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyPrecisionItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyFloatConstraintItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor17PropertyAngleItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyAngleItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyAngleItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyAngleItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyAngleItem, qt_meta_tag_ZN3Gui14PropertyEditor17PropertyAngleItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyAngleItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyUnitConstraintItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyAngleItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyAngleItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyAngleItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyAngleItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyAngleItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyAngleItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyAngleItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyAngleItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyUnitConstraintItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyAngleItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyUnitConstraintItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor16PropertyBoolItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyBoolItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyBoolItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyBoolItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyBoolItem, qt_meta_tag_ZN3Gui14PropertyEditor16PropertyBoolItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyBoolItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyBoolItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyBoolItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyBoolItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyBoolItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyBoolItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyBoolItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyBoolItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyBoolItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyBoolItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor18PropertyVectorItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyVectorItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyVectorItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyVectorItem",
        "x",
        "y",
        "z"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'x'
        QtMocHelpers::PropertyData<double>(1, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'y'
        QtMocHelpers::PropertyData<double>(2, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'z'
        QtMocHelpers::PropertyData<double>(3, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyVectorItem, qt_meta_tag_ZN3Gui14PropertyEditor18PropertyVectorItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyVectorItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyVectorItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyVectorItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyVectorItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyVectorItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyVectorItem *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<double*>(_v) = _t->x(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->y(); break;
        case 2: *reinterpret_cast<double*>(_v) = _t->z(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setX(*reinterpret_cast<double*>(_v)); break;
        case 1: _t->setY(*reinterpret_cast<double*>(_v)); break;
        case 2: _t->setZ(*reinterpret_cast<double*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyVectorItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyVectorItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyVectorItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyVectorItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor20PropertyEditorWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyEditorWidget::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyEditorWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyEditorWidget",
        "buttonClick",
        "",
        "valueChanged",
        "QVariant",
        "setValue"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'buttonClick'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'valueChanged'
        QtMocHelpers::SignalData<void(const QVariant &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 2 },
        }}),
        // Slot 'setValue'
        QtMocHelpers::SlotData<void(const QVariant &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyEditorWidget, qt_meta_tag_ZN3Gui14PropertyEditor20PropertyEditorWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyEditorWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyEditorWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyEditorWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyEditorWidgetE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyEditorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyEditorWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->buttonClick(); break;
        case 1: _t->valueChanged((*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[1]))); break;
        case 2: _t->setValue((*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PropertyEditorWidget::*)()>(_a, &PropertyEditorWidget::buttonClick, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PropertyEditorWidget::*)(const QVariant & )>(_a, &PropertyEditorWidget::valueChanged, 1))
            return;
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyEditorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyEditorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyEditorWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyEditorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void Gui::PropertyEditor::PropertyEditorWidget::buttonClick()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Gui::PropertyEditor::PropertyEditorWidget::valueChanged(const QVariant & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor16VectorListWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::VectorListWidget::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor16VectorListWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::VectorListWidget",
        "buttonClicked",
        ""
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'buttonClicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<VectorListWidget, qt_meta_tag_ZN3Gui14PropertyEditor16VectorListWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::VectorListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyEditorWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16VectorListWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16VectorListWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor16VectorListWidgetE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::VectorListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<VectorListWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->buttonClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::VectorListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::VectorListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16VectorListWidgetE_t>.strings))
        return static_cast<void*>(this);
    return PropertyEditorWidget::qt_metacast(_clname);
}

int Gui::PropertyEditor::VectorListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyEditorWidget::qt_metacall(_c, _id, _a);
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
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor22PropertyVectorListItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyVectorListItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyVectorListItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyVectorListItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyVectorListItem, qt_meta_tag_ZN3Gui14PropertyEditor22PropertyVectorListItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyVectorListItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyVectorListItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyVectorListItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyVectorListItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyVectorListItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyVectorListItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyVectorListItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyVectorListItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyVectorListItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyVectorListItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor26PropertyVectorDistanceItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyVectorDistanceItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyVectorDistanceItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyVectorDistanceItem",
        "x",
        "Base::Quantity",
        "y",
        "z"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'x'
        QtMocHelpers::PropertyData<Base::Quantity>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'y'
        QtMocHelpers::PropertyData<Base::Quantity>(3, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'z'
        QtMocHelpers::PropertyData<Base::Quantity>(4, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyVectorDistanceItem, qt_meta_tag_ZN3Gui14PropertyEditor26PropertyVectorDistanceItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyVectorDistanceItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyVectorDistanceItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyVectorDistanceItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyVectorDistanceItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyVectorDistanceItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyVectorDistanceItem *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Base::Quantity >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<Base::Quantity*>(_v) = _t->x(); break;
        case 1: *reinterpret_cast<Base::Quantity*>(_v) = _t->y(); break;
        case 2: *reinterpret_cast<Base::Quantity*>(_v) = _t->z(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setX(*reinterpret_cast<Base::Quantity*>(_v)); break;
        case 1: _t->setY(*reinterpret_cast<Base::Quantity*>(_v)); break;
        case 2: _t->setZ(*reinterpret_cast<Base::Quantity*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyVectorDistanceItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyVectorDistanceItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor26PropertyVectorDistanceItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyVectorDistanceItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor20PropertyPositionItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyPositionItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyPositionItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyPositionItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyPositionItem, qt_meta_tag_ZN3Gui14PropertyEditor20PropertyPositionItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyPositionItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyVectorDistanceItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyPositionItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyPositionItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyPositionItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyPositionItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyPositionItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyPositionItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyPositionItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyPositionItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyVectorDistanceItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyPositionItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyVectorDistanceItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor21PropertyDirectionItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyDirectionItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyDirectionItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyDirectionItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyDirectionItem, qt_meta_tag_ZN3Gui14PropertyEditor21PropertyDirectionItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyDirectionItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyVectorDistanceItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyDirectionItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyDirectionItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyDirectionItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyDirectionItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyDirectionItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyDirectionItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyDirectionItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyDirectionItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyVectorDistanceItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyDirectionItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyVectorDistanceItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor18PropertyMatrixItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyMatrixItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyMatrixItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyMatrixItem",
        "A11",
        "A12",
        "A13",
        "A14",
        "A21",
        "A22",
        "A23",
        "A24",
        "A31",
        "A32",
        "A33",
        "A34",
        "A41",
        "A42",
        "A43",
        "A44"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'A11'
        QtMocHelpers::PropertyData<double>(1, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A12'
        QtMocHelpers::PropertyData<double>(2, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A13'
        QtMocHelpers::PropertyData<double>(3, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A14'
        QtMocHelpers::PropertyData<double>(4, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A21'
        QtMocHelpers::PropertyData<double>(5, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A22'
        QtMocHelpers::PropertyData<double>(6, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A23'
        QtMocHelpers::PropertyData<double>(7, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A24'
        QtMocHelpers::PropertyData<double>(8, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A31'
        QtMocHelpers::PropertyData<double>(9, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A32'
        QtMocHelpers::PropertyData<double>(10, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A33'
        QtMocHelpers::PropertyData<double>(11, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A34'
        QtMocHelpers::PropertyData<double>(12, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A41'
        QtMocHelpers::PropertyData<double>(13, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A42'
        QtMocHelpers::PropertyData<double>(14, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A43'
        QtMocHelpers::PropertyData<double>(15, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'A44'
        QtMocHelpers::PropertyData<double>(16, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyMatrixItem, qt_meta_tag_ZN3Gui14PropertyEditor18PropertyMatrixItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyMatrixItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyMatrixItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyMatrixItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyMatrixItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyMatrixItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyMatrixItem *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<double*>(_v) = _t->getA11(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->getA12(); break;
        case 2: *reinterpret_cast<double*>(_v) = _t->getA13(); break;
        case 3: *reinterpret_cast<double*>(_v) = _t->getA14(); break;
        case 4: *reinterpret_cast<double*>(_v) = _t->getA21(); break;
        case 5: *reinterpret_cast<double*>(_v) = _t->getA22(); break;
        case 6: *reinterpret_cast<double*>(_v) = _t->getA23(); break;
        case 7: *reinterpret_cast<double*>(_v) = _t->getA24(); break;
        case 8: *reinterpret_cast<double*>(_v) = _t->getA31(); break;
        case 9: *reinterpret_cast<double*>(_v) = _t->getA32(); break;
        case 10: *reinterpret_cast<double*>(_v) = _t->getA33(); break;
        case 11: *reinterpret_cast<double*>(_v) = _t->getA34(); break;
        case 12: *reinterpret_cast<double*>(_v) = _t->getA41(); break;
        case 13: *reinterpret_cast<double*>(_v) = _t->getA42(); break;
        case 14: *reinterpret_cast<double*>(_v) = _t->getA43(); break;
        case 15: *reinterpret_cast<double*>(_v) = _t->getA44(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setA11(*reinterpret_cast<double*>(_v)); break;
        case 1: _t->setA12(*reinterpret_cast<double*>(_v)); break;
        case 2: _t->setA13(*reinterpret_cast<double*>(_v)); break;
        case 3: _t->setA14(*reinterpret_cast<double*>(_v)); break;
        case 4: _t->setA21(*reinterpret_cast<double*>(_v)); break;
        case 5: _t->setA22(*reinterpret_cast<double*>(_v)); break;
        case 6: _t->setA23(*reinterpret_cast<double*>(_v)); break;
        case 7: _t->setA24(*reinterpret_cast<double*>(_v)); break;
        case 8: _t->setA31(*reinterpret_cast<double*>(_v)); break;
        case 9: _t->setA32(*reinterpret_cast<double*>(_v)); break;
        case 10: _t->setA33(*reinterpret_cast<double*>(_v)); break;
        case 11: _t->setA34(*reinterpret_cast<double*>(_v)); break;
        case 12: _t->setA41(*reinterpret_cast<double*>(_v)); break;
        case 13: _t->setA42(*reinterpret_cast<double*>(_v)); break;
        case 14: _t->setA43(*reinterpret_cast<double*>(_v)); break;
        case 15: _t->setA44(*reinterpret_cast<double*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyMatrixItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyMatrixItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyMatrixItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyMatrixItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor20PropertyRotationItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyRotationItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyRotationItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyRotationItem",
        "Angle",
        "Base::Quantity",
        "Axis",
        "Base::Vector3d"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'Angle'
        QtMocHelpers::PropertyData<Base::Quantity>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'Axis'
        QtMocHelpers::PropertyData<Base::Vector3d>(3, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyRotationItem, qt_meta_tag_ZN3Gui14PropertyEditor20PropertyRotationItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyRotationItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyRotationItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyRotationItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyRotationItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyRotationItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyRotationItem *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Base::Quantity >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Base::Vector3d >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<Base::Quantity*>(_v) = _t->getAngle(); break;
        case 1: *reinterpret_cast<Base::Vector3d*>(_v) = _t->getAxis(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAngle(*reinterpret_cast<Base::Quantity*>(_v)); break;
        case 1: _t->setAxis(*reinterpret_cast<Base::Vector3d*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyRotationItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyRotationItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyRotationItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyRotationItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
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
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor15PlacementEditorE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PlacementEditor::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor15PlacementEditorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PlacementEditor",
        "updateValue",
        "",
        "QVariant",
        "v"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'updateValue'
        QtMocHelpers::SlotData<void(const QVariant &, bool, bool)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::Bool, 2 }, { QMetaType::Bool, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlacementEditor, qt_meta_tag_ZN3Gui14PropertyEditor15PlacementEditorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PlacementEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::LabelButton::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor15PlacementEditorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor15PlacementEditorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor15PlacementEditorE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PlacementEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlacementEditor *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->updateValue((*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PlacementEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PlacementEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor15PlacementEditorE_t>.strings))
        return static_cast<void*>(this);
    return Gui::LabelButton::qt_metacast(_clname);
}

int Gui::PropertyEditor::PlacementEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::LabelButton::qt_metacall(_c, _id, _a);
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
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPlacementItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyPlacementItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPlacementItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyPlacementItem",
        "Angle",
        "Base::Quantity",
        "Axis",
        "Base::Vector3d",
        "Position"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'Angle'
        QtMocHelpers::PropertyData<Base::Quantity>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'Axis'
        QtMocHelpers::PropertyData<Base::Vector3d>(3, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'Position'
        QtMocHelpers::PropertyData<Base::Vector3d>(5, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyPlacementItem, qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPlacementItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyPlacementItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPlacementItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPlacementItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPlacementItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyPlacementItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyPlacementItem *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Base::Quantity >(); break;
        case 2:
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Base::Vector3d >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<Base::Quantity*>(_v) = _t->getAngle(); break;
        case 1: *reinterpret_cast<Base::Vector3d*>(_v) = _t->getAxis(); break;
        case 2: *reinterpret_cast<Base::Vector3d*>(_v) = _t->getPosition(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAngle(*reinterpret_cast<Base::Quantity*>(_v)); break;
        case 1: _t->setAxis(*reinterpret_cast<Base::Vector3d*>(_v)); break;
        case 2: _t->setPosition(*reinterpret_cast<Base::Vector3d*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyPlacementItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyPlacementItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyPlacementItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyPlacementItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor16PropertyEnumItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyEnumItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyEnumItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyEnumItem",
        "Enum"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'Enum'
        QtMocHelpers::PropertyData<QStringList>(1, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyEnumItem, qt_meta_tag_ZN3Gui14PropertyEditor16PropertyEnumItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyEnumItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyEnumItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyEnumItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyEnumItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyEnumItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyEnumItem *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QStringList*>(_v) = _t->getEnum(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEnum(*reinterpret_cast<QStringList*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyEnumItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyEnumItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyEnumItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyEnumItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor18PropertyEnumButtonE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyEnumButton::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyEnumButtonE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyEnumButton",
        "picked",
        ""
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'picked'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyEnumButton, qt_meta_tag_ZN3Gui14PropertyEditor18PropertyEnumButtonE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyEnumButton::staticMetaObject = { {
    QMetaObject::SuperData::link<QPushButton::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyEnumButtonE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyEnumButtonE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyEnumButtonE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyEnumButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyEnumButton *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->picked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PropertyEnumButton::*)()>(_a, &PropertyEnumButton::picked, 0))
            return;
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyEnumButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyEnumButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor18PropertyEnumButtonE_t>.strings))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyEnumButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Gui::PropertyEditor::PropertyEnumButton::picked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor22PropertyStringListItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyStringListItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyStringListItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyStringListItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyStringListItem, qt_meta_tag_ZN3Gui14PropertyEditor22PropertyStringListItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyStringListItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyStringListItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyStringListItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyStringListItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyStringListItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyStringListItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyStringListItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyStringListItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor22PropertyStringListItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyStringListItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor21PropertyFloatListItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyFloatListItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyFloatListItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyFloatListItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyFloatListItem, qt_meta_tag_ZN3Gui14PropertyEditor21PropertyFloatListItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyFloatListItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyFloatListItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyFloatListItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyFloatListItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyFloatListItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyFloatListItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyFloatListItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyFloatListItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor21PropertyFloatListItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyFloatListItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor23PropertyIntegerListItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyIntegerListItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor23PropertyIntegerListItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyIntegerListItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyIntegerListItem, qt_meta_tag_ZN3Gui14PropertyEditor23PropertyIntegerListItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyIntegerListItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor23PropertyIntegerListItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor23PropertyIntegerListItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor23PropertyIntegerListItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyIntegerListItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyIntegerListItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyIntegerListItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyIntegerListItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor23PropertyIntegerListItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyIntegerListItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor17PropertyColorItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyColorItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyColorItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyColorItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyColorItem, qt_meta_tag_ZN3Gui14PropertyEditor17PropertyColorItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyColorItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyColorItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyColorItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyColorItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyColorItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyColorItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyColorItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyColorItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor17PropertyColorItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyColorItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor20PropertyMaterialItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyMaterialItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyMaterialItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyMaterialItem",
        "AmbientColor",
        "QColor",
        "DiffuseColor",
        "SpecularColor",
        "EmissiveColor",
        "Shininess",
        "Transparency"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'AmbientColor'
        QtMocHelpers::PropertyData<QColor>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'DiffuseColor'
        QtMocHelpers::PropertyData<QColor>(3, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'SpecularColor'
        QtMocHelpers::PropertyData<QColor>(4, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'EmissiveColor'
        QtMocHelpers::PropertyData<QColor>(5, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'Shininess'
        QtMocHelpers::PropertyData<float>(6, QMetaType::Float, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'Transparency'
        QtMocHelpers::PropertyData<float>(7, QMetaType::Float, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyMaterialItem, qt_meta_tag_ZN3Gui14PropertyEditor20PropertyMaterialItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyMaterialItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyMaterialItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyMaterialItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyMaterialItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyMaterialItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyMaterialItem *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QColor*>(_v) = _t->getAmbientColor(); break;
        case 1: *reinterpret_cast<QColor*>(_v) = _t->getDiffuseColor(); break;
        case 2: *reinterpret_cast<QColor*>(_v) = _t->getSpecularColor(); break;
        case 3: *reinterpret_cast<QColor*>(_v) = _t->getEmissiveColor(); break;
        case 4: *reinterpret_cast<float*>(_v) = _t->getShininess(); break;
        case 5: *reinterpret_cast<float*>(_v) = _t->getTransparency(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAmbientColor(*reinterpret_cast<QColor*>(_v)); break;
        case 1: _t->setDiffuseColor(*reinterpret_cast<QColor*>(_v)); break;
        case 2: _t->setSpecularColor(*reinterpret_cast<QColor*>(_v)); break;
        case 3: _t->setEmissiveColor(*reinterpret_cast<QColor*>(_v)); break;
        case 4: _t->setShininess(*reinterpret_cast<float*>(_v)); break;
        case 5: _t->setTransparency(*reinterpret_cast<float*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyMaterialItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyMaterialItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyMaterialItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyMaterialItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor24PropertyMaterialListItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyMaterialListItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor24PropertyMaterialListItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyMaterialListItem",
        "AmbientColor",
        "QColor",
        "DiffuseColor",
        "SpecularColor",
        "EmissiveColor",
        "Shininess",
        "Transparency"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'AmbientColor'
        QtMocHelpers::PropertyData<QColor>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'DiffuseColor'
        QtMocHelpers::PropertyData<QColor>(3, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'SpecularColor'
        QtMocHelpers::PropertyData<QColor>(4, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'EmissiveColor'
        QtMocHelpers::PropertyData<QColor>(5, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User),
        // property 'Shininess'
        QtMocHelpers::PropertyData<float>(6, QMetaType::Float, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
        // property 'Transparency'
        QtMocHelpers::PropertyData<float>(7, QMetaType::Float, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::User),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyMaterialListItem, qt_meta_tag_ZN3Gui14PropertyEditor24PropertyMaterialListItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyMaterialListItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor24PropertyMaterialListItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor24PropertyMaterialListItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor24PropertyMaterialListItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyMaterialListItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyMaterialListItem *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QColor*>(_v) = _t->getAmbientColor(); break;
        case 1: *reinterpret_cast<QColor*>(_v) = _t->getDiffuseColor(); break;
        case 2: *reinterpret_cast<QColor*>(_v) = _t->getSpecularColor(); break;
        case 3: *reinterpret_cast<QColor*>(_v) = _t->getEmissiveColor(); break;
        case 4: *reinterpret_cast<float*>(_v) = _t->getShininess(); break;
        case 5: *reinterpret_cast<float*>(_v) = _t->getTransparency(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAmbientColor(*reinterpret_cast<QColor*>(_v)); break;
        case 1: _t->setDiffuseColor(*reinterpret_cast<QColor*>(_v)); break;
        case 2: _t->setSpecularColor(*reinterpret_cast<QColor*>(_v)); break;
        case 3: _t->setEmissiveColor(*reinterpret_cast<QColor*>(_v)); break;
        case 4: _t->setShininess(*reinterpret_cast<float*>(_v)); break;
        case 5: _t->setTransparency(*reinterpret_cast<float*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PropertyEditor::PropertyMaterialListItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyMaterialListItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor24PropertyMaterialListItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyMaterialListItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFileItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyFileItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFileItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyFileItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyFileItem, qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFileItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyFileItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFileItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFileItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFileItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyFileItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyFileItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyFileItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyFileItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyFileItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyFileItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor16PropertyPathItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyPathItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyPathItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyPathItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyPathItem, qt_meta_tag_ZN3Gui14PropertyEditor16PropertyPathItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyPathItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyPathItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyPathItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyPathItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyPathItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyPathItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyPathItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyPathItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyPathItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyPathItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor25PropertyTransientFileItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyTransientFileItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor25PropertyTransientFileItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyTransientFileItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyTransientFileItem, qt_meta_tag_ZN3Gui14PropertyEditor25PropertyTransientFileItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyTransientFileItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor25PropertyTransientFileItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor25PropertyTransientFileItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor25PropertyTransientFileItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyTransientFileItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyTransientFileItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyTransientFileItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyTransientFileItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor25PropertyTransientFileItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyTransientFileItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor13LinkSelectionE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::LinkSelection::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor13LinkSelectionE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::LinkSelection",
        "select",
        ""
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'select'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LinkSelection, qt_meta_tag_ZN3Gui14PropertyEditor13LinkSelectionE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::LinkSelection::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor13LinkSelectionE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor13LinkSelectionE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor13LinkSelectionE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::LinkSelection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LinkSelection *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->select(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::LinkSelection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::LinkSelection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor13LinkSelectionE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Gui::PropertyEditor::LinkSelection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor9LinkLabelE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::LinkLabel::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor9LinkLabelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::LinkLabel",
        "linkChanged",
        "",
        "QVariant",
        "onLinkActivated",
        "onEditClicked",
        "onLinkChanged"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'linkChanged'
        QtMocHelpers::SignalData<void(const QVariant &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Slot 'onLinkActivated'
        QtMocHelpers::SlotData<void(const QString &)>(4, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Slot 'onEditClicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'onLinkChanged'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessProtected, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LinkLabel, qt_meta_tag_ZN3Gui14PropertyEditor9LinkLabelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::LinkLabel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor9LinkLabelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor9LinkLabelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor9LinkLabelE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::LinkLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LinkLabel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->linkChanged((*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[1]))); break;
        case 1: _t->onLinkActivated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->onEditClicked(); break;
        case 3: _t->onLinkChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LinkLabel::*)(const QVariant & )>(_a, &LinkLabel::linkChanged, 0))
            return;
    }
}

const QMetaObject *Gui::PropertyEditor::LinkLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::LinkLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor9LinkLabelE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Gui::PropertyEditor::LinkLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void Gui::PropertyEditor::LinkLabel::linkChanged(const QVariant & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor16PropertyLinkItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyLinkItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyLinkItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyLinkItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyLinkItem, qt_meta_tag_ZN3Gui14PropertyEditor16PropertyLinkItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyLinkItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyLinkItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyLinkItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyLinkItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyLinkItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyLinkItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyLinkItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyLinkItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor16PropertyLinkItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyLinkItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor20PropertyLinkListItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyLinkListItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyLinkListItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyLinkListItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyLinkListItem, qt_meta_tag_ZN3Gui14PropertyEditor20PropertyLinkListItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyLinkListItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyLinkItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyLinkListItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyLinkListItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyLinkListItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyLinkListItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyLinkListItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyLinkListItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyLinkListItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor20PropertyLinkListItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyLinkItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyLinkListItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyLinkItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui14PropertyEditor15PropertyMapItemE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PropertyEditor::PropertyMapItem::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui14PropertyEditor15PropertyMapItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PropertyEditor::PropertyMapItem"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyMapItem, qt_meta_tag_ZN3Gui14PropertyEditor15PropertyMapItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PropertyEditor::PropertyMapItem::staticMetaObject = { {
    QMetaObject::SuperData::link<PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor15PropertyMapItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor15PropertyMapItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui14PropertyEditor15PropertyMapItemE_t>.metaTypes,
    nullptr
} };

void Gui::PropertyEditor::PropertyMapItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyMapItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::PropertyEditor::PropertyMapItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PropertyEditor::PropertyMapItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui14PropertyEditor15PropertyMapItemE_t>.strings))
        return static_cast<void*>(this);
    return PropertyItem::qt_metacast(_clname);
}

int Gui::PropertyEditor::PropertyMapItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyItem::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
