// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QGraphicsObject>

class QGraphicsProxyWidget;

namespace Gui::Shell
{

/// Liquid-Glass-Fläche in der Szene des 3D-Viewers.
/// Zeichnet die bereits gerenderten 3D-Pixel unter sich weich (GPU-Blur), mit Lichtbrechung am Rand,
/// heller Kante, Tönung und Schatten. Der Inhalt ist ein normales QWidget mit transparentem Hintergrund.
class GlassPanel: public QGraphicsObject
{
    Q_OBJECT

public:
    GlassPanel(QWidget* content, qreal radius);

    void setGeometry(const QRectF& rect);  ///< in Szenen-/View-Koordinaten
    QWidget* content() const;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QSizeF size;
    qreal radius;
    QGraphicsProxyWidget* proxy;
};

}  // namespace Gui::Shell
