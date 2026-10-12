/****************************************************************************
** Meta object code from reading C++ file 'PropertyEditorMesh.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/Mesh/Gui/PropertyEditorMesh.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertyEditorMesh.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7MeshGui22PropertyMeshKernelItemE_t {};
} // unnamed namespace

template <> constexpr inline auto MeshGui::PropertyMeshKernelItem::qt_create_metaobjectdata<qt_meta_tag_ZN7MeshGui22PropertyMeshKernelItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MeshGui::PropertyMeshKernelItem",
        "Points",
        "Edges",
        "Faces"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'Points'
        QtMocHelpers::PropertyData<int>(1, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'Edges'
        QtMocHelpers::PropertyData<int>(2, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'Faces'
        QtMocHelpers::PropertyData<int>(3, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PropertyMeshKernelItem, qt_meta_tag_ZN7MeshGui22PropertyMeshKernelItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MeshGui::PropertyMeshKernelItem::staticMetaObject = { {
    QMetaObject::SuperData::link<Gui::PropertyEditor::PropertyItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7MeshGui22PropertyMeshKernelItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7MeshGui22PropertyMeshKernelItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7MeshGui22PropertyMeshKernelItemE_t>.metaTypes,
    nullptr
} };

void MeshGui::PropertyMeshKernelItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PropertyMeshKernelItem *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->countPoints(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->countEdges(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->countFaces(); break;
        default: break;
        }
    }
}

const QMetaObject *MeshGui::PropertyMeshKernelItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeshGui::PropertyMeshKernelItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7MeshGui22PropertyMeshKernelItemE_t>.strings))
        return static_cast<void*>(this);
    return Gui::PropertyEditor::PropertyItem::qt_metacast(_clname);
}

int MeshGui::PropertyMeshKernelItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Gui::PropertyEditor::PropertyItem::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
