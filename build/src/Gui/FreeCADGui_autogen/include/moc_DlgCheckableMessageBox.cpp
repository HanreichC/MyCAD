/****************************************************************************
** Meta object code from reading C++ file 'DlgCheckableMessageBox.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/Dialogs/DlgCheckableMessageBox.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgCheckableMessageBox.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui6Dialog22DlgCheckableMessageBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::Dialog::DlgCheckableMessageBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui6Dialog22DlgCheckableMessageBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::Dialog::DlgCheckableMessageBox",
        "slotClicked",
        "",
        "QAbstractButton*",
        "b",
        "text",
        "iconPixmap",
        "QPixmap",
        "isChecked",
        "checkBoxText",
        "buttons",
        "QDialogButtonBox::StandardButtons",
        "defaultButton",
        "QDialogButtonBox::StandardButton"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'slotClicked'
        QtMocHelpers::SlotData<void(QAbstractButton *)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'text'
        QtMocHelpers::PropertyData<QString>(5, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'iconPixmap'
        QtMocHelpers::PropertyData<QPixmap>(6, 0x80000000 | 7, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'isChecked'
        QtMocHelpers::PropertyData<bool>(8, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'checkBoxText'
        QtMocHelpers::PropertyData<QString>(9, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'buttons'
        QtMocHelpers::PropertyData<QDialogButtonBox::StandardButtons>(10, 0x80000000 | 11, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag),
        // property 'defaultButton'
        QtMocHelpers::PropertyData<QDialogButtonBox::StandardButton>(12, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DlgCheckableMessageBox, qt_meta_tag_ZN3Gui6Dialog22DlgCheckableMessageBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_ZN3Gui6Dialog22DlgCheckableMessageBoxE[] = {
    QMetaObject::SuperData::link<QDialogButtonBox::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject Gui::Dialog::DlgCheckableMessageBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog22DlgCheckableMessageBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog22DlgCheckableMessageBoxE_t>.data,
    qt_static_metacall,
    qt_meta_extradata_ZN3Gui6Dialog22DlgCheckableMessageBoxE,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui6Dialog22DlgCheckableMessageBoxE_t>.metaTypes,
    nullptr
} };

void Gui::Dialog::DlgCheckableMessageBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DlgCheckableMessageBox *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->slotClicked((*reinterpret_cast<std::add_pointer_t<QAbstractButton*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->text(); break;
        case 1: *reinterpret_cast<QPixmap*>(_v) = _t->iconPixmap(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isChecked(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->checkBoxText(); break;
        case 4: *reinterpret_cast<QDialogButtonBox::StandardButtons*>(_v) = _t->standardButtons(); break;
        case 5: *reinterpret_cast<QDialogButtonBox::StandardButton*>(_v) = _t->defaultButton(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setIconPixmap(*reinterpret_cast<QPixmap*>(_v)); break;
        case 2: _t->setChecked(*reinterpret_cast<bool*>(_v)); break;
        case 3: _t->setCheckBoxText(*reinterpret_cast<QString*>(_v)); break;
        case 4: _t->setStandardButtons(*reinterpret_cast<QDialogButtonBox::StandardButtons*>(_v)); break;
        case 5: _t->setDefaultButton(*reinterpret_cast<QDialogButtonBox::StandardButton*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::Dialog::DlgCheckableMessageBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::Dialog::DlgCheckableMessageBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui6Dialog22DlgCheckableMessageBoxE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Gui::Dialog::DlgCheckableMessageBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
