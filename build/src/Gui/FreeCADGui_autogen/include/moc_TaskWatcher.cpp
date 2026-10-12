/****************************************************************************
** Meta object code from reading C++ file 'TaskWatcher.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/TaskView/TaskWatcher.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskWatcher.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui8TaskView11TaskWatcherE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TaskView::TaskWatcher::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui8TaskView11TaskWatcherE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TaskView::TaskWatcher"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskWatcher, qt_meta_tag_ZN3Gui8TaskView11TaskWatcherE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TaskView::TaskWatcher::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView11TaskWatcherE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView11TaskWatcherE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui8TaskView11TaskWatcherE_t>.metaTypes,
    nullptr
} };

void Gui::TaskView::TaskWatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskWatcher *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::TaskView::TaskWatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TaskView::TaskWatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView11TaskWatcherE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Gui::SelectionFilter"))
        return static_cast< Gui::SelectionFilter*>(this);
    return QObject::qt_metacast(_clname);
}

int Gui::TaskView::TaskWatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui8TaskView19TaskWatcherCommandsE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TaskView::TaskWatcherCommands::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui8TaskView19TaskWatcherCommandsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TaskView::TaskWatcherCommands"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskWatcherCommands, qt_meta_tag_ZN3Gui8TaskView19TaskWatcherCommandsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TaskView::TaskWatcherCommands::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskWatcher::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView19TaskWatcherCommandsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView19TaskWatcherCommandsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui8TaskView19TaskWatcherCommandsE_t>.metaTypes,
    nullptr
} };

void Gui::TaskView::TaskWatcherCommands::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskWatcherCommands *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::TaskView::TaskWatcherCommands::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TaskView::TaskWatcherCommands::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView19TaskWatcherCommandsE_t>.strings))
        return static_cast<void*>(this);
    return TaskWatcher::qt_metacast(_clname);
}

int Gui::TaskView::TaskWatcherCommands::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskWatcher::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui8TaskView27TaskWatcherCommandsEmptyDocE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TaskView::TaskWatcherCommandsEmptyDoc::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui8TaskView27TaskWatcherCommandsEmptyDocE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TaskView::TaskWatcherCommandsEmptyDoc"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskWatcherCommandsEmptyDoc, qt_meta_tag_ZN3Gui8TaskView27TaskWatcherCommandsEmptyDocE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TaskView::TaskWatcherCommandsEmptyDoc::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskWatcherCommands::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView27TaskWatcherCommandsEmptyDocE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView27TaskWatcherCommandsEmptyDocE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui8TaskView27TaskWatcherCommandsEmptyDocE_t>.metaTypes,
    nullptr
} };

void Gui::TaskView::TaskWatcherCommandsEmptyDoc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskWatcherCommandsEmptyDoc *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::TaskView::TaskWatcherCommandsEmptyDoc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TaskView::TaskWatcherCommandsEmptyDoc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView27TaskWatcherCommandsEmptyDocE_t>.strings))
        return static_cast<void*>(this);
    return TaskWatcherCommands::qt_metacast(_clname);
}

int Gui::TaskView::TaskWatcherCommandsEmptyDoc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskWatcherCommands::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui8TaskView33TaskWatcherCommandsEmptySelectionE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TaskView::TaskWatcherCommandsEmptySelection::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui8TaskView33TaskWatcherCommandsEmptySelectionE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TaskView::TaskWatcherCommandsEmptySelection"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskWatcherCommandsEmptySelection, qt_meta_tag_ZN3Gui8TaskView33TaskWatcherCommandsEmptySelectionE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TaskView::TaskWatcherCommandsEmptySelection::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskWatcherCommands::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView33TaskWatcherCommandsEmptySelectionE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView33TaskWatcherCommandsEmptySelectionE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui8TaskView33TaskWatcherCommandsEmptySelectionE_t>.metaTypes,
    nullptr
} };

void Gui::TaskView::TaskWatcherCommandsEmptySelection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskWatcherCommandsEmptySelection *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::TaskView::TaskWatcherCommandsEmptySelection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TaskView::TaskWatcherCommandsEmptySelection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView33TaskWatcherCommandsEmptySelectionE_t>.strings))
        return static_cast<void*>(this);
    return TaskWatcherCommands::qt_metacast(_clname);
}

int Gui::TaskView::TaskWatcherCommandsEmptySelection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskWatcherCommands::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
