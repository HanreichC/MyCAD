// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung der DXF-Bereinigung (Winzlinge, Doppelte), ohne FreeCAD:
//   g++ -std=c++20 -I src tests/dxf_cleanup_check.cpp -o /tmp/dxf && /tmp/dxf

#include <Mod/Design/App/DxfCleanup.h>

#include <cassert>
#include <cstdio>
#include <numbers>

using namespace DxfCleanup;
using Kind = Piece::Kind;

static Piece line(double x0, double y0, double x1, double y1)
{
    Piece p;
    p.kind = Kind::Line;
    p.a = {x0, y0};
    p.b = {x1, y1};
    return p;
}

static Piece circle(double x, double y, double r)
{
    Piece p;
    p.kind = Kind::Circle;
    p.a = {x, y};
    p.r = r;
    return p;
}

static Piece arc(double x, double y, double r, double s, double e)
{
    Piece p = circle(x, y, r);
    p.kind = Kind::Arc;
    p.start = s;
    p.end = e;
    return p;
}

int main()
{
    constexpr double tol = 0.001;
    constexpr double pi = std::numbers::pi;

    // Winzlinge: Kreis aus einem Platinen-DXF (0,0000762 mm), Nulllinie, Bogen mit winzigem Winkel; normale bleiben
    {
        Piece other;
        other.size = 0.0005;
        const std::vector<Piece> in {circle(1, 1, 0.0000762), line(2, 2, 2, 2.0000001), arc(0, 0, 5, 0, 1e-5),
                                     circle(1, 1, 0.6), line(0, 0, 10, 0), arc(0, 0, 0.01, 0, pi), other};
        const Result r = cleanup(in, tol, true, false);
        assert(r.tiny == 4 && r.duplicates == 0);
        assert((r.keep == std::vector<bool> {false, false, false, true, true, true, false}));
    }

    // Doppelte: gleiche Linie (auch rückwärts), gleicher Kreis, gleicher Bogen (auch mit 2π statt 0); das erste bleibt
    {
        const std::vector<Piece> in {line(0, 0, 10, 0), line(10, 0, 0, 0), line(0, 0, 10, 0.0000001),
                                     circle(5, 5, 2), circle(5, 5, 2), arc(0, 0, 3, 0, pi / 2), arc(0, 0, 3, 2 * pi, pi / 2)};
        const Result r = cleanup(in, tol, false, true);
        assert(r.duplicates == 4 && r.tiny == 0);
        assert((r.keep == std::vector<bool> {true, false, false, true, false, true, false}));
    }

    // Verschieden genug bleibt: Linie 0,01 mm daneben, anderer Radius, Kreis vs. Bogen, anderer Bogenwinkel
    {
        const std::vector<Piece> in {line(0, 0, 10, 0), line(0, 0.01, 10, 0.01), circle(5, 5, 2), circle(5, 5, 2.01),
                                     arc(5, 5, 2, 0, 2 * pi - 0.1), arc(0, 0, 3, 0, pi / 2), arc(0, 0, 3, 0, pi / 3)};
        const Result r = cleanup(in, tol, true, true);
        assert(r.duplicates == 0 && r.tiny == 0);
    }

    // Ausgeschaltet: nichts entfernt
    {
        const std::vector<Piece> in {circle(1, 1, 0.0000762), line(0, 0, 10, 0), line(0, 0, 10, 0)};
        const Result r = cleanup(in, tol, false, false);
        assert(r.tiny == 0 && r.duplicates == 0 && (r.keep == std::vector<bool> {true, true, true}));
    }

    // Winzling wird nicht zusätzlich als Doppelter gezählt
    {
        const std::vector<Piece> in {circle(1, 1, 0.0000762), circle(1, 1, 0.0000762)};
        const Result r = cleanup(in, tol, true, true);
        assert(r.tiny == 2 && r.duplicates == 0);
    }

    std::puts("dxf_cleanup_check: ok");
    return 0;
}
