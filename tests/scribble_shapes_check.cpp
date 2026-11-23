// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung der Formerkennung von Scribbles ("Halten zum Begradigen"), ohne FreeCAD:
//   g++ -std=c++20 -I src tests/scribble_shapes_check.cpp -o /tmp/shapes && /tmp/shapes

#include <Mod/Design/Gui/ScribbleShapes.h>

#include <cassert>
#include <cstdio>

using namespace ScribbleShapes;

namespace
{
/// Handzittern: gleichmäßig, aber nicht periodisch passend zur Form
double jitter(int i, double amount)
{
    return amount * std::sin(i * 2.3) * std::cos(i * 0.7);
}

std::vector<P> line(P a, P b, double noise)
{
    std::vector<P> p;
    for (int i = 0; i <= 60; ++i) {
        const double t = i / 60.0;
        p.push_back({a.x + t * (b.x - a.x) + jitter(i, noise), a.y + t * (b.y - a.y) + jitter(i + 7, noise)});
    }
    return p;
}

std::vector<P> ellipse(P c, double rx, double ry, double noise, double sweep = 2 * M_PI)
{
    std::vector<P> p;
    for (int i = 0; i <= 120; ++i) {
        const double t = sweep * i / 120;
        p.push_back({c.x + rx * std::cos(t) + jitter(i, noise), c.y + ry * std::sin(t) + jitter(i + 3, noise)});
    }
    return p;
}

std::vector<P> rectangle(P c, double w, double h, double angle, double noise)
{
    const P corners[] = {{-w / 2, -h / 2}, {w / 2, -h / 2}, {w / 2, h / 2}, {-w / 2, h / 2}, {-w / 2, -h / 2}};
    std::vector<P> p;
    int k = 0;
    for (int e = 0; e < 4; ++e) {
        for (int i = 0; i < 25; ++i, ++k) {
            const double t = i / 25.0;
            P q {corners[e].x + t * (corners[e + 1].x - corners[e].x), corners[e].y + t * (corners[e + 1].y - corners[e].y)};
            q = {std::cos(angle) * q.x - std::sin(angle) * q.y, std::sin(angle) * q.x + std::cos(angle) * q.y};
            p.push_back({c.x + q.x + jitter(k, noise), c.y + q.y + jitter(k + 5, noise)});
        }
    }
    p.push_back(p.front());
    return p;
}
}  // namespace

int main()
{
    // Linie: gerade erkannt, fast waagerecht rastet ein, schräg bleibt schräg
    Shape s = recognize(line({0, 0}, {100, 4}, 0.8));
    assert(s.kind == Kind::Line && s.points.size() == 2);
    assert(std::abs(s.points[1].y - s.points[0].y) < 1e-9);  // 2,3° → waagerecht
    s = recognize(line({0, 0}, {60, 60}, 0.8));
    assert(s.kind == Kind::Line && std::abs(s.points[1].y - 60) < 3);

    // Kreis, auch zittrig und leicht überzeichnet
    s = recognize(ellipse({10, 20}, 30, 30, 1.0, 2.1 * M_PI));
    assert(s.kind == Kind::Circle);
    assert(std::abs(dist(s.points[0], {10, 20}) - 30) < 2);
    assert(dist(s.points.front(), s.points.back()) < 1e-9);

    // Rechteck und Quadrat (ein Quadrat ist kein Kreis), gedreht bleibt gedreht, fast gerade wird gerade
    s = recognize(rectangle({0, 0}, 80, 40, 0, 0.8));
    assert(s.kind == Kind::Rectangle && s.points.size() == 5);
    assert(std::abs(s.points[0].y - s.points[1].y) < 1e-9);
    s = recognize(rectangle({0, 0}, 50, 50, 0.04, 0.8));
    assert(s.kind == Kind::Rectangle);
    assert(std::abs(s.points[0].y - s.points[1].y) < 1e-9);
    s = recognize(rectangle({0, 0}, 80, 40, 30 * M_PI / 180, 0.5));
    assert(s.kind == Kind::Rectangle);
    assert(std::abs(std::atan2(s.points[1].y - s.points[0].y, s.points[1].x - s.points[0].x) - 30 * M_PI / 180) < 0.05
           || std::abs(std::atan2(s.points[1].y - s.points[0].y, s.points[1].x - s.points[0].x) + 60 * M_PI / 180) < 0.05);

    // Aufräumliste B11: Bogen (halb und flach), Ellipse (auch gedreht), Dreieck
    s = recognize(ellipse({0, 0}, 30, 30, 0.5, M_PI));
    assert(s.kind == Kind::Arc && s.points.size() == 49);
    assert(dist(s.points.front(), {30, 0}) < 1.5 && dist(s.points.back(), {-30, 0}) < 1.5);
    assert(std::abs(dist(s.points[24], {0, 0}) - 30) < 1 && s.points[24].y > 25);  // über oben, nicht unten herum
    s = recognize(ellipse({0, -100}, 100, 100, 0.3, M_PI / 4));  // 45°-Bogen: Sehne fast so lang wie der Bogen
    assert(s.kind == Kind::Arc);
    s = recognize(ellipse({0, 0}, 60, 25, 0.5));
    assert(s.kind == Kind::Ellipse && s.points.size() == 97);
    assert(std::abs(dist(s.points[0], {0, 0}) - 60) < 2 && std::abs(dist(s.points[24], {0, 0}) - 25) < 2);
    {
        std::vector<P> tilted = ellipse({0, 0}, 50, 20, 0.4);
        for (P& q : tilted) {
            q = {std::cos(0.5) * q.x - std::sin(0.5) * q.y, std::sin(0.5) * q.x + std::cos(0.5) * q.y};
        }
        s = recognize(tilted);
        assert(s.kind == Kind::Ellipse);
        const double major = std::max(dist(s.points[0], {0, 0}), dist(s.points[24], {0, 0}));
        assert(std::abs(major - 50) < 2.5);
    }
    std::vector<P> tri = line({0, 0}, {60, 0}, 0.4);
    for (const P& q : line({60, 0}, {30, 45}, 0.4)) {
        tri.push_back(q);
    }
    for (const P& q : line({30, 45}, {0, 0}, 0.4)) {
        tri.push_back(q);
    }
    s = recognize(tri);
    assert(s.kind == Kind::Polygon && s.points.size() == 4);
    std::vector<P> fromSide(tri.begin() + 30, tri.end());  // mitten auf der Grundseite angefangen
    fromSide.insert(fromSide.end(), tri.begin(), tri.begin() + 31);
    s = recognize(fromSide);
    assert(s.kind == Kind::Polygon && s.points.size() == 4);
    for (const P& corner : {P {0, 0}, P {60, 0}, P {30, 45}}) {
        double nearest = 1e9;
        for (const P& q : s.points) {
            nearest = std::min(nearest, dist(q, corner));
        }
        assert(nearest < 2);
    }

    // bleibt frei: Haken, Zickzack, Punkt
    std::vector<P> hook = line({0, 0}, {50, 0}, 0.3);
    for (const P& q : line({50, 0}, {50, 40}, 0.3)) {
        hook.push_back(q);
    }
    assert(recognize(hook).kind == Kind::Free);
    std::vector<P> zigzag;
    for (int i = 0; i <= 10; ++i) {
        zigzag.push_back({i * 10.0, i % 2 ? 12.0 : 0.0});
    }
    assert(recognize(zigzag).kind == Kind::Free);
    assert(recognize({{1, 1}, {1, 1}, {1, 1}}).kind == Kind::Free);

    // Einrasten an den Achsen
    assert(snapAxis({0, 0}, {100, 3}).y == 0);
    assert(snapAxis({0, 0}, {3, 100}).x == 0);
    assert(snapAxis({0, 0}, {100, 30}).y == 30);

    // Freihand für die Skizze: Zickzack wird lauter Linien (Spline-Pole schössen über die Ecken), ein Bogen ein Stück
    std::vector<std::vector<P>> parts = pieces(zigzag, 0.5);
    assert(parts.size() == 10);
    for (size_t i = 0; i < parts.size(); ++i) {
        assert(parts[i].size() == 2);
        assert(i == 0 || dist(parts[i].front(), parts[i - 1].back()) == 0);  // Stücke hängen zusammen
    }
    parts = pieces(ellipse({0, 0}, 30, 30, 0.2, M_PI), 0.6);
    assert(parts.size() == 1 && parts[0].size() > 3 && parts[0].size() < 30);
    assert(simplify(line({0, 0}, {100, 0}, 0.1), 1).size() == 2);

    // aufgezogene Formen: geschlossen, an der richtigen Stelle, Ellipse mit Halbachsen an Punkt 0 und 24
    const auto closed = [](const std::vector<P>& p) { return p.size() > 3 && dist(p.front(), p.back()) < 1e-9; };
    std::vector<P> f = dragged(Drag::Rectangle, {10, 10}, {0, 4});
    assert(f.size() == 5 && closed(f) && f[2].x == 0 && f[2].y == 4);
    f = dragged(Drag::Ellipse, {0, 0}, {20, -10});
    assert(f.size() == 97 && closed(f) && std::abs(f[0].x - 20) < 1e-9 && std::abs(f[0].y + 5) < 1e-9);
    assert(std::abs(f[24].x - 10) < 1e-9 && std::abs(f[24].y) < 1e-9);
    f = dragged(Drag::Triangle, {0, 10}, {8, 0});
    assert(f.size() == 4 && closed(f) && f[2].x == 4 && f[2].y == 10 && f[0].y == 0 && f[1].y == 0);  // Spitze oben
    f = dragged(Drag::Circle, {5, 5}, {8, 9});
    assert(f.size() == 97 && closed(f) && std::abs(dist(f[37], {5, 5}) - 5) < 1e-9);
    f = dragged(Drag::Hexagon, {0, 0}, {0, 10});
    assert(f.size() == 7 && closed(f) && dist(f[0], {0, 10}) < 1e-9 && std::abs(dist(f[3], {0, -10})) < 1e-9);
    for (size_t i = 1; i < f.size(); ++i) {
        assert(std::abs(dist(f[i - 1], f[i]) - 10) < 1e-9);  // regelmäßig: Kante = Radius
    }
    f = dragged(Drag::Arrow, {0, 0}, {100, 0}, 12);
    assert(f.size() == 5 && f[1].x == 100 && f[4].x == 100 && std::abs(f[2].x - 88) < 1e-9 && f[2].y > 0 && f[3].y < 0);
    assert(std::abs(dragged(Drag::Arrow, {0, 0}, {10, 0}, 12)[2].x - 6) < 1e-9);  // kurzer Pfeil: Spitze 40 %

    // Umrandung zum Füllen: über den Anfang hinaus gezeichnet, der Überhang fällt weg; Zittern wird weniger Punkte
    std::vector<P> loop = ellipse({0, 0}, 30, 30, 0.3, 2.3 * M_PI);
    f = lasso(loop, 0.5);
    assert(closed(f) && f.size() < loop.size());
    double swept = 0;  // ohne Überlappung läuft der Umriss nur einmal um die Mitte (mit Überhang: 2,6 π)
    for (size_t i = 1; i < f.size(); ++i) {
        swept += std::abs(std::remainder(std::atan2(f[i].y, f[i].x) - std::atan2(f[i - 1].y, f[i - 1].x), 2 * M_PI));
    }
    assert(swept < 2 * M_PI + 0.5);
    assert(lasso({{0, 0}, {1, 1}}, 0.5).size() == 2);

    // 12.12 Gesten (Bildschirm, y nach unten): Häkchen und Durchkritzeln, nicht verwechselbar mit Formen
    const std::vector<P> tick = {{0, 0}, {5, 6}, {10, 12}, {16, 4}, {22, -4}, {28, -12}, {34, -20}};
    assert(isTick(tick));
    assert(!isTick({{0, 0}, {10, 20}, {20, 0}}));            // "V" mit gleichen Schenkeln
    assert(!isTick({{0, 0}, {-5, 6}, {-10, 12}, {-25, -10}}));  // Haken nach links oben
    assert(!isTick({{0, 0}, {30, 0}}));                      // Linie
    std::vector<P> scratch;
    for (int i = 0; i < 6; ++i) {
        scratch.push_back({i % 2 ? 40.0 : 0.0, i * 3.0});
    }
    assert(isScratch(scratch));
    assert(!isScratch(ellipse({0, 0}, 20, 20, 0, 4 * M_PI)));  // zweimal herum: dreht nie scharf
    assert(!isScratch(tick));
    assert(!isTick(scratch));

    // 12.12 Pfeil in einem Strich: Schaft, dann ein Haken schräg zurück
    std::vector<P> arrow;
    for (int i = 0; i <= 20; ++i) {
        arrow.push_back({i * 5.0, 0});
    }
    arrow.push_back({93, 4});
    arrow.push_back({86, 8});
    assert(arrowTip(arrow) == 20);
    arrow.resize(21);
    assert(arrowTip(arrow) == -1);  // ohne Haken: eine Linie
    assert(arrowTip(tick) == -1);
    assert(arrowTip(scratch) == -1);
    assert(arrowTip(dragged(Drag::Arrow, {0, 0}, {100, 0}, 12)) == 1);  // das Pfeil-Werkzeug: Spitze ist Punkt 1

    std::puts("scribble shapes: ok");
    return 0;
}
