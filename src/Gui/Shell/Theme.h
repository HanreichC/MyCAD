// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QColor>
#include <QFont>
#include <QIcon>
#include <QString>

class QLabel;
class QPainter;
class QWidget;
class QRectF;

namespace Gui::Shell
{

/// MyStyle-Tokens (../MyStyle/tokens/mystyle.tokens.json, Werte wie im daraus generierten Theme.qml) für das
/// aktuelle Erscheinungsbild. Hell/Dunkel, Liquid-Glass-Stufe und Bedienungshilfen stehen in den Einstellungen
/// (MyCAD/Appearance, GlassLevel, IncreaseContrast, ReduceTransparency, ReduceMotion).
struct Theme
{
    bool dark = false;
    bool increaseContrast = false;
    bool reduceTransparency = false;
    bool reduceMotion = false;
    double glassLevel = 0.5;  ///< Liquid Glass: 0 Ultra Clear, 0.5 Default, 1 Tinted

    QColor backgroundTop, backgroundBottom;
    QColor labelPrimary, labelSecondary, labelTertiary, labelOnAccent;
    QColor accent, accentText, focusRing;
    QColor red, orange, green, blue, purple, gray, gray2;
    QColor redIC, orangeIC, purpleIC;  ///< kräftigere Variante (Kontrast erhöhen) für "voll bestimmt" im Skizzenbild
    QColor fillPrimary, fillSecondary, fillTertiary, fillQuaternary;
    QColor separator, separatorOpaque;
    QColor materialFill, materialBorder, materialThumb;
    QColor glassTint, glassBorder, glassEdge, glassOpaqueTop, glassOpaqueBottom, glassPopupBorder;
    QColor shadow, scrim;

    /// Anteil, mit dem glassTint den weichgezeichneten Hintergrund deckt (textSurface = Text-Glas für Browser,
    /// Inspector, Menüs); stückweise linear durch die Stützpunkte bei Stufe 0 / 0.5 / 1
    double glassTintAmount(bool textSurface) const;
    double glassBlur() const;  ///< px wie MultiEffect.blurMax: 12 / 24 / 36
    double glassRim() const;
    int duration(int ms) const;  ///< Bewegung reduzieren: höchstens 150 ms
};

/// Maße aus den Tokens (radius.*, size.*, space.*)
namespace Token
{
constexpr int RadiusWindow = 32, RadiusPanel = 20, RadiusTile = 12, RadiusControl = 8, RadiusCheckbox = 5;
constexpr int RadiusCapsule = 9999;  ///< Höhe / 2
constexpr int WindowInset = 12, WindowButton = 36, ControlDesktop = 30, Segmented = 44, Chip = 24;
constexpr int SwitchWidth = 38, SwitchHeight = 22, SwitchKnob = 18, SliderKnob = 21;
constexpr int IconM = 16, IconWindow = 18, IconL = 20;
constexpr int ContentMaxWidth = 560;
constexpr int DurationFade = 150;
constexpr double OpacityDisabledGlyph = 0.35;
}  // namespace Token

const Theme& theme();
/// Einstellungen und System (Hell/Dunkel, Kontrast, KDE-Animationen) neu lesen; setzt auch Qts Farbschema
void reloadTheme();

/// Textstile der Desktop-Skala (typography.desktop.*), mit Inters Laufweite
enum class Text
{
    Title1,    ///< 24 Bold: Seitentitel
    Title2,    ///< 20 Bold: App-Name in der Seitenleiste, Abschnittstitel
    Headline,  ///< 15 SemiBold: Dialog- und Kartentitel
    Body,      ///< 14 Regular: Zeilenlabels, Fließtext
    Callout,   ///< 13 Regular: Buttons, Seitenleisten-Einträge, Dialogtext (Standard der App)
    Caption,   ///< 12 Medium: Untertitel, Chips
    Section,   ///< 11 SemiBold VERSALIEN: Abschnittsköpfe
};
QFont textFont(Text style, int weight = 0);  ///< weight: anderes Gewicht (400/500/600/700), 0 = das des Stils
void setTextStyle(QWidget* w, Text style, int weight = 0);
/// Abschnittskopf (Section-Stil, labelSecondary)
QLabel* sectionLabel(const QString& text);

/// Farbe als Stylesheet-Wert
QString css(const QColor& c);
/// "@labelPrimary", "@accent" … in einem Stylesheet durch die Farben des aktuellen Themes ersetzen
QString themed(QString styleSheet);

/// Eigenes MyCAD-Icon (src/Gui/Shell/icons) in einer Theme-Farbe. Die Farbe wird beim Zeichnen gelesen, ein
/// Wechsel des Erscheinungsbilds braucht also nur ein Neuzeichnen. Auf Akzentflächen (QIcon::Active/Selected:
/// Menüeintrag unter der Maus, roter Schließen-Knopf mit autoRaise) weiß. Leer, wenn es das Icon nicht gibt.
QIcon designIcon(const QString& name, QColor Theme::*color = &Theme::labelPrimary);
/// Buntes FreeCAD-Icon neutral eingefärbt (Schattierung bleibt), ebenfalls passend zum aktuellen Theme
QIcon neutralIcon(const QIcon& icon);

/// Liquid Glass ohne Hintergrund-Blur (Startseite, Hilfe, Rückfall ohne GL, Transparenz reduzieren):
/// Schatten, Tönung, Lichtkante, dunkler Rand. frost (oder "Transparenz reduzieren"): fast deckend, oben heller,
/// mit Haarlinie, für eigene Fenster, hinter denen nichts weichgezeichnet werden kann (Alerts)
void paintGlass(QPainter& p, const QRectF& r, qreal radius, bool textSurface, bool frost = false);

}  // namespace Gui::Shell
