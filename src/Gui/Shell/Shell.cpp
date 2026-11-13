// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Shell.h"
#include "CommandSearch.h"
#include "GlassPanel.h"
#include "ViewCube.h"
#include "Settings.h"
#include "Theme.h"

#include <App/Application.h>
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Gui/Action.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/TaskView/TaskView.h>
#include <Gui/Document.h>
#include <Gui/Selection/Selection.h>
#include <Gui/ViewProviderDocumentObject.h>
#include <string_view>
#include <Gui/ViewProviderGeometryObject.h>
#include <App/Document.h>
#include <App/ExpressionParser.h>
#include <App/PropertyStandard.h>
#include <App/VarSet.h>
#include <Gui/DockWindowManager.h>
#include <Gui/MainWindow.h>
#include <Gui/Tree.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <Gui/Inventor/SoFCBoundingBox.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Gui/SoFCOffscreenRenderer.h>
#include "BodyShading.h"
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
#include <QDoubleSpinBox>
#include <QDockWidget>
#include <QFontDatabase>
#include <QFrame>
#include <QGraphicsRectItem>
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
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QTextCursor>
#include <QMovie>
#include <QTextDocument>
#include <QTextFrame>
#include <QTreeWidget>
#include <QSizePolicy>
#include <QLabel>
#include <QWindow>
#include <QPixmapCache>
#include <QSurfaceFormat>
#include <QMenuBar>
#include <QDir>
#include <QFile>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QImageReader>
#include <QPainter>
#include <QPainterPath>
#include <QSvgRenderer>
#include <QtMath>
#include <tuple>
#include <QInputDialog>
#include <sstream>
#include <QListWidget>
#include <QPointer>
#include <QStatusBar>
#include <QRegularExpression>
#include <QScreen>
#include <QStyleHints>
#include <QTimer>
#include <QThread>
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

void addVariantMenu(QMenu* menu, App::Document* doc, const std::function<void(const char*)>& run);

namespace
{

/// Hinweis unter dem ViewCube statt Meldungsfenster (wie toolHint() in Design/Gui/Commands.cpp)
void shellHint(const QString& tool, const QString& text)
{
    Base::Console().send<Base::LogStyle::Notification, Base::IntendedRecipient::User, Base::ContentType::Translated>(
        "MyCAD", "{}", (tool + QStringLiteral(": ") + text).toStdString());
}

/// Breite von Browser und Seitenleisten. MyStyle-Abweichung von size.sidebarWidth (232): der Modellbaum braucht wie
/// Fusions Browser Platz für Namen, Sichtbarkeits-Auge und Status-Symbole
constexpr qreal BrowserWidth = 290;
constexpr qreal SearchWidth = 420;  ///< Suchfeld-Kapsel in der Titelzeile von Startseite und Hilfe

std::function<bool(const QString&)> scribbleFind;  ///< Gui::Shell::setScribbleFind
QLineEdit* scribbleFindField = nullptr;            ///< Suchfeld in der Scribble-Palette

void overrideFreeCadIcons();

/// Das Stylesheet der ganzen App; "@token" steht für die Farbe aus dem aktuellen Theme (MyStyle § 9).
/// Schriftgrößen setzt setTextStyle(), nicht das Stylesheet (Qt-Stylesheets kennen keine Laufweite).
QString styleSheet()
{
    const QString s = QStringLiteral(R"(
* { color: @labelPrimary; }
#GlassContent, #GlassContent QWidget { background: transparent; }
/* Aufgeklappte Auswahlliste ist ein eigenes Fenster: deckend wie im Einstellungsfenster, sonst zeigt sie Schwarz */
QComboBoxPrivateContainer, #GlassContent QComboBoxPrivateContainer { background: @glassOpaqueTop; }
QComboBox QAbstractItemView, #GlassContent QComboBox QAbstractItemView { background: @glassOpaqueTop; border: 1px solid @glassPopupBorder; padding: 4px; outline: 0;
    selection-background-color: @accent; selection-color: @labelOnAccent; }
QToolTip { background: @glassOpaqueTop; color: @labelPrimary; border: 1px solid @glassPopupBorder; border-radius: 8px; padding: 4px 8px; }

/* Icon-Buttons in Glas-Bars: rund, Hover fill.tertiary, gedrückt fill.secondary, Tastaturfokus 2-px-Ring */
QToolButton#GlassButton, QToolButton#WindowClose { border: 2px solid transparent; border-radius: 18px; background: transparent; }
QToolButton#GlassButton:hover { background: @fillTertiary; }
QToolButton#GlassButton:pressed, QToolButton#GlassButton:checked { background: @fillSecondary; }
QToolButton#GlassButton:focus, QToolButton#WindowClose:focus, QToolButton#PaletteRow:focus { border-color: @focusRing; }
QToolButton#GlassButton:disabled { background: transparent; }
QToolButton#GlassButton[names="true"] { border-radius: 12px; padding-top: 2px; }
QToolButton#GlassButton[names="true"]::menu-arrow { subcontrol-position: bottom center; bottom: 11px; }
QToolButton#GlassButton[popupMode="1"] { padding-right: 14px; }
QToolButton#GlassButton::menu-button { border: none; width: 14px; }
/* Pfeil für das Menü am Knopf: kräftig genug, um ihn zu sehen und zu treffen (vorher 9 px, Linie 1 px) */
QToolButton#GlassButton::menu-arrow { image: url(:/mycad/icons/Menu_Chevron.svg); width: 14px; height: 14px; }
QToolButton#GlassButton[error="true"] { background: @errorFill; }
QToolButton#WindowClose:hover { background: @red; }
QToolButton#WindowClose:pressed { background: @redPressed; }
/* Schließen-Knopf der Post-its wie beim Hinweis-Popup (MyStyle § 9.4): 28 rund, fill.tertiary */
QToolButton#NoteClose { border: 2px solid transparent; border-radius: 14px; background: @noteFillTertiary; }
QToolButton#NoteClose:hover { background: @noteFillSecondary; }
QLabel#NoteTitle { color: @noteLabel; }
QPlainTextEdit#NoteText QScrollBar::handle { background: @noteScrollbar; }
QToolButton#NoteClose:focus { border-color: @focusRing; }

/* Prominent-Button (Akzentfläche): Kapsel 30 hoch, 16 seitlich, Callout SemiBold, Hover 1 px Weiß 35 %, gedrückt 15 % dunkler */
QToolButton#GlassProminent, QPushButton#Prominent { border: 1px solid transparent; border-radius: 15px; background: @accent; color: @labelOnAccent;
    font-weight: 600; padding: 0 15px; min-height: 28px; }
QToolButton#GlassProminent:hover, QPushButton#Prominent:hover { border-color: @hoverRim; }
QToolButton#GlassProminent:pressed, QPushButton#Prominent:pressed { background: @accentPressed; }
QToolButton#GlassProminent:focus, QPushButton#Prominent:focus { border: 2px solid @focusRing; padding: 0 14px; }

QFrame#TimelineMarker { background: @accent; border-radius: 2px; }
/* Befehlssuche (MyStyle 9.1/9.3): Feld fill.tertiary r 8 mit Fokusring, Treffer wie Seitenleisten-Zeilen */
QWidget#CommandSearch QLineEdit { background: @fillTertiary; border: 2px solid transparent; border-radius: 8px; min-height: 26px; padding: 0 8px; }
QWidget#CommandSearch QLineEdit:focus { border-color: @focusRing; }
QWidget#CommandSearch QListWidget { background: transparent; border: none; outline: 0; }
QWidget#CommandSearch QListWidget::item { border-radius: 8px; padding: 4px 8px; min-height: 26px; color: @labelPrimary; }
QWidget#CommandSearch QListWidget::item:hover { background: @fillTertiary; }
QWidget#CommandSearch QListWidget::item:selected { background: @fillSecondary; color: @labelPrimary; }
/* Seitenleisten-Zeilen: r 12, Hover fill.tertiary, aktiv fill.secondary + SemiBold */
QToolButton#PaletteRow { border: 2px solid transparent; border-radius: 12px; padding: 0 8px; text-align: left; background: transparent; }
QToolButton#PaletteRow:hover { background: @fillTertiary; }
QToolButton#PaletteRow:checked { background: @fillSecondary; font-weight: 600; color: @accentText; }
QFrame#GlassSeparator, QFrame#ToolbarSeparator { background: @separator; border: none; }
QFrame#ToolbarSeparator { margin: 4px; }
QLabel#Section, QLabel#Secondary, QLabel#StartDate, QLabel#StartCaption, QLabel#Hint { color: @labelSecondary; }

#GlassContent QAbstractScrollArea { border: none; }
/* Textfelder (MyStyle 9.3): 30 hoch, r 8, fill.tertiary, 10 seitlich, Fokus 2-px-Ring. Bewusst für jedes Feld der App,
   damit keins in Qts Standard-Optik bleibt (Dialoge, Maßkarte …); die #GlassContent-Varianten schlagen dort
   "background: transparent". Eigene Optik (Suchen, Post-it) über spezifischere Regeln. Prüft tests/gui/harness.py */
QLineEdit, QAbstractSpinBox, QComboBox, #GlassContent QLineEdit, #GlassContent QAbstractSpinBox, #GlassContent QComboBox {
    background: @fillTertiary; border: 2px solid transparent; border-radius: 8px; padding: 2px 8px; min-height: 22px;
}
/* MyStyle-Abweichung: Auswahlfelder in FreeCADs Werkzeug-Formularen als Feld (fill.tertiary) statt randlos,
   weil dort kein Zeilenlabel links steht, an dem man den Pop-up-Button erkennt */
QComboBox:hover, #GlassContent QComboBox:hover { background: @fillSecondary; }
QLineEdit:focus, QAbstractSpinBox:focus, QComboBox:focus,
#GlassContent QLineEdit:focus, #GlassContent QAbstractSpinBox:focus, #GlassContent QComboBox:focus { border-color: @focusRing; }
/* Post-it: ohne Rahmen, auch mit Fokus (ausdrücklicher Wunsch; den Fokus zeigt die Einfügemarke) */
#GlassContent QPlainTextEdit#NoteText { background: transparent; border: none; color: @noteLabel; placeholder-text-color: @noteLabelTertiary;
    selection-background-color: @accent; selection-color: @labelOnAccent; }
/* subcontrol-origin: sonst schrumpft bei Feldern ohne Knöpfe (NoButtons, z. B. die Wertfelder in der Skizze) das
   Eingabefeld auf 1 px, sobald das Feld Rand oder Innenabstand hat: der Text ist unsichtbar */
QAbstractSpinBox::up-button, QAbstractSpinBox::down-button { width: 0; border: none; subcontrol-origin: border; }
QComboBox::drop-down { border: none; width: 24px; }
/* Pop-up-Button (MyStyle): Auf/Ab-Chevrons 16 */
QComboBox::down-arrow { image: url(:/mycad/icons/Chevrons_UpDown.svg); width: 16px; height: 16px; }
QLineEdit { selection-background-color: @accent; selection-color: @labelOnAccent; }

/* Standard-Buttons: Kapsel, fill.tertiary, gedrückt fill.secondary, Hover 1 px Weiß 35 %; Standard-Aktion = Akzent */
#GlassContent QPushButton, [glassPanel="true"] QPushButton, QDialog QPushButton, QMessageBox QPushButton {
    background: @fillTertiary; border: 1px solid transparent; border-radius: 15px; min-height: 28px; padding: 0 15px; font-weight: 600;
}
#GlassContent QPushButton:hover, [glassPanel="true"] QPushButton:hover, QDialog QPushButton:hover, QMessageBox QPushButton:hover { border-color: @hoverRim; }
#GlassContent QPushButton:pressed, [glassPanel="true"] QPushButton:pressed, QDialog QPushButton:pressed, QMessageBox QPushButton:pressed { background: @fillSecondary; }
#GlassContent QPushButton:focus, [glassPanel="true"] QPushButton:focus, QDialog QPushButton:focus, QMessageBox QPushButton:focus { border: 2px solid @focusRing; padding: 0 14px; }
#GlassContent QPushButton:default, [glassPanel="true"] QPushButton:default, QDialog QPushButton:default, QMessageBox QPushButton:default { background: @accent; color: @labelOnAccent; }
#GlassContent QPushButton:default:pressed, [glassPanel="true"] QPushButton:default:pressed, QDialog QPushButton:default:pressed, QMessageBox QPushButton:default:pressed { background: @accentPressed; }
#GlassContent QPushButton:disabled, [glassPanel="true"] QPushButton:disabled, QDialog QPushButton:disabled { color: @labelTertiary; }

/* Auswahl nur auf der Zeile selbst, nicht auch auf der Einrückung links davon */
#GlassContent QTreeView { show-decoration-selected: 0; }
#GlassContent QTreeView::item { min-height: 28px; border-radius: 8px; }
#GlassContent QTreeView::item:hover { background: @fillTertiary; }
#GlassContent QTreeView::item:selected { background: @accent; color: @labelOnAccent; }
#GlassContent QTreeView::branch:selected, #GlassContent QTreeView::branch:hover { background: transparent; }
/* Pfeile als Bild: hat eine ::branch-Regel nur einen Hintergrund (oben), zeichnet Qt den Pfeil nicht, er verschwand
   bei Auswahl und Hover */
#GlassContent QTreeView::branch:has-children:closed { image: url(:/mycad/icons/Tree_Closed.svg); }
#GlassContent QTreeView::branch:has-children:open { image: url(:/mycad/icons/Tree_Open.svg); }
/* Seit Qt 6.5 färbt ::item auch die Einrückung links der Zeile. Die Zeile selbst zeichnet der Browser über ein
   unsichtbares zweites QTreeView (siehe TreeWidgetItemDelegate), der Browser selbst bleibt deshalb ohne Hintergrund. */
#GlassContent Gui--TreeWidget::item:selected, #GlassContent Gui--TreeWidget::item:hover { background: transparent; }
#GlassContent QHeaderView::section { background: transparent; border: none; color: @labelSecondary; font-weight: 600; padding: 4px 8px; }
#GlassContent QTabWidget::pane { border: none; }
#GlassContent QTabBar::tab { background: transparent; border: none; border-radius: 8px; padding: 4px 12px; margin: 2px; color: @labelSecondary; }
#GlassContent QTabBar::tab:selected { background: @fillSecondary; color: @labelPrimary; }
#GlassContent QSplitter::handle { background: @separator; height: 1px; }
/* Listen und Tabellen in Dialogen (Inhalt L1 in der Glas-Karte): Material mit 1-px-Kante, Zeilen wie im Browser.
   Aufgeklappte Auswahllisten liegen auch im Dialog, behalten aber ihre Popup-Optik */
QDialog[glass="true"] QAbstractItemView { background: @materialFill; border: 1px solid @materialBorder; border-radius: 12px;
    padding: 4px; outline: 0; gridline-color: @separator; }
QDialog[glass="true"] QAbstractItemView::item { min-height: 28px; border-radius: 8px; padding: 0 6px; }
QDialog[glass="true"] QAbstractItemView::item:hover { background: @fillTertiary; }
QDialog[glass="true"] QAbstractItemView::item:selected { background: @accent; color: @labelOnAccent; }
QDialog[glass="true"] QComboBox QAbstractItemView { background: @glassOpaqueTop; border: 1px solid @glassPopupBorder; border-radius: 0; }
/* einfache Liste statt Menü-Popup: dessen Scroll-Leisten oben und unten zeichnete Qt schwarz (Drucken: welcher Slicer?) */
QDialog[glass="true"] QComboBox { combobox-popup: 0; }
QDialog[glass="true"] QComboBoxPrivateContainer { background: @glassOpaqueTop; border: none; }
QDialog[glass="true"] QHeaderView, QDialog[glass="true"] QTableCornerButton::section { background: transparent; border: none; }
QDialog[glass="true"] QHeaderView::section { background: transparent; border: none; color: @labelSecondary; font-weight: 600; padding: 4px 8px; }

/* Scrollbar: Overlay-Kapsel ohne Spur, 6 breit, beim Überfahren 9 */
QScrollBar:vertical { background: transparent; width: 9px; margin: 2px 0; }
QScrollBar:horizontal { background: transparent; height: 9px; margin: 0 2px; }
QScrollBar::handle { background: @scrollbar; border-radius: 3px; min-height: 24px; min-width: 24px; }
QScrollBar::handle:vertical { margin: 0 1px 0 2px; }
QScrollBar::handle:horizontal { margin: 2px 0 1px 0; }
QScrollBar::handle:hover { margin: 0; border-radius: 4px; }
QScrollBar::add-line, QScrollBar::sub-line { width: 0; height: 0; }
QScrollBar::add-page, QScrollBar::sub-page { background: transparent; }
/* Abbrechen links, Standard rechts (MyStyle Alert), auch unter KDE, das es umgekehrt ordnet */
QDialogButtonBox { dialogbuttonbox-buttons-have-icons: 0; button-layout: 1; }

/* Menüs: Text-Glas als Frost (eigenes Fenster ohne Blur), r 12, Innenabstand 4, Einträge 30 hoch r 8 */
QMenu { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 @glassOpaqueTop, stop:1 @glassOpaqueBottom);
    border: 1px solid @glassPopupBorder; border-radius: 12px; padding: 4px; }
QMenu::item { padding: 6px 24px 6px 12px; border-radius: 8px; }
QMenu::item:selected { background: @accent; color: @labelOnAccent; }
QMenu::item:disabled { color: @labelTertiary; }
QMenu::separator { height: 1px; background: @separator; margin: 4px 8px; }
QMenu::icon { padding-left: 8px; }
QMenu::right-arrow { image: url(:/mycad/icons/Chevron_Right.svg); width: 14px; height: 14px; margin-right: 6px; }
QMenu::right-arrow:selected { image: url(:/mycad/icons/Chevron_Right_OnAccent.svg); }
QMessageBox, QDialog { background: @glassOpaqueTop; }
QMessageBox[glass="true"], QDialog[glass="true"] { background: transparent; }
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

/// Aussehen der Körper (Einstellung "Body material", Panel "Aussehen"), Farben als 0xRRGGBBAA
struct BodyMaterial
{
    const char* name;
    const char* category;  ///< Gruppe im Panel, englisch wie name
    uint32_t diffuse, specular, emissive, line;
    int shininess;
    const char* texture = nullptr;  ///< diffuse ist dann die mittlere Bildfarbe, für Exporte und als Rückfall
    int transparency = 0;           ///< Prozent
    const char* family = nullptr;   ///< Varianten einer Oberfläche (Farben, Finish) stehen als Chips unter einer Kugel
};

/// Leuchtfarbe = Markierung für das PBR-Material (BodyShading.h): Grün die Bits unten, Blau 1/255 kein Metall,
/// 2/255 Metall. Unsichtbar, steht in jeder Datei und bleibt FreeCAD-kompatibel. Rauheit = 1 - Glanz.
enum Finish : uint32_t
{
    Plain = 0,
    Coat = 1,     ///< Klarlack über dem Material
    Brushed = 2,  ///< Schliff entlang x
    Grain = 4,    ///< Holz: Hirnholz an den x-Seiten
    Layers = 8,   ///< 3D-Druck: Schichten entlang z
};

constexpr uint32_t scaled(uint32_t rgba, int percent)
{
    uint32_t out = 0xFF;
    for (int shift : {8, 16, 24}) {
        out |= std::min(0xFFU, ((rgba >> shift) & 0xFF) * percent / 100) << shift;
    }
    return out;
}

constexpr uint32_t gray(int v)
{
    return uint32_t(v) * 0x01010100U | 0xFF;
}

/// Metall: Glanzlicht in der eigenen Farbe (Phong bei Qualität "Sparsam"), Kanten dunkler
constexpr BodyMaterial metal(const char* name, const char* category, uint32_t diffuse, int shininess, uint32_t finish = Plain,
                             const char* family = nullptr, const char* texture = nullptr)
{
    return {name, category, diffuse, scaled(diffuse, 70), finish << 16 | 0x2FF, scaled(diffuse, 45), shininess, texture, 0, family};
}

/// Nichtmetall: Glanzlicht grau, heller je glatter
constexpr BodyMaterial dielectric(const char* name, const char* category, uint32_t diffuse, int shininess,
                                  uint32_t finish = Plain, const char* family = nullptr, const char* texture = nullptr,
                                  int transparency = 0)
{
    return {name, category, diffuse, gray(20 + shininess), finish << 16 | 0x1FF, scaled(diffuse, 45), shininess, texture,
            transparency, family};
}

constexpr BodyMaterial bodyMaterials[] = {
    // Die ersten zwölf: Apple-Farben (Metall, Ton, Keramik)
    {"Space Gray", "Colors", 0x5C6169FF, 0x737373FF, 0x000002FF, 0x1F1F24FF, 55},
    {"Clay", "Colors", 0xE8DED1FF, 0x1A1A1AFF, 0x000001FF, 0x73665CFF, 10},
    {"Sierra Blue", "Colors", 0x9EBDDBFF, 0x59595FFF, 0x000002FF, 0x384D66FF, 45},
    {"Ceramic", "Colors", 0xF2F2F5FF, 0x999999FF, 0x000001FF, 0x8C8F99FF, 75},
    // weitere Apple-Oberflächen, je etwas heller als das Original, damit die Schattierung lesbar bleibt
    {"Midnight", "Colors", 0x3A4250FF, 0x5E6066FF, 0x000002FF, 0x15181FFF, 50},
    {"Alpine Green", "Colors", 0x5F705DFF, 0x5E625EFF, 0x000002FF, 0x2A3329FF, 50},
    {"Deep Purple", "Colors", 0x6A5E78FF, 0x66626BFF, 0x000002FF, 0x2E2735FF, 50},
    {"Natural Titanium", "Colors", 0xB8B2A7FF, 0x8C8A86FF, 0x000002FF, 0x5C5850FF, 70},
    // Neue Materialien nur anhängen: Der Index steht in den Einstellungen des Benutzers
    {"Silver", "Colors", 0xD5D6D8FF, 0x8C8C8CFF, 0x000002FF, 0x6B6D72FF, 70},
    {"Graphite", "Colors", 0x47484DFF, 0x66666BFF, 0x000002FF, 0x1A1A1DFF, 55},
    {"Rose Gold", "Colors", 0xD8B0A2FF, 0x8C7D78FF, 0x000002FF, 0x7A5C52FF, 70},
    {"Matte Black", "Colors", 0x2C2D30FF, 0x2B2B2BFF, 0x000001FF, 0x0D0D0EFF, 15},
    // Fotoscans aus tools/fetch_textures.py (CC0), diffuse = mittlere Bildfarbe
    {"Oak", "Wood", 0xA17E57FF, 0x262626FF, 0x000401FF, 0x5C4325FF, 20, ":/mycad/textures/oak.jpg", 0, "Oak"},
    {"Walnut", "Wood", 0x5E412BFF, 0x262626FF, 0x000401FF, 0x241710FF, 25, ":/mycad/textures/walnut.jpg", 0, "Walnut"},
    {"Maple", "Wood", 0xE3D4B9FF, 0x262626FF, 0x000401FF, 0x8A7350FF, 20, ":/mycad/textures/maple.jpg", 0, "Maple"},
    {"Cherry", "Wood", 0xAE6745FF, 0x262626FF, 0x000401FF, 0x552D18FF, 25, ":/mycad/textures/cherry.jpg"},
    {"Pine", "Wood", 0xD2AE78FF, 0x1A1A1AFF, 0x000401FF, 0x7D5D2EFF, 15, ":/mycad/textures/pine.jpg"},
    {"Bamboo", "Wood", 0xD2AD80FF, 0x262626FF, 0x000401FF, 0x7F6A3FFF, 25, ":/mycad/textures/bamboo.jpg"},
    {"Brushed Aluminum", "Metal", 0xC5C9CEFF, 0x8C8C8CFF, 0x000202FF, 0x62656AFF, 60, ":/mycad/textures/brushed_aluminum.jpg"},
    {"Brushed Steel", "Metal", 0x9DA1A7FF, 0x8C8C8CFF, 0x000202FF, 0x3A3C40FF, 60, ":/mycad/textures/brushed_steel.jpg"},
    {"Carbon Fiber", "Composites", 0x2F2E31FF, 0x737373FF, 0x000101FF, 0x0D0D0DFF, 70, ":/mycad/textures/carbon.jpg", 0, "Carbon Fiber"},
    {"Concrete", "Stone", 0x9E9C91FF, 0x141414FF, 0x000001FF, 0x4D4C49FF, 10, ":/mycad/textures/concrete.jpg"},
    {"Marble", "Stone", 0xACADB6FF, 0x808080FF, 0x000101FF, 0x7D7B78FF, 80, ":/mycad/textures/marble.jpg"},
    {"Granite", "Stone", 0xB5B1ADFF, 0x4D4D4DFF, 0x000001FF, 0x3D3937FF, 60, ":/mycad/textures/granite.jpg"},
    {"Leather", "Fabric & Leather", 0x512D10FF, 0x262626FF, 0x000001FF, 0x2A180EFF, 35, ":/mycad/textures/leather.jpg"},
    {"Cork", "Fabric & Leather", 0xAF8265FF, 0x141414FF, 0x000001FF, 0x523D28FF, 5, ":/mycad/textures/cork.jpg"},

    // Metalle roh und veredelt: Farbe = Spiegelung (gemessene Werte, leicht abgedunkelt)
    metal("Aluminum", "Metal", 0xD2D4D6FF, 55),
    metal("Polished Aluminum", "Metal", 0xE8EAECFF, 95),
    metal("Stainless Steel", "Metal", 0xC4C6C8FF, 92),
    metal("Steel", "Metal", 0x8F9296FF, 60),
    metal("Blackened Steel", "Metal", 0x3A3B3EFF, 55),
    metal("Cast Iron", "Metal", 0x5A5B5DFF, 30),
    metal("Galvanized Steel", "Metal", 0xB8BCC0FF, 50),
    metal("Chrome", "Metal", 0xDCDEE0FF, 98),
    metal("Titanium", "Metal", 0xC1BAB1FF, 70),
    metal("Brass", "Metal", 0xE6CB8AFF, 85, Plain, "Brass"),
    metal("Brushed Brass", "Metal", 0xE6CB8AFF, 70, Brushed, "Brass"),
    metal("Copper", "Metal", 0xE8A888FF, 85, Plain, "Copper"),
    metal("Brushed Copper", "Metal", 0xE8A888FF, 70, Brushed, "Copper"),
    metal("Bronze", "Metal", 0xC09464FF, 70),
    metal("Gold", "Metal", 0xF2CC7AFF, 92),
    metal("Sterling Silver", "Metal", 0xEDEBE6FF, 92),
    // Eloxiertes Aluminium: gefärbte Oxidschicht, darunter glänzt das Metall
    metal("Anodized Silver", "Anodized", 0xC9CCD0FF, 62, Plain, "Anodized"),
    metal("Anodized Black", "Anodized", 0x2E2F33FF, 62, Plain, "Anodized"),
    metal("Anodized Titanium", "Anodized", 0x7D8188FF, 62, Plain, "Anodized"),
    metal("Anodized Blue", "Anodized", 0x3F6FB0FF, 62, Plain, "Anodized"),
    metal("Anodized Red", "Anodized", 0xB03A3AFF, 62, Plain, "Anodized"),
    metal("Anodized Gold", "Anodized", 0xC9A24FFF, 62, Plain, "Anodized"),
    metal("Anodized Green", "Anodized", 0x4E8A5AFF, 62, Plain, "Anodized"),
    metal("Anodized Purple", "Anodized", 0x6E4F9AFF, 62, Plain, "Anodized"),
    metal("Anodized Orange", "Anodized", 0xD07A35FF, 62, Plain, "Anodized"),
    // Pulverbeschichtet: matt-satiniert, deckend (RAL-Töne)
    dielectric("Powder Coat Black", "Coatings", 0x232427FF, 45, Plain, "Powder Coat"),
    dielectric("Powder Coat Anthracite", "Coatings", 0x383E42FF, 45, Plain, "Powder Coat"),
    dielectric("Powder Coat White", "Coatings", 0xEDEDEAFF, 45, Plain, "Powder Coat"),
    dielectric("Powder Coat Red", "Coatings", 0xC1121CFF, 45, Plain, "Powder Coat"),
    dielectric("Powder Coat Yellow", "Coatings", 0xF0CA00FF, 45, Plain, "Powder Coat"),
    dielectric("Powder Coat Blue", "Coatings", 0x2271B3FF, 45, Plain, "Powder Coat"),
    dielectric("Powder Coat Green", "Coatings", 0x57A639FF, 45, Plain, "Powder Coat"),
    // Lacke: Farbe unter Klarlack; Metallic mit Metallflocken
    dielectric("Piano Black", "Coatings", 0x0E0F11FF, 70, Coat, "Lacquer"),
    dielectric("Lacquer White", "Coatings", 0xF2F2F0FF, 70, Coat, "Lacquer"),
    dielectric("Lacquer Red", "Coatings", 0xB0161EFF, 70, Coat, "Lacquer"),
    dielectric("Lacquer Blue", "Coatings", 0x1F4E9AFF, 70, Coat, "Lacquer"),
    metal("Metallic Silver", "Coatings", 0xB8BCC2FF, 50, Coat, "Metallic Paint"),
    metal("Metallic Graphite", "Coatings", 0x4A4D52FF, 50, Coat, "Metallic Paint"),
    metal("Metallic Blue", "Coatings", 0x2A4F8FFF, 50, Coat, "Metallic Paint"),
    metal("Metallic Red", "Coatings", 0x8E1B1BFF, 50, Coat, "Metallic Paint"),
    // Kunststoffe: matt, satiniert, glänzend
    dielectric("Plastic Matte White", "Plastic", 0xEFEFECFF, 25, Plain, "Plastic Matte"),
    dielectric("Plastic Matte Gray", "Plastic", 0x8E9095FF, 25, Plain, "Plastic Matte"),
    dielectric("Plastic Matte Black", "Plastic", 0x26272AFF, 25, Plain, "Plastic Matte"),
    dielectric("Plastic Satin White", "Plastic", 0xEFEFECFF, 55, Plain, "Plastic Satin"),
    dielectric("Plastic Satin Gray", "Plastic", 0x8E9095FF, 55, Plain, "Plastic Satin"),
    dielectric("Plastic Satin Black", "Plastic", 0x26272AFF, 55, Plain, "Plastic Satin"),
    dielectric("Plastic Glossy White", "Plastic", 0xF2F2EFFF, 88, Plain, "Plastic Glossy"),
    dielectric("Plastic Glossy Black", "Plastic", 0x1C1D20FF, 88, Plain, "Plastic Glossy"),
    dielectric("Plastic Glossy Red", "Plastic", 0xC8302CFF, 88, Plain, "Plastic Glossy"),
    dielectric("Plastic Glossy Blue", "Plastic", 0x2F6DC8FF, 88, Plain, "Plastic Glossy"),
    dielectric("Plastic Glossy Yellow", "Plastic", 0xF2C230FF, 88, Plain, "Plastic Glossy"),
    // 3D-Druck: FDM mit Schichtlinien, SLA glatt, SLS körnig matt
    dielectric("PLA White", "3D Print", 0xF0EFEAFF, 35, Layers, "PLA"),
    dielectric("PLA Gray", "3D Print", 0x9A9C9FFF, 35, Layers, "PLA"),
    dielectric("PLA Black", "3D Print", 0x2A2B2EFF, 35, Layers, "PLA"),
    dielectric("PLA Orange", "3D Print", 0xF07A1EFF, 35, Layers, "PLA"),
    dielectric("PLA Blue", "3D Print", 0x2C6FD1FF, 35, Layers, "PLA"),
    dielectric("PETG Clear", "3D Print", 0xE8F0F0FF, 80, Layers, nullptr, nullptr, 60),
    dielectric("Resin Gray", "3D Print", 0x8C8E91FF, 60),
    dielectric("Nylon SLS", "3D Print", 0xE6E3DAFF, 8),
    // Gummi und Silikon
    dielectric("Rubber Black", "Rubber", 0x1F2022FF, 15, Plain, "Rubber"),
    dielectric("Rubber Gray", "Rubber", 0x5A5C60FF, 15, Plain, "Rubber"),
    dielectric("Silicone White", "Rubber", 0xE8E6E1FF, 35, Plain, "Silicone"),
    dielectric("Silicone Red", "Rubber", 0xD9473FFF, 35, Plain, "Silicone"),
    dielectric("Silicone Blue", "Rubber", 0x4F86C6FF, 35, Plain, "Silicone"),
    // Glas und Acryl: durchsichtig, die Spiegelung bleibt voll
    dielectric("Clear Glass", "Glass", 0xF0F6F6FF, 98, Plain, "Glass", nullptr, 65),
    dielectric("Frosted Glass", "Glass", 0xF0F3F3FF, 45, Plain, "Glass", nullptr, 50),
    dielectric("Tinted Glass", "Glass", 0x60666CFF, 98, Plain, "Glass", nullptr, 60),
    dielectric("Clear Acrylic", "Glass", 0xF8F8F8FF, 95, Plain, "Acrylic", nullptr, 62),
    dielectric("Opal Acrylic", "Glass", 0xF6F6F4FF, 90, Plain, "Acrylic", nullptr, 25),
    dielectric("Red Acrylic", "Glass", 0xD8312AFF, 95, Plain, "Acrylic", nullptr, 45),
    dielectric("Blue Acrylic", "Glass", 0x2F7FD8FF, 95, Plain, "Acrylic", nullptr, 45),
    // Holz mit Oberfläche: roh (oben), geölt, lackiert
    dielectric("Ash", "Wood", 0xAC947DFF, 20, Grain, "Ash", ":/mycad/textures/ash.jpg"),
    dielectric("Teak", "Wood", 0xAF8257FF, 30, Grain, "Teak", ":/mycad/textures/teak.jpg"),
    dielectric("Plywood", "Wood", 0x7E6140FF, 20, Grain, nullptr, ":/mycad/textures/plywood.jpg"),
    dielectric("Oak, Oiled", "Wood", 0xA17E57FF, 50, Grain, "Oak", ":/mycad/textures/oak.jpg"),
    dielectric("Oak, Lacquered", "Wood", 0xA17E57FF, 45, Grain | Coat, "Oak", ":/mycad/textures/oak.jpg"),
    dielectric("Walnut, Oiled", "Wood", 0x5E412BFF, 50, Grain, "Walnut", ":/mycad/textures/walnut.jpg"),
    dielectric("Walnut, Lacquered", "Wood", 0x5E412BFF, 45, Grain | Coat, "Walnut", ":/mycad/textures/walnut.jpg"),
    dielectric("Maple, Oiled", "Wood", 0xE3D4B9FF, 50, Grain, "Maple", ":/mycad/textures/maple.jpg"),
    dielectric("Maple, Lacquered", "Wood", 0xE3D4B9FF, 45, Grain | Coat, "Maple", ":/mycad/textures/maple.jpg"),
    dielectric("Ash, Oiled", "Wood", 0xAC947DFF, 50, Grain, "Ash", ":/mycad/textures/ash.jpg"),
    dielectric("Teak, Oiled", "Wood", 0xAF8257FF, 55, Grain, "Teak", ":/mycad/textures/teak.jpg"),
    // Stein, Beton, Keramik
    dielectric("Black Marble", "Stone", 0x3D3F3EFF, 80, Coat, nullptr, ":/mycad/textures/marble_black.jpg"),
    dielectric("Glazed Ceramic", "Stone", 0xF4F3EFFF, 60, Coat, "Ceramic"),
    dielectric("Porcelain", "Stone", 0xF7F6F2FF, 85, Plain, "Ceramic"),
    dielectric("Stoneware", "Stone", 0xD8D2C8FF, 25, Plain, "Ceramic"),
    dielectric("Terracotta", "Stone", 0xB8653EFF, 12, Plain, "Ceramic"),
    // Leder und Stoff
    dielectric("Fabric", "Fabric & Leather", 0x5B5B5BFF, 5, Plain, nullptr, ":/mycad/textures/fabric.jpg"),
    dielectric("Felt Gray", "Fabric & Leather", 0x7A7B7EFF, 0, Plain, "Felt"),
    dielectric("Felt Anthracite", "Fabric & Leather", 0x3A3B3EFF, 0, Plain, "Felt"),
    // Carbon und Verbund
    dielectric("Carbon Fiber, Matte", "Composites", 0x2F2E31FF, 40, Plain, "Carbon Fiber", ":/mycad/textures/carbon.jpg"),
    dielectric("Fiberglass", "Composites", 0xD9D7C9FF, 50),
    dielectric("Circuit Board", "Composites", 0x2F6B3AFF, 60, Coat),
};

const BodyMaterial& bodyMaterial()
{
    const long i = App::GetApplication()
                       .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")
                       ->GetInt("BodyMaterial", DefaultBodyMaterial);
    static_assert(std::string_view(bodyMaterials[DefaultBodyMaterial].name) == "Steel");
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
    view->SetInt("DefaultShapeTransparency", m.transparency);
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
    // Auswahl in der Skizze grün (Kontrast-Variante): Blau heißt hier schon "unterbestimmt", ausgewählte Kanten sähen
    // sonst aus wie alle anderen
    view->SetUnsigned("SketchSelectionColor", packed(t.greenIC));
    // Vorauswahl (Hover) in der Skizze: das normale Grün, kräftig auf dem hellen Hintergrund; die blasse HighlightColor
    // der 3D-Ansicht ließe Linien und Achsen unter der Maus verschwinden
    view->SetUnsigned("SketchHighlightColor", packed(t.green));
    for (const char* soft : {"SketchEdgeColor", "SketchVertexColor", "ConstrainedDimColor", "ConstrainedIcoColor", "CursorTextColor"}) {
        view->SetUnsigned(soft, packed(t.labelSecondary));
    }

    // B-Splines wie in Fusion: nur das Kontrollpolygon, keine Analyse-Überlagerungen (Kamm, Gewichte, Knoten)
    auto sketcher = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/Sketcher/General");
    sketcher->SetBool("BSplineCombVisible", false);
    sketcher->SetBool("BSplinePoleWeightVisible", false);
    sketcher->SetBool("BSplineKnotMultiplicityVisible", false);
    sketcher->SetBool("BSplineDegreeVisible", false);
    // Keine FreeCAD-Rückfrage, wenn Tangential an verbundenen Enden zur Endpunkt-Tangente wird: das Ergebnis sieht man
    sketcher->SetBool("NotifyConstraintSubstitutions", false);
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
        {"TreeRename", "Design_ScribblePencil", grey},  // Stift am Designnamen beim Überfahren (Tree.cpp)
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
        // "Intersection" allein ist auch der Ecken-Modus von Versatz (deutsch "Schnitt"): voller Name wie in der Hilfe
        {QStringLiteral("Intersection"), QStringLiteral("External Intersection")},
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
        // so breit wie der Name (wie in macOS-Toolbars), 60 bis 108; was dann noch zu lang ist, bricht an einem
        // Leerzeichen oder nach "/" in zwei Zeilen um statt abgeschnitten zu werden (MyStyle T-8). Feste 74 schnitten
        // einzelne lange Wörter ab ("Extrudier…"), bei Menü-Knöpfen fehlte der Pfeil in der Rechnung (Qt kürzte mittig)
        constexpr int narrowest = 60, widest = 108;
        const int extra = dropdown ? 12 + 14 : 12;  // Rand und Innenabstand, bei Menü-Knöpfen dazu der Pfeil (14)
        const QFontMetrics fm(btn->font());
        QString text = btn->property("label").toString();
        if (fm.horizontalAdvance(text) + extra > widest) {
            int best = -1;  // Umbruch möglichst mittig: an einem Leerzeichen (fällt weg) oder nach "/" (bleibt stehen)
            for (int i = 0; i < int(text.size()); ++i) {
                if ((text[i] == QLatin1Char(' ') || text[i] == QLatin1Char('/'))
                    && (best < 0 || std::abs(2 * i - int(text.size())) < std::abs(2 * best - int(text.size())))) {
                    best = i;
                }
            }
            if (best > 0) {
                const bool slash = text[best] == QLatin1Char('/');
                text = text.left(best + (slash ? 1 : 0)) + QLatin1Char('\n') + text.mid(best + 1);
            }
        }
        QStringList lines = text.split(QLatin1Char('\n'));
        int need = 0;
        for (QString& line : lines) {
            line = fm.elidedText(line, Qt::ElideRight, widest - extra);  // nur was selbst bei 96 nicht passt
            need = std::max(need, fm.horizontalAdvance(line));
        }
        btn->setText(lines.join(QLatin1Char('\n')));
        btn->setFixedSize(std::clamp(need + extra, narrowest, widest), 60);
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
    /// Größe eines Elements; ist es allein breiter als die Fläche und kann selbst umbrechen (ein Toolbar-Abschnitt mit
    /// vielen Werkzeugen), bekommt es die volle Breite und die Höhe dafür, statt über den Rand zu laufen
    static QSize itemSize(QLayoutItem* item, int width)
    {
        const QSize s = item->sizeHint();
        return s.width() > width && item->hasHeightForWidth() ? QSize(width, item->heightForWidth(width)) : s;
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
            const int w = itemSize(item, area.width()).width();
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
                rowWidth += itemSize(item, area.width()).width() + spacing();
                rowHeight = std::max(rowHeight, itemSize(item, area.width()).height());
            }
            if (apply) {
                int px = area.left() + (left ? 0 : std::max(0, (area.width() - rowWidth) / 2));
                for (QLayoutItem* item : row) {
                    const QSize s = itemSize(item, area.width());
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

/// Knopf folgt dem Befehl, wird aber nicht grau, solange eine Maustaste gedrückt ist: Skizzenbefehle sind beim Ziehen
/// in der Skizze kurz inaktiv, die Leiste blinkte sonst bei jedem Ziehen. Nach dem Loslassen zieht er nach.
void followEnabled(QToolButton* btn, QAction* action)
{
    if (!action->isEnabled() && btn->isEnabled() && QGuiApplication::mouseButtons() != Qt::NoButton) {
        QTimer::singleShot(200, btn, [btn, action] { followEnabled(btn, action); });
        return;
    }
    btn->setEnabled(action->isEnabled());
}

/// Kapsel-Toolbar mit Befehls-Buttons in Abschnitten wie bei Fusion: "#CREATE" beginnt einen Abschnitt mit dieser
/// Überschrift (darunter), Abschnitte sind durch eine Linie getrennt; "A|B" = Knopf mit Varianten-Menü.
QWidget* toolbar(const std::vector<const char*>& commands)
{

    auto w = content();
    auto lay = new FlowLayout(w);  // bricht um, wenn das Fenster schmal ist
    lay->setContentsMargins(10, 6, 10, 6);
    lay->setSpacing(2);
    FlowLayout* row = nullptr;  // Knöpfe des aktuellen Abschnitts; bricht um, wenn der Abschnitt allein zu breit ist
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
        auto buttons = new QWidget;
        row = new FlowLayout(buttons);
        row->setContentsMargins(0, 0, 0, 0);
        row->setSpacing(2);
        column->addWidget(buttons);
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
                followEnabled(btn, action);
            });
            for (const auto& [n, a] : choices) {
                QObject::connect(a, &QAction::changed, btn, [btn, choices, pick, current] {
                    bool any = false;
                    for (const auto& [cn, ca] : choices) {
                        if (ca->isChecked()) {
                            any = true;
                            if (*current != ca) {
                                pick(cn, ca);
                            }
                        }
                    }
                    // Qt ignoriert setChecked an einem nicht prüfbaren Knopf: erst prüfbar machen, dann setzen
                    if (any) {
                        btn->setCheckable(true);
                    }
                    btn->setChecked(any);
                    btn->setCheckable(any);
                });
            }
            row->addWidget(btn);
            continue;
        }
        btn->setObjectName(QStringLiteral("GlassButton"));
        btn->setProperty("command", QString::fromLatin1(name));
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
            followEnabled(btn, action);
            btn->setCheckable(action->isCheckable());
            btn->setChecked(action->isChecked());
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
    /// Gezogen und losgelassen: Stelle in Koordinaten des Elternwidgets (der Timeline-Leiste)
    std::function<void(QPoint)> onDrop;

protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override
    {
        event->accept();
        if (onDoubleClick) {
            QTimer::singleShot(0, onDoubleClick);  // nicht mitten im Maus-Event den Edit-Modus starten
        }
    }
    // Ziehen ohne QDrag: in den Glas-Panels (Proxy-Widgets in der 3D-Szene) kommt Drag & Drop nicht sicher an,
    // gedrückt gehaltene Maus-Ereignisse schon
    void mousePressEvent(QMouseEvent* event) override
    {
        pressPos = event->position().toPoint();
        dragging = false;
        QToolButton::mousePressEvent(event);
    }
    void mouseMoveEvent(QMouseEvent* event) override
    {
        if ((event->buttons() & Qt::LeftButton) && onDrop
            && (event->position().toPoint() - pressPos).manhattanLength() >= QApplication::startDragDistance()) {
            if (!dragging) {
                dragging = true;
                setDown(false);
                setCursor(Qt::ClosedHandCursor);
            }
            event->accept();
            return;
        }
        QToolButton::mouseMoveEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent* event) override
    {
        if (!dragging) {
            QToolButton::mouseReleaseEvent(event);
            return;
        }
        dragging = false;
        unsetCursor();
        setDown(false);
        event->accept();
        const QPoint at = mapTo(parentWidget(), event->position().toPoint());
        auto drop = onDrop;
        QTimer::singleShot(0, [drop, at] { drop(at); });  // die Leiste wird danach neu aufgebaut
    }

private:
    QPoint pressPos;
    bool dragging = false;
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

WindowGrip* windowGrip()
{
    static auto grip = new WindowGrip;
    return grip;
}

void showStartPage();
void showHelp(const QString& id = QString());
void toggleBrowser();

/// Fensterknöpfe wie unter KDE: minimieren, maximieren/wiederherstellen, schließen. Liegen in einer eigenen Glas-Kapsel
/// rechts oben, darin nichts anderes (MyStyle W-1)
/// Fensterknöpfe rechts oben. MyCAD weicht hier bewusst von MyStyle W-1/W-7 ab (Chris, 2026-11-10): Zurück und
/// Startseite stehen vorne in derselben Kapsel, durch einen Trenner abgesetzt, statt unten in der Seitenleiste
/// (Navigation gehört nach oben, W-5: nichts Wichtiges an den unteren Rand)
class WindowControls: public QWidget
{
public:
    explicit WindowControls(std::function<void()> backAction = {}, const QString& backTip = {}, bool home = false)
    {
        setObjectName(QStringLiteral("GlassContent"));
        auto lay = new QHBoxLayout(this);
        lay->setContentsMargins(4, 4, 4, 4);  // 36 + 2 * 4 = size.barHeight
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
        if (backAction) {
            back = button("Window_Back", "GlassButton", backTip, backAction);
        }
        if (home) {
            button("Window_Home", "GlassButton", T("Home"), showStartPage);
        }
        if (backAction || home) {
            separator = new QFrame;
            separator->setObjectName(QStringLiteral("ToolbarSeparator"));
            separator->setFixedSize(9, 28);
            lay->addWidget(separator);
            onlyBack = !home;
        }
        button("Window_Minimize", "GlassButton", T("Minimize"), [] { getMainWindow()->showMinimized(); });
        maximize = button("Window_Maximize", "GlassButton", T("Maximize"), toggleMaximized);
        // Schließen: rot beim Überfahren, Glyph dann weiß (autoRaise zeichnet das Icon im Zustand Active)
        button("Window_Close", "WindowClose", T("Close"), [] { getMainWindow()->close(); })->setAutoRaise(true);
        getMainWindow()->installEventFilter(this);
        update();
    }

    /// Zurück nur zeigen, wenn es wohin geht (Startseite: ein Design ist offen); ohne Startseite-Knopf auch den Trenner
    void setBackVisible(bool visible)
    {
        if (back) {
            back->setVisible(visible);
            separator->setVisible(visible || !onlyBack);
        }
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
    QToolButton* back = nullptr;
    QFrame* separator = nullptr;
    bool onlyBack = false;
};

/// Kopf jeder Seitenleiste: App-Name auf Höhe der Titelzeile (W-1, W-2), rechts daneben bei Bedarf ein Knopf
QWidget* sidebarHead(QToolButton* toggle = nullptr)
{
    auto head = new QWidget;
    head->setFixedHeight(Token::WindowButton);
    auto lay = new QHBoxLayout(head);
    lay->setContentsMargins(10, 0, 0, 0);
    auto name = new QLabel(QStringLiteral("MyCAD"));
    setTextStyle(name, Text::Title2);
    name->setAttribute(Qt::WA_TransparentForMouseEvents);  // Ziehen geht an die Seitenleiste
    lay->addWidget(name, 1);
    if (toggle) {
        lay->addWidget(toggle);
    }
    return head;
}

/// Fuß jeder Seitenleiste: App-Aktionen über der Version (W-7). home, help: Einträge zu Startseite und Hilfe (nicht auf
/// der jeweiligen Seite selbst). Zurück steht in den Fensterknöpfen (WindowControls)
/// status: steht rechts in der Zeile der Version, wie eine Statuszeile (nicht klickbar, z. B. "Gesichert")
QWidget* sidebarFooter(bool home, bool help = true, QWidget* status = nullptr)
{
    auto foot = new QWidget;
    auto lay = new QVBoxLayout(foot);
    lay->setContentsMargins(0, 8, 0, 0);
    lay->setSpacing(2);
    auto row = [lay](const char* icon, const QString& text, const QString& tip, std::function<void()> action) {
        auto btn = new QToolButton;
        btn->setObjectName(QStringLiteral("PaletteRow"));
        btn->setIcon(designIcon(QString::fromLatin1(icon), &Theme::labelSecondary));
        btn->setIconSize(QSize(Token::IconM, Token::IconM));
        btn->setText(text);
        btn->setToolTip(tip);
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        btn->setFixedHeight(32);
        btn->setCursor(Qt::ArrowCursor);
        QObject::connect(btn, &QToolButton::clicked, btn, [action] { QTimer::singleShot(0, action); });
        lay->addWidget(btn);
        return btn;
    };
    if (home) {
        row("Window_Home", T("Home"), T("Home"), showStartPage);
    }
    if (help) {
        row("Window_Help", T("Help"), T("Help (F1)"), [] { showHelp(); });
    }
    row("MyCAD_Settings", T("Settings"), T("Settings (Ctrl+,)"), [] {
        Application::Instance->commandManager().runCommandByName("MyCAD_Settings");
    });
    auto version = new QLabel(Gui::Shell::version());
    version->setObjectName(QStringLiteral("Hint"));
    setTextStyle(version, Text::Caption);
    version->setContentsMargins(10, 6, 0, 0);
    if (status) {
        auto line = new QHBoxLayout;
        line->setContentsMargins(0, 0, 0, 0);
        line->addWidget(version);
        line->addStretch();
        line->addWidget(status);
        lay->addLayout(line);
    }
    else {
        lay->addWidget(version);
    }
    return foot;
}

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


/// Gerundete Fensterecken (MyStyle radius.window) mit Haarlinie, nur rahmenlos und nicht maximiert. Das Fenster hat dann
/// einen Alphakanal: was hier ausgestanzt wird, ist durchsichtig. Die Ecken sind vorgerenderte Bilder, weil QPainter im
/// 3D-Fenster (OpenGL ohne Multisampling) Kurven nicht glättet.
void paintWindowCorners(QPainter& p, const QSize& size, qreal dpr)
{
    MainWindow* mw = getMainWindow();
    if (!mw->testAttribute(Qt::WA_TranslucentBackground) || mw->isMaximized() || mw->isFullScreen()) {
        return;
    }
    const int r = Token::RadiusWindow;
    const QColor rim = theme().increaseContrast ? theme().glassBorder : theme().glassPopupBorder;
    static QImage cut, line;
    static QColor builtRim;
    static qreal builtDpr = 0;
    if (builtDpr != dpr || builtRim != rim) {
        builtDpr = dpr;
        builtRim = rim;
        const int px = qCeil(r * dpr);
        for (QImage* image : {&cut, &line}) {
            *image = QImage(px, px, QImage::Format_ARGB32_Premultiplied);
            image->setDevicePixelRatio(dpr);
            image->fill(Qt::transparent);
        }
        QPainterPath corner, disc, arc;
        corner.addRect(0, 0, r, r);
        disc.addEllipse(0, 0, 2 * r, 2 * r);
        QPainter c(&cut);
        c.setRenderHint(QPainter::Antialiasing);
        c.fillPath(corner.subtracted(disc), Qt::black);
        c.end();
        arc.moveTo(0.5, r);
        arc.arcTo(0.5, 0.5, 2 * r - 1, 2 * r - 1, 180, -90);
        QPainter l(&line);
        l.setRenderHint(QPainter::Antialiasing);
        l.setPen(QPen(rim, 1));
        l.drawPath(arc);
    }
    const int w = size.width(), h = size.height();
    p.save();
    for (const auto& [x, y, sx, sy] : {std::tuple(0, 0, 1, 1), std::tuple(w, 0, -1, 1), std::tuple(0, h, 1, -1), std::tuple(w, h, -1, -1)}) {
        p.save();
        p.translate(x, y);
        p.scale(sx, sy);
        p.setCompositionMode(QPainter::CompositionMode_DestinationOut);
        p.drawImage(0, 0, cut);
        p.setCompositionMode(QPainter::CompositionMode_SourceOver);
        p.drawImage(0, 0, line);
        p.restore();
    }
    p.fillRect(QRect(r, 0, w - 2 * r, 1), rim);
    p.fillRect(QRect(r, h - 1, w - 2 * r, 1), rim);
    p.fillRect(QRect(0, r, 1, h - 2 * r), rim);
    p.fillRect(QRect(w - 1, r, 1, h - 2 * r), rim);
    p.restore();
}

/// Ecken über Startseite und Hilfe: liegt über den Glasflächen, deren Schatten sonst in die Ausschnitte fielen
class WindowEdge: public QWidget
{
public:
    explicit WindowEdge(QWidget* parent)
        : QWidget(parent)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents);
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        paintWindowCorners(p, size(), devicePixelRatioF());
    }
};

/// Hintergrund von Startseite und Hilfe: wie der Hintergrund des 3D-Fensters
void paintBackdrop(QPainter& p, const QRect& r)
{
    QLinearGradient base(0, 0, 0, r.height());
    base.setColorAt(0, theme().backgroundTop);
    base.setColorAt(1, theme().backgroundBottom);
    p.fillRect(r, base);
}

/// Startseite im Stil des restlichen MyCAD (MyStyle § 7.3): Viewport-Hintergrund, links die Seitenleiste von oben bis
/// unten (Name, Neu, Öffnen, Bereiche), in der Titelzeile die Suche und die Fensterknöpfe, darunter die Designs
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
        // Seitenleiste: Text-Glas, innen 8 seitlich, 4 oben (Name mittig in der Titelzeile), 14 unten
        side = new GlassCard(Token::RadiusPanel, true);
        side->setParent(this);
        auto sideLay = new QVBoxLayout(side);
        sideLay->setContentsMargins(GlassCard::Shadow + 8, GlassCard::Shadow + 4, GlassCard::Shadow + 8, GlassCard::Shadow + 14);
        sideLay->setSpacing(2);
        auto sideHead = sidebarHead();
        sideHead->installEventFilter(&grip);
        sideLay->addWidget(sideHead);
        sideLay->addSpacing(8);
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
        sideLay->addWidget(sidebarFooter(false, true));
        side->installEventFilter(&grip);

        // --- Designs (unter den Glasflächen, damit deren Schatten sichtbar bleiben) ---
        scroll = new QScrollArea(this);
        scroll->setObjectName(QStringLiteral("StartScroll"));
        scroll->setWidgetResizable(true);
        scroll->setFrameShape(QFrame::NoFrame);
        scroll->viewport()->setAutoFillBackground(false);
        scroll->lower();

        // --- Titelzeile: Suche als Kapsel über den Designs, rechts die Fensterknöpfe in ihrer eigenen Kapsel ---
        barCard = new GlassCard(Token::RadiusCapsule, false);
        barCard->setParent(this);
        barCard->installEventFilter(&grip);
        auto barLay = new QHBoxLayout(barCard);
        barLay->setContentsMargins(GlassCard::Shadow + 14, GlassCard::Shadow, GlassCard::Shadow + 14, GlassCard::Shadow);
        barLay->setSpacing(8);
        barLay->addWidget(new IconLabel(designIcon(QStringLiteral("Start_Search"), &Theme::labelSecondary), Token::IconM));
        search = new QLineEdit;
        search->setObjectName(QStringLiteral("StartSearch"));
        search->setPlaceholderText(T("Search designs"));
        search->setAccessibleName(T("Search designs"));
        search->setClearButtonEnabled(true);  // Löschen-Kreuz rechts
        QObject::connect(search, &QLineEdit::textChanged, this, [this] { applyFilter(); });
        barLay->addWidget(search);
        controlsCard = new GlassCard(Token::RadiusCapsule, false);
        controlsCard->setParent(this);
        auto controlsLay = new QHBoxLayout(controlsCard);
        controlsLay->setContentsMargins(GlassCard::Shadow, GlassCard::Shadow, GlassCard::Shadow, GlassCard::Shadow);
        controls = new WindowControls([this] { hide(); }, T("Back to Design"));
        controls->installEventFilter(&grip);
        controlsLay->addWidget(controls);
        side->raise();  // der durchsichtige Schattenrand der Leiste darf die ersten Zeilen der Seitenleiste nicht verdecken
        edge = new WindowEdge(this);

        getMainWindow()->installEventFilter(this);
        hide();
    }

    void open()
    {
        const bool wasVisible = isVisible();
        rebuild();
        controls->setBackVisible(anyDesignOpen());
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
        edge->setGeometry(rect());
        const qreal left = m + BrowserWidth + 32;  // etwas mehr Luft zur Seitenleiste als zwischen den Panels
        const qreal controlsW = controls->sizeHint().width();
        controlsCard->place(QRectF(width() - m - controlsW, m, controlsW, Token::BarHeight));
        // die Suche beginnt bündig mit den Designs
        barCard->place(QRectF(left, m, std::min<qreal>(SearchWidth, width() - left - controlsW - 2 * m), Token::BarHeight));
        const int top = int(m + Token::BarHeight + m);
        side->place(QRectF(m, m, BrowserWidth, height() - 2 * m));
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
            auto t = new StartTile(StartTile::picture(thumbnail(file), designIcon(QStringLiteral("Design_Box"))),
                                   fi.completeBaseName(), when(fi.lastModified()), openFile(fi.absoluteFilePath()));
            t->setContextMenuPolicy(Qt::CustomContextMenu);
            QObject::connect(t, &QWidget::customContextMenuRequested, this,  // Maus oder Menütaste: Menü an der Kachel
                             [this, t, path = fi.absoluteFilePath()](const QPoint& pos) { tileMenu(path, t->mapToGlobal(pos)); });
            return t;
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
        folderLabel->setText(T("Projects folder\n%1").arg(pretty));
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

    /// Kontextmenü einer Kachel: Design umbenennen oder in den Papierkorb legen
    void tileMenu(const QString& file, const QPoint& at)
    {
        QMenu menu;
        menu.addAction(T("Rename…"));
        menu.addSeparator();
        QAction* remove = menu.addAction(T("Delete…"));
        QAction* chosen = menu.exec(at);
        if (!chosen) {
            return;
        }
        // erst nach dem Menü: open() baut die Kacheln neu und löscht dabei auch diese
        QTimer::singleShot(0, this, [this, file, del = chosen == remove] { del ? deleteDesign(file) : renameDesign(file); });
    }

    /// offenes Design zur Datei schließen; mit ask fragt es bei Änderungen nach dem Speichern. false = abgebrochen
    static bool closeFile(const QString& file, bool ask)
    {
        for (App::Document* doc : App::GetApplication().getDocuments()) {
            if (QFileInfo(QString::fromUtf8(doc->FileName.getValue())) != QFileInfo(file)) {
                continue;
            }
            Gui::Document* gdoc = Application::Instance->getDocument(doc);
            if (ask && gdoc && !gdoc->canClose(true, true)) {
                return false;
            }
            App::GetApplication().closeDocument(doc->getName());
        }
        return true;
    }

    /// liegt die Datei in ihrem eigenen Projektordner (Name/Name.mycad, so legt Speichern sie an)?
    static bool inOwnFolder(const QFileInfo& fi)
    {
        return Gui::Shell::inOwnFolder(fi.absoluteFilePath());
    }

    /// Datei in den Papierkorb, im eigenen Projektordner den ganzen Ordner (mit Versionen)
    void deleteDesign(const QString& file)
    {
        const QFileInfo fi(file);
        const QString target = inOwnFolder(fi) ? fi.absolutePath() : file;
        QMessageBox box(QMessageBox::Warning, T("Delete Design"),
                        T("Delete “%1”? The file is moved to the trash:\n%2").arg(fi.completeBaseName(), target),
                        QMessageBox::Cancel, getMainWindow());
        QPushButton* remove = box.addButton(T("Delete"), QMessageBox::DestructiveRole);
        box.setDefaultButton(QMessageBox::Cancel);
        box.exec();
        if (box.clickedButton() != remove) {
            return;
        }
        closeFile(file, false);
        if (!QFile::moveToTrash(target)) {
            QMessageBox::warning(getMainWindow(), T("Delete Design"), T("“%1” could not be moved to the trash. Check that you can write to it.").arg(target));
        }
        open();
    }

    /// Datei umbenennen; liegt sie in ihrem eigenen Projektordner (Name/Name.mycad), den Ordner mit. Versionen
    /// (versions/<Name> neben der Datei) wandern mit, die Liste "Recent" zeigt auf die neue Datei.
    void renameDesign(const QString& file)
    {
        const QFileInfo fi(file);
        bool ok = false;
        const QString name = QInputDialog::getText(getMainWindow(), T("Rename Design"), T("Name"), QLineEdit::Normal,
                                                   fi.completeBaseName(), &ok)
                                 .trimmed();
        if (!ok || name.isEmpty() || name == fi.completeBaseName()) {
            return;
        }
        QString error;
        if (Gui::Shell::renameDesignFile(file, name, error).isEmpty()) {
            QMessageBox::warning(getMainWindow(), T("Rename Design"), error);
        }
        open();
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
    GlassCard* barCard;
    GlassCard* controlsCard;
    WindowEdge* edge;
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
        sideLay->setContentsMargins(GlassCard::Shadow + 8, GlassCard::Shadow + 4, GlassCard::Shadow + 8, GlassCard::Shadow + 14);
        auto sideHead = sidebarHead();
        sideHead->installEventFilter(&grip);
        sideLay->addWidget(sideHead);
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
        sideLay->addWidget(sidebarFooter(false, false));
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
        view->viewport()->installEventFilter(this);  // Textspalte bei jeder Breitenänderung neu mittig setzen

        // Titelzeile wie auf der Startseite: Suche als Kapsel über dem Artikel, rechts die Fensterknöpfe
        barCard = new GlassCard(Token::RadiusCapsule, false);
        barCard->setParent(this);
        barCard->installEventFilter(&grip);
        auto barLay = new QHBoxLayout(barCard);
        barLay->setContentsMargins(GlassCard::Shadow + 14, GlassCard::Shadow, GlassCard::Shadow + 14, GlassCard::Shadow);
        barLay->setSpacing(8);
        barLay->addWidget(new IconLabel(designIcon(QStringLiteral("Start_Search"), &Theme::labelSecondary), Token::IconM));
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
        barLay->addWidget(search);
        controlsCard = new GlassCard(Token::RadiusCapsule, false);
        controlsCard->setParent(this);
        auto controlsLay = new QHBoxLayout(controlsCard);
        controlsLay->setContentsMargins(GlassCard::Shadow, GlassCard::Shadow, GlassCard::Shadow, GlassCard::Shadow);
        controls = new WindowControls([this] { hide(); }, T("Back"), true);
        controls->installEventFilter(&grip);
        controlsLay->addWidget(controls);
        side->raise();  // der durchsichtige Schattenrand der Leiste darf die ersten Zeilen der Seitenleiste nicht verdecken
        edge = new WindowEdge(this);

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
        else if (obj == view->viewport() && event->type() == QEvent::Resize) {
            centreText();
        }
        return false;
    }
    void resizeEvent(QResizeEvent*) override
    {
        const qreal m = Token::WindowInset;
        edge->setGeometry(rect());
        const qreal searchLeft = m + BrowserWidth + 32;  // wie auf der Startseite
        const qreal controlsW = controls->sizeHint().width();
        controlsCard->place(QRectF(width() - m - controlsW, m, controlsW, Token::BarHeight));
        // die Suche beginnt bündig mit dem Artikel
        barCard->place(QRectF(searchLeft, m, std::min<qreal>(SearchWidth, width() - searchLeft - controlsW - 2 * m), Token::BarHeight));
        const qreal top = m + Token::BarHeight + m;
        side->place(QRectF(m, m, BrowserWidth, height() - 2 * m));
        // Karte bis zum Rand; die Textspalte bleibt size.contentMaxWidth breit (W-4), siehe centreText()
        articleCard->place(QRectF(searchLeft, top, width() - searchLeft - m, height() - top - m));  // bündig mit der Suche
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
        qDeleteAll(movies);  // Clips des vorigen Artikels anhalten
        movies.clear();
        // selbst auf 560 px skalieren: mit width-Attribut reserviert Qt die Originalhöhe (große Lücke darunter)
        auto fit = [](QImage image) {
            image = image.scaledToWidth(Token::ContentMaxWidth, Qt::SmoothTransformation);
            if (theme().dark) {  // helle Bildschirmfotos im Dunkeln leicht abdunkeln (MyStyle D-4)
                QPainter dim(&image);
                dim.fillRect(image.rect(), QColor(0, 0, 0, 38));
            }
            return image;
        };
        for (const QJsonValue v : a.value(QStringLiteral("images")).toArray()) {
            const QJsonObject img = v.toObject();
            const QString caption = localized(img, "caption").toString();
            const QString file = QStringLiteral(":/mycad/help/images/") + img.value(QStringLiteral("file")).toString();
            const QUrl picture(QStringLiteral("picture:%1").arg(file));
            if (file.endsWith(QLatin1String(".gif"))) {
                // Erklär-Clip: jedes neue Bild ersetzt die Ressource; Bewegung reduzieren zeigt nur das erste (MyStyle M-5)
                auto movie = new QMovie(file, QByteArray(), this);
                movies.append(movie);
                movie->jumpToFrame(0);
                doc->addResource(QTextDocument::ImageResource, picture, fit(movie->currentImage()));
                QObject::connect(movie, &QMovie::frameChanged, this, [this, movie, picture, fit] {
                    view->document()->addResource(QTextDocument::ImageResource, picture, fit(movie->currentImage()));
                    view->viewport()->update();
                });
                if (!theme().reduceMotion) {
                    movie->start();
                }
            }
            else {
                doc->addResource(QTextDocument::ImageResource, picture, fit(QImage(file)));
            }
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
        // Abschnitte mit eigener Überschrift (Überblick, Anleitungen in Kapiteln)
        for (const QJsonValue s : localized(a, "sections").toArray()) {
            const QJsonArray section = s.toArray();
            const bool numbered = section.at(2).toBool();
            html += QStringLiteral("<h3>%1</h3>").arg(esc(section.at(0).toString())) + (numbered ? QStringLiteral("<ol>") : QStringLiteral("<ul>"));
            for (const QJsonValue item : section.at(1).toArray()) {
                html += QStringLiteral("<li>%1</li>").arg(esc(item.toString()));
            }
            html += numbered ? QStringLiteral("</ol>") : QStringLiteral("</ul>");
        }
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
        centreText();
    }

    /// Lesetext höchstens size.contentMaxWidth (560) breit, mittig in der Karte (W-4); Ränder des Wurzelrahmens
    void centreText()
    {
        QTextDocument* doc = view->document();
        QTextFrameFormat f = doc->rootFrame()->frameFormat();
        const qreal side = std::max(doc->documentMargin(), (view->viewport()->width() - Token::ContentMaxWidth) / 2.0);
        if (f.leftMargin() != side) {
            f.setLeftMargin(side);
            f.setRightMargin(side);
            doc->rootFrame()->setFrameFormat(f);
        }
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
            for (const QJsonValue s : localized(a, "sections").toArray()) {
                haystack += QLatin1Char(' ') + s.toArray().at(0).toString();
                for (const QJsonValue v : s.toArray().at(1).toArray()) {
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
    GlassCard* barCard;
    GlassCard* controlsCard;
    WindowEdge* edge;
    WindowControls* controls;
    QTextBrowser* view;
    QList<QMovie*> movies;  ///< Erklär-Clips (GIF) des offenen Artikels
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
    static constexpr int TitleHeight = 20 + 6;  // Headline-Zeile und Abstand zum Inhalt (MyStyle Alert)

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (event->type() == QEvent::Paint) {
            auto box = static_cast<QWidget*>(obj);
            QPainter p(box);
            paintGlass(p, QRectF(box->rect()).adjusted(Shadow, Shadow, -Shadow, -Shadow), Token::RadiusPanel, true, true);
            if (box->property("glassTitle").toBool()) {  // Titel statt Titelleiste, Headline oben im Glas
                p.setFont(textFont(Text::Headline));
                p.setPen(theme().labelPrimary);
                const QRect line(Shadow + 22, Shadow + 20, box->width() - 2 * (Shadow + 22), 20);
                p.drawText(line, Qt::AlignLeft | Qt::AlignVCenter,
                           p.fontMetrics().elidedText(box->windowTitle(), Qt::ElideRight, line.width()));
            }
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
/// Liquid Glass: Meldungen, Rückfragen und alle anderen modalen Dialoge als rahmenlose Glas-Karten (L3), Titel im Glas
class MenuPolisher: public QObject
{
    /// rahmenloses Fenster mit Text-Glas statt Titelleiste und Hintergrund
    static void makeAlert(QWidget* box)
    {
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
        box->installEventFilter(&painter);
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        // Dezimalkomma auch in einfachen Zahlenfeldern: QDoubleSpinBox prüft nach dem Gebietsschema und verwarf mit Punkt
        // das Komma; Maßfelder (QuantitySpinBox) nehmen es beim Auswerten (App::interpretQuantityInput)
        if (event->type() == QEvent::KeyPress && static_cast<QKeyEvent*>(event)->text() == QLatin1String(",")) {
            auto edit = qobject_cast<QLineEdit*>(obj);
            auto box = edit ? qobject_cast<QDoubleSpinBox*>(edit->parentWidget()) : nullptr;
            if (box && box->locale().decimalPoint() == QLatin1Char('.')) {
                auto key = static_cast<QKeyEvent*>(event);
                QKeyEvent dot(QEvent::KeyPress, Qt::Key_Period, key->modifiers(), QStringLiteral("."));
                QCoreApplication::sendEvent(edit, &dot);
                return true;
            }
        }
        if (event->type() == QEvent::Polish) {
            if (auto box = qobject_cast<QMessageBox*>(obj); box && !box->property("glass").toBool()) {
                makeAlert(box);
                // Innenabstand 20 oben, 22 seitlich, 18 unten (MyStyle § 7.1); QMessageBox bringt selbst etwa 10 mit
                box->setContentsMargins(AlertPainter::Shadow + 12, AlertPainter::Shadow + 10, AlertPainter::Shadow + 12,
                                        AlertPainter::Shadow + 8);
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
            // alle anderen modalen Dialoge (Maß in der Skizze, Name, Versionen …) ebenso, ohne Titelleiste: den Titel
            // zeichnet AlertPainter. Nicht: Dateiauswahl (groß, muss sich ziehen lassen), schon rahmenlose (Einstellungen)
            if (auto dialog = qobject_cast<QDialog*>(obj); dialog && dialog->isWindow() && dialog->parentWidget()
                && !qobject_cast<QMessageBox*>(obj) && !obj->inherits("QFileDialog")
                && !(dialog->windowFlags() & Qt::FramelessWindowHint) && !dialog->property("glass").toBool()) {
                makeAlert(dialog);
                dialog->setProperty("glassTitle", !dialog->windowTitle().isEmpty());
                const int title = dialog->windowTitle().isEmpty() ? 0 : AlertPainter::TitleHeight;
                // Innenabstand 20 oben, 22 seitlich, 18 unten (MyStyle § 7.1) statt dem des Layouts
                dialog->setContentsMargins(AlertPainter::Shadow + 22, AlertPainter::Shadow + 20 + title, AlertPainter::Shadow + 22,
                                           AlertPainter::Shadow + 18);
                if (QLayout* lay = dialog->layout()) {
                    lay->setContentsMargins(0, 0, 0, 0);
                }
                // Stylesheet-Regeln für [glass="true"] greifen erst nach neuem Polieren, auch bei schon polierten
                // Kindern (eine Tabelle poliert ihren Kopf beim Bemessen, lange vor dem Einblenden)
                QList<QWidget*> all = dialog->findChildren<QWidget*>();
                all.prepend(dialog);
                for (QWidget* w : all) {
                    w->style()->unpolish(w);
                    w->style()->polish(w);
                    // die Liste eines Auswahlfelds entsteht schon beim Befüllen (noch als Menü: 2 px schwarzer Rand
                    // oben und unten, z. B. Drucken: welcher Slicer?) und übernimmt Art und Ränder erst mit StyleChange
                    if (qobject_cast<QComboBox*>(w)) {
                        QEvent change(QEvent::StyleChange);
                        QCoreApplication::sendEvent(w, &change);
                    }
                }
            }
            if (auto dialog = qobject_cast<QDialog*>(obj); dialog && dialog->parentWidget()) {
                dialog->installEventFilter(Scrim::instance());
            }
            // FreeCADs Toolbars (MyCAD zeigt sie nie, siehe hideChrome) ohne Platz im Fensterlayout: Qt legt das Layout
            // beim Einblenden sofort neu an, die 3D-Ansicht wurde kleiner und wieder groß (graues Bild beim Betreten
            // der Skizze)
            if (auto bar = qobject_cast<QToolBar*>(obj); bar && bar->parentWidget() == getMainWindow()) {
                bar->setMaximumSize(0, 0);
            }
            if (auto menu = qobject_cast<QMenu*>(obj)) {
                menu->setAttribute(Qt::WA_TranslucentBackground);
                menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
            }
            else if (obj->inherits("Gui::NotificationLabel")) {  // Fehlermeldungen: runde Ecken statt gelbem Tooltip
                static_cast<QWidget*>(obj)->setAttribute(Qt::WA_TranslucentBackground);
            }
        }
        // Zahlenfelder: Qt legt das Eingabefeld trotz padding an den linken Rand (nur rechts zählen Rand und
        // Innenabstand), der Text klebte am Rand. Den fehlenden Abstand links (Rand 2 + Innenabstand 8 wie bei
        // QLineEdit, MyStyle 9.3) als Textrand nachholen; die Breite des Felds rechnet ihn schon ein
        else if (event->type() == QEvent::Resize) {
            if (auto edit = qobject_cast<QLineEdit*>(obj); edit && qobject_cast<QAbstractSpinBox*>(edit->parentWidget())) {
                const int left = std::max(0, 10 - edit->x());
                if (edit->textMargins().left() != left) {
                    edit->setTextMargins(left, 0, 0, 0);
                }
            }
        }
        // FreeCADs Toolbars gleich beim Einblenden wieder verstecken (Werkbank- und Bearbeitungswechsel, z. B. beim
        // Betreten der Skizze): erst im nächsten Durchlauf (hideChromeLater) blitzten sie ein Bild lang auf
        else if (event->type() == QEvent::ShowToParent && qobject_cast<QToolBar*>(obj)
                 && static_cast<QWidget*>(obj)->parentWidget() == getMainWindow()) {
            static_cast<QWidget*>(obj)->hide();
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
        // Klick auf den Designnamen oben im Browser: umbenennen (beim Überfahren zeigt er einen Stift, Tree.cpp);
        // Datei und Projektordner heißen danach mit (Gui::Shell::labelEdited)
        if (tree && event->type() == QEvent::MouseButtonRelease) {
            auto me = static_cast<QMouseEvent*>(event);
            const QPoint pos = me->position().toPoint();
            QTreeWidgetItem* item = tree->itemAt(pos);
            if (me->button() == Qt::LeftButton && me->modifiers() == Qt::NoModifier && item
                && item->type() == TreeWidget::DocumentType && tree->visualItemRect(item).contains(pos)) {
                QTimer::singleShot(0, tree, [tree, index = QPersistentModelIndex(tree->indexAt(pos))] {
                    if (index.isValid()) {
                        tree->selectionModel()->select(index, QItemSelectionModel::Deselect);  // Feld auf ruhigem Grund
                        tree->edit(index);
                    }
                });
            }
        }
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
                    QObject::connect(menu.addAction(T("Save Version")), &QAction::triggered, [run] { run("MyCAD_SaveVersion"); });
                    QObject::connect(menu.addAction(T("Save As…")), &QAction::triggered, [run] { run("Std_SaveAs"); });
                    QObject::connect(menu.addAction(T("Export…")), &QAction::triggered, [run] { run("Design_Export"); });
                    addVariantMenu(menu.addMenu(T("Variants")), guiDoc()->getDocument(), run);
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
                            // im eigenen Projektordner den ganzen Ordner (mit Versionen), wie auf der Startseite;
                            // sonst blieb ein Ordner mit allen Versionen eines gelöschten Designs liegen
                            const QString target = !file.isEmpty() && Gui::Shell::inOwnFolder(file)
                                ? QFileInfo(file).absolutePath() : file;
                            QMessageBox box(QMessageBox::Warning, T("Delete Design"),
                                            file.isEmpty() ? T("Delete “%1”? It has never been saved, so its contents will be gone.")
                                                                 .arg(label)
                                                           : T("Delete “%1”? The file is moved to the trash:\n%2")
                                                                 .arg(label, target),
                                            QMessageBox::Cancel, getMainWindow());
                            QPushButton* remove = box.addButton(T("Delete"), QMessageBox::DestructiveRole);
                            box.setDefaultButton(QMessageBox::Cancel);
                            box.exec();
                            if (box.clickedButton() != remove) {
                                return;
                            }
                            App::GetApplication().closeDocument(doc->getName());
                            if (!target.isEmpty() && !QFile::moveToTrash(target)) {
                                QMessageBox::warning(getMainWindow(), T("Delete Design"),
                                                     T("“%1” could not be moved to the trash. Check that you can write to it.").arg(target));
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
                    Gui::Document* gdoc = Application::Instance->activeDocument();
                    auto edit = gdoc ? dynamic_cast<ViewProviderDocumentObject*>(gdoc->getInEdit()) : nullptr;
                    if (edit && std::string_view(edit->getObject()->getTypeId().getName()) == "Design::Scribble") {
                        showCommandMenu({{T("Undo"), "Std_Undo"},
                                         {T("Redo"), "Std_Redo"},
                                         {QString(), ""},
                                         {T("Look At"), "Design_ScribbleLookAt"},
                                         {T("Tracing Paper"), "Design_ScribbleTracing"},
                                         {QString(), ""},
                                         {T("Finish Scribble"), "Design_ScribbleFinish"}});
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

/// Zeile einer Palette: Text, Befehl, Icon
struct PaletteRow
{
    const char* text;
    const char* command;
    const char* icon;
};

/// Palette rechts unter dem ViewCube wie Fusions Sketch Palette: Zeilen für Befehle (umschaltbare zeigen ihren Zustand),
/// unten der Fertig-Knopf
QWidget* toolPalette(const char* heading, std::initializer_list<PaletteRow> rows, const char* finishCommand, const char* finishText)
{
    auto box = content();
    auto lay = new QVBoxLayout(box);
    lay->setContentsMargins(8, 14, 8, 14);  // wie die Seitenleisten: Zeilen 8 vom Rand (r 20 - 8 = r 12)
    lay->setSpacing(2);
    auto title = new QLabel(T(heading));
    setTextStyle(title, Text::Headline);
    title->setContentsMargins(10, 0, 0, 0);
    lay->addWidget(title);
    lay->addSpacing(4);
    for (const PaletteRow& row : rows) {
        QAction* action = commandAction(row.command);
        if (!action) {
            continue;
        }
        auto btn = new QToolButton;
        btn->setObjectName(QStringLiteral("PaletteRow"));
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btn->setText(T(row.text));
        btn->setIcon(designIcon(QString::fromLatin1(row.icon), &Theme::labelSecondary));
        btn->setIconSize(QSize(Token::IconM, Token::IconM));
        btn->setCheckable(action->isCheckable());
        btn->setChecked(action->isChecked());
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        btn->setFixedHeight(32);
        QObject::connect(btn, &QToolButton::clicked, action, [action] {
            QTimer::singleShot(0, action, &QAction::trigger);
        });
        QObject::connect(action, &QAction::changed, btn, [btn, action] {
            btn->setCheckable(action->isCheckable());
            btn->setChecked(action->isChecked());
        });
        lay->addWidget(btn);
    }
    lay->addSpacing(8);
    if (QAction* finish = commandAction(finishCommand)) {
        auto btn = new QToolButton;
        btn->setObjectName(QStringLiteral("GlassProminent"));
        btn->setProperty("command", QString::fromLatin1(finishCommand));
        btn->setText(T(finishText));
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

/// Freie Fläche der Titelzeile: liegt über der 3D-Ansicht und unter den Panels, verschiebt das Fenster (W-1)
class TitleGrip: public QGraphicsRectItem
{
public:
    TitleGrip()
    {
        setZValue(5);
        setPen(Qt::NoPen);
        setAcceptedMouseButtons(Qt::LeftButton);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*) override
    {
        if (getMainWindow()->windowHandle()) {
            getMainWindow()->windowHandle()->startSystemMove();
        }
    }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override
    {
        QTimer::singleShot(0, toggleMaximized);
    }
};

/// Fensterecken über der 3D-Ansicht: liegt über allem und nimmt keine Mausereignisse an
class WindowCorners: public QGraphicsRectItem
{
public:
    WindowCorners()
    {
        setZValue(1000);
        setPen(Qt::NoPen);
        setAcceptedMouseButtons(Qt::NoButton);
    }
    QPainterPath shape() const override
    {
        return {};
    }
    void paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget* widget) override
    {
        auto ctx = QOpenGLContext::currentContext();
        if (!ctx) {
            return;
        }
        // Durchsichtiges im 3D-Bild (Ursprungsebenen, Glas) hinterlässt Alpha < 1: das Fenster wäre dort durchsichtig
        p->beginNativePainting();
        QOpenGLFunctions* f = ctx->functions();
        f->glDisable(GL_SCISSOR_TEST);
        f->glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
        f->glClearColor(0, 0, 0, 1);
        f->glClear(GL_COLOR_BUFFER_BIT);
        f->glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        p->endNativePainting();
        paintWindowCorners(*p, rect().size().toSize(), widget->devicePixelRatioF());
    }
};

/// Post-it auf dem Bildschirm; das Objekt dahinter (Design::Note) wird über doc/name gesucht, es kann weg sein
struct NotePanel
{
    GlassPanel* panel = nullptr;
    QLabel* title = nullptr;
    QPlainTextEdit* edit = nullptr;
    std::string doc, name;

    App::DocumentObject* object() const
    {
        App::Document* d = App::GetApplication().getDocument(doc.c_str());
        return d ? d->getObject(name.c_str()) : nullptr;
    }
};

struct State
{
    GlassPanel* header = nullptr;  ///< Kopfleiste über die ganze Fensterbreite: Seitenleisten-Knopf, Toolbar, Fensterknöpfe
    QWidget* modelBar = nullptr;
    QWidget* sketchBar = nullptr;
    QWidget* scribbleBar = nullptr;
    GlassPanel* collapsedBar = nullptr;  ///< Name und Seitenleisten-Knopf, solange die Seitenleiste eingeklappt ist (W-1)
    WindowControls* windowControls = nullptr;
    GlassPanel* windowPanel = nullptr;  ///< Kapsel der Fensterknöpfe
    QGraphicsRectItem* titleGrip = nullptr;  ///< freie Fläche der Titelzeile verschiebt das Fenster; nur rahmenlos
    GlassPanel* browser = nullptr;
    GlassPanel* inspector = nullptr;
    GlassPanel* timeline = nullptr;
    GlassPanel* palette = nullptr;
    GlassPanel* scribblePalette = nullptr;
    GlassPanel* scribblePill = nullptr;     ///< "Nur das Blatt": statt Toolbar, Seitenleiste und Palette
    GlassPanel* scribbleActions = nullptr;  ///< Farben und Löschen unter der Auswahl
    bool scribbleFocus = false;
    ViewCube* viewCube = nullptr;
    WindowCorners* corners = nullptr;  ///< nur rahmenlos
    bool sketchMode = false;
    bool scribbleMode = false;  ///< Zeichenblatt eines Scribbles offen
    QGraphicsScene* scene = nullptr;
    std::vector<NotePanel> notes;  ///< offene Post-its des aktiven Designs
    std::string notesDocument;
} state;

extern GlassPanel* searchPanel;  // Befehlssuche (Strg+K), weiter unten
extern QLineEdit* searchField;

std::vector<GlassPanel*> panels()
{
    std::vector<GlassPanel*> all;
    // auch die Suche: sie lag sonst noch in der Szene eines geschlossenen Designs und starb mit ihr (Absturz danach)
    for (auto p : {state.header, state.browser, state.inspector, state.timeline, state.palette, state.scribblePalette,
                   state.scribblePill, state.scribbleActions, state.collapsedBar, state.windowPanel, searchPanel}) {
        if (p) {
            all.push_back(p);
        }
    }
    for (const NotePanel& note : state.notes) {
        all.push_back(note.panel);
    }
    return all;
}

constexpr int NoteWidth = 248, NoteHeight = 200;  // Breite wie das Hinweis-Popup (MyStyle § 9.4)

int noteValue(App::DocumentObject* note, const char* prop)
{
    return static_cast<int>(static_cast<App::PropertyInteger*>(note->getPropertyByName(prop))->getValue());
}

/// Lage im Fenster aus Ecke und Abstand; bleibt immer ganz sichtbar, auch nach dem Verkleinern des Fensters
QRectF noteRect(App::DocumentObject* note, const QRectF& r)
{
    const int corner = noteValue(note, "Corner");
    const qreal x = corner & 1 ? r.width() - noteValue(note, "OffsetX") - NoteWidth : noteValue(note, "OffsetX");
    const qreal y = corner & 2 ? r.height() - noteValue(note, "OffsetY") - NoteHeight : noteValue(note, "OffsetY");
    const qreal m = Token::WindowInset;
    return QRectF(std::max(m, std::min(x, r.width() - NoteWidth - m)), std::max(m, std::min(y, r.height() - NoteHeight - m)),
                  NoteWidth, NoteHeight);
}

/// Neue Lage merken: als Abstand zur nächsten Fensterecke
void setNotePosition(App::DocumentObject* note, const QPointF& pos, const QRectF& r)
{
    const bool right = pos.x() + NoteWidth / 2.0 > r.center().x();
    const bool bottom = pos.y() + NoteHeight / 2.0 > r.center().y();
    const auto set = [note](const char* prop, int value) {
        static_cast<App::PropertyInteger*>(note->getPropertyByName(prop))->setValue(value);
    };
    set("Corner", (right ? 1 : 0) | (bottom ? 2 : 0));
    set("OffsetX", qRound(right ? r.width() - pos.x() - NoteWidth : pos.x()));
    set("OffsetY", qRound(bottom ? r.height() - pos.y() - NoteHeight : pos.y()));
}

void placeSearch(const QRectF& r, qreal top);

void layout()
{
    if (!state.scene) {
        return;
    }
    const QRectF r = state.scene->sceneRect();
    const qreal m = Token::WindowInset;
    if (state.corners) {
        state.corners->setRect(r);
    }
    QWidget* bar = state.sketchMode ? state.sketchBar : state.scribbleMode ? state.scribbleBar : state.modelBar;
    for (QWidget* b : {state.modelBar, state.sketchBar, state.scribbleBar}) {
        b->setVisible(b == bar);
    }
    const QSizeF bs = bar->sizeHint();  // eine Reihe
    const QSizeF cs = state.windowControls ? QSizeF(state.windowControls->sizeHint()) : QSizeF();
    if (state.windowPanel) {
        state.windowPanel->setGeometry(QRectF(r.width() - m - cs.width(), m, cs.width(), Token::BarHeight));
    }
    const bool browser = state.browser
        && !App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetBool("BrowserHidden", false);
    // Die Titelzeile beginnt rechts neben der Seitenleiste; eingeklappt stehen an ihrem Anfang Name und Seitenleisten-Knopf
    // als eigene Kapsel. Die Toolbar steht in der Fenstermitte (Ausnahme in MyStyle W-2) und rückt nur so weit zur
    // Seite, wie sie sonst Seitenleiste oder Fensterknöpfe überdecken würde; reicht die Breite nicht, bricht sie um
    qreal left = m + BrowserWidth + m;
    if (state.collapsedBar) {
        state.collapsedBar->setVisible(!browser);
        if (!browser) {
            const qreal w = state.collapsedBar->content()->sizeHint().width();
            state.collapsedBar->setGeometry(QRectF(m, m, w, Token::BarHeight));
            left = m + w + m;
        }
    }
    const qreal right = r.width() - m - (cs.width() > 0 ? cs.width() + m : 0);
    // Mittig bleiben (MyStyle § 7.3): nur so breit, wie es zentriert zwischen Kapsel und Fensterknöpfe passt;
    // sonst bricht die Toolbar lieber in zwei Reihen um, als zur Seite zu rutschen
    const qreal centered = 2 * std::min(r.width() / 2 - left, right - r.width() / 2);
    qreal barW = std::max<qreal>(100, std::min({qreal(bs.width()), right - left, centered}));
    const qreal barH = barW < bs.width() ? bar->heightForWidth(int(barW)) : bs.height();
    if (barW < bs.width()) {  // Reihen ausgleichen: schmalste Breite mit gleich vielen Reihen
        int lo = 100, hi = int(barW);
        while (lo < hi) {
            const int mid = (lo + hi) / 2;
            if (bar->heightForWidth(mid) <= barH) {
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        barW = hi;
    }
    const qreal headerH = std::max<qreal>(barH, Token::BarHeight);  // eine höhere Toolbar macht nur die Titelzeile höher
    state.header->setGeometry(QRectF(std::max(left, std::min((r.width() - barW) / 2, right - barW)), m, barW, headerH));
    placeSearch(r, m + headerH + m);
    bar->setGeometry(QRectF(0, (headerH - barH) / 2, barW, barH).toRect());
    if (state.titleGrip) {
        state.titleGrip->setRect(0, 0, r.width(), m + headerH);
    }
    // eine Reihe: Kapsel; umgebrochen wäre eine Kapsel zu rund für die Knöpfe in den Ecken, dann Panel-Radius
    state.header->setRadius(barH > bs.height() ? Token::RadiusPanel : Token::RadiusCapsule);

    for (const NotePanel& note : state.notes) {
        if (App::DocumentObject* obj = note.object()) {
            note.panel->setGeometry(noteRect(obj, r));
        }
    }

    qreal bottom = r.height() - m;
    if (state.timeline) {
        const QSizeF ts = state.timeline->content()->sizeHint();
        const bool show = state.timeline->content()->property("count").toInt() > 0;
        state.timeline->setVisible(show);
        state.timeline->setGeometry(
            QRectF(r.center().x() - ts.width() / 2, r.height() - m - ts.height(), ts.width(), ts.height())
        );
    }

    const qreal top = m + headerH + m;  // alles andere beginnt unter der Kopfleiste
    if (state.browser) {
        state.browser->setVisible(browser);
        state.browser->setGeometry(QRectF(m, m, BrowserWidth, bottom - m));  // von oben bis unten (W-1)
    }
    qreal belowCube = 170;
    if (state.viewCube) {
        state.viewCube->setPos(r.width() - state.viewCube->boundingRect().width() - m, top);
        belowCube = top + state.viewCube->boundingRect().height() + m;
    }
    // Im Skizzenmodus übernimmt die Sketch Palette; nur Werkzeug-Optionen (Kopien, Ecken, Abstand …) erscheinen
    // darunter, solange das Werkzeug welche hat (wie Fusions kleine Werkzeug-Dialoge), genau so breit wie die Palette
    QWidget* tool = nullptr;
    QSizeF toolSize;
    if (state.inspector) {
        QWidget* inspector = state.inspector->content();
        for (auto box : inspector->findChildren<QDialogButtonBox*>()) {
            box->setVisible(!state.sketchMode);
        }
        for (auto w : inspector->findChildren<QWidget*>()) {
            if (state.sketchMode && w->inherits("SketcherGui::TaskSketcherTool") && !w->isHidden()) {
                tool = w;
            }
        }
        // Größe aus dem Inhalt: der Inhalt des Rollbereichs plus alles um den Rollbereich herum (Ränder, Panel).
        // Der Rollbereich selbst meldet eine gemerkte alte Größe (QScrollArea::sizeHint), sein Anteil fällt heraus
        QScrollArea* area = nullptr;
        for (QWidget* w = tool; w && !area; w = w->parentWidget()) {
            area = qobject_cast<QScrollArea*>(w);
        }
        if (area) {
            toolSize = inspector->sizeHint() - area->sizeHint().expandedTo(area->minimumSize()) + area->widget()->sizeHint();
        }
    }
    for (auto [panel, show] : {std::pair {state.palette, state.sketchMode}, std::pair {state.scribblePalette, state.scribbleMode}}) {
        if (panel) {
            QSizeF ps = panel->content()->sizeHint();
            ps.setWidth(std::max<qreal>({ps.width(), qreal(panel->content()->minimumWidth()),
                                         panel == state.palette ? toolSize.width() : 0.}));
            panel->setVisible(show);
            panel->setGeometry(QRectF(r.width() - ps.width() - m, belowCube, ps.width(), ps.height()));
        }
    }
    if (state.inspector) {
        const qreal itop = belowCube;  // unter dem ViewCube
        if (!state.sketchMode) {
            state.inspector->setVisible(Control().activeDialog() != nullptr);
            state.inspector->setGeometry(QRectF(r.width() - 340 - m, itop, 340, bottom - itop));
        }
        else {
            state.inspector->setVisible(tool != nullptr);
            if (tool) {
                const qreal top = state.palette ? state.palette->sceneBoundingRect().bottom() + m : itop;
                const qreal w = state.palette ? state.palette->shape().boundingRect().width() : toolSize.width();
                const qreal h = std::min<qreal>(toolSize.height(), bottom - top);
                state.inspector->setGeometry(QRectF(r.width() - w - m, top, w, h));
            }
        }
    }

    // Scribble "Nur das Blatt": nur die Pille oben in der Mitte (und die Fensterknöpfe) bleiben
    const bool focus = state.scribbleMode && state.scribbleFocus;
    if (state.scribblePill) {
        state.scribblePill->setVisible(focus);
        const QSizeF ps = state.scribblePill->content()->sizeHint();
        state.scribblePill->setGeometry(QRectF((r.width() - ps.width()) / 2, m, ps.width(), std::max<qreal>(ps.height(), Token::BarHeight)));
    }
    if (focus) {
        for (QGraphicsItem* item : std::initializer_list<QGraphicsItem*> {state.header, state.browser, state.collapsedBar,
                                                                          state.scribblePalette, state.timeline, state.viewCube}) {
            if (item) {
                item->setVisible(false);
            }
        }
    }
    else {
        state.header->setVisible(true);
        if (state.viewCube) {
            state.viewCube->setVisible(true);
        }
    }
    if (state.scribbleActions && !state.scribbleMode) {
        state.scribbleActions->setVisible(false);
    }

    // Freier Teil der Ansicht, als Anteil: Fit All passt das Modell dort ein (View3DInventorViewer::viewBoundBox),
    // zwischen Seitenleiste und Panels rechts, unter der Kopfleiste und über der Timeline
    QRectF free(0, top, r.width(), (state.timeline && state.timeline->isVisible() ? state.timeline->pos().y() : r.height()) - top);
    for (GlassPanel* p : {state.browser, state.inspector, state.palette, state.scribblePalette}) {
        if (p && p->isVisible()) {
            const QRectF glass = p->mapRectToScene(p->shape().boundingRect());
            glass.center().x() < r.center().x() ? free.setLeft(std::max(free.left(), glass.right() + m))
                                                : free.setRight(std::min(free.right(), glass.left() - m));
        }
    }
    for (QGraphicsView* view : state.scene->views()) {
        view->setProperty("freeArea", QRectF(free.x() / r.width(), free.y() / r.height(), free.width() / r.width(),
                                             free.height() / r.height()));
    }
}

/// Browser (Seitenleiste links) ein-/ausklappen; der Zustand bleibt über Neustarts (MyCAD/BrowserHidden)
void toggleBrowser()
{
    auto grp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    grp->SetBool("BrowserHidden", !grp->GetBool("BrowserHidden", false));
    layout();
}

/// Klick in ein Zahlen- oder Textfeld wählt den ganzen Inhalt, Tippen überschreibt ihn. Erst danach auswählen: der
/// Mausklick selbst, der nach dem Fokus kommt, hebt die Auswahl sonst wieder auf.
class SelectFieldOnClick: public QObject
{
protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (event->type() != QEvent::FocusIn || static_cast<QFocusEvent*>(event)->reason() != Qt::MouseFocusReason) {
            return false;
        }
        if (auto box = qobject_cast<QAbstractSpinBox*>(obj)) {
            QTimer::singleShot(0, box, &QAbstractSpinBox::selectAll);
        }
        else if (auto line = qobject_cast<QLineEdit*>(obj); line && !line->isReadOnly()) {
            QTimer::singleShot(0, line, &QLineEdit::selectAll);
        }
        return false;
    }
};

/// Sketcher-Panel: im Skizzenmodus nur "Tool Parameters" zeigen, bei jedem Werkzeugwechsel neu anordnen
class SketchTaskFilter: public QObject
{
protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        const auto type = event->type();
        // In der Skizze schluckt der 3D-Viewer Tasten, bevor die Szene sie bekommt: an Suche oder Post-it mit Fokus durchreichen
        if ((type == QEvent::KeyPress || type == QEvent::KeyRelease) && qobject_cast<QGraphicsView*>(obj)) {
            if (searchField && searchField->hasFocus()) {
                QApplication::sendEvent(searchField, event);
                return true;
            }
            for (const NotePanel& note : state.notes) {
                if (note.edit->hasFocus()) {
                    QApplication::sendEvent(note.edit, event);
                    return true;
                }
            }
        }
        // Esc im 3D-Fenster bricht ein Panel ohne Bearbeitungsmodus (Appearance, Measure …) ab wie Cancel; Panels mit
        // Bearbeitungsmodus bekommen es über ViewProvider::eventCallback
        if (type == QEvent::KeyPress && static_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape
            && qobject_cast<View3DInventorViewer*>(obj) && Control().activeDialog()) {
            auto gdoc = Application::Instance->activeDocument();
            auto panel = Control().taskPanel();
            if (gdoc && !gdoc->getInEdit() && panel && !static_cast<View3DInventorViewer*>(obj)->isSelecting()) {
                QKeyEvent esc(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
                QApplication::sendEvent(panel, &esc);
                return true;
            }
        }
        // Esc beendet wie in Fusion das Skizzen-Werkzeug, auch wenn ein Maßfeld den Fokus hat (FreeCAD bricht dort
        // nur die Eingabe ab, und das nächste Feld holt sich den Fokus zurück)
        if (type == QEvent::KeyPress && state.sketchMode && static_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape
            && obj == QApplication::focusWidget() && obj != searchField  // Esc in der Suche schließt nur die Suche
            && (qobject_cast<QAbstractSpinBox*>(obj) || qobject_cast<QLineEdit*>(obj))
            && !qobject_cast<QDialog*>(static_cast<QWidget*>(obj)->window())) {  // Maß-Dialog: Esc verwirft wie Cancel
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
        // FreeCADs Sketcher-Panels (Sketch Edit, Constraints, Elements) gleich beim Einblenden verstecken, sonst
        // blitzen sie beim Betreten der Skizze und bei jedem Werkzeugstart ein Bild lang auf. Beim Betreten ist
        // state.sketchMode noch nicht gesetzt, die Skizze aber schon in Bearbeitung. Show ohne ShowToParent (der
        // Panel-Bereich selbst erscheint) erst im nächsten Durchlauf: mitten im Show-Event verstecken mag Qt nicht
        if ((type == QEvent::ShowToParent || type == QEvent::Show) && obj->inherits("Gui::TaskView::TaskBox")
            && QByteArray(obj->metaObject()->className()).startsWith("SketcherGui::")) {
            static const Base::Type sketch = Base::Type::fromName("Sketcher::SketchObject");
            auto gdoc = Application::Instance->activeDocument();
            auto vp = gdoc ? dynamic_cast<ViewProviderDocumentObject*>(gdoc->getInEdit()) : nullptr;
            if (state.sketchMode || (vp && !sketch.isBad() && vp->getObject()->getTypeId().isDerivedFrom(sketch))) {
                if (type == QEvent::ShowToParent) {
                    static_cast<QWidget*>(obj)->hide();
                }
                else {
                    QTimer::singleShot(0, static_cast<QWidget*>(obj), &QWidget::hide);
                }
            }
        }
        return false;
    }
};

/// Python-Ausdruck für ein Objekt (das Design-Modul hängt nicht an der Shell, die Shell spricht es über Python an)
std::string pyObject(const App::DocumentObject* obj)
{
    return "App.getDocument('" + std::string(obj->getDocument()->getName()) + "').getObject('"
        + obj->getNameInDocument() + "')";
}

/// Design-Funktion als eine Transaktion ausführen; Fehler (ValueError) als Hinweis zeigen. Liefert das Ergebnis
/// (repr) oder leer bei Fehler.
std::string runDesign(App::Document* doc, const char* transaction, const std::string& expr)
{
    doc->openTransaction(transaction);
    try {
        Base::PyGILStateLocker lock;
        const std::string result = Base::Interpreter().runStringWithKey(
            ("import FreeCAD as App, Design\n_r = repr(" + expr + ")").c_str(), "_r");
        doc->commitTransaction();
        return result;
    }
    catch (const Base::Exception& e) {
        doc->abortTransaction();
        QString text = QString::fromUtf8(e.what()).trimmed();
        static const QRegularExpression needs(QStringLiteral("It (needs|is needed by) (.*)$"));
        const auto m = needs.match(text);
        if (m.hasMatch()) {
            text = (m.captured(1) == QLatin1String("needs") ? T("This step cannot go before %1, which it needs.")
                                                            : T("This step cannot go after %1, which needs it."))
                       .arg(m.captured(2));
        }
        else {
            const int at = text.lastIndexOf(QLatin1String("Error: "));  // "ValueError: Text" -> "Text"
            if (at >= 0) {
                text = text.mid(at + 7);
            }
        }
        shellHint(T("Timeline"), text);
        return {};
    }
}

/// Gruppe eines Timeline-Eintrags ("" ohne)
QString timelineGroupOf(const App::DocumentObject* obj)
{
    auto prop = freecad_cast<App::PropertyString*>(obj->getPropertyByName("TimelineGroup"));
    return prop ? QString::fromUtf8(prop->getValue()) : QString();
}

/// Aufgeklappte Gruppen ("Dokument/Gruppe"); Gruppen sind anfangs zu wie in Fusion
std::set<std::string>& openTimelineGroups()
{
    static std::set<std::string> open;
    return open;
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

/// Rechenzeile eines Post-its ("120 / 4 =", ohne Text davor oder mit "Breite: 120 / 4 =", weitergerechnet
/// "120 / 4 = 30 * 2 ="). Rechnet mit FreeCADs Formel-Parser, also auch mit Einheiten und den Namen aus
/// "Change Parameters". Leer, wenn die Zeile keine Rechnung ist: dann bleibt das "=" einfach Text.
QString calculateLine(const NotePanel& note, QString line)
{
    App::DocumentObject* owner = note.object();
    if (!owner) {
        return {};
    }
    line.chop(1);  // das eben getippte "="
    line = line.mid(std::max(line.lastIndexOf(QLatin1Char(':')), line.lastIndexOf(QLatin1Char('='))) + 1).trimmed();
    static const QRegularExpression decimalComma(QStringLiteral(R"((\d),(\d))"));
    line.replace(decimalComma, QStringLiteral(R"(\1.\2)"));
    // ein bloßer Name ("Wand =") ist der Anfang einer Parameterzeile (Idee 3), keine Rechnung
    static const QRegularExpression name(QStringLiteral(R"(^[^\W\d]\w*$)"), QRegularExpression::UseUnicodePropertiesOption);
    if (line.isEmpty() || name.match(line).hasMatch()) {
        return {};
    }
    // Der Parser sucht bloße Namen am Besitzer: mit dem Parameter-Objekt als Besitzer gelten die Parameternamen
    for (auto obj : owner->getDocument()->getObjectsOfType(App::VarSet::getClassTypeId())) {
        if (std::strcmp(obj->Label.getValue(), "Parameters") == 0) {
            owner = obj;
        }
    }
    try {
        const App::ExpressionPtr result = App::Expression::parse(owner, line.toStdString())->eval();
        auto number = freecad_cast<App::NumberExpression*>(result.get());
        if (!number) {
            return {};
        }
        const Base::Quantity quantity = number->getQuantity();
        QString text = quantity.isDimensionless() ? QString::number(quantity.getValue(), 'g', 10)
                                                  : QString::fromStdString(quantity.getUserString());
        return language() == QLatin1String("German") ? text.replace(QLatin1Char('.'), QLatin1Char(',')) : text;
    }
    catch (const Base::Exception&) {
        return {};  // keine Rechnung, z. B. "Breite = " ohne so einen Parameter
    }
    catch (const std::exception&) {
        return {};
    }
}

/// Idee 3: Zeilen "Name = Ausdruck" der Notiz sind Parameter (Design.syncNoteParameters legt an, löscht, schreibt
/// Werte und Fehler dahinter). Fehlerhinweise schreibt das Design englisch: hier hin und zurück übersetzt.
void syncNoteParameters(App::DocumentObject* obj, QPlainTextEdit* edit)
{
    auto text = obj ? static_cast<App::PropertyString*>(obj->getPropertyByName("Text")) : nullptr;
    auto defines = obj ? obj->getPropertyByName("Defines") : nullptr;
    if (!text || !defines || (!std::strchr(text->getValue(), '=') && static_cast<App::PropertyStringList*>(defines)->getSize() == 0)) {
        return;  // keine Zeile mit "=" und nichts angelegt: nichts abzugleichen
    }
    static const char* hints[] = {"Already defined in", "This name is used twice", "Choose another name",
                                  "Not a value or formula", " is still used by "};
    QString value = QString::fromUtf8(text->getValue());
    for (const char* hint : hints) {
        value.replace(T(hint), QString::fromUtf8(hint));
    }
    text->setValue(value.toStdString());
    runDesign(obj->getDocument(), "Change Parameters", "Design.syncNoteParameters(" + pyObject(obj) + ")");
    value = QString::fromUtf8(text->getValue());
    for (const char* hint : hints) {
        value.replace(QString::fromUtf8(hint), T(hint));
    }
    text->setValue(value.toStdString());
    if (edit->toPlainText() != value) {  // Hinweise sind dazugekommen: Text erneuern, Schreibstelle behalten
        const QTextCursor old = edit->textCursor();
        const int line = old.blockNumber();
        const int column = old.positionInBlock();
        const QSignalBlocker block(edit);
        edit->setPlainText(value);
        QTextCursor cursor(edit->document()->findBlockByNumber(std::min(line, edit->document()->blockCount() - 1)));
        cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, std::min(column, cursor.block().length() - 1));
        edit->setTextCursor(cursor);
    }
}

/// Textfeld im Post-it: "=" am Zeilenende rechnet, Esc gibt die Tastatur an die 3D-Ansicht zurück
class NoteEdit: public QPlainTextEdit
{
public:
    std::function<QString(const QString&)> calculate;
    std::function<void()> finished;  ///< Zeile fertig (Enter) oder Notiz verlassen: Parameter abgleichen

protected:
    void focusOutEvent(QFocusEvent* event) override
    {
        QPlainTextEdit::focusOutEvent(event);
        finished();
    }

    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Escape) {
            if (state.scene) {
                state.scene->clearFocus();
            }
            return;
        }
        QPlainTextEdit::keyPressEvent(event);
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            finished();
            return;
        }
        QTextCursor cursor = textCursor();
        if (event->text() == QLatin1String("=") && cursor.atBlockEnd()) {
            const QString result = calculate(cursor.block().text());
            if (!result.isEmpty()) {
                cursor.insertText(QLatin1Char(' ') + result);
            }
        }
    }
};

/// Post-it am Titel ziehen
class NoteGrip: public QObject
{
public:
    NoteGrip(GlassPanel* panel, std::function<App::DocumentObject*()> object, QObject* parent)
        : QObject(parent)
        , panel(panel)
        , object(std::move(object))
    {}

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        const auto type = event->type();
        if (type != QEvent::MouseButtonPress && type != QEvent::MouseMove && type != QEvent::MouseButtonRelease) {
            return false;
        }
        // Griffpunkt im Panel; bleibt beim Ziehen gleich, die Maus in der Szene ist Panel-Lage + dieser Punkt
        const QPointF inPanel = static_cast<QMouseEvent*>(event)->position() + static_cast<QWidget*>(obj)->pos();
        const QPointF scene = panel->pos() + inPanel;
        if (type == QEvent::MouseButtonPress) {
            grab = inPanel;
            dragging = true;
        }
        else if (type == QEvent::MouseButtonRelease) {
            dragging = false;
        }
        else if (dragging && state.scene) {
            if (App::DocumentObject* note = object()) {
                setNotePosition(note, scene - grab, state.scene->sceneRect());
                panel->setGeometry(noteRect(note, state.scene->sceneRect()));
            }
        }
        return true;
    }

private:
    GlassPanel* panel;
    std::function<App::DocumentObject*()> object;
    QPointF grab;
    bool dragging = false;
};

NotePanel makeNotePanel(App::DocumentObject* obj)
{
    NotePanel note;
    note.doc = obj->getDocument()->getName();
    note.name = obj->getNameInDocument();
    const auto find = [note] { return note.object(); };

    auto box = content();
    auto lay = new QVBoxLayout(box);
    lay->setContentsMargins(8, 8, 8, 8);
    lay->setSpacing(0);
    auto head = new QWidget;
    auto headLay = new QHBoxLayout(head);
    headLay->setContentsMargins(0, 0, 0, 0);
    note.title = new QLabel;
    note.title->setObjectName(QStringLiteral("NoteTitle"));
    setTextStyle(note.title, Text::Headline);
    note.title->setContentsMargins(10, 0, 0, 0);
    note.title->setAttribute(Qt::WA_TransparentForMouseEvents);
    headLay->addWidget(note.title, 1);
    auto close = new QToolButton;
    close->setObjectName(QStringLiteral("NoteClose"));
    close->setIcon(designIcon(QStringLiteral("Window_Close"), &Theme::noteLabel));
    close->setIconSize(QSize(Token::IconM, Token::IconM));
    close->setFixedSize(28, 28);
    close->setToolTip(T("Close Note"));
    close->setAccessibleName(T("Close Note"));
    QObject::connect(close, &QToolButton::clicked, close, [find] {
        QTimer::singleShot(0, [find] {  // nicht mitten im Klick das Panel abbauen
            if (App::DocumentObject* obj = find()) {
                obj->Visibility.setValue(false);
            }
        });
    });
    headLay->addWidget(close);
    lay->addWidget(head);

    auto edit = new NoteEdit;
    edit->calculate = [note](const QString& line) { return calculateLine(note, line); };
    edit->setObjectName(QStringLiteral("NoteText"));
    edit->finished = [find, edit] { syncNoteParameters(find(), edit); };
    edit->setPlaceholderText(T("Write here, calculate (120 / 4 =) or define a parameter (Wall = 2 mm)"));
    edit->setTabChangesFocus(true);
    edit->document()->setDocumentMargin(10);  // Text beginnt bündig mit dem Titel
    setTextStyle(edit, Text::Body);
    note.edit = edit;
    lay->addWidget(edit, 1);
    box->setFixedSize(NoteWidth, NoteHeight);

    note.panel = new GlassPanel(box, Token::RadiusPanel, true);  // mehrzeiliger Text steht auf Text-Glas (GV-2)
    note.panel->setSurface(&Theme::noteSurface);
    note.panel->setZValue(20);  // über den anderen Panels
    head->installEventFilter(new NoteGrip(note.panel, find, head));

    // Text direkt ins Objekt: ohne Speicher-Schritt, das Design gilt dadurch als geändert
    QObject::connect(edit, &QPlainTextEdit::textChanged, edit, [find, edit] {
        if (App::DocumentObject* obj = find()) {
            auto text = static_cast<App::PropertyString*>(obj->getPropertyByName("Text"));
            const std::string value = edit->toPlainText().toStdString();
            if (value != text->getValue()) {
                text->setValue(value);
            }
        }
    });
    return note;
}

bool isNote(const App::DocumentObject* obj)
{
    // nicht als static: die Shell startet vor dem Design-Modul
    const Base::Type type = Base::Type::fromName("Design::Note");
    return !type.isBad() && obj->getTypeId().isDerivedFrom(type);
}

/// Post-its auf dem Bildschirm an das aktive Design anpassen: offene zeigen, alle anderen abbauen
void syncNotes()
{
    App::Document* doc = App::GetApplication().getActiveDocument();
    const std::string docName = doc ? doc->getName() : std::string();
    const bool sameDesign = docName == state.notesDocument;
    state.notesDocument = docName;
    std::erase_if(state.notes, [&docName](const NotePanel& note) {
        App::DocumentObject* obj = note.doc == docName ? note.object() : nullptr;
        if (obj && obj->Visibility.getValue()) {
            return false;
        }
        if (QGraphicsScene* scene = note.panel->scene()) {
            scene->removeItem(note.panel);
        }
        note.panel->deleteLater();
        return true;
    });
    for (auto obj : doc ? doc->getObjects() : std::vector<App::DocumentObject*>()) {
        if (!isNote(obj) || !obj->Visibility.getValue()) {
            continue;
        }
        const std::string name = obj->getNameInDocument();
        auto note = std::find_if(state.notes.begin(), state.notes.end(), [&name](const NotePanel& n) { return n.name == name; });
        const bool created = note == state.notes.end();
        if (created) {
            state.notes.push_back(makeNotePanel(obj));
            note = std::prev(state.notes.end());
            if (state.scene) {
                state.scene->addItem(note->panel);
            }
        }
        note->title->setText(QString::fromUtf8(obj->Label.getValue()));
        const QString text = QString::fromUtf8(static_cast<App::PropertyString*>(obj->getPropertyByName("Text"))->getValue());
        if (note->edit->toPlainText() != text) {
            note->edit->setPlainText(text);
        }
        if (created && sameDesign) {  // eben geöffnet (nicht: Design gewechselt oder Datei geladen): gleich lostippen
            // erst wenn das Panel in der Szene liegt und seine Lage hat; die Szene gibt den Fokus nur so weiter
            QTimer::singleShot(0, note->edit, [panel = note->panel, edit = note->edit] {
                panel->setFocus();
                edit->setFocus();
            });
        }
    }
}

// --- Befehlssuche (Strg+K) ---------------------------------------------------------------------------------------

/// Weitere Suchwörter je Befehl: deutsch und englisch, dazu Begriffe aus anderen CAD-Programmen
const std::map<std::string, std::vector<std::string>>& searchSynonyms()
{
    static const std::map<std::string, std::vector<std::string>> words = {
        {"Design_Extrude", {"extrudieren", "pad", "pocket", "ziehen", "block", "platte", "tasche"}},
        {"Design_Hole", {"loch", "bohren", "drill", "bore", "gewindebohrung", "senkung", "screw hole"}},
        {"Design_Thread", {"gewinde", "schraube", "bolt", "screw", "mutter", "nut", "druckgewinde"}},
        {"Design_Fastener", {"schraube hier", "schraube", "verschrauben", "screw", "bolt", "einschmelzmutter", "gewindeeinsatz",
                             "heat-set insert", "mutterfalle", "nut trap", "zylinderkopf", "senkkopf", "fastener"}},
        {"Design_RemoveFace", {"flaeche entfernen", "flaeche loeschen", "delete face", "remove face", "defeature",
                               "fase entfernen", "rundung entfernen", "bohrung schliessen", "weg"}},
        {"Design_RedPen", {"rotstift", "korrektur", "korrigieren", "anmerken", "markup", "red pen", "redline", "handschrift",
                           "aufs modell schreiben"}},
        {"Design_PrintView", {"druckansicht", "ueberhang", "overhang", "stuetzen", "support", "wandstaerke", "duenne wand",
                              "druckbar", "printable", "3d-druck pruefen"}},
        {"Design_PrintDown", {"druckrichtung", "auf das bett", "unterseite", "flach hinlegen", "lay flat", "print direction",
                              "orientierung", "orientation"}},
        {"Design_Print", {"drucken", "slicer", "3d-drucker", "orcaslicer", "bambu", "prusaslicer", "cura", "print", "printer"}},
        {"Design_Fit", {"passung", "spiel", "toleranz", "h7", "presspassung", "spielpassung", "clearance", "tolerance",
                        "druckspiel", "press fit"}},
        {"Design_Fillet", {"runden", "abrunden", "rundung", "round", "radius"}},
        {"Design_Chamfer", {"fase", "anfasen", "bevel"}},
        {"Design_Shell", {"aushoehlen", "hohl", "wandstaerke", "hollow"}},
        {"Design_PressPull", {"druecken", "ziehen", "offset face", "push pull"}},
        {"Design_Combine", {"boolean", "vereinigen", "abziehen", "union", "subtract", "schneiden"}},
        {"Design_Mirror", {"spiegeln", "symmetrisch", "symmetry"}},
        {"Design_Pattern", {"muster", "array", "kopien", "wiederholen", "reihe"}},
        {"Design_Move", {"verschieben", "drehen", "rotate", "translate", "bewegen"}},
        {"Design_Measure", {"messen", "abstand", "distance", "masse", "gewicht", "weight", "mass", "volumen"}},
        {"Design_Appearance", {"farbe", "material", "color", "werkstoff", "aussehen"}},
        {"Design_Parameters", {"parameter", "variable", "formel", "formula", "change parameters"}},
        {"Design_CreateSketch", {"skizze", "zeichnen", "draw", "sketch"}},
        {"Design_Export", {"stl", "3mf", "step", "dxf", "speichern als", "save as"}},
        {"Design_Import", {"einfuegen", "step", "dxf", "svg", "insert"}},
        {"Design_Note", {"notiz", "post-it", "rechnen", "taschenrechner", "calculator"}},
        {"Design_Scribble", {"stift", "pen", "idee", "zeichnen", "skizzieren", "handschrift"}},
        {"Design_Joint", {"gelenk", "verbindung", "baugruppe", "assembly"}},
        {"Design_NewComponent", {"komponente", "teil", "part", "baugruppe"}},
        {"Design_Section", {"schnitt", "schnittansicht", "clip"}},
        {"Design_Revolve", {"drehen", "rotieren", "lathe", "drehteil"}},
        {"Design_Loft", {"uebergang", "aushaengen"}},
        {"Design_Sweep", {"pfad", "rohr", "pipe"}},
        {"MyCAD_Settings", {"einstellungen", "optionen", "preferences", "sprache", "language"}},
    };
    return words;
}

ParameterGrp::handle shellParams()
{
    return App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
}

/// zuletzt benutzte Suchtreffer, neuester zuerst (höchstens 8)
std::vector<std::string> recentSearches()
{
    std::vector<std::string> keys;
    std::stringstream in(shellParams()->GetASCII("RecentSearches", ""));
    for (std::string key; std::getline(in, key, '\n');) {
        if (!key.empty()) {
            keys.push_back(key);
        }
    }
    return keys;
}

void rememberSearch(const std::string& key)
{
    auto keys = recentSearches();
    std::erase(keys, key);
    keys.insert(keys.begin(), key);
    keys.resize(std::min<size_t>(keys.size(), 8));
    std::string out;
    for (const auto& k : keys) {
        out += k + "\n";
    }
    shellParams()->SetASCII("RecentSearches", out.c_str());
}

struct SearchHit
{
    std::string key;  ///< Befehlsname oder "Dokument/Objekt"
    QString label;
    QString detail;   ///< Tastenkürzel oder Art des Objekts
    QIcon icon;
    std::function<void()> run;
    int score = 0;
};

GlassPanel* searchPanel = nullptr;
QLineEdit* searchField = nullptr;
QListWidget* searchList = nullptr;
std::vector<SearchHit> searchHits;

void hideSearch()
{
    if (searchPanel && searchPanel->isVisible()) {
        searchPanel->hide();
        if (auto view = qobject_cast<View3DInventor*>(getMainWindow()->activeWindow())) {
            view->getViewer()->setFocus();  // Tasten wieder an die 3D-Ansicht
        }
    }
}

void runSearchHit(int row)
{
    if (row < 0 || row >= int(searchHits.size())) {
        return;
    }
    const SearchHit hit = searchHits[row];
    hideSearch();
    rememberSearch(hit.key);
    QTimer::singleShot(0, hit.run);  // nicht im Tastenereignis der Suche
}

/// Treffer zur Eingabe: Befehle, die gerade gehen, und Körper, Skizzen und Parameter des aktiven Designs
void refreshSearch()
{
    const std::string query = searchField->text().toStdString();
    const auto recent = recentSearches();
    std::vector<SearchHit> hits;
    static const std::set<std::string> standard = {"Std_New", "Std_Open", "Std_Save", "Std_SaveAs", "Std_Undo", "Std_Redo",
                                              "Std_ViewFitAll", "Std_ViewIsometric", "Std_ViewTop", "Std_ViewFront",
                                              "Std_ViewRight", "MyCAD_Settings"};
    for (Gui::Command* cmd : Application::Instance->commandManager().getAllCommands()) {
        const std::string name = cmd->getName();
        const bool sketch = name.rfind("Sketcher_", 0) == 0;
        const bool design = name.rfind("Design_", 0) == 0 && name.rfind("Design_Scribble", 0) != 0;
        // Gruppenbefehle (Sketcher_CompCreateRegularPolygon …) nicht: sie führen nur ihre zuletzt gewählte Variante aus
        // und doppelten die Varianten in der Liste ("Polygon" zeichnete ein Dreieck)
        if ((!design && !standard.contains(name) && !(sketch && state.sketchMode)) || name == "MyCAD_Search"
            || !cmd->isActive() || dynamic_cast<GroupCommand*>(cmd)) {
            continue;
        }
        const char* english = cmd->getMenuText();
        if (!english || !*english) {
            continue;
        }
        QString label = T(english);
        label.remove(QLatin1Char('&'));
        auto synonyms = searchSynonyms().contains(name) ? searchSynonyms().at(name) : std::vector<std::string>();
        synonyms.push_back(name);
        // auch der deutsche Name, in jeder Sprache: die Hilfe verspricht Suche auf Deutsch oder Englisch
        const int score = CommandSearch::score(query, {label.toStdString(), english, german(english).toStdString()}, synonyms);
        if (score > 0) {
            const char* accel = cmd->getAccel();
            hits.push_back({name, label, QKeySequence(QString::fromLatin1(accel ? accel : "")).toString(QKeySequence::NativeText),
                            commandIcon(QString::fromLatin1(name), QIcon()), [name] {
                                Application::Instance->commandManager().runCommandByName(name.c_str());
                            }, score});
        }
    }
    if (App::Document* doc = App::GetApplication().getActiveDocument()) {  // leer: zuletzt benutzte Körper und Skizzen
        static const Base::Type body = Base::Type::fromName("Design::Body");
        static const Base::Type sketch = Base::Type::fromName("Sketcher::SketchObject");
        for (App::DocumentObject* obj : doc->getObjects()) {
            const bool isBody = !body.isBad() && obj->getTypeId().isDerivedFrom(body);
            const bool isSketch = !sketch.isBad() && obj->getTypeId().isDerivedFrom(sketch);
            if (!isBody && !isSketch) {
                continue;
            }
            const int score = CommandSearch::score(query, {obj->Label.getValue()});
            if (score > 0) {
                const App::DocumentObjectT ref(obj);
                hits.push_back({std::string(doc->getName()) + "/" + obj->getNameInDocument(),
                                QString::fromUtf8(obj->Label.getValue()), isBody ? T("Body") : T("Sketch"),
                                commandIcon(isBody ? QStringLiteral("Design_Body") : QStringLiteral("Design_CreateSketch"), QIcon()),
                                [ref, isBody] {
                                    auto o = ref.getObject();
                                    if (!o) {
                                        return;
                                    }
                                    Selection().clearSelection();
                                    Selection().addSelection(o->getDocument()->getName(), o->getNameInDocument());
                                    auto gd = Application::Instance->getDocument(o->getDocument());
                                    if (isBody) {
                                        Application::Instance->commandManager().runCommandByName("Std_ViewFitSelection");
                                    }
                                    else if (gd) {
                                        gd->setEdit(gd->getViewProvider(o));
                                    }
                                },
                                score});
            }
        }
    }
    // Beste Treffer zuerst; bei gleicher Güte die zuletzt benutzten
    const auto rank = [&recent](const SearchHit& h) {
        const auto it = std::ranges::find(recent, h.key);
        return h.score * 10 + (it == recent.end() ? 0 : 8 - int(it - recent.begin()));
    };
    std::ranges::stable_sort(hits, [&rank](const SearchHit& a, const SearchHit& b) { return rank(a) > rank(b); });
    if (query.empty()) {  // ohne Eingabe nur die zuletzt benutzten
        std::erase_if(hits, [&recent](const SearchHit& h) { return std::ranges::find(recent, h.key) == recent.end(); });
    }
    hits.resize(std::min<size_t>(hits.size(), 10));
    searchHits = hits;
    searchList->clear();
    for (const auto& h : searchHits) {
        auto item = new QListWidgetItem(h.icon, h.detail.isEmpty() ? h.label : h.label + QStringLiteral("    ") + h.detail);
        item->setData(Qt::AccessibleTextRole, h.label);
        item->setData(Qt::UserRole, QString::fromStdString(h.key));
        searchList->addItem(item);
    }
    searchList->setCurrentRow(searchHits.empty() ? -1 : 0);
    searchList->setVisible(!searchHits.empty());
    searchPanel->content()->adjustSize();
    layout();
}

/// Pfeiltasten und Enter im Suchfeld steuern die Liste, Esc schließt
class SearchKeys: public QObject
{
protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (event->type() == QEvent::FocusOut && obj == searchField) {
            QTimer::singleShot(0, [] {  // Klick daneben schließt (Klick in die Liste nicht)
                if (searchPanel && !searchList->hasFocus() && !searchField->hasFocus()) {
                    hideSearch();
                }
            });
        }
        if (event->type() != QEvent::KeyPress) {
            return false;
        }
        const int key = static_cast<QKeyEvent*>(event)->key();
        const int row = searchList->currentRow();
        if (key == Qt::Key_Down || key == Qt::Key_Up) {
            const int next = std::clamp(row + (key == Qt::Key_Down ? 1 : -1), 0, std::max(0, searchList->count() - 1));
            searchList->setCurrentRow(next);
            return true;
        }
        if (key == Qt::Key_Return || key == Qt::Key_Enter) {
            runSearchHit(row);
            return true;
        }
        if (key == Qt::Key_Escape) {
            hideSearch();
            return true;
        }
        return false;
    }
};

void showCommandSearch()
{
    if (!state.scene) {
        return;
    }
    if (!searchPanel) {
        auto box = new QWidget;
        box->setObjectName(QStringLiteral("CommandSearch"));
        box->setFixedWidth(520);
        auto lay = new QVBoxLayout(box);
        lay->setContentsMargins(12, 12, 12, 12);
        lay->setSpacing(8);
        searchField = new QLineEdit;
        searchField->setPlaceholderText(T("Search commands and the design"));
        searchField->setAccessibleName(T("Search"));
        searchField->setClearButtonEnabled(true);
        searchList = new QListWidget;
        searchList->setAccessibleName(T("Results"));
        searchList->setFrameShape(QFrame::NoFrame);
        searchList->setIconSize(QSize(Token::IconL, Token::IconL));
        searchList->setFocusPolicy(Qt::NoFocus);
        searchList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        searchList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lay->addWidget(searchField);
        lay->addWidget(searchList);
        static SearchKeys keys;
        searchField->installEventFilter(&keys);
        QObject::connect(searchField, &QLineEdit::textChanged, searchField, [] { refreshSearch(); });
        QObject::connect(searchList, &QListWidget::itemClicked, searchList,
                         [](QListWidgetItem* item) { runSearchHit(searchList->row(item)); });
        searchPanel = new GlassPanel(box, Token::RadiusPanel, true);
        searchPanel->setZValue(10);  // über Inspector und Timeline
    }
    if (searchPanel->scene() != state.scene) {
        state.scene->addItem(searchPanel);
    }
    searchPanel->show();  // erst sichtbar, dann auslegen: sonst bekommt das Glas die Größe vor dem Inhalt
    searchField->clear();
    refreshSearch();
    searchField->setFocus();
}

}  // namespace

namespace
{
QStringList& quietlyCreated()
{
    static QStringList files;  // still angelegte Designs dieser Sitzung
    return files;
}
}  // namespace

void Gui::Shell::savedAs(const QString& before, const QString& after)
{
    const QFileInfo old(before), now(after);
    if (before.isEmpty() || old == now || !quietlyCreated().contains(old.absoluteFilePath())) {
        return;
    }
    quietlyCreated().removeAll(old.absoluteFilePath());
    // Versionen mitnehmen (DesignVersions: versions/<Name> neben der Datei)
    const QString from = old.absolutePath() + QStringLiteral("/versions/") + old.completeBaseName();
    const QString to = now.absolutePath() + QStringLiteral("/versions/") + now.completeBaseName();
    if (QDir(from).exists() && !QDir(to).exists()) {
        QDir().mkpath(now.absolutePath() + QStringLiteral("/versions"));
        QDir().rename(from, to);
    }
    // der alte Ordner gehört nur diesem Design (so legt saveQuietly ihn an): in den Papierkorb, nicht löschen
    const QDir folder = old.absoluteDir();
    if (folder.dirName() == old.completeBaseName() && QDir(projectsFolder()) == QDir(QFileInfo(folder.absolutePath()).absolutePath())
        && !now.absoluteFilePath().startsWith(folder.absolutePath() + QLatin1Char('/'))) {
        QFile::moveToTrash(folder.absolutePath());
    }
}

bool Gui::Shell::inOwnFolder(const QString& file)
{
    const QFileInfo fi(file);
    const QDir dir = fi.absoluteDir();
    return dir.dirName() == fi.completeBaseName() && QDir(projectsFolder()) == QDir(QFileInfo(dir.absolutePath()).absolutePath());
}

QString Gui::Shell::renameDesignFile(const QString& file, const QString& wanted, QString& error)
{
    const QFileInfo fi(file);
    QString name = wanted.trimmed();
    static const QRegularExpression unsafe(QStringLiteral(R"([/\\:*?"<>|])"));  // wie saveQuietly
    name.remove(unsafe);
    if (name.isEmpty() || name.startsWith(QLatin1Char('.'))) {
        error = T("“%1” is not a valid name.").arg(wanted);
        return {};
    }
    const QDir dir = fi.absoluteDir();
    const bool ownFolder = inOwnFolder(file);
    const QString newFolder = ownFolder ? QFileInfo(dir.absolutePath()).absolutePath() + QLatin1Char('/') + name : dir.absolutePath();
    const QString newFile = newFolder + QLatin1Char('/') + name + QLatin1Char('.') + fi.suffix();
    if (newFile == fi.absoluteFilePath()) {
        return newFile;
    }
    if (QFileInfo::exists(ownFolder ? newFolder : newFile)) {
        error = T("“%1” already exists. Choose another name.").arg(name);
        return {};
    }
    const QString renamed = dir.absoluteFilePath(name + QLatin1Char('.') + fi.suffix());
    if (!QFile::rename(file, renamed) || (ownFolder && !QDir().rename(dir.absolutePath(), newFolder))) {
        QFile::rename(renamed, file);  // halb umbenannt: zurück
        error = T("“%1” could not be renamed. Check that you can write to %2.").arg(fi.completeBaseName(), dir.absolutePath());
        return {};
    }
    QDir(newFolder).rename(QStringLiteral("versions/") + fi.completeBaseName(), QStringLiteral("versions/") + name);
    auto mru = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/RecentFiles");
    for (const auto& [key, value] : mru->GetASCIIMap("MRU")) {
        const QString path = QFileInfo(QString::fromUtf8(value.c_str())).absoluteFilePath();
        if (path == fi.absoluteFilePath()) {
            mru->SetASCII(key.c_str(), newFile.toUtf8().constData());
        }
        else if (path == newFile) {
            mru->RemoveASCII(key.c_str());  // alter Eintrag gleichen Namens: sonst stünde das Design zweimal unter Recent
        }
    }
    mru->SetInt("RecentFiles", mru->GetInt("RecentFiles", 4));  // meldet es RecentFilesAction, sonst schreibt sie den alten Pfad zurück
    for (QString& f : quietlyCreated()) {
        if (f == fi.absoluteFilePath()) {
            f = newFile;
        }
    }
    // ein offenes Design zeigt auf die neue Datei und heißt wie sie
    for (App::Document* doc : App::GetApplication().getDocuments()) {
        if (QFileInfo(QString::fromUtf8(doc->FileName.getValue())).absoluteFilePath() == fi.absoluteFilePath()) {
            doc->FileName.setValue(newFile.toUtf8().constData());
            if (QString::fromUtf8(doc->Label.getValue()) != wanted.trimmed()) {
                doc->Label.setValue(name.toUtf8().constData());
            }
        }
    }
    return newFile;
}

void Gui::Shell::labelEdited(App::Document* doc)
{
    // nach dem Editor: eine Meldung mitten im Schließen des Editors ginge verloren
    QTimer::singleShot(0, [name = std::string(doc->getName())] {
        App::Document* doc = App::GetApplication().getDocument(name.c_str());
        const QString file = doc ? QString::fromUtf8(doc->FileName.getValue()) : QString();
        if (file.isEmpty()) {
            return;  // noch nie gespeichert: das stille Speichern nimmt den Namen ohnehin
        }
        const QString label = QString::fromUtf8(doc->Label.getValue());
        QString error;
        if (renameDesignFile(file, label, error).isEmpty()) {
            doc->Label.setValue(QFileInfo(file).completeBaseName().toUtf8().constData());  // Name passt wieder zur Datei
            QMessageBox::warning(getMainWindow(), T("Rename Design"), error);
        }
    });
}

/// Idee 7: Varianten im Browser umschalten (Kontextmenü des Designs): Hauptdesign und Varianten, die offene mit Haken
namespace
{
/// Text als Python-Zeichenkette in einfachen Anführungszeichen
std::string pyQuoted(QString s)
{
    s.replace(QLatin1Char('\\'), QStringLiteral("\\\\")).replace(QLatin1Char('\''), QStringLiteral("\\'"));
    return "'" + s.toStdString() + "'";
}
}  // namespace

void addVariantMenu(QMenu* menu, App::Document* doc, const std::function<void(const char*)>& run)
{
    const std::string name = doc->getName();
    const QString file = QString::fromUtf8(doc->FileName.getValue());
    QStringList entries;  // je Zeile "Titel<Tab>Pfad", das Hauptdesign ohne Titel
    if (!file.isEmpty()) {
        try {
            Base::PyGILStateLocker lock;
            const std::string r = Base::Interpreter().runStringWithKey(
                ("import DesignVersions\n_p = " + pyQuoted(file)
                 + "\n_r = '\\n'.join(['\\t' + DesignVersions.main_of(_p)] + [v['name'] + '\\t' + v['path'] for v in "
                   "DesignVersions.variants(_p)])")
                    .c_str(),
                "_r");
            entries = QString::fromStdString(r).split(QLatin1Char('\n'), Qt::SkipEmptyParts);
        }
        catch (const Base::Exception& e) {
            Base::Console().warning("Variants: %s\n", e.what());
        }
    }
    const QFileInfo open(file);
    for (const QString& entry : entries) {
        const QString title = entry.section(QLatin1Char('\t'), 0, 0), path = entry.section(QLatin1Char('\t'), 1);
        QAction* action = menu->addAction(title.isEmpty() ? T("Main design") : title);
        action->setCheckable(true);
        action->setChecked(QFileInfo(path) == open);
        QObject::connect(action, &QAction::triggered, [name, path, open] {
            if (QFileInfo(path) == open) {
                return;
            }
            QTimer::singleShot(0, [name, path] {
                try {
                    Base::PyGILStateLocker lock;
                    Base::Interpreter().runString(("import DesignVersions, FreeCAD as App\nDesignVersions.switch(App.getDocument('"
                                                   + name + "'), " + pyQuoted(path) + ")")
                                                      .c_str());
                }
                catch (const Base::Exception& e) {
                    shellHint(T("Variants"), QString::fromUtf8(e.what()));
                }
            });
        });
    }
    if (!entries.isEmpty()) {
        menu->addSeparator();
    }
    QObject::connect(menu->addAction(T("Versions and Variants…")), &QAction::triggered, [run] { run("Design_Versions"); });
}

bool Gui::Shell::alwaysSave()
{
    return App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetBool("AlwaysSave", true);
}

bool Gui::Shell::saveQuietly(App::Document* doc, const QString& title)
{
    bool ok = false;
    try {
        if (!*doc->FileName.getValue()) {
            QString name = QString::fromUtf8(doc->Label.getValue()).trimmed();
            static const QRegularExpression unsafe(QStringLiteral(R"([/\\:*?"<>|])"));
            name.remove(unsafe);
            if (name.isEmpty()) {
                name = QStringLiteral("Design");
            }
            QDir projects(projectsFolder());
            QString folder = name;
            for (int n = 2; projects.exists(folder); ++n) {
                folder = QStringLiteral("%1 %2").arg(name).arg(n);
            }
            projects.mkpath(folder);
            const QString file = projects.filePath(folder + QLatin1Char('/') + folder + QStringLiteral(".mycad"));
            ok = doc->saveAs(file.toUtf8().constData());
            if (ok) {
                quietlyCreated() << QFileInfo(file).absoluteFilePath();
                getMainWindow()->appendRecentFile(file);  // Startseite "Recent" wie nach Speichern unter
            }
        }
        else {
            ok = doc->save();
        }
    }
    catch (const Base::Exception& e) {
        Base::Console().error("Save: %s\n", e.what());
        ok = false;
    }
    if (!ok) {
        return false;
    }
    if (Gui::Document* gdoc = Application::Instance->getDocument(doc)) {
        gdoc->setModified(false);
    }
    QString t = title;
    t.replace(QLatin1Char('\\'), QStringLiteral("\\\\")).replace(QLatin1Char('\''), QStringLiteral("\\'"));
    try {
        Base::PyGILStateLocker lock;
        Base::Interpreter().runString(("import DesignVersions, FreeCAD as App\nDesignVersions.snapshot(App.getDocument('"
                                       + std::string(doc->getName()) + "'), '" + t.toStdString() + "')")
                                          .c_str());
    }
    catch (const Base::Exception& e) {
        Base::Console().warning("Version: %s\n", e.what());
    }
    return true;
}

namespace
{
/// Idee 7: nach jeder abgeschlossenen Aktion speichern, sobald MyCAD 2 s ruht (nicht mitten in einem Werkzeug-Dialog,
/// nicht beim Ziehen)
void startAlwaysSave()
{
    static std::map<std::string, qint64> lastChange;
    App::GetApplication().signalChangedObject.connect([](const App::DocumentObject& obj, const App::Property&) {
        if (const App::Document* doc = obj.getDocument()) {
            lastChange[doc->getName()] = QDateTime::currentMSecsSinceEpoch();
        }
    });
    auto timer = new QTimer(getMainWindow());
    timer->setInterval(1000);
    QObject::connect(timer, &QTimer::timeout, timer, [] {
        // nur in der Hauptschleife: in einer verschachtelten (Kamera-Animation, Dialog) würde das Speichern samt
        // Vorschaubild mitten in die laufende Darstellung greifen
        if (!alwaysSave() || Control().activeDialog() || QApplication::mouseButtons() != Qt::NoButton
            || QApplication::activeModalWidget() || QThread::currentThread()->loopLevel() > 1) {
            return;
        }
        const qint64 now = QDateTime::currentMSecsSinceEpoch();
        for (App::Document* doc : App::GetApplication().getDocuments()) {
            Gui::Document* gdoc = Application::Instance->getDocument(doc);
            // offene Transaktion: mitten in einer Aktion (Werkzeug, Vorschau des Rotstifts) – erst danach speichern
            if (!gdoc || !gdoc->isModified() || doc->hasPendingTransaction() || doc->testStatus(App::Document::TempDoc)
                || doc->testStatus(App::Document::PartialDoc) || now - lastChange[doc->getName()] < 2000) {
                continue;
            }
            saveQuietly(doc);
        }
    });
    timer->start();
}

/// "Version sichern…" (Strg+S): speichern ist ohnehin immer; hier bekommt der Stand einen Namen
class CmdSaveVersion: public Gui::Command
{
public:
    CmdSaveVersion()
        : Command("MyCAD_SaveVersion")
    {
        sGroup = "File";
        sMenuText = "Save Version";
        sToolTipText = "Save Version: your design is always saved; give this state a name to find it again";
        sStatusTip = sToolTipText;
        sWhatsThis = "MyCAD_SaveVersion";
        sPixmap = "Std_Save";
        sAccel = "Ctrl+S";
        eType = 0;
    }
    const char* className() const override
    {
        return "CmdSaveVersion";
    }

protected:
    bool isActive() override
    {
        return App::GetApplication().getActiveDocument() != nullptr;
    }
    void activated(int) override
    {
        App::Document* doc = App::GetApplication().getActiveDocument();
        bool ok = false;
        const QString title = QInputDialog::getText(getMainWindow(), T("Save Version"),
                                                    T("Name of this version, e.g. “Before the holes”:"), QLineEdit::Normal,
                                                    QString(), &ok);
        if (ok && doc && !saveQuietly(doc, title.trimmed().isEmpty() ? T("Saved") : title.trimmed())) {
            QMessageBox::warning(getMainWindow(), T("Save Version"), T("The design could not be saved."));
        }
    }
};

class CmdSearch: public Gui::Command
{
public:
    CmdSearch()
        : Command("MyCAD_Search")
    {
        sGroup = "Tools";
        sMenuText = "Search";
        sToolTipText = "Find a command, body or sketch by typing";
        sStatusTip = sToolTipText;
        sWhatsThis = "MyCAD_Search";
        sPixmap = "Start_Search";
        sAccel = "Ctrl+K";
        eType = 0;
    }
    const char* className() const override
    {
        return "CmdSearch";
    }

protected:
    void activated(int) override
    {
        showCommandSearch();
    }
};

/// mittig unter der Kopfleiste (aus layout())
void placeSearch(const QRectF& r, qreal top)
{
    if (searchPanel && searchPanel->isVisible()) {
        QWidget* box = searchPanel->content();
        box->adjustSize();
        const QSizeF s(box->width(), box->sizeHint().height());
        searchPanel->setGeometry(QRectF((r.width() - s.width()) / 2, top, s.width(), s.height()));
    }
}

void rebuildTimelineLater();

/// Einträge einer Gruppe in Timeline-Reihenfolge
std::vector<App::DocumentObject*> groupMembers(App::Document* doc, const QString& group)
{
    std::vector<App::DocumentObject*> members;
    for (auto o : timelineItems(doc)) {
        if (timelineGroupOf(o) == group) {
            members.push_back(o);
        }
    }
    return members;
}

/// Design.setTimelineGroup([…], name) als eine Transaktion; false, wenn die Einträge nicht aneinander liegen
bool setGroup(App::Document* doc, const std::vector<App::DocumentObject*>& objs, const QString& name)
{
    std::string list = "[";
    for (auto o : objs) {
        list += pyObject(o) + ",";
    }
    list += "]";
    QString quoted = name;
    quoted.replace(QLatin1Char('\\'), QStringLiteral("\\\\")).replace(QLatin1Char('\''), QStringLiteral("\\'"));
    const std::string ok = runDesign(doc, "Group", "Design.setTimelineGroup(" + list + ", '" + quoted.toStdString() + "')");
    rebuildTimelineLater();
    return ok == "True";
}

/// Timeline-Leiste neu aufbauen (nach jeder Änderung am Dokument, gebündelt)
void rebuildTimeline()
{
    if (!state.timeline) {
        return;
    }
    syncNotes();
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
        // Gruppe: vor ihrem ersten Eintrag ein Knopf mit dem Namen; zugeklappt fehlen ihre Einträge
        const QString group = timelineGroupOf(obj);
        if (!group.isEmpty()) {
            const std::string key = std::string(doc->getName()) + "/" + group.toStdString();
            const bool open = openTimelineGroups().contains(key);
            if (index == 0 || timelineGroupOf(items[index - 1]) != group) {
                auto chip = new QToolButton;
                chip->setObjectName(QStringLiteral("GlassButton"));
                chip->setText(group);
                chip->setToolButtonStyle(Qt::ToolButtonTextOnly);
                chip->setFixedHeight(Token::WindowButton);
                chip->setCheckable(true);
                chip->setChecked(open);
                chip->setToolTip(open ? T("Collapse group") : T("Expand group"));
                chip->setAccessibleName(T("Group %1").arg(group));
                chip->setProperty("timelineGroup", group);
                QObject::connect(chip, &QToolButton::clicked, chip, [key] {
                    auto& set = openTimelineGroups();
                    set.contains(key) ? void(set.erase(key)) : void(set.insert(key));
                    rebuildTimelineLater();
                });
                const std::string docName = doc->getName();
                chip->setContextMenuPolicy(Qt::CustomContextMenu);
                QObject::connect(chip, &QWidget::customContextMenuRequested, chip, [docName, group] {
                    QMenu menu;
                    QAction* rename = menu.addAction(T("Rename…"));
                    QAction* ungroup = menu.addAction(T("Ungroup"));
                    QAction* chosen = menu.exec(QCursor::pos());
                    QTimer::singleShot(0, [docName, group, chosen, rename, ungroup] {
                        App::Document* d = App::GetApplication().getDocument(docName.c_str());
                        if (!d || !chosen) {
                            return;
                        }
                        if (chosen == ungroup) {
                            setGroup(d, groupMembers(d, group), QString());
                        }
                        else if (chosen == rename) {
                            bool ok = false;
                            const QString name = QInputDialog::getText(getMainWindow(), T("Rename Group"), T("Name"),
                                                                       QLineEdit::Normal, group, &ok).trimmed();
                            if (ok && !name.isEmpty()) {
                                setGroup(d, groupMembers(d, group), name);
                            }
                        }
                    });
                });
                lay->addWidget(chip);
                ++count;
            }
            if (!open) {
                continue;
            }
        }
        auto vp = gdoc->getViewProvider(obj);
        auto btn = new TimelineButton;
        btn->setProperty("timelineIndex", index);
        btn->setObjectName(QStringLiteral("GlassButton"));
        // Timeline-Icon = Icon des Werkzeugs, das den Eintrag erzeugt hat ("Design::Extrude" -> "Design_Extrude")
        QString type = QString::fromLatin1(obj->getTypeId().getName()).replace(QStringLiteral("::"), QStringLiteral("_"));
        if (type.startsWith(QLatin1String("Sketcher_"))) {
            type = QStringLiteral("Design_CreateSketch");
        }
        btn->setIcon(commandIcon(type, vp ? vp->getIcon() : QIcon()));
        btn->setIconSize(QSize(Token::IconL, Token::IconL));
        btn->setFixedSize(Token::WindowButton, Token::WindowButton);
        auto warningProp = freecad_cast<App::PropertyString*>(obj->getPropertyByName("Warning"));
        const QString warning = warningProp ? QString::fromUtf8(warningProp->getValue()) : QString();
        btn->setToolTip(QString::fromUtf8(obj->Label.getValue())
                        + (obj->isError() ? QStringLiteral("\n") + T(obj->getStatusString()) : QString())
                        + (warning.isEmpty() ? QString()
                                             : QStringLiteral("\n") + T((warning.section(QLatin1String(": "), 0, 0).toStdString() + ": ").c_str())
                                                   + warning.section(QLatin1String(": "), 1)));
        btn->setAccessibleName(QString::fromUtf8(obj->Label.getValue()));
        btn->setProperty("error", obj->isError());
        if (obj->isError()) {  // Farbe nie allein (C-5): Fehler-Symbol in die Ecke
            QPixmap pm = btn->icon().pixmap(QSize(Token::IconL, Token::IconL), btn->devicePixelRatioF());
            QPainter p(&pm);
            designIcon(QStringLiteral("Badge_Error"), &Theme::red).paint(&p, QRect(9, 9, 11, 11));
            p.end();
            btn->setIcon(pm);
        }
        else if (!warning.isEmpty()) {  // unsicherer Bezug: Warnsymbol (nie nur Farbe)
            QPixmap pm = btn->icon().pixmap(QSize(Token::IconL, Token::IconL), btn->devicePixelRatioF());
            QPainter p(&pm);
            designIcon(QStringLiteral("Badge_Warning"), &Theme::orange).paint(&p, QRect(9, 9, 11, 11));
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
            // Gruppieren: mehrere mit Strg+Klick gewählte Einträge; auflösen: Eintrag in einer Gruppe
            std::vector<App::DocumentObjectT> picked;
            const auto all = timelineItems(o->getDocument());
            for (const auto& sel : Selection().getSelection(o->getDocument()->getName())) {
                if (std::ranges::find(all, sel.pObject) != all.end()) {
                    picked.emplace_back(sel.pObject);
                }
            }
            const bool pickedThis = std::ranges::any_of(picked, [o](const auto& t) { return t.getObject() == o; });
            QAction* group = picked.size() >= 2 && pickedThis ? menu.addAction(T("Group Selected Steps")) : nullptr;
            QAction* ungroup = timelineGroupOf(o).isEmpty() ? nullptr : menu.addAction(T("Ungroup"));
            // Idee 6: Vorschläge des Features, betroffene Kanten zeigen, Warnung bestätigen
            std::vector<std::pair<QAction*, std::string>> fixes;
            if (auto list = freecad_cast<App::PropertyStringList*>(o->getPropertyByName("Fixes"))) {
                for (const auto& entry : list->getValues()) {
                    const QStringList parts = QString::fromStdString(entry).split(QLatin1Char('\t'));
                    if (parts.size() == 3) {
                        fixes.emplace_back(menu.addAction(fixText(parts[0])), entry);
                    }
                }
            }
            auto elements = freecad_cast<App::PropertyStringList*>(o->getPropertyByName("ErrorElements"));
            QAction* showElements = elements && elements->getSize() ? menu.addAction(T("Show Affected Edges")) : nullptr;
            auto warn = freecad_cast<App::PropertyString*>(o->getPropertyByName("Warning"));
            QAction* looksRight = warn && *warn->getValue() ? menu.addAction(T("Looks Right")) : nullptr;
            menu.addSeparator();
            QAction* remove = menu.addAction(T("Delete"));
            QAction* chosen = menu.exec(QCursor::pos());
            // Nach dem Menü ausführen, nicht innerhalb des Maus-Events
            QTimer::singleShot(0, [ref, chosen, edit, rollback, suppress, remove, group, ungroup, picked, fixes, showElements,
                                   looksRight] {
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
                else if (chosen == group) {
                    std::vector<App::DocumentObject*> objs;
                    for (const auto& t : picked) {
                        if (auto p = t.getObject()) {
                            objs.push_back(p);
                        }
                    }
                    std::set<QString> names;
                    for (auto item : timelineItems(doc)) {
                        names.insert(timelineGroupOf(item));
                    }
                    int n = 1;
                    while (names.contains(T("Group %1").arg(n))) {
                        ++n;
                    }
                    const QString name = T("Group %1").arg(n);
                    if (setGroup(doc, objs, name)) {
                        openTimelineGroups().insert(std::string(doc->getName()) + "/" + name.toStdString());
                    }
                    else {
                        shellHint(T("Timeline"), T("Only steps that follow each other can be grouped."));
                    }
                }
                else if (chosen == ungroup) {
                    setGroup(doc, groupMembers(doc, timelineGroupOf(o)), QString());
                }
                else if (chosen == looksRight) {
                    doc->openTransaction("Confirm");
                    static_cast<App::PropertyString*>(o->getPropertyByName("Warning"))->setValue("");
                    doc->commitTransaction();
                    rebuildTimelineLater();
                }
                else if (chosen == showElements) {  // im Zustand davor markieren (dort gibt es die Kanten noch)
                    auto bases = freecad_cast<App::PropertyLinkList*>(o->getPropertyByName("BaseFeatures"));
                    App::DocumentObject* base = bases && bases->getSize() ? bases->getValues().front() : o;
                    Selection().clearSelection();
                    for (const auto& name : static_cast<App::PropertyStringList*>(o->getPropertyByName("ErrorElements"))->getValues()) {
                        Selection().addSelection(doc->getName(), base->getNameInDocument(), name.c_str());
                    }
                }
                else if (auto fix = std::ranges::find(fixes, chosen, &std::pair<QAction*, std::string>::first); fix != fixes.end()) {
                    const QStringList parts = QString::fromStdString(fix->second).split(QLatin1Char('\t'));
                    runDesign(doc, "Fix", "setattr(" + pyObject(o) + ", '" + parts[1].toStdString() + "', "
                                              + "(lambda o, v: int(v) if isinstance(getattr(o, '" + parts[1].toStdString()
                                              + "'), str) else v)(" + pyObject(o) + ", " + parts[2].toStdString() + ")) or "
                                              + pyObject(o) + ".Document.recompute()");
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
                if (!(QApplication::keyboardModifiers() & Qt::ControlModifier)) {  // Strg+Klick wählt dazu
                    Selection().clearSelection();
                }
                Selection().addSelection(o->getDocument()->getName(), o->getNameInDocument());
            }
        });
        // Ziehen und auf einem anderen Eintrag loslassen: an dessen Stelle schieben
        const QPointer<QWidget> bar(box);
        btn->onDrop = [ref, bar](QPoint at) {
            auto o = ref.getObject();
            if (!o || !bar || Control().activeDialog()) {
                return;
            }
            int target = -1;
            for (auto b : bar->findChildren<QToolButton*>()) {  // nur Einträge tragen timelineIndex
                if (b->property("timelineIndex").isValid() && at.x() >= b->geometry().left()
                    && at.x() <= b->geometry().right()) {
                    target = b->property("timelineIndex").toInt();
                }
            }
            if (target >= 0) {
                runDesign(o->getDocument(), "Move in Timeline",
                          "Design.moveInTimeline(" + pyObject(o) + ", " + std::to_string(target) + ")");
            }
        };
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

/// Raster an Einstellung (MyCAD/GroundGrid), Skizzen- und Scribble-Modus (dort zeigen Skizze bzw. Blatt ihr eigenes)
/// und Theme anpassen
void updateGroundGrid()
{
    const bool on = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetBool("GroundGrid", true);
    const QColor c = theme().separator;  // MyStyle-Diagrammraster: separator, Hauptlinien voll, sonst 50 %
    groundGrid().color->value.setValue(c.redF(), c.greenF(), c.blueF(), c.alphaF());
    groundGrid().node->whichChild = on && !state.sketchMode && !state.scribbleMode ? 0 : SO_SWITCH_NONE;
}

void attach(View3DInventor* view)
{
    QGraphicsScene* scene = view->getViewer()->scene();
    if (scene == state.scene) {
        return;
    }
    auto root = static_cast<SoSeparator*>(view->getViewer()->getSceneGraph());
    if (root->findChild(groundGrid().node) < 0) {
        SoSearchAction search;  // Körper der Ansicht für den Kontaktschatten (View3DInventorViewer::objectGroup)
        search.setName(SbName("ObjectGroup"));
        search.apply(root);
        if (SoPath* path = search.getPath()) {
            // Schatten werfen nur Körper (wie beim Material-Shader in ViewProviderExt): Skizzen, Profile, Scribbles,
            // Ebenen, Achsen und Punkte (Part::Datum ist auch ein Part::Feature) nicht
            QPointer<View3DInventor> owner(view);
            auto others = [owner] {
                std::vector<SoSwitch*> list;
                Gui::Document* doc = owner ? owner->getGuiDocument() : nullptr;
                for (App::DocumentObject* obj : doc ? doc->getDocument()->getObjects() : std::vector<App::DocumentObject*>()) {
                    const bool solid = obj->isDerivedFrom(Base::Type::fromName("Part::Feature"))
                        && !obj->isDerivedFrom(Base::Type::fromName("Part::Part2DObject"))
                        && !obj->isDerivedFrom(Base::Type::fromName("Part::Datum"))
                        && std::string_view(obj->getTypeId().getName()) != "Design::Profiles";
                    Gui::ViewProvider* vp = doc->getViewProvider(obj);
                    if (!solid && vp && vp->getModeSwitch() && !vp->getChildRoot()) {  // Gruppen (Komponenten) enthalten die Körper
                        list.push_back(vp->getModeSwitch());
                    }
                }
                return list;
            };
            root->addChild(Gui::Shell::contactShadow(path->getTail(), others));  // vor dem Raster: Linien über dem Schatten
        }
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
    if (state.corners) {
        scene->addItem(state.corners);
    }
    if (state.titleGrip) {
        scene->addItem(state.titleGrip);
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
    if (state.corners) {
        state.scene->removeItem(state.corners);
    }
    if (state.titleGrip) {
        state.scene->removeItem(state.titleGrip);
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

/// Rahmenloses Fenster wie eine macOS-App (abschaltbar: MainWindow/MyCADFrameless = false)
bool frameless()
{
    return App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MainWindow")->GetBool("MyCADFrameless", true);
}

}  // namespace

void Gui::Shell::prepareWindow()
{
    // Nicht bei jedem Anzeigen auf den Bildschirmtakt warten: Zeigt Qt in einem Bild zweimal an (das Maßfeld neben dem
    // Cursor ist ein eigenes Widget), läuft die Ansicht sonst nur mit der halben Bildrate. Reißen kann unter Wayland
    // nichts, das Bild setzt der Compositor zusammen; die 3D-Ansicht begrenzt sich selbst auf die Bildschirmrate.
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(format);
    // Platz für den gemerkten Inhalt der Glas-Panels, auch auf großen und hochauflösenden Bildschirmen
    QPixmapCache::setCacheLimit(64 * 1024);
    if (frameless()) {
        // Der Alphakanal lässt sich nur setzen, bevor Qt das native Fenster anlegt
        getMainWindow()->setAttribute(Qt::WA_TranslucentBackground);
        getMainWindow()->setWindowFlag(Qt::FramelessWindowHint, true);
    }
}

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
    Application::Instance->commandManager().addCommand(new CmdSearch);  // vor der Toolbar, die ihn zeigt
    // Idee 7: Speichern ist immer; Strg+S sichert eine benannte Version
    if (Command* save = Application::Instance->commandManager().getCommandByName("Std_Save")) {
        save->setAccel("");
    }
    Application::Instance->commandManager().addCommand(new CmdSaveVersion);
    startAlwaysSave();

    state.modelBar =
        toolbar({"#FILE", "Std_New", "Std_Open", "MyCAD_SaveVersion|Design_Versions", "Design_Import", "Design_Export", "Design_Print",
                 "Std_Undo", "Std_Redo",
                 "#CREATE", "Design_CreateSketch", "Design_Extrude", "Design_Revolve",
                 "Design_Sweep|Design_Loft|Design_Rib|Design_Web|Design_Emboss",
                 "Design_Box|Design_Cylinder|Design_Sphere|Design_Torus|Design_Coil", "Design_Hole|Design_Fastener|Design_Thread",
                 "Design_Pattern", "Design_Mirror",
                 "#MODIFY", "Design_PressPull|Design_Fit|Design_RemoveFace|Design_ReplaceFace|Design_SplitFace", "Design_Fillet", "Design_Chamfer",
                 "Design_Shell", "Design_Draft", "Design_Combine|Design_SplitBody", "Design_Move|Design_Align|Design_Scale",
                 "#CONSTRUCT", "Design_OffsetPlane|Design_AnglePlane|Design_Midplane|Design_Plane|Design_Axis|Design_Point",
                 "#ASSEMBLE", "Design_NewComponent", "Design_Joint",
                 "#INSPECT", "Design_Measure", "Design_Section", "Design_PrintView", "Std_ViewFitAll",
                 "#UTILITIES", "MyCAD_Search", "Design_Parameters", "Design_Appearance", "Design_Scribble|Design_RedPen", "Design_Note"});
    state.sketchBar =
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
                 "#UTILITIES", "Design_Note"});
    state.scribbleBar =
        toolbar({"#FILE", "MyCAD_SaveVersion", "Std_Undo", "Std_Redo",
                 "#DRAW", "Design_ScribbleSelect", "Design_ScribblePencil", "Design_ScribblePen", "Design_ScribbleMarker", "Design_ScribbleText", "Design_ScribbleFill",
                 "Design_ScribbleEraser",
                 "Design_ScribbleBlack|Design_ScribbleBlue|Design_ScribbleRed|Design_ScribbleGreen|Design_ScribbleYellow",
                 "#SHAPES", "Design_ScribbleLine|Design_ScribbleArrow",
                 "Design_ScribbleRectangle|Design_ScribbleTriangle|Design_ScribbleHexagon",
                 "Design_ScribbleCircle|Design_ScribbleEllipse",
                 "#SHEET", "Design_ScribbleSheet",
                 "#UTILITIES", "Design_Note"});
    QWidget* header = content();
    state.modelBar->setParent(header);
    state.sketchBar->setParent(header);
    state.scribbleBar->setParent(header);
    state.header = new GlassPanel(header, Token::RadiusCapsule);
    state.viewCube = new ViewCube;
    state.palette = new GlassPanel(toolPalette("Sketch Palette",
                                               {{"Look At", "Sketcher_ViewSketch", "Palette_LookAt"},
                                                {"Slice", "Sketcher_ViewSection", "Palette_Section"},
                                                {"Grid", "Sketcher_Grid", "Palette_Grid"},
                                                {"Snap", "Sketcher_Snap", "Palette_Snap"},
                                                {"Construction", "Sketcher_ToggleConstruction", "Sketcher_ToggleConstruction"}},
                                               "Sketcher_LeaveSketch", "Finish Sketch"),
                                   Token::RadiusPanel, true);
    // Scribble: Zeichenwerkzeuge oben, Blatt-Optionen hier, darüber die Suche in der Handschrift (setScribbleFind)
    QWidget* scribbleBox = toolPalette("Scribble",
                                       {{"Look At", "Design_ScribbleLookAt", "Palette_LookAt"},
                                        {"Tracing Paper", "Design_ScribbleTracing", "Palette_Tracing"},
                                        {"Only the Sheet", "Design_ScribbleFocus", "Design_ScribbleFocus"},
                                        {"Apply Corrections", "Design_ScribbleCorrect", "Design_RedPen"},
                                        {"Convert to Sketch", "Design_ScribbleToSketch", "Tree_Sketch"}},
                                       "Design_ScribbleFinish", "Finish Scribble");
    scribbleFindField = new QLineEdit;
    scribbleFindField->setPlaceholderText(T("Find handwriting"));
    scribbleFindField->setAccessibleName(T("Find handwriting"));
    scribbleFindField->setToolTip(T("Find handwriting: type what you wrote, Enter jumps to the next match on this sheet"));
    scribbleFindField->setClearButtonEnabled(true);
    scribbleFindField->setVisible(bool(scribbleFind));
    QObject::connect(scribbleFindField, &QLineEdit::returnPressed, scribbleFindField, [] {
        const QString text = scribbleFindField->text().trimmed();
        if (scribbleFind && !text.isEmpty() && !scribbleFind(text)) {
            QToolTip::showText(scribbleFindField->mapToGlobal(QPoint(0, scribbleFindField->height())),
                               T("Not found on this sheet"), scribbleFindField);
        }
    });
    static_cast<QVBoxLayout*>(scribbleBox->layout())->insertWidget(2, scribbleFindField);  // unter der Überschrift
    state.scribblePalette = new GlassPanel(scribbleBox, Token::RadiusPanel, true);
    // "Nur das Blatt" (Tab): was man beim Schreiben braucht, der Rest klappt ein (wie reMarkable und Supernote)
    state.scribblePill = new GlassPanel(toolbar({"Std_Undo", "Design_ScribblePen", "Design_ScribbleEraser", "Design_ScribbleFocus"}),
                                        Token::RadiusCapsule);
    state.scribblePill->setVisible(false);
    // an der Auswahl: umfärben und löschen, ohne den Weg zur Toolbar (wie Boox und reMarkable)
    state.scribbleActions = new GlassPanel(toolbar({"Design_ScribbleBlack", "Design_ScribbleBlue", "Design_ScribbleRed",
                                                    "Design_ScribbleGreen", "Design_ScribbleYellow", "Design_ScribbleDeleteSelection"}),
                                           Token::RadiusCapsule);
    state.scribbleActions->setVisible(false);
    qApp->installEventFilter(new MenuPolisher);
    qApp->installEventFilter(new HelpKey);
    qApp->installEventFilter(new SketchTaskFilter);
    qApp->installEventFilter(new SelectFieldOnClick);
    if (frameless()) {
        state.corners = new WindowCorners;
        state.titleGrip = new TitleGrip;
        state.windowControls = new WindowControls({}, {}, true);
        state.windowPanel = new GlassPanel(state.windowControls, Token::RadiusCapsule);
        for (QWidget* w : {header, state.modelBar, state.sketchBar, state.scribbleBar, static_cast<QWidget*>(state.windowControls)}) {
            w->installEventFilter(windowGrip());
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
        auto sidebarToggle = [](const QString& tip) {
            auto btn = new QToolButton;
            btn->setObjectName(QStringLiteral("GlassButton"));
            btn->setIcon(designIcon(QStringLiteral("Window_Sidebar")));
            btn->setIconSize(QSize(Token::IconWindow, Token::IconWindow));
            btn->setFixedSize(Token::WindowButton, Token::WindowButton);
            btn->setCursor(Qt::ArrowCursor);
            btn->setToolTip(tip);
            btn->setAccessibleName(tip);
            QObject::connect(btn, &QToolButton::clicked, btn, [] { QTimer::singleShot(0, toggleBrowser); });
            return btn;
        };
        // Seitenleiste von oben bis unten: Name mit Knopf, der Baum, unten die App-Aktionen (W-1, W-7)
        auto side = content();
        auto sideLay = new QVBoxLayout(side);
        sideLay->setContentsMargins(0, 4, 0, 14);
        sideLay->setSpacing(0);
        auto head = sidebarHead(sidebarToggle(T("Hide sidebar")));
        head->setContentsMargins(8, 0, 8, 0);
        sideLay->addWidget(head);
        sideLay->addWidget(tree, 1);
        // "Gesichert" wie die Statuszeile in MyNotes: rechts in der Zeile der Version, klein und nicht klickbar; nur
        // wenn der Stand des aktiven Designs auf der Platte ist. Der Platz bleibt auch ausgeblendet (kein Springen)
        auto saved = new QWidget;
        saved->setObjectName(QStringLiteral("SavedState"));
        auto savedLay = new QHBoxLayout(saved);
        savedLay->setContentsMargins(0, 6, 2, 0);
        savedLay->setSpacing(4);
        savedLay->addWidget(new IconLabel(designIcon(QStringLiteral("Status_Saved"), &Theme::labelSecondary), 12));
        auto savedText = new QLabel(T("Saved"));
        savedText->setObjectName(QStringLiteral("Hint"));
        setTextStyle(savedText, Text::Caption);
        savedLay->addWidget(savedText, 1);
        QSizePolicy keep = saved->sizePolicy();
        keep.setRetainSizeWhenHidden(true);
        saved->setSizePolicy(keep);
        auto savedCheck = new QTimer(saved);
        QObject::connect(savedCheck, &QTimer::timeout, saved, [saved] {
            Gui::Document* gdoc = Application::Instance->activeDocument();
            const QString file = gdoc ? QString::fromUtf8(gdoc->getDocument()->FileName.getValue()) : QString();
            const bool ok = !file.isEmpty() && !gdoc->isModified();
            if (ok != saved->isVisible()) {
                saved->setVisible(ok);
            }
            saved->setToolTip(ok ? T("Saved to %1").arg(QDir::toNativeSeparators(file)) : QString());
        });
        savedCheck->start(500);
        saved->hide();
        auto foot = sidebarFooter(!frameless(), true, saved);  // rahmenlos steht die Startseite in den Fensterknöpfen
        foot->setContentsMargins(8, 0, 8, 0);
        sideLay->addWidget(foot);
        state.browser = new GlassPanel(side, Token::RadiusPanel);  // normales Glas wie MyPods' Seitenleiste: das Design scheint durch
        for (QWidget* w : {side, head}) {
            w->installEventFilter(windowGrip());
        }
        // eingeklappt: Name und Knopf als eigene Kapsel am Anfang der Titelzeile (W-1)
        auto collapsed = content();
        auto collapsedLay = new QHBoxLayout(collapsed);
        collapsedLay->setContentsMargins(0, 4, 4, 4);
        auto collapsedHead = sidebarHead(sidebarToggle(T("Show sidebar")));
        collapsedHead->setContentsMargins(4, 0, 0, 0);
        collapsedLay->addWidget(collapsedHead);
        collapsedHead->installEventFilter(windowGrip());
        collapsed->installEventFilter(windowGrip());
        state.collapsedBar = new GlassPanel(collapsed, Token::RadiusCapsule);
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
    commandAction("MyCAD_Search");  // Strg+K

    hideChrome();
    Application::Instance->signalActivateWorkbench.connect([](const char*) { hideChromeLater(); });
    Application::Instance->signalInEdit.connect([](const ViewProviderDocumentObject& vp) {
        // Skizzen und Scribbles schalten auf ihre Toolbar und Palette; Feature-Dialoge brauchen den Inspector
        static const Base::Type sketch = Base::Type::fromName("Sketcher::SketchObject");
        static const Base::Type scribble = Base::Type::fromName("Design::Scribble");
        state.sketchMode = !sketch.isBad() && vp.getObject()->getTypeId().isDerivedFrom(sketch);
        state.scribbleMode = !scribble.isBad() && vp.getObject()->getTypeId().isDerivedFrom(scribble);
        updateGroundGrid();
        hideChromeLater();
        QTimer::singleShot(0, layout);
    });
    Application::Instance->signalResetEdit.connect([](const ViewProviderDocumentObject&) {
        state.sketchMode = false;
        state.scribbleMode = false;
        state.scribbleFocus = false;  // "Nur das Blatt" endet mit dem Scribble
        if (QAction* a = commandAction("Design_ScribbleFocus")) {
            a->setChecked(false);
        }
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
    App::GetApplication().signalDeletedDocument.connect([] { rebuildTimelineLater(); });
    App::GetApplication().signalChangedObject.connect([](const App::DocumentObject& obj, const App::Property& prop) {
        if (&prop == &obj.Visibility && isNote(&obj)) {  // Post-it geschlossen oder (Auge, Doppelklick) geöffnet
            rebuildTimelineLater();
        }
    });

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

std::vector<Gui::Shell::BodyMaterialEntry> Gui::Shell::bodyMaterialList()
{
    std::vector<BodyMaterialEntry> list;
    for (const auto& m : bodyMaterials) {
        list.push_back({m.name, m.texture, std::strcmp(m.category, "Wood") == 0, m.category, m.family ? m.family : m.name});
    }
    return list;
}

App::Material Gui::Shell::bodyMaterialAppearance(int index)
{
    const BodyMaterial& m = bodyMaterials[index];
    App::Material mat;
    mat.diffuseColor.setPackedValue(m.diffuse);
    mat.specularColor.setPackedValue(m.specular);
    mat.emissiveColor.setPackedValue(m.emissive);
    mat.ambientColor.setPackedValue(0x333333FF);
    mat.shininess = float(m.shininess) / 100.0F;
    mat.transparency = float(m.transparency) / 100.0F;
    mat.imagePath = m.texture ? m.texture : "";
    return mat;
}

const char* Gui::Shell::defaultBodyTexture()
{
    return bodyMaterial().texture;
}

int Gui::Shell::bodyMaterialIndex(const App::Material& mat)
{
    for (int i = 0; i < int(std::size(bodyMaterials)); ++i) {
        const App::Material m = bodyMaterialAppearance(i);
        if (m.imagePath == mat.imagePath && m.diffuseColor.getPackedValue() == mat.diffuseColor.getPackedValue()
            && m.emissiveColor.getPackedValue() == mat.emissiveColor.getPackedValue()
            && std::abs(m.shininess - mat.shininess) < 0.005F && std::abs(m.transparency - mat.transparency) < 0.005F) {
            return i;
        }
    }
    return -1;
}

QPixmap Gui::Shell::materialPreview(int index, int size, qreal ratio)
{
    // Alle Kugeln in einem Bild, einmal je Sitzung: mit dem Körper-Shader (BodyShading), also genau wie im Modell.
    // Die Kugeln stehen in einer Ebene quer zum Blick, leicht von oben gesehen: Boden und Decke spiegeln sich.
    constexpr int Cell = 128, Columns = 12;
    static QImage sheet;
    static long lighting = -1;  // anderes Licht (Einstellung "Licht"): neu rendern
    const long now = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetInt("Lighting", 0);
    if (now != lighting) {
        sheet = QImage();
        lighting = now;
    }
    const int count = int(std::size(bodyMaterials));
    const int rows = (count + Columns - 1) / Columns;
    if (sheet.isNull()) {
        constexpr float Radius = 20.0F, Pitch = 2 * Radius;  // 40-mm-Kugel: Texturen in echter Größe
        const SbVec3f dir = SbVec3f(0, 1, -0.4F) / SbVec3f(0, 1, -0.4F).length();
        const SbVec3f right(1, 0, 0), up = right.cross(dir);
        auto root = new SoSeparator;
        root->ref();
        auto camera = new SoOrthographicCamera;
        const SbVec3f center = right * (Pitch * (Columns - 1) / 2) - up * (Pitch * float(rows - 1) / 2);
        camera->position = center - dir * 1000;
        camera->pointAt(center, SbVec3f(0, 0, 1));
        camera->height = Pitch * float(rows);
        camera->aspectRatio = float(Columns) / float(rows);
        camera->nearDistance = 900;
        camera->farDistance = 1100;
        root->addChild(camera);
        auto light = new SoDirectionalLight;  // Kopflicht wie in der Ansicht
        light->direction = dir;
        root->addChild(light);
        auto complexity = new SoComplexity;
        complexity->value = 1;
        root->addChild(complexity);
        root->addChild(Gui::Shell::bodyShading());
        for (int i = 0; i < count; ++i) {
            const App::Material m = bodyMaterialAppearance(i);
            auto cell = new SoSeparator;
            auto move = new SoTranslation;
            move->translation = right * (Pitch * float(i % Columns)) - up * (Pitch * float(i / Columns));
            cell->addChild(move);
            auto material = new SoMaterial;
            SoNode* texture = Gui::Shell::bodyTexture(m.imagePath);
            const Base::Color d = texture ? Base::Color(1, 1, 1) : m.diffuseColor;  // wie ViewProviderTextureExtension
            material->diffuseColor.setValue(d.r, d.g, d.b);
            material->specularColor.setValue(m.specularColor.r, m.specularColor.g, m.specularColor.b);
            material->emissiveColor.setValue(texture ? 2 / 255.0F : m.emissiveColor.r, m.emissiveColor.g, m.emissiveColor.b);
            material->ambientColor.setValue(0.2F, 0.2F, 0.2F);
            material->shininess = m.shininess;
            material->transparency = m.transparency;
            cell->addChild(material);
            if (texture) {
                cell->addChild(texture);
            }
            auto sphere = new SoSphere;
            sphere->radius = Radius;
            cell->addChild(sphere);
            root->addChild(cell);
        }
        SoQtOffscreenRenderer renderer(SbViewportRegion(short(Cell * Columns), short(Cell * rows)));
        renderer.setNumPasses(4);
        renderer.setBackgroundColor(SbColor4f(0.5F, 0.5F, 0.5F, 1));  // wird weggeschnitten; Glas zeigt dieses Grau
        renderer.getGLRenderAction()->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_BLEND);
        if (renderer.render(root)) {
            renderer.writeToImage(sheet);
        }
        root->unref();
        if (sheet.isNull()) {
            sheet = QImage(Cell * Columns, Cell * rows, QImage::Format_ARGB32);
            sheet.fill(Qt::gray);
        }
    }
    QPixmap out(QSize(size, size) * ratio);
    out.setDevicePixelRatio(ratio);
    out.fill(Qt::transparent);
    if (index < 0 || index >= count) {
        return out;
    }
    const QImage cell = sheet.copy((index % Columns) * Cell, (index / Columns) * Cell, Cell, Cell)
                            .scaled(QSize(size, size) * ratio, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPainter p(&out);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    QBrush brush(cell);
    brush.setTransform(QTransform::fromScale(1 / ratio, 1 / ratio));
    p.setBrush(brush);
    p.drawEllipse(QRectF(0.5, 0.5, size - 1.0, size - 1.0));  // Kante weich statt treppig
    return out;
}

void Gui::Shell::setBodyMaterial(int index)
{
    const BodyMaterial& previous = bodyMaterial();
    App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->SetInt("BodyMaterial", index);
    setDefaultMaterial();
    const BodyMaterial& m = bodyMaterial();
    const App::Material mat = bodyMaterialAppearance(index);
    // Körper mit der bisherigen Vorgabe (oder einem früheren Grau) umfärben, eigene Farben und Texturen bleiben.
    // ponytail: erkennt "Standard" an Grundfarbe bzw. Textur; was zufällig gleich aussieht, wird mit umgefärbt
    std::set<uint32_t> presets = {0xCDD1D8, 0xA4A9B2, 0xD5D9DF, 0xAEB3BC, 0xC8CCD4, 0x9EA3AD, 0xCCCCCC};
    if (!previous.texture) {
        presets.insert(previous.diffuse >> 8);
    }
    const Base::Type body = Base::Type::fromName("Design::Body");
    for (auto doc : App::GetApplication().getDocuments()) {
        for (auto obj : doc->getObjects()) {
            auto vp = dynamic_cast<Gui::ViewProviderGeometryObject*>(Gui::Application::Instance->getViewProvider(obj));
            if (!vp || !obj->isDerivedFrom(body)) {
                continue;
            }
            const std::string& texture = vp->ShapeAppearance[0].imagePath;
            if (texture.empty() ? !presets.contains(vp->ShapeAppearance.getDiffuseColor().getPackedValue() >> 8)
                                : !previous.texture || texture != previous.texture) {
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

void Gui::Shell::setScribbleFind(std::function<bool(const QString&)> find)
{
    scribbleFind = std::move(find);
    if (scribbleFindField) {
        scribbleFindField->setVisible(bool(scribbleFind));  // die Palette nimmt beim nächsten Layout ihre neue Höhe
    }
}

void Gui::Shell::setScribbleFocus(bool on)
{
    state.scribbleFocus = on && state.scribbleMode;
    if (QAction* a = commandAction("Design_ScribbleFocus")) {
        a->setCheckable(true);
        a->setChecked(state.scribbleFocus);
    }
    layout();
}

bool Gui::Shell::scribbleFocus()
{
    return state.scribbleFocus;
}

void Gui::Shell::showScribbleActions(const QRectF& selection)
{
    if (!state.scribbleActions || !state.scene) {
        return;
    }
    if (selection.isEmpty() || !state.scribbleMode) {
        state.scribbleActions->setVisible(false);
        return;
    }
    // unter der Auswahl, mittig; passt es unten nicht mehr hin, darüber. Immer ganz im Fenster.
    const QRectF r = state.scene->sceneRect();
    const qreal m = Token::WindowInset, gap = 12;
    const QSizeF s = state.scribbleActions->content()->sizeHint();
    const qreal h = std::max<qreal>(s.height(), Token::BarHeight);
    qreal y = selection.bottom() + gap;
    if (y + h > r.height() - m) {
        y = selection.top() - gap - h;
    }
    const qreal x = std::clamp(selection.center().x() - s.width() / 2, m, std::max(m, r.width() - s.width() - m));
    state.scribbleActions->setGeometry(QRectF(x, std::clamp(y, m, std::max(m, r.height() - h - m)), s.width(), h));
    state.scribbleActions->setVisible(true);
}

void Gui::Shell::setToolNames(bool on)
{
    App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->SetBool("ToolNames", on);
    for (QWidget* bar : {state.modelBar, state.sketchBar}) {
        if (!bar) {
            continue;
        }
        for (auto btn : bar->findChildren<QToolButton*>(QStringLiteral("GlassButton"))) {
            styleToolButton(btn);
        }
        for (auto sep : bar->findChildren<QFrame*>(QStringLiteral("ToolbarSeparator"))) {
            sep->setFixedSize(9, on ? 44 : 28);
        }
        // Von innen nach außen neu rechnen (Knopfreihe, Abschnitt, Toolbar): Qt reicht neue Größen sonst nur über
        // nachgereichte LayoutRequests je Ebene weiter, und layout() mäße mit den alten (Knöpfe übereinander, zu hoch).
        // findChildren liefert Eltern vor Kindern, rückwärts also die innersten zuerst. activate() rechnet nur ein als
        // ungültig markiertes Layout neu; die neue Knopfgröße markiert es erst später (LayoutRequest), daher invalidate()
        const auto widgets = bar->findChildren<QWidget*>();
        for (auto it = widgets.rbegin(); it != widgets.rend(); ++it) {
            if ((*it)->layout()) {
                (*it)->layout()->invalidate();
                (*it)->layout()->activate();
            }
        }
        bar->layout()->invalidate();
    }
    layout();
}
