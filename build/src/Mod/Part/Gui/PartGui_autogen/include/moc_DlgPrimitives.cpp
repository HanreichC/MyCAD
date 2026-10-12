/****************************************************************************
** Meta object code from reading C++ file 'DlgPrimitives.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/Part/Gui/DlgPrimitives.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgPrimitives.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7PartGui17AbstractPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::AbstractPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui17AbstractPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::AbstractPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AbstractPrimitive, qt_meta_tag_ZN7PartGui17AbstractPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::AbstractPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui17AbstractPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui17AbstractPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui17AbstractPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::AbstractPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AbstractPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::AbstractPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::AbstractPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui17AbstractPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PartGui::AbstractPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui14PlanePrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::PlanePrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui14PlanePrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::PlanePrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlanePrimitive, qt_meta_tag_ZN7PartGui14PlanePrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::PlanePrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14PlanePrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14PlanePrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui14PlanePrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::PlanePrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlanePrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::PlanePrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::PlanePrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14PlanePrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::PlanePrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui12BoxPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::BoxPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui12BoxPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::BoxPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BoxPrimitive, qt_meta_tag_ZN7PartGui12BoxPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::BoxPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui12BoxPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui12BoxPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui12BoxPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::BoxPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BoxPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::BoxPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::BoxPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui12BoxPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::BoxPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui17CylinderPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::CylinderPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui17CylinderPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::CylinderPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CylinderPrimitive, qt_meta_tag_ZN7PartGui17CylinderPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::CylinderPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui17CylinderPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui17CylinderPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui17CylinderPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::CylinderPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CylinderPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::CylinderPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::CylinderPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui17CylinderPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::CylinderPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui13ConePrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::ConePrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui13ConePrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::ConePrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ConePrimitive, qt_meta_tag_ZN7PartGui13ConePrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::ConePrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui13ConePrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui13ConePrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui13ConePrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::ConePrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ConePrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::ConePrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::ConePrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui13ConePrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::ConePrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui15SpherePrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::SpherePrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui15SpherePrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::SpherePrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SpherePrimitive, qt_meta_tag_ZN7PartGui15SpherePrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::SpherePrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15SpherePrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15SpherePrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui15SpherePrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::SpherePrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SpherePrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::SpherePrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::SpherePrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15SpherePrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::SpherePrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui18EllipsoidPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::EllipsoidPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui18EllipsoidPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::EllipsoidPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<EllipsoidPrimitive, qt_meta_tag_ZN7PartGui18EllipsoidPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::EllipsoidPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui18EllipsoidPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui18EllipsoidPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui18EllipsoidPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::EllipsoidPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EllipsoidPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::EllipsoidPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::EllipsoidPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui18EllipsoidPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::EllipsoidPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui14TorusPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::TorusPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui14TorusPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::TorusPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TorusPrimitive, qt_meta_tag_ZN7PartGui14TorusPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::TorusPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14TorusPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14TorusPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui14TorusPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::TorusPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TorusPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::TorusPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::TorusPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14TorusPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::TorusPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui14PrismPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::PrismPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui14PrismPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::PrismPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrismPrimitive, qt_meta_tag_ZN7PartGui14PrismPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::PrismPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14PrismPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14PrismPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui14PrismPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::PrismPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrismPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::PrismPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::PrismPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14PrismPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::PrismPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui14WedgePrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::WedgePrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui14WedgePrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::WedgePrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<WedgePrimitive, qt_meta_tag_ZN7PartGui14WedgePrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::WedgePrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14WedgePrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14WedgePrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui14WedgePrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::WedgePrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WedgePrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::WedgePrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::WedgePrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14WedgePrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::WedgePrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui14HelixPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::HelixPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui14HelixPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::HelixPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<HelixPrimitive, qt_meta_tag_ZN7PartGui14HelixPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::HelixPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14HelixPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14HelixPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui14HelixPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::HelixPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<HelixPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::HelixPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::HelixPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14HelixPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::HelixPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui15SpiralPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::SpiralPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui15SpiralPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::SpiralPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SpiralPrimitive, qt_meta_tag_ZN7PartGui15SpiralPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::SpiralPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15SpiralPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15SpiralPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui15SpiralPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::SpiralPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SpiralPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::SpiralPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::SpiralPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15SpiralPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::SpiralPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui15CirclePrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::CirclePrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui15CirclePrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::CirclePrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CirclePrimitive, qt_meta_tag_ZN7PartGui15CirclePrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::CirclePrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15CirclePrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15CirclePrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui15CirclePrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::CirclePrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CirclePrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::CirclePrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::CirclePrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15CirclePrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::CirclePrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui16EllipsePrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::EllipsePrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui16EllipsePrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::EllipsePrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<EllipsePrimitive, qt_meta_tag_ZN7PartGui16EllipsePrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::EllipsePrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui16EllipsePrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui16EllipsePrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui16EllipsePrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::EllipsePrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EllipsePrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::EllipsePrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::EllipsePrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui16EllipsePrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::EllipsePrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui16PolygonPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::PolygonPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui16PolygonPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::PolygonPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PolygonPrimitive, qt_meta_tag_ZN7PartGui16PolygonPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::PolygonPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui16PolygonPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui16PolygonPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui16PolygonPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::PolygonPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PolygonPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::PolygonPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::PolygonPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui16PolygonPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::PolygonPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui13LinePrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::LinePrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui13LinePrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::LinePrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LinePrimitive, qt_meta_tag_ZN7PartGui13LinePrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::LinePrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui13LinePrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui13LinePrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui13LinePrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::LinePrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LinePrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::LinePrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::LinePrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui13LinePrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::LinePrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui15VertexPrimitiveE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::VertexPrimitive::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui15VertexPrimitiveE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::VertexPrimitive"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<VertexPrimitive, qt_meta_tag_ZN7PartGui15VertexPrimitiveE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::VertexPrimitive::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractPrimitive::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15VertexPrimitiveE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15VertexPrimitiveE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui15VertexPrimitiveE_t>.metaTypes,
    nullptr
} };

void PartGui::VertexPrimitive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<VertexPrimitive *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::VertexPrimitive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::VertexPrimitive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui15VertexPrimitiveE_t>.strings))
        return static_cast<void*>(this);
    return AbstractPrimitive::qt_metacast(_clname);
}

int PartGui::VertexPrimitive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractPrimitive::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui13DlgPrimitivesE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::DlgPrimitives::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui13DlgPrimitivesE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::DlgPrimitives"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DlgPrimitives, qt_meta_tag_ZN7PartGui13DlgPrimitivesE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::DlgPrimitives::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui13DlgPrimitivesE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui13DlgPrimitivesE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui13DlgPrimitivesE_t>.metaTypes,
    nullptr
} };

void PartGui::DlgPrimitives::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DlgPrimitives *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::DlgPrimitives::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::DlgPrimitives::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui13DlgPrimitivesE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PartGui::DlgPrimitives::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui8LocationE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::Location::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui8LocationE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::Location"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Location, qt_meta_tag_ZN7PartGui8LocationE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::Location::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui8LocationE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui8LocationE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui8LocationE_t>.metaTypes,
    nullptr
} };

void PartGui::Location::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Location *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::Location::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::Location::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui8LocationE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PartGui::Location::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui14TaskPrimitivesE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::TaskPrimitives::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui14TaskPrimitivesE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::TaskPrimitives"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskPrimitives, qt_meta_tag_ZN7PartGui14TaskPrimitivesE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::TaskPrimitives::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14TaskPrimitivesE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14TaskPrimitivesE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui14TaskPrimitivesE_t>.metaTypes,
    nullptr
} };

void PartGui::TaskPrimitives::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskPrimitives *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::TaskPrimitives::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::TaskPrimitives::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui14TaskPrimitivesE_t>.strings))
        return static_cast<void*>(this);
    return Gui::TaskView::TaskDialog::qt_metacast(_clname);
}

int PartGui::TaskPrimitives::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskDialog::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN7PartGui18TaskPrimitivesEditE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::TaskPrimitivesEdit::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui18TaskPrimitivesEditE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::TaskPrimitivesEdit"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskPrimitivesEdit, qt_meta_tag_ZN7PartGui18TaskPrimitivesEditE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::TaskPrimitivesEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui18TaskPrimitivesEditE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui18TaskPrimitivesEditE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui18TaskPrimitivesEditE_t>.metaTypes,
    nullptr
} };

void PartGui::TaskPrimitivesEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskPrimitivesEdit *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PartGui::TaskPrimitivesEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::TaskPrimitivesEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui18TaskPrimitivesEditE_t>.strings))
        return static_cast<void*>(this);
    return Gui::TaskView::TaskDialog::qt_metacast(_clname);
}

int PartGui::TaskPrimitivesEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskDialog::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
