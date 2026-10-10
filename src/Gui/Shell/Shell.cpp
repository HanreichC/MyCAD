// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Shell.h"
#include "GlassPanel.h"
#include "ViewCube.h"
#include "Settings.h"

#include <App/Application.h>
#include <Gui/Action.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/Selection/Selection.h>
#include <Gui/ViewProviderDocumentObject.h>
#include <App/Document.h>
#include <App/PropertyStandard.h>
#include <Gui/DockWindowManager.h>
#include <Gui/MainWindow.h>
#include <Gui/Tree.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>

#include <QAbstractScrollArea>
#include <QApplication>
#include <QDockWidget>
#include <QFontDatabase>
#include <QFrame>
#include <QGraphicsScene>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QCursor>
#include <QMouseEvent>
#include <QTreeWidget>
#include <QSizePolicy>
#include <QLabel>
#include <QWindow>
#include <QMenuBar>
#include <QFile>
#include <QPainter>
#include <QSvgRenderer>
#include <QPointer>
#include <QStatusBar>
#include <QStyleHints>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>

#include <functional>
#include <vector>

using namespace Gui;
using namespace Gui::Shell;

namespace
{

struct Theme
{
    bool dark;
    QString text, secondary, accent, hover, pressed, field, fieldBorder, separator;
};

Theme theme()
{
    if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark) {
        return {true, "#F5F5F7", "rgba(235,235,245,0.6)", "#0A84FF", "rgba(255,255,255,0.10)",
                "rgba(255,255,255,0.18)", "rgba(255,255,255,0.08)", "rgba(255,255,255,0.12)",
                "rgba(255,255,255,0.14)"};
    }
    return {false, "#1D1D1F", "rgba(60,60,67,0.6)", "#007AFF", "rgba(0,0,0,0.06)",
            "rgba(0,0,0,0.12)", "rgba(255,255,255,0.65)", "rgba(0,0,0,0.08)", "rgba(0,0,0,0.10)"};
}

void overrideFreeCadIcons(const Theme& t);

QString styleSheet(const Theme& t)
{
    return QStringLiteral(R"(
* { color: %1; }
QToolButton#GlassButton { border: none; border-radius: 10px; background: transparent; }
QToolButton#GlassButton:hover { background: %4; }
QToolButton#GlassButton:pressed { background: %5; }
QToolButton#GlassButton:disabled { background: transparent; }
#GlassContent QToolButton#GlassProminent { border: none; border-radius: 15px; background: %3; color: white; font-weight: 600; padding: 0 14px; }
#GlassContent QToolButton#GlassProminent:hover { background: %3; border: 2px solid rgba(255,255,255,0.35); }
QFrame#TimelineMarker { background: %3; border-radius: 2px; }
QToolButton#PaletteRow { border: none; border-radius: 8px; padding: 0 8px; text-align: left; background: transparent; }
QToolButton#PaletteRow:hover { background: %4; }
QToolButton#PaletteRow:checked { background: %5; }
QToolButton#TrafficLight { border: none; border-radius: 6px; }
QToolButton#TrafficLight[role="close"] { background: #FF5F57; }
QToolButton#TrafficLight[role="minimize"] { background: #FEBC2E; }
QToolButton#TrafficLight[role="zoom"] { background: #28C840; }
QLabel#WindowTitle { font-weight: 600; }
QToolButton#GlassButton[error="true"] { background: rgba(255,59,48,0.28); }
QFrame#GlassSeparator { background: %8; border: none; }
#GlassContent, #GlassContent QWidget { background: transparent; }
#GlassContent QAbstractScrollArea { border: none; }
#GlassContent QLineEdit, #GlassContent QAbstractSpinBox, #GlassContent QComboBox {
    background: %6; border: 1px solid %7; border-radius: 7px; padding: 3px 6px; min-height: 20px;
}
#GlassContent QLineEdit:focus, #GlassContent QAbstractSpinBox:focus { border: 2px solid %3; }
#GlassContent QPushButton {
    background: %6; border: 1px solid %7; border-radius: 7px; padding: 5px 12px;
}
#GlassContent QPushButton:hover { background: %4; }
#GlassContent QPushButton:default { background: %3; color: white; border: none; }
#GlassContent QTreeView::item { min-height: 26px; border-radius: 6px; }
#GlassContent QTreeView::item:hover { background: %4; }
#GlassContent QTreeView::item:selected { background: %3; color: white; }
#GlassContent QHeaderView::section {
    background: transparent; border: none; color: %2; font-weight: 600; padding: 4px 6px;
}
#GlassContent QTabWidget::pane { border: none; }
#GlassContent QTabBar::tab {
    background: transparent; border: none; border-radius: 7px; padding: 5px 12px; margin: 2px; color: %2;
}
#GlassContent QTabBar::tab:selected { background: %6; color: %1; }
#GlassContent QScrollBar:vertical { background: transparent; width: 8px; margin: 2px; }
#GlassContent QScrollBar:horizontal { background: transparent; height: 8px; margin: 2px; }
#GlassContent QScrollBar::handle { background: %5; border-radius: 3px; min-height: 24px; min-width: 24px; }
#GlassContent QScrollBar::add-line, #GlassContent QScrollBar::sub-line { width: 0; height: 0; }
#GlassContent QScrollBar::add-page, #GlassContent QScrollBar::sub-page { background: transparent; }
#GlassContent QSplitter::handle { background: %8; height: 1px; }
QDialogButtonBox { dialogbuttonbox-buttons-have-icons: 0; }
QMenu { background: %9; border: 1px solid %7; border-radius: 10px; padding: 5px; }
QMenu::item { padding: 6px 22px 6px 12px; border-radius: 6px; margin: 1px 0; }
QMenu::item:selected { background: %3; color: white; }
QMenu::item:disabled { color: %2; }
QMenu::separator { height: 1px; background: %8; margin: 4px 8px; }
QMenu::icon { padding-left: 8px; }
QMessageBox, QDialog { background: %9; }
QMessageBox QPushButton, QDialog QPushButton { background: %6; border: 1px solid %7; border-radius: 7px; padding: 5px 16px; min-width: 64px; }
QMessageBox QPushButton:default, QDialog QPushButton:default { background: %3; color: white; border: none; }
QCheckBox::indicator { width: 16px; height: 16px; border-radius: 5px; border: 1px solid %7; background: %6; }
QCheckBox::indicator:checked { background: %3; border: none; image: url(:/mycad/icons/Check.svg); }
QToolTip { background: %6; color: %1; border: 1px solid %7; border-radius: 6px; padding: 4px 8px; }
)")
        .arg(t.text, t.secondary, t.accent, t.hover, t.pressed, t.field, t.fieldBorder, t.separator)
        .arg(t.dark ? QStringLiteral("#2C2C2E") : QStringLiteral("#FBFBFD"));
}

void applyTheme()
{
    const Theme t = theme();
    if (QFontDatabase::families().contains(QStringLiteral("Inter"))) {
        QFont font(QStringLiteral("Inter"));
        font.setPixelSize(13);
        QApplication::setFont(font);
    }
    qApp->setStyleSheet(styleSheet(t));
    overrideFreeCadIcons(t);
    TreeWidget::reloadDocumentPixmap();  // der Baum hat sein Dokument-Icon schon beim Start geladen

    // 3D-Hintergrund: ruhiger Verlauf passend zum Theme (Farben als 0xRRGGBBAA)
    auto view = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/View");
    view->SetBool("RadialGradient", false);
    view->SetBool("UseBackgroundColorMid", false);
    view->SetUnsigned("BackgroundColor2", t.dark ? 0x2A2C31FFUL : 0xF4F5F7FFUL);
    view->SetUnsigned("BackgroundColor3", t.dark ? 0x111214FFUL : 0xD5D9E0FFUL);
    view->SetBool("Gradient", true);
    view->SetBool("ShowNaviCube", false);  // eigener ViewCube (Shell/ViewCube)
    view->SetInt("AntiAliasing", 3);       // MSAA 4x: glatte Kanten (8x lässt Coin auf Intel/Mesa Flächen verlieren)
    view->SetUnsigned("SelectionColor", t.dark ? 0x0A84FFFFUL : 0x007AFFFFUL);

    // Skizzenfarben wie in Fusion (FreeCADs Vorgaben sind für dunkle Hintergründe gedacht):
    // unterbestimmt blau, voll bestimmt schwarz/weiß, Konstruktion orange, projiziert lila
    const unsigned long ink = t.dark ? 0xF5F5F7FFUL : 0x1D1D1FFFUL;
    const unsigned long soft = t.dark ? 0xC7C7CCFFUL : 0x3C3C43FFUL;
    view->SetUnsigned("EditedEdgeColor", t.dark ? 0x5AA9FFFFUL : 0x1E73E8FFUL);
    view->SetUnsigned("FullyConstrainedColor", ink);
    view->SetUnsigned("FullyConstraintElementColor", ink);
    view->SetUnsigned("ConstructionColor", 0xFF9500FFUL);
    view->SetUnsigned("FullyConstraintConstructionElementColor", 0xC77700FFUL);
    view->SetUnsigned("InternalAlignedGeoColor", 0x8E8E93FFUL);
    view->SetUnsigned("FullyConstraintInternalAlignmentColor", 0x636366FFUL);
    view->SetUnsigned("ExternalColor", 0xAF52DEFFUL);
    view->SetUnsigned("ExternalDefiningColor", 0x8944ABFFUL);
    view->SetUnsigned("SketchEdgeColor", soft);
    view->SetUnsigned("SketchVertexColor", soft);
    view->SetUnsigned("ConstrainedDimColor", soft);
    view->SetUnsigned("ConstrainedIcoColor", soft);
    view->SetUnsigned("CursorTextColor", soft);

    // B-Splines wie in Fusion: nur das Kontrollpolygon, keine Analyse-Überlagerungen (Kamm, Gewichte, Knoten)
    auto sketcher = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/Sketcher/General");
    sketcher->SetBool("BSplineCombVisible", false);
    sketcher->SetBool("BSplinePoleWeightVisible", false);
    sketcher->SetBool("BSplineKnotMultiplicityVisible", false);
    sketcher->SetBool("BSplineDegreeVisible", false);
    view->SetUnsigned("HighlightColor", t.dark ? 0x64B5FFFFUL : 0x66AFFFFFUL);
    view->SetUnsigned("DefaultShapeColor", t.dark ? 0x9EA3ADFFUL : 0xC8CCD4FFUL);
    view->SetUnsigned("DefaultShapeLineColor", t.dark ? 0x2A2D33FFUL : 0x6B717CFFUL);
    view->SetInt("DefaultShapeLineWidth", 1);

    // ViewCube: hell/dunkel wie die Glass-Panels, runde Kanten, Inter, Akzentfarbe beim Überfahren
    auto cube = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/NaviCube");
    cube->SetInt("CubeSize", 112);
    cube->SetFloat("ChamferSize", 0.1);
    cube->SetFloat("BorderWidth", 0.6);
    cube->SetFloat("FontZoom", 0.34);
    cube->SetASCII("FontString", "Inter");
    cube->SetInt("FontWeight", 600);
    cube->SetBool("ShowCS", false);
    cube->SetInt("InactiveOpacity", 90);
    cube->SetInt("OffsetY", 6);
    cube->SetUnsigned("BaseColor", t.dark ? 0x3A3B40F0UL : 0xF7F8FAF0UL);
    cube->SetUnsigned("EmphaseColor", t.dark ? 0xEBEBF0FFUL : 0x3C3C43FFUL);
    cube->SetUnsigned("HiliteColor", t.dark ? 0x0A84FFFFUL : 0x007AFFFFUL);
}

/// Bunte FreeCAD-Icons neutral einfärben, Schattierung bleibt erhalten.
/// ponytail: Übergang bis zum eigenen Icon-Set (Phase 3)
QIcon neutralIcon(const QIcon& icon, bool dark)
{
    QIcon out;
    for (int s : {22, 44}) {
        QImage img = icon.pixmap(s, s).toImage().convertToFormat(QImage::Format_ARGB32);
        for (int y = 0; y < img.height(); ++y) {
            auto line = reinterpret_cast<QRgb*>(img.scanLine(y));
            for (int x = 0; x < img.width(); ++x) {
                const QRgb c = line[x];
                const double lum = (0.299 * qRed(c) + 0.587 * qGreen(c) + 0.114 * qBlue(c)) / 255.0;
                const int g = dark ? int(120 + lum * 135) : int(35 + lum * 165);
                line[x] = qRgba(g, g, g, qAlpha(c));
            }
        }
        out.addPixmap(QPixmap::fromImage(img));
        // Deaktiviert: deutlich blasser, damit man sieht, was gerade nicht anklickbar ist
        QImage faded = img;
        for (int y = 0; y < faded.height(); ++y) {
            auto line = reinterpret_cast<QRgb*>(faded.scanLine(y));
            for (int x = 0; x < faded.width(); ++x) {
                line[x] = qRgba(qRed(line[x]), qGreen(line[x]), qBlue(line[x]), qAlpha(line[x]) * 3 / 10);
            }
        }
        out.addPixmap(QPixmap::fromImage(faded), QIcon::Disabled);
    }
    return out;
}

/// Eigenes MyCAD-Icon (src/Gui/Shell/icons, tools/make_icons.py) in der Textfarbe des Themes, sonst leer
QIcon designIcon(const QString& name)
{
    QFile file(QStringLiteral(":/mycad/icons/%1.svg").arg(name));
    if (!file.open(QIODevice::ReadOnly)) {
        return {};
    }
    const QByteArray svg = file.readAll().replace("currentColor", theme().text.toLatin1());
    QSvgRenderer renderer(svg);
    QIcon icon;
    for (int s : {22, 44}) {
        for (bool faded : {false, true}) {
            QImage img(s, s, QImage::Format_ARGB32_Premultiplied);
            img.fill(Qt::transparent);
            QPainter p(&img);
            p.setOpacity(faded ? 0.3 : 1.0);  // deaktiviert: blass
            renderer.render(&p);
            p.end();
            icon.addPixmap(QPixmap::fromImage(img), faded ? QIcon::Disabled : QIcon::Normal);
        }
    }
    return icon;
}

/// Icon für einen Befehl: eigenes MyCAD-Icon, sonst das FreeCAD-Icon neutral eingefärbt
QIcon commandIcon(const QString& name, const QIcon& fallback)
{
    QIcon icon = designIcon(name);
    return icon.isNull() ? neutralIcon(fallback, theme().dark) : icon;
}

/// FreeCAD-Icons, die im Browser, in Menüs, Meldungen und im Skizzenbild auftauchen, durch eigene ersetzen.
/// Der BitmapFactory-Cache wird vor jeder Datei gefragt, also gewinnen diese Einträge überall.
void overrideFreeCadIcons(const Theme& t)
{
    const QString grey = t.dark ? QStringLiteral("#AEAEB2") : QStringLiteral("#6E6E73");
    struct Override
    {
        const char* freecad;
        const char* ours;
        QString color;
    };
    const Override overrides[] = {
        {"Document", "Tree_Document", grey},
        {"Geofeaturegroup.svg", "Tree_Component", t.accent},
        {"folder", "Tree_Folder", t.accent},
        {"Std_CoordinateSystem", "Tree_Origin", grey},
        {"Std_Axis", "Tree_Axis", grey},
        {"Std_Plane", "Tree_Plane", grey},
        {"Std_Point", "Tree_Point", grey},
        {"PartDesign_Body", "Tree_Body", t.accent},
        {"Sketcher_Sketch", "Tree_Sketch", t.accent},
        {"TreeItemVisible", "Tree_Visible", grey},
        {"TreeItemInvisible", "Tree_Invisible", grey},
        {"Sketcher_NotFullyConstrained", "Badge_Dot", QStringLiteral("#FF9500")},
        {":/icons/Warning.svg", "Badge_Warning", QStringLiteral("#FF9500")},
        {":/icons/info.svg", "Badge_Info", t.accent},
        {":/icons/critical-info.svg", "Badge_Error", QStringLiteral("#FF3B30")},
        {"Constraint_Horizontal", "Sketcher_ConstrainHorizontal", grey},
        {"Constraint_Vertical", "Sketcher_ConstrainVertical", grey},
        {"Constraint_Parallel", "Sketcher_ConstrainParallel", grey},
        {"Constraint_Perpendicular", "Sketcher_ConstrainPerpendicular", grey},
        {"Constraint_Tangent", "Sketcher_ConstrainTangent", grey},
        {"Constraint_EqualLength", "Sketcher_ConstrainEqual", grey},
        {"Constraint_Symmetric", "Sketcher_ConstrainSymmetric", grey},
        {"Constraint_Block", "Sketcher_ConstrainBlock", grey},
        {"Constraint_PointOnObject", "Sketcher_ConstrainCoincidentUnified", grey},
    };
    for (const auto& o : overrides) {
        QFile file(QStringLiteral(":/mycad/icons/%1.svg").arg(QString::fromLatin1(o.ours)));
        if (!file.open(QIODevice::ReadOnly)) {
            continue;
        }
        QSvgRenderer renderer(file.readAll().replace("currentColor", o.color.toLatin1()));
        QImage img(64, 64, QImage::Format_ARGB32_Premultiplied);
        img.fill(Qt::transparent);
        QPainter p(&img);
        renderer.render(&p, QRectF(4, 4, 56, 56));  // etwas Luft wie bei den FreeCAD-Icons
        p.end();
        BitmapFactory().addPixmapToCache(o.freecad, QPixmap::fromImage(img));
    }
}

QWidget* content()
{
    auto w = new QWidget;
    w->setObjectName(QStringLiteral("GlassContent"));
    return w;
}

/// QAction eines Befehls; hängt sie ans Hauptfenster, damit ihr Tastenkürzel auch ohne Menü/Toolbar wirkt
QAction* commandAction(const char* name)
{
    static QWidget sink;  // Command::addTo legt die QAction erst beim ersten Einfügen an
    Command* cmd = Application::Instance->commandManager().getCommandByName(name);
    if (!cmd) {
        return nullptr;
    }
    if (!cmd->getAction()) {
        cmd->addTo(&sink);
    }
    QAction* action = cmd->getAction()->action();
    getMainWindow()->addAction(action);
    return action;
}

/// Kapsel-Toolbar mit Befehls-Buttons. "" = Trenner.
QWidget* toolbar(const std::vector<const char*>& commands)
{

    auto w = content();
    auto lay = new QHBoxLayout(w);
    lay->setContentsMargins(10, 6, 10, 6);
    lay->setSpacing(2);
    for (const char* name : commands) {
        if (!*name) {
            auto sep = new QFrame;
            sep->setObjectName(QStringLiteral("GlassSeparator"));
            sep->setFixedSize(1, 22);
            lay->addSpacing(6);
            lay->addWidget(sep);
            lay->addSpacing(6);
            continue;
        }
        QAction* action = commandAction(name);
        if (!action) {
            continue;
        }
        auto btn = new QToolButton;
        btn->setObjectName(QStringLiteral("GlassButton"));
        btn->setProperty("command", QString::fromLatin1(name));
        if (std::string(name) == "Sketcher_LeaveSketch") {  // wie in Fusion: deutlicher Abschluss-Knopf
            btn->setObjectName(QStringLiteral("GlassProminent"));
            btn->setText(QStringLiteral("Finish Sketch"));
            btn->setToolTip(QStringLiteral("Finish Sketch"));
            btn->setFixedHeight(30);
            QObject::connect(btn, &QToolButton::clicked, action, [action] {
                QTimer::singleShot(0, action, &QAction::trigger);
            });
            lay->addSpacing(6);
            lay->addWidget(btn);
            continue;
        }
        btn->setIcon(commandIcon(QString::fromLatin1(name), action->icon()));
        btn->setIconSize(QSize(22, 22));
        btn->setFixedSize(38, 38);
        btn->setToolTip(action->toolTip().isEmpty() ? action->text() : action->toolTip());
        btn->setEnabled(action->isEnabled());
        // Erst nach dem Mausklick auslösen: Befehle bauen die Oberfläche um (neue Ansicht, Dialog, Edit-Modus),
        // während Qt den Klick noch an das Proxy-Widget weiterreicht. Synchron führte das zum Absturz.
        QObject::connect(btn, &QToolButton::clicked, action, [action] {
            QTimer::singleShot(0, action, &QAction::trigger);
        });
        QObject::connect(action, &QAction::changed, btn, [btn, action] {
            btn->setEnabled(action->isEnabled());
        });
        lay->addWidget(btn);
    }
    w->adjustSize();
    return w;
}

/// FreeCAD-Dock-Fenster (Baum, Aufgaben) aus dem Dock lösen, damit es in ein Glass-Panel kann.
QWidget* takeDockWindow(const char* name)
{
    auto mgr = DockWindowManager::instance();
    QWidget* w = mgr->findRegisteredDockWindow(name);
    if (!w) {
        return nullptr;
    }
    w->setProperty("mycadEmbedded", true);  // DockWindowManager::setup dockt es dann nicht wieder an
    mgr->removeDockWindow(w);
    w->setParent(nullptr);

    auto box = content();
    auto lay = new QVBoxLayout(box);
    lay->setContentsMargins(8, 8, 8, 8);
    lay->addWidget(w);
    w->show();
    for (auto area : box->findChildren<QAbstractScrollArea*>()) {
        area->setFrameShape(QFrame::NoFrame);
        area->viewport()->setAutoFillBackground(false);
    }
    // Wie in Fusion zeigt der Browser nur den Baum; Einstellungen haben eigene Dialoge
    for (auto child : box->findChildren<QWidget*>()) {
        if (std::string(child->metaObject()->className()) == "Gui::PropertyView") {
            child->hide();
        }
    }
    return box;
}

/// Timeline-Eintrag: Klick wählt aus, Doppelklick bearbeitet (wie in Fusion)
class TimelineButton: public QToolButton
{
public:
    std::function<void()> onDoubleClick;

protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override
    {
        event->accept();
        if (onDoubleClick) {
            QTimer::singleShot(0, onDoubleClick);  // nicht mitten im Maus-Event den Edit-Modus starten
        }
    }
};

/// Rahmenloses Fenster: Knöpfe wie macOS + Dokumentname; Ziehen verschiebt, Doppelklick maximiert
class TitleBar: public QWidget
{
public:
    TitleBar()
    {
        setObjectName(QStringLiteral("GlassContent"));
        auto lay = new QHBoxLayout(this);
        lay->setContentsMargins(14, 0, 16, 0);
        lay->setSpacing(8);
        auto light = [&](const char* role, std::function<void()> action) {
            auto btn = new QToolButton;
            btn->setObjectName(QStringLiteral("TrafficLight"));
            btn->setProperty("role", QString::fromLatin1(role));
            btn->setFixedSize(12, 12);
            btn->setCursor(Qt::ArrowCursor);
            QObject::connect(btn, &QToolButton::clicked, btn, [action] { QTimer::singleShot(0, action); });
            lay->addWidget(btn);
        };
        light("close", [] { getMainWindow()->close(); });
        light("minimize", [] { getMainWindow()->showMinimized(); });
        light("zoom", toggleMaximized);
        lay->addSpacing(8);
        title = new QLabel;
        title->setObjectName(QStringLiteral("WindowTitle"));
        lay->addWidget(title);
        lay->addStretch();
        setFixedHeight(50);
    }

    void setTitle(const QString& text)
    {
        title->setText(text);
        adjustSize();
    }

    static void toggleMaximized()
    {
        MainWindow* mw = getMainWindow();
        mw->isMaximized() ? mw->showNormal() : mw->showMaximized();
    }

protected:
    void mousePressEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton && getMainWindow()->windowHandle()) {
            getMainWindow()->windowHandle()->startSystemMove();
        }
    }
    void mouseDoubleClickEvent(QMouseEvent*) override
    {
        QTimer::singleShot(0, toggleMaximized);
    }

private:
    QLabel* title;
};

/// Menüs mit runden Ecken: dafür brauchen sie einen transparenten, rahmenlosen Hintergrund
class MenuPolisher: public QObject
{
protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (event->type() == QEvent::Polish) {
            if (auto menu = qobject_cast<QMenu*>(obj)) {
                menu->setAttribute(Qt::WA_TranslucentBackground);
                menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
            }
        }
        return false;
    }
};

/// Eigenes Kontextmenü aus Befehlen; "" = Trenner, "@rename" = Umbenennen im Browser
void showCommandMenu(const std::vector<std::pair<QString, const char*>>& entries, QTreeWidget* tree = nullptr)
{
    QMenu menu;
    auto& mgr = Application::Instance->commandManager();
    for (const auto& [label, command] : entries) {
        if (!*command) {
            if (!menu.isEmpty() && !menu.actions().back()->isSeparator()) {
                menu.addSeparator();  // keine doppelten oder führenden Trenner
            }
            continue;
        }
        if (std::string(command) == "@rename") {
            const auto items = tree ? tree->selectedItems() : QList<QTreeWidgetItem*>();
            if (items.size() == 1) {
                QTreeWidgetItem* item = items.front();
                menu.addAction(QStringLiteral("Rename"), [tree, item] { tree->editItem(item); });
            }
            continue;
        }
        Command* cmd = mgr.getCommandByName(command);
        if (!cmd || !cmd->isActive()) {
            continue;
        }
        QAction* action = menu.addAction(label);
        action->setIcon(designIcon(QString::fromLatin1(command)));
        const std::string name = command;
        QObject::connect(action, &QAction::triggered, [name] {
            QTimer::singleShot(0, [name] { Application::Instance->commandManager().runCommandByName(name.c_str()); });
        });
    }
    if (!menu.isEmpty() && menu.actions().back()->isSeparator()) {
        menu.removeAction(menu.actions().back());
    }
    if (!menu.isEmpty()) {
        menu.exec(QCursor::pos());
    }
}

/// Rechtsklick ohne Ziehen im 3D-Fenster bzw. im Browser: eigene, aufgeräumte Menüs statt der FreeCAD-Menüs
class ContextMenus: public QObject
{
protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        auto widget = qobject_cast<QWidget*>(obj);
        if (!widget) {
            return false;
        }
        if (auto tree = qobject_cast<QTreeWidget*>(widget->parentWidget());
            tree && event->type() == QEvent::ContextMenu) {
            QTimer::singleShot(0, [tree] {
                const bool any = !Selection().getSelection().empty();
                if (!any) {
                    return;
                }
                showCommandMenu({{QStringLiteral("Show / Hide"), "Std_ToggleVisibility"},
                                 {QString(), "@rename"},
                                 {QString(), ""},
                                 {QStringLiteral("Move"), "Design_Move"},
                                 {QStringLiteral("Export"), "Design_Export"},
                                 {QString(), ""},
                                 {QStringLiteral("Delete"), "Design_Delete"}},
                                tree);
            });
            return true;
        }
        if (qobject_cast<QGraphicsView*>(widget->parentWidget())) {
            auto me = static_cast<QMouseEvent*>(event);
            if (event->type() == QEvent::MouseButtonPress && me->button() == Qt::RightButton) {
                pressPos = me->globalPosition().toPoint();
            }
            else if (event->type() == QEvent::MouseButtonRelease && me->button() == Qt::RightButton
                     && (me->globalPosition().toPoint() - pressPos).manhattanLength() < 5) {
                QTimer::singleShot(0, [] {
                    if (Control().activeDialog()) {
                        return;
                    }
                    showCommandMenu({{QStringLiteral("Undo"), "Std_Undo"},
                                     {QStringLiteral("Redo"), "Std_Redo"},
                                     {QString(), ""},
                                     {QStringLiteral("Create Sketch"), "Design_CreateSketch"},
                                     {QStringLiteral("Extrude"), "Design_Extrude"},
                                     {QStringLiteral("Press Pull"), "Design_PressPull"},
                                     {QStringLiteral("Fillet"), "Design_Fillet"},
                                     {QStringLiteral("Hole"), "Design_Hole"},
                                     {QStringLiteral("Move"), "Design_Move"},
                                     {QString(), ""},
                                     {QStringLiteral("Show / Hide"), "Std_ToggleVisibility"},
                                     {QStringLiteral("Delete"), "Design_Delete"},
                                     {QString(), ""},
                                     {QStringLiteral("Fit All"), "Std_ViewFitAll"}});
                });
            }
        }
        return false;
    }

private:
    QPoint pressPos;
};

/// Größe ändern an den Rändern des rahmenlosen Fensters
class EdgeResizer: public QObject
{
protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (event->type() != QEvent::MouseMove && event->type() != QEvent::MouseButtonPress) {
            return false;
        }
        MainWindow* mw = getMainWindow();
        auto widget = qobject_cast<QWidget*>(obj);
        if (!mw->isVisible() || mw->isMaximized() || !widget || widget->window() != mw || !mw->windowHandle()) {
            return false;
        }
        auto me = static_cast<QMouseEvent*>(event);
        const QPoint p = mw->mapFromGlobal(me->globalPosition().toPoint());
        constexpr int border = 6;
        Qt::Edges edges;
        if (p.x() < border) {
            edges |= Qt::LeftEdge;
        }
        if (p.x() > mw->width() - border) {
            edges |= Qt::RightEdge;
        }
        if (p.y() < border) {
            edges |= Qt::TopEdge;
        }
        if (p.y() > mw->height() - border) {
            edges |= Qt::BottomEdge;
        }
        if (event->type() == QEvent::MouseMove && me->buttons() == Qt::NoButton) {
            const bool diagonal = (edges & (Qt::LeftEdge | Qt::RightEdge)) && (edges & (Qt::TopEdge | Qt::BottomEdge));
            const bool falling = edges == (Qt::LeftEdge | Qt::TopEdge) || edges == (Qt::RightEdge | Qt::BottomEdge);
            const Qt::CursorShape shape = !edges ? Qt::ArrowCursor
                : diagonal ? (falling ? Qt::SizeFDiagCursor : Qt::SizeBDiagCursor)
                : (edges & (Qt::LeftEdge | Qt::RightEdge)) ? Qt::SizeHorCursor
                                                           : Qt::SizeVerCursor;
            if (edges && !overriding) {
                QApplication::setOverrideCursor(shape);
                overriding = true;
            }
            else if (edges && overriding) {
                QApplication::changeOverrideCursor(shape);
            }
            else if (!edges && overriding) {
                QApplication::restoreOverrideCursor();
                overriding = false;
            }
            return false;
        }
        if (event->type() == QEvent::MouseButtonPress && edges && me->button() == Qt::LeftButton) {
            mw->windowHandle()->startSystemResize(edges);
            return true;
        }
        return false;
    }

private:
    bool overriding = false;
};

/// Skizzen und Design-Features in Dokument-Reihenfolge. Typen per Name, damit die Shell nicht vom Design-Modul abhängt.
bool isTimelineItem(const App::DocumentObject* obj)
{
    static const Base::Type sketch = Base::Type::fromName("Sketcher::SketchObject");
    static const Base::Type feature = Base::Type::fromName("Design::Feature");
    const Base::Type t = obj->getTypeId();
    return (!sketch.isBad() && t.isDerivedFrom(sketch)) || (!feature.isBad() && t.isDerivedFrom(feature));
}

/// Sketch Palette wie in Fusion: ersetzt im Skizzenmodus FreeCADs Skizzen-Panel
QWidget* sketchPalette()
{
    auto box = content();
    auto lay = new QVBoxLayout(box);
    lay->setContentsMargins(14, 12, 14, 14);
    lay->setSpacing(4);
    auto title = new QLabel(QStringLiteral("Sketch Palette"));
    title->setObjectName(QStringLiteral("WindowTitle"));
    lay->addWidget(title);
    lay->addSpacing(4);
    const std::pair<const char*, const char*> rows[] = {
        {"Look At", "Sketcher_ViewSketch"}, {"Slice", "Sketcher_ViewSection"}, {"Grid", "Sketcher_Grid"},
        {"Snap", "Sketcher_Snap"},          {"Construction", "Sketcher_ToggleConstruction"},
    };
    const char* icons[] = {"Palette_LookAt", "Palette_Section", "Palette_Grid", "Palette_Snap",
                           "Sketcher_ToggleConstruction"};
    for (size_t i = 0; i < std::size(rows); ++i) {
        QAction* action = commandAction(rows[i].second);
        if (!action) {
            continue;
        }
        auto btn = new QToolButton;
        btn->setObjectName(QStringLiteral("PaletteRow"));
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btn->setText(QString::fromLatin1(rows[i].first));
        btn->setIcon(designIcon(QString::fromLatin1(icons[i])));
        btn->setIconSize(QSize(18, 18));
        btn->setCheckable(action->isCheckable());
        btn->setChecked(action->isChecked());
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        btn->setFixedHeight(32);
        QObject::connect(btn, &QToolButton::clicked, action, [action] {
            QTimer::singleShot(0, action, &QAction::trigger);
        });
        QObject::connect(action, &QAction::changed, btn, [btn, action] { btn->setChecked(action->isChecked()); });
        lay->addWidget(btn);
    }
    lay->addSpacing(8);
    if (QAction* finish = commandAction("Sketcher_LeaveSketch")) {
        auto btn = new QToolButton;
        btn->setObjectName(QStringLiteral("GlassProminent"));
        btn->setText(QStringLiteral("Finish Sketch"));
        btn->setFixedHeight(32);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        QObject::connect(btn, &QToolButton::clicked, finish, [finish] {
            QTimer::singleShot(0, finish, &QAction::trigger);
        });
        lay->addWidget(btn);
    }
    box->setFixedWidth(220);
    box->adjustSize();
    return box;
}

struct State
{
    GlassPanel* modelBar = nullptr;
    GlassPanel* sketchBar = nullptr;
    GlassPanel* browser = nullptr;
    GlassPanel* inspector = nullptr;
    GlassPanel* timeline = nullptr;
    GlassPanel* titleBar = nullptr;
    GlassPanel* palette = nullptr;
    ViewCube* viewCube = nullptr;
    bool sketchMode = false;
    QGraphicsScene* scene = nullptr;
} state;

std::vector<GlassPanel*> panels()
{
    std::vector<GlassPanel*> all;
    for (auto p : {state.modelBar, state.sketchBar, state.browser, state.inspector, state.timeline, state.titleBar,
                   state.palette}) {
        if (p) {
            all.push_back(p);
        }
    }
    return all;
}

void layout()
{
    if (!state.scene) {
        return;
    }
    const QRectF r = state.scene->sceneRect();
    const qreal m = 12;
    GlassPanel* bar = state.sketchMode ? state.sketchBar : state.modelBar;
    state.modelBar->setVisible(!state.sketchMode);
    state.sketchBar->setVisible(state.sketchMode);
    const QSizeF bs = bar->content()->sizeHint();
    bar->setGeometry(QRectF(r.center().x() - bs.width() / 2, m, bs.width(), bs.height()));

    qreal bottom = r.height() - m;
    if (state.timeline) {
        const QSizeF ts = state.timeline->content()->sizeHint();
        const bool show = state.timeline->content()->property("count").toInt() > 0;
        state.timeline->setVisible(show);
        state.timeline->setGeometry(
            QRectF(r.center().x() - ts.width() / 2, r.height() - m - ts.height(), ts.width(), ts.height())
        );
    }

    const qreal top = m + bs.height() + m;
    if (state.browser) {
        state.browser->setGeometry(QRectF(m, top, 290, bottom - top));
    }
    if (state.titleBar) {
        const QSizeF ts = state.titleBar->content()->sizeHint();
        state.titleBar->setGeometry(QRectF(m, m, ts.width(), bs.height()));
    }
    if (state.palette) {
        QSizeF ps = state.palette->content()->sizeHint();
        ps.setWidth(std::max<qreal>(ps.width(), state.palette->content()->minimumWidth()));
        state.palette->setVisible(state.sketchMode);
        state.palette->setGeometry(QRectF(r.width() - ps.width() - m, 170, ps.width(), ps.height()));
    }
    if (state.viewCube) {
        state.viewCube->setPos(r.width() - state.viewCube->boundingRect().width() - m, m);
    }
    if (state.inspector) {
        const qreal itop = 170;  // unter dem ViewCube
        // Im Skizzenmodus übernimmt die Sketch Palette (FreeCADs Skizzen-Panel bleibt verborgen aktiv)
        state.inspector->setVisible(Control().activeDialog() != nullptr && !state.sketchMode);
        state.inspector->setGeometry(QRectF(r.width() - 340 - m, itop, 340, bottom - itop));
    }
}

/// Objekt mit der Timeline-Reihenfolge (Root-Komponente des Design-Moduls), sonst nullptr
App::DocumentObject* timelineHolder(App::Document* doc)
{
    for (auto obj : doc ? doc->getObjects() : std::vector<App::DocumentObject*>()) {
        if (freecad_cast<App::PropertyLinkList*>(obj->getPropertyByName("Timeline"))) {
            return obj;
        }
    }
    return nullptr;
}

std::vector<App::DocumentObject*> timelineItems(App::Document* doc)
{
    std::vector<App::DocumentObject*> items;
    if (auto holder = timelineHolder(doc)) {
        items = static_cast<App::PropertyLinkList*>(holder->getPropertyByName("Timeline"))->getValues();
        std::erase(items, nullptr);
        return items;
    }
    for (auto obj : doc ? doc->getObjects() : std::vector<App::DocumentObject*>()) {
        if (isTimelineItem(obj)) {
            items.push_back(obj);
        }
    }
    return items;
}

int timelineMarker(App::Document* doc)
{
    auto holder = timelineHolder(doc);
    auto prop = holder ? freecad_cast<App::PropertyInteger*>(holder->getPropertyByName("RollbackMarker")) : nullptr;
    return prop ? static_cast<int>(prop->getValue()) : -1;
}

/// Rollback-Marker setzen: nur die ersten n Einträge sind aktiv (-1 = alle)
void setTimelineMarker(App::Document* doc, int n)
{
    auto holder = timelineHolder(doc);
    auto prop = holder ? freecad_cast<App::PropertyInteger*>(holder->getPropertyByName("RollbackMarker")) : nullptr;
    if (!prop || Control().activeDialog()) {
        return;
    }
    const int count = static_cast<int>(timelineItems(doc).size());
    doc->openTransaction("Roll Back");
    prop->setValue(n < 0 || n >= count ? -1 : n);
    for (auto obj : doc->getObjects()) {
        if (obj->getPropertyByName("Suppressed")) {  // Features neu berechnen lassen
            obj->touch();
        }
    }
    doc->recompute();
    doc->commitTransaction();
}

/// Timeline-Leiste neu aufbauen (nach jeder Änderung am Dokument, gebündelt)
void rebuildTimeline()
{
    if (!state.timeline) {
        return;
    }
    QWidget* box = state.timeline->content();
    auto lay = static_cast<QHBoxLayout*>(box->layout());
    while (QLayoutItem* item = lay->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    int count = 0;
    App::Document* doc = App::GetApplication().getActiveDocument();
    Gui::Document* gdoc = doc ? Application::Instance->getDocument(doc) : nullptr;
    const auto items = timelineItems(doc);
    const int marker = timelineMarker(doc);
    const int total = static_cast<int>(items.size());

    // Wiedergabe-Knöpfe wie in Fusion: Anfang, zurück, vor, Ende
    if (gdoc && timelineHolder(doc) && total > 0) {
        const std::string docName = doc->getName();
        auto play = [&](const char* icon, std::function<int(int)> target) {
            auto btn = new QToolButton;
            btn->setObjectName(QStringLiteral("GlassButton"));
            btn->setIcon(designIcon(QString::fromLatin1(icon)));
            btn->setIconSize(QSize(18, 18));
            btn->setFixedSize(28, 36);
            QObject::connect(btn, &QToolButton::clicked, btn, [docName, target] {
                QTimer::singleShot(0, [docName, target] {
                    if (App::Document* d = App::GetApplication().getDocument(docName.c_str())) {
                        setTimelineMarker(d, target(timelineMarker(d)));
                    }
                });
            });
            lay->addWidget(btn);
        };
        play("Timeline_Start", [](int) { return 0; });
        play("Timeline_Back", [total](int m) { return std::max(0, (m < 0 ? total : m) - 1); });
        play("Timeline_Forward", [](int m) { return m < 0 ? -1 : m + 1; });
        play("Timeline_End", [](int) { return -1; });
        auto sep = new QFrame;
        sep->setObjectName(QStringLiteral("GlassSeparator"));
        sep->setFixedSize(1, 22);
        lay->addSpacing(4);
        lay->addWidget(sep);
        lay->addSpacing(4);
    }
    auto markerLine = [&] {
        auto line = new QFrame;
        line->setObjectName(QStringLiteral("TimelineMarker"));
        line->setFixedSize(4, 30);
        lay->addWidget(line);
    };

    for (int index = 0; index < total && gdoc; ++index) {
        App::DocumentObject* obj = items[index];
        if (index == marker) {
            markerLine();
        }
        auto vp = gdoc->getViewProvider(obj);
        auto btn = new TimelineButton;
        btn->setObjectName(QStringLiteral("GlassButton"));
        // Timeline-Icon = Icon des Werkzeugs, das den Eintrag erzeugt hat ("Design::Extrude" -> "Design_Extrude")
        QString type = QString::fromLatin1(obj->getTypeId().getName()).replace(QStringLiteral("::"), QStringLiteral("_"));
        if (type.startsWith(QLatin1String("Sketcher_"))) {
            type = QStringLiteral("Design_CreateSketch");
        }
        btn->setIcon(commandIcon(type, vp ? vp->getIcon() : QIcon()));
        btn->setIconSize(QSize(22, 22));
        btn->setFixedSize(36, 36);
        btn->setToolTip(QString::fromUtf8(obj->Label.getValue())
                        + (obj->isError() ? QStringLiteral("\n") + QString::fromUtf8(obj->getStatusString())
                                          : QString()));
        btn->setProperty("error", obj->isError());
        auto suppressed = freecad_cast<App::PropertyBool*>(obj->getPropertyByName("Suppressed"));
        const bool rolledBack = marker >= 0 && index >= marker;
        if ((suppressed && suppressed->getValue()) || rolledBack) {
            btn->setIcon(QIcon(btn->icon().pixmap(QSize(44, 44), QIcon::Disabled)));  // unterdrückt: blass
        }
        const App::DocumentObjectT ref(obj);
        btn->setContextMenuPolicy(Qt::CustomContextMenu);
        QObject::connect(btn, &QWidget::customContextMenuRequested, btn, [ref] {
            auto o = ref.getObject();
            if (!o || Control().activeDialog()) {
                return;
            }
            QMenu menu;
            QAction* edit = menu.addAction(QStringLiteral("Edit"));
            QAction* rollback = timelineHolder(o->getDocument()) ? menu.addAction(QStringLiteral("Roll Back to Here")) : nullptr;
            QAction* suppress = nullptr;
            if (auto prop = freecad_cast<App::PropertyBool*>(o->getPropertyByName("Suppressed"))) {
                suppress = menu.addAction(prop->getValue() ? QStringLiteral("Unsuppress") : QStringLiteral("Suppress"));
            }
            menu.addSeparator();
            QAction* remove = menu.addAction(QStringLiteral("Delete"));
            QAction* chosen = menu.exec(QCursor::pos());
            // Nach dem Menü ausführen, nicht innerhalb des Maus-Events
            QTimer::singleShot(0, [ref, chosen, edit, rollback, suppress, remove] {
                auto o = ref.getObject();
                if (!o || !chosen) {
                    return;
                }
                App::Document* doc = o->getDocument();
                if (chosen == rollback) {
                    const auto all = timelineItems(doc);
                    setTimelineMarker(doc, static_cast<int>(std::ranges::find(all, o) - all.begin()) + 1);
                }
                else if (chosen == edit) {
                    auto gd = Application::Instance->getDocument(doc);
                    gd->setEdit(gd->getViewProvider(o));
                }
                else if (chosen == suppress) {
                    auto prop = static_cast<App::PropertyBool*>(o->getPropertyByName("Suppressed"));
                    doc->openTransaction(prop->getValue() ? "Unsuppress" : "Suppress");
                    prop->setValue(!prop->getValue());
                    doc->recompute();
                    doc->commitTransaction();
                }
                else if (chosen == remove) {
                    Selection().clearSelection();
                    Selection().addSelection(doc->getName(), o->getNameInDocument());
                    auto& mgr = Application::Instance->commandManager();
                    mgr.runCommandByName(mgr.getCommandByName("Design_Delete") ? "Design_Delete" : "Std_Delete");
                }
            });
        });
        QObject::connect(btn, &QToolButton::clicked, btn, [ref] {
            if (auto o = ref.getObject()) {
                Selection().clearSelection();
                Selection().addSelection(o->getDocument()->getName(), o->getNameInDocument());
            }
        });
        btn->onDoubleClick = [ref] {
            auto o = ref.getObject();
            if (o && !Control().activeDialog()) {
                auto gd = Application::Instance->getDocument(o->getDocument());
                gd->setEdit(gd->getViewProvider(o));
            }
        };
        lay->addWidget(btn);
        ++count;
    }
    if (marker >= 0 && marker >= total && total > 0) {
        markerLine();
    }
    box->setProperty("count", count);
    if (state.titleBar) {
        static_cast<TitleBar*>(state.titleBar->content())
            ->setTitle(doc ? QString::fromUtf8(doc->Label.getValue()) : QStringLiteral("MyCAD"));
    }
    box->adjustSize();
    layout();
}

void rebuildTimelineLater()
{
    static QTimer* timer = [] {
        auto t = new QTimer(qApp);
        t->setSingleShot(true);
        t->setInterval(50);
        QObject::connect(t, &QTimer::timeout, rebuildTimeline);
        return t;
    }();
    timer->start();
}

void attach(View3DInventor* view)
{
    QGraphicsScene* scene = view->getViewer()->scene();
    if (scene == state.scene) {
        return;
    }
    state.scene = scene;
    for (auto p : panels()) {
        scene->addItem(p);  // entfernt es automatisch aus der vorherigen Szene
    }
    if (state.viewCube) {
        scene->addItem(state.viewCube);
        state.viewCube->setViewer(view->getViewer());
    }
    static ContextMenus* menus = new ContextMenus;
    view->getViewer()->setPopupMenuEnabled(false);  // FreeCAD-Menü aus, eigenes Menü über ContextMenus
    view->getViewer()->viewport()->installEventFilter(menus);
    if (!scene->property("mycadShell").toBool()) {
        scene->setProperty("mycadShell", true);
        QObject::connect(scene, &QGraphicsScene::sceneRectChanged, scene, [scene] {
            if (scene == state.scene) {
                layout();
            }
        });
        QObject::connect(scene, &QObject::destroyed, [scene] {
            if (scene == state.scene) {
                state.scene = nullptr;
            }
        });
    }
    layout();
}

void addActionsRecursive(QWidget* target, const QList<QAction*>& actions)
{
    for (auto a : actions) {
        if (a->menu()) {
            addActionsRecursive(target, a->menu()->actions());
        }
        else if (!a->isSeparator()) {
            target->addAction(a);
        }
    }
}

/// Menüs, Toolbars, Statusleiste und Docks ausblenden. Ihre Tastenkürzel bleiben über das Hauptfenster aktiv.
void hideChrome()
{
    MainWindow* mw = getMainWindow();
    addActionsRecursive(mw, mw->menuBar()->actions());
    mw->menuBar()->hide();
    mw->statusBar()->hide();
    for (auto tb : mw->findChildren<QToolBar*>()) {
        addActionsRecursive(mw, tb->actions());
        tb->hide();
    }
    for (auto dw : mw->findChildren<QDockWidget*>()) {
        dw->hide();
    }
}

void hideChromeLater()
{
    QTimer::singleShot(0, hideChrome);
}

}  // namespace

void Gui::Shell::install()
{
    applyTheme();

    // Design-Modul laden (Create Sketch, Extrude, …), egal welche Workbench zuletzt aktiv war
    Application::Instance->activateWorkbench("DesignWorkbench");
    registerSettings();

    state.modelBar = new GlassPanel(
        toolbar({"Std_New", "Std_Open", "Std_Save", "Design_Export", "", "Std_Undo", "Std_Redo", "",
                 "Design_CreateSketch", "Design_Extrude", "Design_Revolve", "",
                 "Design_Hole", "Design_PressPull", "Design_Fillet", "Design_Chamfer", "Design_Shell", "", "Design_Pattern",
                 "Design_Mirror", "Design_Combine", "Design_Move", "", "Design_OffsetPlane", "Design_NewComponent", "", "Std_ViewFitAll", "MyCAD_Settings"}),
        24);
    state.sketchBar = new GlassPanel(
        toolbar({"Sketcher_CreateLine", "Sketcher_CreatePolyline", "Sketcher_CreateRectangle",
                 "Sketcher_CreateCircle", "Sketcher_CreateArc", "Sketcher_CreateSlot",
                 "Sketcher_CompCreateRegularPolygon", "Sketcher_CreateBSpline", "Sketcher_CreateConic",
                 "Sketcher_CreatePoint", "Sketcher_CompExternal", "",
                 "Sketcher_CreateFillet", "Sketcher_Trimming", "Sketcher_Extend", "Sketcher_Split",
                 "Sketcher_ToggleConstruction", "", "Sketcher_Dimension",
                 "Sketcher_ConstrainCoincidentUnified", "Sketcher_ConstrainHorizontal",
                 "Sketcher_ConstrainVertical", "Sketcher_ConstrainParallel",
                 "Sketcher_ConstrainPerpendicular", "Sketcher_ConstrainTangent", "Sketcher_ConstrainEqual",
                 "Sketcher_ConstrainSymmetric", "Sketcher_ConstrainBlock", "", "Sketcher_LeaveSketch"}),
        24);
    state.viewCube = new ViewCube;
    state.palette = new GlassPanel(sketchPalette(), 20);
    qApp->installEventFilter(new MenuPolisher);
    // Rahmenloses Fenster wie eine macOS-App (abschaltbar: MainWindow/MyCADFrameless = false)
    auto mainGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MainWindow");
    if (mainGrp->GetBool("MyCADFrameless", true)) {
        MainWindow* mw = getMainWindow();
        const bool wasVisible = mw->isVisible();
        mw->setWindowFlag(Qt::FramelessWindowHint, true);
        if (wasVisible) {
            mw->show();
        }
        state.titleBar = new GlassPanel(new TitleBar, 24);
        qApp->installEventFilter(new EdgeResizer);
    }
    {
        auto box = content();
        auto lay = new QHBoxLayout(box);
        lay->setContentsMargins(10, 6, 10, 6);
        lay->setSpacing(2);
        state.timeline = new GlassPanel(box, 24);
    }
    if (QWidget* tree = takeDockWindow("Std_ComboView")) {
        static ContextMenus* menus = new ContextMenus;
        for (auto t : tree->findChildren<QTreeWidget*>()) {
            t->viewport()->installEventFilter(menus);
        }
        state.browser = new GlassPanel(tree, 20);
    }
    if (QWidget* tasks = takeDockWindow("Std_TaskView")) {
        state.inspector = new GlassPanel(tasks, 20);
    }

    // Entf löscht Timeline-Einträge mit neu verbundener Kette (Design_Delete fällt sonst auf Std_Delete zurück)
    if (QAction* del = commandAction("Design_Delete")) {
        if (QAction* std = commandAction("Std_Delete")) {
            std->setShortcut(QKeySequence());
        }
        del->setShortcut(QKeySequence::Delete);
    }
    if (QAction* prefs = commandAction("Std_DlgPreferences")) {
        prefs->setShortcut(QKeySequence());  // Ctrl+, öffnet MyCAD_Settings
    }
    commandAction("MyCAD_Settings");

    hideChrome();
    Application::Instance->signalActivateWorkbench.connect([](const char*) { hideChromeLater(); });
    Application::Instance->signalInEdit.connect([](const ViewProviderDocumentObject& vp) {
        // Nur Skizzen schalten auf Sketch-Toolbar und Palette; Feature-Dialoge brauchen den Inspector
        static const Base::Type sketch = Base::Type::fromName("Sketcher::SketchObject");
        state.sketchMode = !sketch.isBad() && vp.getObject()->getTypeId().isDerivedFrom(sketch);
        hideChromeLater();
        QTimer::singleShot(0, layout);
    });
    Application::Instance->signalResetEdit.connect([](const ViewProviderDocumentObject&) {
        state.sketchMode = false;
        hideChromeLater();
        QTimer::singleShot(0, layout);
    });

    QMdiArea* mdi = getMainWindow()->getMdiArea();
    QObject::connect(mdi, &QMdiArea::subWindowActivated, mdi, [](QMdiSubWindow* sub) {
        // Panels nicht mitten in einem Event in eine andere Szene umziehen
        QPointer<View3DInventor> view = sub ? qobject_cast<View3DInventor*>(sub->widget()) : nullptr;
        QTimer::singleShot(0, [view] {
            if (view) {
                attach(view);
            }
        });
        hideChromeLater();
    });

    // Timeline aktuell halten
    App::GetApplication().signalNewObject.connect([](const App::DocumentObject&) { rebuildTimelineLater(); });
    App::GetApplication().signalDeletedObject.connect([](const App::DocumentObject&) { rebuildTimelineLater(); });
    App::GetApplication().signalRelabelObject.connect([](const App::DocumentObject&) { rebuildTimelineLater(); });
    App::GetApplication().signalRecomputed.connect([](const App::Document&) { rebuildTimelineLater(); });
    App::GetApplication().signalActiveDocument.connect([](const App::Document&) { rebuildTimelineLater(); });

    // Inspector ein-/ausblenden, wenn ein Werkzeug-Dialog startet oder endet
    // ponytail: Polling, weil ControlSingleton kein Signal hat; 4 Hz reicht fürs Auge
    auto poll = new QTimer(qApp);
    QObject::connect(poll, &QTimer::timeout, [] {
        static bool active = false;
        if (active != (Control().activeDialog() != nullptr)) {
            active = !active;
            layout();
        }
    });
    poll->start(250);

    // Wie in Fusion: es ist immer ein Design offen
    QTimer::singleShot(0, [] {
        if (!App::GetApplication().getActiveDocument()) {
            Application::Instance->commandManager().runCommandByName("Std_New");
        }
    });
}
