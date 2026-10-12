/****************************************************************************
** Meta object code from reading C++ file 'QuantitySpinBox.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/QuantitySpinBox.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QuantitySpinBox.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui15QuantitySpinBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::QuantitySpinBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui15QuantitySpinBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::QuantitySpinBox",
        "valueChanged",
        "",
        "Base::Quantity",
        "textChanged",
        "showFormulaDialog",
        "returnPressed",
        "inputCleared",
        "inputRejected",
        "message",
        "errorStartUtf16",
        "errorLengthUtf16",
        "setValue",
        "val",
        "userInput",
        "text",
        "handlePendingEmit",
        "updateUnit",
        "unit",
        "minimum",
        "maximum",
        "singleStep",
        "rawValue",
        "decimals",
        "value",
        "binding",
        "expression",
        "autoNormalize",
        "autoAdjustWidth",
        "addIconSpace",
        "maxExpectedDigits"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'valueChanged'
        QtMocHelpers::SignalData<void(const Base::Quantity &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Signal 'valueChanged'
        QtMocHelpers::SignalData<void(double)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 2 },
        }}),
        // Signal 'textChanged'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'showFormulaDialog'
        QtMocHelpers::SignalData<void(bool)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Signal 'returnPressed'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'inputCleared'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'inputRejected'
        QtMocHelpers::SignalData<void(const QString &, int, int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 }, { QMetaType::Int, 10 }, { QMetaType::Int, 11 },
        }}),
        // Slot 'setValue'
        QtMocHelpers::SlotData<void(const Base::Quantity &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 13 },
        }}),
        // Slot 'setValue'
        QtMocHelpers::SlotData<void(double)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 2 },
        }}),
        // Slot 'userInput'
        QtMocHelpers::SlotData<void(const QString &)>(14, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'handlePendingEmit'
        QtMocHelpers::SlotData<void(bool)>(16, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::Bool, 17 },
        }}),
        // Slot 'handlePendingEmit'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessProtected | QMC::MethodCloned, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'unit'
        QtMocHelpers::PropertyData<QString>(18, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'minimum'
        QtMocHelpers::PropertyData<double>(19, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'maximum'
        QtMocHelpers::PropertyData<double>(20, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'singleStep'
        QtMocHelpers::PropertyData<double>(21, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'rawValue'
        QtMocHelpers::PropertyData<double>(22, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable, 0),
        // property 'decimals'
        QtMocHelpers::PropertyData<double>(23, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'value'
        QtMocHelpers::PropertyData<Base::Quantity>(24, 0x80000000 | 3, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::User, 0),
        // property 'binding'
        QtMocHelpers::PropertyData<QString>(25, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'expression'
        QtMocHelpers::PropertyData<QString>(26, QMetaType::QString, QMC::DefaultPropertyFlags),
        // property 'autoNormalize'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoAdjustWidth'
        QtMocHelpers::PropertyData<bool>(28, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'addIconSpace'
        QtMocHelpers::PropertyData<bool>(29, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'maxExpectedDigits'
        QtMocHelpers::PropertyData<int>(30, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<QuantitySpinBox, qt_meta_tag_ZN3Gui15QuantitySpinBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::QuantitySpinBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractSpinBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15QuantitySpinBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15QuantitySpinBoxE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui15QuantitySpinBoxE_t>.metaTypes,
    nullptr
} };

void Gui::QuantitySpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QuantitySpinBox *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast<std::add_pointer_t<Base::Quantity>>(_a[1]))); break;
        case 1: _t->valueChanged((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->textChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->showFormulaDialog((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->returnPressed(); break;
        case 5: _t->inputCleared(); break;
        case 6: _t->inputRejected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 7: _t->setValue((*reinterpret_cast<std::add_pointer_t<Base::Quantity>>(_a[1]))); break;
        case 8: _t->setValue((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 9: _t->userInput((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->handlePendingEmit((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->handlePendingEmit(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Base::Quantity >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Base::Quantity >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (QuantitySpinBox::*)(const Base::Quantity & )>(_a, &QuantitySpinBox::valueChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (QuantitySpinBox::*)(double )>(_a, &QuantitySpinBox::valueChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (QuantitySpinBox::*)(const QString & )>(_a, &QuantitySpinBox::textChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (QuantitySpinBox::*)(bool )>(_a, &QuantitySpinBox::showFormulaDialog, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (QuantitySpinBox::*)()>(_a, &QuantitySpinBox::returnPressed, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (QuantitySpinBox::*)()>(_a, &QuantitySpinBox::inputCleared, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (QuantitySpinBox::*)(const QString & , int , int )>(_a, &QuantitySpinBox::inputRejected, 6))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Base::Quantity >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->unitText(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->minimum(); break;
        case 2: *reinterpret_cast<double*>(_v) = _t->maximum(); break;
        case 3: *reinterpret_cast<double*>(_v) = _t->singleStep(); break;
        case 4: *reinterpret_cast<double*>(_v) = _t->rawValue(); break;
        case 5: *reinterpret_cast<double*>(_v) = _t->decimals(); break;
        case 6: *reinterpret_cast<Base::Quantity*>(_v) = _t->value(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->boundToName(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->expressionText(); break;
        case 9: *reinterpret_cast<bool*>(_v) = _t->autoNormalize(); break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->autoAdjustWidth(); break;
        case 11: *reinterpret_cast<bool*>(_v) = _t->isIconSpaceAdded(); break;
        case 12: *reinterpret_cast<int*>(_v) = _t->getMaxExpectedDigits(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setUnitText(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setMinimum(*reinterpret_cast<double*>(_v)); break;
        case 2: _t->setMaximum(*reinterpret_cast<double*>(_v)); break;
        case 3: _t->setSingleStep(*reinterpret_cast<double*>(_v)); break;
        case 4: _t->setValue(*reinterpret_cast<double*>(_v)); break;
        case 5: _t->setDecimals(*reinterpret_cast<double*>(_v)); break;
        case 6: _t->setValue(*reinterpret_cast<Base::Quantity*>(_v)); break;
        case 7: _t->setBoundToByName(*reinterpret_cast<QString*>(_v)); break;
        case 9: _t->setAutoNormalize(*reinterpret_cast<bool*>(_v)); break;
        case 10: _t->setAutoAdjustWidth(*reinterpret_cast<bool*>(_v)); break;
        case 11: _t->addIconSpace(*reinterpret_cast<bool*>(_v)); break;
        case 12: _t->setMaxExpectedDigits(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::QuantitySpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::QuantitySpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15QuantitySpinBoxE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ExpressionSpinBox"))
        return static_cast< ExpressionSpinBox*>(this);
    return QAbstractSpinBox::qt_metacast(_clname);
}

int Gui::QuantitySpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Gui::QuantitySpinBox::valueChanged(const Base::Quantity & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Gui::QuantitySpinBox::valueChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Gui::QuantitySpinBox::textChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Gui::QuantitySpinBox::showFormulaDialog(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Gui::QuantitySpinBox::returnPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Gui::QuantitySpinBox::inputCleared()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Gui::QuantitySpinBox::inputRejected(const QString & _t1, int _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP
