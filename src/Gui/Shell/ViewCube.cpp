// SPDX-License-Identifier: LGPL-2.1-or-later

#include "ViewCube.h"
#include "Shell.h"
#include "Theme.h"

#include <Gui/Application.h>
#include <Gui/Camera.h>
#include <Gui/Command.h>
#include <Gui/View3DInventorViewer.h>

#include <Inventor/SbRotation.h>
#include <Inventor/SbVec3f.h>

#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QPainter>
#include <QPainterPath>
#include <QStyleHints>
#include <QTimer>
#include <QtMath>

#include <algorithm>
#include <cmath>
#include <numeric>

using namespace Gui::Shell;

namespace
{
constexpr qreal Width = 120, Height = 150, CenterX = 60, CenterY = 64, Scale = 29;
constexpr int Home = 6, TurnLeft = 7, TurnRight = 8;
const QRectF HomeRect(6, Height - 32, 26, 26);
// Drehpfeile oben rechts (wie Fusion): nur in einer Seitenansicht, drehen die Kamera um 90° um die Blickrichtung
const QRectF TurnLeftRect(Width - 50, 2, 22, 22);
const QRectF TurnRightRect(Width - 24, 2, 22, 22);

struct Face
{
    SbVec3f n, u, v;  ///< Normale; u/v = rechts/oben, wenn man von außen auf die Seite schaut
    const char* label;
    const char* command;
};
const Face Faces[6] = {
    {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}, "TOP", "Std_ViewTop"},
    {{0, 0, -1}, {1, 0, 0}, {0, -1, 0}, "BOTTOM", "Std_ViewBottom"},
    {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}, "FRONT", "Std_ViewFront"},
    {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}, "BACK", "Std_ViewRear"},
    {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, "RIGHT", "Std_ViewRight"},
    {{-1, 0, 0}, {0, -1, 0}, {0, 0, 1}, "LEFT", "Std_ViewLeft"},
};
}  // namespace

ViewCube::ViewCube()
{
    setAcceptHoverEvents(true);
    setZValue(10);
}

void ViewCube::setViewer(View3DInventorViewer* v)
{
    viewer = v;
    update();
}

QRectF ViewCube::boundingRect() const
{
    return {0, 0, Width, Height};
}

void ViewCube::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (!viewer) {
        return;
    }
    p->setRenderHint(QPainter::Antialiasing);
    const Theme& th = theme();
    const SbRotation toCamera = viewer->getCameraOrientation().inverse();
    auto project = [&](const SbVec3f& w) {
        SbVec3f c;
        toCamera.multVec(w, c);
        return QPointF(CenterX + c[0] * Scale, CenterY - c[1] * Scale);
    };

    // weicher Schatten unter dem Würfel
    QRadialGradient shadow(QPointF(CenterX, CenterY + 46), 44);
    shadow.setColorAt(0, th.shadow);
    shadow.setColorAt(1, QColor(0, 0, 0, 0));
    p->setPen(Qt::NoPen);
    p->setBrush(shadow);
    p->drawEllipse(QPointF(CenterX, CenterY + 46), 44, 10);

    // Seiten von hinten nach vorne zeichnen
    std::array<float, 6> depth {};
    for (int i = 0; i < 6; ++i) {
        SbVec3f nc;
        toCamera.multVec(Faces[i].n, nc);
        depth[i] = nc[2];
        faces[i].clear();
    }
    std::array<int, 6> order {};
    std::iota(order.begin(), order.end(), 0);
    std::ranges::sort(order, [&](int a, int b) { return depth[a] < depth[b]; });

    QFont font = textFont(Text::Headline);  // im 100er-Raster der Seite, wird mit ihr skaliert
    font.setPixelSize(19);
    for (int i : order) {
        if (depth[i] < 0.02F) {
            continue;  // abgewandt
        }
        const Face& f = Faces[i];
        // oben-links, oben-rechts, unten-rechts, unten-links (aus Sicht von außen)
        QPolygonF quad {project(f.n - f.u + f.v), project(f.n + f.u + f.v), project(f.n + f.u - f.v),
                        project(f.n - f.u - f.v)};
        faces[i] = quad;

        // Seiten wie Frost-Glas (glass.opaqueTop), zur Kamera hin heller; Hover: Akzentfläche
        const qreal light = 0.86 + 0.14 * depth[i];
        const QColor base = th.glassOpaqueTop;
        QColor fill = hover == i ? th.accent : QColor::fromRgbF(base.redF() * light, base.greenF() * light, base.blueF() * light);
        p->setBrush(fill);
        p->setPen(QPen(th.separator, 1.2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        p->drawPolygon(quad);

        if (depth[i] > 0.35F) {  // nur gut lesbare Seiten beschriften
            QTransform t;
            if (QTransform::quadToQuad(QPolygonF(QRectF(0, 0, 100, 100)), quad, t)) {
                p->save();
                p->setTransform(t, true);
                p->setFont(font);
                p->setPen(hover == i ? th.labelOnAccent : th.labelSecondary);
                p->drawText(QRectF(0, 0, 100, 100), Qt::AlignCenter, Gui::Shell::T(f.label));
                p->restore();
            }
        }
    }

    // In einer Seitenansicht: Drehpfeile oben rechts
    aligned = std::ranges::any_of(depth, [](float d) { return d > 0.999F; });
    if (aligned) {
        for (const auto& [id, rect] : {std::pair {TurnLeft, TurnLeftRect}, std::pair {TurnRight, TurnRightRect}}) {
            p->setBrush(hover == id ? th.accent : th.glassOpaqueTop);
            p->setPen(QPen(th.glassPopupBorder, 1));
            p->drawEllipse(rect);
            // 270°-Bogen mit Pfeilspitze in Laufrichtung: links gegen, rechts im Uhrzeigersinn
            const QPointF m = rect.center();
            constexpr qreal r = 5.5;
            const bool right = id == TurnRight;
            const qreal start = right ? 120 : 60, sweep = right ? -270 : 270;
            QPainterPath glyph;
            glyph.arcMoveTo(QRectF(m.x() - r, m.y() - r, 2 * r, 2 * r), start);
            glyph.arcTo(QRectF(m.x() - r, m.y() - r, 2 * r, 2 * r), start, sweep);
            const qreal end = qDegreesToRadians(start + sweep);
            const QPointF tip(m.x() + r * std::cos(end), m.y() - r * std::sin(end));
            QPointF dir = right ? QPointF(std::sin(end), std::cos(end)) : QPointF(-std::sin(end), -std::cos(end));
            auto turned = [&](qreal deg) {
                const qreal a = qDegreesToRadians(deg);
                return QPointF(dir.x() * std::cos(a) - dir.y() * std::sin(a), dir.x() * std::sin(a) + dir.y() * std::cos(a));
            };
            glyph.moveTo(tip - turned(35) * 3.6);
            glyph.lineTo(tip);
            glyph.lineTo(tip - turned(-35) * 3.6);
            p->setBrush(Qt::NoBrush);
            p->setPen(QPen(hover == id ? th.labelOnAccent : th.labelPrimary, 1.6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            p->drawPath(glyph);
        }
    }

    // Home-Knopf (Iso-Ansicht)
    p->setBrush(hover == Home ? th.accent : th.glassOpaqueTop);
    p->setPen(QPen(th.glassPopupBorder, 1));
    p->drawEllipse(HomeRect);
    QPainterPath house;
    const QPointF c = HomeRect.center();
    house.moveTo(c + QPointF(-5.5, -0.5));
    house.lineTo(c + QPointF(0, -5.5));
    house.lineTo(c + QPointF(5.5, -0.5));
    house.moveTo(c + QPointF(-4, -1.5));
    house.lineTo(c + QPointF(-4, 5));
    house.lineTo(c + QPointF(4, 5));
    house.lineTo(c + QPointF(4, -1.5));
    p->setBrush(Qt::NoBrush);
    p->setPen(QPen(hover == Home ? th.labelOnAccent : th.labelPrimary, 1.8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p->drawPath(house);
}

int ViewCube::hitTest(const QPointF& pos) const
{
    if (QLineF(pos, HomeRect.center()).length() <= HomeRect.width() / 2) {
        return Home;
    }
    if (aligned && QLineF(pos, TurnLeftRect.center()).length() <= TurnLeftRect.width() / 2) {
        return TurnLeft;
    }
    if (aligned && QLineF(pos, TurnRightRect.center()).length() <= TurnRightRect.width() / 2) {
        return TurnRight;
    }
    for (int i = 0; i < 6; ++i) {
        if (!faces[i].isEmpty() && faces[i].containsPoint(pos, Qt::OddEvenFill)) {
            return i;
        }
    }
    return -1;
}

void ViewCube::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    const int hit = hitTest(event->pos());
    if (hit != hover) {
        hover = hit;
        setCursor(hit >= 0 ? Qt::PointingHandCursor : Qt::ArrowCursor);
        update();
    }
}

void ViewCube::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    hover = -1;
    update();
}

void ViewCube::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (hitTest(event->pos()) >= 0) {
        event->accept();  // nicht an die 3D-Navigation weiterreichen
    }
    else {
        event->ignore();
    }
}

void ViewCube::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    const int hit = hitTest(event->pos());
    if (hit < 0) {
        return;
    }
    if (hit == Home) {  // Iso-Ansicht und ganzes Modell einpassen (in den freien Bereich wie Fit All)
        QTimer::singleShot(0, viewer, [v = viewer] { v->viewHome(Camera::rotation(Camera::Isometric)); });
        return;
    }
    if (hit == TurnLeft || hit == TurnRight) {
        // um die eigene Blickachse drehen: rechts = Bild dreht im Uhrzeigersinn
        const float angle = float(M_PI / 2) * (hit == TurnRight ? 1.F : -1.F);
        QTimer::singleShot(0, viewer, [v = viewer, angle] {
            v->setCameraOrientation(SbRotation(SbVec3f(0, 0, 1), angle) * v->getCameraOrientation());
        });
        return;
    }
    const char* command = Faces[hit].command;
    QTimer::singleShot(0, [command] { Application::Instance->commandManager().runCommandByName(command); });
}
