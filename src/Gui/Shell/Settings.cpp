// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Settings.h"
#include "Shell.h"
#include "TabletKeys.h"
#include "Theme.h"

#include <App/Application.h>
#include <Base/Interpreter.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/MainWindow.h>
#include <Gui/Navigation/NavigationStyle.h>
#include <Quarter/devices/InputDevice.h>
#include <Gui/View3DInventorViewer.h>

#include <QAbstractSpinBox>
#include <QDoubleSpinBox>
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QPointingDevice>
#include <QNativeGestureEvent>
#include <QWheelEvent>
#include <QToolButton>
#include <QDir>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QCursor>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGraphicsDropShadowEffect>
#include <QGridLayout>
#include <QGraphicsProxyWidget>
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
#include <QVariantAnimation>
#include <QVBoxLayout>
#include <memory>
#include <functional>
#include <QAbstractItemView>
#include <QWindow>
#include <QSvgRenderer>
#include <QStackedWidget>
#include <QPainter>
#include <QPlainTextEdit>
#include <QMouseEvent>
#include <QFile>
#include <QButtonGroup>
#include <QAbstractButton>
#include <QElapsedTimer>
#include <QProcess>
#include <QTabletEvent>

#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <libinput.h>
#include <libudev.h>
#include <sys/stat.h>
#include <unistd.h>
#include <QPointer>
#include <QSocketNotifier>

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

/// Navigationsstile mit Bedienung (aus den Zustandsautomaten der Stile abgeleitet).
/// Alternativen durch " | " getrennt, Tasten-Chips durch "+"
struct Style
{
    const char* type;
    const char* label;
    const char* rotate;
    const char* pan;
    const char* zoom;
    const char* select;
};
const Style Styles[] = {
    {"Gui::RevitNavigationStyle", "Fusion 360", "Shift+Middle drag", "Middle drag | Left+Right drag",
     "Scroll | Ctrl+Middle drag", "Left click"},
    {"Gui::GestureNavigationStyle", "Gesture (trackpad & touch)", "Left drag | One-finger drag",
     "Right drag | Two-finger drag", "Scroll | Pinch | PgUp / PgDn", "Left click | Tap"},
    {"Gui::TouchpadNavigationStyle", "Touchpad", "Alt+Move", "Shift+Move", "Ctrl+Shift+Move | Scroll", "Left click"},
    {"Gui::CADNavigationStyle", "CAD", "Middle+Left drag | Shift+Right drag", "Middle drag | Ctrl+Right drag",
     "Scroll | Middle+Left drag up/down", "Left click"},
    {"Gui::SolidWorksNavigationStyle", "SolidWorks", "Middle drag", "Ctrl+Middle drag", "Scroll | Shift+Middle drag",
     "Left click"},
    {"Gui::BlenderNavigationStyle", "Blender", "Middle drag", "Shift+Middle drag | Left+Right drag",
     "Scroll | Ctrl+Middle drag", "Left click"},
    {"Gui::InventorNavigationStyle", "Open Inventor", "Left drag", "Middle drag", "Scroll | Left+Middle drag",
     "Ctrl+Left click"},
    {"Gui::OpenCascadeNavigationStyle", "OpenCascade", "Ctrl+Right drag", "Middle drag", "Ctrl+Left drag | Scroll",
     "Left click"},
    {"Gui::TinkerCADNavigationStyle", "TinkerCAD", "Right drag", "Middle drag", "Scroll", "Left click"},
    {"Gui::OpenSCADNavigationStyle", "OpenSCAD", "Left drag", "Right drag", "Middle drag | Shift+Right drag | Scroll",
     "Left click"},
    {"Gui::MayaGestureNavigationStyle", "Maya", "Alt+Left drag | One-finger drag", "Alt+Middle drag | Two-finger drag",
     "Alt+Right drag | Scroll | Pinch", "Left click | Tap"},
    {"Gui::SiemensNXNavigationStyle", "Siemens NX", "Middle drag", "Middle+Right drag", "Scroll", "Left click"},
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
            lay->addWidget(new QLabel(T("Press the key that should act as a mouse button …")));
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

/// Trackpad im 3D-Fenster: Zoomrichtung getrennt für Maus und Trackpad (Einstellungen) und 3 Finger = drehen.
/// FreeCAD kennt nur eine Zoomrichtung ("InvertZoom", gilt fürs Mausrad); beim Trackpad wird die Richtung im Ereignis
/// selbst umgedreht, bevor das 3D-Fenster es sieht. (Ein neu zugestelltes Ersatz-Ereignis kam bei echten Trackpads
/// nicht an: Qt bindet Scrollphasen an das Original.) 2 Finger schieben und Spreizen erledigt NavigationStyle selbst.
struct FlipWheel: QWheelEvent
{
    static void flip(QWheelEvent* e)
    {
        auto f = static_cast<FlipWheel*>(e);  // nur Zugriff auf die geschützten Felder, keine eigenen Daten
        f->m_angleDelta = -f->m_angleDelta;
        f->m_pixelDelta = -f->m_pixelDelta;
    }
};
struct FlipGesture: QNativeGestureEvent
{
    static void flip(QNativeGestureEvent* e)
    {
        auto f = static_cast<FlipGesture*>(e);
        f->m_realValue = -f->m_realValue;
    }
};

/// 3-Finger-Wischen, das MyCAD selbst vom Touchpad liest (TouchpadReader), trägt dieses Gerät. Sobald es welche
/// geliefert hat (Eigenschaft am qApp, prüfbar in tests/gui/test_gestures), sind 3-Finger-Gesten anderer Herkunft
/// Doppel: ein Compositor wie Sway reicht sie zusätzlich weiter, die Ansicht drehte sich doppelt so schnell.
const char* const ReaderDevice = "MyCAD touchpad reader";
const char* const ReaderSwipes = "mycadTouchpadReaderSwipes";

class Trackpad: public QObject
{
public:
    static void install()
    {
        static Trackpad filter;
        qApp->installEventFilter(&filter);
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if ((event->type() != QEvent::Wheel && event->type() != QEvent::NativeGesture) || !isViewport(obj)) {
            return false;
        }
        const bool mouseInvert = viewParams()->GetBool("InvertZoom", true);
        const bool padInvert = myParams()->GetBool("InvertTrackpadZoom", mouseInvert);
        if (event->type() == QEvent::Wheel) {
            auto we = static_cast<QWheelEvent*>(event);
            // Wayland meldet Maus und Trackpad oft als ein Gerät; Trackpad-Scrollen hat aber Phasen bzw. Pixel-Schritte
            const bool trackpad = (we->pointingDevice() && we->pointingDevice()->type() == QInputDevice::DeviceType::TouchPad)
                || we->phase() != Qt::NoScrollPhase || !we->pixelDelta().isNull();
            const bool zooms = Gui::NavigationStyle::wheelAction(true, Gui::NavigationStyle::touchpadScrollPans(),
                                                                 we->modifiers() & Qt::ShiftModifier,
                                                                 we->modifiers() & Qt::ControlModifier)
                == Gui::NavigationStyle::WheelAction::Zoom;  // beim Schieben nichts umdrehen
            if (trackpad && zooms && padInvert != mouseInvert) {
                FlipWheel::flip(we);
            }
            return false;
        }
        auto ge = static_cast<QNativeGestureEvent*>(event);
        if (ge->gestureType() == Qt::ZoomNativeGesture && padInvert) {
            FlipGesture::flip(ge);  // Spreizen: ohne Umkehr wie gewohnt (auseinander = näher)
        }
        // 3 Finger wischen = drehen wie Ziehen mit der Maus (2 Finger sind Scrollen; 4 belegen KDE/GNOME selbst).
        // Qt meldet Beginn/Ende für Wischen und Spreizen gleich, darum erst bei der ersten Wischbewegung anfangen.
        const bool fromReader = ge->device() && ge->device()->name() == QLatin1String(ReaderDevice);
        if (ge->fingerCount() >= 3 && !fromReader && qApp->property(ReaderSwipes).toBool()) {
            return true;  // das Doppel des Compositors: gedreht wird mit dem, was der Reader liest
        }
        auto nav = static_cast<Gui::View3DInventorViewer*>(obj->parent())->navigationStyle();
        if (ge->gestureType() == Qt::PanNativeGesture && ge->fingerCount() >= 3 && nav) {
            auto vp = static_cast<QWidget*>(obj);
            if (!orbiting) {
                Gui::NavigationStyle::OrbitDragOptions grab;  // dreht den Körper unter dem Cursor wie die Maus, nicht den Raum
                grab.centerMode = Gui::NavigationStyle::OrbitDragOptions::CenterMode::Cursor;
                grab.cursor = SIM::Coin3D::Quarter::InputDevice::toDevicePixelPosition(
                    ge->position(), SbVec2s(short(vp->width()), short(vp->height())), vp->devicePixelRatio());
                nav->beginOrbitDrag(grab);
                orbiting = true;
            }
            const SbVec2f mid(0.5F, 0.5F);  // Qt: y nach unten, Coin: y nach oben
            const auto k = float(viewParams()->GetFloat("TrackpadRotateSpeed", 1.0));
            nav->updateOrbitDrag(mid + k * SbVec2f(float(ge->delta().x() / vp->width()), float(-ge->delta().y() / vp->height())), mid);
            return true;
        }
        if (ge->gestureType() == Qt::EndNativeGesture && orbiting && nav) {
            nav->endOrbitDrag();
            orbiting = false;
        }
        return false;
    }

private:
    bool orbiting = false;
};

/// Tasten am Grafiktablett (Einstellungen › Tablett): was der TouchpadReader über das Tablett weiß, und wer gerade
/// zuhört. Ist die Seite offen, leuchten nur ihre Zeilen auf, statt dass die Tasten etwas tun.
struct TabletPad
{
    QString name;         ///< Gerätename von libinput, leer = keins angeschlossen (oder nicht lesbar)
    bool denied = false;  ///< ein Tablett ist da, aber MyCAD darf es nicht lesen (udev-Regel fehlt)
    std::function<void(const std::string& key, bool down)> listener;
    std::function<void()> changed;
};
TabletPad& tabletPad()
{
    static TabletPad pad;
    return pad;
}
/// eine Taste am Tablett ("pad1" …) oder am Stift ("penLow", "penHigh") ist gedrückt/losgelassen (TabletActions)
void tabletKey(const std::string& key, bool down, bool pad);

/// KWin behält jedes Wischen mit 3+ Fingern für sich (auch ohne Kürzel), Programme bekommen es nie. Darum liest
/// MyCAD lesbare Touchpads selbst mit, neben KWin (wie libinput-gestures), und reicht 3-Finger-Wischen als Qt-Geste
/// an die 3D-Ansicht unter dem Zeiger; dort dreht Trackpad oben. Lesbar macht Touchpads eine udev-Regel (uaccess,
/// siehe jomaa.kb96trackpad.config); ohne Zugriff passiert einfach nichts.
/// Leitet ein Compositor 3-Finger-Wischen doch weiter (z. B. Sway), verwirft der Trackpad-Filter dieses Doppel, sobald
/// hier Wischen ankommt.
/// Ebenso liest er die Tasten am Grafiktablett (Qt meldet sie unter Wayland nicht) für Einstellungen › Tablett; lesbar
/// macht sie die udev-Regel, die die Seite mit "Zugriff erlauben" anlegt.
class TouchpadReader: public QObject
{
public:
    static TouchpadReader& install()
    {
        static TouchpadReader reader;
        return reader;
    }
    /// alle Geräte neu öffnen, z. B. nachdem die udev-Regel für Tabletts angelegt ist
    void reconnect()
    {
        if (li) {
            tabletPad().denied = false;
            libinput_suspend(li);
            libinput_resume(li);
            read();
            if (tabletPad().changed) {
                tabletPad().changed();
            }
        }
    }

private:
    TouchpadReader()
    {
        static const libinput_interface io {
            [](const char* path, int flags, void* udev) -> int {
                // nur Touchpads und die Tasten von Grafiktabletts öffnen, nie Tastaturen (falls der Benutzer z. B. in
                // der Gruppe input ist)
                struct stat st {};
                if (stat(path, &st) != 0) {
                    return -errno;
                }
                auto dev = udev_device_new_from_devnum(static_cast<struct udev*>(udev), 'c', st.st_rdev);
                const auto is = [dev](const char* property) {
                    const char* v = dev ? udev_device_get_property_value(dev, property) : nullptr;
                    return v && std::strcmp(v, "1") == 0;
                };
                const bool touchpad = is("ID_INPUT_TOUCHPAD"), pad = is("ID_INPUT_TABLET_PAD");
                // NAME trägt das Eingabegerät darüber (input42), nicht eventN; gehört dev, kein eigenes unref
                struct udev_device* input = dev ? udev_device_get_parent_with_subsystem_devtype(dev, "input", nullptr) : nullptr;
                const char* name = input ? udev_device_get_property_value(input, "NAME") : nullptr;
                const QString padName = pad && name ? QString::fromUtf8(name).remove(QLatin1Char('"')) : QString();
                udev_device_unref(dev);
                if (!touchpad && !pad) {
                    return -EPERM;
                }
                const int fd = ::open(path, flags | O_CLOEXEC);
                const int err = errno;
                if (fd < 0 && pad && (err == EACCES || err == EPERM)) {
                    tabletPad().denied = true;  // da, aber nicht lesbar: die Seite bietet "Zugriff erlauben" an
                    tabletPad().name = padName;
                }
                return fd < 0 ? -err : fd;
            },
            [](int fd, void*) { ::close(fd); }};
        struct udev* udev = udev_new();
        li = udev ? libinput_udev_create_context(&io, udev, udev) : nullptr;
        if (!li) {
            return;
        }
        // nicht lesbare Geräte (der Normalfall ohne udev-Regel) nicht bei jedem Start ins Terminal melden
        libinput_log_set_handler(li, [](libinput*, libinput_log_priority, const char*, va_list) {});
        if (libinput_udev_assign_seat(li, "seat0") != 0) {
            return;
        }
        auto notifier = new QSocketNotifier(libinput_get_fd(li), QSocketNotifier::Read, this);
        connect(notifier, &QSocketNotifier::activated, this, &TouchpadReader::read);
        read();
    }

    void read()
    {
        libinput_dispatch(li);
        while (libinput_event* e = libinput_get_event(li)) {
            const auto type = libinput_event_get_type(e);
            if (type == LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN || type == LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE
                || type == LIBINPUT_EVENT_GESTURE_SWIPE_END) {
                auto g = libinput_event_get_gesture_event(e);
                if (libinput_event_gesture_get_finger_count(g) == 3) {  // 4 Finger gehören KDE
                    swipe(type, QPointF(libinput_event_gesture_get_dx(g), libinput_event_gesture_get_dy(g)));
                }
            }
            else if (type == LIBINPUT_EVENT_TABLET_PAD_BUTTON) {
                auto p = libinput_event_get_tablet_pad_event(e);
                tabletKey(Gui::Shell::TabletKeys::padKey(int(libinput_event_tablet_pad_get_button_number(p)) + 1),
                          libinput_event_tablet_pad_get_button_state(p) == LIBINPUT_BUTTON_STATE_PRESSED, true);
            }
            else if (type == LIBINPUT_EVENT_DEVICE_ADDED || type == LIBINPUT_EVENT_DEVICE_REMOVED) {
                libinput_device* dev = libinput_event_get_device(e);
                if (libinput_device_has_capability(dev, LIBINPUT_DEVICE_CAP_TABLET_PAD)) {
                    const bool added = type == LIBINPUT_EVENT_DEVICE_ADDED;
                    tabletPad().name = added ? QString::fromUtf8(libinput_device_get_name(dev)) : QString();
                    tabletPad().denied = tabletPad().denied && !added;
                    if (tabletPad().changed) {
                        tabletPad().changed();
                    }
                }
            }
            libinput_event_destroy(e);
        }
    }

    void swipe(libinput_event_type type, QPointF delta)
    {
        if (type == LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN) {
            viewport = nullptr;
            for (QWidget* w : QApplication::allWidgets()) {
                if (isViewport(w) && w->isVisible() && w->underMouse()) {
                    viewport = w;
                }
            }
            return;
        }
        if (!viewport) {
            return;
        }
        const QPointF global = QCursor::pos();
        const QPointF local = viewport->mapFromGlobal(global);
        static const QPointingDevice device(QLatin1String(ReaderDevice), 0x4d79, QInputDevice::DeviceType::TouchPad,
                                            QPointingDevice::PointerType::Finger, QInputDevice::Capability::Position, 5, 0);
        qApp->setProperty(ReaderSwipes, true);
        QNativeGestureEvent ev(type == LIBINPUT_EVENT_GESTURE_SWIPE_END ? Qt::EndNativeGesture : Qt::PanNativeGesture,
                               &device, 3, local, local, global, 0, delta);
        QApplication::sendEvent(viewport, &ev);
    }

    libinput* li = nullptr;
    QPointer<QWidget> viewport;
};

/// Tippt der Benutzer gerade Text? Dann bleiben Tasten Tasten.
/// Schreibt der Benutzer gerade Text (Umbenennen, Namen …)? Dann bleiben alle Tasten Tasten, auch Shift.
/// Zahlenfelder zählen nicht: dort braucht man weder Großbuchstaben noch Leertaste, und Navigieren bei offenem
/// Dialog soll weiter gehen.
bool typing()
{
    QWidget* f = QApplication::focusWidget();
    // Browser, Inspector … sind Glass-Panels in der Szene der 3D-Ansicht: Qt meldet dann die Ansicht als Fokus,
    // geschrieben wird aber im Feld im Panel
    while (auto view = qobject_cast<QGraphicsView*>(f)) {
        auto proxy = view->scene() ? dynamic_cast<QGraphicsProxyWidget*>(view->scene()->focusItem()) : nullptr;
        f = proxy && proxy->widget() ? proxy->widget()->focusWidget() : nullptr;
    }
    if (!f || !f->isVisible()) {
        return false;
    }
    if (qobject_cast<QTextEdit*>(f) || qobject_cast<QPlainTextEdit*>(f)) {
        return true;
    }
    return qobject_cast<QLineEdit*>(f) && !qobject_cast<QAbstractSpinBox*>(f->parentWidget());
}

/// Tasten am Grafiktablett tun, was in Einstellungen › Tablett steht (TabletKeys.h): einen Befehl ausführen, oder die
/// Ansicht drehen/verschieben, solange die Taste gedrückt ist (wie die Maustaste, mit der der Navigationsstil das tut).
/// Tasten am Tablett liest der TouchpadReader, die Stift-Tasten kommen von Qt (Mitte = untere, Rechts = obere).
/// Belegt KDE dieselben Tasten noch, überhört MyCAD das: das Tastenkürzel direkt nach einer selbst gelesenen
/// Tablett-Taste, die Maustaste einer Stift-Taste, solange der Stift in Reichweite ist. Andere Programme bekommen die
/// KDE-Belegung weiter.
/// ponytail: angenommen, die selbst gelesene Taste kommt vor dem Kürzel von KWin an (KWin reicht es erst weiter);
/// eine echte Taste der Tastatur in den 150 ms danach geht verloren. Kommt das Kürzel je zuerst: Tasten kurz zurückhalten.
/// Welche Stift-Taste Qt als Mitte meldet, hängt an KDE; die Seite zeigt beim Drücken, welche Zeile es ist.
class TabletActions: public QObject
{
public:
    static TabletActions& instance()
    {
        static TabletActions actions;
        return actions;
    }

    void key(const std::string& key, bool down, bool pad)
    {
        if (pad) {
            quiet.start();
        }
        if (tabletPad().listener) {
            tabletPad().listener(key, down);  // Einstellungen offen: nur zeigen, welche Taste es ist
            return;
        }
        using Gui::Shell::TabletKeys::Kind;
        const auto& a = Gui::Shell::TabletKeys::actionFor(Gui::Shell::TabletKeys::parse(myParams()->GetASCII("TabletKeys", "")), key);
        if (a.kind == Kind::Command && down) {
            run(a.command);
        }
        else if (a.kind == Kind::Hold) {
            run(a.command);  // umschalten beim Drücken, zurück beim Loslassen
        }
        else if ((a.kind == Kind::Rotate || a.kind == Kind::Pan) && down) {
            beginDrag(a.kind == Kind::Rotate);
        }
        else if ((a.kind == Kind::Rotate || a.kind == Kind::Pan) && !down) {
            endDrag();
        }
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (sending) {
            return false;
        }
        switch (event->type()) {
            case QEvent::TabletEnterProximity:
                nearPen = true;
                return false;
            case QEvent::TabletLeaveProximity:
                nearPen = false;
                return false;
            case QEvent::ShortcutOverride:
            case QEvent::KeyPress:
            case QEvent::KeyRelease:
                if (quiet.isValid() && quiet.elapsed() < 150) {
                    event->accept();  // das KDE-Kürzel der Tablett-Taste: weder als Kürzel noch als Taste
                    return true;
                }
                return false;
            case QEvent::TabletPress:
            case QEvent::TabletRelease:
            case QEvent::MouseButtonPress:
            case QEvent::MouseButtonRelease:
                return button(obj, event);
            case QEvent::TabletMove:
            case QEvent::MouseMove:
                return move(obj, event);
            default:
                return false;
        }
    }

private:
    TabletActions()
    {
        qApp->installEventFilter(this);
    }

    static void run(const char* name)
    {
        if (Gui::Command* cmd = Gui::Application::Instance->commandManager().getCommandByName(name)) {
            cmd->invoke(0);  // prüft selbst, ob der Befehl gerade geht (Scribble-Befehle nur im Scribble)
        }
    }

    static QPointF globalOf(QEvent* event)
    {
        return event->type() == QEvent::TabletPress || event->type() == QEvent::TabletRelease || event->type() == QEvent::TabletMove
            ? static_cast<QTabletEvent*>(event)->globalPosition()
            : static_cast<QMouseEvent*>(event)->globalPosition();
    }

    /// Stift-Taste gedrückt/losgelassen: als Taste melden statt als Maustaste (sofern belegt oder die Seite offen ist)
    bool button(QObject* obj, QEvent* event)
    {
        const bool tablet = event->type() == QEvent::TabletPress || event->type() == QEvent::TabletRelease;
        const Qt::MouseButton b = tablet ? static_cast<QTabletEvent*>(event)->button() : static_cast<QMouseEvent*>(event)->button();
        if ((b == Qt::MiddleButton || b == Qt::RightButton) && (tablet || nearPen)) {
            const std::string which = b == Qt::MiddleButton ? "penLow" : "penHigh";
            const bool down = event->type() == QEvent::TabletPress || event->type() == QEvent::MouseButtonPress;
            using Gui::Shell::TabletKeys::Kind;
            const auto& a = Gui::Shell::TabletKeys::actionFor(Gui::Shell::TabletKeys::parse(myParams()->GetASCII("TabletKeys", "")), which);
            if (a.kind == Kind::None && !tabletPad().listener) {
                return false;  // Nichts: wie bisher (KDE/Qt machen daraus eine Maustaste)
            }
            if (down != bool(penHeld & b)) {  // Tablett- und Mausereignis derselben Taste: einmal
                penHeld.setFlag(b, down);
                penHolding.setFlag(b, down && a.kind == Kind::Hold && !tabletPad().listener);
                key(which, down, false);
            }
            event->accept();
            return true;
        }
        if (!tablet || !(static_cast<QTabletEvent*>(event)->buttons() & penHolding)) {
            return false;  // sonst bleibt es, wie Qt es meldet: Spitze mit Seitentaste ist Navigation, kein Strich
        }
        // Spitze aufsetzen, während eine Stift-Taste gehalten ist (Radierer, solange gedrückt): ohne die Stift-Taste
        // weiterreichen, sonst hielte das Scribble es für Navigation
        strip(obj, static_cast<QTabletEvent*>(event));
        return true;
    }

    bool move(QObject* obj, QEvent* event)
    {
        const QPointF global = globalOf(event);
        if (dragButton == Qt::NoButton) {
            if (isViewport(obj)) {  // 3D-Ansicht unter dem Zeiger merken (QCursor::pos() ist unter Wayland unzuverlässig)
                view = static_cast<QWidget*>(obj);
                pos = view->mapFromGlobal(global);
            }
            if (event->type() == QEvent::TabletMove && (static_cast<QTabletEvent*>(event)->buttons() & penHolding)) {
                strip(obj, static_cast<QTabletEvent*>(event));
                return true;
            }
            return false;
        }
        // Ansicht drehen/verschieben: jede Bewegung (Stift in der Luft oder Maus) zieht mit der Taste des Stils
        if (view) {
            pos = view->mapFromGlobal(global);
            send(QEvent::MouseMove);
        }
        event->accept();
        return true;
    }

    void strip(QObject* obj, QTabletEvent* te)
    {
        QTabletEvent copy(te->type(), te->pointingDevice(), te->position(), te->globalPosition(), te->pressure(),
                          te->xTilt(), te->yTilt(), te->tangentialPressure(), te->rotation(), te->z(), te->modifiers(),
                          te->button(), te->buttons() & ~penHolding);
        sending = true;
        QCoreApplication::sendEvent(obj, &copy);
        sending = false;
        te->setAccepted(copy.isAccepted());
    }

    void beginDrag(bool rotate)
    {
        const std::string style = viewParams()->GetASCII("NavigationStyle", "Gui::RevitNavigationStyle");
        Gui::Shell::TabletKeys::Drag d;
        for (const Style& s : Styles) {
            if (style == s.type) {
                d = Gui::Shell::TabletKeys::drag(rotate ? s.rotate : s.pan);
            }
        }
        if (!d.ok || !view || dragButton != Qt::NoButton) {
            return;
        }
        dragButton = d.button == 'L' ? Qt::LeftButton : d.button == 'M' ? Qt::MiddleButton : Qt::RightButton;
        dragModifiers = Qt::KeyboardModifiers().setFlag(Qt::ShiftModifier, d.shift).setFlag(Qt::ControlModifier, d.ctrl)
                            .setFlag(Qt::AltModifier, d.alt);
        send(QEvent::MouseButtonPress);
    }

    void endDrag()
    {
        if (dragButton != Qt::NoButton) {
            if (view) {
                send(QEvent::MouseButtonRelease);
            }
            dragButton = Qt::NoButton;
        }
    }

    void send(QEvent::Type type)
    {
        const Qt::MouseButton b = type == QEvent::MouseMove ? Qt::NoButton : dragButton;
        const Qt::MouseButtons held = type == QEvent::MouseButtonRelease ? Qt::NoButton : Qt::MouseButtons(dragButton);
        QMouseEvent event(type, pos, view->mapToGlobal(pos), b, held, dragModifiers);
        sending = true;
        QApplication::sendEvent(view, &event);
        sending = false;
    }

    QElapsedTimer quiet;  ///< seit der letzten selbst gelesenen Tablett-Taste
    bool nearPen = false;
    Qt::MouseButtons penHeld;
    Qt::MouseButtons penHolding;  ///< davon mit "…, solange gedrückt": Spitze aufsetzen zeichnet bzw. radiert dann
    QPointer<QWidget> view;
    QPointF pos;
    Qt::MouseButton dragButton = Qt::NoButton;
    Qt::KeyboardModifiers dragModifiers;
    bool sending = false;
};

void tabletKey(const std::string& key, bool down, bool pad)
{
    TabletActions::instance().key(key, down, pad);
}

/// Modifier-Taste -> Modifier (sonst NoModifier)
Qt::KeyboardModifier modifierOf(int key)
{
    switch (key) {
        case Qt::Key_Shift:
            return Qt::ShiftModifier;
        case Qt::Key_Control:
            return Qt::ControlModifier;
        case Qt::Key_Alt:
            return Qt::AltModifier;
        case Qt::Key_Meta:
            return Qt::MetaModifier;
        default:
            return Qt::NoModifier;
    }
}
}  // namespace

void MouseKeyMapper::send(int type, Qt::MouseButton button)
{
    // Wie cad.helper: gehaltene Modifier-Tasten bleiben gedrückt (Shift als Mitte = Shift + Mitte, im Fusion-Stil
    // also Drehen). Während des Tastendrucks kennt Qt den Modifier noch nicht, daher selbst ergänzen.
    Qt::KeyboardModifiers mods = QApplication::keyboardModifiers() | heldModifiers;
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
    const Qt::KeyboardModifier modifier = m ? modifierOf(m->key) : Qt::NoModifier;
    // Zeiger über dem 3D-Fenster, aber seit dem Verlassen nicht bewegt: aktuelle Position nehmen
    if (m && !hover) {
        QWidget* under = QApplication::widgetAt(QCursor::pos());
        if (under && isViewport(under)) {
            hover = under;
            hoverPos = under->mapFromGlobal(QCursor::pos());
        }
    }
    // nur über dem 3D-Fenster und nicht, während Text geschrieben wird
    const bool releasing = m && event->type() == QEvent::KeyRelease && (held & m->button);  // nie hängen lassen
    if (!m || !hover || ((QApplication::activeModalWidget() || typing()) && !releasing)) {
        return false;
    }
    if (modifier != Qt::NoModifier) {
        // Modifier wie bei cad.helper nicht verschlucken: das Programm sieht Shift weiterhin
        if (event->type() == QEvent::KeyPress && !ke->isAutoRepeat()) {
            heldModifiers |= modifier;
        }
        else if (event->type() == QEvent::KeyRelease && !ke->isAutoRepeat()) {
            heldModifiers &= ~modifier;
        }
        if (event->type() == QEvent::ShortcutOverride) {
            return false;
        }
    }
    if (event->type() == QEvent::ShortcutOverride) {
        event->accept();  // Taste als KeyPress zustellen statt als Tastenkürzel auslösen
        return true;
    }
    if (ke->isAutoRepeat()) {
        return modifier == Qt::NoModifier;
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
    return modifier == Qt::NoModifier;  // Modifier weiterreichen, andere Tasten verschlucken
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
    // Drehen um die Mitte des Körpers unter dem Cursor als Standard (einmalig, eigene Wahl bleibt danach)
    if (!myParams()->GetBool("RotationDefaultBody", false)) {
        viewParams()->SetInt("RotationMode", 3);
        myParams()->SetBool("RotationDefaultBody", true);
    }
    // Skizzen ohne eigene Innenflächen: sonst fangen sie den Klick ab und statt des gewählten Profils
    // (Design::Profiles) wird die ganze Skizze extrudiert
    App::GetApplication()
        .GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/Sketcher")
        ->SetBool("MakeInternals", false);
    MouseKeyMapper::instance();
    Trackpad::install();
    TouchpadReader::install();
    TabletActions::instance();
}

namespace
{
/// Switch (MyStyle § 9.3): 38 × 22, weißer Knopf 18 mit Schatten, aus fill.secondary, an Grün; der Knopf wird beim
/// Drücken 22 breit und gleitet mit 280 ms OutBack
class Switch: public QAbstractButton
{
public:
    explicit Switch(bool on)
    {
        setCheckable(true);
        setChecked(on);
        setCursor(Qt::PointingHandCursor);
        setFocusPolicy(Qt::TabFocus);  // Fokusring nur bei Tastaturbedienung
        setFixedSize(Token::SwitchWidth + 4, Token::SwitchHeight + 4);  // 2 px rundum für den Fokusring
        position = on ? 1 : 0;
        QObject::connect(&anim, &QVariantAnimation::valueChanged, this, [this](const QVariant& v) {
            position = v.toReal();
            update();
        });
        QObject::connect(this, &QAbstractButton::toggled, this, [this](bool checked) {
            const Theme& t = theme();
            anim.stop();
            anim.setDuration(t.duration(280));
            QEasingCurve curve(t.reduceMotion ? QEasingCurve::OutCubic : QEasingCurve::OutBack);
            curve.setOvershoot(1.3);
            anim.setEasingCurve(curve);
            anim.setStartValue(position);
            anim.setEndValue(checked ? 1.0 : 0.0);
            anim.start();
        });
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        const Theme& t = theme();
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setOpacity(isEnabled() ? 1.0 : 0.4);  // deaktiviert (MyStyle § 9)
        const QRectF track = QRectF(rect()).adjusted(2, 2, -2, -2);
        if (hasFocus()) {
            p.setPen(QPen(t.focusRing, 2));
            p.setBrush(Qt::NoBrush);
            p.drawRoundedRect(QRectF(rect()).adjusted(1, 1, -1, -1), height() / 2.0 - 1, height() / 2.0 - 1);
        }
        p.setPen(Qt::NoPen);
        p.setBrush(isChecked() ? t.green : t.fillSecondary);
        p.drawRoundedRect(track, track.height() / 2, track.height() / 2);
        const qreal d = Token::SwitchKnob, w = isDown() ? 22 : d, pad = (track.height() - d) / 2;
        const qreal x = track.left() + pad + std::clamp(position, -0.1, 1.1) * (track.width() - 2 * pad - w);
        const QRectF knob(x, track.top() + pad, w, d);
        p.setBrush(QColor(0, 0, 0, 64));  // elevation.knob (0, 2, 4, 25 %), vereinfacht
        p.drawRoundedRect(knob.translated(0, 1).adjusted(-0.5, 0, 0.5, 1), d / 2, d / 2);
        p.setBrush(QColor(Qt::white));
        p.drawRoundedRect(knob, d / 2, d / 2);
    }
    void mousePressEvent(QMouseEvent* e) override
    {
        QAbstractButton::mousePressEvent(e);
        update();  // Knopf wird breit
    }

private:
    qreal position = 0;
    QVariantAnimation anim;
};

/// Ereignis eines anderen Objekts beobachten (z. B. Aufklapp-Liste wird geschlossen)
class EventHook: public QObject
{
public:
    EventHook(QObject* target, QEvent::Type type, std::function<void()> fn)
        : QObject(target)
        , type(type)
        , fn(std::move(fn))
    {
        target->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject*, QEvent* event) override
    {
        if (event->type() == type) {
            fn();
        }
        return false;
    }

private:
    QEvent::Type type;
    std::function<void()> fn;
};

/// Rahmenloses Fenster am Kopf verschieben
class DragArea: public QWidget
{
protected:
    void mousePressEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton && window()->windowHandle()) {
            window()->windowHandle()->startSystemMove();
        }
    }
};

/// Bedienung als Tasten-Chips: "Shift+Middle drag | Scroll" -> [Shift] + [Middle drag]  or  [Scroll]
QWidget* chips(const QString& spec)
{
    auto w = new QWidget;
    auto lay = new QHBoxLayout(w);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(4);
    const QStringList alternatives = spec.split(QStringLiteral(" | "));
    for (int i = 0; i < alternatives.size(); ++i) {
        if (i > 0) {
            auto orLabel = new QLabel(T("or"));
            orLabel->setObjectName(QStringLiteral("Secondary"));
            lay->addSpacing(2);
            lay->addWidget(orLabel);
            lay->addSpacing(2);
        }
        const QStringList keys = alternatives[i].split(QLatin1Char('+'));
        for (int k = 0; k < keys.size(); ++k) {
            if (k > 0) {
                auto plus = new QLabel(QStringLiteral("+"));
                plus->setObjectName(QStringLiteral("Secondary"));
                lay->addWidget(plus);
            }
            auto chip = new QLabel(T(keys[k].trimmed()));
            chip->setObjectName(QStringLiteral("Chip"));
            setTextStyle(chip, Text::Caption);
            chip->setFixedHeight(Token::Chip);
            lay->addWidget(chip);
        }
    }
    lay->addStretch();
    return w;
}

/// Stylesheet des Einstellungsfensters (MyStyle § 9): Fenster auf dem Backdrop, Karten aus Material
QString settingsStyle()
{
    return themed(QStringLiteral(R"(
* { color: @labelPrimary; }
QDialog#Settings { background: transparent; }
QFrame#Window { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 @backgroundTop, stop:1 @backgroundBottom);
    border: 1px solid @glassPopupBorder; border-radius: 24px; }
QFrame#Card { background: @materialFill; border: 1px solid @materialBorder; border-radius: 20px; }
QFrame#Separator { background: @separator; border: none; min-height: 1px; max-height: 1px; }
QLabel#Section, QLabel#Secondary, QLabel#Hint { color: @labelSecondary; }
QLabel#Chip { background: @fillTertiary; border-radius: 12px; padding: 0 10px; }
QWidget#KeyRow[pressed="true"] { background: @fillSecondary; border-radius: 8px; }
QWidget#KeyRow[pressed="true"] QLabel#Chip { background: @accent; color: @labelOnAccent; }
QLabel#Pressed { color: @accentText; }
QComboBox { background: transparent; border: 2px solid transparent; border-radius: 8px; padding: 2px 8px; min-height: 22px; color: @labelSecondary; }
QComboBox:hover { background: @fillTertiary; }
QComboBox:focus { border-color: @focusRing; }
QComboBox::drop-down { border: none; width: 24px; }
QComboBox::down-arrow { image: url(:/mycad/icons/Chevrons_UpDown.svg); width: 16px; height: 16px; }
QComboBox QAbstractItemView { background: @glassOpaqueTop; border: 1px solid @glassPopupBorder; padding: 4px; outline: 0;
    selection-background-color: @accent; selection-color: @labelOnAccent; }
/* Textfeld (9.3): 30 hoch, r 8, fill.tertiary, Fokus 2-px-Ring; Wert per Tippen, Pfeiltasten oder Mausrad */
QAbstractSpinBox { background: @fillTertiary; border: 2px solid transparent; border-radius: 8px; padding: 2px 8px; min-height: 22px;
    selection-background-color: @accent; selection-color: @labelOnAccent; }
QAbstractSpinBox:focus { border-color: @focusRing; }
/* subcontrol-origin: sonst schrumpft bei Feldern ohne Knöpfe (NoButtons, z. B. die Wertfelder in der Skizze) das
   Eingabefeld auf 1 px, sobald das Feld Rand oder Innenabstand hat: der Text ist unsichtbar */
QAbstractSpinBox::up-button, QAbstractSpinBox::down-button { width: 0; border: none; subcontrol-origin: border; }
QSlider { min-height: 24px; }
QSlider::groove:horizontal { height: 4px; background: @fillSecondary; border-radius: 2px; }
QSlider::sub-page:horizontal { background: @accent; border-radius: 2px; }
QSlider::handle:horizontal { background: @knob; border: 1px solid @separator; width: 19px; height: 19px; margin: -9px 0; border-radius: 10px; }
QSlider::handle:horizontal:focus { border: 2px solid @focusRing; }
QToolButton#CloseSettings, QToolButton#Remove { background: @fillTertiary; border: 2px solid transparent; border-radius: 14px; }
QToolButton#Remove { background: transparent; }
QToolButton#CloseSettings:hover, QToolButton#Remove:hover { background: @fillSecondary; }
QToolButton#CloseSettings:focus, QToolButton#Remove:focus { border-color: @focusRing; }
)"));
}
/// Tablett und Stift als Zeichnung (Einstellungen › Tablett, Hero-Karte): die gedrückte Taste in Akzentfarbe, die
/// Taste der Zeile unter der Maus mit Ring. Maße wie im Prototyp.
/// MyStyle: kein Token für Maße der Geräte-Zeichnung
class TabletPicture: public QWidget
{
public:
    TabletPicture()
    {
        setFixedSize(260, 150);  // der schräge Stift reicht oben bis x 258
        setAccessibleName(T("Tablet and pen"));
    }
    int keys = 0;          ///< Tasten am Tablett
    std::string pressed;   ///< "pad3", "penLow" …
    std::string hovered;

protected:
    void paintEvent(QPaintEvent*) override
    {
        const Theme& t = theme();
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        const auto key = [&](const QRectF& r, const std::string& id, int radius, const QString& label) {
            p.setPen(id == hovered ? QPen(t.accentText, 2) : Qt::NoPen);
            p.setBrush(id == pressed ? t.accent : t.fillPrimary);
            p.drawRoundedRect(r, radius, radius);
            if (!label.isEmpty()) {
                p.setPen(id == pressed ? t.labelOnAccent : t.labelPrimary);
                p.setFont(textFont(Text::Section));
                p.drawText(r, Qt::AlignCenter, label);
            }
        };
        const QRectF tablet(0.5, 11.5, 196, 128);
        p.setPen(QPen(t.separator, 1));
        p.setBrush(t.gray5);
        p.drawRoundedRect(tablet, Token::RadiusTile, Token::RadiusTile);
        p.setBrush(Qt::NoBrush);
        p.drawRoundedRect(tablet.adjusted(36, 12, -12, -12), Token::RadiusControl, Token::RadiusControl);
        const double step = keys > 0 ? std::min(19.0, (tablet.height() - 16) / keys) : 0;
        for (int n = 1; n <= keys; ++n) {
            key(QRectF(10, tablet.top() + 8 + (n - 1) * step, 18, std::min(16.0, step - 3)), Gui::Shell::TabletKeys::padKey(n),
            Token::RadiusCheckbox, QString::number(n));
        }
        // Stift, leicht schräg, mit unterer und oberer Taste
        p.translate(217, 142);
        p.rotate(14);
        p.setPen(Qt::NoPen);
        p.setBrush(t.fillPrimary);
        p.drawRoundedRect(QRectF(-7, -140, 14, 140), 7, 7);
        key(QRectF(-5, -112, 10, 18), "penHigh", 4, QString());
        key(QRectF(-5, -90, 10, 18), "penLow", 4, QString());
    }
};
}  // namespace

void Gui::Shell::showSettings()
{
    QDialog dlg(Gui::getMainWindow(), Qt::Dialog | Qt::FramelessWindowHint);
    dlg.setAttribute(Qt::WA_TranslucentBackground);
    dlg.setObjectName(QStringLiteral("Settings"));
    dlg.setWindowTitle(T("Settings"));
    // Inhalt höchstens size.contentMaxWidth breit (W-4), Fenster 12 rundum (Fenster r 32 − 12 = Karte r 20)
    dlg.setMinimumWidth(Token::ContentMaxWidth + 2 * Token::WindowInset);
    std::vector<std::function<void()>> restyle;  // bei Wechsel Hell/Dunkel/Kontrast: alles neu einfärben
    auto updateStyle = [&dlg, &restyle] {
        dlg.setStyleSheet(settingsStyle());
        for (const auto& fn : restyle) {
            fn();
        }
    };

    auto outer = new QVBoxLayout(&dlg);
    outer->setContentsMargins(0, 0, 0, 0);
    auto window = new QFrame;
    window->setObjectName(QStringLiteral("Window"));
    outer->addWidget(window);
    auto lay = new QVBoxLayout(window);
    lay->setContentsMargins(Token::WindowInset, Token::WindowInset, Token::WindowInset, Token::WindowInset);
    lay->setSpacing(8);

    // Kopf: Titel (zum Verschieben), Bereiche, Schließen
    auto head = new DragArea;
    auto headLay = new QHBoxLayout(head);
    headLay->setContentsMargins(Token::WindowInset, 0, 0, 0);
    auto title = new QLabel(T("Settings"));
    setTextStyle(title, Text::Title1);
    headLay->addWidget(title);
    headLay->addStretch();
    auto pages = new QStackedWidget;
    auto pageSwitch = segmented({T("General"), T("Navigation"), T("Keys"), T("Tablet")}, 0,
                                [pages](int i) { pages->setCurrentIndex(i); });
    pageSwitch->setProperty("backdrop", true);  // steht auf dem Backdrop: Material statt Fill
    headLay->addWidget(pageSwitch);
    headLay->addSpacing(8);
    auto close = new QToolButton;  // schließen wie bei macOS-Panels; Esc schließt ebenfalls
    close->setObjectName(QStringLiteral("CloseSettings"));
    close->setIcon(designIcon(QStringLiteral("Window_Close"), &Theme::labelSecondary));
    close->setIconSize(QSize(Token::IconM, Token::IconM));
    close->setFixedSize(28, 28);
    close->setToolTip(T("Close"));
    close->setAccessibleName(T("Close"));
    close->setCursor(Qt::PointingHandCursor);
    QObject::connect(close, &QToolButton::clicked, &dlg, &QDialog::accept);
    headLay->addWidget(close);
    lay->addWidget(head);
    lay->addWidget(pages);

    // Karten (Material, r 20, innen 16/4) mit Zeilen: Label links, Bedienelement rechts, Trennlinie oberhalb
    struct Card
    {
        QVBoxLayout* rows;
        bool first = true;
    };
    auto addCard = [&restyle](QVBoxLayout* page, const QString& heading) {
        if (!heading.isEmpty()) {
            auto label = sectionLabel(heading);
            label->setContentsMargins(16, 8, 0, 4);
            page->addWidget(label);
        }
        auto frame = new QFrame;
        frame->setObjectName(QStringLiteral("Card"));
        auto rows = new QVBoxLayout(frame);
        rows->setContentsMargins(16, 4, 16, 4);
        rows->setSpacing(0);
        page->addWidget(frame);
        // Kartenschatten elevation.card (0, 4, 24, 5 %) nur hell, im Dunkeln keiner (D-2)
        restyle.push_back([frame] {
            if (theme().dark) {
                frame->setGraphicsEffect(nullptr);
                return;
            }
            auto shadow = new QGraphicsDropShadowEffect;
            shadow->setBlurRadius(24);
            shadow->setOffset(0, 4);
            shadow->setColor(QColor(0, 0, 0, 13));
            frame->setGraphicsEffect(shadow);
        });
        return std::make_shared<Card>(Card {rows});
    };
    auto addRow = [](const std::shared_ptr<Card>& c, const QString& label, QWidget* field, bool wide = false) {
        auto row = new QWidget;  // mit eigener Trennlinie oben: eine verborgene Zeile nimmt ihre Linie mit
        auto v = new QVBoxLayout(row);
        v->setContentsMargins(0, 0, 0, 0);
        v->setSpacing(0);
        if (!c->first) {  // Trennlinie nur unter einer Zeile darüber
            auto line = new QFrame;
            line->setObjectName(QStringLiteral("Separator"));
            v->addWidget(line);
        }
        c->first = false;
        auto h = new QHBoxLayout;
        v->addLayout(h);
        h->setContentsMargins(0, 8, 0, 8);
        h->setSpacing(12);
        if (!label.isEmpty()) {
            auto text = new QLabel(label);
            setTextStyle(text, Text::Body);
            text->setWordWrap(true);  // umbrechen statt abschneiden (T-8, längere deutsche Texte)
            h->addWidget(text, 1);
            if (field->accessibleName().isEmpty()) {
                field->setAccessibleName(label);
            }
        }
        else {
            h->addStretch(wide ? 0 : 1);
        }
        h->addWidget(field, wide ? 1 : 0);
        c->rows->addWidget(row);
        return row;
    };
    auto hint = [](const QString& text) {
        auto label = new QLabel(text);
        label->setObjectName(QStringLiteral("Hint"));
        label->setWordWrap(true);
        label->setContentsMargins(16, 0, 16, 0);
        return label;
    };
    auto view = viewParams();
    auto toggle = [&](const std::shared_ptr<Card>& c, const QString& label, bool on, std::function<void(bool)> changed) {
        auto sw = new Switch(on);
        QObject::connect(sw, &QAbstractButton::toggled, sw, changed);
        addRow(c, label, sw);
    };
    auto viewToggle = [&](const std::shared_ptr<Card>& c, const QString& label, const char* param, bool def) {
        toggle(c, label, view->GetBool(param, def), [view, param](bool on) { view->SetBool(param, on); });
    };
    auto myToggle = [&](const std::shared_ptr<Card>& c, const QString& label, const char* param, bool on) {
        toggle(c, label, on, [param, updateStyle](bool v) {
            myParams()->SetBool(param, v);
            Gui::Shell::applyAppearance();
            updateStyle();
        });
    };
    /// rollt, wenn das Fenster niedriger ist als die Seite (sonst quetschte Qt die Zeilen, Controls lagen auf den
    /// Trennlinien); will so hoch sein wie die Seite
    struct PageScroll: QScrollArea
    {
        QSize sizeHint() const override
        {
            return widget() ? widget()->sizeHint() : QScrollArea::sizeHint();
        }
    };
    auto newPage = [pages] {
        auto scroll = new PageScroll;
        scroll->setWidgetResizable(true);
        scroll->setFrameShape(QFrame::NoFrame);
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll->viewport()->setAutoFillBackground(false);
        auto page = new QWidget;
        auto l = new QVBoxLayout(page);
        l->setContentsMargins(0, 0, 0, 0);
        l->setSpacing(4);
        scroll->setWidget(page);
        pages->addWidget(scroll);
        return l;
    };

    // --- Seite General: Darstellung, Bedienungshilfen, Sprache, Projektordner ---
    QVBoxLayout* general = newPage();
    const Theme& t = theme();
    auto lookCard = addCard(general, T("Display"));
    addRow(lookCard, T("Color scheme"),
           segmented({T("Automatic"), T("Light"), T("Dark")}, int(myParams()->GetInt("Appearance", 0)), [updateStyle](int i) {
               myParams()->SetInt("Appearance", i);
               Gui::Shell::applyAppearance();
               updateStyle();
           }));

    // Liquid Glass (MyStyle GQ-2): stufenlos von Ultra Clear über Default bis Tinted, wirkt sofort
    auto glass = new QWidget;
    auto glassLay = new QGridLayout(glass);
    glassLay->setContentsMargins(0, 0, 0, 0);
    glassLay->setHorizontalSpacing(0);
    glassLay->setVerticalSpacing(2);
    auto level = new QSlider(Qt::Horizontal);
    level->setRange(0, 100);
    level->setValue(int(std::lround(t.glassLevel * 100)));
    level->setFixedWidth(260);
    level->setAccessibleName(T("Liquid Glass"));
    glassLay->addWidget(level, 0, 0, 1, 3);
    const std::pair<QString, Qt::Alignment> stops[] = {{T("Ultra Clear"), Qt::AlignLeft},
                                                      {T("Default"), Qt::AlignHCenter},
                                                      {T("Tinted"), Qt::AlignRight}};
    for (int i = 0; i < 3; ++i) {
        auto label = new QLabel(stops[i].first);
        label->setObjectName(QStringLiteral("Secondary"));
        setTextStyle(label, Text::Caption);
        glassLay->addWidget(label, 1, i, stops[i].second);
    }
    QObject::connect(level, &QSlider::valueChanged, level, [](int v) {
        // nahe der Mitte rastet der Standard ein
        myParams()->SetFloat("GlassLevel", std::abs(v - 50) <= 2 ? 0.5 : v / 100.0);
        reloadTheme();
        for (QWidget* w : QApplication::allWidgets()) {
            w->update();
        }
        for (auto view : Gui::getMainWindow()->findChildren<QGraphicsView*>()) {
            if (view->scene()) {
                view->scene()->update();
            }
        }
    });
    addRow(lookCard, T("Liquid Glass"), glass);
    auto material = new QComboBox;  // Pop-up-Button: mehr Materialien, als ein Segmented Control fasst (≤ 7)
    {
        // nach Gruppen, mit Trennlinie dazwischen; die Nummer des Materials steht in den Daten des Eintrags
        const QSize thumb(Token::IconL, Token::IconL);
        const auto list = Gui::Shell::bodyMaterialList();
        QStringList categories;
        for (const auto& entry : list) {
            if (!categories.contains(QLatin1String(entry.category))) {
                categories << QLatin1String(entry.category);
            }
        }
        for (const QString& category : categories) {
            if (material->count() > 0) {
                material->insertSeparator(material->count());
            }
            for (int i = 0; i < int(list.size()); ++i) {
                if (category == QLatin1String(list[i].category)) {
                    material->addItem(Gui::Shell::materialPreview(i, thumb.width(), material->devicePixelRatioF()), T(list[i].name), i);
                }
            }
        }
        material->setIconSize(thumb);
        material->setMaxVisibleItems(16);
    }
    material->setCurrentIndex(material->findData(int(myParams()->GetInt("BodyMaterial", Gui::Shell::DefaultBodyMaterial))));
    QObject::connect(material, &QComboBox::currentIndexChanged, [material](int i) {
        Gui::Shell::setBodyMaterial(material->itemData(i).toInt());
    });
    // Materialien und Licht der Körper (BodyShading.h): jedes einzeln abschaltbar, wenn es beim Arbeiten stört; wirkt sofort
    auto materialCard = addCard(general, T("Materials and Light"));
    addRow(materialCard, T("Body material"), material);
    // Studio: Licht von links oben, jede Fläche hat ihren Tonwert (CAD). Raum: weich wie die Browser-Vorschau (three.js)
    addRow(materialCard, T("Lighting"), segmented({T("Studio"), T("Room")}, int(myParams()->GetInt("Lighting", 0)),
                                                  [](int i) { myParams()->SetInt("Lighting", i); }));
    auto realistic = new Switch(myParams()->GetBool("RealisticMaterials", true));
    addRow(materialCard, T("Realistic materials"), realistic);
    std::vector<Switch*> needsRealistic;  // ohne realistische Materialien wirkungslos: abgeblendet (MyStyle: 0,4)
    for (const auto& [label, param] : {std::pair {"Reflections", "Reflections"}, std::pair {"Relief and end grain", "SurfaceDetail"}}) {
        auto sw = new Switch(myParams()->GetBool(param, true));
        sw->setEnabled(realistic->isChecked());
        QObject::connect(sw, &QAbstractButton::toggled, sw, [param = param](bool on) { myParams()->SetBool(param, on); });
        addRow(materialCard, T(label), sw);
        needsRealistic.push_back(sw);
    }
    QObject::connect(realistic, &QAbstractButton::toggled, realistic, [needsRealistic](bool on) {
        myParams()->SetBool("RealisticMaterials", on);  // BodyShading beobachtet die Parameter
        for (Switch* sw : needsRealistic) {
            sw->setEnabled(on);
        }
    });
    auto shadow = new Switch(myParams()->GetBool("ContactShadow", true));
    QObject::connect(shadow, &QAbstractButton::toggled, shadow, [](bool on) { myParams()->SetBool("ContactShadow", on); });
    addRow(materialCard, T("Contact shadow"), shadow);
    auto names = new Switch(myParams()->GetBool("ToolNames", false));
    QObject::connect(names, &QAbstractButton::toggled, [](bool on) { Gui::Shell::setToolNames(on); });
    addRow(lookCard, T("Show tool names"), names);
    myToggle(lookCard, T("Show grid"), "GroundGrid", myParams()->GetBool("GroundGrid", true));

    auto a11yCard = addCard(general, T("Accessibility"));
    myToggle(a11yCard, T("Increase contrast"), "IncreaseContrast", t.increaseContrast);
    myToggle(a11yCard, T("Reduce transparency"), "ReduceTransparency", t.reduceTransparency);
    myToggle(a11yCard, T("Reduce motion"), "ReduceMotion", t.reduceMotion);

    auto generalCard = addCard(general, T("General"));
    // Sprache: FreeCAD lädt seine Übersetzungen beim Start, die Oberfläche wird dabei neu aufgebaut
    auto restartHint = new QLabel(T("Takes effect after restarting MyCAD."));
    restartHint->setObjectName(QStringLiteral("Hint"));
    restartHint->setWordWrap(true);
    // eigene Schreibweise jeder Sprache (S-5)
    QWidget* restartRow = nullptr;
    addRow(generalCard, T("Language"),
           segmented({QStringLiteral("English"), QStringLiteral("Deutsch")}, Gui::Shell::language() == QLatin1String("German") ? 1 : 0,
                     [&restartRow](int i) {
                         Gui::Shell::setLanguage(i == 1 ? QStringLiteral("German") : QStringLiteral("English"));
                         restartRow->show();
                     }));
    restartRow = addRow(generalCard, QString(), restartHint, true);
    restartRow->hide();
    // Nur mit zwei GPUs etwas zu wählen. Beim Start gesetzt (main), daher erst nach einem Neustart wirksam; zurück auf
    // den Wert, mit dem MyCAD gerade läuft, braucht keinen
    if (QDir(QStringLiteral("/sys/class/drm")).entryList({QStringLiteral("card?"), QStringLiteral("card??")}, QDir::AllEntries).size() > 1) {
        static const int runningGpu = int(myParams()->GetInt("Gpu", 0));
        addRow(generalCard, T("Graphics card"),
               segmented({T("Dedicated"), T("Processor")}, int(myParams()->GetInt("Gpu", 0)), [&dlg](int i) {
                   myParams()->SetInt("Gpu", i);
                   if (i != runningGpu) {
                       QTimer::singleShot(0, &dlg, [&dlg] {
                           QMessageBox::information(&dlg, T("Restart MyCAD"),
                                                    T("The selected graphics card is used after you restart MyCAD."));
                       });
                   }
               }));
    }
    auto folder = new QPushButton;
    auto showFolder = [folder] {
        QString path = Gui::Shell::projectsFolder();
        folder->setText(path.replace(QDir::homePath(), QStringLiteral("~")));
    };
    showFolder();
    folder->setToolTip(T("Designs in this folder appear on the start page; Save starts here"));
    folder->setAutoDefault(false);
    QObject::connect(folder, &QPushButton::clicked, folder, [folder, showFolder] {
        const QString dir = QFileDialog::getExistingDirectory(folder->window(), T("Projects Folder"),
                                                              Gui::Shell::projectsFolder());
        if (!dir.isEmpty()) {
            myParams()->SetASCII("ProjectsFolder", dir.toUtf8().constData());
            App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                ->SetASCII("FileOpenSavePath", dir.toUtf8().constData());
            showFolder();
        }
    });
    addRow(generalCard, T("Projects folder"), folder);
    // Wie fein gekrümmte Flächen beim Export als STL/3MF in Dreiecke zerlegt werden (DesignExport.QUALITY)
    addRow(generalCard, T("Export resolution"),
           segmented({T("Coarse"), T("Normal"), T("Fine")}, int(myParams()->GetInt("ExportQuality", 1)),
                     [](int i) { myParams()->SetInt("ExportQuality", i); }));
    // Slicer für Drucken (Design_Print merkt sich die erste Wahl); zu wählen gibt es erst mit mehreren installierten
    QStringList slicers;
    try {
        Base::PyGILStateLocker lock;
        slicers = QString::fromStdString(Base::Interpreter().runStringWithKey(
                                             "import DesignExport\n_r = '\\n'.join(n for n, c in DesignExport.find_slicers())", "_r"))
                      .split(QLatin1Char('\n'), Qt::SkipEmptyParts);
    }
    catch (const Base::Exception&) {
    }
    if (slicers.size() > 1) {
        auto slicer = new QComboBox;
        slicer->addItems(slicers);
        slicer->setCurrentIndex(int(slicers.indexOf(QString::fromStdString(myParams()->GetASCII("Slicer", "")))));
        QObject::connect(slicer, &QComboBox::currentTextChanged, slicer,
                         [](const QString& name) { myParams()->SetASCII("Slicer", name.toStdString()); });
        addRow(generalCard, T("Slicer"), slicer);
    }
    // Spiel je Seite für die Passungen "3D-Druck eng/normal/locker" (Design::Fitting, Idee 4); je eine Zeile wie die
    // anderen Zahlenfelder: alle drei in einer Zeile ließen dem Label keinen Platz, es wurde abgeschnitten
    static const char* plays[][2] = {
        {"PrintFitTight", "Clearance tight"}, {"PrintFitNormal", "Clearance normal"}, {"PrintFitLoose", "Clearance loose"}};
    for (int i = 0; i < 3; ++i) {
        auto box = new QDoubleSpinBox;
        box->setRange(0, 1);
        box->setSingleStep(0.05);
        box->setDecimals(2);
        box->setSuffix(QStringLiteral(" mm"));
        box->setValue(myParams()->GetFloat(plays[i][0], 0.1 * (i + 1)));
        QObject::connect(box, &QDoubleSpinBox::valueChanged, box, [key = plays[i][0]](double v) { myParams()->SetFloat(key, v); });
        addRow(generalCard, T(plays[i][1]), box);
    }
    // Grenzen der Druckansicht (Design::printCheck): Überhang in Grad, kleinste Wand in mm
    for (const auto& [key, label, fallback, suffix, top] :
         {std::tuple {"OverhangAngle", "Overhang angle", 45.0, "°", 89.0}, std::tuple {"MinWall", "Minimum wall", 0.8, " mm", 10.0}}) {
        auto box = new QDoubleSpinBox;
        box->setRange(top > 50 ? 10 : 0.1, top);
        box->setDecimals(top > 50 ? 0 : 2);
        box->setSingleStep(top > 50 ? 5 : 0.1);
        box->setSuffix(QString::fromUtf8(suffix));
        box->setValue(myParams()->GetFloat(key, fallback));
        QObject::connect(box, &QDoubleSpinBox::valueChanged, box, [key](double v) { myParams()->SetFloat(key, v); });
        addRow(generalCard, T(label), box);
    }
    auto version = new QLabel(Gui::Shell::version());
    version->setTextInteractionFlags(Qt::TextSelectableByMouse);  // zum Kopieren in Fehlerberichte
    addRow(generalCard, T("Version"), version);
    general->addStretch();

    // --- Seite Navigation ---
    QVBoxLayout* nav = newPage();
    auto styleCard = addCard(nav, T("Mouse & Trackpad"));
    auto style = new QComboBox;
    const std::string current = view->GetASCII("NavigationStyle", "Gui::RevitNavigationStyle");
    for (const auto& s : Styles) {
        style->addItem(T(s.label), QString::fromLatin1(s.type));
        if (current == s.type) {
            style->setCurrentIndex(style->count() - 1);
        }
    }
    addRow(styleCard, T("Style"), style);

    // Vorschau: wie gedreht, geschoben, gezoomt und ausgewählt wird; folgt auch dem Überfahren der Liste
    auto help = new QWidget;
    auto helpLay = new QVBoxLayout(help);
    helpLay->setContentsMargins(0, 0, 0, 0);
    helpLay->setSpacing(6);
    addRow(styleCard, QString(), help, true);
    auto showHelp = [helpLay](int index) {
        if (index < 0 || index >= int(std::size(Styles))) {
            return;
        }
        while (QLayoutItem* item = helpLay->takeAt(0)) {
            delete item->widget();
            delete item;
        }
        // belegte Tasten (Leertaste = Mitte …) als zusätzliche Möglichkeit
        QStringList keyAlternatives[3];
        for (const auto& v : QJsonDocument::fromJson(QByteArray::fromStdString(myParams()->GetASCII("MouseKeys", "[]"))).array()) {
            const QJsonObject o = v.toObject();
            const QString mode = o.value(QStringLiteral("mode")).toString();
            if (mode != QLatin1String("hold") && mode != QLatin1String("toggle")) {
                continue;
            }
            for (int b = 0; b < 3; ++b) {
                if (o.value(QStringLiteral("button")).toString() == QLatin1String(Buttons[b].second)) {
                    keyAlternatives[b] << keyName(o.value(QStringLiteral("key")).toInt());
                }
            }
        }
        const char* dragNames[3] = {"Left drag", "Middle drag", "Right drag"};
        const Style& s = Styles[index];
        const std::pair<const char*, const char*> actions[] = {
            {"Nav_Rotate", s.rotate}, {"Nav_Pan", s.pan}, {"Nav_Zoom", s.zoom}, {"Nav_Select", s.select}};
        const char* names[] = {"Rotate", "Pan", "Zoom", "Select"};
        int i = 0;
        for (const auto& [icon, spec] : actions) {
            QString combos = QString::fromLatin1(spec);
            for (int b = 0; b < 3; ++b) {
                for (const QString& key : keyAlternatives[b]) {
                    for (const QString& alt : QString::fromLatin1(spec).split(QStringLiteral(" | "))) {
                        if (alt.contains(QLatin1String(dragNames[b])) && !alt.contains(QLatin1Char('+'))) {
                            combos += QStringLiteral(" | ") + key + QStringLiteral("+Move");
                        }
                        else if (alt.endsWith(QLatin1String(dragNames[b])) && alt.count(QLatin1Char('+')) == 1) {
                            combos += QStringLiteral(" | ") + alt.section(QLatin1Char('+'), 0, 0) + QLatin1Char('+')
                                + key + QStringLiteral("+Move");
                        }
                    }
                }
            }
            auto row = new QWidget;
            auto h = new QHBoxLayout(row);
            h->setContentsMargins(0, 0, 0, 0);
            h->setSpacing(10);
            auto glyph = new QLabel;
            glyph->setPixmap(designIcon(QString::fromLatin1(icon), &Theme::labelSecondary)
                                 .pixmap(QSize(Token::IconM, Token::IconM), glyph->devicePixelRatioF()));
            h->addWidget(glyph);
            auto name = new QLabel(T(names[i++]));
            name->setFixedWidth(86);
            h->addWidget(name);
            h->addWidget(chips(combos), 1);
            helpLay->addWidget(row);
            row->show();  // sonst erst verzögert sichtbar (Vorschau beim Überfahren der Liste)
        }
    };
    showHelp(style->currentIndex());
    restyle.push_back([style, showHelp] { showHelp(style->currentIndex()); });  // Symbole in der neuen Farbe
    QObject::connect(style, &QComboBox::highlighted, help, showHelp);
    QObject::connect(style, &QComboBox::currentIndexChanged, help, [style, view, showHelp](int i) {
        view->SetASCII("NavigationStyle", style->itemData(i).toString().toStdString());
        showHelp(i);
    });
    new EventHook(style->view(), QEvent::Hide, [style, showHelp] { showHelp(style->currentIndex()); });
    nav->addWidget(hint(T("On a trackpad: two fingers pan, three fingers rotate, pinch zooms. "
                          "Keys that act as mouse buttons are set up under Keys.")));

    auto viewCard = addCard(nav, T("View"));
    addRow(viewCard, T("Camera"),
           segmented({T("Orthographic"), T("Perspective")},
                     view->GetBool("Orthographic", true) ? 0 : 1, [view](int i) {
                         view->SetBool("Perspective", i == 1);
                         view->SetBool("Orthographic", i == 0);  // wirkt sofort auf alle Ansichten
                     }));
    auto orbit = new QComboBox;
    orbit->addItems({T("Turntable (Z stays up)"), T("Trackball (free)"),
                     T("Free turntable"), T("Trackball classic"),
                     T("Rounded arcball")});
    orbit->setCurrentIndex(static_cast<int>(view->GetInt("OrbitStyle", 0)));
    QObject::connect(orbit, &QComboBox::currentIndexChanged, [view](int i) { view->SetInt("OrbitStyle", i); });
    addRow(viewCard, T("Rotate"), orbit);
    auto center = new QComboBox;
    center->addItems({T("Window center"), T("Point under the cursor"),
                      T("Center of all bodies"), T("Center of the body under the cursor")});
    center->setCurrentIndex(static_cast<int>(view->GetInt("RotationMode", 3)));
    QObject::connect(center, &QComboBox::currentIndexChanged, [view](int i) { view->SetInt("RotationMode", i); });
    addRow(viewCard, T("Rotate around"), center);
    viewToggle(viewCard, T("Animate view changes"), "UseNavigationAnimations", true);

    auto speedCard = addCard(nav, T("Speed & Zoom"));
    auto slider = [](int lo, int hi, int value) {
        auto s = new QSlider(Qt::Horizontal);
        s->setRange(lo, hi);
        s->setValue(value);
        s->setFixedWidth(240);
        return s;
    };
    auto sensitivity = slider(5, 100, int(view->GetFloat("Sensitivity", 2.0) * 10));  // 0.5 … 10
    QObject::connect(sensitivity, &QSlider::valueChanged, [view](int v) { view->SetFloat("Sensitivity", v / 10.0); });
    addRow(speedCard, T("Rotation speed"), sensitivity);
    auto zoomStep = slider(2, 50, int(std::max(0.02, view->GetFloat("ZoomStep", 0.2)) * 100));  // 0.02 … 0.5
    QObject::connect(zoomStep, &QSlider::valueChanged, [view](int v) { view->SetFloat("ZoomStep", v / 100.0); });
    addRow(speedCard, T("Zoom & scroll speed"), zoomStep);
    viewToggle(speedCard, T("Zoom towards the cursor"), "ZoomAtCursor", true);
    viewToggle(speedCard, T("Invert zoom (mouse wheel)"), "InvertZoom", true);

    auto padCard = addCard(nav, T("Trackpad"));
    viewToggle(padCard, T("Two fingers pan"), "TouchpadScrollPans", Gui::NavigationStyle::touchpadScrollPansByDefault());
    // Spreizen, und 2-Finger-Scrollen, falls es zoomt
    toggle(padCard, T("Invert zoom"), myParams()->GetBool("InvertTrackpadZoom", view->GetBool("InvertZoom", true)),
           [](bool on) { myParams()->SetBool("InvertTrackpadZoom", on); });
    for (auto [label, param] : {std::pair {"Rotate (3 fingers)", "TrackpadRotateSpeed"},
                                std::pair {"Pan (2 fingers)", "TrackpadPanSpeed"},
                                std::pair {"Zoom (pinch)", "TrackpadZoomSpeed"}}) {
        auto s = slider(25, 400, int(view->GetFloat(param, 1.0) * 100));  // 25 % … 400 %
        QObject::connect(s, &QSlider::valueChanged, [view, param](int v) { view->SetFloat(param, v / 100.0); });
        addRow(padCard, T(label), s);
    }

    // Schönschrift in Scribbles (ScribbleTidy): Schalter und Stärke, gelesen beim Aufräumen
    auto penCard = addCard(nav, T("Pen & Handwriting"));
    toggle(penCard, T("Tidy handwriting after a pause"), myParams()->GetBool("ScribbleTidy", true),
           [](bool on) { myParams()->SetBool("ScribbleTidy", on); });
    auto strength = slider(0, 100, int(myParams()->GetInt("ScribbleTidyStrength", 100)));
    QObject::connect(strength, &QSlider::valueChanged, [](int v) { myParams()->SetInt("ScribbleTidyStrength", v); });
    addRow(penCard, T("Tidying strength"), strength);
    nav->addWidget(hint(T("A second after you lift the pen, what you just wrote in a Scribble lines up: straight lines, "
                          "even size, slant and spacing. Undo brings back the raw handwriting.")));
    nav->addStretch();

    // --- Seite Tasten als Maustasten (cad.helper) ---
    QVBoxLayout* keys = newPage();
    keys->addWidget(hint(T("Hold a key while moving on the trackpad to pan or rotate, like with a mouse button. "
                           "Works while the pointer is over the 3D view.")));
    auto keyCard = addCard(keys, T("Keys as mouse buttons"));
    auto empty = new QLabel(T("No keys yet. Add one, e.g. Space as the middle mouse button."));
    empty->setObjectName(QStringLiteral("Secondary"));
    empty->setWordWrap(true);
    empty->setContentsMargins(0, 12, 0, 12);
    keyCard->rows->addWidget(empty);

    struct Entry
    {
        int key;
        QComboBox* button;
        QComboBox* mode;
        QWidget* row;
    };
    auto entries = std::make_shared<std::vector<Entry>>();
    auto save = [entries, empty, style, showHelp] {
        QJsonArray array;
        for (const auto& e : *entries) {
            QJsonObject o;
            o[QStringLiteral("key")] = e.key;
            o[QStringLiteral("button")] = QString::fromLatin1(Buttons[e.button->currentIndex()].second);
            o[QStringLiteral("mode")] = QString::fromLatin1(Modes[e.mode->currentIndex()]);
            array.append(o);
        }
        myParams()->SetASCII("MouseKeys", QJsonDocument(array).toJson(QJsonDocument::Compact).toStdString());
        empty->setVisible(entries->empty());
        showHelp(style->currentIndex());  // Vorschau zeigt die Tasten als Alternative
    };
    auto addEntry = [keyCard, entries, save](int key, int button, int mode) {
        auto row = new QWidget;
        auto h = new QHBoxLayout(row);
        h->setContentsMargins(0, 8, 0, 8);
        h->setSpacing(8);
        auto chip = new QLabel(T(keyName(key)));
        chip->setObjectName(QStringLiteral("Chip"));
        setTextStyle(chip, Text::Caption);
        chip->setFixedHeight(Token::Chip);
        chip->setMinimumWidth(56);
        chip->setAlignment(Qt::AlignCenter);
        h->addWidget(chip);
        auto acts = new QLabel(T("acts as"));
        acts->setObjectName(QStringLiteral("Secondary"));
        h->addWidget(acts);
        auto buttons = new QComboBox;
        for (auto label : ButtonLabels) {
            buttons->addItem(T(label));
        }
        buttons->setCurrentIndex(button);
        buttons->setAccessibleName(T("Mouse button"));
        h->addWidget(buttons, 1);
        auto modes = new QComboBox;
        for (auto label : ModeLabels) {
            modes->addItem(T(label));
        }
        modes->setCurrentIndex(mode);
        modes->setAccessibleName(T("Mode"));
        h->addWidget(modes, 1);
        auto remove = new QToolButton;
        remove->setObjectName(QStringLiteral("Remove"));
        remove->setIcon(designIcon(QStringLiteral("Window_Close"), &Theme::labelSecondary));
        remove->setIconSize(QSize(Token::IconM, Token::IconM));
        remove->setFixedSize(28, 28);
        remove->setToolTip(T("Remove"));
        remove->setAccessibleName(T("Remove"));
        h->addWidget(remove);
        keyCard->rows->addWidget(row);
        entries->push_back({key, buttons, modes, row});
        QObject::connect(buttons, &QComboBox::currentIndexChanged, save);
        QObject::connect(modes, &QComboBox::currentIndexChanged, save);
        QObject::connect(remove, &QToolButton::clicked, row, [entries, row, save] {
            std::erase_if(*entries, [row](const Entry& e) { return e.row == row; });
            row->deleteLater();
            save();
        });
    };
    for (const auto& v : QJsonDocument::fromJson(QByteArray::fromStdString(myParams()->GetASCII("MouseKeys", "[]"))).array()) {
        const QJsonObject o = v.toObject();
        int button = 1, mode = 0;
        for (int b = 0; b < 3; ++b) {
            button = o.value(QStringLiteral("button")).toString() == QLatin1String(Buttons[b].second) ? b : button;
        }
        for (int m = 0; m < 4; ++m) {
            mode = o.value(QStringLiteral("mode")).toString() == QLatin1String(Modes[m]) ? m : mode;
        }
        addEntry(o.value(QStringLiteral("key")).toInt(), button, mode);
    }
    empty->setVisible(entries->empty());
    keys->addWidget(hint(T("Hold: the button is pressed while the key is down. Toggle: first press holds, second press releases. "
                           "Click and Double-click send a single click.")));
    auto addRowLay = new QHBoxLayout;
    addRowLay->setContentsMargins(16, 4, 16, 0);
    auto add = new QPushButton(T("Add Key…"));
    add->setAutoDefault(false);
    QObject::connect(add, &QPushButton::clicked, &dlg, [&dlg, addEntry, save] {
        if (const int key = recordKey(&dlg)) {
            addEntry(key, 1, 0);  // Standard: mittlere Maustaste halten (Pan/Orbit)
            save();
        }
    });
    addRowLay->addWidget(add);
    addRowLay->addStretch();
    keys->addLayout(addRowLay);
    keys->addStretch();

    // --- Seite Tablett: Tasten am Grafiktablett und am Stift (TabletKeys.h, ausgeführt von TabletActions) ---
    namespace TK = Gui::Shell::TabletKeys;
    QVBoxLayout* tabletPage = newPage();
    auto picture = new TabletPicture;
    auto model = std::make_shared<std::string>();  // angezeigtes Modell; leer: refresh() baut beim ersten Mal die Zeilen
    auto assignment = std::make_shared<TK::Assignment>(TK::parse(myParams()->GetASCII("TabletKeys", "")));
    auto saveTablet = [assignment] { myParams()->SetASCII("TabletKeys", TK::format(*assignment)); };

    auto tabletCard = addCard(tabletPage, T("Tablet"));
    auto hero = new QWidget;  // Hero-Karte (MyStyle § 9.2): Zeichnung links, rechts Modell und Zustand
    auto heroLay = new QHBoxLayout(hero);
    heroLay->setContentsMargins(0, 4, 0, 4);
    heroLay->setSpacing(16);
    heroLay->addWidget(picture);
    auto info = new QVBoxLayout;
    info->setSpacing(6);
    auto modelName = new QLabel;
    setTextStyle(modelName, Text::Headline);
    auto status = new QLabel;
    status->setWordWrap(true);
    setTextStyle(status, Text::Callout);
    auto device = new QLabel;
    device->setObjectName(QStringLiteral("Secondary"));
    device->setTextInteractionFlags(Qt::TextSelectableByMouse);
    setTextStyle(device, Text::Caption);
    auto padHint = new QLabel;
    padHint->setObjectName(QStringLiteral("Hint"));
    padHint->setWordWrap(true);
    setTextStyle(padHint, Text::Caption);
    auto allow = new QPushButton(T("Allow Access…"));
    allow->setAutoDefault(false);
    allow->setToolTip(T("MyCAD asks for your password once, then it may read the keys of graphics tablets (never keyboards)"));
    info->addStretch();
    for (QWidget* w : {static_cast<QWidget*>(modelName), static_cast<QWidget*>(status), static_cast<QWidget*>(device),
                       static_cast<QWidget*>(padHint)}) {
        info->addWidget(w);
    }
    info->addWidget(allow, 0, Qt::AlignLeft);
    auto accessHint = new QLabel;  // im Container, oder wenn "Zugriff erlauben" nicht ging: wie es von Hand geht
    accessHint->setObjectName(QStringLiteral("Hint"));
    accessHint->setWordWrap(true);
    accessHint->setTextInteractionFlags(Qt::TextSelectableByMouse);
    setTextStyle(accessHint, Text::Caption);
    accessHint->hide();
    info->addWidget(accessHint);
    info->addStretch();
    heroLay->addLayout(info, 1);
    addRow(tabletCard, QString(), hero, true);
    auto modelBox = new QComboBox;
    QString brand;
    for (const TK::Model& m : TK::Models) {
        const QString b = QString::fromLatin1(m.label).section(QLatin1Char(' '), 0, 0);  // Trennlinie je Hersteller
        if (modelBox->count() > 0 && b != brand) {
            modelBox->insertSeparator(modelBox->count());
        }
        brand = b;
        modelBox->addItem(T(m.label), QString::fromLatin1(m.id));
    }
    modelBox->setMaxVisibleItems(20);
    addRow(tabletCard, T("Model"), modelBox);

    // Zeilen: Chip mit der Nummer, Name, "gedrückt" und die Aktion. Eine gedrückte Taste färbt ihre Zeile (fill.secondary)
    // und ihre Taste in der Zeichnung; über einer Zeile leuchtet ihre Taste in der Zeichnung auf.
    struct KeyRow
    {
        std::string key;
        QWidget* row;
        QWidget* field;
        QLabel* pressed;
        QComboBox* action;
    };
    auto keyRows = std::make_shared<std::vector<KeyRow>>();
    auto makeRow = [&, picture, assignment, saveTablet, keyRows](const std::shared_ptr<Card>& card, const std::string& key, const QString& num,
                                                          const QString& label) {
        auto field = new QWidget;
        field->setObjectName(QStringLiteral("KeyRow"));
        field->setAttribute(Qt::WA_StyledBackground);
        auto h = new QHBoxLayout(field);
        h->setContentsMargins(0, 0, 0, 0);
        h->setSpacing(10);
        auto chip = new QLabel(num);
        chip->setObjectName(QStringLiteral("Chip"));
        setTextStyle(chip, Text::Caption);
        chip->setFixedHeight(Token::Chip);
        // alle gleich breit (Platz für zwei Ziffern), sonst stehen die Namen je nach Ziffer versetzt
        chip->setFixedWidth(chip->fontMetrics().horizontalAdvance(QStringLiteral("88")) + 20);
        chip->setAlignment(Qt::AlignCenter);
        h->addWidget(chip);
        auto text = new QLabel(label);
        setTextStyle(text, Text::Body);
        h->addWidget(text, 1);
        auto pressed = new QLabel(T("pressed"));
        pressed->setObjectName(QStringLiteral("Pressed"));
        setTextStyle(pressed, Text::Caption);
        pressed->hide();
        h->addWidget(pressed);
        auto box = new QComboBox;
        int group = TK::Actions[0].group;
        for (const TK::Action& a : TK::Actions) {
            if (a.group != group) {
                box->insertSeparator(box->count());
                group = a.group;
            }
            box->addItem(T(a.label), QString::fromLatin1(a.id));
        }
        box->setMaxVisibleItems(20);
        box->setCurrentIndex(box->findData(QString::fromLatin1(TK::actionFor(*assignment, key).id)));
        box->setAccessibleName(label);
        QObject::connect(box, &QComboBox::currentIndexChanged, box, [box, key, assignment, saveTablet](int i) {
            (*assignment)[key] = box->itemData(i).toString().toStdString();
            saveTablet();
        });
        h->addWidget(box);
        new EventHook(field, QEvent::Enter, [picture, key] {
            picture->hovered = key;
            picture->update();
        });
        new EventHook(field, QEvent::Leave, [picture] {
            picture->hovered.clear();
            picture->update();
        });
        keyRows->push_back({key, addRow(card, QString(), field, true), field, pressed, box});
    };

    auto tabletKeysCard = addCard(tabletPage, T("Keys on the Tablet"));
    auto padEmpty = new QLabel(T("No keys yet. Press each key on the tablet once, then its row appears here."));
    padEmpty->setObjectName(QStringLiteral("Secondary"));
    padEmpty->setWordWrap(true);
    padEmpty->setContentsMargins(0, 12, 0, 12);
    tabletKeysCard->rows->addWidget(padEmpty);
    // so viele Zeilen, wie das Modell Tasten hat; unbekannte Modelle lernen sie beim Drücken
    auto padCount = [model] {
        const TK::Model& m = TK::model(*model);
        return m.buttons > 0 ? m.buttons : int(myParams()->GetInt("TabletKeysSeen", 0));
    };
    auto buildPadRows = [&, keyRows, tabletKeysCard, padEmpty, picture, padCount] {
        std::erase_if(*keyRows, [](const KeyRow& r) {
            if (r.key.rfind("pad", 0) == 0) {
                delete r.row;
                return true;
            }
            return false;
        });
        tabletKeysCard->first = true;
        const int n = padCount();
        for (int k = 1; k <= n; ++k) {
            makeRow(tabletKeysCard, TK::padKey(k), QString::number(k), T("Key %1").arg(k));
        }
        padEmpty->setVisible(n == 0);
        picture->keys = n;
        picture->update();
    };
    auto tabletPenCard = addCard(tabletPage, T("Keys on the Pen"));
    makeRow(tabletPenCard, "penLow", QStringLiteral("1"), T("Lower Button"));
    makeRow(tabletPenCard, "penHigh", QStringLiteral("2"), T("Upper Button"));
    tabletPage->addWidget(hint(T("Rotate and pan the view work while the key is held. Eraser switches over, a second press "
                                 "brings back the pen.")));
    auto restoreLay = new QHBoxLayout;
    restoreLay->setContentsMargins(16, 4, 16, 0);
    auto restore = new QPushButton(T("Restore Suggestion"));
    restore->setAutoDefault(false);
    QObject::connect(restore, &QPushButton::clicked, restore, [assignment, saveTablet, keyRows] {
        assignment->clear();
        saveTablet();
        for (const KeyRow& r : *keyRows) {
            QSignalBlocker block(r.action);
            r.action->setCurrentIndex(r.action->findData(QString::fromLatin1(TK::actionFor({}, r.key).id)));
        }
    });
    restoreLay->addWidget(restore);
    restoreLay->addStretch();
    tabletPage->addLayout(restoreLay);
    tabletPage->addWidget(hint(T("If KDE still maps these keys to shortcuts or mouse buttons, MyCAD ignores what KDE sends "
                                 "right after a key it read itself, so nothing happens twice. Other programs keep the KDE mapping.")));
    tabletPage->addStretch();

    // Zustand: angeschlossen, nicht lesbar (dann "Zugriff erlauben"), kein Tablett; ein erkanntes Modell wird vorgewählt,
    // solange keins gewählt ist
    auto refresh = [&, model, modelBox, buildPadRows] {
        const TabletPad& pad = tabletPad();
        status->setText(pad.denied          ? T("Connected, but MyCAD can't read its keys yet.")
                        : pad.name.isEmpty() ? T("No tablet connected")
                                             : T("Connected"));
        // im Container (install.sh) gibt es kein pkexec und keinen Weg nach /etc: dort legt install.sh die Regel an
        static const bool contained = QFile::exists(QStringLiteral("/run/.containerenv")) || QFile::exists(QStringLiteral("/.dockerenv"));
        allow->setVisible(pad.denied && !contained);
        if (pad.denied && contained) {
            accessHint->setText(T("MyCAD runs in a container here. Run install.sh once more: it sets up access (asks for your "
                                  "password once). Then restart MyCAD."));
        }
        accessHint->setVisible(pad.denied && (contained || !accessHint->text().isEmpty()));
        device->setText(pad.name);
        device->setVisible(!pad.name.isEmpty());
        const std::string chosen = myParams()->GetASCII("TabletModel", "");
        const std::string shown = !chosen.empty() ? chosen : TK::detect(pad.name.toStdString()).id;
        if (shown != *model) {
            *model = shown;
            QSignalBlocker block(modelBox);
            modelBox->setCurrentIndex(modelBox->findData(QString::fromStdString(shown)));
            buildPadRows();
        }
        const TK::Model& m = TK::model(*model);
        modelName->setText(T(m.label));
        padHint->setText(m.buttons > 0 ? T("Press a key on the tablet or pen: its row lights up.")
                                       : T("MyCAD doesn't know the keys of this model yet. Press each key once, then its row appears."));
    };
    QObject::connect(modelBox, &QComboBox::currentIndexChanged, modelBox, [modelBox, refresh](int i) {
        myParams()->SetASCII("TabletModel", modelBox->itemData(i).toString().toStdString());
        refresh();
    });
    // Zugriff: dieselbe Art Regel wie für Touchpads (uaccess für den angemeldeten Benutzer), nur für die Tasten-Geräte
    // von Tabletts, nie für Tastaturen. pkexec fragt nach dem Passwort; danach öffnet der Reader die Geräte neu.
    // Gleiche Regel legt install.sh an (MyCAD im Container)
    QObject::connect(allow, &QPushButton::clicked, allow, [allow, accessHint, &dlg] {
        const QString rule = QStringLiteral(
            R"(ACTION!="remove", SUBSYSTEM=="input", KERNEL=="event*", ENV{ID_INPUT_TABLET_PAD}=="1", TAG+="uaccess")");
        auto proc = new QProcess(&dlg);
        allow->setEnabled(false);
        // Abbrechen im Passwort-Dialog (pkexec: 126) ist kein Fehler; sonst nie still scheitern: der Befehl fürs Terminal
        const auto done = [proc, allow, accessHint, rule](int code) {
            proc->deleteLater();
            allow->setEnabled(true);
            if (code == 0) {
                accessHint->hide();
                QTimer::singleShot(500, allow, [] { TouchpadReader::install().reconnect(); });  // bis udev die Rechte setzt
            }
            else if (code != 126) {
                accessHint->setText(T("Couldn't set up access. In a terminal:") + QStringLiteral("\necho '") + rule
                                    + QStringLiteral("' | sudo tee /etc/udev/rules.d/70-mycad-tablet.rules && sudo udevadm "
                                                     "control --reload && sudo udevadm trigger --subsystem-match=input"));
                accessHint->show();
            }
        };
        QObject::connect(proc, &QProcess::finished, allow, [done](int code, QProcess::ExitStatus st) {
            done(st == QProcess::NormalExit ? code : -1);
        });
        QObject::connect(proc, &QProcess::errorOccurred, allow, [done](QProcess::ProcessError e) {
            if (e == QProcess::FailedToStart) {
                done(-1);
            }
        });
        proc->start(QStringLiteral("pkexec"),
                    {QStringLiteral("sh"), QStringLiteral("-c"),
                     QStringLiteral("printf '%s\\n' \"$1\" > /etc/udev/rules.d/70-mycad-tablet.rules"
                                    " && udevadm control --reload && udevadm trigger --subsystem-match=input"),
                     QStringLiteral("sh"), rule});
    });
    // eine Taste drücken: ihre Zeile und ihre Taste leuchten kurz auf (die Tasten tun dabei nichts)
    auto flashes = std::make_shared<int>(0);
    tabletPad().listener = [&, keyRows, picture, model, flashes, buildPadRows](const std::string& key, bool down) {
        if (!down) {
            return;
        }
        if (key.rfind("pad", 0) == 0 && TK::model(*model).buttons == 0) {
            const int n = std::atoi(key.c_str() + 3);
            if (n > myParams()->GetInt("TabletKeysSeen", 0)) {  // unbekanntes Modell: die Taste bekommt eine Zeile
                myParams()->SetInt("TabletKeysSeen", n);
                buildPadRows();
            }
        }
        const int flash = ++*flashes;
        const auto light = [keyRows, picture](const std::string& on) {
            for (const KeyRow& r : *keyRows) {
                r.field->setProperty("pressed", r.key == on);
                for (QWidget* w : r.field->findChildren<QWidget*>() << r.field) {  // auch der Chip (Regel hängt an der Zeile)
                    w->style()->unpolish(w);
                    w->style()->polish(w);
                }
                r.pressed->setVisible(r.key == on);
            }
            picture->pressed = on;
            picture->update();
        };
        light(key);
        QTimer::singleShot(1600, picture, [light, flashes, flash] {
            if (*flashes == flash) {
                light({});
            }
        });
    };
    tabletPad().changed = refresh;
    refresh();

    updateStyle();
    // so hoch wie die längste Seite, höchstens so hoch wie der Bildschirm (dann rollt die Seite); ohne das zeigte Qt
    // den Dialog in der Mindesthöhe der Rollflächen
    dlg.resize(dlg.sizeHint().boundedTo(getMainWindow()->screen()->availableGeometry().size()
                                        - QSize(0, 2 * Token::WindowInset)));
    window->setFocusPolicy(Qt::ClickFocus);  // kein Fokusring beim Öffnen; Tab führt zu den Bedienelementen
    window->setFocus();
    dlg.exec();
    tabletPad().listener = nullptr;  // die Seite ist zu: Tablett-Tasten tun wieder, was belegt ist
    tabletPad().changed = nullptr;
}
