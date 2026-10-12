/****************************************************************************
** Meta object code from reading C++ file 'QuarterWidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/Gui/Quarter/QuarterWidget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QuarterWidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3SIM6Coin3D7Quarter13QuarterWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto SIM::Coin3D::Quarter::QuarterWidget::qt_create_metaobjectdata<qt_meta_tag_ZN3SIM6Coin3D7Quarter13QuarterWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SIM::Coin3D::Quarter::QuarterWidget",
        "devicePixelRatioChanged",
        "",
        "dev_pixel_ratio",
        "viewAll",
        "seek",
        "redraw",
        "setRenderMode",
        "SIM::Coin3D::Quarter::QuarterWidget::RenderMode",
        "mode",
        "setStereoMode",
        "SIM::Coin3D::Quarter::QuarterWidget::StereoMode",
        "setTransparencyType",
        "SIM::Coin3D::Quarter::QuarterWidget::TransparencyType",
        "type",
        "replaceViewport",
        "navigationModeFile",
        "QUrl",
        "backgroundColor",
        "QColor",
        "contextMenuEnabled",
        "headlightEnabled",
        "clearZBuffer",
        "clearWindow",
        "interactionModeEnabled",
        "interactionModeOn",
        "transparencyType",
        "TransparencyType",
        "renderMode",
        "RenderMode",
        "stereoMode",
        "StereoMode",
        "maxFrameRate",
        "devicePixelRatio",
        "SCREEN_DOOR",
        "ADD",
        "DELAYED_ADD",
        "SORTED_OBJECT_ADD",
        "BLEND",
        "DELAYED_BLEND",
        "SORTED_OBJECT_BLEND",
        "SORTED_OBJECT_SORTED_TRIANGLE_ADD",
        "SORTED_OBJECT_SORTED_TRIANGLE_BLEND",
        "NONE",
        "SORTED_LAYERS_BLEND",
        "AS_IS",
        "WIREFRAME",
        "WIREFRAME_OVERLAY",
        "POINTS",
        "HIDDEN_LINE",
        "BOUNDING_BOX",
        "MONO",
        "ANAGLYPH",
        "QUAD_BUFFER",
        "INTERLEAVED_ROWS",
        "INTERLEAVED_COLUMNS"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'devicePixelRatioChanged'
        QtMocHelpers::SignalData<void(qreal)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QReal, 3 },
        }}),
        // Slot 'viewAll'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'seek'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'redraw'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setRenderMode'
        QtMocHelpers::SlotData<void(SIM::Coin3D::Quarter::QuarterWidget::RenderMode)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'setStereoMode'
        QtMocHelpers::SlotData<void(SIM::Coin3D::Quarter::QuarterWidget::StereoMode)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 9 },
        }}),
        // Slot 'setTransparencyType'
        QtMocHelpers::SlotData<void(SIM::Coin3D::Quarter::QuarterWidget::TransparencyType)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 13, 14 },
        }}),
        // Slot 'replaceViewport'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'navigationModeFile'
        QtMocHelpers::PropertyData<QUrl>(16, 0x80000000 | 17, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Resettable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'backgroundColor'
        QtMocHelpers::PropertyData<QColor>(18, 0x80000000 | 19, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'contextMenuEnabled'
        QtMocHelpers::PropertyData<bool>(20, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'headlightEnabled'
        QtMocHelpers::PropertyData<bool>(21, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'clearZBuffer'
        QtMocHelpers::PropertyData<bool>(22, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'clearWindow'
        QtMocHelpers::PropertyData<bool>(23, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'interactionModeEnabled'
        QtMocHelpers::PropertyData<bool>(24, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'interactionModeOn'
        QtMocHelpers::PropertyData<bool>(25, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'transparencyType'
        QtMocHelpers::PropertyData<enum TransparencyType>(26, 0x80000000 | 27, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'renderMode'
        QtMocHelpers::PropertyData<enum RenderMode>(28, 0x80000000 | 29, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'stereoMode'
        QtMocHelpers::PropertyData<enum StereoMode>(30, 0x80000000 | 31, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'maxFrameRate'
        QtMocHelpers::PropertyData<int>(32, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'devicePixelRatio'
        QtMocHelpers::PropertyData<qreal>(33, QMetaType::QReal, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'TransparencyType'
        QtMocHelpers::EnumData<enum TransparencyType>(27, 27, QMC::EnumFlags{}).add({
            {   34, TransparencyType::SCREEN_DOOR },
            {   35, TransparencyType::ADD },
            {   36, TransparencyType::DELAYED_ADD },
            {   37, TransparencyType::SORTED_OBJECT_ADD },
            {   38, TransparencyType::BLEND },
            {   39, TransparencyType::DELAYED_BLEND },
            {   40, TransparencyType::SORTED_OBJECT_BLEND },
            {   41, TransparencyType::SORTED_OBJECT_SORTED_TRIANGLE_ADD },
            {   42, TransparencyType::SORTED_OBJECT_SORTED_TRIANGLE_BLEND },
            {   43, TransparencyType::NONE },
            {   44, TransparencyType::SORTED_LAYERS_BLEND },
        }),
        // enum 'RenderMode'
        QtMocHelpers::EnumData<enum RenderMode>(29, 29, QMC::EnumFlags{}).add({
            {   45, RenderMode::AS_IS },
            {   46, RenderMode::WIREFRAME },
            {   47, RenderMode::WIREFRAME_OVERLAY },
            {   48, RenderMode::POINTS },
            {   49, RenderMode::HIDDEN_LINE },
            {   50, RenderMode::BOUNDING_BOX },
        }),
        // enum 'StereoMode'
        QtMocHelpers::EnumData<enum StereoMode>(31, 31, QMC::EnumFlags{}).add({
            {   51, StereoMode::MONO },
            {   52, StereoMode::ANAGLYPH },
            {   53, StereoMode::QUAD_BUFFER },
            {   54, StereoMode::INTERLEAVED_ROWS },
            {   55, StereoMode::INTERLEAVED_COLUMNS },
        }),
    };
    return QtMocHelpers::metaObjectData<QuarterWidget, qt_meta_tag_ZN3SIM6Coin3D7Quarter13QuarterWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SIM::Coin3D::Quarter::QuarterWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3SIM6Coin3D7Quarter13QuarterWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3SIM6Coin3D7Quarter13QuarterWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3SIM6Coin3D7Quarter13QuarterWidgetE_t>.metaTypes,
    nullptr
} };

void SIM::Coin3D::Quarter::QuarterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QuarterWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->devicePixelRatioChanged((*reinterpret_cast<std::add_pointer_t<qreal>>(_a[1]))); break;
        case 1: _t->viewAll(); break;
        case 2: _t->seek(); break;
        case 3: _t->redraw(); break;
        case 4: _t->setRenderMode((*reinterpret_cast<std::add_pointer_t<SIM::Coin3D::Quarter::QuarterWidget::RenderMode>>(_a[1]))); break;
        case 5: _t->setStereoMode((*reinterpret_cast<std::add_pointer_t<SIM::Coin3D::Quarter::QuarterWidget::StereoMode>>(_a[1]))); break;
        case 6: _t->setTransparencyType((*reinterpret_cast<std::add_pointer_t<SIM::Coin3D::Quarter::QuarterWidget::TransparencyType>>(_a[1]))); break;
        case 7: _t->replaceViewport(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (QuarterWidget::*)(qreal )>(_a, &QuarterWidget::devicePixelRatioChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QUrl*>(_v) = _t->navigationModeFile(); break;
        case 1: *reinterpret_cast<QColor*>(_v) = _t->backgroundColor(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->contextMenuEnabled(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->headlightEnabled(); break;
        case 4: *reinterpret_cast<bool*>(_v) = _t->clearZBuffer(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->clearWindow(); break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->interactionModeEnabled(); break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->interactionModeOn(); break;
        case 8: *reinterpret_cast<enum TransparencyType*>(_v) = _t->transparencyType(); break;
        case 9: *reinterpret_cast<enum RenderMode*>(_v) = _t->renderMode(); break;
        case 10: *reinterpret_cast<enum StereoMode*>(_v) = _t->stereoMode(); break;
        case 11: *reinterpret_cast<int*>(_v) = _t->maxFrameRate(); break;
        case 12: *reinterpret_cast<qreal*>(_v) = _t->devicePixelRatio(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setNavigationModeFile(*reinterpret_cast<QUrl*>(_v)); break;
        case 1: _t->setBackgroundColor(*reinterpret_cast<QColor*>(_v)); break;
        case 2: _t->setContextMenuEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 3: _t->setHeadlightEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setClearZBuffer(*reinterpret_cast<bool*>(_v)); break;
        case 5: _t->setClearWindow(*reinterpret_cast<bool*>(_v)); break;
        case 6: _t->setInteractionModeEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 7: _t->setInteractionModeOn(*reinterpret_cast<bool*>(_v)); break;
        case 8: _t->setTransparencyType(*reinterpret_cast<enum TransparencyType*>(_v)); break;
        case 9: _t->setRenderMode(*reinterpret_cast<enum RenderMode*>(_v)); break;
        case 10: _t->setStereoMode(*reinterpret_cast<enum StereoMode*>(_v)); break;
        case 11: _t->setMaxFrameRate(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
    if (_c == QMetaObject::ResetProperty) {
        switch (_id) {
        case 0: _t->resetNavigationModeFile(); break;
        default: break;
        }
    }
}

const QMetaObject *SIM::Coin3D::Quarter::QuarterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SIM::Coin3D::Quarter::QuarterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3SIM6Coin3D7Quarter13QuarterWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int SIM::Coin3D::Quarter::QuarterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
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
void SIM::Coin3D::Quarter::QuarterWidget::devicePixelRatioChanged(qreal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
QT_WARNING_POP
