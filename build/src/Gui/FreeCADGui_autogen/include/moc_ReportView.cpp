/****************************************************************************
** Meta object code from reading C++ file 'ReportView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/ReportView.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReportView.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui7DockWnd10ReportViewE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::DockWnd::ReportView::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui7DockWnd10ReportViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::DockWnd::ReportView"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ReportView, qt_meta_tag_ZN3Gui7DockWnd10ReportViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::DockWnd::ReportView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui7DockWnd10ReportViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui7DockWnd10ReportViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui7DockWnd10ReportViewE_t>.metaTypes,
    nullptr
} };

void Gui::DockWnd::ReportView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ReportView *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::DockWnd::ReportView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::DockWnd::ReportView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui7DockWnd10ReportViewE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Gui::DockWnd::ReportView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui7DockWnd12ReportOutputE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::DockWnd::ReportOutput::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui7DockWnd12ReportOutputE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::DockWnd::ReportOutput",
        "onSaveAs",
        "",
        "onToggleError",
        "onToggleWarning",
        "onToggleLogMessage",
        "onToggleNormalMessage",
        "onToggleCritical",
        "onToggleShowReportViewOnWarning",
        "onToggleShowReportViewOnError",
        "onToggleShowReportViewOnNormalMessage",
        "onToggleShowReportViewOnCritical",
        "onToggleShowReportViewOnLogMessage",
        "onToggleRedirectPythonStdout",
        "onToggleRedirectPythonStderr",
        "onToggleGoToEnd"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onSaveAs'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleError'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleWarning'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleLogMessage'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleNormalMessage'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleCritical'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleShowReportViewOnWarning'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleShowReportViewOnError'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleShowReportViewOnNormalMessage'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleShowReportViewOnCritical'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleShowReportViewOnLogMessage'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleRedirectPythonStdout'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleRedirectPythonStderr'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onToggleGoToEnd'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ReportOutput, qt_meta_tag_ZN3Gui7DockWnd12ReportOutputE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::DockWnd::ReportOutput::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextEdit::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui7DockWnd12ReportOutputE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui7DockWnd12ReportOutputE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui7DockWnd12ReportOutputE_t>.metaTypes,
    nullptr
} };

void Gui::DockWnd::ReportOutput::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ReportOutput *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onSaveAs(); break;
        case 1: _t->onToggleError(); break;
        case 2: _t->onToggleWarning(); break;
        case 3: _t->onToggleLogMessage(); break;
        case 4: _t->onToggleNormalMessage(); break;
        case 5: _t->onToggleCritical(); break;
        case 6: _t->onToggleShowReportViewOnWarning(); break;
        case 7: _t->onToggleShowReportViewOnError(); break;
        case 8: _t->onToggleShowReportViewOnNormalMessage(); break;
        case 9: _t->onToggleShowReportViewOnCritical(); break;
        case 10: _t->onToggleShowReportViewOnLogMessage(); break;
        case 11: _t->onToggleRedirectPythonStdout(); break;
        case 12: _t->onToggleRedirectPythonStderr(); break;
        case 13: _t->onToggleGoToEnd(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Gui::DockWnd::ReportOutput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::DockWnd::ReportOutput::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui7DockWnd12ReportOutputE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "WindowParameter"))
        return static_cast< WindowParameter*>(this);
    if (!strcmp(_clname, "Base::ILogger"))
        return static_cast< Base::ILogger*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int Gui::DockWnd::ReportOutput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui7DockWnd20ReportOutputObserverE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::DockWnd::ReportOutputObserver::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui7DockWnd20ReportOutputObserverE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::DockWnd::ReportOutputObserver"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ReportOutputObserver, qt_meta_tag_ZN3Gui7DockWnd20ReportOutputObserverE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::DockWnd::ReportOutputObserver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui7DockWnd20ReportOutputObserverE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui7DockWnd20ReportOutputObserverE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui7DockWnd20ReportOutputObserverE_t>.metaTypes,
    nullptr
} };

void Gui::DockWnd::ReportOutputObserver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ReportOutputObserver *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::DockWnd::ReportOutputObserver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::DockWnd::ReportOutputObserver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui7DockWnd20ReportOutputObserverE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Gui::DockWnd::ReportOutputObserver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
