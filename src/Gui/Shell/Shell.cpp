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
#include <QActionGroup>
#include <QApplication>
#include <QDialogButtonBox>
#include <QDockWidget>
#include <QFontDatabase>
#include <QFrame>
#include <QGraphicsScene>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QPushButton>
#include <QMessageBox>
#include <QCursor>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QLineEdit>
#include <QAbstractSpinBox>
#include <QKeyEvent>
#include <QTreeWidget>
#include <QSizePolicy>
#include <QLabel>
#include <QWindow>
#include <QMenuBar>
#include <QDir>
#include <QFile>
#include <QPainter>
#include <QSvgRenderer>
#include <QPointer>
#include <QStatusBar>
#include <QRegularExpression>
#include <QScreen>
#include <QStyleHints>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <cstring>
#include <QFontMetrics>
#include <QToolTip>
#include <QVBoxLayout>

#include <functional>
#include <map>
#include <memory>
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
QToolButton#GlassButton[names="true"] { font-size: 10px; padding-top: 3px; }
#GlassContent QToolButton#GlassProminent { border: none; border-radius: 15px; background: %3; color: white; font-weight: 600; padding: 0 14px; }
#GlassContent QToolButton#GlassProminent:hover { background: %3; border: 2px solid rgba(255,255,255,0.35); }
QFrame#TimelineMarker { background: %3; border-radius: 2px; }
QToolButton#PaletteRow { border: none; border-radius: 8px; padding: 0 8px; text-align: left; background: transparent; }
QToolButton#PaletteRow:hover { background: %4; }
QToolButton#PaletteRow:checked { background: %5; }
QToolButton#WindowClose { border: none; border-radius: 10px; background: transparent; }
QToolButton#WindowClose:hover { background: #E5484D; }
QToolButton#WindowClose:pressed { background: #C93A3F; }
QLabel#WindowTitle { font-weight: 600; }
QToolButton#GlassButton[popupMode="1"] { padding-right: 10px; }
QToolButton#GlassButton::menu-button { border: none; width: 12px; }
QToolButton#GlassButton::menu-arrow { image: url(:/mycad/icons/Chevron_Down.svg); width: 9px; height: 9px; }
QToolButton#GlassButton[error="true"] { background: rgba(255,59,48,0.28); }
QFrame#GlassSeparator { background: %8; border: none; }
#GlassContent QFrame#ToolbarSeparator { background: %2; border: none; margin: 4px 4px; }
QLabel#SectionCaption { color: %2; font-size: 9px; font-weight: 600; letter-spacing: 0.6px; padding-top: 1px; }
#GlassContent, #GlassContent QWidget { background: transparent; }
#GlassContent QAbstractScrollArea { border: none; }
#GlassContent QLineEdit, #GlassContent QAbstractSpinBox, #GlassContent QComboBox {
    background: %6; border: 1px solid %7; border-radius: 7px; padding: 3px 6px; min-height: 20px;
}
#GlassContent QLineEdit:focus, #GlassContent QAbstractSpinBox:focus { border: 2px solid %3; }
#GlassContent QAbstractSpinBox::up-button, #GlassContent QAbstractSpinBox::down-button { width: 0; border: none; }
#GlassContent QComboBox::drop-down { border: none; width: 20px; }
#GlassContent QComboBox::down-arrow { image: url(:/mycad/icons/Chevron_Down.svg); width: 10px; height: 10px; }
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
Gui--NotificationLabel { background: %9; color: %1; border: 1px solid %7; border-radius: 12px; padding: 8px 10px; }
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
        QByteArray freecad;
        QByteArray ours;
        QString color;
    };
    std::vector<Override> overrides = {
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
    // Sketcher-Befehle heißen wie ihre FreeCAD-Bilder: so passen auch Menüs, Panel-Köpfe und Kontextmenüs
    for (const QString& file : QDir(QStringLiteral(":/mycad/icons")).entryList({QStringLiteral("Sketcher_*.svg")})) {
        const QByteArray name = file.chopped(4).toLatin1();
        overrides.push_back({name, name, t.text});
    }
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

/// Tooltips der Toolbar schon nach 0,3 s und direkt unter dem Knopf (Qts Standard wartet rund eine Sekunde)
class QuickTip: public QObject
{
public:
    static QuickTip* instance()
    {
        static QuickTip* tip = new QuickTip;
        return tip;
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        auto btn = qobject_cast<QToolButton*>(obj);
        if (!btn) {
            return false;
        }
        switch (event->type()) {
            case QEvent::Enter:
                target = btn;
                timer.start();
                return false;
            case QEvent::Leave:
            case QEvent::MouseButtonPress:
            case QEvent::Hide:
                timer.stop();
                QToolTip::hideText();
                return false;
            case QEvent::ToolTip:
                return true;  // langsamen Standard-Tooltip unterdrücken
            default:
                return false;
        }
    }

private:
    QuickTip()
    {
        timer.setSingleShot(true);
        timer.setInterval(300);
        QObject::connect(&timer, &QTimer::timeout, this, [this] {
            if (target && target->underMouse()) {
                QToolTip::showText(target->mapToGlobal(QPoint(target->width() / 2, target->height() + 6)),
                                   target->toolTip(), target);
            }
        });
    }
    QTimer timer;
    QPointer<QToolButton> target;
};

/// Kurzer Name für die Beschriftung unter dem Symbol ("&Extrude…" -> "Extrude"); der volle Name steht im Tooltip
QString shortName(QString text)
{
    // kürzere Namen für lange Befehle
    static const std::map<QString, QString> shorter = {
        {QStringLiteral("New Document"), QStringLiteral("New")},
        {QStringLiteral("Change Parameters"), QStringLiteral("Parameters")},
        {QStringLiteral("Section Analysis"), QStringLiteral("Section")},
        {QStringLiteral("New Component"), QStringLiteral("Component")},
    };
    text.remove(QLatin1Char('&'));
    if (auto it = shorter.find(text.trimmed()); it != shorter.end()) {
        return it->second;
    }
    // FreeCAD-Sketcher-Namen auf Fusion-Kürze bringen: "Coincident Constraint", "Text (Experimental)",
    // "Rotate / Polar Transform", "Circle From Center" …
    static const QRegularExpression noise(QStringLiteral(
        R"(\s*\(.*\)|\s+Constraint$|\s+Transform$|\s+[Ff]rom\s+.*$|^Centered\s+|^External\s+|^Toggle\s+|\s+Edge$)"));
    text.remove(noise);
    text = text.section(QStringLiteral(" / "), 0, 0).section(QLatin1Char('/'), 0, 0);
    static const std::map<QString, QString> sketch = {
        {QStringLiteral("Projection"), QStringLiteral("Project")},
        {QStringLiteral("Rectangular Array"), QStringLiteral("Pattern")},
        {QStringLiteral("Conic Curve"), QStringLiteral("Conic")},
    };
    if (auto it = sketch.find(text.trimmed()); it != sketch.end()) {
        return it->second;
    }
    text.remove(QLatin1Char('&'));
    text.remove(QStringLiteral("…"));
    text.remove(QStringLiteral("..."));
    for (const char* prefix : {"Constrain ", "Create "}) {
        if (text.startsWith(QLatin1String(prefix)) && text.size() > int(std::strlen(prefix)) + 3) {
            text.remove(0, int(std::strlen(prefix)));
        }
    }
    return text.trimmed();
}

/// Namen unter den Symbolen (Einstellung "Show tool names", MyCAD/ToolNames)
bool toolNames()
{
    return App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetBool(
        "ToolNames", false);
}

void styleToolButton(QToolButton* btn)
{
    const bool names = toolNames();
    const bool dropdown = btn->popupMode() == QToolButton::MenuButtonPopup;
    btn->setToolButtonStyle(names ? Qt::ToolButtonTextUnderIcon : Qt::ToolButtonIconOnly);
    btn->setProperty("names", names);
    if (names) {
        const int width = dropdown ? 86 : 74;
        QFont font = btn->font();
        font.setPixelSize(10);  // wie im Stylesheet für die Beschriftung
        btn->setText(QFontMetrics(font).elidedText(btn->property("label").toString(), Qt::ElideRight, width - 6));
        btn->setFixedSize(width, 56);
    }
    else {
        btn->setFixedSize(dropdown ? 44 : 34, 38);
    }
    btn->style()->unpolish(btn);
    btn->style()->polish(btn);
}

/// Knöpfe nebeneinander, bei zu wenig Breite in weiteren Reihen (jede Reihe mittig, Elemente vertikal zentriert)
class FlowLayout: public QLayout
{
public:
    explicit FlowLayout(QWidget* parent)
        : QLayout(parent)
    {}
    ~FlowLayout() override
    {
        while (QLayoutItem* item = takeAt(0)) {
            delete item;
        }
    }
    void addItem(QLayoutItem* item) override
    {
        items.append(item);
    }
    int count() const override
    {
        return int(items.size());
    }
    QLayoutItem* itemAt(int i) const override
    {
        return items.value(i);
    }
    QLayoutItem* takeAt(int i) override
    {
        return i >= 0 && i < items.size() ? items.takeAt(i) : nullptr;
    }
    Qt::Orientations expandingDirections() const override
    {
        return {};
    }
    bool hasHeightForWidth() const override
    {
        return true;
    }
    int heightForWidth(int width) const override
    {
        return arrange(QRect(0, 0, width, 0), false);
    }
    QSize sizeHint() const override  // alles in einer Reihe
    {
        int w = 0, h = 0;
        for (QLayoutItem* item : items) {
            if (!item->isEmpty()) {
                w += item->sizeHint().width() + spacing();
                h = std::max(h, item->sizeHint().height());
            }
        }
        const QMargins mg = contentsMargins();
        return {std::max(0, w - spacing()) + mg.left() + mg.right(), h + mg.top() + mg.bottom()};
    }
    QSize minimumSize() const override
    {
        QSize size;
        for (QLayoutItem* item : items) {
            size = size.expandedTo(item->minimumSize());
        }
        const QMargins mg = contentsMargins();
        return size + QSize(mg.left() + mg.right(), mg.top() + mg.bottom());
    }
    void setGeometry(const QRect& rect) override
    {
        QLayout::setGeometry(rect);
        arrange(rect, true);
    }

private:
    static bool separator(QLayoutItem* item)
    {
        return item->widget() && item->widget()->objectName() == QLatin1String("ToolbarSeparator");
    }
    int arrange(const QRect& rect, bool apply) const
    {
        const QRect area = rect.marginsRemoved(contentsMargins());
        std::vector<std::vector<QLayoutItem*>> rows(1);
        int x = 0;
        for (QLayoutItem* item : items) {
            if (item->isEmpty()) {
                continue;
            }
            const int w = item->sizeHint().width();
            if (x > 0 && x + w > area.width() && !separator(item)) {
                rows.emplace_back();
                x = 0;
            }
            rows.back().push_back(item);
            x += w + spacing();
        }
        for (auto& row : rows) {  // Trennlinie am Zeilenende fällt weg
            if (row.size() > 1 && separator(row.back())) {
                if (apply) {
                    row.back()->widget()->move(-100, -100);  // außerhalb des Panels
                }
                row.pop_back();
            }
        }
        int y = area.top();
        for (const auto& row : rows) {
            int rowWidth = -spacing(), rowHeight = 0;
            for (QLayoutItem* item : row) {
                rowWidth += item->sizeHint().width() + spacing();
                rowHeight = std::max(rowHeight, item->sizeHint().height());
            }
            if (apply) {
                int px = area.left() + std::max(0, (area.width() - rowWidth) / 2);
                for (QLayoutItem* item : row) {
                    const QSize s = item->sizeHint();
                    item->setGeometry(QRect(QPoint(px, y + (rowHeight - s.height()) / 2), s));
                    px += s.width() + spacing();
                }
            }
            y += rowHeight + 4;
        }
        return y - 4 - area.top() + contentsMargins().top() + contentsMargins().bottom();
    }
    QList<QLayoutItem*> items;
};

/// Varianten eines Knopfs: "A|B" = eigene Gruppe, Gruppenbefehle (z. B. Sketcher_CompCreateArc) bringen ihre mit
std::vector<std::pair<QString, QAction*>> variants(const QString& entry)
{
    std::vector<std::pair<QString, QAction*>> result;
    const QStringList names = entry.split(QLatin1Char('|'));
    if (names.size() > 1) {
        for (const QString& n : names) {
            if (QAction* a = commandAction(n.toLatin1().constData())) {
                result.emplace_back(n, a);
            }
        }
        return result;
    }
    const QByteArray name = entry.toLatin1();
    commandAction(name.constData());  // legt die Action an
    Command* cmd = Application::Instance->commandManager().getCommandByName(name.constData());
    if (auto group = cmd ? qobject_cast<ActionGroup*>(cmd->getAction()) : nullptr) {
        for (QAction* a : group->groupAction()->actions()) {
            if (auto owner = qobject_cast<Action*>(a->parent()); owner && !a->isSeparator()) {
                result.emplace_back(QString::fromLatin1(owner->command()->getName()), a);
            }
        }
    }
    return result;
}

/// Kapsel-Toolbar mit Befehls-Buttons in Abschnitten wie bei Fusion: "#CREATE" beginnt einen Abschnitt mit dieser
/// Überschrift (darunter), Abschnitte sind durch eine Linie getrennt; "A|B" = Knopf mit Varianten-Menü.
QWidget* toolbar(const std::vector<const char*>& commands)
{

    auto w = content();
    auto lay = new FlowLayout(w);  // bricht um, wenn das Fenster schmal ist
    lay->setContentsMargins(10, 6, 10, 6);
    lay->setSpacing(2);
    QHBoxLayout* row = nullptr;  // Knöpfe des aktuellen Abschnitts
    auto section = [&](const QString& caption) {
        if (row) {
            auto sep = new QFrame;
            sep->setObjectName(QStringLiteral("ToolbarSeparator"));
            sep->setFixedSize(9, toolNames() ? 70 : 50);  // so hoch wie ein Abschnitt samt Überschrift
            lay->addWidget(sep);
        }
        auto group = new QWidget;
        auto column = new QVBoxLayout(group);
        column->setContentsMargins(0, 0, 0, 0);
        column->setSpacing(0);
        row = new QHBoxLayout;
        row->setSpacing(2);
        column->addLayout(row);
        if (!caption.isEmpty()) {
            auto label = new QLabel(caption);
            label->setObjectName(QStringLiteral("SectionCaption"));
            label->setAlignment(Qt::AlignCenter);
            column->addWidget(label);
        }
        lay->addWidget(group);
    };
    for (const char* name : commands) {
        if (*name == '#') {
            section(QString::fromLatin1(name + 1));
            continue;
        }
        if (!*name) {
            continue;
        }
        if (!row) {
            section(QString());
        }
        const auto choices = variants(QString::fromLatin1(name));
        QAction* action = choices.empty() ? commandAction(name) : choices.front().second;
        if (!action) {
            continue;
        }
        auto btn = new QToolButton;
        if (!choices.empty()) {
            // Knopf führt die zuletzt gewählte Variante aus, der Pfeil zeigt alle (wie Fusions Dropdowns)
            auto current = std::make_shared<QPointer<QAction>>(action);
            auto pick = [btn, current](const QString& n, QAction* a) {
                *current = a;
                btn->setIcon(commandIcon(n, a->icon()));
                btn->setToolTip(a->toolTip().isEmpty() ? a->text() : a->toolTip());
                btn->setProperty("label", shortName(a->text()));
                if (btn->property("names").toBool()) {
                    styleToolButton(btn);
                }
            };
            auto menu = new QMenu;  // ohne Eltern: sonst bettet Qt das Menü in die 3D-Szene ein
            QObject::connect(btn, &QObject::destroyed, menu, &QObject::deleteLater);
            for (const auto& [n, a] : choices) {
                QObject::connect(menu->addAction(commandIcon(n, a->icon()), a->text()), &QAction::triggered, a,
                                 [pick, n, a] {
                                     pick(n, a);
                                     QTimer::singleShot(0, a, &QAction::trigger);
                                 });
            }
            btn->setObjectName(QStringLiteral("GlassButton"));
            btn->setProperty("command", QString::fromLatin1(name));
            btn->setMenu(menu);
            btn->setPopupMode(QToolButton::MenuButtonPopup);
            btn->setIconSize(QSize(22, 22));
            pick(choices.front().first, action);
            styleToolButton(btn);
            btn->installEventFilter(QuickTip::instance());
            btn->setEnabled(action->isEnabled());
            QObject::connect(btn, &QToolButton::clicked, action, [current] {
                if (*current) {
                    QTimer::singleShot(0, current->data(), &QAction::trigger);
                }
            });
            QObject::connect(action, &QAction::changed, btn, [btn, action] {
                btn->setEnabled(action->isEnabled());
            });
            row->addWidget(btn);
            continue;
        }
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
            row->addWidget(btn);
            continue;
        }
        btn->setIcon(commandIcon(QString::fromLatin1(name), action->icon()));
        btn->setIconSize(QSize(22, 22));
        btn->setToolTip(action->toolTip().isEmpty() ? action->text() : action->toolTip());
        btn->setProperty("label", shortName(action->text()));
        styleToolButton(btn);
        btn->installEventFilter(QuickTip::instance());
        btn->setEnabled(action->isEnabled());
        // Erst nach dem Mausklick auslösen: Befehle bauen die Oberfläche um (neue Ansicht, Dialog, Edit-Modus),
        // während Qt den Klick noch an das Proxy-Widget weiterreicht. Synchron führte das zum Absturz.
        QObject::connect(btn, &QToolButton::clicked, action, [action] {
            QTimer::singleShot(0, action, &QAction::trigger);
        });
        QObject::connect(action, &QAction::changed, btn, [btn, action] {
            btn->setEnabled(action->isEnabled());
        });
        row->addWidget(btn);
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

void toggleMaximized()
{
    MainWindow* mw = getMainWindow();
    if (!mw->isMaximized()) {
        mw->showMaximized();
        return;
    }
    // Wurde MyCAD immer maximiert gestartet, ist die "normale" Größe der ganze Bildschirm: Wiederherstellen sähe
    // dann aus, als passiere nichts. Stattdessen ein Fenster mit 75 % der Fläche, mittig.
    const QRect screen = mw->screen() ? mw->screen()->availableGeometry() : QRect();
    const QRect normal = mw->normalGeometry();
    mw->showNormal();
    if (screen.isValid() && normal.width() >= screen.width() * 0.9 && normal.height() >= screen.height() * 0.9) {
        // erst nach dem Zustandswechsel setzen: unter Wayland schickt der Compositor danach noch die alte Größe
        const QRect target(screen.center() - QPoint(screen.width() * 3 / 8, screen.height() * 3 / 8),
                           QSize(screen.width() * 3 / 4, screen.height() * 3 / 4));
        for (int delay : {50, 250}) {
            QTimer::singleShot(delay, mw, [mw, target] {
                if (!mw->isMaximized() && !mw->isMinimized()) {
                    mw->setGeometry(target);
                }
            });
        }
    }
}

/// Rahmenloses Fenster: freie Flächen von Toolbar und Fensterknöpfen dienen als Griff
/// (Ziehen verschiebt, Doppelklick maximiert). Klicks auf Knöpfe kommen hier nicht an.
class WindowGrip: public QObject
{
protected:
    bool eventFilter(QObject*, QEvent* event) override
    {
        if (event->type() == QEvent::MouseButtonPress && static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton
            && getMainWindow()->windowHandle()) {
            getMainWindow()->windowHandle()->startSystemMove();
            return true;
        }
        if (event->type() == QEvent::MouseButtonDblClick) {
            QTimer::singleShot(0, toggleMaximized);
            return true;
        }
        return false;
    }
};

/// Fensterknöpfe rechts oben wie unter KDE: minimieren, maximieren/wiederherstellen, schließen
class WindowControls: public QWidget
{
public:
    WindowControls()
    {
        setObjectName(QStringLiteral("GlassContent"));
        auto lay = new QHBoxLayout(this);
        lay->setContentsMargins(8, 6, 8, 6);
        lay->setSpacing(2);
        auto button = [&](const char* icon, const char* name, const QString& tip, std::function<void()> action) {
            auto btn = new QToolButton;
            btn->setObjectName(QString::fromLatin1(name));
            btn->setIcon(designIcon(QString::fromLatin1(icon)));
            btn->setIconSize(QSize(18, 18));
            btn->setFixedSize(38, 38);
            btn->setToolTip(tip);
            btn->setCursor(Qt::ArrowCursor);
            QObject::connect(btn, &QToolButton::clicked, btn, [action] { QTimer::singleShot(0, action); });
            lay->addWidget(btn);
            return btn;
        };
        // deutlicher Griff zum Verschieben (die Fläche um die Knöpfe allein ist zu schmal zum Treffen)
        auto handle = new QLabel;
        handle->setPixmap(designIcon(QStringLiteral("Window_Grip")).pixmap(18, 18));
        handle->setFixedSize(26, 38);
        handle->setAlignment(Qt::AlignCenter);
        handle->setCursor(Qt::OpenHandCursor);
        handle->setToolTip(QStringLiteral("Drag to move the window, double-click to maximize"));
        lay->addWidget(handle);
        button("MyCAD_Settings", "GlassButton", QStringLiteral("Settings (Ctrl+,)"), [] {
            Application::Instance->commandManager().runCommandByName("MyCAD_Settings");
        });
        button("Window_Minimize", "GlassButton", QStringLiteral("Minimize"), [] { getMainWindow()->showMinimized(); });
        maximize = button("Window_Maximize", "GlassButton", QStringLiteral("Maximize"), toggleMaximized);
        button("Window_Close", "WindowClose", QStringLiteral("Close"), [] { getMainWindow()->close(); });
        getMainWindow()->installEventFilter(this);
        update();
    }

protected:
    bool eventFilter(QObject*, QEvent* event) override
    {
        if (event->type() == QEvent::WindowStateChange) {
            update();
        }
        return false;
    }

private:
    void update()  // maximiert: "Wiederherstellen"-Symbol
    {
        const bool max = getMainWindow()->isMaximized();
        maximize->setIcon(designIcon(max ? QStringLiteral("Window_Restore") : QStringLiteral("Window_Maximize")));
        maximize->setToolTip(max ? QStringLiteral("Restore") : QStringLiteral("Maximize"));
    }
    QToolButton* maximize;
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
            else if (obj->inherits("Gui::NotificationLabel")) {  // Fehlermeldungen: runde Ecken statt gelbem Tooltip
                static_cast<QWidget*>(obj)->setAttribute(Qt::WA_TranslucentBackground);
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
            // Dokument-Eintrag: speichern, umbenennen, schließen (ein Dokument wird geschlossen, nicht gelöscht)
            QTreeWidgetItem* item = tree->itemAt(static_cast<QContextMenuEvent*>(event)->pos());
            if (item && item->type() == TreeWidget::DocumentType) {
                const std::string name = static_cast<DocumentItem*>(item)->document()->getDocument()->getName();
                auto guiDoc = [name]() -> Gui::Document* {  // Dokument kann inzwischen geschlossen sein
                    App::Document* doc = App::GetApplication().getDocument(name.c_str());
                    return doc ? Application::Instance->getDocument(doc) : nullptr;
                };
                QTimer::singleShot(0, [tree, item, guiDoc] {
                    if (!guiDoc()) {
                        return;
                    }
                    QMenu menu;
                    auto run = [guiDoc](const char* command) {
                        if (Gui::Document* gdoc = guiDoc()) {
                            Application::Instance->setActiveDocument(gdoc);
                            Application::Instance->commandManager().runCommandByName(command);
                        }
                    };
                    QObject::connect(menu.addAction(QStringLiteral("Save")), &QAction::triggered, [run] { run("Std_Save"); });
                    QObject::connect(menu.addAction(QStringLiteral("Save As…")), &QAction::triggered, [run] { run("Std_SaveAs"); });
                    QObject::connect(menu.addAction(QStringLiteral("Export…")), &QAction::triggered, [run] { run("Design_Export"); });
                    menu.addSeparator();
                    QObject::connect(menu.addAction(QStringLiteral("Rename")), &QAction::triggered, [tree, item] { tree->editItem(item); });
                    menu.addSeparator();
                    QObject::connect(menu.addAction(QStringLiteral("Close")), &QAction::triggered, [guiDoc] {
                        QTimer::singleShot(0, [guiDoc] {
                            Gui::Document* gdoc = guiDoc();
                            if (gdoc && gdoc->canClose(true, true)) {  // fragt bei Änderungen nach dem Speichern
                                App::GetApplication().closeDocument(gdoc->getDocument()->getName());
                            }
                        });
                    });
                    // Löschen: ohne Speichern schließen; eine gespeicherte Datei kommt in den Papierkorb (nicht endgültig weg)
                    QObject::connect(menu.addAction(QStringLiteral("Delete…")), &QAction::triggered, [guiDoc] {
                        QTimer::singleShot(0, [guiDoc] {
                            Gui::Document* gdoc = guiDoc();
                            if (!gdoc) {
                                return;
                            }
                            App::Document* doc = gdoc->getDocument();
                            const QString file = QString::fromUtf8(doc->FileName.getValue());
                            const QString label = QString::fromUtf8(doc->Label.getValue());
                            QMessageBox box(QMessageBox::Warning, QStringLiteral("Delete Design"),
                                            file.isEmpty() ? QStringLiteral("Delete “%1”? It has never been saved, "
                                                                            "so its contents will be gone.")
                                                                 .arg(label)
                                                           : QStringLiteral("Delete “%1”? The file is moved to the "
                                                                            "trash:\n%2")
                                                                 .arg(label, file),
                                            QMessageBox::Cancel, getMainWindow());
                            QPushButton* remove = box.addButton(QStringLiteral("Delete"), QMessageBox::DestructiveRole);
                            box.setDefaultButton(QMessageBox::Cancel);
                            box.exec();
                            if (box.clickedButton() != remove) {
                                return;
                            }
                            App::GetApplication().closeDocument(doc->getName());
                            if (!file.isEmpty()) {
                                QFile::moveToTrash(file);
                            }
                        });
                    });
                    menu.exec(QCursor::pos());
                });
                return true;
            }
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
    GlassPanel* windowControls = nullptr;
    GlassPanel* palette = nullptr;
    ViewCube* viewCube = nullptr;
    bool sketchMode = false;
    QGraphicsScene* scene = nullptr;
} state;

std::vector<GlassPanel*> panels()
{
    std::vector<GlassPanel*> all;
    for (auto p : {state.modelBar, state.sketchBar, state.browser, state.inspector, state.timeline,
                   state.windowControls, state.palette}) {
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
    const QSizeF bs = bar->content()->sizeHint();  // eine Reihe
    // Toolbar mittig zwischen Browser und Fensterknöpfen; reicht die Breite nicht, bricht sie in weitere Reihen um
    const qreal browserWidth = 290;
    const qreal left = state.browser ? m + browserWidth + m : m;
    const qreal right = r.width() - m
        - (state.windowControls ? state.windowControls->content()->sizeHint().width() + m : 0);
    const qreal barW = std::max<qreal>(100, std::min(bs.width(), right - left));
    const qreal barH = barW < bs.width() ? bar->content()->heightForWidth(int(barW)) : bs.height();
    bar->setGeometry(QRectF(left + (right - left - barW) / 2, m, barW, barH));

    qreal bottom = r.height() - m;
    if (state.timeline) {
        const QSizeF ts = state.timeline->content()->sizeHint();
        const bool show = state.timeline->content()->property("count").toInt() > 0;
        state.timeline->setVisible(show);
        state.timeline->setGeometry(
            QRectF(r.center().x() - ts.width() / 2, r.height() - m - ts.height(), ts.width(), ts.height())
        );
    }

    const qreal top = m;
    if (state.browser) {
        state.browser->setGeometry(QRectF(m, top, browserWidth, bottom - top));
    }
    qreal cubeTop = m;
    if (state.windowControls) {
        const QSizeF cs = state.windowControls->content()->sizeHint();
        state.windowControls->setGeometry(QRectF(r.width() - cs.width() - m, m, cs.width(), bs.height()));
        cubeTop = m + bs.height() + m;
    }
    qreal belowCube = 170;
    if (state.viewCube) {
        state.viewCube->setPos(r.width() - state.viewCube->boundingRect().width() - m, cubeTop);
        belowCube = cubeTop + state.viewCube->boundingRect().height() + m;
    }
    if (state.palette) {
        QSizeF ps = state.palette->content()->sizeHint();
        ps.setWidth(std::max<qreal>(ps.width(), state.palette->content()->minimumWidth()));
        state.palette->setVisible(state.sketchMode);
        state.palette->setGeometry(QRectF(r.width() - ps.width() - m, belowCube, ps.width(), ps.height()));
    }
    if (state.inspector) {
        const qreal itop = belowCube;  // unter dem ViewCube
        QWidget* inspector = state.inspector->content();
        for (auto box : inspector->findChildren<QDialogButtonBox*>()) {
            box->setVisible(!state.sketchMode);
        }
        if (!state.sketchMode) {
            state.inspector->setVisible(Control().activeDialog() != nullptr);
            state.inspector->setGeometry(QRectF(r.width() - 340 - m, itop, 340, bottom - itop));
        }
        else {
            // Im Skizzenmodus übernimmt die Sketch Palette; nur Werkzeug-Optionen (Kopien, Ecken, Abstand …)
            // erscheinen darunter, solange das Werkzeug welche hat (wie Fusions kleine Werkzeug-Dialoge)
            QWidget* tool = nullptr;
            for (auto w : inspector->findChildren<QWidget*>()) {
                if (w->inherits("SketcherGui::TaskSketcherTool") && !w->isHidden()) {
                    tool = w;
                }
            }
            state.inspector->setVisible(tool != nullptr);
            if (tool) {
                const qreal top = state.palette ? state.palette->sceneBoundingRect().bottom() + m : itop;
                const qreal h = std::min<qreal>(tool->sizeHint().height() + 40, bottom - top);
                state.inspector->setGeometry(QRectF(r.width() - 340 - m, top, 340, h));
            }
        }
    }
}

/// Sketcher-Panel: im Skizzenmodus nur "Tool Parameters" zeigen, bei jedem Werkzeugwechsel neu anordnen
class SketchTaskFilter: public QObject
{
protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        const auto type = event->type();
        // Esc beendet wie in Fusion das Skizzen-Werkzeug, auch wenn ein Maßfeld den Fokus hat (FreeCAD bricht dort
        // nur die Eingabe ab, und das nächste Feld holt sich den Fokus zurück)
        if (type == QEvent::KeyPress && state.sketchMode && static_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape
            && obj == QApplication::focusWidget() && (qobject_cast<QAbstractSpinBox*>(obj) || qobject_cast<QLineEdit*>(obj))) {
            auto gdoc = Application::Instance->activeDocument();
            auto view = gdoc ? dynamic_cast<View3DInventor*>(gdoc->getActiveView()) : nullptr;
            if (view) {
                QWidget* viewport = view->getViewer()->viewport();
                viewport->setFocus();
                QKeyEvent press(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
                QKeyEvent release(QEvent::KeyRelease, Qt::Key_Escape, Qt::NoModifier);
                QApplication::sendEvent(viewport, &press);
                QApplication::sendEvent(viewport, &release);
                return true;
            }
        }
        if (obj->inherits("SketcherGui::TaskSketcherTool")) {
            // *ToParent: kommt auch, solange das Panel noch verborgen ist (Show käme erst danach)
            if (type == QEvent::ShowToParent || type == QEvent::HideToParent) {
                QTimer::singleShot(0, layout);
            }
            return false;
        }
        if (type == QEvent::Show && state.sketchMode && obj->inherits("Gui::TaskView::TaskBox")
            && QByteArray(obj->metaObject()->className()).startsWith("SketcherGui::")) {
            QTimer::singleShot(0, static_cast<QWidget*>(obj), &QWidget::hide);
        }
        return false;
    }
};

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
    // Knöpfe eines verborgenen Panels gelten sonst als versteckt und zählen nicht zur Größe (Timeline war zu flach)
    for (int i = 0; i < lay->count(); ++i) {
        if (QWidget* w = lay->itemAt(i)->widget()) {
            w->show();
        }
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

/// Panels aus der Szene nehmen, bevor ihr 3D-Fenster verschwindet: die Szene löscht sonst alle Elemente mit,
/// samt eingebettetem Browser (Absturz beim Schließen eines Dokuments)
void detach()
{
    if (!state.scene) {
        return;
    }
    for (auto p : panels()) {
        state.scene->removeItem(p);
    }
    if (state.viewCube) {
        state.scene->removeItem(state.viewCube);
    }
    state.scene = nullptr;
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
        toolbar({"#FILE", "Std_New", "Std_Open", "Std_Save", "Design_Import", "Design_Export",
                 "Std_Undo", "Std_Redo",
                 "#CREATE", "Design_CreateSketch", "Design_Extrude", "Design_Revolve",
                 "Design_Sweep|Design_Loft|Design_Rib|Design_Web|Design_Emboss",
                 "Design_Box|Design_Cylinder|Design_Sphere|Design_Torus|Design_Coil", "Design_Hole|Design_Thread",
                 "Design_Pattern", "Design_Mirror",
                 "#MODIFY", "Design_PressPull|Design_ReplaceFace|Design_SplitFace", "Design_Fillet", "Design_Chamfer",
                 "Design_Shell", "Design_Draft", "Design_Combine|Design_SplitBody", "Design_Move|Design_Align|Design_Scale",
                 "#CONSTRUCT", "Design_OffsetPlane|Design_AnglePlane|Design_Midplane|Design_Plane|Design_Axis|Design_Point",
                 "#ASSEMBLE", "Design_NewComponent", "Design_Joint",
                 "#INSPECT", "Design_Measure", "Design_Section", "Std_ViewFitAll",
                 "#UTILITIES", "Design_Parameters", "Design_Appearance"}),
        24);
    state.sketchBar = new GlassPanel(
        toolbar({"#CREATE", "Sketcher_CreateLine", "Sketcher_CreatePolyline", "Sketcher_CompCreateRectangles",
                 "Sketcher_CompCreateConic", "Sketcher_CompCreateArc", "Sketcher_CompSlot",
                 "Sketcher_CompCreateRegularPolygon", "Sketcher_CompCreateBSpline", "Sketcher_CreateConic",
                 "Sketcher_CreatePoint", "Sketcher_CreateText", "Sketcher_CompExternal",
                 "#MODIFY", "Sketcher_CompCreateFillets", "Sketcher_Trimming|Sketcher_Extend|Sketcher_Split",
                 "Sketcher_Offset", "Sketcher_Symmetry", "Sketcher_RectangularArray|Sketcher_Rotate",
                 "Sketcher_Translate|Sketcher_Scale", "Sketcher_ToggleConstruction",
                 "#CONSTRAINTS", "Sketcher_Dimension", "Sketcher_ConstrainCoincidentUnified",
                 "Sketcher_ConstrainHorizontal|Sketcher_ConstrainVertical",
                 "Sketcher_ConstrainParallel|Sketcher_ConstrainPerpendicular", "Sketcher_ConstrainTangent",
                 "Sketcher_ConstrainEqual", "Sketcher_ConstrainSymmetric", "Sketcher_ConstrainBlock",
                 "#", "Sketcher_LeaveSketch"}),
        24);
    state.viewCube = new ViewCube;
    state.palette = new GlassPanel(sketchPalette(), 20);
    qApp->installEventFilter(new MenuPolisher);
    qApp->installEventFilter(new SketchTaskFilter);
    // Rahmenloses Fenster wie eine macOS-App (abschaltbar: MainWindow/MyCADFrameless = false)
    auto mainGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MainWindow");
    if (mainGrp->GetBool("MyCADFrameless", true)) {
        MainWindow* mw = getMainWindow();
        const bool wasVisible = mw->isVisible();
        mw->setWindowFlag(Qt::FramelessWindowHint, true);
        if (wasVisible) {
            mw->show();
        }
        state.windowControls = new GlassPanel(new WindowControls, 24);
        static WindowGrip* grip = new WindowGrip;
        for (GlassPanel* p : {state.modelBar, state.sketchBar, state.windowControls}) {
            p->content()->installEventFilter(grip);
        }
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

    // Fenster wird geschlossen (nach "Speichern?"-Abfrage, vor dem Abbau): Panels vorher herausnehmen
    Application::Instance->signalCloseView.connect([](const Gui::MDIView* view) {
        auto v3d = dynamic_cast<const View3DInventor*>(view);
        if (v3d && v3d->getViewer()->scene() == state.scene) {
            detach();
        }
    });
    Application::Instance->signalDeleteDocument.connect([](const Gui::Document& gdoc) {
        for (auto view : const_cast<Gui::Document&>(gdoc).getMDIViews()) {
            auto v3d = dynamic_cast<View3DInventor*>(view);
            if (v3d && v3d->getViewer()->scene() == state.scene) {
                detach();
            }
        }
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

void Gui::Shell::setToolNames(bool on)
{
    App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->SetBool("ToolNames", on);
    for (GlassPanel* bar : {state.modelBar, state.sketchBar}) {
        if (!bar) {
            continue;
        }
        for (auto btn : bar->content()->findChildren<QToolButton*>(QStringLiteral("GlassButton"))) {
            styleToolButton(btn);
        }
        for (auto sep : bar->content()->findChildren<QFrame*>(QStringLiteral("ToolbarSeparator"))) {
            sep->setFixedSize(9, on ? 70 : 50);
        }
        // Abschnitte zuerst neu rechnen, sonst misst die Toolbar mit den alten Knopfgrößen (zweite Reihe abgeschnitten)
        for (auto group : bar->content()->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
            if (group->layout()) {
                group->layout()->activate();
            }
        }
        bar->content()->layout()->invalidate();
    }
    layout();
}
