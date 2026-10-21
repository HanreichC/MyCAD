// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Settings.h"
#include "Shell.h"
#include "Theme.h"

#include <App/Application.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/MainWindow.h>

#include <QAbstractSpinBox>
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QPointingDevice>
#include <QNativeGestureEvent>
#include <QWheelEvent>
#include <QToolButton>
#include <QDir>
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

/// Zoomrichtung getrennt für Maus und Trackpad (Einstellungen). FreeCAD kennt nur eine Richtung ("InvertZoom",
/// gilt fürs Mausrad); beim Trackpad wird die Richtung im Ereignis selbst umgedreht, bevor das 3D-Fenster es sieht.
/// (Ein neu zugestelltes Ersatz-Ereignis kam bei echten Trackpads nicht an: Qt bindet Scrollphasen an das Original.)
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

class ZoomDirection: public QObject
{
public:
    static void install()
    {
        static ZoomDirection filter;
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
            if (trackpad && padInvert != mouseInvert) {
                FlipWheel::flip(we);
            }
            return false;
        }
        auto ge = static_cast<QNativeGestureEvent*>(event);
        if (ge->gestureType() == Qt::ZoomNativeGesture && padInvert) {
            FlipGesture::flip(ge);  // Spreizen: ohne Umkehr wie gewohnt (auseinander = näher)
        }
        return false;
    }
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
    ZoomDirection::install();
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

/// Segmented Control mit Pfeiltasten (MyStyle A-2)
class SegmentKeys: public QObject
{
public:
    explicit SegmentKeys(QButtonGroup* group)
        : QObject(group)
        , group(group)
    {}

protected:
    bool eventFilter(QObject*, QEvent* event) override
    {
        if (event->type() != QEvent::KeyPress) {
            return false;
        }
        const int key = static_cast<QKeyEvent*>(event)->key();
        if (key != Qt::Key_Left && key != Qt::Key_Right) {
            return false;
        }
        const int n = int(group->buttons().size());
        const int next = std::clamp(group->checkedId() + (key == Qt::Key_Right ? 1 : -1), 0, n - 1);
        if (QAbstractButton* b = group->button(next); b && next != group->checkedId()) {
            b->setFocus(Qt::TabFocusReason);
            b->click();
        }
        return true;
    }

private:
    QButtonGroup* group;
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
    border: 1px solid @glassPopupBorder; border-radius: 32px; }
QFrame#Card { background: @materialFill; border: 1px solid @materialBorder; border-radius: 20px; }
QFrame#Separator { background: @separator; border: none; min-height: 1px; max-height: 1px; }
QLabel#Section, QLabel#Secondary, QLabel#Hint { color: @labelSecondary; }
QLabel#Chip { background: @fillTertiary; border-radius: 12px; padding: 0 10px; }
QWidget#Segmented { background: @fillTertiary; border-radius: 22px; }
QWidget#Segmented[backdrop="true"] { background: @materialFill; border: 1px solid @materialBorder; }
QPushButton#Segment { background: transparent; border: 2px solid transparent; border-radius: 18px; padding: 0 14px; min-height: 32px; font-weight: 400; }
QPushButton#Segment:hover { background: @fillTertiary; }
QPushButton#Segment:checked { background: @materialThumb; font-weight: 600; }
QPushButton#Segment:focus { border-color: @focusRing; }
QComboBox { background: transparent; border: 2px solid transparent; border-radius: 8px; padding: 2px 8px; min-height: 22px; color: @labelSecondary; }
QComboBox:hover { background: @fillTertiary; }
QComboBox:focus { border-color: @focusRing; }
QComboBox::drop-down { border: none; width: 20px; }
QComboBox::down-arrow { image: url(:/mycad/icons/Chevron_Down.svg); width: 10px; height: 10px; }
QComboBox QAbstractItemView { background: @glassOpaqueTop; border: 1px solid @glassPopupBorder; padding: 4px; outline: 0;
    selection-background-color: @accent; selection-color: @labelOnAccent; }
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

    auto segmented = [](const QStringList& items, int current, std::function<void(int)> changed) {
        auto box = new QWidget;
        box->setObjectName(QStringLiteral("Segmented"));
        box->setAttribute(Qt::WA_StyledBackground);
        box->setFixedHeight(Token::Segmented);
        auto row = new QHBoxLayout(box);
        row->setContentsMargins(4, 4, 4, 4);
        row->setSpacing(2);
        auto group = new QButtonGroup(box);
        auto keys = new SegmentKeys(group);
        for (int i = 0; i < items.size(); ++i) {
            auto b = new QPushButton(items[i]);
            b->setObjectName(QStringLiteral("Segment"));
            b->setCheckable(true);
            b->setChecked(i == current);
            b->setAutoDefault(false);
            b->setFocusPolicy(Qt::TabFocus);
            b->installEventFilter(keys);
            group->addButton(b, i);
            row->addWidget(b, 1);  // gleich breite Segmente
        }
        // so breit wie der längste (fette) Text, sonst schneidet Qt ihn ab; als Stylesheet, weil min-width aus dem
        // Stylesheet eine gesetzte Mindestbreite überschreibt
        const QFontMetrics fm(textFont(Text::Callout, 600));
        int widest = 0;
        for (const QString& item : items) {
            widest = std::max(widest, fm.horizontalAdvance(item) + 2);
        }
        box->setStyleSheet(QStringLiteral("QPushButton#Segment { min-width: %1px; }").arg(widest));
        QObject::connect(group, &QButtonGroup::idClicked, box, [changed](int id) { changed(id); });
        return box;
    };

    // Kopf: Titel (zum Verschieben), Bereiche, Schließen
    auto head = new DragArea;
    auto headLay = new QHBoxLayout(head);
    headLay->setContentsMargins(Token::WindowInset, 0, 0, 0);
    auto title = new QLabel(T("Settings"));
    setTextStyle(title, Text::Title1);
    headLay->addWidget(title);
    headLay->addStretch();
    auto pages = new QStackedWidget;
    auto pageSwitch = segmented({T("General"), T("Navigation"), T("Keys")}, 0, [pages](int i) { pages->setCurrentIndex(i); });
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
    auto newPage = [pages] {
        auto page = new QWidget;
        auto l = new QVBoxLayout(page);
        l->setContentsMargins(0, 0, 0, 0);
        l->setSpacing(4);
        pages->addWidget(page);
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
    QStringList materials;
    for (const char* name : Gui::Shell::bodyMaterialNames()) {
        materials << T(name);
    }
    addRow(lookCard, T("Body material"),
           segmented(materials, int(myParams()->GetInt("BodyMaterial", 0)), [](int i) { Gui::Shell::setBodyMaterial(i); }));
    auto names = new Switch(myParams()->GetBool("ToolNames", false));
    QObject::connect(names, &QAbstractButton::toggled, [](bool on) { Gui::Shell::setToolNames(on); });
    addRow(lookCard, T("Show tool names"), names);

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
    nav->addWidget(hint(T("On a trackpad, two-finger scrolling acts as the scroll wheel. "
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
    toggle(speedCard, T("Invert zoom (trackpad)"), myParams()->GetBool("InvertTrackpadZoom", view->GetBool("InvertZoom", true)),
           [](bool on) { myParams()->SetBool("InvertTrackpadZoom", on); });
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

    updateStyle();
    window->setFocusPolicy(Qt::ClickFocus);  // kein Fokusring beim Öffnen; Tab führt zu den Bedienelementen
    window->setFocus();
    dlg.exec();
}
