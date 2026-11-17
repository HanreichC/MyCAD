// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Phase 11.9 Foto wird Skizze: aus einem Graustufenbild die Umrisse des Teils (außen und seine Löcher) als
/// geschlossene Linienzüge in Pixeln. Das Teil ist die größte zusammenhängende Fläche, die den Bildrand nicht berührt
/// (hell auf dunkel oder dunkel auf hell, Schwelle nach Otsu). Ohne Qt und FreeCAD, damit es sich allein prüfen lässt:
/// tests/photo_contour_check.cpp

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <map>
#include <utility>
#include <vector>

namespace PhotoContour
{

struct Point
{
    double x, y;
};
using Loop = std::vector<Point>;  ///< geschlossen, erster Punkt nicht wiederholt

/// Schwelle nach Otsu (größte Varianz zwischen hell und dunkel)
inline int otsu(const std::vector<std::uint8_t>& gray)
{
    double hist[256] = {};
    for (auto g : gray) {
        hist[g] += 1;
    }
    const double total = static_cast<double>(gray.size());
    double sum = 0;
    for (int i = 0; i < 256; ++i) {
        sum += i * hist[i];
    }
    double sumB = 0, wB = 0, best = -1;
    int threshold = 128;
    for (int t = 0; t < 256; ++t) {
        wB += hist[t];
        if (wB == 0 || wB == total) {
            continue;
        }
        sumB += t * hist[t];
        const double mB = sumB / wB, mF = (sum - sumB) / (total - wB);
        const double between = wB * (total - wB) * (mB - mF) * (mB - mF);
        if (between > best) {
            best = between;
            threshold = t;
        }
    }
    return threshold;
}

/// Maske des Teils: größte Fläche einer Klasse, die den Rand nicht berührt; Löcher darin bleiben 0
inline std::vector<std::uint8_t> partMask(const std::vector<std::uint8_t>& gray, int w, int h)
{
    const int t = otsu(gray);
    std::vector<int> label(gray.size(), -1);
    std::vector<std::uint8_t> best;
    size_t bestSize = 0;
    std::vector<int> stack;
    for (int start = 0; start < w * h; ++start) {
        if (label[start] >= 0) {
            continue;
        }
        const bool dark = gray[start] <= t;
        std::vector<int> members;
        bool border = false;
        stack.assign(1, start);
        label[start] = start;
        while (!stack.empty()) {
            const int i = stack.back();
            stack.pop_back();
            members.push_back(i);
            const int x = i % w, y = i / w;
            border = border || x == 0 || y == 0 || x == w - 1 || y == h - 1;
            const int next[4][2] = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
            for (const auto& n : next) {
                if (n[0] < 0 || n[1] < 0 || n[0] >= w || n[1] >= h) {
                    continue;
                }
                const int j = n[1] * w + n[0];
                if (label[j] < 0 && (gray[j] <= t) == dark) {
                    label[j] = start;
                    stack.push_back(j);
                }
            }
        }
        if (!border && members.size() > bestSize) {
            bestSize = members.size();
            best.assign(gray.size(), 0);
            for (int i : members) {
                best[i] = 1;
            }
        }
    }
    return best;  // leer: kein Teil gefunden
}

/// Umrisse der Maske (marching squares, Punkte auf Pixelkanten): außen und jedes Loch eine Schleife
inline std::vector<Loop> trace(const std::vector<std::uint8_t>& mask, int w, int h)
{
    if (mask.empty()) {
        return {};
    }
    const auto at = [&](int x, int y) { return x >= 0 && y >= 0 && x < w && y < h && mask[y * w + x]; };
    // Kanten zwischen Pixeln, die innen und außen trennen, als gerichtete Strecken (Inneres links); Punkte doppelt
    // skaliert, damit sie ganzzahlig sind
    std::map<std::pair<int, int>, std::pair<int, int>> next;
    for (int y = -1; y <= h; ++y) {
        for (int x = -1; x <= w; ++x) {
            if (!at(x, y)) {
                continue;
            }
            if (!at(x, y - 1)) {
                next[{2 * x, 2 * y}] = {2 * x + 2, 2 * y};  // oben
            }
            if (!at(x + 1, y)) {
                next[{2 * x + 2, 2 * y}] = {2 * x + 2, 2 * y + 2};  // rechts
            }
            if (!at(x, y + 1)) {
                next[{2 * x + 2, 2 * y + 2}] = {2 * x, 2 * y + 2};  // unten
            }
            if (!at(x - 1, y)) {
                next[{2 * x, 2 * y + 2}] = {2 * x, 2 * y};  // links
            }
        }
    }
    // ponytail: zwei Pixel, die sich nur an einer Ecke berühren, teilen einen Punkt; dann zählt die zuerst gefundene Kante
    std::vector<Loop> loops;
    while (!next.empty()) {
        Loop loop;
        auto start = next.begin()->first;
        auto p = start;
        do {
            loop.push_back({p.first / 2.0, p.second / 2.0});
            auto it = next.find(p);
            if (it == next.end()) {
                break;
            }
            p = it->second;
            next.erase(it);
        } while (p != start);
        if (loop.size() >= 4) {
            loops.push_back(loop);
        }
    }
    return loops;
}

/// Douglas-Peucker für einen geschlossenen Linienzug: weniger Punkte, höchstens tol Pixel Abweichung
inline Loop simplify(const Loop& loop, double tol)
{
    if (loop.size() < 4) {
        return loop;
    }
    const auto dist = [](const Point& p, const Point& a, const Point& b) {
        const double dx = b.x - a.x, dy = b.y - a.y, len = std::hypot(dx, dy);
        return len < 1e-12 ? std::hypot(p.x - a.x, p.y - a.y) : std::abs(dy * (p.x - a.x) - dx * (p.y - a.y)) / len;
    };
    std::vector<bool> keep(loop.size(), false);
    // offen machen an den zwei am weitesten auseinander liegenden Punkten
    size_t far = 0;
    double farD = -1;
    for (size_t i = 0; i < loop.size(); ++i) {
        const double d = std::hypot(loop[i].x - loop[0].x, loop[i].y - loop[0].y);
        if (d > farD) {
            farD = d;
            far = i;
        }
    }
    const auto run = [&](auto&& self, size_t a, size_t b) -> void {  // Indizes zyklisch, b > a (b kann loop.size() sein)
        double worst = -1;
        size_t at = a;
        for (size_t i = a + 1; i < b; ++i) {
            const double d = dist(loop[i % loop.size()], loop[a % loop.size()], loop[b % loop.size()]);
            if (d > worst) {
                worst = d;
                at = i;
            }
        }
        if (worst > tol) {
            keep[at % loop.size()] = true;
            self(self, a, at);
            self(self, at, b);
        }
    };
    keep[0] = keep[far] = true;
    run(run, 0, far);
    run(run, far, loop.size());
    Loop out;
    for (size_t i = 0; i < loop.size(); ++i) {
        if (keep[i]) {
            out.push_back(loop[i]);
        }
    }
    return out;
}

/// Alles zusammen: Umrisse des Teils, vereinfacht (tol in Pixeln)
inline std::vector<Loop> contours(const std::vector<std::uint8_t>& gray, int w, int h, double tol = 1.5)
{
    std::vector<Loop> out;
    for (const auto& loop : trace(partMask(gray, w, h), w, h)) {
        out.push_back(simplify(loop, tol));
    }
    return out;
}

struct Circle
{
    Point centre {0, 0};
    double radius = 0;
};

/// Kreis durch die Punkte nach kleinsten Quadraten (Kasa); liefert die größte Abweichung eines Punkts vom Kreis
inline double fitCircle(const Loop& loop, Circle& c)
{
    if (loop.size() < 3) {
        return 1e100;
    }
    double mx = 0, my = 0;
    for (const auto& p : loop) {
        mx += p.x;
        my += p.y;
    }
    mx /= loop.size();
    my /= loop.size();
    // x² + y² + D x + E y + F = 0 in Koordinaten um den Schwerpunkt: Normalgleichungen 3 x 3
    double a[3][4] = {};
    for (const auto& p : loop) {
        const double x = p.x - mx, y = p.y - my, z = -(x * x + y * y);
        const double row[3] = {x, y, 1};
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                a[i][j] += row[i] * row[j];
            }
            a[i][3] += row[i] * z;
        }
    }
    for (int i = 0; i < 3; ++i) {  // Gauß mit Spaltenpivot
        int pivot = i;
        for (int k = i + 1; k < 3; ++k) {
            pivot = std::abs(a[k][i]) > std::abs(a[pivot][i]) ? k : pivot;
        }
        std::swap(a[i], a[pivot]);
        if (std::abs(a[i][i]) < 1e-12) {
            return 1e100;
        }
        for (int k = 0; k < 3; ++k) {
            if (k != i) {
                const double f = a[k][i] / a[i][i];
                for (int j = i; j < 4; ++j) {
                    a[k][j] -= f * a[i][j];
                }
            }
        }
    }
    const double d = a[0][3] / a[0][0], e = a[1][3] / a[1][1], f = a[2][3] / a[2][2];
    const double r2 = d * d / 4 + e * e / 4 - f;
    if (r2 <= 0) {
        return 1e100;
    }
    c.centre = {mx - d / 2, my - e / 2};
    c.radius = std::sqrt(r2);
    double worst = 0;
    for (const auto& p : loop) {
        worst = std::max(worst, std::abs(std::hypot(p.x - c.centre.x, p.y - c.centre.y) - c.radius));
    }
    return worst;
}

/// Ein Umriss: Kreis (ein rundes Loch, ein runder Umriss) oder vereinfachter Linienzug
struct Outline
{
    bool circle = false;
    Circle c;
    Loop points;
};

/// Umrisse des Teils; ein Umriss, der höchstens tol Pixel (und nicht mehr als die Pixeltreppe) von einem Kreis abweicht
/// und mindestens 3 Pixel Radius hat, wird ein Kreis, sonst ein vereinfachter Linienzug
inline std::vector<Outline> outlines(const std::vector<std::uint8_t>& gray, int w, int h, double tol = 1.5)
{
    std::vector<Outline> out;
    for (const auto& loop : trace(partMask(gray, w, h), w, h)) {
        Outline o;
        o.circle = loop.size() >= 12 && fitCircle(loop, o.c) <= tol && o.c.radius >= 3;
        if (!o.circle) {
            o.points = simplify(loop, tol);
        }
        out.push_back(o);
    }
    return out;
}

}  // namespace PhotoContour
