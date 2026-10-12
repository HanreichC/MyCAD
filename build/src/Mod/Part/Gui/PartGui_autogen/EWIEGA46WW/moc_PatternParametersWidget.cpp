/****************************************************************************
** Meta object code from reading C++ file 'PatternParametersWidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../src/Mod/Part/Gui/PatternParametersWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PatternParametersWidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7PartGui23PatternParametersWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto PartGui::PatternParametersWidget::qt_create_metaobjectdata<qt_meta_tag_ZN7PartGui23PatternParametersWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PartGui::PatternParametersWidget",
        "onReversePressed",
        "",
        "onModeChanged",
        "index",
        "onLengthChanged",
        "value",
        "onOffsetChanged",
        "onOccurrencesChanged",
        "onGroupBoxToggled",
        "checked",
        "onEnableCheckBoxToggled",
        "onAddSpacingButtonClicked",
        "onDynamicSpacingChanged",
        "onRemoveSpacingButtonClicked",
        "QWidget*",
        "rowWidget",
        "onSpacingLabelClicked",
        "Gui::EditableDatumLabel*",
        "label",
        "onSpacingLabelRightClicked",
        "QPoint",
        "globalPos"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onReversePressed'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onModeChanged'
        QtMocHelpers::SlotData<void(int)>(3, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 4 },
        }}),
        // Slot 'onLengthChanged'
        QtMocHelpers::SlotData<void(double)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 6 },
        }}),
        // Slot 'onOffsetChanged'
        QtMocHelpers::SlotData<void(double)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 6 },
        }}),
        // Slot 'onOccurrencesChanged'
        QtMocHelpers::SlotData<void(unsigned int)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::UInt, 6 },
        }}),
        // Slot 'onGroupBoxToggled'
        QtMocHelpers::SlotData<void(bool)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 10 },
        }}),
        // Slot 'onEnableCheckBoxToggled'
        QtMocHelpers::SlotData<void(bool)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 10 },
        }}),
        // Slot 'onAddSpacingButtonClicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDynamicSpacingChanged'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRemoveSpacingButtonClicked'
        QtMocHelpers::SlotData<void(QWidget *)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Slot 'onSpacingLabelClicked'
        QtMocHelpers::SlotData<void(Gui::EditableDatumLabel *)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 18, 19 },
        }}),
        // Slot 'onSpacingLabelRightClicked'
        QtMocHelpers::SlotData<void(Gui::EditableDatumLabel *, const QPoint &)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 18, 19 }, { 0x80000000 | 21, 22 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PatternParametersWidget, qt_meta_tag_ZN7PartGui23PatternParametersWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PartGui::PatternParametersWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<PatternReferenceWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui23PatternParametersWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui23PatternParametersWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7PartGui23PatternParametersWidgetE_t>.metaTypes,
    nullptr
} };

void PartGui::PatternParametersWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PatternParametersWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onReversePressed(); break;
        case 1: _t->onModeChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->onLengthChanged((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->onOffsetChanged((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->onOccurrencesChanged((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 5: _t->onGroupBoxToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->onEnableCheckBoxToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->onAddSpacingButtonClicked(); break;
        case 8: _t->onDynamicSpacingChanged(); break;
        case 9: _t->onRemoveSpacingButtonClicked((*reinterpret_cast<std::add_pointer_t<QWidget*>>(_a[1]))); break;
        case 10: _t->onSpacingLabelClicked((*reinterpret_cast<std::add_pointer_t<Gui::EditableDatumLabel*>>(_a[1]))); break;
        case 11: _t->onSpacingLabelRightClicked((*reinterpret_cast<std::add_pointer_t<Gui::EditableDatumLabel*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QPoint>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Gui::EditableDatumLabel* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Gui::EditableDatumLabel* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *PartGui::PatternParametersWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PartGui::PatternParametersWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7PartGui23PatternParametersWidgetE_t>.strings))
        return static_cast<void*>(this);
    return PatternReferenceWidget::qt_metacast(_clname);
}

int PartGui::PatternParametersWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PatternReferenceWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_WARNING_POP
