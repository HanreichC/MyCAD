/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/MainWindow.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui10UrlHandlerE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::UrlHandler::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui10UrlHandlerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::UrlHandler"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<UrlHandler, qt_meta_tag_ZN3Gui10UrlHandlerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::UrlHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10UrlHandlerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10UrlHandlerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui10UrlHandlerE_t>.metaTypes,
    nullptr
} };

void Gui::UrlHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<UrlHandler *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Gui::UrlHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::UrlHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10UrlHandlerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Gui::UrlHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::MainWindow",
        "guiInitialized",
        "",
        "timeEvent",
        "windowStateChanged",
        "QWidget*",
        "workbenchActivated",
        "mainWindowClosed",
        "recentFileAdded",
        "filename",
        "updateEditorActions",
        "setPaneText",
        "i",
        "text",
        "setUserSchema",
        "userSchema",
        "tile",
        "cascade",
        "closeActiveWindow",
        "closeAllDocuments",
        "close",
        "confirmSave",
        "App::Document*",
        "doc",
        "parent",
        "addCheckBox",
        "activateNextWindow",
        "activatePreviousWindow",
        "activateWorkbench",
        "whatsThis",
        "switchToTopLevelMode",
        "switchToDockedMode",
        "statusMessageChanged",
        "showMessage",
        "message",
        "timeout",
        "setRightSideMessage",
        "isRightSideMessageVisible",
        "addStatusBarItem",
        "widget",
        "StatusBarItemSpec",
        "spec",
        "removeStatusBarItem",
        "id",
        "buildStatusBarContextMenu",
        "QMenu&",
        "menu",
        "setWindowTitle",
        "string",
        "setActiveSubWindow",
        "onWindowActivated",
        "QMdiSubWindow*",
        "tabCloseRequested",
        "index",
        "onWindowsMenuAboutToShow",
        "onToolBarMenuAboutToShow",
        "onDockWindowMenuAboutToShow",
        "_updateActions",
        "delayedStartup",
        "processMessages",
        "clearStatus"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'guiInitialized'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'timeEvent'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'windowStateChanged'
        QtMocHelpers::SignalData<void(QWidget *)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 2 },
        }}),
        // Signal 'workbenchActivated'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'mainWindowClosed'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'recentFileAdded'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'updateEditorActions'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setPaneText'
        QtMocHelpers::SlotData<void(int, QString)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::QString, 13 },
        }}),
        // Slot 'setUserSchema'
        QtMocHelpers::SlotData<void(int)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'tile'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'cascade'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'closeActiveWindow'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'closeAllDocuments'
        QtMocHelpers::SlotData<bool(bool)>(19, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Bool, 20 },
        }}),
        // Slot 'closeAllDocuments'
        QtMocHelpers::SlotData<bool()>(19, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool),
        // Slot 'confirmSave'
        QtMocHelpers::SlotData<int(App::Document *, QWidget *, bool)>(21, 2, QMC::AccessPublic, QMetaType::Int, {{
            { 0x80000000 | 22, 23 }, { 0x80000000 | 5, 24 }, { QMetaType::Bool, 25 },
        }}),
        // Slot 'confirmSave'
        QtMocHelpers::SlotData<int(App::Document *, QWidget *)>(21, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Int, {{
            { 0x80000000 | 22, 23 }, { 0x80000000 | 5, 24 },
        }}),
        // Slot 'confirmSave'
        QtMocHelpers::SlotData<int(App::Document *)>(21, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Int, {{
            { 0x80000000 | 22, 23 },
        }}),
        // Slot 'activateNextWindow'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'activatePreviousWindow'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'activateWorkbench'
        QtMocHelpers::SlotData<void(const QString &)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Slot 'whatsThis'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'switchToTopLevelMode'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'switchToDockedMode'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'statusMessageChanged'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'showMessage'
        QtMocHelpers::SlotData<void(const QString &, int)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 34 }, { QMetaType::Int, 35 },
        }}),
        // Slot 'showMessage'
        QtMocHelpers::SlotData<void(const QString &)>(33, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 34 },
        }}),
        // Slot 'setRightSideMessage'
        QtMocHelpers::SlotData<void(const QString &)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 34 },
        }}),
        // Slot 'isRightSideMessageVisible'
        QtMocHelpers::SlotData<bool() const>(37, 2, QMC::AccessPublic, QMetaType::Bool),
        // Slot 'addStatusBarItem'
        QtMocHelpers::SlotData<void(QWidget *, const StatusBarItemSpec &)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 39 }, { 0x80000000 | 40, 41 },
        }}),
        // Slot 'removeStatusBarItem'
        QtMocHelpers::SlotData<void(const QByteArray &)>(42, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 43 },
        }}),
        // Slot 'buildStatusBarContextMenu'
        QtMocHelpers::SlotData<void(QMenu &)>(44, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 45, 46 },
        }}),
        // Slot 'setWindowTitle'
        QtMocHelpers::SlotData<void(const QString &)>(47, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 48 },
        }}),
        // Slot 'setActiveSubWindow'
        QtMocHelpers::SlotData<void(QWidget *)>(49, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 5, 2 },
        }}),
        // Slot 'onWindowActivated'
        QtMocHelpers::SlotData<void(QMdiSubWindow *)>(50, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 51, 2 },
        }}),
        // Slot 'tabCloseRequested'
        QtMocHelpers::SlotData<void(int)>(52, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 53 },
        }}),
        // Slot 'onWindowsMenuAboutToShow'
        QtMocHelpers::SlotData<void()>(54, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onToolBarMenuAboutToShow'
        QtMocHelpers::SlotData<void()>(55, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDockWindowMenuAboutToShow'
        QtMocHelpers::SlotData<void()>(56, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot '_updateActions'
        QtMocHelpers::SlotData<void()>(57, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'delayedStartup'
        QtMocHelpers::SlotData<void()>(58, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'processMessages'
        QtMocHelpers::SlotData<void(const QList<QString> &)>(59, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QStringList, 2 },
        }}),
        // Slot 'clearStatus'
        QtMocHelpers::SlotData<void()>(60, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN3Gui10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui10MainWindowE_t>.metaTypes,
    nullptr
} };

void Gui::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->guiInitialized(); break;
        case 1: _t->timeEvent(); break;
        case 2: _t->windowStateChanged((*reinterpret_cast<std::add_pointer_t<QWidget*>>(_a[1]))); break;
        case 3: _t->workbenchActivated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->mainWindowClosed(); break;
        case 5: _t->recentFileAdded((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->updateEditorActions(); break;
        case 7: _t->setPaneText((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->setUserSchema((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->tile(); break;
        case 10: _t->cascade(); break;
        case 11: _t->closeActiveWindow(); break;
        case 12: { bool _r = _t->closeAllDocuments((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->closeAllDocuments();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { int _r = _t->confirmSave((*reinterpret_cast<std::add_pointer_t<App::Document*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QWidget*>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 15: { int _r = _t->confirmSave((*reinterpret_cast<std::add_pointer_t<App::Document*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QWidget*>>(_a[2])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 16: { int _r = _t->confirmSave((*reinterpret_cast<std::add_pointer_t<App::Document*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->activateNextWindow(); break;
        case 18: _t->activatePreviousWindow(); break;
        case 19: _t->activateWorkbench((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->whatsThis(); break;
        case 21: _t->switchToTopLevelMode(); break;
        case 22: _t->switchToDockedMode(); break;
        case 23: _t->statusMessageChanged(); break;
        case 24: _t->showMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 25: _t->showMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 26: _t->setRightSideMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 27: { bool _r = _t->isRightSideMessageVisible();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->addStatusBarItem((*reinterpret_cast<std::add_pointer_t<QWidget*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<StatusBarItemSpec>>(_a[2]))); break;
        case 29: _t->removeStatusBarItem((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 30: _t->buildStatusBarContextMenu((*reinterpret_cast<std::add_pointer_t<QMenu&>>(_a[1]))); break;
        case 31: _t->setWindowTitle((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 32: _t->setActiveSubWindow((*reinterpret_cast<std::add_pointer_t<QWidget*>>(_a[1]))); break;
        case 33: _t->onWindowActivated((*reinterpret_cast<std::add_pointer_t<QMdiSubWindow*>>(_a[1]))); break;
        case 34: _t->tabCloseRequested((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 35: _t->onWindowsMenuAboutToShow(); break;
        case 36: _t->onToolBarMenuAboutToShow(); break;
        case 37: _t->onDockWindowMenuAboutToShow(); break;
        case 38: _t->_updateActions(); break;
        case 39: _t->delayedStartup(); break;
        case 40: _t->processMessages((*reinterpret_cast<std::add_pointer_t<QList<QString>>>(_a[1]))); break;
        case 41: _t->clearStatus(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 28:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 32:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::guiInitialized, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::timeEvent, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(QWidget * )>(_a, &MainWindow::windowStateChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(const QString & )>(_a, &MainWindow::workbenchActivated, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::mainWindowClosed, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(const QString & )>(_a, &MainWindow::recentFileAdded, 5))
            return;
    }
}

const QMetaObject *Gui::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Gui::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    }
    return _id;
}

// SIGNAL 0
void Gui::MainWindow::guiInitialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Gui::MainWindow::timeEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Gui::MainWindow::windowStateChanged(QWidget * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Gui::MainWindow::workbenchActivated(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Gui::MainWindow::mainWindowClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Gui::MainWindow::recentFileAdded(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
