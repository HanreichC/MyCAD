/****************************************************************************
** Meta object code from reading C++ file 'PrefWidgets.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Gui/PrefWidgets.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PrefWidgets.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3Gui11PrefSpinBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefSpinBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui11PrefSpinBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefSpinBox",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefSpinBox, qt_meta_tag_ZN3Gui11PrefSpinBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefSpinBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QSpinBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui11PrefSpinBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui11PrefSpinBoxE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui11PrefSpinBoxE_t>.metaTypes,
    nullptr
} };

void Gui::PrefSpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefSpinBox *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui11PrefSpinBoxE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QSpinBox::qt_metacast(_clname);
}

int Gui::PrefSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui17PrefDoubleSpinBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefDoubleSpinBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui17PrefDoubleSpinBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefDoubleSpinBox",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefDoubleSpinBox, qt_meta_tag_ZN3Gui17PrefDoubleSpinBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefDoubleSpinBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QDoubleSpinBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui17PrefDoubleSpinBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui17PrefDoubleSpinBoxE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui17PrefDoubleSpinBoxE_t>.metaTypes,
    nullptr
} };

void Gui::PrefDoubleSpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefDoubleSpinBox *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefDoubleSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefDoubleSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui17PrefDoubleSpinBoxE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QDoubleSpinBox::qt_metacast(_clname);
}

int Gui::PrefDoubleSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDoubleSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui12PrefLineEditE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefLineEdit::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui12PrefLineEditE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefLineEdit",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefLineEdit, qt_meta_tag_ZN3Gui12PrefLineEditE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefLineEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QLineEdit::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefLineEditE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefLineEditE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui12PrefLineEditE_t>.metaTypes,
    nullptr
} };

void Gui::PrefLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefLineEdit *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefLineEditE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QLineEdit::qt_metacast(_clname);
}

int Gui::PrefLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui12PrefTextEditE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefTextEdit::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui12PrefTextEditE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefTextEdit",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefTextEdit, qt_meta_tag_ZN3Gui12PrefTextEditE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefTextEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextEdit::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefTextEditE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefTextEditE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui12PrefTextEditE_t>.metaTypes,
    nullptr
} };

void Gui::PrefTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefTextEdit *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefTextEditE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int Gui::PrefTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui15PrefFileChooserE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefFileChooser::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui15PrefFileChooserE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefFileChooser",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefFileChooser, qt_meta_tag_ZN3Gui15PrefFileChooserE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefFileChooser::staticMetaObject = { {
    QMetaObject::SuperData::link<FileChooser::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefFileChooserE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefFileChooserE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui15PrefFileChooserE_t>.metaTypes,
    nullptr
} };

void Gui::PrefFileChooser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefFileChooser *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefFileChooser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefFileChooser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefFileChooserE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return FileChooser::qt_metacast(_clname);
}

int Gui::PrefFileChooser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FileChooser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui12PrefComboBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefComboBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui12PrefComboBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefComboBox",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefComboBox, qt_meta_tag_ZN3Gui12PrefComboBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefComboBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QComboBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefComboBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefComboBoxE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui12PrefComboBoxE_t>.metaTypes,
    nullptr
} };

void Gui::PrefComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefComboBox *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefComboBoxE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QComboBox::qt_metacast(_clname);
}

int Gui::PrefComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui12PrefCheckBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefCheckBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui12PrefCheckBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefCheckBox",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefCheckBox, qt_meta_tag_ZN3Gui12PrefCheckBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefCheckBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QCheckBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefCheckBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefCheckBoxE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui12PrefCheckBoxE_t>.metaTypes,
    nullptr
} };

void Gui::PrefCheckBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefCheckBox *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefCheckBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefCheckBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui12PrefCheckBoxE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QCheckBox::qt_metacast(_clname);
}

int Gui::PrefCheckBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCheckBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui15PrefRadioButtonE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefRadioButton::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui15PrefRadioButtonE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefRadioButton",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefRadioButton, qt_meta_tag_ZN3Gui15PrefRadioButtonE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefRadioButton::staticMetaObject = { {
    QMetaObject::SuperData::link<QRadioButton::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefRadioButtonE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefRadioButtonE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui15PrefRadioButtonE_t>.metaTypes,
    nullptr
} };

void Gui::PrefRadioButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefRadioButton *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefRadioButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefRadioButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefRadioButtonE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QRadioButton::qt_metacast(_clname);
}

int Gui::PrefRadioButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QRadioButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui10PrefSliderE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefSlider::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui10PrefSliderE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefSlider",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefSlider, qt_meta_tag_ZN3Gui10PrefSliderE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefSlider::staticMetaObject = { {
    QMetaObject::SuperData::link<QSlider::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10PrefSliderE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10PrefSliderE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui10PrefSliderE_t>.metaTypes,
    nullptr
} };

void Gui::PrefSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefSlider *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui10PrefSliderE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QSlider::qt_metacast(_clname);
}

int Gui::PrefSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui15PrefColorButtonE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefColorButton::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui15PrefColorButtonE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefColorButton",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefColorButton, qt_meta_tag_ZN3Gui15PrefColorButtonE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefColorButton::staticMetaObject = { {
    QMetaObject::SuperData::link<ColorButton::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefColorButtonE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefColorButtonE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui15PrefColorButtonE_t>.metaTypes,
    nullptr
} };

void Gui::PrefColorButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefColorButton *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefColorButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefColorButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefColorButtonE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return ColorButton::qt_metacast(_clname);
}

int Gui::PrefColorButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ColorButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui15PrefUnitSpinBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefUnitSpinBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui15PrefUnitSpinBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefUnitSpinBox",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefUnitSpinBox, qt_meta_tag_ZN3Gui15PrefUnitSpinBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefUnitSpinBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QuantitySpinBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefUnitSpinBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefUnitSpinBoxE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui15PrefUnitSpinBoxE_t>.metaTypes,
    nullptr
} };

void Gui::PrefUnitSpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefUnitSpinBox *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefUnitSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefUnitSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui15PrefUnitSpinBoxE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QuantitySpinBox::qt_metacast(_clname);
}

int Gui::PrefUnitSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QuantitySpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui19PrefQuantitySpinBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefQuantitySpinBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui19PrefQuantitySpinBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefQuantitySpinBox",
        "prefEntry",
        "prefPath",
        "historySize"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'historySize'
        QtMocHelpers::PropertyData<int>(3, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefQuantitySpinBox, qt_meta_tag_ZN3Gui19PrefQuantitySpinBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefQuantitySpinBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QuantitySpinBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui19PrefQuantitySpinBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui19PrefQuantitySpinBoxE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui19PrefQuantitySpinBoxE_t>.metaTypes,
    nullptr
} };

void Gui::PrefQuantitySpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefQuantitySpinBox *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->historySize(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        case 2: _t->setHistorySize(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefQuantitySpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefQuantitySpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui19PrefQuantitySpinBoxE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QuantitySpinBox::qt_metacast(_clname);
}

int Gui::PrefQuantitySpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QuantitySpinBox::qt_metacall(_c, _id, _a);
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
namespace {
struct qt_meta_tag_ZN3Gui11PrefFontBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefFontBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui11PrefFontBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefFontBox",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefFontBox, qt_meta_tag_ZN3Gui11PrefFontBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefFontBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QFontComboBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui11PrefFontBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui11PrefFontBoxE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui11PrefFontBoxE_t>.metaTypes,
    nullptr
} };

void Gui::PrefFontBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefFontBox *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefFontBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefFontBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui11PrefFontBoxE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QFontComboBox::qt_metacast(_clname);
}

int Gui::PrefFontBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFontComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN3Gui21PrefCheckableGroupBoxE_t {};
} // unnamed namespace

template <> constexpr inline auto Gui::PrefCheckableGroupBox::qt_create_metaobjectdata<qt_meta_tag_ZN3Gui21PrefCheckableGroupBoxE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Gui::PrefCheckableGroupBox",
        "prefEntry",
        "prefPath"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'prefEntry'
        QtMocHelpers::PropertyData<QByteArray>(1, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'prefPath'
        QtMocHelpers::PropertyData<QByteArray>(2, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrefCheckableGroupBox, qt_meta_tag_ZN3Gui21PrefCheckableGroupBoxE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Gui::PrefCheckableGroupBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QGroupBox::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui21PrefCheckableGroupBoxE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui21PrefCheckableGroupBoxE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3Gui21PrefCheckableGroupBoxE_t>.metaTypes,
    nullptr
} };

void Gui::PrefCheckableGroupBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrefCheckableGroupBox *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->entryName(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->paramGrpPath(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEntryName(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setParamGrpPath(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Gui::PrefCheckableGroupBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::PrefCheckableGroupBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3Gui21PrefCheckableGroupBoxE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrefWidget"))
        return static_cast< PrefWidget*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int Gui::PrefCheckableGroupBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
