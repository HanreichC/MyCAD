// SPDX-License-Identifier: LGPL-2.1-or-later

#include "ViewCube.h"
#include "Shell.h"

#include <Gui/Application.h>
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

#include <algorithm>
#include <numeric>

using namespace Gui::Shell;

namespace
{
constexpr qreal Width = 120, Height = 150, CenterX = 60, CenterY = 64, Scale = 29;
constexpr int Home = 6;
const QRectF HomeRect(6, Height - 32, 26, 26);

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

bool isDark()
{
    return false;  // MyCAD ist immer hell
}

QColor accent()
{
    return isDark() ? QColor(10, 132, 255) : QColor(0, 122, 255);
}
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
    const bool dark = isDark();
    const SbRotation toCamera = viewer->getCameraOrientation().inverse();
    auto project = [&](const SbVec3f& w) {
        SbVec3f c;
        toCamera.multVec(w, c);
        return QPointF(CenterX + c[0] * Scale, CenterY - c[1] * Scale);
    };

    // weicher Schatten unter dem Würfel
    QRadialGradient shadow(QPointF(CenterX, CenterY + 46), 44);
    shadow.setColorAt(0, QColor(0, 0, 0, dark ? 90 : 38));
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

    QFont font(QStringLiteral("Inter"));
    font.setPixelSize(19);
    font.setWeight(QFont::DemiBold);
    for (int i : order) {
        if (depth[i] < 0.02F) {
            continue;  // abgewandt
        }
        const Face& f = Faces[i];
        // oben-links, oben-rechts, unten-rechts, unten-links (aus Sicht von außen)
        QPolygonF quad {project(f.n - f.u + f.v), project(f.n + f.u + f.v), project(f.n + f.u - f.v),
                        project(f.n - f.u - f.v)};
        faces[i] = quad;

        const qreal light = 0.86 + 0.14 * depth[i];
        QColor fill = dark ? QColor::fromRgbF(0.24 * light, 0.24 * light, 0.27 * light)
                           : QColor::fromRgbF(0.97 * light, 0.975 * light, 0.985 * light);
        if (hover == i) {
            const QColor a = accent();
            fill = QColor::fromRgbF(fill.redF() * 0.55 + a.redF() * 0.45, fill.greenF() * 0.55 + a.greenF() * 0.45,
                                    fill.blueF() * 0.55 + a.blueF() * 0.45);
        }
        p->setBrush(fill);
        p->setPen(QPen(dark ? QColor(255, 255, 255, 40) : QColor(0, 0, 0, 38), 1.2, Qt::SolidLine, Qt::RoundCap,
                       Qt::RoundJoin));
        p->drawPolygon(quad);

        if (depth[i] > 0.35F) {  // nur gut lesbare Seiten beschriften
            QTransform t;
            if (QTransform::quadToQuad(QPolygonF(QRectF(0, 0, 100, 100)), quad, t)) {
                p->save();
                p->setTransform(t, true);
                p->setFont(font);
                p->setPen(hover == i ? QColor(Qt::white)
                                     : (dark ? QColor(235, 235, 245, 200) : QColor(60, 60, 67, 190)));
                p->drawText(QRectF(0, 0, 100, 100), Qt::AlignCenter, Gui::Shell::T(f.label));
                p->restore();
            }
        }
    }

    // Home-Knopf (Iso-Ansicht)
    p->setBrush(hover == Home ? accent() : (dark ? QColor(58, 58, 64, 230) : QColor(255, 255, 255, 230)));
    p->setPen(QPen(dark ? QColor(255, 255, 255, 40) : QColor(0, 0, 0, 30), 1));
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
    p->setPen(QPen(hover == Home ? QColor(Qt::white) : (dark ? QColor(245, 245, 247) : QColor(29, 29, 31)), 1.6,
                   Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p->drawPath(house);
}

int ViewCube::hitTest(const QPointF& pos) const
{
    if (QLineF(pos, HomeRect.center()).length() <= HomeRect.width() / 2) {
        return Home;
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
    const char* command = hit == Home ? "Std_ViewIsometric" : Faces[hit].command;
    QTimer::singleShot(0, [command] { Application::Instance->commandManager().runCommandByName(command); });
}
