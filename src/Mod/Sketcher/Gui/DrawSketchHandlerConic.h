// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <Gui/CommandT.h>
#include <Gui/Notifications.h>
#include <Mod/Sketcher/App/SketchObject.h>

#include "DrawSketchHandler.h"
#include "SnapManager.h"
#include "Utils.h"
#include "ViewProviderSketch.h"

namespace SketcherGui
{

/// Conic Curve wie in Fusion: Startpunkt, Endpunkt, Schulterpunkt.
/// Ergebnis ist ein rationaler quadratischer B-Spline (Gewicht w = rho/(1-rho), rho 0.5 = Parabel);
/// die Form lässt sich danach über den mittleren Kontrollpunkt und sein Gewicht ändern.
class DrawSketchHandlerConic: public DrawSketchHandler
{
public:
    void mouseMove(SnapManager::SnapHandle snapHandle) override
    {
        const Base::Vector2d pos = snapHandle.compute();
        if (points.empty()) {
            setPositionText(pos);
            return;
        }
        drawEdit(points.size() == 1 ? std::vector<Base::Vector2d> {points[0], pos}
                                    : sample(points[0], pos, points[1]));
    }

    bool pressButton(Base::Vector2d pos) override
    {
        points.push_back(pos);
        if (points.size() == 3) {
            create();  // beendet das Werkzeug; danach keinen Code mehr
        }
        return true;
    }

    bool releaseButton(Base::Vector2d) override
    {
        return true;
    }

private:
    QString getCrosshairCursorSVGName() const override
    {
        return QStringLiteral("Sketcher_Pointer_Create_BSpline");
    }

    static constexpr double Rho = 0.5;

    /// Kurvenpunkte für die Vorschau: B(t) = ((1-t)²a + 2t(1-t)w·apex + t²b) / ((1-t)² + 2t(1-t)w + t²)
    static std::vector<Base::Vector2d> sample(const Base::Vector2d& a, const Base::Vector2d& apex, const Base::Vector2d& b)
    {
        const double w = Rho / (1 - Rho);
        std::vector<Base::Vector2d> curve;
        for (int i = 0; i <= 48; ++i) {
            const double t = i / 48.0, s = 1 - t;
            const double d = s * s + 2 * t * s * w + t * t;
            curve.push_back((a * (s * s) + apex * (2 * t * s * w) + b * (t * t)) / d);
        }
        return curve;
    }

    void create()
    {
        const Base::Vector2d &a = points[0], &b = points[1], &apex = points[2];
        try {
            openCommand(QT_TRANSLATE_NOOP("Command", "Add conic curve"));
            Gui::cmdAppObjectArgs(
                sketchgui->getObject(),
                "addGeometry(Part.BSplineCurve([App.Vector(%f,%f,0),App.Vector(%f,%f,0),App.Vector(%f,%f,0)],"
                "[3,3],[0,1],False,2,[1,%f,1]),%s)",
                a.x, a.y, apex.x, apex.y, b.x, b.y, Rho / (1 - Rho), constructionModeAsBooleanText()
            );
            // Kontrollpunkte sichtbar machen, damit die Kurve wie in Fusion angepasst werden kann
            Gui::cmdAppObjectArgs(sketchgui->getObject(), "exposeInternalGeometry(%d)", getHighestCurveIndex());
            commitCommand();
            tryAutoRecomputeIfNotSolve(sketchgui->getObject<Sketcher::SketchObject>());
        }
        catch (const Base::Exception&) {
            abortCommand();
            Gui::NotifyError(sketchgui, QT_TRANSLATE_NOOP("Notifications", "Error"),
                             QT_TRANSLATE_NOOP("Notifications", "Failed to add conic curve"));
        }
        sketchgui->purgeHandler();  // löscht dieses Werkzeug
    }

    std::vector<Base::Vector2d> points;
};

}  // namespace SketcherGui
