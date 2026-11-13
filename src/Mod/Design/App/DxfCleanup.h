// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// DXF einfügen: Winzlinge und Doppelte erkennen, bevor die Kanten in die Skizze gehen. Platinen- und Laser-DXFs
/// bringen oft tausende davon mit (Kreise mit 0,00008 mm Radius, jede Linie zweimal); in der Skizze bremsen sie und
/// stören Profile. Ohne FreeCAD, damit es sich allein prüfen lässt: tests/dxf_cleanup_check.cpp

#include <algorithm>
#include <array>
#include <cmath>
#include <numbers>
#include <set>
#include <vector>

namespace DxfCleanup
{

/// Ein Element der Zeichnung, wie es die Prüfung braucht (Längen in mm, Winkel im Bogenmaß gegen den Uhrzeigersinn)
struct Piece
{
    enum class Kind
    {
        Line,    ///< a = Start x, y; b = Ende x, y
        Circle,  ///< a = Mittelpunkt x, y; r = Radius
        Arc,     ///< wie Circle, dazu start, end
        Other    ///< Ellipse, Spline …: nur Größe (size), nie doppelt
    };
    Kind kind = Kind::Other;
    std::array<double, 2> a {}, b {};
    double r = 0, start = 0, end = 0;
    double size = 0;  ///< nur Other: Diagonale der Bounding Box
};

/// kennzeichnende Länge: Linienlänge, Radius, Bogenlänge (der kleinere Wert zählt bei Bögen), sonst size
inline double extent(const Piece& p)
{
    switch (p.kind) {
        case Piece::Kind::Line:
            return std::hypot(p.b[0] - p.a[0], p.b[1] - p.a[1]);
        case Piece::Kind::Circle:
            return p.r;
        case Piece::Kind::Arc: {
            double sweep = std::fmod(p.end - p.start, 2 * std::numbers::pi);
            if (sweep <= 0) {
                sweep += 2 * std::numbers::pi;
            }
            return std::min(p.r, p.r * sweep);
        }
        case Piece::Kind::Other:
            break;
    }
    return p.size;
}

struct Result
{
    std::vector<bool> keep;  ///< je Element: übernehmen?
    int tiny = 0;            ///< entfernte Winzlinge
    int duplicates = 0;      ///< entfernte Doppelte (das erste bleibt)
};

/// Welche Elemente übernommen werden. tiny: kleiner als tolerance; doppelt: gleiche Art und gleiche Lage bis auf
/// tolerance (Linien auch umgekehrt gezeichnet). ponytail: Abgleich über gerundete Werte; zwei fast gleiche Elemente
/// genau an einer Rundungsgrenze gelten als verschieden (bleiben also beide, nichts geht verloren)
inline Result cleanup(const std::vector<Piece>& pieces, double tolerance, bool removeTiny, bool removeDuplicates)
{
    Result result;
    result.keep.assign(pieces.size(), true);
    const auto q = [tolerance](double v) { return std::llround(v / tolerance); };
    const auto angle = [&q](double v) {  // Winkel als Punkt auf dem Einheitskreis: 0 und 2π sind gleich
        return std::array<long long, 2> {q(std::cos(v) * 1000), q(std::sin(v) * 1000)};
    };
    std::set<std::array<long long, 8>> seen;
    for (size_t i = 0; i < pieces.size(); ++i) {
        const Piece& p = pieces[i];
        if (removeTiny && extent(p) < tolerance) {
            result.keep[i] = false;
            ++result.tiny;
            continue;
        }
        if (!removeDuplicates || p.kind == Piece::Kind::Other) {
            continue;
        }
        std::array<long long, 8> key {static_cast<long long>(p.kind)};
        if (p.kind == Piece::Kind::Line) {
            std::array<long long, 2> s {q(p.a[0]), q(p.a[1])}, e {q(p.b[0]), q(p.b[1])};
            if (e < s) {
                std::swap(s, e);
            }
            key = {0, s[0], s[1], e[0], e[1], 0, 0, 0};
        }
        else {
            key = {static_cast<long long>(p.kind), q(p.a[0]), q(p.a[1]), q(p.r), 0, 0, 0, 0};
            if (p.kind == Piece::Kind::Arc) {
                const auto s = angle(p.start), e = angle(p.end);
                key[4] = s[0], key[5] = s[1], key[6] = e[0], key[7] = e[1];
            }
        }
        if (!seen.insert(key).second) {
            result.keep[i] = false;
            ++result.duplicates;
        }
    }
    return result;
}

}  // namespace DxfCleanup
