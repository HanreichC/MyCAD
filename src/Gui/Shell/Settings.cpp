// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Settings.h"
#include "Shell.h"

#include <App/Application.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/MainWindow.h>

#include <QAbstractSpinBox>
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QCursor>
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
/// Schreibt der Benutzer gerade Text (Umbenennen, Namen …)? Dann bleiben alle Tasten Tasten, auch Shift.
/// Zahlenfelder zählen nicht: dort braucht man weder Großbuchstaben noch Leertaste, und Navigieren bei offenem
/// Dialog soll weiter gehen.
bool typing()
{
    QWidget* f = QApplication::focusWidget();
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
}

namespace
{
/// Schalter wie in macOS/iOS statt Häkchen
class Switch: public QAbstractButton
{
public:
    explicit Switch(bool on)
    {
        setCheckable(true);
        setChecked(on);
        setCursor(Qt::PointingHandCursor);
        setFixedSize(42, 24);
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        const bool dark = palette().color(QPalette::Window).lightness() < 128;
        const QColor off = dark ? QColor(0x39, 0x39, 0x3D) : QColor(0xE9, 0xE9, 0xEB);
        p.setPen(Qt::NoPen);
        p.setBrush(isChecked() ? QColor(0x34, 0xC7, 0x59) : off);
        p.drawRoundedRect(rect(), height() / 2.0, height() / 2.0);
        const qreal d = height() - 4;
        const QRectF knob(isChecked() ? width() - d - 2 : 2, 2, d, d);
        p.setBrush(QColor(0, 0, 0, 40));
        p.drawEllipse(knob.translated(0, 1));
        p.setBrush(Qt::white);
        p.drawEllipse(knob);
    }
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

QPixmap tintedIcon(const QString& name, const QColor& color, int size)
{
    QFile file(QStringLiteral(":/mycad/icons/%1.svg").arg(name));
    if (!file.open(QIODevice::ReadOnly)) {
        return {};
    }
    QSvgRenderer renderer(file.readAll().replace("currentColor", color.name().toLatin1()));
    const qreal dpr = qApp->devicePixelRatio();
    QPixmap pix(int(size * dpr), int(size * dpr));
    pix.fill(Qt::transparent);
    QPainter painter(&pix);
    renderer.render(&painter);
    painter.end();
    pix.setDevicePixelRatio(dpr);
    return pix;
}

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
            auto orLabel = new QLabel(QStringLiteral("or"));
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
            auto chip = new QLabel(keys[k].trimmed());
            chip->setObjectName(QStringLiteral("Chip"));
            lay->addWidget(chip);
        }
    }
    lay->addStretch();
    return w;
}
}  // namespace

void Gui::Shell::showSettings()
{
    QDialog dlg(Gui::getMainWindow(), Qt::Dialog | Qt::FramelessWindowHint);
    dlg.setAttribute(Qt::WA_TranslucentBackground);
    dlg.setObjectName(QStringLiteral("Settings"));
    dlg.setWindowTitle(QStringLiteral("Settings"));
    dlg.setMinimumWidth(660);

    // Farben wie im Rest von MyCAD (hell/dunkel nach System)
    const bool dark = qApp->palette().color(QPalette::Window).lightness() < 128;
    const QString bg = dark ? QStringLiteral("#1C1C1E") : QStringLiteral("#F2F2F7");
    const QString card = dark ? QStringLiteral("#2C2C2E") : QStringLiteral("#FFFFFF");
    const QString border = dark ? QStringLiteral("rgba(255,255,255,0.10)") : QStringLiteral("rgba(0,0,0,0.08)");
    const QString sep = dark ? QStringLiteral("rgba(255,255,255,0.08)") : QStringLiteral("rgba(60,60,67,0.12)");
    const QString secondary = dark ? QStringLiteral("#98989D") : QStringLiteral("#6E6E73");
    const QString text = dark ? QStringLiteral("#F5F5F7") : QStringLiteral("#1D1D1F");
    const QString accent = dark ? QStringLiteral("#0A84FF") : QStringLiteral("#007AFF");
    const QString chipBg = dark ? QStringLiteral("#3A3A3C") : QStringLiteral("#F5F5F7");
    const QString segBg = dark ? QStringLiteral("rgba(118,118,128,0.24)") : QStringLiteral("rgba(118,118,128,0.12)");
    const QString segSel = dark ? QStringLiteral("#636366") : QStringLiteral("#FFFFFF");
    dlg.setStyleSheet(QStringLiteral(R"(
* { color: %1; }
QDialog#Settings { background: transparent; }
QFrame#Window { background: %2; border: 1px solid %4; border-radius: 14px; }
QFrame#Card { background: %3; border: 1px solid %4; border-radius: 10px; }
QFrame#Separator { background: %5; border: none; min-height: 1px; max-height: 1px; }
QLabel#Title { font-size: 20px; font-weight: 700; }
QLabel#SectionTitle { color: %6; font-size: 11px; font-weight: 600; padding-left: 4px; }
QLabel#Secondary { color: %6; }
QLabel#Hint { color: %6; font-size: 12px; }
QLabel#Chip { background: %8; border: 1px solid %4; border-radius: 5px; padding: 1px 7px; font-size: 12px; font-weight: 600; }
QWidget#Segmented { background: %9; border-radius: 8px; }
QPushButton#Segment { background: transparent; border: none; border-radius: 6px; padding: 4px 16px; min-width: 0; }
QPushButton#Segment:checked { background: %10; font-weight: 600; }
QComboBox { background: %3; border: 1px solid %4; border-radius: 7px; padding: 3px 8px; min-height: 22px; }
QComboBox::drop-down { border: none; width: 20px; }
QComboBox::down-arrow { image: url(:/mycad/icons/Chevron_Down.svg); width: 10px; height: 10px; }
QComboBox QAbstractItemView { background: %3; border: 1px solid %4; border-radius: 8px; padding: 4px; outline: 0;
    selection-background-color: %7; selection-color: white; }
QSlider::groove:horizontal { height: 4px; background: %5; border-radius: 2px; }
QSlider::sub-page:horizontal { background: %7; border-radius: 2px; }
QSlider::handle:horizontal { background: white; border: 1px solid %4; width: 18px; height: 18px; margin: -8px 0; border-radius: 9px; }
QPushButton#Done { background: %7; color: white; border: none; border-radius: 7px; padding: 6px 22px; font-weight: 600; min-width: 0; }
QPushButton#Plain { background: %3; border: 1px solid %4; border-radius: 7px; padding: 5px 14px; min-width: 0; }
QPushButton#Remove { background: transparent; border: none; color: %6; font-size: 15px; padding: 2px 6px; min-width: 0; }
QPushButton#Remove:hover { color: #FF3B30; }
)")
                          .arg(text, bg, card, border, sep, secondary, accent, chipBg, segBg)
                          .arg(segSel));

    auto outer = new QVBoxLayout(&dlg);
    outer->setContentsMargins(0, 0, 0, 0);
    auto window = new QFrame;
    window->setObjectName(QStringLiteral("Window"));
    outer->addWidget(window);
    auto lay = new QVBoxLayout(window);
    lay->setContentsMargins(24, 18, 24, 20);
    lay->setSpacing(8);

    auto segmented = [](const QStringList& items, int current, std::function<void(int)> changed) {
        auto box = new QWidget;
        box->setObjectName(QStringLiteral("Segmented"));
        box->setAttribute(Qt::WA_StyledBackground);
        auto row = new QHBoxLayout(box);
        row->setContentsMargins(2, 2, 2, 2);
        row->setSpacing(2);
        auto group = new QButtonGroup(box);
        for (int i = 0; i < items.size(); ++i) {
            auto b = new QPushButton(items[i]);
            b->setObjectName(QStringLiteral("Segment"));
            b->setCheckable(true);
            b->setChecked(i == current);
            b->setAutoDefault(false);
            group->addButton(b, i);
            row->addWidget(b);
        }
        QObject::connect(group, &QButtonGroup::idClicked, box, [changed](int id) { changed(id); });
        return box;
    };

    // Kopf: Titel (zum Verschieben) und Bereiche
    auto head = new DragArea;
    auto headLay = new QHBoxLayout(head);
    headLay->setContentsMargins(0, 0, 0, 0);
    auto title = new QLabel(QStringLiteral("Settings"));
    title->setObjectName(QStringLiteral("Title"));
    headLay->addWidget(title);
    headLay->addStretch();
    auto pages = new QStackedWidget;
    headLay->addWidget(segmented({QStringLiteral("Navigation"), QStringLiteral("Keys")}, 0,
                                 [pages](int i) { pages->setCurrentIndex(i); }));
    lay->addWidget(head);
    lay->addSpacing(6);
    lay->addWidget(pages);

    // Karten mit Zeilen (Beschriftung links, Bedienelement rechts), Trennlinien dazwischen
    struct Card
    {
        QVBoxLayout* rows;
        bool first = true;
    };
    auto addCard = [](QVBoxLayout* page, const QString& heading) {
        if (!heading.isEmpty()) {
            auto label = new QLabel(heading.toUpper());
            label->setObjectName(QStringLiteral("SectionTitle"));
            page->addSpacing(4);
            page->addWidget(label);
        }
        auto frame = new QFrame;
        frame->setObjectName(QStringLiteral("Card"));
        auto rows = new QVBoxLayout(frame);
        rows->setContentsMargins(14, 4, 14, 4);
        rows->setSpacing(0);
        page->addWidget(frame);
        return std::make_shared<Card>(Card {rows});
    };
    auto addRow = [](const std::shared_ptr<Card>& c, const QString& label, QWidget* field, bool wide = false) {
        if (!c->first) {
            auto line = new QFrame;
            line->setObjectName(QStringLiteral("Separator"));
            c->rows->addWidget(line);
        }
        c->first = false;
        auto row = new QWidget;
        auto h = new QHBoxLayout(row);
        h->setContentsMargins(0, 8, 0, 8);
        if (!label.isEmpty()) {
            h->addWidget(new QLabel(label));
        }
        h->addStretch(wide ? 0 : 1);
        h->addWidget(field, wide ? 1 : 0);
        c->rows->addWidget(row);
    };

    auto view = viewParams();

    // --- Seite Navigation ---
    auto navPage = new QWidget;
    auto nav = new QVBoxLayout(navPage);
    nav->setContentsMargins(0, 0, 0, 0);
    nav->setSpacing(6);

    auto styleCard = addCard(nav, QStringLiteral("Mouse & Trackpad"));
    auto style = new QComboBox;
    style->setMinimumWidth(260);
    const std::string current = view->GetASCII("NavigationStyle", "Gui::RevitNavigationStyle");
    for (const auto& s : Styles) {
        style->addItem(QString::fromLatin1(s.label), QString::fromLatin1(s.type));
        if (current == s.type) {
            style->setCurrentIndex(style->count() - 1);
        }
    }
    addRow(styleCard, QStringLiteral("Style"), style);

    // Vorschau: wie gedreht, geschoben, gezoomt und ausgewählt wird; folgt auch dem Überfahren der Liste
    auto help = new QWidget;
    auto helpLay = new QVBoxLayout(help);
    helpLay->setContentsMargins(0, 0, 0, 0);
    helpLay->setSpacing(6);
    addRow(styleCard, QString(), help, true);
    const QColor iconColor(secondary);
    auto showHelp = [help, helpLay, iconColor](int index) {
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
            glyph->setPixmap(tintedIcon(QString::fromLatin1(icon), iconColor, 18));
            h->addWidget(glyph);
            auto name = new QLabel(QString::fromLatin1(names[i++]));
            name->setFixedWidth(52);
            h->addWidget(name);
            h->addWidget(chips(combos), 1);
            helpLay->addWidget(row);
            row->show();  // sonst erst verzögert sichtbar (Vorschau beim Überfahren der Liste)
        }
    };
    showHelp(style->currentIndex());
    QObject::connect(style, &QComboBox::highlighted, help, showHelp);
    QObject::connect(style, &QComboBox::currentIndexChanged, help, [style, view, showHelp](int i) {
        view->SetASCII("NavigationStyle", style->itemData(i).toString().toStdString());
        showHelp(i);
    });
    new EventHook(style->view(), QEvent::Hide, [style, showHelp] { showHelp(style->currentIndex()); });
    auto trackpadNote = new QLabel(QStringLiteral("On a trackpad, two-finger scrolling acts as the scroll wheel. "
                                                  "Keys that act as mouse buttons are set up under Keys."));
    trackpadNote->setObjectName(QStringLiteral("Hint"));
    trackpadNote->setWordWrap(true);
    trackpadNote->setContentsMargins(4, 0, 4, 0);
    nav->addWidget(trackpadNote);

    auto viewCard = addCard(nav, QStringLiteral("View"));
    addRow(viewCard, QStringLiteral("Camera"),
           segmented({QStringLiteral("Orthographic"), QStringLiteral("Perspective")},
                     view->GetBool("Orthographic", true) ? 0 : 1, [view](int i) {
                         view->SetBool("Perspective", i == 1);
                         view->SetBool("Orthographic", i == 0);  // wirkt sofort auf alle Ansichten
                     }));
    auto orbit = new QComboBox;
    orbit->addItems({QStringLiteral("Turntable (Z stays up)"), QStringLiteral("Trackball (free)"),
                     QStringLiteral("Free turntable"), QStringLiteral("Trackball classic"),
                     QStringLiteral("Rounded arcball")});
    orbit->setCurrentIndex(static_cast<int>(view->GetInt("OrbitStyle", 0)));
    QObject::connect(orbit, &QComboBox::currentIndexChanged, [view](int i) { view->SetInt("OrbitStyle", i); });
    addRow(viewCard, QStringLiteral("Rotate"), orbit);
    auto center = new QComboBox;
    center->addItems({QStringLiteral("Window center"), QStringLiteral("Point under the cursor"),
                      QStringLiteral("Center of all bodies"), QStringLiteral("Center of the body under the cursor")});
    center->setCurrentIndex(static_cast<int>(view->GetInt("RotationMode", 3)));
    QObject::connect(center, &QComboBox::currentIndexChanged, [view](int i) { view->SetInt("RotationMode", i); });
    addRow(viewCard, QStringLiteral("Rotate around"), center);
    auto toggle = [&](const std::shared_ptr<Card>& c, const QString& label, const char* param, bool def) {
        auto sw = new Switch(view->GetBool(param, def));
        QObject::connect(sw, &QAbstractButton::toggled, [view, param](bool on) { view->SetBool(param, on); });
        addRow(c, label, sw);
    };
    toggle(viewCard, QStringLiteral("Animate view changes"), "UseNavigationAnimations", true);
    auto names = new Switch(myParams()->GetBool("ToolNames", false));
    QObject::connect(names, &QAbstractButton::toggled, [](bool on) { Gui::Shell::setToolNames(on); });
    addRow(viewCard, QStringLiteral("Show tool names"), names);
    QStringList materials;
    for (const char* name : Gui::Shell::bodyMaterialNames()) {
        materials << QString::fromLatin1(name);
    }
    addRow(viewCard, QStringLiteral("Body material"),
           segmented(materials, int(myParams()->GetInt("BodyMaterial", 0)), [](int i) { Gui::Shell::setBodyMaterial(i); }));

    auto speedCard = addCard(nav, QStringLiteral("Speed & Zoom"));
    auto slider = [](int lo, int hi, int value) {
        auto s = new QSlider(Qt::Horizontal);
        s->setRange(lo, hi);
        s->setValue(value);
        s->setFixedWidth(240);
        return s;
    };
    auto sensitivity = slider(5, 100, int(view->GetFloat("Sensitivity", 2.0) * 10));  // 0.5 … 10
    QObject::connect(sensitivity, &QSlider::valueChanged, [view](int v) { view->SetFloat("Sensitivity", v / 10.0); });
    addRow(speedCard, QStringLiteral("Rotation speed"), sensitivity);
    auto zoomStep = slider(2, 50, int(std::max(0.02, view->GetFloat("ZoomStep", 0.2)) * 100));  // 0.02 … 0.5
    QObject::connect(zoomStep, &QSlider::valueChanged, [view](int v) { view->SetFloat("ZoomStep", v / 100.0); });
    addRow(speedCard, QStringLiteral("Zoom & scroll speed"), zoomStep);
    toggle(speedCard, QStringLiteral("Zoom towards the cursor"), "ZoomAtCursor", true);
    toggle(speedCard, QStringLiteral("Invert zoom direction"), "InvertZoom", true);
    nav->addStretch();
    pages->addWidget(navPage);

    // --- Seite Tasten als Maustasten (cad.helper) ---
    auto keyPage = new QWidget;
    auto keys = new QVBoxLayout(keyPage);
    keys->setContentsMargins(0, 0, 0, 0);
    keys->setSpacing(6);
    auto intro = new QLabel(QStringLiteral(
        "Hold a key while moving on the trackpad to pan or rotate, like with a mouse button. "
        "Works while the pointer is over the 3D view."));
    intro->setObjectName(QStringLiteral("Hint"));
    intro->setWordWrap(true);
    keys->addWidget(intro);
    auto keyCard = addCard(keys, QStringLiteral("Keys as mouse buttons"));
    auto empty = new QLabel(QStringLiteral("No keys yet. Add one, e.g. Space as the middle mouse button."));
    empty->setObjectName(QStringLiteral("Secondary"));
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
        auto chip = new QLabel(keyName(key));
        chip->setObjectName(QStringLiteral("Chip"));
        chip->setMinimumWidth(56);
        chip->setAlignment(Qt::AlignCenter);
        h->addWidget(chip);
        auto acts = new QLabel(QStringLiteral("acts as"));
        acts->setObjectName(QStringLiteral("Secondary"));
        h->addWidget(acts);
        auto buttons = new QComboBox;
        for (auto label : ButtonLabels) {
            buttons->addItem(QString::fromLatin1(label));
        }
        buttons->setCurrentIndex(button);
        h->addWidget(buttons, 1);
        auto modes = new QComboBox;
        for (auto label : ModeLabels) {
            modes->addItem(QString::fromLatin1(label));
        }
        modes->setCurrentIndex(mode);
        h->addWidget(modes, 1);
        auto remove = new QPushButton(QStringLiteral("✕"));
        remove->setObjectName(QStringLiteral("Remove"));
        remove->setToolTip(QStringLiteral("Remove"));
        remove->setAutoDefault(false);
        h->addWidget(remove);
        keyCard->rows->addWidget(row);
        entries->push_back({key, buttons, modes, row});
        QObject::connect(buttons, &QComboBox::currentIndexChanged, save);
        QObject::connect(modes, &QComboBox::currentIndexChanged, save);
        QObject::connect(remove, &QPushButton::clicked, row, [entries, row, save] {
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
    auto modesHint = new QLabel(QStringLiteral(
        "Hold: the button is pressed while the key is down. Toggle: first press holds, second press releases. "
        "Click and Double-click send a single click."));
    modesHint->setObjectName(QStringLiteral("Hint"));
    modesHint->setWordWrap(true);
    keys->addWidget(modesHint);
    auto addRowLay = new QHBoxLayout;
    auto add = new QPushButton(QStringLiteral("Add Key…"));
    add->setObjectName(QStringLiteral("Plain"));
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
    pages->addWidget(keyPage);

    // Fuß: Fertig
    auto foot = new QHBoxLayout;
    foot->addStretch();
    auto done = new QPushButton(QStringLiteral("Done"));
    done->setObjectName(QStringLiteral("Done"));
    done->setDefault(true);
    QObject::connect(done, &QPushButton::clicked, &dlg, &QDialog::accept);
    foot->addWidget(done);
    lay->addSpacing(6);
    lay->addLayout(foot);
    dlg.exec();
}
