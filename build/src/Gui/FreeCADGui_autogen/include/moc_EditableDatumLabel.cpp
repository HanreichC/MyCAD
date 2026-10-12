/****************************************************************************
** Meta object code from reading C++ file 'EditableDatumLabel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/EditableDatumLabel.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditableDatumLabel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui18EditableDatumLabelE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::EditableDatumLabel::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui18EditableDatumLabelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::EditableDatumLabel",
        "valueChanged",
        "",
        "val",
        "editingFinished",
        "editingCanceled",
        "parameterUnset",
        "finishEditingOnAllOVPs",
        "clicked",
        "EditableDatumLabel*",
        "label",
        "rightClicked",
        "QPoint",
        "globalPos",
        "editFinished",
        "value",
        "focusLost",
        "focusGained"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'valueChanged'
        QtMocHelpers::SignalData<void(double)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Signal 'editingFinished'
        QtMocHelpers::SignalData<void(double)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Signal 'editingCanceled'
        QtMocHelpers::SignalData<void(double)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Signal 'parameterUnset'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'finishEditingOnAllOVPs'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'clicked'
        QtMocHelpers::SignalData<void(EditableDatumLabel *)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'rightClicked'
        QtMocHelpers::SignalData<void(EditableDatumLabel *, const QPoint &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 }, { 0x80000000 | 12, 13 },
        }}),
        // Signal 'editFinished'
        QtMocHelpers::SignalData<void(double)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 15 },
        }}),
        // Signal 'focusLost'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'focusGained'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<EditableDatumLabel, qt_meta_tag_ZN3Gui18EditableDatumLabelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::EditableDatumLabel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui18EditableDatumLabelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui18EditableDatumLabelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui18EditableDatumLabelE_t>.metaTypes,
    nullptr
} };

void Gui::EditableDatumLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EditableDatumLabel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->editingFinished((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->editingCanceled((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->parameterUnset(); break;
        case 4: _t->finishEditingOnAllOVPs(); break;
        case 5: _t->clicked((*reinterpret_cast<std::add_pointer_t<EditableDatumLabel*>>(_a[1]))); break;
        case 6: _t->rightClicked((*reinterpret_cast<std::add_pointer_t<EditableDatumLabel*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QPoint>>(_a[2]))); break;
        case 7: _t->editFinished((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 8: _t->focusLost(); break;
        case 9: _t->focusGained(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< EditableDatumLabel* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< EditableDatumLabel* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)(double )>(_a, &EditableDatumLabel::valueChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)(double )>(_a, &EditableDatumLabel::editingFinished, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)(double )>(_a, &EditableDatumLabel::editingCanceled, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)()>(_a, &EditableDatumLabel::parameterUnset, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)()>(_a, &EditableDatumLabel::finishEditingOnAllOVPs, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)(EditableDatumLabel * )>(_a, &EditableDatumLabel::clicked, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)(EditableDatumLabel * , const QPoint & )>(_a, &EditableDatumLabel::rightClicked, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)(double )>(_a, &EditableDatumLabel::editFinished, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)()>(_a, &EditableDatumLabel::focusLost, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditableDatumLabel::*)()>(_a, &EditableDatumLabel::focusGained, 9))
            return;
    }
}

const QMetaObject *Gui::EditableDatumLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::EditableDatumLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui18EditableDatumLabelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Gui::EditableDatumLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Gui::EditableDatumLabel::valueChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Gui::EditableDatumLabel::editingFinished(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Gui::EditableDatumLabel::editingCanceled(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Gui::EditableDatumLabel::parameterUnset()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Gui::EditableDatumLabel::finishEditingOnAllOVPs()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Gui::EditableDatumLabel::clicked(EditableDatumLabel * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void Gui::EditableDatumLabel::rightClicked(EditableDatumLabel * _t1, const QPoint & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void Gui::EditableDatumLabel::editFinished(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void Gui::EditableDatumLabel::focusLost()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Gui::EditableDatumLabel::focusGained()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
