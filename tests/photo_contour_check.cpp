// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung von Foto wird Skizze (Phase 11.9) ohne FreeCAD:
//   g++ -std=c++20 -I src tests/photo_contour_check.cpp -o /tmp/photo && /tmp/photo

#include <Mod/Design/App/PhotoContour.h>

#include <cassert>
#include <cmath>
#include <cstdio>

using namespace PhotoContour;

namespace
{
double area(const Loop& l)  // mit Vorzeichen (Umlaufsinn)
{
    double a = 0;
    for (size_t i = 0; i < l.size(); ++i) {
        const Point& p = l[i];
        const Point& q = l[(i + 1) % l.size()];
        a += p.x * q.y - q.x * p.y;
    }
    return a / 2;
}
}  // namespace

int main()
{
    // helles Papier 120 x 90, dunkle Platte 60 x 40 bei (30, 25), darin ein Loch r = 8 bei (60, 45); etwas Rauschen
    const int w = 120, h = 90;
    std::vector<std::uint8_t> img(w * h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            const bool plate = x >= 30 && x < 90 && y >= 25 && y < 65;
            const bool hole = std::hypot(x + 0.5 - 60, y + 0.5 - 45) < 8;
            const int noise = ((x * 7 + y * 13) % 11) - 5;
            img[y * w + x] = static_cast<std::uint8_t>((plate && !hole ? 50 : 210) + noise);
        }
    }
    const int t = otsu(img);
    assert(t >= 55 && t < 205);  // irgendwo zwischen dunkel (45…55) und hell (205…215)

    const auto mask = partMask(img, w, h);
    size_t inside = 0;
    for (auto m : mask) {
        inside += m;
    }
    assert(inside > 60 * 40 - 220 && inside < 60 * 40 - 180);  // Platte ohne Loch (π·8² ≈ 201)

    const auto loops = contours(img, w, h, 1.0);
    assert(loops.size() == 2);  // außen und das Loch
    const Loop& outer = std::abs(area(loops[0])) > std::abs(area(loops[1])) ? loops[0] : loops[1];
    const Loop& hole = &outer == &loops[0] ? loops[1] : loops[0];
    assert(outer.size() == 4);                         // ein Rechteck: vier Ecken
    assert(std::abs(std::abs(area(outer)) - 2400) < 1e-9);
    assert(area(outer) * area(hole) < 0);              // Loch andersherum
    assert(std::abs(std::abs(area(hole)) - 201) < 25); // ungefähr ein Kreis r = 8
    assert(hole.size() >= 8 && hole.size() <= 40);     // vereinfacht, aber noch rund
    double minX = 1e9, maxX = -1e9;
    for (const auto& p : outer) {
        minX = std::min(minX, p.x);
        maxX = std::max(maxX, p.x);
    }
    assert(minX == 30 && maxX == 90);  // Kanten genau auf den Pixelgrenzen

    // Kreise als Kreise: das Loch wird einer (Mitte und Radius genau), der rechteckige Umriss nicht
    const auto shapes = outlines(img, w, h, 1.5);
    assert(shapes.size() == 2);
    int circles = 0;
    for (const auto& o : shapes) {
        if (o.circle) {
            ++circles;
            assert(std::abs(o.c.centre.x - 60) < 0.2 && std::abs(o.c.centre.y - 45) < 0.2);
            assert(std::abs(o.c.radius - 8) < 0.3);
        }
        else {
            assert(o.points.size() == 4);
        }
    }
    assert(circles == 1);
    Circle c;
    Loop square;  // Quadrat 20 x 20, an den Kanten abgetastet wie ein Umriss: kein Kreis
    for (int i = 0; i < 20; ++i) {
        square.push_back({double(i), 0});
        square.push_back({20, double(i)});
        square.push_back({20.0 - i, 20});
        square.push_back({0, 20.0 - i});
    }
    assert(fitCircle(square, c) > 1.5);

    // Rasterpapier: Kästchen 25 px (Linien 2 px, hellgrau), darauf ein dunkles Teil; die Periode stimmt auf 1/20 Pixel
    {
        const int gw = 800, gh = 600;
        std::vector<std::uint8_t> grid(gw * gh);
        for (int y = 0; y < gh; ++y) {
            for (int x = 0; x < gw; ++x) {
                const bool line = (x % 25) < 2 || (y % 25) < 2;
                const bool part = x >= 200 && x < 520 && y >= 150 && y < 390;
                const int light = 200 + ((x + 3 * y) % 7);  // ungleichmäßiges Papier
                grid[y * gw + x] = static_cast<std::uint8_t>(part ? 55 : line ? light - 35 : light + 25);
            }
        }
        const auto m = partMask(grid, gw, gh);
        const double p = gridPeriod(grid, gw, gh, m);
        assert(std::abs(p - 25) < 0.05);
        const auto parts = outlines(grid, gw, gh);  // das Teil wird trotz Raster gefunden: 320 px breit
        assert(parts.size() == 1 && parts[0].points.size() == 4);
        // ohne Raster: 0
        assert(gridPeriod(img, w, h, partMask(img, w, h)) == 0);
    }

    // nichts im Bild: leer
    std::vector<std::uint8_t> blank(w * h, 200);
    assert(contours(blank, w, h).empty());

    std::puts("photo contour ok");
    return 0;
}
