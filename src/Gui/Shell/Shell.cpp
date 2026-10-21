// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Shell.h"
#include "GlassPanel.h"
#include "ViewCube.h"
#include "Settings.h"
#include "Theme.h"

#include <App/Application.h>
#include <Gui/Action.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/Selection/Selection.h>
#include <Gui/ViewProviderDocumentObject.h>
#include <Gui/ViewProviderGeometryObject.h>
#include <App/Document.h>
#include <App/PropertyStandard.h>
#include <Gui/DockWindowManager.h>
#include <Gui/MainWindow.h>
#include <Gui/Tree.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <Gui/Inventor/SoFCBoundingBox.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDepthBuffer.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoFragmentShader.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoPolygonOffset.h>
#include <Inventor/nodes/SoShaderParameter.h>
#include <Inventor/nodes/SoShaderProgram.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTransparencyType.h>
#include <Inventor/nodes/SoVertexShader.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include <QAbstractScrollArea>
#include <QActionGroup>
#include <QApplication>
#include <QDialogButtonBox>
#include <QDockWidget>
#include <QFontDatabase>
#include <QFrame>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QGuiApplication>
#include <QGridLayout>
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
#include <QSurfaceFormat>
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
#include <algorithm>
#include <array>
#include <cstring>
#include <set>
#include <QFontMetrics>
#include <QDateTime>
#include <QLocale>
#include <QScrollArea>
#include <QSet>
#include <QTextBrowser>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QButtonGroup>
#include <QStandardPaths>
#include <zipios++/zipfile.h>
#include <iterator>
#include <memory>
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

/// Breite von Browser und Seitenleisten. MyStyle-Abweichung von size.sidebarWidth (232): der Modellbaum braucht wie
/// Fusions Browser Platz für Namen, Sichtbarkeits-Auge und Status-Symbole
constexpr qreal BrowserWidth = 290;

void overrideFreeCadIcons();

/// Das Stylesheet der ganzen App; "@token" steht für die Farbe aus dem aktuellen Theme (MyStyle § 9).
/// Schriftgrößen setzt setTextStyle(), nicht das Stylesheet (Qt-Stylesheets kennen keine Laufweite).
QString styleSheet()
{
    const QString s = QStringLiteral(R"(
* { color: @labelPrimary; }
#GlassContent, #GlassContent QWidget { background: transparent; }
QToolTip { background: @glassOpaqueTop; color: @labelPrimary; border: 1px solid @glassPopupBorder; border-radius: 8px; padding: 4px 8px; }

/* Icon-Buttons in Glas-Bars: rund, Hover fill.tertiary, gedrückt fill.secondary, Tastaturfokus 2-px-Ring */
QToolButton#GlassButton, QToolButton#WindowClose { border: 2px solid transparent; border-radius: 18px; background: transparent; }
QToolButton#GlassButton:hover { background: @fillTertiary; }
QToolButton#GlassButton:pressed, QToolButton#GlassButton:checked { background: @fillSecondary; }
QToolButton#GlassButton:focus, QToolButton#WindowClose:focus, QToolButton#PaletteRow:focus { border-color: @focusRing; }
QToolButton#GlassButton:disabled { background: transparent; }
QToolButton#GlassButton[names="true"] { border-radius: 12px; padding-top: 2px; }
QToolButton#GlassButton[names="true"]::menu-arrow { subcontrol-position: bottom center; bottom: 9px; }
QToolButton#GlassButton[popupMode="1"] { padding-right: 10px; }
QToolButton#GlassButton::menu-button { border: none; width: 12px; }
QToolButton#GlassButton::menu-arrow { image: url(:/mycad/icons/Chevron_Down.svg); width: 9px; height: 9px; }
QToolButton#GlassButton[error="true"] { background: @errorFill; }
QToolButton#WindowClose:hover { background: @red; }
QToolButton#WindowClose:pressed { background: @redPressed; }

/* Prominent-Button (Akzentfläche): Kapsel 30 hoch, 16 seitlich, Callout SemiBold, Hover 1 px Weiß 35 %, gedrückt 15 % dunkler */
QToolButton#GlassProminent, QPushButton#Prominent { border: 1px solid transparent; border-radius: 15px; background: @accent; color: @labelOnAccent;
    font-weight: 600; padding: 0 15px; min-height: 28px; }
QToolButton#GlassProminent:hover, QPushButton#Prominent:hover { border-color: @hoverRim; }
QToolButton#GlassProminent:pressed, QPushButton#Prominent:pressed { background: @accentPressed; }
QToolButton#GlassProminent:focus, QPushButton#Prominent:focus { border: 2px solid @focusRing; padding: 0 14px; }

QFrame#TimelineMarker { background: @accent; border-radius: 2px; }
/* Seitenleisten-Zeilen: r 12, Hover fill.tertiary, aktiv fill.secondary + SemiBold */
QToolButton#PaletteRow { border: 2px solid transparent; border-radius: 12px; padding: 0 8px; text-align: left; background: transparent; }
QToolButton#PaletteRow:hover { background: @fillTertiary; }
QToolButton#PaletteRow:checked { background: @fillSecondary; font-weight: 600; }
QFrame#GlassSeparator, QFrame#ToolbarSeparator { background: @separator; border: none; }
QFrame#ToolbarSeparator { margin: 4px; }
QLabel#Section, QLabel#Secondary, QLabel#StartDate, QLabel#StartCaption, QLabel#Hint { color: @labelSecondary; }

#GlassContent QAbstractScrollArea { border: none; }
/* Textfelder: 30 hoch, r 8, fill.tertiary, 10 seitlich, Fokus 2-px-Ring */
#GlassContent QLineEdit, #GlassContent QAbstractSpinBox, #GlassContent QComboBox {
    background: @fillTertiary; border: 2px solid transparent; border-radius: 8px; padding: 2px 8px; min-height: 22px;
}
/* MyStyle-Abweichung: Auswahlfelder in FreeCADs Werkzeug-Formularen als Feld (fill.tertiary) statt randlos,
   weil dort kein Zeilenlabel links steht, an dem man den Pop-up-Button erkennt */
#GlassContent QComboBox:hover { background: @fillSecondary; }
#GlassContent QLineEdit:focus, #GlassContent QAbstractSpinBox:focus, #GlassContent QComboBox:focus { border-color: @focusRing; }
#GlassContent QAbstractSpinBox::up-button, #GlassContent QAbstractSpinBox::down-button { width: 0; border: none; }
QComboBox::drop-down { border: none; width: 20px; }
QComboBox::down-arrow { image: url(:/mycad/icons/Chevron_Down.svg); width: 10px; height: 10px; }
QLineEdit { selection-background-color: @accent; selection-color: @labelOnAccent; }

/* Standard-Buttons: Kapsel, fill.tertiary, gedrückt fill.secondary, Hover 1 px Weiß 35 %; Standard-Aktion = Akzent */
#GlassContent QPushButton, QDialog QPushButton, QMessageBox QPushButton {
    background: @fillTertiary; border: 1px solid transparent; border-radius: 15px; min-height: 28px; padding: 0 15px; font-weight: 600;
}
#GlassContent QPushButton:hover, QDialog QPushButton:hover, QMessageBox QPushButton:hover { border-color: @hoverRim; }
#GlassContent QPushButton:pressed, QDialog QPushButton:pressed, QMessageBox QPushButton:pressed { background: @fillSecondary; }
#GlassContent QPushButton:focus, QDialog QPushButton:focus, QMessageBox QPushButton:focus { border: 2px solid @focusRing; padding: 0 14px; }
#GlassContent QPushButton:default, QDialog QPushButton:default, QMessageBox QPushButton:default { background: @accent; color: @labelOnAccent; }
#GlassContent QPushButton:default:pressed, QDialog QPushButton:default:pressed, QMessageBox QPushButton:default:pressed { background: @accentPressed; }
#GlassContent QPushButton:disabled, QDialog QPushButton:disabled { color: @labelTertiary; }

#GlassContent QTreeView::item { min-height: 28px; border-radius: 8px; }
#GlassContent QTreeView::item:hover { background: @fillTertiary; }
#GlassContent QTreeView::item:selected { background: @accent; color: @labelOnAccent; }
#GlassContent QTreeView::branch:selected, #GlassContent QTreeView::branch:hover { background: transparent; }
#GlassContent QHeaderView::section { background: transparent; border: none; color: @labelSecondary; font-weight: 600; padding: 4px 8px; }
#GlassContent QTabWidget::pane { border: none; }
#GlassContent QTabBar::tab { background: transparent; border: none; border-radius: 8px; padding: 4px 12px; margin: 2px; color: @labelSecondary; }
#GlassContent QTabBar::tab:selected { background: @fillSecondary; color: @labelPrimary; }
#GlassContent QSplitter::handle { background: @separator; height: 1px; }

/* Scrollbar: Overlay-Kapsel ohne Spur, 6 breit, beim Überfahren 9 */
QScrollBar:vertical { background: transparent; width: 9px; margin: 2px 0; }
QScrollBar:horizontal { background: transparent; height: 9px; margin: 0 2px; }
QScrollBar::handle { background: @scrollbar; border-radius: 3px; min-height: 24px; min-width: 24px; }
QScrollBar::handle:vertical { margin: 0 1px 0 2px; }
QScrollBar::handle:horizontal { margin: 2px 0 1px 0; }
QScrollBar::handle:hover { margin: 0; border-radius: 4px; }
QScrollBar::add-line, QScrollBar::sub-line { width: 0; height: 0; }
QScrollBar::add-page, QScrollBar::sub-page { background: transparent; }
QDialogButtonBox { dialogbuttonbox-buttons-have-icons: 0; }

/* Menüs: Text-Glas als Frost (eigenes Fenster ohne Blur), r 12, Innenabstand 4, Einträge 30 hoch r 8 */
QMenu { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 @glassOpaqueTop, stop:1 @glassOpaqueBottom);
    border: 1px solid @glassPopupBorder; border-radius: 12px; padding: 4px; }
QMenu::item { padding: 6px 24px 6px 12px; border-radius: 8px; }
QMenu::item:selected { background: @accent; color: @labelOnAccent; }
QMenu::item:disabled { color: @labelTertiary; }
QMenu::separator { height: 1px; background: @separator; margin: 4px 8px; }
QMenu::icon { padding-left: 8px; }
QMessageBox, QDialog { background: @glassOpaqueTop; }
QMessageBox[glass="true"] { background: transparent; }
QMessageBox[glass="true"] QLabel#qt_msgbox_informativelabel { color: @labelSecondary; }
/* Checkbox: 16, r 5, aus fill.secondary, an Akzent mit weißem Häkchen */
QCheckBox::indicator { width: 16px; height: 16px; border-radius: 5px; border: none; background: @fillSecondary; }
QCheckBox::indicator:checked { background: @accent; image: url(:/mycad/icons/Check.svg); }
QCheckBox:focus { color: @accentText; }
Gui--NotificationLabel { background: @glassOpaqueTop; color: @labelPrimary; border: 1px solid @glassPopupBorder; border-radius: 12px; padding: 8px 12px; }

/* Startseite und Hilfe */
QScrollArea#StartScroll, #StartContent, QTextBrowser#HelpArticle { background: transparent; border: none; }
QLineEdit#StartSearch { background: transparent; border: none; padding: 4px 2px; }
)");
    return themed(s);
}

/// Palette für alles, was das Stylesheet nicht erfasst (FreeCAD-Dialoge, Listen, Tabellen, Aufgaben-Köpfe)
QPalette palette()
{
    const Theme& t = theme();
    QPalette p = QApplication::style()->standardPalette();
    const QColor base = t.glassOpaqueTop.rgb(), alternate = t.glassOpaqueBottom.rgb();  // deckend
    const std::pair<QPalette::ColorRole, QColor> roles[] = {
        {QPalette::Window, alternate}, {QPalette::Base, base}, {QPalette::AlternateBase, alternate},
        {QPalette::Button, base}, {QPalette::Light, base}, {QPalette::Midlight, alternate},
        {QPalette::ToolTipBase, base}, {QPalette::WindowText, t.labelPrimary}, {QPalette::Text, t.labelPrimary},
        {QPalette::ButtonText, t.labelPrimary}, {QPalette::ToolTipText, t.labelPrimary},
        {QPalette::BrightText, t.labelOnAccent}, {QPalette::PlaceholderText, t.labelTertiary},
        {QPalette::Highlight, t.accent}, {QPalette::HighlightedText, t.labelOnAccent}, {QPalette::Link, t.accentText},
        {QPalette::LinkVisited, t.accentText}, {QPalette::Mid, t.separatorOpaque}, {QPalette::Dark, t.gray},
        {QPalette::Shadow, t.shadow}};
    for (const auto& [role, color] : roles) {
        p.setColor(role, color);
    }
    for (auto role : {QPalette::WindowText, QPalette::Text, QPalette::ButtonText}) {
        p.setColor(QPalette::Disabled, role, t.labelTertiary);
    }
    return p;
}

/// Farbe als 0xRRGGBBAA für FreeCADs Parameter
unsigned long packed(const QColor& c)
{
    return (unsigned long)(c.red()) << 24 | c.green() << 16 | c.blue() << 8 | 0xFF;
}

QColor mix(const QColor& a, const QColor& b, double f)
{
    return QColor::fromRgbF(a.redF() + (b.redF() - a.redF()) * f, a.greenF() + (b.greenF() - a.greenF()) * f,
                            a.blueF() + (b.blueF() - a.blueF()) * f);
}

/// Aussehen der Körper (Einstellung "Body material"), Farben als 0xRRGGBBAA
struct BodyMaterial
{
    const char* name;
    uint32_t diffuse, specular, emissive, line;
    int shininess;
};
constexpr BodyMaterial bodyMaterials[] = {
    {"Space Gray", 0x5C6169FF, 0x737373FF, 0x0A0A0BFF, 0x1F1F24FF, 55},
    {"Clay", 0xE8DED1FF, 0x1A1A1AFF, 0x1A1714FF, 0x73665CFF, 10},
    {"Sierra Blue", 0x9EBDDBFF, 0x59595FFF, 0x0F1217FF, 0x384D66FF, 45},
    {"Ceramic", 0xF2F2F5FF, 0x999999FF, 0x0F0F0FFF, 0x8C8F99FF, 75},
    // weitere Apple-Oberflächen, je etwas heller als das Original, damit die Schattierung lesbar bleibt
    {"Midnight", 0x3A4250FF, 0x5E6066FF, 0x0A0B0EFF, 0x15181FFF, 50},
    {"Alpine Green", 0x5F705DFF, 0x5E625EFF, 0x0B0D0BFF, 0x2A3329FF, 50},
    {"Deep Purple", 0x6A5E78FF, 0x66626BFF, 0x0D0B0FFF, 0x2E2735FF, 50},
    {"Natural Titanium", 0xB8B2A7FF, 0x8C8A86FF, 0x12110FFF, 0x5C5850FF, 70},
};

const BodyMaterial& bodyMaterial()
{
    const long i = App::GetApplication()
                       .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")
                       ->GetInt("BodyMaterial", 0);
    return bodyMaterials[std::clamp(i, 0L, long(std::size(bodyMaterials)) - 1)];
}

/// Vorgaben für neue Körper
void setDefaultMaterial()
{
    const BodyMaterial& m = bodyMaterial();
    auto view = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/View");
    view->SetUnsigned("DefaultShapeColor", m.diffuse);
    view->SetUnsigned("DefaultSpecularColor", m.specular);
    view->SetUnsigned("DefaultEmissiveColor", m.emissive);
    view->SetUnsigned("DefaultAmbientColor", 0x333333FF);
    view->SetInt("DefaultShapeShininess", m.shininess);
    view->SetUnsigned("DefaultShapeLineColor", m.line);
}

/// Farben und Schrift aus dem Theme auf App, Palette, 3D-Ansicht und Skizzen übertragen (FreeCAD beobachtet die
/// Parameter und färbt offene Ansichten sofort um)
void applyTheme()
{
    reloadTheme();
    const Theme& t = theme();
    if (!QFontDatabase::families().contains(QStringLiteral("Inter"))) {  // AppImage bringt Inter mit
        QFontDatabase::addApplicationFont(QString::fromStdString(App::Application::getHomePath())
                                          + QStringLiteral("share/fonts/Inter.ttc"));
    }
    if (QFontDatabase::families().contains(QStringLiteral("Inter"))) {
        QApplication::setFont(textFont(Text::Callout));
    }
    QApplication::setPalette(palette());
    qApp->setStyleSheet(styleSheet());
    overrideFreeCadIcons();
    TreeWidget::reloadDocumentPixmap();  // der Baum hat sein Dokument-Icon schon beim Start geladen

    // 3D-Hintergrund = Backdrop (L0): ruhiger Verlauf, im Dunkeln dunkelgrau statt schwarz
    auto view = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/View");
    view->SetBool("RadialGradient", false);
    view->SetBool("UseBackgroundColorMid", false);
    view->SetUnsigned("BackgroundColor2", packed(t.backgroundTop));
    view->SetUnsigned("BackgroundColor3", packed(t.backgroundBottom));
    view->SetBool("Gradient", true);
    view->SetBool("ShowNaviCube", false);  // eigener ViewCube (Shell/ViewCube)
    view->SetInt("AntiAliasing", 3);       // MSAA 4x: glatte Kanten (8x lässt Coin auf Intel/Mesa Flächen verlieren)
    // MyStyle: kein Token für Auswahl/Vorauswahl im 3D-Bild. Akzent aufgehellt (volles Blau überdeckt die
    // Schattierung), Vorauswahl noch heller
    view->SetUnsigned("SelectionColor", packed(mix(t.accent, Qt::white, 0.3)));
    view->SetUnsigned("HighlightColor", packed(mix(t.accent, Qt::white, t.dark ? 0.5 : 0.65)));
    view->SetUnsigned("AxisXColor", packed(t.red));
    view->SetUnsigned("AxisYColor", packed(t.green));
    view->SetUnsigned("AxisZColor", packed(t.blue));

    // Skizzenfarben wie in Fusion (FreeCADs Vorgaben sind für dunkle Hintergründe gedacht): unterbestimmt blau,
    // voll bestimmt schwarz (hell) bzw. weiß (dunkel), Konstruktion orange, projiziert lila; "voll bestimmt"
    // jeweils in der kräftigeren Kontrast-Variante derselben Systemfarbe
    view->SetUnsigned("EditedEdgeColor", packed(t.accentText));
    view->SetUnsigned("FullyConstrainedColor", packed(t.labelPrimary));
    view->SetUnsigned("FullyConstraintElementColor", packed(t.labelPrimary));
    view->SetUnsigned("ConstructionColor", packed(t.orange));
    view->SetUnsigned("FullyConstraintConstructionElementColor", packed(t.orangeIC));
    view->SetUnsigned("InternalAlignedGeoColor", packed(t.gray));
    view->SetUnsigned("FullyConstraintInternalAlignmentColor", packed(t.labelSecondary));
    view->SetUnsigned("ExternalColor", packed(t.purple));
    view->SetUnsigned("ExternalDefiningColor", packed(t.purpleIC));
    for (const char* soft : {"SketchEdgeColor", "SketchVertexColor", "ConstrainedDimColor", "ConstrainedIcoColor", "CursorTextColor"}) {
        view->SetUnsigned(soft, packed(t.labelSecondary));
    }

    // B-Splines wie in Fusion: nur das Kontrollpolygon, keine Analyse-Überlagerungen (Kamm, Gewichte, Knoten)
    auto sketcher = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/Sketcher/General");
    sketcher->SetBool("BSplineCombVisible", false);
    sketcher->SetBool("BSplinePoleWeightVisible", false);
    sketcher->SetBool("BSplineKnotMultiplicityVisible", false);
    sketcher->SetBool("BSplineDegreeVisible", false);
    // Skizzenraster: feine Linien wie Trennlinien, jede n-te etwas kräftiger
    sketcher->SetUnsigned("GridLineColor", packed(t.separatorOpaque));
    sketcher->SetUnsigned("GridDivLineColor", packed(t.gray2));
    setDefaultMaterial();
    view->SetInt("DefaultShapeLineWidth", 1);
}

/// Icon für einen Befehl: eigenes MyCAD-Icon, sonst das FreeCAD-Icon neutral eingefärbt
QIcon commandIcon(const QString& name, const QIcon& fallback)
{
    QIcon icon = designIcon(name);
    return icon.isNull() ? neutralIcon(fallback) : icon;
}

/// FreeCAD-Icons, die im Browser, in Menüs, Meldungen und im Skizzenbild auftauchen, durch eigene ersetzen.
/// Der BitmapFactory-Cache wird vor jeder Datei gefragt, also gewinnen diese Einträge überall.
void overrideFreeCadIcons()
{
    const Theme& t = theme();
    const QColor grey = t.labelSecondary, blue = t.accentText;  // Glyphen: Akzent als Vordergrund (C-2)
    struct Override
    {
        QByteArray freecad;
        QByteArray ours;
        QColor color;
    };
    std::vector<Override> overrides = {
        {"Document", "Tree_Document", grey},
        {"Geofeaturegroup.svg", "Tree_Component", blue},
        {"folder", "Tree_Folder", blue},
        {"Std_CoordinateSystem", "Tree_Origin", grey},
        {"Std_Axis", "Tree_Axis", grey},
        {"Std_Plane", "Tree_Plane", grey},
        {"Std_Point", "Tree_Point", grey},
        {"PartDesign_Body", "Tree_Body", blue},
        {"Sketcher_Sketch", "Tree_Sketch", blue},
        {"TreeItemVisible", "Tree_Visible", grey},
        {"TreeItemInvisible", "Tree_Invisible", grey},
        {"Sketcher_NotFullyConstrained", "Badge_Dot", t.orange},
        {":/icons/Warning.svg", "Badge_Warning", t.orange},
        {":/icons/info.svg", "Badge_Info", blue},
        {":/icons/critical-info.svg", "Badge_Error", t.red},
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
        overrides.push_back({name, name, t.labelPrimary});
    }
    for (const auto& o : overrides) {
        QFile file(QStringLiteral(":/mycad/icons/%1.svg").arg(QString::fromLatin1(o.ours)));
        if (!file.open(QIODevice::ReadOnly)) {
            continue;
        }
        QSvgRenderer renderer(file.readAll().replace("currentColor", o.color.name().toLatin1()));
        QImage img(64, 64, QImage::Format_ARGB32_Premultiplied);
        img.fill(Qt::transparent);
        QPainter p(&img);
        renderer.render(&p, QRectF(4, 4, 56, 56));  // etwas Luft wie bei den FreeCAD-Icons
        p.end();
        BitmapFactory().addPixmapToCache(o.freecad, QPixmap::fromImage(img));
    }
}

/// Symbol als Label, das beim Zeichnen die Theme-Farbe nimmt (Lupe, Fenstergriff)
class IconLabel: public QWidget
{
public:
    IconLabel(const QIcon& icon, int size)
        : icon(icon)
        , size(size)
    {
        setFixedSize(size, size);
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        icon.paint(&p, rect());
    }

private:
    QIcon icon;
    int size;
};

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
    /// Hilfe-ID des Werkzeugs unter der Maus (für F1)
    static QString hoveredHelp()
    {
        QToolButton* t = instance()->target;
        return t && t->underMouse() ? t->property("help").toString() : QString();
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
                const bool help = !target->property("help").toString().isEmpty();
                QToolTip::showText(target->mapToGlobal(QPoint(target->width() / 2, target->height() + 6)),
                                   target->toolTip() + (help ? QStringLiteral("\n") + T("F1: Help") : QString()), target);
            }
        });
    }
    QTimer timer;
    QPointer<QToolButton> target;
};

QString shortName(QString text);

/// Beschriftung unter dem Symbol: aus dem englischen Befehlsnamen gekürzt, dann übersetzt
QString toolLabel(const QString& name, QAction* action)
{
    Command* cmd = Application::Instance->commandManager().getCommandByName(name.toLatin1().constData());
    const QByteArray english = shortName(cmd ? QString::fromUtf8(cmd->getMenuText()) : action->text()).toUtf8();
    return T(english.constData());
}

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
    setTextStyle(btn, Text::Caption);
    if (names) {
        // zu lange Namen in zwei Zeilen umbrechen statt abschneiden (MyStyle T-8)
        const int width = dropdown ? 86 : 74;
        const QFontMetrics fm(btn->font());
        QString text = btn->property("label").toString();
        if (fm.horizontalAdvance(text) > width - 8 && text.contains(QLatin1Char(' '))) {
            int best = -1;
            for (int i = text.indexOf(QLatin1Char(' ')); i >= 0; i = text.indexOf(QLatin1Char(' '), i + 1)) {
                if (best < 0 || std::abs(2 * i - int(text.size())) < std::abs(2 * best - int(text.size()))) {
                    best = i;
                }
            }
            text = fm.elidedText(text.left(best), Qt::ElideRight, width - 8) + QLatin1Char('\n')
                + fm.elidedText(text.mid(best + 1), Qt::ElideRight, width - 8);
        }
        else {
            text = fm.elidedText(text, Qt::ElideRight, width - 8);
        }
        btn->setText(text);
        btn->setFixedSize(width, 60);
    }
    else {
        btn->setFixedSize(dropdown ? 46 : Token::WindowButton, Token::WindowButton);
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
    bool left = false;  ///< Reihen linksbündig statt mittig (Kachelraster)

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
                int px = area.left() + (left ? 0 : std::max(0, (area.width() - rowWidth) / 2));
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
            sep->setFixedSize(9, toolNames() ? 44 : 28);
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
            auto label = sectionLabel(caption);
            label->setAlignment(Qt::AlignCenter);
            column->addWidget(label);
        }
        lay->addWidget(group);
    };
    for (const char* name : commands) {
        if (*name == '#') {
            section(T(name + 1));
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
                btn->setProperty("help", n);  // F1 erklärt die gewählte Variante
                btn->setIcon(commandIcon(n, a->icon()));
                btn->setToolTip(a->toolTip().isEmpty() ? a->text() : a->toolTip());
                btn->setProperty("label", toolLabel(n, a));
                btn->setAccessibleName(btn->property("label").toString());
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
            btn->setIconSize(QSize(Token::IconL, Token::IconL));
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
            btn->setText(T("Finish Sketch"));
            btn->setToolTip(T("Finish Sketch"));
            btn->setFixedHeight(Token::ControlDesktop);
            QObject::connect(btn, &QToolButton::clicked, action, [action] {
                QTimer::singleShot(0, action, &QAction::trigger);
            });
            row->addWidget(btn);
            continue;
        }
        btn->setIcon(commandIcon(QString::fromLatin1(name), action->icon()));
        btn->setIconSize(QSize(Token::IconL, Token::IconL));
        btn->setToolTip(action->toolTip().isEmpty() ? action->text() : action->toolTip());
        btn->setProperty("label", toolLabel(QString::fromLatin1(name), action));
        btn->setAccessibleName(btn->property("label").toString());
        btn->setProperty("help", QString::fromLatin1(name));
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

void showStartPage();
void showHelp(const QString& id = QString());
void toggleBrowser();

/// Fensterknöpfe rechts oben wie unter KDE: minimieren, maximieren/wiederherstellen, schließen
class WindowControls: public QWidget
{
public:
    /// home: Home- und Hilfe-Knopf; back: zusätzlicher Zurück-Knopf vorne (Hilfe); sidebar: Knopf zum Ein-/Ausklappen
    /// der Seitenleiste (nur im Design: Startseite und Hilfe zeigen ihre Seitenleiste immer)
    explicit WindowControls(bool home = true, std::function<void()> back = {}, std::function<void()> sidebar = {})
    {
        setObjectName(QStringLiteral("GlassContent"));
        auto lay = new QHBoxLayout(this);
        lay->setContentsMargins(8, 6, 8, 6);
        lay->setSpacing(2);
        auto button = [&](const char* icon, const char* name, const QString& tip, std::function<void()> action) {
            auto btn = new QToolButton;
            btn->setObjectName(QString::fromLatin1(name));
            btn->setIcon(designIcon(QString::fromLatin1(icon)));
            btn->setIconSize(QSize(Token::IconWindow, Token::IconWindow));
            btn->setFixedSize(Token::WindowButton, Token::WindowButton);
            btn->setToolTip(tip);
            btn->setAccessibleName(tip);
            btn->setCursor(Qt::ArrowCursor);
            QObject::connect(btn, &QToolButton::clicked, btn, [action] { QTimer::singleShot(0, action); });
            lay->addWidget(btn);
            return btn;
        };
        // deutlicher Griff zum Verschieben (die Fläche um die Knöpfe allein ist zu schmal zum Treffen), 30 breit
        auto handle = new QWidget;
        handle->setFixedSize(30, Token::WindowButton);
        auto grip = new QHBoxLayout(handle);
        grip->setContentsMargins(0, 0, 0, 0);
        grip->addWidget(new IconLabel(designIcon(QStringLiteral("Window_Grip"), &Theme::labelSecondary), Token::IconWindow));
        handle->setCursor(Qt::OpenHandCursor);
        handle->setToolTip(T("Drag to move the window, double-click to maximize"));
        lay->addWidget(handle);
        if (sidebar) {
            sidebarButton = button("Window_Sidebar", "GlassButton", T("Hide sidebar"), sidebar);
        }
        if (back) {
            backButton = button("Window_Back", "GlassButton", T("Back"), back);
        }
        if (home) {
            button("Window_Home", "GlassButton", T("Home"), showStartPage);
            button("Window_Help", "GlassButton", T("Help (F1)"), [] { showHelp(); });
        }
        button("MyCAD_Settings", "GlassButton", T("Settings (Ctrl+,)"), [] {
            Application::Instance->commandManager().runCommandByName("MyCAD_Settings");
        });
        button("Window_Minimize", "GlassButton", T("Minimize"), [] { getMainWindow()->showMinimized(); });
        maximize = button("Window_Maximize", "GlassButton", T("Maximize"), toggleMaximized);
        // Schließen: rot beim Überfahren, Glyph dann weiß (autoRaise zeichnet das Icon im Zustand Active)
        button("Window_Close", "WindowClose", T("Close"), [] { getMainWindow()->close(); })->setAutoRaise(true);
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
        maximize->setToolTip(max ? T("Restore") : T("Maximize"));
    }
    QToolButton* maximize;

public:
    QToolButton* backButton = nullptr;     ///< nur mit back-Funktion
    QToolButton* sidebarButton = nullptr;  ///< nur mit sidebar-Funktion
};

// --- Startseite: neue, zuletzt geöffnete und Projekt-Designs als Kacheln ---------------------------------------

/// echte Designs (keine temporären Dokumente, z. B. beim Import)
bool anyDesignOpen()
{
    return std::ranges::any_of(App::GetApplication().getDocuments(),
                               [](App::Document* d) { return !d->testStatus(App::Document::TempDoc); });
}

/// Vorschaubild aus der Design-Datei (.mycad/.FCStd, ein ZIP mit thumbnails/Thumbnail.png; FreeCAD legt es beim Speichern an)
QImage thumbnail(const QString& file)
{
    try {
        zipios::ZipFile zip(file.toStdString());
        std::unique_ptr<std::istream> in(zip.getInputStream("thumbnails/Thumbnail.png"));
        if (in) {
            const std::string data((std::istreambuf_iterator<char>(*in)), std::istreambuf_iterator<char>());
            return QImage::fromData(QByteArray::fromStdString(data));
        }
    }
    catch (...) {  // kaputte oder fremde Datei: Platzhalter
    }
    return {};
}

QString when(const QDateTime& t)
{
    const QLocale en(language() == QLatin1String("German") ? QLocale::German : QLocale::English);
    const qint64 days = t.date().daysTo(QDate::currentDate());
    if (days == 0 || days == 1) {
        return (days == 0 ? T("Today, ") : T("Yesterday, ")) + en.toString(t.time(), QStringLiteral("HH:mm"));
    }
    return en.toString(t.date(), language() == QLatin1String("German") ? QStringLiteral("d. MMM yyyy") : QStringLiteral("MMM d, yyyy"));
}

/// Glas-Panel als Widget; der Rand von Shadow Pixeln trägt den Schatten
class GlassCard: public QWidget
{
public:
    static constexpr int Shadow = 34;  // Schatten 28 weich + 6 nach unten

    /// Inhalt: Layout mit mindestens Shadow Pixeln Rand; textSurface: Text-Glas (Seitenleiste, Artikel)
    GlassCard(qreal radius, bool textSurface)
        : radius(radius)
        , textSurface(textSurface)
    {}
    /// Panel (ohne Schattenrand) an diese Stelle setzen
    void place(const QRectF& panel)
    {
        setGeometry(panel.toRect().adjusted(-Shadow, -Shadow, Shadow, Shadow));
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        paintGlass(p, QRectF(rect()).adjusted(Shadow, Shadow, -Shadow, -Shadow), radius, textSurface);
    }

private:
    qreal radius;
    bool textSurface;
};

/// Kachel: großes rundes Vorschaubild mit Schatten, darunter Name und Datum; Hover = Akzentring
class StartTile: public QWidget
{
public:
    static constexpr QSize Picture {224, 168};
    static constexpr int Pad = 10;  // Platz für Schatten und Ring

    StartTile(const QPixmap& picture, const QString& title, const QString& subtitle, std::function<void()> action)
        : image(picture)
        , action(std::move(action))
    {
        setObjectName(QStringLiteral("StartTile"));
        setProperty("title", title);
        setAttribute(Qt::WA_Hover);
        setCursor(Qt::PointingHandCursor);
        setToolTip(title);
        setFocusPolicy(Qt::StrongFocus);
        setAccessibleName(title);
        setFixedSize(Picture.width() + 2 * Pad, Picture.height() + 2 * Pad + 40);
        auto lay = new QVBoxLayout(this);
        lay->setContentsMargins(Pad + 2, Picture.height() + 2 * Pad - 2, Pad, 0);
        lay->setSpacing(2);
        const QFont font = textFont(Text::Callout, 600);
        auto name = new QLabel(QFontMetrics(font).elidedText(title, Qt::ElideMiddle, Picture.width()));
        name->setObjectName(QStringLiteral("StartName"));
        name->setFont(font);
        lay->addWidget(name);
        auto sub = new QLabel(subtitle);
        sub->setObjectName(QStringLiteral("StartDate"));
        setTextStyle(sub, Text::Caption);
        lay->addWidget(sub);
        lay->addStretch();
    }

    /// Vorschaubild auf das Kachelformat zuschneiden; ohne Bild: Symbol auf ruhiger Fläche
    static QPixmap picture(const QImage& image, const QIcon& fallback, const QColor& fill = {})
    {
        const qreal dpr = qApp->devicePixelRatio();
        QPixmap result(Picture * dpr);
        result.setDevicePixelRatio(dpr);
        result.fill(fill.isValid() ? fill : theme().glassOpaqueTop.rgb());
        QPainter p(&result);
        p.setRenderHint(QPainter::SmoothPixmapTransform);
        if (!image.isNull()) {
            const QImage scaled = image.scaled(Picture * dpr, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            p.drawImage(QRectF(QPointF(), QSizeF(Picture)),
                        scaled.copy((scaled.width() - Picture.width() * dpr) / 2, (scaled.height() - Picture.height() * dpr) / 2,
                                    Picture.width() * dpr, Picture.height() * dpr));
        }
        else {
            const int s = 48;
            fallback.paint(&p, QRect((Picture.width() - s) / 2, (Picture.height() - s) / 2, s, s));
        }
        return result;
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        const QRectF r(QPointF(Pad, Pad), QSizeF(Picture));
        const Theme& t = theme();
        constexpr qreal radius = Token::RadiusTile;
        p.setPen(Qt::NoPen);
        if (!t.dark) {  // Kartenschatten elevation.card (0, 4, 24, 5 %), im Dunkeln keiner (D-2)
            for (int i = 8; i > 0; i -= 2) {
                p.setBrush(QColor(0, 0, 0, 4));
                p.drawRoundedRect(r.adjusted(-i, -i + 4, i, i + 4), radius + i, radius + i);
            }
        }
        QPainterPath clip;
        clip.addRoundedRect(r, radius, radius);
        p.save();
        p.setClipPath(clip);
        p.drawPixmap(r.topLeft(), image);
        p.restore();
        p.setBrush(Qt::NoBrush);
        if (underMouse() || hasFocus()) {  // Auswahl-/Fokusring, konzentrisch 4 px außen
            p.setPen(QPen(t.focusRing, 2));
            p.drawRoundedRect(r.adjusted(-4, -4, 4, 4), radius + 4, radius + 4);
        }
        else {
            p.setPen(QPen(t.materialBorder, 1));  // 1-px-Lichtkante wie bei Karten
            p.drawRoundedRect(r.adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);
        }
    }
    bool event(QEvent* e) override
    {
        if (e->type() == QEvent::HoverEnter || e->type() == QEvent::HoverLeave || e->type() == QEvent::FocusIn
            || e->type() == QEvent::FocusOut) {
            update();
        }
        return QWidget::event(e);
    }
    void keyPressEvent(QKeyEvent* event) override  // Enter/Leertaste öffnen wie ein Klick
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space) {
            QTimer::singleShot(0, action);
            return;
        }
        QWidget::keyPressEvent(event);
    }
    void mousePressEvent(QMouseEvent* event) override
    {
        event->accept();  // nicht zum Fenstergriff durchreichen
    }
    void mouseReleaseEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton && rect().contains(event->position().toPoint())) {
            QTimer::singleShot(0, action);
        }
    }

private:
    QPixmap image;
    std::function<void()> action;
};


/// Hintergrund von Startseite und Hilfe: wie der Hintergrund des 3D-Fensters
void paintBackdrop(QPainter& p, const QRect& r)
{
    QLinearGradient base(0, 0, 0, r.height());
    base.setColorAt(0, theme().backgroundTop);
    base.setColorAt(1, theme().backgroundBottom);
    p.fillRect(r, base);
}

/// Startseite im Stil des restlichen MyCAD: Viewport-Hintergrund, links ein Glas-Panel (Neu, Öffnen, Bereiche),
/// oben Suche und die Fensterknöpfe in einer Glas-Kapsel, rechts die Designs als große Vorschaubilder
class StartPage: public QWidget
{
public:
    StartPage()
        : QWidget(getMainWindow())
    {
        setObjectName(QStringLiteral("StartPage"));
        static WindowGrip grip;
        installEventFilter(&grip);  // freie Fläche verschiebt das Fenster

        // --- Seitenleiste an der Stelle des Browsers ---
        // Seitenleiste: Text-Glas, innen 8 seitlich, 16 oben, 14 unten
        side = new GlassCard(Token::RadiusPanel, true);
        side->setParent(this);
        auto sideLay = new QVBoxLayout(side);
        sideLay->setContentsMargins(GlassCard::Shadow + 8, GlassCard::Shadow + 16, GlassCard::Shadow + 8, GlassCard::Shadow + 14);
        sideLay->setSpacing(2);
        auto title = new QLabel(QStringLiteral("MyCAD"));
        setTextStyle(title, Text::Title2);
        title->setContentsMargins(10, 0, 0, 0);
        sideLay->addWidget(title);
        sideLay->addSpacing(16);
        auto create = new QPushButton(designIcon(QStringLiteral("Std_New"), &Theme::labelOnAccent), T("New Design"));
        create->setObjectName(QStringLiteral("Prominent"));
        create->setCursor(Qt::PointingHandCursor);
        QObject::connect(create, &QPushButton::clicked, this, [this] { runAndHide("Std_New"); });
        sideLay->addWidget(create);
        sideLay->addSpacing(4);
        auto row = [&](const char* icon, const QString& text) {
            auto b = new QToolButton;
            b->setObjectName(QStringLiteral("PaletteRow"));
            b->setIcon(designIcon(QString::fromLatin1(icon), &Theme::labelSecondary));
            b->setIconSize(QSize(Token::IconM, Token::IconM));
            b->setText(text);
            b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
            b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            b->setFixedHeight(32);
            sideLay->addWidget(b);
            return b;
        };
        QObject::connect(row("Std_Open", T("Open…")), &QToolButton::clicked, this, [this] { runAndHide("Std_Open"); });
        sideLay->addSpacing(12);
        auto library = sectionLabel(T("LIBRARY"));
        library->setContentsMargins(10, 0, 0, 4);
        sideLay->addWidget(library);
        auto group = new QButtonGroup(this);
        const std::pair<const char*, QString> filters[] = {{"Window_Home", T("All Designs")},
                                                           {"Start_Recent", T("Recent")},
                                                           {"Std_Open", T("Projects")}};
        for (int i = 0; i < 3; ++i) {
            QToolButton* b = row(filters[i].first, filters[i].second);
            b->setCheckable(true);
            b->setChecked(i == 0);
            group->addButton(b, i);
        }
        QObject::connect(group, &QButtonGroup::idClicked, this, [this](int id) {
            filter = id;
            applyFilter();
        });
        sideLay->addStretch();
        folderLabel = new QLabel;
        folderLabel->setObjectName(QStringLiteral("Hint"));
        setTextStyle(folderLabel, Text::Caption);
        folderLabel->setContentsMargins(10, 0, 0, 0);
        folderLabel->setWordWrap(true);
        sideLay->addWidget(folderLabel);
        side->installEventFilter(&grip);

        // --- Designs (unter den Glasflächen, damit deren Schatten sichtbar bleiben) ---
        scroll = new QScrollArea(this);
        scroll->setObjectName(QStringLiteral("StartScroll"));
        scroll->setWidgetResizable(true);
        scroll->setFrameShape(QFrame::NoFrame);
        scroll->viewport()->setAutoFillBackground(false);
        scroll->lower();

        // --- oben: Suche an der Stelle der Toolbar, Fensterknöpfe wie im 3D-Fenster ---
        searchCard = new GlassCard(Token::RadiusCapsule, false);
        searchCard->setParent(this);
        auto searchLay = new QHBoxLayout(searchCard);
        searchLay->setContentsMargins(GlassCard::Shadow + 16, GlassCard::Shadow, GlassCard::Shadow + 12, GlassCard::Shadow);
        searchLay->addWidget(new IconLabel(designIcon(QStringLiteral("Start_Search"), &Theme::labelSecondary), Token::IconM));
        search = new QLineEdit;
        search->setObjectName(QStringLiteral("StartSearch"));
        search->setPlaceholderText(T("Search designs"));
        search->setAccessibleName(T("Search designs"));
        search->setClearButtonEnabled(true);  // Löschen-Kreuz rechts
        QObject::connect(search, &QLineEdit::textChanged, this, [this] { applyFilter(); });
        searchLay->addWidget(search);
        controlsCard = new GlassCard(Token::RadiusCapsule, false);
        controlsCard->setParent(this);
        auto controlsLay = new QHBoxLayout(controlsCard);
        controlsLay->setContentsMargins(GlassCard::Shadow, GlassCard::Shadow, GlassCard::Shadow, GlassCard::Shadow);
        controls = new WindowControls(true, [this] { hide(); });  // wie im 3D-Fenster; Zurück vorne wie in der Hilfe
        controls->backButton->setToolTip(T("Back to Design"));
        controls->installEventFilter(&grip);
        controlsLay->addWidget(controls);

        getMainWindow()->installEventFilter(this);
        hide();
    }

    void open()
    {
        const bool wasVisible = isVisible();
        rebuild();
        controls->backButton->setVisible(anyDesignOpen());
        setGeometry(getMainWindow()->rect());
        place();
        show();
        raise();
        if (!wasVisible) {  // weich einblenden
            auto fade = new QGraphicsOpacityEffect(this);
            setGraphicsEffect(fade);
            auto anim = new QPropertyAnimation(fade, "opacity", fade);
            anim->setDuration(Token::DurationFade);
            anim->setStartValue(0.0);
            anim->setEndValue(1.0);
            anim->setEasingCurve(QEasingCurve::OutCubic);
            QObject::connect(anim, &QPropertyAnimation::finished, this, [this] { setGraphicsEffect(nullptr); });
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (obj == getMainWindow() && event->type() == QEvent::Resize) {
            setGeometry(getMainWindow()->rect());
        }
        return false;
    }
    void resizeEvent(QResizeEvent*) override
    {
        place();
    }
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Escape && anyDesignOpen()) {
            hide();
        }
    }
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        paintBackdrop(p, rect());
    }

private:
    /// Glasflächen an dieselben Stellen wie Browser, Toolbar und Fensterknöpfe in layout()
    void place()
    {
        const qreal m = Token::WindowInset;
        const qreal barH = controls->sizeHint().height();  // so flach wie die Knöpfe selbst
        side->place(QRectF(m, m, BrowserWidth, height() - 2 * m));
        const QSizeF cs = controls->sizeHint();
        const QRectF ctl(width() - cs.width() - m, m, cs.width(), barH);
        controlsCard->place(ctl);
        const qreal left = m + BrowserWidth + 32;  // etwas mehr Luft zur Seitenleiste als zwischen den Panels
        searchCard->place(QRectF(left, m, std::min<qreal>(380, ctl.left() - m - left), barH));  // so hoch wie die Kapsel
        const int top = int(m + barH + m);
        scroll->setGeometry(int(left) - StartTile::Pad, top, int(width() - left - m + StartTile::Pad), height() - top);
    }

    void runAndHide(const char* command)
    {
        Application::Instance->commandManager().runCommandByName(command);
        if (anyDesignOpen()) {
            hide();
        }
    }

    void rebuild()
    {
        auto page = new QWidget;
        page->setObjectName(QStringLiteral("StartContent"));
        auto lay = new QVBoxLayout(page);
        lay->setContentsMargins(0, 8, 12, 40);  // beginnt mit der Suche, wie die Toolbar
        lay->setSpacing(6);
        sections.clear();
        auto section = [&](const QString& heading, const QString& caption) {
            auto box = new QWidget;
            auto boxLay = new QVBoxLayout(box);
            boxLay->setContentsMargins(0, 10, 0, 10);
            boxLay->setSpacing(4);
            auto label = new QLabel(heading);
            setTextStyle(label, Text::Title2);
            label->setContentsMargins(StartTile::Pad, 0, 0, 0);
            boxLay->addWidget(label);
            if (!caption.isEmpty()) {
                auto cap = new QLabel(caption);
                cap->setObjectName(QStringLiteral("StartCaption"));
                setTextStyle(cap, Text::Caption);
                cap->setContentsMargins(StartTile::Pad, 0, 0, 0);
                boxLay->addWidget(cap);
            }
            boxLay->addSpacing(6);
            auto grid = new QWidget;
            auto flow = new FlowLayout(grid);
            flow->left = true;
            flow->setContentsMargins(0, 0, 0, 0);
            flow->setSpacing(10);
            boxLay->addWidget(grid);
            lay->addWidget(box);
            sections.push_back(box);
            return flow;
        };
        auto hint = [&](FlowLayout* flow, const QString& text) {
            auto label = new QLabel(text);
            label->setObjectName(QStringLiteral("StartCaption"));
            setTextStyle(label, Text::Callout);
            label->setContentsMargins(StartTile::Pad, 0, 0, 0);
            flow->addWidget(label);
        };
        auto openFile = [this](const QString& file) {
            return [this, file] {
                Application::Instance->open(file.toUtf8().constData(), "FreeCAD");
                if (anyDesignOpen()) {
                    hide();  // auch wenn die Datei schon offen war (dann gibt es kein neues Dokument)
                }
            };
        };
        auto tile = [&](const QString& file) {
            const QFileInfo fi(file);
            return new StartTile(StartTile::picture(thumbnail(file), designIcon(QStringLiteral("Design_Box"))),
                                 fi.completeBaseName(), when(fi.lastModified()), openFile(fi.absoluteFilePath()));
        };

        // zuletzt geöffnet (FreeCAD führt die Liste; Skripte und gelöschte Dateien überspringen)
        FlowLayout* recent = section(T("Recent"), QString());
        const QStringList designFiles {QStringLiteral("*.mycad"), QStringLiteral("*.FCStd")};  // eigenes Format, ältere Designs
        auto mru = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/RecentFiles")->GetASCIIs("MRU");
        int shown = 0;
        for (const auto& entry : mru) {
            const QString file = QString::fromUtf8(entry.c_str());
            if (shown < 8 && QDir::match(designFiles, QFileInfo(file).fileName()) && QFileInfo::exists(file)) {
                recent->addWidget(tile(file));
                ++shown;
            }
        }
        if (!shown) {
            hint(recent, T("Designs you open or save show up here."));
        }

        const QString folder = Gui::Shell::projectsFolder();
        QString pretty = folder;
        pretty.replace(QDir::homePath(), QStringLiteral("~"));
        folderLabel->setText(T("Projects folder\n%1").arg(pretty) + QStringLiteral("\n\nMyCAD ") + Gui::Shell::version());
        FlowLayout* projects = section(T("Projects"), pretty);
        // Designs direkt im Ordner und in Projektunterordnern (Speichern legt je Design einen an), neueste zuerst
        QFileInfoList files = QDir(folder).entryInfoList(designFiles, QDir::Files);
        for (const QFileInfo& sub : QDir(folder).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            files += QDir(sub.absoluteFilePath()).entryInfoList(designFiles, QDir::Files);
        }
        std::sort(files.begin(), files.end(), [](const QFileInfo& a, const QFileInfo& b) { return a.lastModified() > b.lastModified(); });
        for (const QFileInfo& fi : files) {
            projects->addWidget(tile(fi.absoluteFilePath()));
        }
        if (files.isEmpty()) {
            hint(projects, T("Save designs to %1 and they show up here.").arg(pretty));
        }
        lay->addStretch();
        scroll->setWidget(page);  // ersetzt (und löscht) den alten Inhalt
        applyFilter();
    }

    /// Bereich (Alle / Recent / Projects) und Suchtext anwenden
    void applyFilter()
    {
        const QString text = search->text().trimmed();
        for (int i = 0; i < int(sections.size()); ++i) {
            sections[i]->setVisible(filter == 0 || filter == i + 1);
            for (auto t : sections[i]->findChildren<QWidget*>(QStringLiteral("StartTile"))) {
                t->setVisible(text.isEmpty() || t->property("title").toString().contains(text, Qt::CaseInsensitive));
            }
        }
    }

    GlassCard* side;
    GlassCard* searchCard;
    GlassCard* controlsCard;
    WindowControls* controls;
    QScrollArea* scroll;
    QLineEdit* search;
    QLabel* folderLabel;
    std::vector<QWidget*> sections;
    int filter = 0;
};

StartPage* startPage = nullptr;

// --- Hilfe: jedes Werkzeug erklärt, mit Bildern, Schlagwörtern und Suche (Inhalt: Shell/help/help.json) ----------

/// Text eines Artikel-Felds in der eingestellten Sprache (Englisch als Rückfall)
QJsonValue localized(const QJsonObject& article, const char* field)
{
    const QJsonObject texts = article.value(QLatin1String(field)).toObject();
    const QString lang = language() == QLatin1String("German") ? QStringLiteral("de") : QStringLiteral("en");
    return texts.contains(lang) ? texts.value(lang) : texts.value(QStringLiteral("en"));
}

QIcon helpIcon(const QString& name)
{
    if (QAction* a = commandAction(name.toLatin1().constData())) {
        return commandIcon(name, a->icon());
    }
    return designIcon(name);
}

class HelpPage: public QWidget
{
public:
    HelpPage()
        : QWidget(getMainWindow())
    {
        setObjectName(QStringLiteral("HelpPage"));
        static WindowGrip grip;
        installEventFilter(&grip);
        QFile file(QStringLiteral(":/mycad/help/help.json"));
        if (file.open(QIODevice::ReadOnly)) {
            const QJsonObject root = QJsonDocument::fromJson(file.readAll()).object();
            groups = root.value(QStringLiteral("groups")).toArray();
            for (const QJsonValue v : root.value(QStringLiteral("articles")).toArray()) {
                articles.append(v.toObject());
            }
        }

        // Seitenleiste mit allen Artikeln, nach Toolbar-Bereichen gruppiert
        side = new GlassCard(Token::RadiusPanel, true);
        side->setParent(this);
        side->installEventFilter(&grip);
        auto sideLay = new QVBoxLayout(side);
        sideLay->setContentsMargins(GlassCard::Shadow + 8, GlassCard::Shadow + 16, GlassCard::Shadow + 8, GlassCard::Shadow + 14);
        auto title = new QLabel(T("Help"));
        setTextStyle(title, Text::Title2);
        title->setContentsMargins(10, 0, 0, 0);
        sideLay->addWidget(title);
        sideLay->addSpacing(8);
        auto list = new QScrollArea;
        list->setObjectName(QStringLiteral("StartScroll"));
        list->setWidgetResizable(true);
        list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        list->setFrameShape(QFrame::NoFrame);
        list->viewport()->setAutoFillBackground(false);
        auto listWidget = new QWidget;
        listWidget->setObjectName(QStringLiteral("StartContent"));
        auto listLay = new QVBoxLayout(listWidget);
        listLay->setContentsMargins(0, 0, 4, 0);
        listLay->setSpacing(1);
        rowGroup = new QButtonGroup(this);
        for (const QJsonValue g : groups) {
            const QJsonObject group = g.toObject();
            auto caption = sectionLabel(localized(group, "title").toString());
            caption->setContentsMargins(10, 12, 0, 4);
            listLay->addWidget(caption);
            captions.append({caption, group.value(QStringLiteral("id")).toString()});
            for (int i = 0; i < articles.size(); ++i) {
                if (articles[i].value(QStringLiteral("group")) != group.value(QStringLiteral("id"))) {
                    continue;
                }
                auto b = new QToolButton;
                b->setObjectName(QStringLiteral("PaletteRow"));
                b->setIcon(helpIcon(articles[i].value(QStringLiteral("icon")).toString()));
                b->setIconSize(QSize(Token::IconM, Token::IconM));
                b->setText(localized(articles[i], "title").toString());
                b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
                b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
                b->setFixedHeight(32);
                b->setCheckable(true);
                b->setProperty("group", group.value(QStringLiteral("id")).toString());
                rowGroup->addButton(b, i);
                listLay->addWidget(b);
            }
        }
        listLay->addStretch();
        list->setWidget(listWidget);
        sideLay->addWidget(list);
        QObject::connect(rowGroup, &QButtonGroup::idClicked, this, [this](int i) { showArticle(i); });

        // Artikel
        articleCard = new GlassCard(Token::RadiusPanel, true);
        articleCard->setParent(this);
        auto articleLay = new QVBoxLayout(articleCard);
        articleLay->setContentsMargins(GlassCard::Shadow + 28, GlassCard::Shadow + 20, GlassCard::Shadow + 16, GlassCard::Shadow + 16);
        view = new QTextBrowser;
        view->setObjectName(QStringLiteral("HelpArticle"));
        view->setFrameShape(QFrame::NoFrame);
        view->setOpenLinks(false);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->viewport()->setAutoFillBackground(false);
        QObject::connect(view, &QTextBrowser::anchorClicked, this, [this](const QUrl& url) {
            if (url.scheme() == QLatin1String("help")) {
                open(url.path());
            }
        });
        articleLay->addWidget(view);

        // oben: Suche an der Stelle der Toolbar, rechts Zurück und Fensterknöpfe wie überall
        searchCard = new GlassCard(Token::RadiusCapsule, false);
        searchCard->setParent(this);
        auto searchLay = new QHBoxLayout(searchCard);
        searchLay->setContentsMargins(GlassCard::Shadow + 16, GlassCard::Shadow, GlassCard::Shadow + 12, GlassCard::Shadow);
        searchLay->addWidget(new IconLabel(designIcon(QStringLiteral("Start_Search"), &Theme::labelSecondary), Token::IconM));
        search = new QLineEdit;
        search->setObjectName(QStringLiteral("StartSearch"));
        search->setPlaceholderText(T("Search help, e.g. donut, hole, rounded"));
        search->setAccessibleName(T("Search help, e.g. donut, hole, rounded"));
        search->setClearButtonEnabled(true);
        QObject::connect(search, &QLineEdit::textChanged, this, [this] { filter(); });
        QObject::connect(search, &QLineEdit::returnPressed, this, [this] {
            for (QAbstractButton* b : rowGroup->buttons()) {
                if (b->isVisible()) {
                    showArticle(rowGroup->id(b));
                    return;
                }
            }
        });
        searchLay->addWidget(search);
        controlsCard = new GlassCard(Token::RadiusCapsule, false);
        controlsCard->setParent(this);
        auto controlsLay = new QHBoxLayout(controlsCard);
        controlsLay->setContentsMargins(GlassCard::Shadow, GlassCard::Shadow, GlassCard::Shadow, GlassCard::Shadow);
        controls = new WindowControls(true, [this] { hide(); });  // Zurück vorne in der Kapsel
        controls->installEventFilter(&grip);
        controlsLay->addWidget(controls);

        getMainWindow()->installEventFilter(this);
        hide();
    }

    /// Artikel in den Farben des aktuellen Themes neu setzen (Wechsel Hell/Dunkel)
    void refresh()
    {
        if (current >= 0) {
            showArticle(current);
        }
    }

    /// Artikel zu einem Befehl (z. B. "Design_Extrude") oder einer Artikel-ID öffnen; leer = Übersicht
    void open(const QString& id)
    {
        int index = 0;
        for (int i = 0; i < articles.size(); ++i) {
            const QJsonObject& a = articles[i];
            if (a.value(QStringLiteral("id")).toString() == id
                || a.value(QStringLiteral("commands")).toArray().contains(QJsonValue(id))) {
                index = i;
                break;
            }
        }
        search->clear();
        setGeometry(getMainWindow()->rect());
        resizeEvent(nullptr);
        show();
        raise();
        showArticle(index);
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (obj == getMainWindow() && event->type() == QEvent::Resize) {
            setGeometry(getMainWindow()->rect());
        }
        return false;
    }
    void resizeEvent(QResizeEvent*) override
    {
        const qreal m = Token::WindowInset;
        const qreal barH = controls->sizeHint().height();  // so flach wie die Knöpfe selbst
        side->place(QRectF(m, m, BrowserWidth, height() - 2 * m));
        const QSizeF cs = controls->sizeHint();
        const QRectF ctl(width() - cs.width() - m, m, cs.width(), barH);
        controlsCard->place(ctl);
        const qreal searchLeft = m + BrowserWidth + 32;  // wie auf der Startseite
        searchCard->place(QRectF(searchLeft, m, std::min<qreal>(420, ctl.left() - m - searchLeft), barH));  // so hoch wie die Kapsel
        const qreal top = m + barH + m;
        // Lesebreite höchstens size.contentMaxWidth (560) plus Innenabstand und Scrollbar (W-4)
        const qreal articleWidth = std::min<qreal>(width() - searchLeft - m, Token::ContentMaxWidth + 28 + 16 + 24);
        articleCard->place(QRectF(searchLeft, top, articleWidth, height() - top - m));  // bündig mit der Suche
    }
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Escape) {
            hide();
        }
    }
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        paintBackdrop(p, rect());
    }

private:
    void showArticle(int index)
    {
        if (index < 0 || index >= articles.size()) {
            return;
        }
        if (QAbstractButton* b = rowGroup->button(index)) {
            b->setChecked(true);
        }
        current = index;
        const QJsonObject& a = articles[index];
        QTextDocument* doc = view->document();
        // Desktop-Skala: Title 1, Headline, Body, Caption; Kurzbeschreibung als Body in Sekundärfarbe
        doc->setDefaultStyleSheet(QStringLiteral(R"(
h1 { font-size: 24px; font-weight: 700; letter-spacing: -0.47px; margin: 0; }
h3 { font-size: 15px; font-weight: 600; letter-spacing: -0.13px; margin-top: 12px; margin-bottom: 4px; }
p, li, td { font-size: 14px; letter-spacing: -0.09px; line-height: 150%; }
.summary { color: %1; }
.caption { font-size: 12px; font-weight: 500; color: %1; }
.keywords { font-size: 12px; font-weight: 500; color: %2; }
.option { font-weight: 600; padding-right: 16px; }
a { color: %3; text-decoration: none; }
)")
                                      .arg(theme().labelSecondary.name(), theme().labelTertiary.name(), theme().accentText.name()));
        const QUrl iconUrl(QStringLiteral("icon:%1").arg(index));
        doc->addResource(QTextDocument::ImageResource, iconUrl,
                         helpIcon(a.value(QStringLiteral("icon")).toString()).pixmap(48, 48).toImage());
        auto esc = [](const QString& s) { return s.toHtmlEscaped(); };
        QString html = QStringLiteral("<table><tr><td><img src=\"%1\" width=\"40\" height=\"40\"></td>"
                                      "<td style=\"padding-left:12px; vertical-align:middle\"><h1>%2</h1></td></tr></table>")
                           .arg(iconUrl.toString(), esc(localized(a, "title").toString()));
        html += QStringLiteral("<p class=\"summary\">%1</p>").arg(esc(localized(a, "summary").toString()));
        for (const QJsonValue v : a.value(QStringLiteral("images")).toArray()) {
            const QJsonObject img = v.toObject();
            const QString caption = localized(img, "caption").toString();
            const QString file = QStringLiteral(":/mycad/help/images/") + img.value(QStringLiteral("file")).toString();
            // selbst auf 560 px skalieren: mit width-Attribut reserviert Qt die Originalhöhe (große Lücke darunter)
            const QUrl picture(QStringLiteral("picture:%1").arg(file));
            QImage image = QImage(file).scaledToWidth(Token::ContentMaxWidth, Qt::SmoothTransformation);
            if (theme().dark) {  // helle Bildschirmfotos im Dunkeln leicht abdunkeln (MyStyle D-4)
                QPainter dim(&image);
                dim.fillRect(image.rect(), QColor(0, 0, 0, 38));
            }
            doc->addResource(QTextDocument::ImageResource, picture, image);
            html += QStringLiteral("<p style=\"margin-bottom:0; line-height:100%\"><img src=\"%1\">%2</p>")
                        .arg(picture.toString(),
                             caption.isEmpty() ? QString() : QStringLiteral("<br><span class=\"caption\">%1</span>").arg(esc(caption)));
        }
        auto list = [&](const char* field, const QString& heading, bool numbered) {
            const QJsonArray items = localized(a, field).toArray();
            if (items.isEmpty()) {
                return;
            }
            html += QStringLiteral("<h3>%1</h3>").arg(esc(heading)) + (numbered ? QStringLiteral("<ol>") : QStringLiteral("<ul>"));
            for (const QJsonValue item : items) {
                html += QStringLiteral("<li>%1</li>").arg(esc(item.toString()));
            }
            html += numbered ? QStringLiteral("</ol>") : QStringLiteral("</ul>");
        };
        list("steps", T("How to use it"), true);
        const QJsonArray options = localized(a, "options").toArray();
        if (!options.isEmpty()) {
            html += QStringLiteral("<h3>%1</h3><table cellspacing=\"6\">").arg(esc(T("Options")));
            for (const QJsonValue o : options) {
                const QJsonArray pair = o.toArray();
                html += QStringLiteral("<tr><td class=\"option\">%1</td><td>%2</td></tr>")
                            .arg(esc(pair.at(0).toString()), esc(pair.at(1).toString()));
            }
            html += QStringLiteral("</table>");
        }
        list("tips", T("Tips"), false);
        const QJsonArray see = a.value(QStringLiteral("see")).toArray();
        if (!see.isEmpty()) {
            QStringList links;
            for (const QJsonValue s : see) {
                for (const QJsonObject& other : std::as_const(articles)) {
                    if (other.value(QStringLiteral("id")) == s) {
                        links << QStringLiteral("<a href=\"help:%1\">%2</a>").arg(s.toString(), esc(localized(other, "title").toString()));
                    }
                }
            }
            html += QStringLiteral("<h3>%1</h3><p>%2</p>").arg(esc(T("See also")), links.join(QStringLiteral(" · ")));
        }
        QStringList keywords;
        for (const QJsonValue k : localized(a, "keywords").toArray()) {
            keywords << k.toString();
        }
        if (!keywords.isEmpty()) {
            html += QStringLiteral("<p class=\"keywords\">%1: %2</p>").arg(esc(T("Keywords")), esc(keywords.join(QStringLiteral(", "))));
        }
        view->setHtml(html);
    }

    /// Suche in Titel, Schlagwörtern, Kurzbeschreibung und Schritten
    void filter()
    {
        const QStringList words = search->text().simplified().split(QLatin1Char(' '), Qt::SkipEmptyParts);
        QSet<QString> visibleGroups;
        for (QAbstractButton* b : rowGroup->buttons()) {
            const QJsonObject& a = articles[rowGroup->id(b)];
            QString haystack = localized(a, "title").toString() + QLatin1Char(' ') + localized(a, "summary").toString();
            for (const char* field : {"keywords", "steps", "tips"}) {
                for (const QJsonValue v : localized(a, field).toArray()) {
                    haystack += QLatin1Char(' ') + v.toString();
                }
            }
            const bool match = std::ranges::all_of(words, [&](const QString& w) { return haystack.contains(w, Qt::CaseInsensitive); });
            b->setVisible(match);
            if (match) {
                visibleGroups.insert(b->property("group").toString());
            }
        }
        for (const auto& [caption, group] : captions) {
            caption->setVisible(visibleGroups.contains(group));
        }
    }

    QJsonArray groups;
    QList<QJsonObject> articles;
    QList<std::pair<QLabel*, QString>> captions;
    QButtonGroup* rowGroup;
    GlassCard* side;
    GlassCard* articleCard;
    GlassCard* searchCard;
    GlassCard* controlsCard;
    WindowControls* controls;
    QTextBrowser* view;
    QLineEdit* search;
    int current = -1;
};

HelpPage* helpPage = nullptr;

void showHelp(const QString& id)
{
    if (!helpPage) {
        helpPage = new HelpPage;  // erst bei Bedarf: lädt Inhalt und Symbole
    }
    helpPage->open(id);
}



void showStartPage()
{
    if (startPage) {
        startPage->open();
    }
}

/// Glas-Alert (L3): Text-Glas als Frost (eigenes Fenster, kein Blur möglich), r 20, Schatten, statt Titelleiste
class AlertPainter: public QObject
{
public:
    static constexpr int Shadow = 34;  // Schatten 28 weich + 6 nach unten

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (event->type() == QEvent::Paint) {
            auto box = static_cast<QWidget*>(obj);
            QPainter p(box);
            paintGlass(p, QRectF(box->rect()).adjusted(Shadow, Shadow, -Shadow, -Shadow), Token::RadiusPanel, true, true);
        }
        return false;  // Text und Knöpfe zeichnet die Box selbst
    }
};

/// Abdunklung (color.scrim) über dem Hauptfenster, solange ein modaler Dialog oder Alert offen ist (L3)
class Scrim: public QObject
{
public:
    static Scrim* instance()
    {
        static Scrim* scrim = new Scrim;
        return scrim;
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        auto dialog = static_cast<QWidget*>(obj);
        if (event->type() == QEvent::Show && dialog->isWindow() && dialog->windowModality() != Qt::NonModal) {
            open.insert(obj);
        }
        else if (event->type() == QEvent::Hide) {
            open.remove(obj);
        }
        else {
            return false;
        }
        MainWindow* mw = getMainWindow();
        if (!overlay) {
            overlay = new Overlay;
            overlay->setParent(mw);
            overlay->setAttribute(Qt::WA_TransparentForMouseEvents);
        }
        overlay->setGeometry(mw->rect());
        overlay->setVisible(!open.isEmpty());
        overlay->raise();
        return false;
    }

private:
    struct Overlay: QWidget
    {
        void paintEvent(QPaintEvent*) override
        {
            QPainter(this).fillRect(rect(), theme().scrim);
        }
    };
    QPointer<Overlay> overlay;
    QSet<QObject*> open;
};

/// Menüs mit runden Ecken: dafür brauchen sie einen transparenten, rahmenlosen Hintergrund.
/// Liquid Glass: Meldungen und Rückfragen als rahmenlose Glas-Alerts (Titel fett im Text, Kapsel-Knöpfe)
class MenuPolisher: public QObject
{
protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (event->type() == QEvent::Polish) {
            if (auto box = qobject_cast<QMessageBox*>(obj); box && !box->property("glass").toBool()) {
                static AlertPainter painter;
                box->setProperty("glass", true);
                box->setAttribute(Qt::WA_TranslucentBackground);
                box->setWindowFlags(box->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
                // Beim Polieren existiert das native Fenster schon ohne Alphakanal (der Schattenrand wäre schwarz):
                // mit Alphakanal neu anlegen lassen
                if (QWindow* window = box->windowHandle()) {
                    QSurfaceFormat format = window->format();
                    format.setAlphaBufferSize(8);
                    window->setFormat(format);
                    window->destroy();
                }
                // Innenabstand 20 oben, 22 seitlich, 18 unten (MyStyle § 7.1); QMessageBox bringt selbst etwa 10 mit
                box->setContentsMargins(AlertPainter::Shadow + 12, AlertPainter::Shadow + 10, AlertPainter::Shadow + 12,
                                        AlertPainter::Shadow + 8);
                box->installEventFilter(&painter);
                // Titel Headline; Text und Zusatztext Callout in Sekundärfarbe ins Zusatztext-Feld: das bricht in
                // Fensterbreite um (beim Haupttext schaltet Qt den Umbruch zum Bemessen ab, er würde abgeschnitten)
                if (!box->windowTitle().isEmpty() && !Qt::mightBeRichText(box->text())) {
                    auto html = [](const QString& s) { return s.toHtmlEscaped().replace(QLatin1Char('\n'), QStringLiteral("<br>")); };
                    QString body = html(box->text());
                    if (!box->informativeText().isEmpty()) {
                        body += QStringLiteral("<br><br>") + html(box->informativeText());
                    }
                    box->setText(QStringLiteral("<p style='font-size:15px; font-weight:600; letter-spacing:-0.13px'>%1</p>")
                                     .arg(box->windowTitle().toHtmlEscaped()));
                    box->setInformativeText(body);
                    if (auto info = box->findChild<QLabel*>(QStringLiteral("qt_msgbox_informativelabel"))) {
                        info->setTextFormat(Qt::RichText);
                        info->setMinimumWidth(360 - 2 * 22);  // 360 breit, breiter nur wenn die Knöpfe es brauchen
                    }
                }
                box->setIcon(QMessageBox::NoIcon);
                // Text bündig mit den Knöpfen: ohne Symbol rückt Qt den Text trotzdem ein (Spaltenabstand, Einrückung)
                if (auto grid = qobject_cast<QGridLayout*>(box->layout())) {
                    grid->setHorizontalSpacing(0);
                    grid->setColumnStretch(grid->columnCount() - 1, 1);  // Platz der Knopfzeile geht an den Text
                    for (int i = 0; i < grid->count(); ++i) {
                        if (QSpacerItem* indent = grid->itemAt(i)->spacerItem(); indent && indent->sizeHint().height() <= 1) {
                            indent->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
                        }
                    }
                }
                box->style()->unpolish(box);  // Stylesheet-Regeln für [glass="true"] greifen erst nach neuem Polieren
                box->style()->polish(box);
            }
            if (auto dialog = qobject_cast<QDialog*>(obj); dialog && dialog->parentWidget()) {
                dialog->installEventFilter(Scrim::instance());
            }
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
                menu.addAction(T("Rename"), [tree, item] { tree->editItem(item); });
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

/// F1: Hilfe zum Werkzeug unter der Maus, sonst zum gerade bearbeiteten Feature, sonst die Übersicht
class HelpKey: public QObject
{
protected:
    bool eventFilter(QObject*, QEvent* event) override
    {
        if (event->type() != QEvent::ShortcutOverride && event->type() != QEvent::KeyPress) {
            return false;
        }
        if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_F1) {
            return false;
        }
        if (event->type() == QEvent::ShortcutOverride) {
            event->accept();  // nicht FreeCADs Online-Hilfe auslösen
            return true;
        }
        QString id = QuickTip::hoveredHelp();
        if (id.isEmpty()) {
            Gui::Document* gdoc = Application::Instance->activeDocument();
            auto edit = gdoc ? dynamic_cast<ViewProviderDocumentObject*>(gdoc->getInEdit()) : nullptr;
            if (edit) {  // "Design::Extrude" -> "Design_Extrude", Skizze -> Skizzen-Grundlagen
                id = QString::fromLatin1(edit->getObject()->getTypeId().getName()).replace(QStringLiteral("::"), QStringLiteral("_"));
                if (id.startsWith(QLatin1String("Sketcher_"))) {
                    id = QStringLiteral("sketch_basics");
                }
            }
        }
        QTimer::singleShot(0, [id] { showHelp(id); });
        return true;
    }
};

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
        auto tree = qobject_cast<QTreeWidget*>(widget->parentWidget());
        // Browser: Menü erst beim Loslassen der rechten Taste öffnen. Öffnet es schon beim Drücken (Qt-Standard unter
        // Linux), schluckt das Menü das Loslassen; Qt hält die Taste dann für gedrückt und Knöpfe in danach geöffneten
        // Dialogen (z. B. "Delete" in der Rückfrage) reagieren nicht auf Klicks
        if (tree && event->type() == QEvent::ContextMenu
            && static_cast<QContextMenuEvent*>(event)->reason() == QContextMenuEvent::Mouse) {
            return true;
        }
        const bool rightRelease = event->type() == QEvent::MouseButtonRelease
            && static_cast<QMouseEvent*>(event)->button() == Qt::RightButton;
        if (tree && (event->type() == QEvent::ContextMenu || rightRelease)) {
            const QPoint pos = rightRelease ? static_cast<QMouseEvent*>(event)->position().toPoint()
                                            : static_cast<QContextMenuEvent*>(event)->pos();
            // Dokument-Eintrag: speichern, umbenennen, schließen (ein Dokument wird geschlossen, nicht gelöscht)
            QTreeWidgetItem* item = tree->itemAt(pos);
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
                    QObject::connect(menu.addAction(T("Save")), &QAction::triggered, [run] { run("Std_Save"); });
                    QObject::connect(menu.addAction(T("Save As…")), &QAction::triggered, [run] { run("Std_SaveAs"); });
                    QObject::connect(menu.addAction(T("Export…")), &QAction::triggered, [run] { run("Design_Export"); });
                    menu.addSeparator();
                    QObject::connect(menu.addAction(T("Rename")), &QAction::triggered, [tree, item] { tree->editItem(item); });
                    menu.addSeparator();
                    QObject::connect(menu.addAction(T("Close")), &QAction::triggered, [guiDoc] {
                        QTimer::singleShot(0, [guiDoc] {
                            Gui::Document* gdoc = guiDoc();
                            if (gdoc && gdoc->canClose(true, true)) {  // fragt bei Änderungen nach dem Speichern
                                App::GetApplication().closeDocument(gdoc->getDocument()->getName());
                            }
                        });
                    });
                    // Löschen: ohne Speichern schließen; eine gespeicherte Datei kommt in den Papierkorb (nicht endgültig weg)
                    QObject::connect(menu.addAction(T("Delete…")), &QAction::triggered, [guiDoc] {
                        QTimer::singleShot(0, [guiDoc] {
                            Gui::Document* gdoc = guiDoc();
                            if (!gdoc) {
                                return;
                            }
                            App::Document* doc = gdoc->getDocument();
                            const QString file = QString::fromUtf8(doc->FileName.getValue());
                            const QString label = QString::fromUtf8(doc->Label.getValue());
                            QMessageBox box(QMessageBox::Warning, T("Delete Design"),
                                            file.isEmpty() ? T("Delete “%1”? It has never been saved, so its contents will be gone.")
                                                                 .arg(label)
                                                           : T("Delete “%1”? The file is moved to the trash:\n%2")
                                                                 .arg(label, file),
                                            QMessageBox::Cancel, getMainWindow());
                            QPushButton* remove = box.addButton(T("Delete"), QMessageBox::DestructiveRole);
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
                showCommandMenu({{T("Show / Hide"), "Std_ToggleVisibility"},
                                 {QString(), "@rename"},
                                 {QString(), ""},
                                 {T("Move"), "Design_Move"},
                                 {T("Export"), "Design_Export"},
                                 {QString(), ""},
                                 {T("Delete"), "Design_Delete"}},
                                tree);
            });
            return true;
        }
        if (auto gv = qobject_cast<QGraphicsView*>(widget->parentWidget())) {
            auto me = static_cast<QMouseEvent*>(event);
            if (event->type() == QEvent::MouseButtonRelease && gv->itemAt(me->position().toPoint())) {
                return false;  // über einem Glass-Panel (Browser, Toolbar …): dessen eigenes Menü
            }
            if (event->type() == QEvent::MouseButtonPress && me->button() == Qt::RightButton) {
                pressPos = me->globalPosition().toPoint();
            }
            else if (event->type() == QEvent::MouseButtonRelease && me->button() == Qt::RightButton
                     && (me->globalPosition().toPoint() - pressPos).manhattanLength() < 5) {
                QTimer::singleShot(0, [] {
                    if (Control().activeDialog()) {
                        return;
                    }
                    showCommandMenu({{T("Undo"), "Std_Undo"},
                                     {T("Redo"), "Std_Redo"},
                                     {QString(), ""},
                                     {T("Create Sketch"), "Design_CreateSketch"},
                                     {T("Extrude"), "Design_Extrude"},
                                     {T("Press Pull"), "Design_PressPull"},
                                     {T("Fillet"), "Design_Fillet"},
                                     {T("Hole"), "Design_Hole"},
                                     {T("Move"), "Design_Move"},
                                     {QString(), ""},
                                     {T("Show / Hide"), "Std_ToggleVisibility"},
                                     {T("Delete"), "Design_Delete"},
                                     {QString(), ""},
                                     {T("Fit All"), "Std_ViewFitAll"}});
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
    lay->setContentsMargins(8, 14, 8, 14);  // wie die Seitenleisten: Zeilen 8 vom Rand (r 20 - 8 = r 12)
    lay->setSpacing(2);
    auto title = new QLabel(T("Sketch Palette"));
    setTextStyle(title, Text::Headline);
    title->setContentsMargins(10, 0, 0, 0);
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
        btn->setText(T(rows[i].first));
        btn->setIcon(designIcon(QString::fromLatin1(icons[i]), &Theme::labelSecondary));
        btn->setIconSize(QSize(Token::IconM, Token::IconM));
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
        btn->setText(T("Finish Sketch"));
        btn->setFixedHeight(Token::ControlDesktop);
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
    const qreal m = Token::WindowInset;
    GlassPanel* bar = state.sketchMode ? state.sketchBar : state.modelBar;
    state.modelBar->setVisible(!state.sketchMode);
    state.sketchBar->setVisible(state.sketchMode);
    const QSizeF bs = bar->content()->sizeHint();  // eine Reihe
    // Toolbar mittig zwischen Browser und Fensterknöpfen; reicht die Breite nicht, bricht sie in weitere Reihen um
    const bool browser = state.browser
        && !App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetBool("BrowserHidden", false);
    const qreal left = browser ? m + BrowserWidth + m : m;
    const qreal right = r.width() - m
        - (state.windowControls ? state.windowControls->content()->sizeHint().width() + m : 0);
    qreal barW = std::max<qreal>(100, std::min(bs.width(), right - left));
    const qreal barH = barW < bs.width() ? bar->content()->heightForWidth(int(barW)) : bs.height();
    if (barW < bs.width()) {  // Reihen ausgleichen: schmalste Breite mit gleich vielen Reihen
        int lo = 100, hi = int(barW);
        while (lo < hi) {
            const int mid = (lo + hi) / 2;
            if (bar->content()->heightForWidth(mid) <= barH) {
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        barW = hi;
    }
    bar->setGeometry(QRectF(left + (right - left - barW) / 2, m, barW, barH));
    // eine Reihe: Kapsel; umgebrochen wäre eine Kapsel zu rund für die Knöpfe in den Ecken, dann Panel-Radius
    bar->setRadius(barH > bs.height() ? Token::RadiusPanel : Token::RadiusCapsule);

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
        state.browser->setVisible(browser);
        state.browser->setGeometry(QRectF(m, top, BrowserWidth, bottom - top));
    }
    if (QToolButton* toggle = state.windowControls ? static_cast<WindowControls*>(state.windowControls->content())->sidebarButton : nullptr) {
        toggle->setToolTip(browser ? T("Hide sidebar") : T("Show sidebar"));
        toggle->setAccessibleName(toggle->toolTip());
    }
    qreal cubeTop = m;
    if (state.windowControls) {
        const QSizeF cs = state.windowControls->content()->sizeHint();
        state.windowControls->setGeometry(QRectF(r.width() - cs.width() - m, m, cs.width(), cs.height()));  // so flach wie die Knöpfe, wie auf Startseite und Hilfe
        cubeTop = m + cs.height() + m;
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

/// Browser (Seitenleiste links) ein-/ausklappen; der Zustand bleibt über Neustarts (MyCAD/BrowserHidden)
void toggleBrowser()
{
    auto grp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    grp->SetBool("BrowserHidden", !grp->GetBool("BrowserHidden", false));
    layout();
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
        auto play = [&](const char* icon, const QString& tip, std::function<int(int)> target) {
            auto btn = new QToolButton;
            btn->setObjectName(QStringLiteral("GlassButton"));
            btn->setIcon(designIcon(QString::fromLatin1(icon)));
            btn->setIconSize(QSize(Token::IconWindow, Token::IconWindow));
            btn->setFixedSize(Token::WindowButton, Token::WindowButton);
            btn->setToolTip(tip);
            btn->setAccessibleName(tip);
            QObject::connect(btn, &QToolButton::clicked, btn, [docName, target] {
                QTimer::singleShot(0, [docName, target] {
                    if (App::Document* d = App::GetApplication().getDocument(docName.c_str())) {
                        setTimelineMarker(d, target(timelineMarker(d)));
                    }
                });
            });
            lay->addWidget(btn);
        };
        play("Timeline_Start", T("Go to Start"), [](int) { return 0; });
        play("Timeline_Back", T("Step Back"), [total](int m) { return std::max(0, (m < 0 ? total : m) - 1); });
        play("Timeline_Forward", T("Step Forward"), [](int m) { return m < 0 ? -1 : m + 1; });
        play("Timeline_End", T("Go to End"), [](int) { return -1; });
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
        btn->setIconSize(QSize(Token::IconL, Token::IconL));
        btn->setFixedSize(Token::WindowButton, Token::WindowButton);
        btn->setToolTip(QString::fromUtf8(obj->Label.getValue())
                        + (obj->isError() ? QStringLiteral("\n") + T(obj->getStatusString())
                                          : QString()));
        btn->setAccessibleName(QString::fromUtf8(obj->Label.getValue()));
        btn->setProperty("error", obj->isError());
        if (obj->isError()) {  // Farbe nie allein (C-5): Fehler-Symbol in die Ecke
            QPixmap pm = btn->icon().pixmap(QSize(Token::IconL, Token::IconL), btn->devicePixelRatioF());
            QPainter p(&pm);
            designIcon(QStringLiteral("Badge_Error"), &Theme::red).paint(&p, QRect(9, 9, 11, 11));
            p.end();
            btn->setIcon(pm);
        }
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
            QAction* edit = menu.addAction(T("Edit"));
            QAction* rollback = timelineHolder(o->getDocument()) ? menu.addAction(T("Roll Back to Here")) : nullptr;
            QAction* suppress = nullptr;
            if (auto prop = freecad_cast<App::PropertyBool*>(o->getPropertyByName("Suppressed"))) {
                suppress = menu.addAction(prop->getValue() ? T("Unsuppress") : T("Suppress"));
            }
            menu.addSeparator();
            QAction* remove = menu.addAction(T("Delete"));
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

/// Bodenraster wie in Fusion: Linien auf der XY-Ebene, die beim Zoomen in Zehnerschritten (1, 10, 100 mm …) dichter
/// oder gröber werden und ganz schmal am Bildrand auslaufen. Ein Knoten für alle Ansichten (attach hängt ihn ein).
/// Der Shader legt ein Quadrat um den Punkt der Ebene in der Bildmitte, doppelt so groß wie das sichtbare Bild.
struct GroundGrid
{
    SoSwitch* node;
    SoShaderParameter4f* color;
};

GroundGrid& groundGrid()
{
    static GroundGrid g = [] {
        GroundGrid g {new SoSwitch, new SoShaderParameter4f};
        g.node->ref();
        g.color->name = "lineColor";

        auto vertex = new SoVertexShader;
        vertex->sourceType = SoShaderObject::GLSL_PROGRAM;
        vertex->sourceProgram = R"(
            #version 120
            varying vec2 world;   // Punkt auf der Ebene (mm)
            varying vec2 local;   // 1 = Bildrand (längere Seite), für das Auslaufen
            varying float facing; // 0 = Ebene von der Kante gesehen
            varying vec4 clip;    // Bildschirmposition, für das Auslaufen am Bildrand
            void main()
            {
                // Bildmitte auf der Ebene: Sehachse (0, 0, z) im Augenraum schneidet die Ebene z = 0
                vec3 n = gl_NormalMatrix * vec3(0.0, 0.0, 1.0);
                vec3 o = (gl_ModelViewMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
                float z = dot(n, o) / (abs(n.z) > 1e-3 ? n.z : 1e-3);
                float h = (gl_ProjectionMatrix[3][3] == 1.0 ? 1.0 : abs(z)) / gl_ProjectionMatrix[1][1];
                float r = h * max(1.0, gl_ProjectionMatrix[1][1] / gl_ProjectionMatrix[0][0]);
                vec2 center = (gl_ModelViewMatrixInverse * vec4(0.0, 0.0, z, 1.0)).xy;
                local = gl_Vertex.xy;
                world = center + local * r;
                facing = abs(n.z);
                gl_Position = gl_ModelViewProjectionMatrix * vec4(world, 0.0, 1.0);
                clip = gl_Position;
            }
        )";
        auto fragment = new SoFragmentShader;
        fragment->sourceType = SoShaderObject::GLSL_PROGRAM;
        fragment->sourceProgram = R"(
            #version 120
            uniform vec4 lineColor;
            varying vec2 world;
            varying vec2 local;
            varying float facing;
            varying vec4 clip;
            // Deckung einer Linienschar mit Abstand s: 1 px breit, geglättet
            float lines(float s, vec2 px)
            {
                vec2 d = abs(fract(world / s + 0.5) - 0.5) * s / px;
                return 1.0 - min(min(d.x, d.y), 1.0);
            }
            void main()
            {
                vec2 px = max(fwidth(world), vec2(1e-6));                  // mm je Pixel
                float lod = log(max(px.x, px.y) * 2.0) / log(10.0);        // Abstand, der 2 px wäre
                // Linien mit Abstand 10^k: ab 2 px blendet die feine Stufe ein (50 %), zehnmal gröber die Hauptlinie (100 %)
                float a = 0.0;
                for (int i = 1; i <= 3; ++i) {
                    float k = floor(lod) + float(i);
                    float strength = 0.5 * clamp(k - lod, 0.0, 1.0) + 0.5 * clamp(k - lod - 1.0, 0.0, 1.0);
                    a = max(a, strength * lines(pow(10.0, k), px));
                }
                // ganz schmal am Bildrand auslaufen (4 % je Seite), perspektivisch außerdem zum Horizont hin
                vec2 ndc = abs(clip.xy / clip.w);
                a *= smoothstep(0.0, 0.04, 1.0 - max(ndc.x, ndc.y));
                a *= (1.0 - smoothstep(1.0, 1.8, length(local))) * smoothstep(0.05, 0.25, facing);
                if (a < 0.004) {
                    discard;
                }
                gl_FragColor = vec4(lineColor.rgb, lineColor.a * a);
            }
        )";
        fragment->parameter.set1Value(0, g.color);
        auto program = new SoShaderProgram;
        program->shaderObject.set1Value(0, vertex);
        program->shaderObject.set1Value(1, fragment);

        // Ebenenteile vor oder hinter dem Bereich der Körper nicht abschneiden (Clipping richtet sich nach den Körpern)
        auto depthClamp = [](bool on) {
            auto cb = new SoCallback;
            cb->setCallback(
                [](void* on, SoAction* action) {
                    if (action->isOfType(SoGLRenderAction::getClassTypeId())) {
                        on ? glEnable(GL_DEPTH_CLAMP) : glDisable(GL_DEPTH_CLAMP);
                    }
                },
                on ? cb : nullptr);
            return cb;
        };
        auto pick = new SoPickStyle;
        pick->style = SoPickStyle::UNPICKABLE;
        auto blend = new SoTransparencyType;  // gleich in Reihenfolge zeichnen (nach den Körpern), nicht verzögert
        blend->value = SoTransparencyType::BLEND;
        auto material = new SoMaterial;
        material->transparency = 0.5F;  // schaltet Blending ein; die Deckkraft kommt aus dem Shader
        auto depth = new SoDepthBuffer;  // verdeckt nichts, Körper verdecken das Raster
        depth->write = FALSE;
        depth->function = SoDepthBuffer::LEQUAL;
        auto offset = new SoPolygonOffset;  // Skizzenprofile auf z = 0 liegen über dem Raster
        auto coords = new SoCoordinate3;
        coords->point.setValues(0, 4, std::array<SbVec3f, 4> {{{-2, -2, 0}, {2, -2, 0}, {2, 2, 0}, {-2, 2, 0}}}.data());
        auto sep = new SoSeparator;
        sep->renderCulling = SoSeparator::OFF;  // die echte Lage entsteht erst im Shader
        for (SoNode* n : std::initializer_list<SoNode*> {pick, blend, material, depth, offset, program, coords,
                                                         depthClamp(true), new SoFaceSet, depthClamp(false)}) {
            sep->addChild(n);
        }
        auto skip = new SoSkipBoundingGroup;  // Einpassen und Clipping richten sich nur nach den Körpern
        skip->mode = SoSkipBoundingGroup::EXCLUDE_BBOX;
        skip->addChild(sep);
        g.node->addChild(skip);
        return g;
    }();
    return g;
}

/// Raster an Einstellung (MyCAD/GroundGrid), Skizzenmodus (dort zeigt die Skizze ihr eigenes) und Theme anpassen
void updateGroundGrid()
{
    const bool on = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetBool("GroundGrid", true);
    const QColor c = theme().separator;  // MyStyle-Diagrammraster: separator, Hauptlinien voll, sonst 50 %
    groundGrid().color->value.setValue(c.redF(), c.greenF(), c.blueF(), c.alphaF());
    groundGrid().node->whichChild = on && !state.sketchMode ? 0 : SO_SWITCH_NONE;
}

void attach(View3DInventor* view)
{
    QGraphicsScene* scene = view->getViewer()->scene();
    if (scene == state.scene) {
        return;
    }
    auto root = static_cast<SoSeparator*>(view->getViewer()->getSceneGraph());
    if (root->findChild(groundGrid().node) < 0) {
        root->addChild(groundGrid().node);
    }
    updateGroundGrid();
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
    installTranslations();  // vor dem Aufbau der Oberfläche, damit alle Beschriftungen gleich deutsch sind
    applyTheme();           // Hell/Dunkel nach Einstellung (Automatic folgt dem System)
    // Automatic: Wechsel im System sofort übernehmen; Kontrast-Einstellung des Systems ebenso
    QObject::connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged, qApp, [] {
        const bool dark = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
        if (dark != theme().dark && App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")
                                            ->GetInt("Appearance", 0) == 0) {
            QTimer::singleShot(0, applyAppearance);
        }
    });
    // Fenster verliert den Fokus: Glas tritt zurück (MyStyle GM-4)
    QObject::connect(qApp, &QGuiApplication::applicationStateChanged, qApp, [] {
        if (state.scene) {
            state.scene->update();
        }
        getMainWindow()->update();
    });

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
        Token::RadiusCapsule);
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
        Token::RadiusCapsule);
    state.viewCube = new ViewCube;
    state.palette = new GlassPanel(sketchPalette(), Token::RadiusPanel, true);
    qApp->installEventFilter(new MenuPolisher);
    qApp->installEventFilter(new HelpKey);
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
        state.windowControls = new GlassPanel(new WindowControls(true, {}, toggleBrowser), Token::RadiusCapsule);
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
        state.timeline = new GlassPanel(box, Token::RadiusCapsule);
    }
    if (QWidget* tree = takeDockWindow("Std_ComboView")) {
        static ContextMenus* menus = new ContextMenus;
        for (auto t : tree->findChildren<QTreeWidget*>()) {
            t->viewport()->installEventFilter(menus);
        }
        state.browser = new GlassPanel(tree, Token::RadiusPanel, true);  // Text-Glas: bunter 3D-Inhalt läuft darunter
    }
    if (QWidget* tasks = takeDockWindow("Std_TaskView")) {
        state.inspector = new GlassPanel(tasks, Token::RadiusPanel, true);
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
        updateGroundGrid();
        hideChromeLater();
        QTimer::singleShot(0, layout);
    });
    Application::Instance->signalResetEdit.connect([](const ViewProviderDocumentObject&) {
        state.sketchMode = false;
        updateGroundGrid();
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
            // inzwischen mitgeschlossen (mehrere Designs auf einmal zu, z. B. beim Beenden): Szene ist schon weg
            if (view && getMainWindow()->windows().contains(view.data())) {
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

    // Startseite beim Start und nach dem Schließen des letzten Designs; ein neues oder geöffnetes Design blendet sie aus
    startPage = new StartPage;
    App::GetApplication().signalNewDocument.connect([](const App::Document& doc, bool) {
        if (!doc.testStatus(App::Document::TempDoc)) {
            QTimer::singleShot(0, [] { startPage->hide(); });
        }
    });
    App::GetApplication().signalDeletedDocument.connect([] {
        QTimer::singleShot(0, [] {
            if (!anyDesignOpen() && getMainWindow()->isVisible()) {
                showStartPage();
            }
        });
    });
    QTimer::singleShot(0, [] {
        if (!anyDesignOpen()) {
            showStartPage();
        }
    });
    // Projektordner anlegen; Öffnen-/Speichern-Dialoge starten dort, damit gespeicherte Designs auf der Startseite landen
    QDir().mkpath(projectsFolder());
    // keine .FCBak neben dem Design: FreeCAD schreibt erst in eine Temp-Datei und benennt dann um, ein Absturz beim
    // Speichern lässt die alte Datei also heil
    App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Document")->SetBool("CreateBackupFiles", false);
    App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
        ->SetASCII("FileOpenSavePath", projectsFolder().toUtf8().constData());
    auto recent = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/RecentFiles");
    if (recent->GetInt("RecentFiles", 4) < 16) {
        recent->SetInt("RecentFiles", 16);  // Platz für die Startseite
    }
}

QString Gui::Shell::projectsFolder()
{
    const QString fallback = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + QStringLiteral("/MyCAD");
    return QString::fromUtf8(App::GetApplication()
                                 .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")
                                 ->GetASCII("ProjectsFolder", fallback.toUtf8().constData())
                                 .c_str());
}

QString Gui::Shell::version()
{
    auto& cfg = App::Application::Config();
    return QString::fromStdString(cfg["BuildRevisionDate"]).left(10).replace(QLatin1Char('/'), QLatin1Char('.'))
        + QStringLiteral(" · ") + QString::fromStdString(cfg["BuildRevisionHash"]).left(7);
}

std::vector<const char*> Gui::Shell::bodyMaterialNames()
{
    std::vector<const char*> names;
    for (const auto& m : bodyMaterials) {
        names.push_back(m.name);
    }
    return names;
}

void Gui::Shell::setBodyMaterial(int index)
{
    App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->SetInt("BodyMaterial", index);
    setDefaultMaterial();
    const BodyMaterial& m = bodyMaterial();
    App::Material mat;
    mat.diffuseColor.setPackedValue(m.diffuse);
    mat.specularColor.setPackedValue(m.specular);
    mat.emissiveColor.setPackedValue(m.emissive);
    mat.ambientColor.setPackedValue(0x333333FF);
    mat.shininess = float(m.shininess) / 100.0F;
    mat.transparency = 0.0F;
    // Körper mit einem der Standard-Looks (auch früheren Vorgaben) umfärben, eigene Farben bleiben.
    // ponytail: erkennt "Standard" an der Grundfarbe; eine eigene Farbe, die zufällig gleich ist, wird mit umgefärbt
    std::set<uint32_t> presets = {0xCDD1D8, 0xA4A9B2, 0xD5D9DF, 0xAEB3BC, 0xC8CCD4, 0x9EA3AD, 0xCCCCCC};
    for (const auto& b : bodyMaterials) {
        presets.insert(b.diffuse >> 8);
    }
    const Base::Type body = Base::Type::fromName("Design::Body");
    for (auto doc : App::GetApplication().getDocuments()) {
        for (auto obj : doc->getObjects()) {
            auto vp = dynamic_cast<Gui::ViewProviderGeometryObject*>(Gui::Application::Instance->getViewProvider(obj));
            if (!vp || !obj->isDerivedFrom(body) || !presets.contains(vp->ShapeAppearance.getDiffuseColor().getPackedValue() >> 8)) {
                continue;
            }
            vp->ShapeAppearance.setValue(mat);
            if (auto line = dynamic_cast<App::PropertyColor*>(vp->getPropertyByName("LineColor"))) {
                line->setValue(Base::Color(m.line));
            }
        }
    }
}

void Gui::Shell::applyAppearance()
{
    applyTheme();
    // Baum: Icons aus dem BitmapFactory-Cache neu holen
    for (App::Document* doc : App::GetApplication().getDocuments()) {
        if (Gui::Document* gdoc = Application::Instance->getDocument(doc)) {
            for (App::DocumentObject* obj : doc->getObjects()) {
                if (auto vp = dynamic_cast<ViewProviderDocumentObject*>(gdoc->getViewProvider(obj))) {
                    vp->signalChangeIcon();
                }
            }
        }
    }
    rebuildTimeline();  // Fehler-Symbole und blasse Einträge sind fertige Bilder
    updateGroundGrid();
    if (startPage && startPage->isVisible()) {
        startPage->open();  // Vorschaubilder neu
    }
    if (helpPage) {
        helpPage->refresh();
    }
    if (state.scene) {
        state.scene->update();
    }
    for (QWidget* w : QApplication::allWidgets()) {  // Icons und selbst gezeichnete Flächen lesen die Farben beim Zeichnen
        w->update();
    }
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
            sep->setFixedSize(9, on ? 44 : 28);
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
