/****************************************************************************
** Meta object code from reading C++ file 'ShortcutManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/ShortcutManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShortcutManager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui15ShortcutManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::ShortcutManager::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui15ShortcutManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::ShortcutManager",
        "shortcutChanged",
        "",
        "const char*",
        "name",
        "QKeySequence",
        "oldShortcut",
        "actionShortcutChanged",
        "QAction*",
        "priorityChanged",
        "priority"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'shortcutChanged'
        QtMocHelpers::SignalData<void(const char *, const QKeySequence &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'actionShortcutChanged'
        QtMocHelpers::SignalData<void(QAction *, const QKeySequence &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 2 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'priorityChanged'
        QtMocHelpers::SignalData<void(const char *, int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::Int, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ShortcutManager, qt_meta_tag_ZN3Gui15ShortcutManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::ShortcutManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15ShortcutManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15ShortcutManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui15ShortcutManagerE_t>.metaTypes,
    nullptr
} };

void Gui::ShortcutManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ShortcutManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->shortcutChanged((*reinterpret_cast<std::add_pointer_t<const char*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QKeySequence>>(_a[2]))); break;
        case 1: _t->actionShortcutChanged((*reinterpret_cast<std::add_pointer_t<QAction*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QKeySequence>>(_a[2]))); break;
        case 2: _t->priorityChanged((*reinterpret_cast<std::add_pointer_t<const char*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ShortcutManager::*)(const char * , const QKeySequence & )>(_a, &ShortcutManager::shortcutChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShortcutManager::*)(QAction * , const QKeySequence & )>(_a, &ShortcutManager::actionShortcutChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShortcutManager::*)(const char * , int )>(_a, &ShortcutManager::priorityChanged, 2))
            return;
    }
}

const QMetaObject *Gui::ShortcutManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::ShortcutManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15ShortcutManagerE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ParameterGrp::ObserverType"))
        return static_cast< ParameterGrp::ObserverType*>(this);
    return QObject::qt_metacast(_clname);
}

int Gui::ShortcutManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Gui::ShortcutManager::shortcutChanged(const char * _t1, const QKeySequence & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void Gui::ShortcutManager::actionShortcutChanged(QAction * _t1, const QKeySequence & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void Gui::ShortcutManager::priorityChanged(const char * _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}
QT_WARNING_POP
