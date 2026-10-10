// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Settings.h"

#include <App/Application.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/MainWindow.h>

#include <QAbstractSpinBox>
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>

#include <cstring>

using namespace Gui::Shell;

namespace
{

ParameterGrp::handle viewParams()
{
    return App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/View");
}

ParameterGrp::handle myParams()
{
    return App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
}

const std::pair<const char*, const char*> Styles[] = {
    {"Gui::RevitNavigationStyle", "Fusion 360 (middle: pan, Shift+middle: orbit)"},
    {"Gui::GestureNavigationStyle", "Gesture (trackpad and touch friendly)"},
    {"Gui::TouchpadNavigationStyle", "Touchpad (Shift: pan, Alt: orbit, Ctrl+Shift: zoom)"},
    {"Gui::CADNavigationStyle", "CAD (middle: pan, middle+left: orbit)"},
    {"Gui::SolidWorksNavigationStyle", "SolidWorks"},
    {"Gui::BlenderNavigationStyle", "Blender"},
    {"Gui::InventorNavigationStyle", "Open Inventor"},
    {"Gui::OpenCascadeNavigationStyle", "OpenCascade"},
    {"Gui::TinkerCADNavigationStyle", "TinkerCAD"},
    {"Gui::OpenSCADNavigationStyle", "OpenSCAD"},
    {"Gui::MayaGestureNavigationStyle", "Maya Gesture"},
    {"Gui::SiemensNXNavigationStyle", "Siemens NX"},
};

const std::pair<Qt::MouseButton, const char*> Buttons[] = {
    {Qt::LeftButton, "left"}, {Qt::MiddleButton, "middle"}, {Qt::RightButton, "right"}};
const char* ButtonLabels[] = {"Left button", "Middle button", "Right button"};
const char* Modes[] = {"hold", "click", "double", "toggle"};
const char* ModeLabels[] = {"Hold", "Click", "Double-click", "Toggle"};

/// Kleiner Dialog: "Drücke eine Taste"
int recordKey(QWidget* parent)
{
    class Recorder: public QDialog
    {
    public:
        explicit Recorder(QWidget* parent)
            : QDialog(parent)
        {
            setWindowTitle(QStringLiteral("Shortcut"));
            auto lay = new QVBoxLayout(this);
            lay->addWidget(new QLabel(QStringLiteral("Press the key that should act as a mouse button …")));
        }
        int key = 0;

    protected:
        void keyPressEvent(QKeyEvent* e) override
        {
            if (e->key() == Qt::Key_Escape) {
                reject();
                return;
            }
            key = e->key();
            accept();
        }
    };
    Recorder dlg(parent);
    return dlg.exec() == QDialog::Accepted ? dlg.key : 0;
}

QString keyName(int key)
{
    switch (key) {
        case Qt::Key_Control:
            return QStringLiteral("Ctrl");
        case Qt::Key_Shift:
            return QStringLiteral("Shift");
        case Qt::Key_Alt:
            return QStringLiteral("Alt");
        case Qt::Key_Meta:
            return QStringLiteral("Meta");
        default:
            return QKeySequence(key).toString(QKeySequence::NativeText);
    }
}

}  // namespace

// ---------------------------------------------------------------------------------------------

MouseKeyMapper& MouseKeyMapper::instance()
{
    static MouseKeyMapper* mapper = [] {
        auto m = new MouseKeyMapper;
        m->reload();
        myParams()->Attach(m);
        qApp->installEventFilter(m);
        return m;
    }();
    return *mapper;
}

void MouseKeyMapper::OnChange(Base::Subject<const char*>&, const char* name)
{
    if (name && std::strcmp(name, "MouseKeys") == 0) {
        reload();
    }
}

void MouseKeyMapper::reload()
{
    mappings.clear();
    const QByteArray json = QByteArray::fromStdString(myParams()->GetASCII("MouseKeys", "[]"));
    for (const auto& v : QJsonDocument::fromJson(json).array()) {
        const QJsonObject o = v.toObject();
        Qt::MouseButton button = Qt::MiddleButton;
        for (const auto& [b, name] : Buttons) {
            if (o.value(QStringLiteral("button")).toString() == QLatin1String(name)) {
                button = b;
            }
        }
        mappings.push_back({o.value(QStringLiteral("key")).toInt(), button, o.value(QStringLiteral("mode")).toString()});
    }
}

namespace
{
/// Viewport des Coin-Viewers (QGraphicsView)?
bool isViewport(QObject* obj)
{
    auto w = qobject_cast<QWidget*>(obj);
    auto view = w ? qobject_cast<QGraphicsView*>(w->parentWidget()) : nullptr;
    return view && view->viewport() == w && view->inherits("Gui::View3DInventorViewer");
}

/// Tippt der Benutzer gerade Text? Dann bleiben Tasten Tasten.
bool typing()
{
    QWidget* f = QApplication::focusWidget();
    return f && (qobject_cast<QLineEdit*>(f) || qobject_cast<QAbstractSpinBox*>(f) || qobject_cast<QTextEdit*>(f));
}
}  // namespace

void MouseKeyMapper::send(int type, Qt::MouseButton button)
{
    // Modifier-Tasten, die selbst als Maustaste dienen, nicht mitschicken (sonst deuten Navigationsstile sie um)
    Qt::KeyboardModifiers mods = QApplication::keyboardModifiers();
    for (const auto& m : mappings) {
        if (m.key == Qt::Key_Shift) {
            mods &= ~Qt::ShiftModifier;
        }
        else if (m.key == Qt::Key_Control) {
            mods &= ~Qt::ControlModifier;
        }
        else if (m.key == Qt::Key_Alt) {
            mods &= ~Qt::AltModifier;
        }
    }
    QMouseEvent event(QEvent::Type(type), hoverPos, hover->mapToGlobal(hoverPos), button, held, mods);
    sending = true;
    QApplication::sendEvent(hover, &event);
    sending = false;
}

const MouseKeyMapper::Mapping* MouseKeyMapper::find(int key) const
{
    for (const auto& m : mappings) {
        if (m.key == key) {
            return &m;
        }
    }
    return nullptr;
}

bool MouseKeyMapper::eventFilter(QObject* obj, QEvent* event)
{
    if (sending || mappings.empty()) {
        return false;
    }
    switch (event->type()) {
        case QEvent::MouseMove: {
            if (!isViewport(obj)) {
                return false;
            }
            // Position merken: QCursor::pos() ist unter Wayland nicht verlässlich
            auto me = static_cast<QMouseEvent*>(event);
            hover = static_cast<QWidget*>(obj);
            hoverPos = me->position().toPoint();
            // Trackpad-Bewegungen tragen keine Maustasten: gehaltene virtuelle Tasten ergänzen
            if (held && (me->buttons() & held) != held) {
                send(QEvent::MouseMove, Qt::NoButton);
                return true;
            }
            return false;
        }
        case QEvent::Leave:
            if (obj == hover && !held) {
                hover = nullptr;
            }
            return false;
        case QEvent::ShortcutOverride:
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
            break;
        default:
            return false;
    }
    auto ke = static_cast<QKeyEvent*>(event);
    const Mapping* m = find(ke->key());
    // nur über dem 3D-Fenster (hover wird beim Verlassen gelöscht, außer während eine Taste gehalten wird)
    if (!m || !hover || QApplication::activeModalWidget() || typing()) {
        return false;
    }
    if (event->type() == QEvent::ShortcutOverride) {
        event->accept();  // Taste als KeyPress zustellen statt als Tastenkürzel auslösen
        return true;
    }
    if (ke->isAutoRepeat()) {
        return true;
    }
    const auto press = [&](int type) {
        held |= m->button;
        send(type, m->button);
    };
    const auto release = [&] {
        held &= ~m->button;
        send(QEvent::MouseButtonRelease, m->button);
    };
    if (event->type() == QEvent::KeyPress) {
        if (m->mode == QLatin1String("click") || m->mode == QLatin1String("double")) {
            press(QEvent::MouseButtonPress);
            release();
            if (m->mode == QLatin1String("double")) {
                press(QEvent::MouseButtonDblClick);
                release();
            }
        }
        else if (m->mode == QLatin1String("toggle") && (held & m->button)) {
            release();
        }
        else {  // hold, toggle (Start)
            press(QEvent::MouseButtonPress);
        }
    }
    else if (m->mode == QLatin1String("hold") && (held & m->button)) {
        release();
    }
    return true;
}
// ---------------------------------------------------------------------------------------------

namespace
{
class CmdSettings: public Gui::Command
{
public:
    CmdSettings()
        : Command("MyCAD_Settings")
    {
        sGroup = "Tools";
        sMenuText = "Settings";
        sToolTipText = "Navigation, zoom, rotation and keys as mouse buttons";
        sStatusTip = sToolTipText;
        sWhatsThis = "MyCAD_Settings";
        sAccel = "Ctrl+,";
        eType = 0;
    }
    const char* className() const override
    {
        return "CmdSettings";
    }

protected:
    void activated(int) override
    {
        showSettings();
    }
};
}  // namespace

void Gui::Shell::registerSettings()
{
    auto& commands = Gui::Application::Instance->commandManager();
    commands.addCommand(new CmdSettings);
    // Fusion-artige Navigation als Standard, einmalig (spätere eigene Wahl bleibt erhalten)
    if (!myParams()->GetBool("NavigationDefaultSet", false)) {
        viewParams()->SetASCII("NavigationStyle", "Gui::RevitNavigationStyle");
        viewParams()->SetInt("RotationMode", 1);
        myParams()->SetBool("NavigationDefaultSet", true);
    }
    MouseKeyMapper::instance();
}

void Gui::Shell::showSettings()
{
    QDialog dlg(Gui::getMainWindow());
    dlg.setWindowTitle(QStringLiteral("Settings"));
    dlg.setMinimumWidth(560);
    auto lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 20, 24, 20);
    lay->setSpacing(10);
    auto heading = [&](const QString& text) {
        auto label = new QLabel(text);
        label->setObjectName(QStringLiteral("WindowTitle"));
        lay->addSpacing(6);
        lay->addWidget(label);
    };
    auto view = viewParams();

    // --- Navigation ---
    heading(QStringLiteral("Navigation"));
    auto form = new QFormLayout;
    form->setLabelAlignment(Qt::AlignRight);
    auto style = new QComboBox;
    const std::string current = view->GetASCII("NavigationStyle", "Gui::RevitNavigationStyle");
    for (const auto& [type, label] : Styles) {
        style->addItem(QString::fromLatin1(label), QString::fromLatin1(type));
        if (current == type) {
            style->setCurrentIndex(style->count() - 1);
        }
    }
    QObject::connect(style, &QComboBox::currentIndexChanged, [style, view] {
        view->SetASCII("NavigationStyle", style->currentData().toString().toStdString());
    });
    form->addRow(QStringLiteral("Mouse and trackpad"), style);

    auto camera = new QComboBox;
    camera->addItems({QStringLiteral("Orthographic"), QStringLiteral("Perspective")});
    camera->setCurrentIndex(view->GetBool("Orthographic", true) ? 0 : 1);
    QObject::connect(camera, &QComboBox::currentIndexChanged, [view](int i) {
        view->SetBool("Perspective", i == 1);
        view->SetBool("Orthographic", i == 0);  // wirkt sofort auf alle Ansichten (View3DSettings)
    });
    form->addRow(QStringLiteral("Camera"), camera);

    auto orbit = new QComboBox;
    orbit->addItems({QStringLiteral("Turntable (Z stays up)"), QStringLiteral("Trackball (free)"),
                     QStringLiteral("Free turntable"), QStringLiteral("Trackball classic"),
                     QStringLiteral("Rounded arcball")});
    orbit->setCurrentIndex(static_cast<int>(view->GetInt("OrbitStyle", 0)));
    QObject::connect(orbit, &QComboBox::currentIndexChanged, [view](int i) { view->SetInt("OrbitStyle", i); });
    form->addRow(QStringLiteral("Rotate"), orbit);

    auto center = new QComboBox;
    center->addItems({QStringLiteral("Window center"), QStringLiteral("Point under the cursor"),
                      QStringLiteral("Center of the model")});
    center->setCurrentIndex(static_cast<int>(view->GetInt("RotationMode", 1)));
    QObject::connect(center, &QComboBox::currentIndexChanged, [view](int i) { view->SetInt("RotationMode", i); });
    form->addRow(QStringLiteral("Rotate around"), center);

    auto sensitivity = new QSlider(Qt::Horizontal);
    sensitivity->setRange(5, 100);  // 0.5 … 10
    sensitivity->setValue(int(view->GetFloat("Sensitivity", 2.0) * 10));
    QObject::connect(sensitivity, &QSlider::valueChanged, [view](int v) { view->SetFloat("Sensitivity", v / 10.0); });
    form->addRow(QStringLiteral("Rotation speed"), sensitivity);

    auto zoomStep = new QSlider(Qt::Horizontal);
    zoomStep->setRange(2, 50);  // 0.02 … 0.5
    zoomStep->setValue(int(std::max(0.02, view->GetFloat("ZoomStep", 0.2)) * 100));
    QObject::connect(zoomStep, &QSlider::valueChanged, [view](int v) { view->SetFloat("ZoomStep", v / 100.0); });
    form->addRow(QStringLiteral("Zoom / scroll speed"), zoomStep);

    auto checkbox = [&](const QString& text, const char* param, bool def) {
        auto box = new QCheckBox(text);
        box->setChecked(view->GetBool(param, def));
        QObject::connect(box, &QCheckBox::toggled, [view, param](bool on) { view->SetBool(param, on); });
        form->addRow(QString(), box);
    };
    checkbox(QStringLiteral("Zoom towards the cursor"), "ZoomAtCursor", true);
    checkbox(QStringLiteral("Invert zoom direction"), "InvertZoom", true);
    checkbox(QStringLiteral("Animate view changes"), "UseNavigationAnimations", true);
    lay->addLayout(form);

    // --- Tasten als Maustasten ---
    heading(QStringLiteral("Keys as mouse buttons"));
    auto hint = new QLabel(QStringLiteral(
        "Hold a key while moving on the trackpad to pan or orbit, like with a mouse button. "
        "Hold: button pressed while the key is down. Toggle: first press holds, second press releases. "
        "Works while the pointer is over the 3D view."
    ));
    hint->setWordWrap(true);
    lay->addWidget(hint);
    auto table = new QTableWidget(0, 4);
    table->setHorizontalHeaderLabels({QStringLiteral("Key"), QStringLiteral("Acts as"), QStringLiteral("Mode"), QString()});
    table->verticalHeader()->hide();
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setShowGrid(false);
    table->setMinimumHeight(150);
    lay->addWidget(table);

    auto save = [table] {
        QJsonArray array;
        for (int r = 0; r < table->rowCount(); ++r) {
            QJsonObject o;
            o[QStringLiteral("key")] = table->item(r, 0)->data(Qt::UserRole).toInt();
            o[QStringLiteral("button")] = QString::fromLatin1(
                Buttons[static_cast<QComboBox*>(table->cellWidget(r, 1))->currentIndex()].second
            );
            o[QStringLiteral("mode")] = QString::fromLatin1(Modes[static_cast<QComboBox*>(table->cellWidget(r, 2))->currentIndex()]);
            array.append(o);
        }
        myParams()->SetASCII("MouseKeys", QJsonDocument(array).toJson(QJsonDocument::Compact).toStdString());
    };
    auto addRow = [table, save](int key, int button, int mode) {
        const int r = table->rowCount();
        table->insertRow(r);
        auto item = new QTableWidgetItem(keyName(key));
        item->setData(Qt::UserRole, key);
        item->setFlags(Qt::ItemIsEnabled);
        table->setItem(r, 0, item);
        auto buttons = new QComboBox;
        for (auto label : ButtonLabels) {
            buttons->addItem(QString::fromLatin1(label));
        }
        buttons->setCurrentIndex(button);
        auto modes = new QComboBox;
        for (auto label : ModeLabels) {
            modes->addItem(QString::fromLatin1(label));
        }
        modes->setCurrentIndex(mode);
        table->setCellWidget(r, 1, buttons);
        table->setCellWidget(r, 2, modes);
        auto remove = new QPushButton(QStringLiteral("Remove"));
        remove->setAutoDefault(false);
        table->setCellWidget(r, 3, remove);
        QObject::connect(buttons, &QComboBox::currentIndexChanged, save);
        QObject::connect(modes, &QComboBox::currentIndexChanged, save);
        QObject::connect(remove, &QPushButton::clicked, table, [table, remove, save] {
            for (int i = 0; i < table->rowCount(); ++i) {
                if (table->cellWidget(i, 3) == remove) {
                    table->removeRow(i);
                    break;
                }
            }
            save();
        });
    };
    const QByteArray json = QByteArray::fromStdString(myParams()->GetASCII("MouseKeys", "[]"));
    for (const auto& v : QJsonDocument::fromJson(json).array()) {
        const QJsonObject o = v.toObject();
        int button = 1, mode = 0;
        for (int i = 0; i < 3; ++i) {
            button = o.value(QStringLiteral("button")).toString() == QLatin1String(Buttons[i].second) ? i : button;
        }
        for (int i = 0; i < 4; ++i) {
            mode = o.value(QStringLiteral("mode")).toString() == QLatin1String(Modes[i]) ? i : mode;
        }
        addRow(o.value(QStringLiteral("key")).toInt(), button, mode);
    }

    auto row = new QHBoxLayout;
    auto add = new QPushButton(QStringLiteral("Add Key …"));
    add->setAutoDefault(false);
    QObject::connect(add, &QPushButton::clicked, &dlg, [&dlg, addRow, save] {
        if (const int key = recordKey(&dlg)) {
            addRow(key, 1, 0);  // Standard: mittlere Maustaste halten (Pan/Orbit)
            save();
        }
    });
    row->addWidget(add);
    row->addStretch();
    auto more = new QPushButton(QStringLiteral("More Preferences …"));
    more->setAutoDefault(false);
    QObject::connect(more, &QPushButton::clicked, &dlg, [&dlg] {
        dlg.accept();
        Gui::Application::Instance->commandManager().runCommandByName("Std_DlgPreferences");
    });
    row->addWidget(more);
    lay->addLayout(row);

    auto buttons = new QDialogButtonBox(QDialogButtonBox::Close);
    buttons->button(QDialogButtonBox::Close)->setDefault(true);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::accept);
    lay->addWidget(buttons);
    dlg.exec();
}
