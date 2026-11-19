// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Schönschrift in Scribbles: räumt Handschrift auf, ohne sie zu lesen. Zittern glätten, Zeilen gerade und in gleichem
/// Abstand, jedes Wort auf dieselbe x-Höhe und Schräge, gleiche Wortabstände und linker Rand, gleichmäßigere
/// Strichstärke. Die Buchstabenformen bleiben die eigenen. Jeder Strich behält seine Punktzahl, so lassen sich Vorher
/// und Nachher überblenden (Stärke, Gleiten). Reine Mathematik in Blatt-Koordinaten (2D, y nach oben, Einheit egal).
/// Prüfung: tests/scribble_tidy_check.cpp

#include <algorithm>
#include <cmath>
#include <vector>

namespace ScribbleTidy
{

struct Pt
{
    double x = 0, y = 0, w = 0;  ///< w: Strichbreite an diesem Punkt
};
using Stroke = std::vector<Pt>;

struct Options
{
    bool smooth = true, straight = true, size = true, slant = true, gaps = true, width = true;
    bool upright = false;  ///< Schräge: aufrecht statt der eigenen mittleren
    /// jede Zeile bleibt, wo sie steht: kein gemeinsamer linker Rand, kein gleicher Zeilenabstand (Rotstift: jede Zeile
    /// ist eine eigene Korrektur an ihrer Stelle im Modell)
    bool inPlace = false;
    /// alle Zeilen am linken Rand der Runde; ohne beginnt jede, wo sie anfängt, und follow richtet sie an der Zeile
    /// darüber aus (auch an schon Geschriebenem: die Fortsetzung einer Zeile bleibt rechts, wo sie hingehört)
    bool margin = true;
    /// je Strich die Nummer seines Worts, wie die Schrifterkennung es liest (ScribbleRead::words; leer oder -1: nicht
    /// gelesen). Trennt auch eng geschriebene Wörter („derPlan“), die sonst erst ab 0,6 x-Höhe Lücke zwei wären
    std::vector<int> word;
};

namespace detail
{

inline double quant(std::vector<double> a, double p)
{
    if (a.empty()) {
        return 0;
    }
    std::sort(a.begin(), a.end());
    const double i = double(a.size() - 1) * p;
    const size_t lo = size_t(std::floor(i)), hi = size_t(std::ceil(i));
    return a[lo] + (a[hi] - a[lo]) * (i - double(lo));
}

inline double median(const std::vector<double>& a)
{
    return quant(a, 0.5);
}

struct Box
{
    double minX = INFINITY, maxX = -INFINITY, minY = INFINITY, maxY = -INFINITY;
    double h() const
    {
        return maxY - minY;
    }
};

inline Box box(const Stroke& s)
{
    Box b;
    for (const Pt& p : s) {
        b.minX = std::min(b.minX, p.x);
        b.maxX = std::max(b.maxX, p.x);
        b.minY = std::min(b.minY, p.y);
        b.maxY = std::max(b.maxY, p.y);
    }
    return b;
}

/// Gauß über die Bogenlänge: nimmt das Zittern raus, zu den Enden hin bleibt der Strich, wo er war
inline void smooth(Stroke& s, double sigma)
{
    const size_t n = s.size();
    if (n < 3 || sigma <= 0) {
        return;
    }
    std::vector<double> arc(n, 0);
    for (size_t i = 1; i < n; ++i) {
        arc[i] = arc[i - 1] + std::hypot(s[i].x - s[i - 1].x, s[i].y - s[i - 1].y);
    }
    Stroke out = s;
    for (size_t i = 0; i < n; ++i) {
        double sx = 0, sy = 0, sw = 0, W = 0;
        for (size_t j = 0; j < n; ++j) {
            const double d = std::abs(arc[j] - arc[i]);
            if (d < 3 * sigma) {
                const double g = std::exp(-d * d / (2 * sigma * sigma));
                sx += g * s[j].x;
                sy += g * s[j].y;
                sw += g * s[j].w;
                W += g;
            }
        }
        const double edge = std::min(1.0, std::min(arc[i], arc[n - 1] - arc[i]) / sigma);
        out[i] = {s[i].x + (sx / W - s[i].x) * edge, s[i].y + (sy / W - s[i].y) * edge, sw / W};
    }
    s = out;
}

/// typische Strichhöhe (ohne Punkte), 0 wenn es nur Punkte gibt
inline double typicalHeight(const std::vector<Stroke>& S)
{
    std::vector<double> hs;
    for (const Stroke& s : S) {
        if (const double h = box(s).h(); h > 0) {
            hs.push_back(h);
        }
    }
    return quant(hs, 0.6);
}

/// Zeilen in Schreibreihenfolge: neue Zeile, wenn der Stift weit nach links und nach unten springt oder weit weg ist
/// (darüber, darunter oder weit rechts).
/// y nach unten; Ergebnis von oben nach unten sortiert.
inline std::vector<std::vector<size_t>> groupLines(const std::vector<Stroke>& S, double h)
{
    struct Line
    {
        std::vector<size_t> idx;
        std::vector<double> centers;
        double cy = 0, minX = INFINITY, maxX = -INFINITY;
    };
    std::vector<Line> lines;
    for (size_t i = 0; i < S.size(); ++i) {
        const Box b = box(S[i]);
        const double cy = (b.minY + b.maxY) / 2;
        // weit rechts oder links neben der Zeile (mehr als drei Zeichenhöhen Lücke, kein Wortabstand) beginnt etwas
        // Eigenes: zwei Rotstift-Korrekturen auf einer Höhe sind zwei Zeilen, auch wenn die linke als zweite kommt
        if (lines.empty() || std::abs(cy - lines.back().cy) > 1.6 * h
            || (b.minX < lines.back().maxX - 3 * h && cy > lines.back().cy + 0.7 * h) || b.minX > lines.back().maxX + 3 * h
            || b.maxX < lines.back().minX - 3 * h) {
            lines.emplace_back();
        }
        Line& L = lines.back();
        L.idx.push_back(i);
        L.centers.push_back(cy);
        L.cy = median(L.centers);
        L.minX = std::min(L.minX, b.minX);
        L.maxX = std::max(L.maxX, b.maxX);
    }
    std::sort(lines.begin(), lines.end(), [](const Line& a, const Line& b) { return a.cy < b.cy; });
    std::vector<std::vector<size_t>> out;
    for (const Line& L : lines) {
        out.push_back(L.idx);
    }
    return out;
}

}  // namespace detail

/// Zeilen der Striche (Blatt-Koordinaten, y nach oben), von oben nach unten, je Zeile die Nummern ihrer Striche
inline std::vector<std::vector<size_t>> lines(std::vector<Stroke> S)
{
    for (Stroke& s : S) {
        for (Pt& p : s) {
            p.y = -p.y;
        }
    }
    const double h = detail::typicalHeight(S);
    return h > 0 ? detail::groupLines(S, h) : std::vector<std::vector<size_t>> {};
}

/// Sieht die Gruppe nach Schrift aus? Mindestens zwei Striche, auf dem Bildschirm schriftgroß, zusammen nicht schmaler
/// als hoch. unitsPerPx: Blatt-Einheiten je Bildschirm-Pixel.
/// Nur die Größe: mit Schrifterkennung entscheidet danach noch, ob sie Schrift liest (ScribbleRead::looksRead in
/// Scribble.cpp); ohne bleibt eine Skizze aus kleinen Strichen ein Fall fürs Aufräumen (Rückgängig holt sie zurück).
/// Größer (Grafiktablett) gilt mit Schrifterkennung trotzdem als Schrift, wenn sie darin ein Wort ab drei Zeichen liest
inline bool looksLikeWriting(const std::vector<Stroke>& strokes, double unitsPerPx)
{
    if (strokes.size() < 2 || unitsPerPx <= 0) {
        return false;
    }
    detail::Box all;
    std::vector<double> heights;
    for (const Stroke& s : strokes) {
        const detail::Box b = detail::box(s);
        heights.push_back(b.h());
        all = {std::min(all.minX, b.minX), std::max(all.maxX, b.maxX), std::min(all.minY, b.minY), std::max(all.maxY, b.maxY)};
    }
    const double typical = detail::median(heights);
    const double tallest = *std::max_element(heights.begin(), heights.end());
    return typical > 0 && typical / unitsPerPx <= 60 && tallest / unitsPerPx <= 150 && all.maxX - all.minX >= typical;
}

inline Stroke blend(const Stroke& a, const Stroke& b, double k)
{
    Stroke out = a;
    for (size_t i = 0; i < out.size() && i < b.size(); ++i) {
        out[i] = {a[i].x + (b[i].x - a[i].x) * k, a[i].y + (b[i].y - a[i].y) * k, a[i].w + (b[i].w - a[i].w) * k};
    }
    return out;
}

/// Striche in Schreibreihenfolge (Zeile für Zeile, links nach rechts) → aufgeräumt, gleiche Punktzahl je Strich
inline std::vector<Stroke> tidy(std::vector<Stroke> S, const Options& o = {})
{
    using namespace detail;
    // innen y nach unten wie auf Papier: die Grundlinie ist das größte y einer Zeile
    const auto flip = [&S] {
        for (Stroke& s : S) {
            for (Pt& p : s) {
                p.y = -p.y;
            }
        }
    };
    flip();
    [&] {
        const double h = typicalHeight(S);
        if (h <= 0) {
            return;  // nur Punkte
        }
        if (o.smooth) {
            for (Stroke& s : S) {
                smooth(s, 0.1 * h);
            }
        }
        if (o.width) {
            std::vector<double> ws;
            for (const Stroke& s : S) {
                for (const Pt& p : s) {
                    ws.push_back(p.w);
                }
            }
            const double m = median(ws);
            for (Stroke& s : S) {
                for (Pt& p : s) {
                    p.w = 0.2 * p.w + 0.8 * m;
                }
            }
        }
        if (!(o.straight || o.size || o.slant || o.gaps)) {
            return;
        }
        std::vector<Box> B(S.size());
        const auto measure = [&](const std::vector<size_t>& idx) {
            for (size_t i : idx) {
                B[i] = box(S[i]);
            }
        };
        const auto each = [&S](const std::vector<size_t>& idx, auto f) {
            for (size_t i : idx) {
                for (Pt& p : S[i]) {
                    f(p);
                }
            }
        };
        for (size_t i = 0; i < S.size(); ++i) {
            B[i] = box(S[i]);
        }
        /// Striche, die mindestens frac so hoch sind wie der höchste: ohne Punkte, Querstriche und Kommas
        const auto tall = [&B](const std::vector<size_t>& idx, double frac) {
            double mh = 0;
            for (size_t i : idx) {
                mh = std::max(mh, B[i].h());
            }
            std::vector<size_t> out;
            for (size_t i : idx) {
                if (B[i].h() > frac * mh) {
                    out.push_back(i);
                }
            }
            return out.empty() ? idx : out;
        };
        const auto bottoms = [&B](const std::vector<size_t>& idx) {
            std::vector<double> v;
            for (size_t i : idx) {
                v.push_back(B[i].maxY);
            }
            return median(v);
        };

        struct Word
        {
            std::vector<size_t> idx;
            double minX = 0, maxX = 0, base = 0, size = 0, slant = 0;
            bool hasSlant = false;
        };
        struct Line
        {
            std::vector<size_t> idx;
            double base = 0, xh = 0;
            std::vector<Word> words;
            bool beside = false;  ///< eine andere Zeile steht auf gleicher Höhe daneben: beide bleiben, wo sie stehen
        };
        std::vector<Line> lines;
        for (auto& idx : groupLines(S, h)) {
            lines.emplace_back().idx = std::move(idx);
        }

        for (Line& L : lines) {
            // Neigung der Zeile: Ausgleichsgerade durch die Strich-Unterkanten, Unterlängen fallen als Ausreißer raus
            if (o.straight) {
                std::vector<std::pair<double, double>> pts;
                for (size_t i : tall(L.idx, 0.4)) {
                    const Pt low = *std::max_element(S[i].begin(), S[i].end(), [](const Pt& a, const Pt& b) { return a.y < b.y; });
                    pts.push_back({low.x, low.y});
                }
                bool fitted = false;
                double k = 0, mx = 0, my = 0;
                for (int pass = 0; pass < 2 && pts.size() >= 3; ++pass) {
                    mx = my = 0;
                    for (auto [x, y] : pts) {
                        mx += x / double(pts.size());
                        my += y / double(pts.size());
                    }
                    double sxx = 0, sxy = 0;
                    for (auto [x, y] : pts) {
                        sxx += (x - mx) * (x - mx);
                        sxy += (x - mx) * (y - my);
                    }
                    k = sxx > 0 ? sxy / sxx : 0;
                    fitted = true;
                    std::vector<std::pair<double, double>> keep;
                    for (auto [x, y] : pts) {
                        if (std::abs(y - (my + k * (x - mx))) < 0.3 * h) {
                            keep.push_back({x, y});
                        }
                    }
                    if (keep.size() >= 3) {
                        pts = keep;
                    }
                }
                if (fitted) {
                    const double a = -std::clamp(std::atan(k), -0.3, 0.3), c = std::cos(a), s = std::sin(a);
                    each(L.idx, [&](Pt& p) {
                        const double x = p.x - mx, y = p.y - my;
                        p.x = mx + x * c - y * s;
                        p.y = my + x * s + y * c;
                    });
                    measure(L.idx);
                }
            }
            const std::vector<size_t> t = tall(L.idx, 0.3);
            L.base = bottoms(t);
            std::vector<double> tops;
            for (size_t i : t) {
                tops.push_back(L.base - B[i].minY);
            }
            L.xh = quant(tops, 0.25);
            // Wörter: waagrecht überlappende Striche sind ein Stück (ein Buchstabe), eine große Lücke trennt Wörter, und
            // ist die ganze Zeile gelesen, auch eine Wortgrenze der Schrifterkennung (dann Wort für Wort sortiert)
            const auto wordOf = [&o](size_t i) { return i < o.word.size() ? o.word[i] : -1; };
            const bool read = std::all_of(L.idx.begin(), L.idx.end(), [&](size_t i) { return wordOf(i) >= 0; });
            const auto same = [&](size_t a, size_t b) { return !read || wordOf(a) == wordOf(b); };
            std::vector<size_t> order = L.idx;
            std::sort(order.begin(), order.end(), [&](size_t a, size_t b) {
                return read && wordOf(a) != wordOf(b) ? wordOf(a) < wordOf(b) : B[a].minX < B[b].minX;
            });
            std::vector<Word> units;
            for (size_t i : order) {
                if (!units.empty() && B[i].minX <= units.back().maxX + 0.02 * h && same(i, units.back().idx.front())) {
                    units.back().idx.push_back(i);
                    units.back().maxX = std::max(units.back().maxX, B[i].maxX);
                }
                else {
                    units.push_back({{i}, B[i].minX, B[i].maxX});
                }
            }
            for (const Word& u : units) {
                if (!L.words.empty() && u.minX - L.words.back().maxX < 0.6 * L.xh && same(u.idx.front(), L.words.back().idx.front())) {
                    Word& w = L.words.back();
                    w.idx.insert(w.idx.end(), u.idx.begin(), u.idx.end());
                    w.maxX = std::max(w.maxX, u.maxX);
                }
                else {
                    L.words.push_back(u);
                }
            }
        }
        // Gruppen auf gleicher Höhe (x-Höhen überlappen) sind getrennte Notizen nebeneinander: an den gemeinsamen linken
        // Rand gerückt, lägen sie übereinander
        for (Line& L : lines) {
            for (const Line& M : lines) {
                L.beside = L.beside || (&L != &M && std::abs(L.base - M.base) < (L.xh + M.xh) / 2);
            }
        }
        std::vector<Word*> words;
        std::vector<double> lineXh;
        for (Line& L : lines) {
            lineXh.push_back(L.xh);
            for (Word& w : L.words) {
                words.push_back(&w);
            }
        }
        const double pageXh = median(lineXh) > 0 ? median(lineXh) : h;

        // Schräglage je Wort aus den steilen Strichstücken (nach Länge gewichteter Median), Ziel: die eigene oder aufrecht
        if (o.slant) {
            std::vector<double> all;
            for (Word* w : words) {
                std::vector<std::pair<double, double>> v;  // Schräge, Gewicht
                double total = 0;
                for (size_t i : w->idx) {
                    const Stroke& p = S[i];
                    for (size_t j = 3; j < p.size(); j += 3) {
                        double dx = p[j].x - p[j - 3].x, dy = p[j].y - p[j - 3].y;
                        if (dy > 0) {
                            dx = -dx;
                            dy = -dy;
                        }
                        const double len = std::hypot(dx, dy);
                        if (len > 0 && -dy > 1.3 * std::abs(dx)) {
                            v.push_back({dx / -dy, len});
                            total += len;
                        }
                    }
                }
                std::sort(v.begin(), v.end());
                double acc = 0;
                for (auto [x, wt] : v) {
                    acc += wt;
                    if (acc >= total / 2) {
                        w->slant = x;
                        w->hasSlant = true;
                        all.push_back(x);
                        break;
                    }
                }
            }
            const double target = o.upright ? 0 : median(all);
            for (Word* w : words) {
                if (!w->hasSlant) {
                    continue;  // nichts Steiles drin (×, °, -): bleibt, wie es ist
                }
                const double base = bottoms(tall(w->idx, 0.3)), d = w->slant - target;
                each(w->idx, [&](Pt& p) { p.x -= (base - p.y) * d; });
                measure(w->idx);
            }
        }
        // Größe je Wort: x-Höhe. Wörter nur aus Ziffern oder Großbuchstaben misst die Versalhöhe.
        // ponytail: Versalhöhe = 1,6 x-Höhe fest angenommen; besser aus gemischten Wörtern des Blatts schätzen
        for (Word* w : words) {
            const std::vector<size_t> t = tall(w->idx, 0.3);
            w->base = bottoms(t);
            std::vector<double> tops;
            for (size_t i : t) {
                tops.push_back(w->base - B[i].minY);
            }
            const double q25 = quant(tops, 0.25);
            w->size = q25 > 1.3 * pageXh ? *std::max_element(tops.begin(), tops.end()) / 1.6 : q25;
        }
        if (o.size) {
            std::vector<double> sizes;
            for (Word* w : words) {
                sizes.push_back(w->size);
            }
            const double target = median(sizes);
            for (Word* w : words) {
                const double f = w->size > 0 ? std::clamp(target / w->size, 0.7, 1.45) : 1.0;
                double x0 = INFINITY;
                for (size_t i : w->idx) {
                    x0 = std::min(x0, B[i].minX);
                }
                each(w->idx, [&](Pt& p) {
                    p.x = x0 + (p.x - x0) * f;
                    p.y = w->base + (p.y - w->base) * f;
                });
                measure(w->idx);
            }
        }
        // Wörter auf die Grundlinie ihrer Zeile; ab drei Zeilen auch gleicher Zeilenabstand
        if (o.straight) {
            std::vector<Line*> stacked;  // Zeilen untereinander; die nebeneinander behalten ihre Höhe
            for (Line& L : lines) {
                if (!L.beside) {
                    stacked.push_back(&L);
                }
            }
            std::vector<double> gaps;
            for (size_t i = 1; i < stacked.size(); ++i) {
                gaps.push_back(stacked[i]->base - stacked[i - 1]->base);
            }
            const double step = gaps.size() > 1 && !o.inPlace ? median(gaps) : 0;
            for (Line& L : lines) {
                const size_t k = size_t(std::find(stacked.begin(), stacked.end(), &L) - stacked.begin());
                const double target = !L.beside && step > 0 && k > 0 ? stacked[0]->base + double(k) * step : L.base;
                for (Word& w : L.words) {
                    const double dy = target - w.base;
                    each(w.idx, [dy](Pt& p) { p.y += dy; });
                    w.base = target;
                    measure(w.idx);
                }
            }
        }
        // gleiche Wortabstände, alle Zeilen am selben linken Rand
        if (o.gaps) {
            const auto left = [&B](const Word& w) {
                double v = INFINITY;
                for (size_t i : w.idx) {
                    v = std::min(v, B[i].minX);
                }
                return v;
            };
            const auto right = [&B](const Word& w) {
                double v = -INFINITY;
                for (size_t i : w.idx) {
                    v = std::max(v, B[i].maxX);
                }
                return v;
            };
            std::vector<double> gaps;
            double margin = INFINITY;
            for (const Line& L : lines) {
                margin = L.beside ? margin : std::min(margin, left(L.words.front()));
                for (size_t i = 1; i < L.words.size(); ++i) {
                    gaps.push_back(left(L.words[i]) - right(L.words[i - 1]));
                }
            }
            const double gap = std::clamp(gaps.empty() ? pageXh : median(gaps), 0.55 * pageXh, 1.1 * pageXh);
            for (Line& L : lines) {
                double cursor = o.inPlace || !o.margin || L.beside ? left(L.words.front()) : margin;
                for (Word& w : L.words) {
                    const double dx = cursor - left(w);
                    each(w.idx, [dx](Pt& p) { p.x += dx; });
                    measure(w.idx);
                    cursor = right(w) + gap;
                }
            }
        }
    }();
    flip();
    return S;
}

/// Maße einer Zeile wie in tidy (y nach oben): Grundlinie, x-Höhe, Breite, typischer Wortabstand (0 bei einem Wort)
struct Row
{
    double base = 0, xh = 0, minX = INFINITY, maxX = -INFINITY, gap = 0;
};

inline Row row(const std::vector<Stroke>& S, const std::vector<size_t>& idx)
{
    using namespace detail;
    Row r;
    double tallest = 0;
    for (size_t i : idx) {
        const Box b = box(S[i]);
        tallest = std::max(tallest, b.h());
        r.minX = std::min(r.minX, b.minX);
        r.maxX = std::max(r.maxX, b.maxX);
    }
    std::vector<double> bottoms, tops;
    for (size_t i : idx) {
        if (const Box b = box(S[i]); b.h() > 0.3 * tallest) {
            bottoms.push_back(b.minY);
            tops.push_back(b.maxY);
        }
    }
    r.base = median(bottoms);
    for (double& t : tops) {
        t -= r.base;
    }
    r.xh = quant(tops, 0.25);
    // Wörter: Lücken ab 0,6 x-Höhe zwischen waagrecht nicht überlappenden Strichen
    std::vector<size_t> order = idx;
    std::sort(order.begin(), order.end(), [&S](size_t a, size_t b) { return box(S[a]).minX < box(S[b]).minX; });
    std::vector<double> gaps;
    double reach = -INFINITY;
    for (size_t i : order) {
        const Box b = box(S[i]);
        if (reach > -INFINITY && b.minX - reach >= 0.6 * r.xh) {
            gaps.push_back(b.minX - reach);
        }
        reach = std::max(reach, b.maxX);
    }
    r.gap = gaps.empty() ? 0 : median(gaps);
    return r;
}

/// Weiterschreiben nach einer Pause: tidy sieht nur die Striche seit der letzten Pause. Jede Zeile von fresh (eben
/// aufgeräumt, Blatt-Koordinaten) bekommt die x-Höhe der Zeile aus before (schon da, je Zeile die Nummern ihrer Striche),
/// an die sie anschließt: rechts daneben auf deren Grundlinie mit deren Wortabstand, oder darunter an deren linken Rand.
/// So wird, was mit abgesetztem Stift geschrieben ist, so gleich wie in einem Zug.
inline void follow(std::vector<Stroke>& fresh, std::vector<Stroke> before, std::vector<std::vector<size_t>> beforeLines)
{
    std::vector<Row> rows;
    for (const auto& idx : beforeLines) {
        rows.push_back(row(before, idx));
    }
    for (const std::vector<size_t>& idx : lines(fresh)) {  // von oben nach unten: die nächste kann an diese anschließen
        const Row F = row(fresh, idx);
        const Row* same = nullptr;
        const Row* above = nullptr;
        for (const Row& C : rows) {
            if (C.xh <= 0) {
                continue;
            }
            if (std::abs(F.base - C.base) < (F.xh + C.xh) / 2) {
                if (F.minX > C.maxX - C.xh && F.minX < C.maxX + 4 * C.xh && (!same || C.maxX > same->maxX)) {
                    same = &C;
                }
            }
            else if (C.base > F.base && C.base - F.base < 4 * C.xh && F.minX < C.maxX && F.maxX > C.minX
                     && (!above || C.base < above->base)) {
                above = &C;
            }
        }
        const Row* C = same ? same : above;
        if (!C || F.xh <= 0) {
            continue;
        }
        const double f = std::clamp(C->xh / F.xh, 0.7, 1.45);  // wie tidy je Wort
        const double x0 = same ? C->maxX + (C->gap > 0 ? C->gap : C->xh) : C->minX;
        const double y0 = same ? C->base : F.base;
        for (size_t i : idx) {
            for (Pt& p : fresh[i]) {
                p.x = x0 + (p.x - F.minX) * f;
                p.y = y0 + (p.y - F.base) * f;
            }
        }
        // gleich mit in den Bestand: die nächste Zeile von fresh schließt an diese an
        std::vector<size_t> added;
        for (size_t i : idx) {
            added.push_back(before.size());
            before.push_back(fresh[i]);
        }
        rows.push_back(row(before, added));
    }
}

}  // namespace ScribbleTidy
