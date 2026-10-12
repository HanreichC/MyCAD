// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QGraphicsItem>
#include <QPolygonF>
#include <QPointer>

#include <array>

namespace Gui
{
class View3DInventorViewer;
}

namespace Gui::Shell
{

/// Eigener ViewCube in der Szene des 3D-Viewers: folgt der Kamera, Klick auf eine Seite dreht in diese Ansicht,
/// der runde Knopf darunter führt zur Iso-Ansicht.
class ViewCube: public QGraphicsItem
{
public:
    ViewCube();
    void setViewer(View3DInventorViewer* viewer);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int hitTest(const QPointF& pos) const;  ///< Seite 0..5, 6 = Home, -1 = nichts

    QPointer<View3DInventorViewer> viewer;  // Ansicht kann mit dem Dokument verschwinden
    std::array<QPolygonF, 6> faces;  ///< zuletzt gezeichnete Seiten (leer = nicht sichtbar)
    int hover = -1;
};

}  // namespace Gui::Shell
