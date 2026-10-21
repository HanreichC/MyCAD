// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Theme.h"

#include <App/Application.h>

#include <QApplication>
#include <QFile>
#include <QIconEngine>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPixmapCache>
#include <QSettings>
#include <QStandardPaths>
#include <QStyleHints>
#include <QSvgRenderer>
#include <QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
# include <QAccessibilityHints>
#endif

#include <algorithm>
#include <array>

using namespace Gui::Shell;

namespace
{

Theme current;
bool loaded = false;

/// stückweise linear durch die Werte bei Glas-Stufe 0 / 0.5 / 1 (wie Theme.qml piecewise())
double piecewise(double level, const std::array<double, 3>& a)
{
    return a[0] + (a[1] - a[0]) * 2 * std::min(level, 0.5) + (a[2] - a[1]) * 2 * std::max(level - 0.5, 0.0);
}

/// Icon, dessen Farbe beim Zeichnen aus dem aktuellen Theme kommt (SVG mit currentColor oder FreeCAD-Icon)
class ThemedIcon: public QIconEngine
{
public:
    ThemedIcon(QByteArray svg, QString id, QColor Theme::*color, QIcon source = {})
        : svg(std::move(svg))
        , id(std::move(id))
        , color(color)
        , source(std::move(source))
    {}
    QIconEngine* clone() const override
    {
        return new ThemedIcon(*this);
    }
    void paint(QPainter* p, const QRect& rect, QIcon::Mode mode, QIcon::State state) override
    {
        p->drawPixmap(rect, scaledPixmap(rect.size(), mode, state, p->device()->devicePixelRatioF()));
    }
    QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state) override
    {
        return scaledPixmap(size, mode, state, 1.0);
    }
    QPixmap scaledPixmap(const QSize& size, QIcon::Mode mode, QIcon::State state, qreal scale) override
    {
        const Theme& t = theme();
        // auf Akzentfläche (Menüeintrag unter der Maus, Auswahl, roter Schließen-Knopf): weiß;
        // aktiv (eingeschaltete Seitenleisten-/Palettenzeile): Akzent als Vordergrund
        const bool onAccent = mode == QIcon::Active || mode == QIcon::Selected;
        const QColor c = onAccent ? t.labelOnAccent : state == QIcon::On ? t.accentText : t.*color;
        const QSize px = size * scale;
        const QString key = QStringLiteral("mycad:%1:%2x%3:%4:%5:%6")
                                .arg(id)
                                .arg(px.width())
                                .arg(px.height())
                                .arg(c.rgba())
                                .arg(int(mode))
                                .arg(int(t.dark));
        QPixmap pm;
        if (!QPixmapCache::find(key, &pm)) {
            QImage img(px, QImage::Format_ARGB32_Premultiplied);
            img.fill(Qt::transparent);
            if (!svg.isEmpty()) {
                QPainter p(&img);
                p.setOpacity(c.alphaF() * (mode == QIcon::Disabled ? Token::OpacityDisabledGlyph : 1.0));
                QSvgRenderer(QByteArray(svg).replace("currentColor", c.name().toLatin1())).render(&p);
            }
            else {
                // ponytail: Graustufen statt eigenem Icon, bis jeder Befehl ein MyCAD-Icon hat
                img = source.pixmap(px).toImage().convertToFormat(QImage::Format_ARGB32);
                for (int y = 0; y < img.height(); ++y) {
                    auto line = reinterpret_cast<QRgb*>(img.scanLine(y));
                    for (int x = 0; x < img.width(); ++x) {
                        const QRgb s = line[x];
                        const double lum = (0.299 * qRed(s) + 0.587 * qGreen(s) + 0.114 * qBlue(s)) / 255.0;
                        const int g = onAccent ? 255 : t.dark ? int(120 + lum * 135) : int(35 + lum * 165);
                        const double a = mode == QIcon::Disabled ? Token::OpacityDisabledGlyph : 1.0;
                        line[x] = qRgba(g, g, g, int(qAlpha(s) * a));
                    }
                }
            }
            pm = QPixmap::fromImage(img);
            QPixmapCache::insert(key, pm);
        }
        pm.setDevicePixelRatio(scale);
        return pm;
    }

private:
    QByteArray svg;
    QString id;
    QColor Theme::*color;
    QIcon source;
};

}  // namespace

double Theme::glassTintAmount(bool textSurface) const
{
    const double t = textSurface ? piecewise(glassLevel, dark ? std::array {0.66, 0.75, 0.84} : std::array {0.72, 0.80, 0.88})
                                 : piecewise(glassLevel, dark ? std::array {0.16, 0.33, 0.66} : std::array {0.10, 0.27, 0.62});
    return increaseContrast ? std::max(t, 0.85) : t;
}

double Theme::glassBlur() const
{
    return piecewise(glassLevel, {12, 24, 36});
}

double Theme::glassRim() const
{
    return piecewise(glassLevel, dark ? std::array {0.20, 0.20, 0.04} : std::array {0.70, 0.70, 0.70});
}

int Theme::duration(int ms) const
{
    return reduceMotion ? std::min(ms, Token::DurationFade) : ms;
}

const Theme& Gui::Shell::theme()
{
    if (!loaded) {
        reloadTheme();
    }
    return current;
}

void Gui::Shell::reloadTheme()
{
    auto grp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    auto hints = QGuiApplication::styleHints();
    const long mode = grp->GetInt("Appearance", 0);  // 0 Automatic (wie das System), 1 Light, 2 Dark
    if (mode == 0) {
        hints->unsetColorScheme();
    }
    else {
        hints->setColorScheme(mode == 2 ? Qt::ColorScheme::Dark : Qt::ColorScheme::Light);
    }
    bool systemContrast = false;
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
    systemContrast = hints->accessibility()->contrastPreference() == Qt::ContrastPreference::HighContrast;
#endif
    // KDE: Animationsgeschwindigkeit "sofort" heißt Bewegung reduzieren
    const QSettings kde(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QStringLiteral("/kdeglobals"),
                        QSettings::IniFormat);
    const bool systemMotion = kde.value(QStringLiteral("KDE/AnimationDurationFactor"), 1.0).toDouble() == 0.0;

    Theme t;
    t.dark = mode == 0 ? hints->colorScheme() == Qt::ColorScheme::Dark : mode == 2;
    t.increaseContrast = grp->GetBool("IncreaseContrast", systemContrast);
    t.reduceTransparency = grp->GetBool("ReduceTransparency", false);
    t.reduceMotion = grp->GetBool("ReduceMotion", systemMotion);
    // früher nur Tinted/Clear: Clear entspricht Ultra Clear
    t.glassLevel = std::clamp(grp->GetFloat("GlassLevel", grp->GetInt("GlassClear", 0) == 1 ? 0.0 : 0.5), 0.0, 1.0);

    const auto pick = [&t](const char* light, const char* dark, const char* lightIC, const char* darkIC) {
        return QColor::fromString(QLatin1String(t.dark ? (t.increaseContrast ? darkIC : dark) : (t.increaseContrast ? lightIC : light)));
    };
    const auto ic = [&t](const char* lightIC, const char* darkIC) { return QColor::fromString(QLatin1String(t.dark ? darkIC : lightIC)); };
    t.backgroundTop = pick("#F4F5F7", "#2A2A2E", "#F4F5F7", "#2A2A2E");
    t.backgroundBottom = pick("#D5D9E0", "#1C1C1F", "#D5D9E0", "#1C1C1F");
    t.labelPrimary = pick("#1D1D1F", "#F5F5F7", "#000000", "#FFFFFF");
    t.labelSecondary = pick("#5E5E63", "#A1A1A6", "#3A3A3C", "#D8D8DC");
    t.labelTertiary = pick("#A1A1A6", "#6C6C70", "#6E6E73", "#98989D");
    t.labelOnAccent = pick("#FFFFFF", "#FFFFFF", "#FFFFFF", "#FFFFFF");
    t.accent = pick("#0088FF", "#0091FF", "#1E6EF4", "#0091FF");
    t.accentText = pick("#0071E3", "#3D9BFF", "#0058B9", "#7CC0FF");
    t.focusRing = t.accentText;
    t.red = pick("#FF383C", "#FF4245", "#E9152D", "#FF6165");
    t.orange = pick("#FF8D28", "#FF9230", "#C55300", "#FFA056");
    t.green = pick("#34C759", "#30D158", "#008932", "#4AD968");
    t.blue = pick("#0088FF", "#0091FF", "#1E6EF4", "#5CB8FF");
    t.purple = pick("#CB30E0", "#DB34F2", "#B02FC2", "#EA8DFF");
    t.gray = pick("#8E8E93", "#8E8E93", "#6C6C70", "#AEAEB2");
    t.gray2 = pick("#AEAEB2", "#636366", "#8E8E93", "#7C7C80");
    t.redIC = ic("#E9152D", "#FF6165");
    t.orangeIC = ic("#C55300", "#FFA056");
    t.purpleIC = ic("#B02FC2", "#EA8DFF");
    t.fillPrimary = pick("#33787880", "#5C787880", "#47787880", "#70787880");
    t.fillSecondary = pick("#29787880", "#52787880", "#3D787880", "#66787880");
    t.fillTertiary = pick("#1F767680", "#3D767680", "#33767680", "#52767680");
    t.fillQuaternary = pick("#14747480", "#2E747480", "#24747480", "#3D747480");
    t.separator = pick("#4A3C3C43", "#A6545458", "#993C3C43", "#CC8C8C94");
    t.separatorOpaque = pick("#C6C6C8", "#38383A", "#8E8E93", "#6C6C70");
    t.materialFill = pick("#9EFFFFFF", "#0FFFFFFF", "#E0FFFFFF", "#1AFFFFFF");
    t.materialBorder = pick("#F2FFFFFF", "#1AFFFFFF", "#40000000", "#59FFFFFF");
    t.materialThumb = pick("#FFFFFF", "#636366", "#FFFFFF", "#636366");
    t.glassTint = pick("#FFFFFF", "#1F1F24", "#FFFFFF", "#1F1F24");
    t.glassBorder = pick("#F2FFFFFF", "#24FFFFFF", "#73000000", "#8CFFFFFF");
    t.glassEdge = pick("#1A000000", "#59000000", "#4C000000", "#8C000000");
    t.glassOpaqueTop = pick("#FCFFFFFF", "#FA34343A", "#FCFFFFFF", "#FA34343A");
    t.glassOpaqueBottom = pick("#FCF4F5F8", "#FA26262B", "#FCF4F5F8", "#FA26262B");
    t.glassPopupBorder = pick("#17000000", "#21FFFFFF", "#66000000", "#73FFFFFF");
    t.shadow = pick("#21000000", "#40000000", "#21000000", "#40000000");
    t.scrim = pick("#24000000", "#59000000", "#24000000", "#59000000");
    current = t;
    loaded = true;
}

QFont Gui::Shell::textFont(Text style, int weight)
{
    struct Spec
    {
        int size, weight;
        qreal tracking;
    };
    static constexpr Spec specs[] = {{24, 700, -0.47}, {20, 700, -0.33}, {15, 600, -0.13}, {14, 400, -0.09},
                                     {13, 400, -0.04}, {12, 500, 0.01},  {11, 600, 0.55}};
    const Spec& s = specs[int(style)];
    QFont font(QStringLiteral("Inter"));
    font.setPixelSize(s.size);
    font.setWeight(QFont::Weight(weight ? weight : s.weight));
    font.setLetterSpacing(QFont::AbsoluteSpacing, s.tracking);
    if (style == Text::Section) {
        font.setCapitalization(QFont::AllUppercase);
    }
    return font;
}

void Gui::Shell::setTextStyle(QWidget* w, Text style, int weight)
{
    w->setFont(textFont(style, weight));
}

QLabel* Gui::Shell::sectionLabel(const QString& text)
{
    auto label = new QLabel(text);
    label->setObjectName(QStringLiteral("Section"));
    setTextStyle(label, Text::Section);
    return label;
}

QString Gui::Shell::css(const QColor& c)
{
    return QStringLiteral("rgba(%1, %2, %3, %4)").arg(c.red()).arg(c.green()).arg(c.blue()).arg(c.alphaF(), 0, 'f', 3);
}

QString Gui::Shell::themed(QString s)
{
    const Theme& t = theme();
    QColor errorFill = t.red;
    errorFill.setAlphaF(0.24);  // MyStyle: kein Token für eine Fehlerfläche (system.red gedämpft, dazu Fehler-Symbol)
    const std::pair<const char*, QColor> colors[] = {
        {"labelPrimary", t.labelPrimary},
        {"labelSecondary", t.labelSecondary},
        {"labelTertiary", t.labelTertiary},
        {"labelOnAccent", t.labelOnAccent},
        {"accentPressed", t.accent.darker(118)},  // gedrückt: 15 % dunkler
        {"accentText", t.accentText},
        {"accent", t.accent},
        {"focusRing", t.focusRing},
        {"redPressed", t.red.darker(118)},
        {"red", t.red},
        {"green", t.green},
        {"errorFill", errorFill},
        {"fillSecondary", t.fillSecondary},
        {"fillTertiary", t.fillTertiary},
        {"separator", t.separator},
        {"materialFill", t.materialFill},
        {"materialBorder", t.materialBorder},
        {"materialThumb", t.materialThumb},
        {"backgroundTop", t.backgroundTop},
        {"backgroundBottom", t.backgroundBottom},
        {"glassOpaqueTop", t.glassOpaqueTop},
        {"glassOpaqueBottom", t.glassOpaqueBottom},
        {"glassPopupBorder", t.increaseContrast ? t.glassBorder : t.glassPopupBorder},
        {"hoverRim", QColor(255, 255, 255, 89)},  // Button-Hover: 1 px Weiß 35 % (§ 9.3)
        {"knob", QColor(255, 255, 255)},          // Knöpfe von Switch/Slider (C-1-Ausnahme)
        // Scrollbar: Schwarz 28 % / Weiß 35 % (§ 9.3)
        {"scrollbar", t.dark ? QColor(255, 255, 255, 89) : QColor(0, 0, 0, 71)},
    };
    for (const auto& [name, color] : colors) {  // längere Namen stehen vor ihren Präfixen (accentText vor accent)
        s.replace(QLatin1Char('@') + QLatin1String(name), css(color));
    }
    return s;
}

QIcon Gui::Shell::designIcon(const QString& name, QColor Theme::*color)
{
    QFile file(QStringLiteral(":/mycad/icons/%1.svg").arg(name));
    if (!file.open(QIODevice::ReadOnly)) {
        return {};
    }
    return QIcon(new ThemedIcon(file.readAll(), name, color));
}

QIcon Gui::Shell::neutralIcon(const QIcon& icon)
{
    return QIcon(new ThemedIcon({}, QStringLiteral("freecad%1").arg(icon.cacheKey()), &Theme::labelPrimary, icon));
}

void Gui::Shell::paintGlass(QPainter& p, const QRectF& r, qreal radius, bool textSurface, bool frost)
{
    const Theme& t = theme();
    // elevation.glass × glass.thickness.regular: 28 px weich, 6 px nach unten
    constexpr qreal S = 28, Y = 6;
    radius = std::min({radius, r.width() / 2, r.height() / 2});
    const bool inactive = qApp->applicationState() != Qt::ApplicationActive;  // GM-4: Glas tritt zurück
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath panel;
    panel.addRoundedRect(r, radius, radius);

    // Schatten nur außerhalb des Glases: Ringe, deren Deckkraft sich zur Kurve des Glas-Shaders aufsummiert
    auto curve = [&](qreal d) {
        const qreal x = std::clamp((d + 0.3 * S) / (1.3 * S), 0.0, 1.0);
        const qreal s = x * x * (3 - 2 * x);
        return (1 - s) * (1 - s) * t.shadow.alphaF();
    };
    QPainterPath outside;
    outside.addRect(r.adjusted(-2 * S, -2 * S, 2 * S, 2 * S));
    p.save();
    p.setClipPath(outside.subtracted(panel));
    p.setPen(Qt::NoPen);
    qreal carry = 0;  // Rundungsrest weitertragen: die Alphawerte je Ring sind winzig
    for (qreal k = S; k > -0.3 * S; k -= 1.5) {
        const qreal a = (curve(k - 1.5) - curve(k)) * 255 + carry;
        const int alpha = int(std::round(a));
        carry = a - alpha;
        p.setBrush(QColor(0, 0, 0, std::clamp(alpha, 0, 255)));
        const qreal rr = std::max<qreal>(0, radius + k - 1.5);
        p.drawRoundedRect(r.adjusted(-(k - 1.5), -(k - 1.5) + Y, k - 1.5, k - 1.5 + Y), rr, rr);
    }
    p.restore();

    if (frost || t.reduceTransparency) {  // Frost: fast deckend, oben heller, Haarlinie
        QLinearGradient frost(r.topLeft(), r.bottomLeft());
        frost.setColorAt(0, t.glassOpaqueTop);
        frost.setColorAt(1, t.glassOpaqueBottom);
        p.setBrush(frost);
        p.setPen(QPen(t.increaseContrast ? t.glassBorder : t.glassPopupBorder, 1));
        p.drawRoundedRect(r.adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);
        return;
    }

    p.setPen(Qt::NoPen);
    QColor tint = t.glassTint;
    tint.setAlphaF(std::min(1.0, t.glassTintAmount(textSurface) + (inactive ? 0.1 : 0.0)));
    p.setBrush(tint);
    p.drawPath(panel);
    QLinearGradient sheen(r.topLeft(), r.bottomLeft());  // feiner Glanz von oben
    sheen.setColorAt(0, QColor(255, 255, 255, t.dark ? 8 : 13));
    sheen.setColorAt(1, QColor(255, 255, 255, 0));
    p.setBrush(sheen);
    p.drawPath(panel);

    // äußerstes Pixel abgedunkelt, die Lichtkante direkt innen; oben und unten heller (Licht von (−0.45, −1))
    p.setBrush(Qt::NoBrush);
    p.setPen(QPen(t.glassEdge, 1));
    p.drawRoundedRect(r.adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);
    const double rim = t.glassRim() * (inactive ? 0.5 : 1.0);
    QLinearGradient light(r.topLeft(), r.bottomLeft());
    light.setColorAt(0, QColor(255, 255, 255, int(255 * rim * 0.94)));
    light.setColorAt(0.5, QColor(255, 255, 255, int(255 * rim * 0.59)));
    light.setColorAt(1, QColor(255, 255, 255, int(255 * rim * 0.94)));
    p.setPen(QPen(QBrush(light), 1.5));
    p.drawRoundedRect(r.adjusted(1.75, 1.75, -1.75, -1.75), std::max<qreal>(0, radius - 1.75), std::max<qreal>(0, radius - 1.75));
    if (t.increaseContrast) {
        p.setPen(QPen(t.glassBorder, 1));
        p.drawRoundedRect(r.adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);
    }
}
