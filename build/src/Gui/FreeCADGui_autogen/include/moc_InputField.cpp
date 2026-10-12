/****************************************************************************
** Meta object code from reading C++ file 'InputField.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/InputField.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InputField.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui10InputFieldE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::InputField::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui10InputFieldE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::InputField",
        "valueChanged",
        "",
        "Base::Quantity",
        "parseError",
        "errorText",
        "newInput",
        "text",
        "updateIconLabel",
        "prefPath",
        "singleStep",
        "maximum",
        "minimum",
        "rawValue",
        "historySize",
        "unit",
        "precision",
        "format",
        "quantity",
        "quantityString",
        "rawText"
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
        // Signal 'parseError'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'newInput'
        QtMocHelpers::SlotData<void(const QString &)>(6, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Slot 'updateIconLabel'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(9, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'singleStep'
        QtMocHelpers::PropertyData<double>(10, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'maximum'
        QtMocHelpers::PropertyData<double>(11, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'minimum'
        QtMocHelpers::PropertyData<double>(12, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'rawValue'
        QtMocHelpers::PropertyData<double>(13, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable, 0),
        // property 'historySize'
        QtMocHelpers::PropertyData<int>(14, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'unit'
        QtMocHelpers::PropertyData<QString>(15, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'precision'
        QtMocHelpers::PropertyData<int>(16, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'format'
        QtMocHelpers::PropertyData<QString>(17, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'quantity'
        QtMocHelpers::PropertyData<Base::Quantity>(18, 0x80000000 | 3, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag, 0),
        // property 'quantityString'
        QtMocHelpers::PropertyData<QString>(19, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'rawText'
        QtMocHelpers::PropertyData<QString>(20, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InputField, qt_meta_tag_ZN3Gui10InputFieldE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::InputField::staticMetaObject = { {
    QMetaObject::SuperData::link<ExpressionLineEdit::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10InputFieldE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10InputFieldE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui10InputFieldE_t>.metaTypes,
    nullptr
} };

void Gui::InputField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<InputField *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast<std::add_pointer_t<Base::Quantity>>(_a[1]))); break;
        case 1: _t->valueChanged((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->parseError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->newInput((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->updateIconLabel((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
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
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (InputField::*)(const Base::Quantity & )>(_a, &InputField::valueChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (InputField::*)(double )>(_a, &InputField::valueChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (InputField::*)(const QString & )>(_a, &InputField::parseError, 2))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Base::Quantity >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->singleStep(); break;
        case 2: *reinterpret_cast<double*>(_v) = _t->maximum(); break;
        case 3: *reinterpret_cast<double*>(_v) = _t->minimum(); break;
        case 4: *reinterpret_cast<double*>(_v) = _t->rawValue(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->historySize(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->getUnitText(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->getPrecision(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->getFormat(); break;
        case 9: *reinterpret_cast<Base::Quantity*>(_v) = _t->getQuantity(); break;
        case 10: *reinterpret_cast<QString*>(_v) = _t->getQuantityString(); break;
        case 11: *reinterpret_cast<QString*>(_v) = _t->rawText(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setSingleStep(*reinterpret_cast<double*>(_v)); break;
        case 2: _t->setMaximum(*reinterpret_cast<double*>(_v)); break;
        case 3: _t->setMinimum(*reinterpret_cast<double*>(_v)); break;
        case 4: _t->setValue(*reinterpret_cast<double*>(_v)); break;
        case 5: _t->setHistorySize(*reinterpret_cast<int*>(_v)); break;
        case 6: _t->setUnitText(*reinterpret_cast<QString*>(_v)); break;
        case 7: _t->setPrecision(*reinterpret_cast<int*>(_v)); break;
        case 8: _t->setFormat(*reinterpret_cast<QString*>(_v)); break;
        case 9: _t->setValue(*reinterpret_cast<Base::Quantity*>(_v)); break;
        case 10: _t->setQuantityString(*reinterpret_cast<QString*>(_v)); break;
        case 11: _t->setRawText(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::InputField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::InputField::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10InputFieldE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ExpressionWidget"))
        return static_cast< ExpressionWidget*>(this);
    return ExpressionLineEdit::qt_metacast(_clname);
}

int Gui::InputField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ExpressionLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Gui::InputField::valueChanged(const Base::Quantity & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Gui::InputField::valueChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Gui::InputField::parseError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
