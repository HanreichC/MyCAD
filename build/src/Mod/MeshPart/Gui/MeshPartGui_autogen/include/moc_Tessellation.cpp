/****************************************************************************
** Meta object code from reading C++ file 'Tessellation.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/MeshPart/Gui/Tessellation.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Tessellation.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11MeshPartGui14Mesh2ShapeGmshE_t {};
} // unnamed namespace

template <> constexpr inline auto MeshPartGui::Mesh2ShapeGmsh::qt_create_metaobjectdata<qt_meta_tag_ZN11MeshPartGui14Mesh2ShapeGmshE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MeshPartGui::Mesh2ShapeGmsh",
        "processed",
        ""
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'processed'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Mesh2ShapeGmsh, qt_meta_tag_ZN11MeshPartGui14Mesh2ShapeGmshE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MeshPartGui::Mesh2ShapeGmsh::staticMetaObject = { {
    QMetaObject::SuperData::link<MeshGui::GmshWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MeshPartGui14Mesh2ShapeGmshE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MeshPartGui14Mesh2ShapeGmshE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11MeshPartGui14Mesh2ShapeGmshE_t>.metaTypes,
    nullptr
} };

void MeshPartGui::Mesh2ShapeGmsh::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Mesh2ShapeGmsh *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->processed(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Mesh2ShapeGmsh::*)()>(_a, &Mesh2ShapeGmsh::processed, 0))
            return;
    }
}

const QMetaObject *MeshPartGui::Mesh2ShapeGmsh::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeshPartGui::Mesh2ShapeGmsh::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MeshPartGui14Mesh2ShapeGmshE_t>.strings))
        return static_cast<void*>(this);
    return MeshGui::GmshWidget::qt_metacast(_clname);
}

int MeshPartGui::Mesh2ShapeGmsh::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MeshGui::GmshWidget::qt_metacall(_c, _id, _a);
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
void MeshPartGui::Mesh2ShapeGmsh::processed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN11MeshPartGui12TessellationE_t {};
} // unnamed namespace

template <> constexpr inline auto MeshPartGui::Tessellation::qt_create_metaobjectdata<qt_meta_tag_ZN11MeshPartGui12TessellationE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MeshPartGui::Tessellation"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Tessellation, qt_meta_tag_ZN11MeshPartGui12TessellationE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MeshPartGui::Tessellation::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MeshPartGui12TessellationE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MeshPartGui12TessellationE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11MeshPartGui12TessellationE_t>.metaTypes,
    nullptr
} };

void MeshPartGui::Tessellation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Tessellation *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *MeshPartGui::Tessellation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeshPartGui::Tessellation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MeshPartGui12TessellationE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MeshPartGui::Tessellation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN11MeshPartGui16TaskTessellationE_t {};
} // unnamed namespace

template <> constexpr inline auto MeshPartGui::TaskTessellation::qt_create_metaobjectdata<qt_meta_tag_ZN11MeshPartGui16TaskTessellationE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MeshPartGui::TaskTessellation"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskTessellation, qt_meta_tag_ZN11MeshPartGui16TaskTessellationE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MeshPartGui::TaskTessellation::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::TaskView::TaskDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MeshPartGui16TaskTessellationE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MeshPartGui16TaskTessellationE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11MeshPartGui16TaskTessellationE_t>.metaTypes,
    nullptr
} };

void MeshPartGui::TaskTessellation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskTessellation *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *MeshPartGui::TaskTessellation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeshPartGui::TaskTessellation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MeshPartGui16TaskTessellationE_t>.strings))
        return static_cast<void*>(this);
    return Gui::TaskView::TaskDialog::qt_metacast(_clname);
}

int MeshPartGui::TaskTessellation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::TaskView::TaskDialog::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
