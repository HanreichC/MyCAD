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

    // bleibt frei: Bogen, Haken, Ellipse, Zickzack, Punkt
    assert(recognize(ellipse({0, 0}, 30, 30, 0.5, M_PI)).kind == Kind::Free);
    std::vector<P> hook = line({0, 0}, {50, 0}, 0.3);
    for (const P& q : line({50, 0}, {50, 40}, 0.3)) {
        hook.push_back(q);
    }
    assert(recognize(hook).kind == Kind::Free);
    assert(recognize(ellipse({0, 0}, 60, 25, 0.5)).kind == Kind::Free);
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

    std::puts("scribble shapes: ok");
    return 0;
}
