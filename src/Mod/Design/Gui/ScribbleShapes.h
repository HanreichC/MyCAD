// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// "Halten zum Begradigen" in Scribbles: erkennt in einem Freihand-Strich eine Linie, einen Kreis oder ein Rechteck.
/// Reine Mathematik in Blatt-Koordinaten (2D, Einheit egal, alle Toleranzen sind relativ), ohne Abhängigkeiten.
/// Prüfung: tests/scribble_shapes_check.cpp

#include <algorithm>
#include <cmath>
#include <vector>

namespace ScribbleShapes
{

struct P
{
    double x = 0, y = 0;
};

enum class Kind  ///< gleiche Nummern wie Design::Scribble::Kind
{
    Free,
    Line,
    Circle,
    Rectangle
};

struct Shape
{
    Kind kind = Kind::Free;
    std::vector<P> points;  ///< Linie: 2 Punkte; Kreis und Rechteck geschlossen (letzter = erster)
};

inline double dist(P a, P b)
{
    return std::hypot(a.x - b.x, a.y - b.y);
}

inline double length(const std::vector<P>& p)
{
    double l = 0;
    for (size_t i = 1; i < p.size(); ++i) {
        l += dist(p[i - 1], p[i]);
    }
    return l;
}

/// n Punkte gleichmäßig nach Weglänge: langsam gezeichnete Stellen bekommen so kein größeres Gewicht
inline std::vector<P> resample(std::vector<P> p, size_t n)
{
    const double total = length(p);
    if (p.size() < 2 || total <= 0 || n < 2) {
        return p;
    }
    const double step = total / double(n - 1);
    std::vector<P> out {p.front()};
    double walked = 0;
    for (size_t i = 1; i < p.size() && out.size() < n; ++i) {
        const double d = dist(p[i - 1], p[i]);
        if (d > 0 && walked + d >= step) {
            const double t = (step - walked) / d;
            const P q {p[i - 1].x + t * (p[i].x - p[i - 1].x), p[i - 1].y + t * (p[i].y - p[i - 1].y)};
            out.push_back(q);
            p.insert(p.begin() + long(i), q);
            walked = 0;
        }
        else {
            walked += d;
        }
    }
    while (out.size() < n) {
        out.push_back(p.back());
    }
    return out;
}

/// gleitender Mittelwert über ±3 Punkte: Zittern macht den Weg sonst viel länger, als der Strich ist
inline std::vector<P> smooth(const std::vector<P>& p)
{
    std::vector<P> out(p.size());
    for (size_t i = 0; i < p.size(); ++i) {
        const size_t from = i < 3 ? 0 : i - 3, to = std::min(p.size() - 1, i + 3);
        for (size_t k = from; k <= to; ++k) {
            out[i] = {out[i].x + p[k].x / double(to - from + 1), out[i].y + p[k].y / double(to - from + 1)};
        }
    }
    return out;
}

/// b so verschieben, dass a→b genau waagerecht oder senkrecht ist, wenn es höchstens tolDeg davon abweicht
inline P snapAxis(P a, P b, double tolDeg = 5)
{
    const double dx = b.x - a.x, dy = b.y - a.y;
    const double off = std::atan2(std::min(std::abs(dx), std::abs(dy)), std::max(std::abs(dx), std::abs(dy)));
    if (off * 180 / M_PI > tolDeg) {
        return b;
    }
    return std::abs(dx) >= std::abs(dy) ? P {b.x, a.y} : P {a.x, b.y};
}

namespace detail
{
inline P rotate(P p, double angle)
{
    const double c = std::cos(angle), s = std::sin(angle);
    return {c * p.x - s * p.y, s * p.x + c * p.y};
}

/// Rechteck, das die Punkte in einem um angle gedrehten Koordinatensystem umschließt: min/max in diesem System
inline void bounds(const std::vector<P>& pts, double angle, P& lo, P& hi)
{
    lo = {1e300, 1e300};
    hi = {-1e300, -1e300};
    for (const P& q : pts) {
        const P r = rotate(q, -angle);
        lo = {std::min(lo.x, r.x), std::min(lo.y, r.y)};
        hi = {std::max(hi.x, r.x), std::max(hi.y, r.y)};
    }
}
}  // namespace detail

/// Linie (fast gerade), sonst bei geschlossenem Strich Rechteck (Punkte auf dem Rand des kleinsten umschließenden
/// Rechtecks, alle vier Ecken getroffen) oder Kreis (Abstand zur Mitte fast überall gleich). Alles andere bleibt frei.
/// ponytail: keine Ellipsen, Dreiecke oder Bögen; die Toleranzen sind Erfahrungswerte für Hand-Striche
inline Shape recognize(const std::vector<P>& raw)
{
    if (raw.size() < 3) {
        return {};
    }
    const double len = length(smooth(raw));
    const P a = raw.front(), b = raw.back();
    const double chord = dist(a, b);
    if (len <= 0) {
        return {};
    }
    if (chord > 0.8 * len) {
        double dev = 0;
        for (const P& q : raw) {
            dev = std::max(dev, std::abs((b.x - a.x) * (a.y - q.y) - (a.x - q.x) * (b.y - a.y)) / chord);
        }
        if (dev < 0.06 * chord) {
            return {Kind::Line, {a, snapAxis(a, b)}};
        }
        return {};
    }
    if (chord > 0.25 * len) {
        return {};  // offen: Bogen, Haken, Wellenlinie
    }
    const std::vector<P> pts = resample(raw, 96);

    // Rechteck zuerst: ein Quadrat hat um seine Mitte fast so gleichmäßige Abstände wie ein wackliger Kreis
    double bestAngle = 0, bestArea = 1e300;
    for (int deg = 0; deg < 90; ++deg) {
        P lo, hi;
        detail::bounds(pts, deg * M_PI / 180, lo, hi);
        const double area = (hi.x - lo.x) * (hi.y - lo.y);
        if (area < bestArea) {
            bestArea = area;
            bestAngle = deg * M_PI / 180;
        }
    }
    if (bestAngle < 6 * M_PI / 180 || bestAngle > 84 * M_PI / 180) {
        bestAngle = 0;  // fast achsparallel: genau achsparallel
    }
    P lo, hi;
    detail::bounds(pts, bestAngle, lo, hi);
    const double w = hi.x - lo.x, h = hi.y - lo.y, side = std::min(w, h);
    if (side > 0.08 * std::max(w, h)) {
        double edge = 0;
        for (const P& q : pts) {
            const P r = detail::rotate(q, -bestAngle);
            edge += std::min({r.x - lo.x, hi.x - r.x, r.y - lo.y, hi.y - r.y});
        }
        const P corners[] = {{lo.x, lo.y}, {hi.x, lo.y}, {hi.x, hi.y}, {lo.x, hi.y}};
        bool allCorners = true;
        for (const P& c : corners) {
            double nearest = 1e300;
            for (const P& q : pts) {
                nearest = std::min(nearest, dist(detail::rotate(q, -bestAngle), c));
            }
            allCorners = allCorners && nearest < 0.15 * side;
        }
        if (allCorners && edge / double(pts.size()) < 0.06 * side) {
            Shape s {Kind::Rectangle, {}};
            for (const P& c : corners) {
                s.points.push_back(detail::rotate(c, bestAngle));
            }
            s.points.push_back(s.points.front());
            return s;
        }
    }

    P c;
    for (const P& q : pts) {
        c = {c.x + q.x / double(pts.size()), c.y + q.y / double(pts.size())};
    }
    double mean = 0, sq = 0;
    for (const P& q : pts) {
        const double r = dist(q, c);
        mean += r / double(pts.size());
        sq += r * r / double(pts.size());
    }
    const double sd = std::sqrt(std::max(0.0, sq - mean * mean));
    if (mean > 0 && sd < 0.1 * mean) {
        Shape s {Kind::Circle, {}};
        constexpr int n = 96;
        for (int i = 0; i <= n; ++i) {
            const double t = 2 * M_PI * i / n;
            s.points.push_back({c.x + mean * std::cos(t), c.y + mean * std::sin(t)});
        }
        return s;
    }
    return {};
}

enum class Drag  ///< Form-Werkzeuge, die man aufzieht
{
    Rectangle,  ///< a, b: gegenüberliegende Ecken
    Ellipse,    ///< a, b: Ecken des umschließenden Rechtecks
    Triangle,   ///< a, b: Ecken des umschließenden Rechtecks, Spitze oben in der Mitte
    Circle,     ///< a: Mitte, b: auf dem Rand
    Hexagon,    ///< a: Mitte, b: eine Ecke
    Arrow       ///< a: Ende, b: Spitze; head: Länge der Spitze
};

/// Punkte einer aufgezogenen Form. Geschlossene Formen enden auf ihrem ersten Punkt; Kreis und Ellipse haben 96 + 1
/// Punkte, Punkt 0 liegt auf der x-Halbachse, Punkt 24 auf der y-Halbachse. Der Pfeil läuft Ende → Spitze → Flügel →
/// Flügel → Spitze: ein Strich ohne doppelte Stücke, die Spitze ist ein geschlossenes Dreieck.
inline std::vector<P> dragged(Drag d, P a, P b, double head = 0)
{
    constexpr int n = 96;
    const auto round = [](P c, double rx, double ry) {
        std::vector<P> p;
        for (int i = 0; i <= n; ++i) {
            const double t = 2 * M_PI * i / n;
            p.push_back({c.x + rx * std::cos(t), c.y + ry * std::sin(t)});
        }
        return p;
    };
    const P lo {std::min(a.x, b.x), std::min(a.y, b.y)}, hi {std::max(a.x, b.x), std::max(a.y, b.y)};
    switch (d) {
        case Drag::Rectangle:
            return {a, {b.x, a.y}, b, {a.x, b.y}, a};
        case Drag::Ellipse:
            return round({(lo.x + hi.x) / 2, (lo.y + hi.y) / 2}, (hi.x - lo.x) / 2, (hi.y - lo.y) / 2);
        case Drag::Triangle:
            return {{lo.x, lo.y}, {hi.x, lo.y}, {(lo.x + hi.x) / 2, hi.y}, {lo.x, lo.y}};
        case Drag::Circle:
            return round(a, dist(a, b), dist(a, b));
        case Drag::Hexagon: {
            std::vector<P> p;
            for (int i = 0; i <= 6; ++i) {
                p.push_back(detail::rotate({b.x - a.x, b.y - a.y}, M_PI / 3 * (i % 6)));
                p.back() = {a.x + p.back().x, a.y + p.back().y};
            }
            return p;
        }
        case Drag::Arrow: {
            const double len = dist(a, b);
            if (len <= 0) {
                return {a, b};
            }
            const double h = std::min(head, 0.4 * len), ux = (b.x - a.x) / len, uy = (b.y - a.y) / len;
            const P base {b.x - ux * h, b.y - uy * h};
            const double w = h * 0.55;  // Flügel je ~29° zur Achse
            return {a, b, {base.x - uy * w, base.y + ux * w}, {base.x + uy * w, base.y - ux * w}, b};
        }
    }
    return {a, b};
}

/// Douglas-Peucker: nur die Punkte, die mehr als tol von der Verbindung ihrer Nachbarn abweichen
inline std::vector<P> simplify(const std::vector<P>& p, double tol)
{
    if (p.size() < 3) {
        return p;
    }
    std::vector<bool> keep(p.size(), false);
    keep.front() = keep.back() = true;
    std::vector<std::pair<size_t, size_t>> todo {{0, p.size() - 1}};
    while (!todo.empty()) {
        const auto [a, b] = todo.back();
        todo.pop_back();
        const double len = dist(p[a], p[b]);
        double worst = 0;
        size_t at = a;
        for (size_t i = a + 1; i < b; ++i) {
            const double d = len > 0
                ? std::abs((p[b].x - p[a].x) * (p[a].y - p[i].y) - (p[a].x - p[i].x) * (p[b].y - p[a].y)) / len
                : dist(p[i], p[a]);
            if (d > worst) {
                worst = d;
                at = i;
            }
        }
        if (worst > tol) {
            keep[at] = true;
            todo.push_back({a, at});
            todo.push_back({at, b});
        }
    }
    std::vector<P> out;
    for (size_t i = 0; i < p.size(); ++i) {
        if (keep[i]) {
            out.push_back(p[i]);
        }
    }
    return out;
}

/// Umrandete Fläche zum Füllen: ohne Zittern (simplify mit tol) und geschlossen. Wer über den Anfang hinaus
/// weiterzeichnet, dessen Überhang fällt weg (Schnitt am Punkt im letzten Drittel, der dem Anfang am nächsten ist):
/// sonst kreuzte sich der Umriss und die Überlappung bliebe leer.
/// ponytail: Umrisse, die sich mittendrin kreuzen (Acht), füllen nur die ungeraden Bereiche
inline std::vector<P> lasso(const std::vector<P>& raw, double tol)
{
    std::vector<P> p = simplify(raw, tol);
    if (p.size() < 3) {
        return p;
    }
    size_t cut = p.size() - 1;
    for (size_t i = p.size() * 2 / 3; i < p.size(); ++i) {
        if (i > 1 && dist(p[i], p.front()) < dist(p[cut], p.front())) {
            cut = i;
        }
    }
    p.resize(cut + 1);
    p.push_back(p.front());
    return p;
}

/// Freihand-Strich für eine Skizze: vereinfacht (tol) und an Knicken über 45° geteilt. Ein Stück aus zwei Punkten wird
/// eine Linie, längere ein Spline durch seine Punkte; aufeinanderfolgende Stücke teilen ihren Endpunkt.
inline std::vector<std::vector<P>> pieces(const std::vector<P>& p, double tol)
{
    const std::vector<P> q = simplify(p, tol);
    std::vector<std::vector<P>> out;
    if (q.size() < 2) {
        return out;
    }
    std::vector<P> piece {q.front()};
    for (size_t i = 1; i < q.size(); ++i) {
        piece.push_back(q[i]);
        if (i + 1 < q.size()) {
            const double a1 = std::atan2(q[i].y - q[i - 1].y, q[i].x - q[i - 1].x);
            const double a2 = std::atan2(q[i + 1].y - q[i].y, q[i + 1].x - q[i].x);
            const double turn = std::abs(std::remainder(a2 - a1, 2 * M_PI));
            if (turn > M_PI / 4) {
                out.push_back(piece);
                piece = {q[i]};
            }
        }
    }
    out.push_back(piece);
    return out;
}

}  // namespace ScribbleShapes
