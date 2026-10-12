/****************************************************************************
** Meta object code from reading C++ file 'TaskSelectLinkProperty.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/TaskView/TaskSelectLinkProperty.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskSelectLinkProperty.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui8TaskView22TaskSelectLinkPropertyE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::TaskView::TaskSelectLinkProperty::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui8TaskView22TaskSelectLinkPropertyE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::TaskView::TaskSelectLinkProperty",
        "emitSelectionFit",
        "",
        "emitSelectionMisfit"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'emitSelectionFit'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'emitSelectionMisfit'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TaskSelectLinkProperty, qt_meta_tag_ZN3Gui8TaskView22TaskSelectLinkPropertyE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::TaskView::TaskSelectLinkProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<TaskBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView22TaskSelectLinkPropertyE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView22TaskSelectLinkPropertyE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui8TaskView22TaskSelectLinkPropertyE_t>.metaTypes,
    nullptr
} };

void Gui::TaskView::TaskSelectLinkProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TaskSelectLinkProperty *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->emitSelectionFit(); break;
        case 1: _t->emitSelectionMisfit(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TaskSelectLinkProperty::*)()>(_a, &TaskSelectLinkProperty::emitSelectionFit, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TaskSelectLinkProperty::*)()>(_a, &TaskSelectLinkProperty::emitSelectionMisfit, 1))
            return;
    }
}

const QMetaObject *Gui::TaskView::TaskSelectLinkProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::TaskView::TaskSelectLinkProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui8TaskView22TaskSelectLinkPropertyE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Gui::SelectionSingleton::ObserverType"))
        return static_cast< Gui::SelectionSingleton::ObserverType*>(this);
    return TaskBox::qt_metacast(_clname);
}

int Gui::TaskView::TaskSelectLinkProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TaskBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Gui::TaskView::TaskSelectLinkProperty::emitSelectionFit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Gui::TaskView::TaskSelectLinkProperty::emitSelectionMisfit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
