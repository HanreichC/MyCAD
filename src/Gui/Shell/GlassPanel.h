// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QColor>
#include <QGraphicsObject>

class QGraphicsProxyWidget;

namespace Gui::Shell
{

struct Theme;

/// Liquid-Glass-Fläche in der Szene des 3D-Viewers.
/// Zeichnet die bereits gerenderten 3D-Pixel unter sich weich (GPU-Blur), mit Lichtbrechung am Rand,
/// heller Kante, Tönung und Schatten (MyStyle Liquid Glass, Dicke regular). Der Inhalt ist ein normales QWidget mit
/// transparentem Hintergrund. textSurface: dichteres Text-Glas für mehrzeiligen Text (Browser, Inspector, Palette).
/// MyStyle GM-1 (Glas materialisiert beim Einblenden) fehlt: die Panels erscheinen hart.
class GlassPanel: public QGraphicsObject
{
    Q_OBJECT

public:
    GlassPanel(QWidget* content, qreal radius, bool textSurface = false);

    void setGeometry(const QRectF& rect);  ///< in Szenen-/View-Koordinaten
    void setRadius(qreal radius);          ///< Token::RadiusCapsule = Höhe / 2
    void setTint(QColor Theme::*color);    ///< Glas leicht in dieser Theme-Farbe tönen (Post-its)
    QWidget* content() const;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QSizeF size;
    qreal radius;
    bool textSurface;
    QColor Theme::*tint = nullptr;
    QGraphicsProxyWidget* proxy;
};

}  // namespace Gui::Shell
