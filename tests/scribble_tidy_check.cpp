// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung der Schönschrift von Scribbles (Handschrift aufräumen), ohne FreeCAD:
//   g++ -std=c++20 -I src tests/scribble_tidy_check.cpp -o /tmp/tidy && /tmp/tidy

#include <Mod/Design/Gui/ScribbleTidy.h>

#include <cassert>
#include <cstdio>

using namespace ScribbleTidy;

namespace
{

constexpr double Xh = 10;  // x-Höhe in mm

/// Druckschrift aus "o" (Kreis) und "l" (Strich von oben nach unten), Grundlinie y = 0, Einheit x-Höhe
Stroke glyphO(double x)
{
    Stroke s;
    for (int i = 0; i <= 40; ++i) {
        const double t = 2 * M_PI * i / 40;
        s.push_back({x + 0.4 + 0.35 * std::cos(t), 0.5 + 0.5 * std::sin(t), 0.3});
    }
    return s;
}
Stroke glyphL(double x)
{
    Stroke s;
    for (int i = 0; i <= 30; ++i) {
        s.push_back({x + 0.1, 1.7 * (1 - i / 30.0), 0.3});
    }
    return s;
}

struct Distortion
{
    double dy, scale, shear;
};

/// Zeile "olo olo olo": je Wort versetzt, anders groß und schräg, die ganze Zeile gekippt, mit Handzittern
std::vector<Stroke> line(double baseline, double tilt, const std::vector<Distortion>& words)
{
    std::vector<Stroke> out;
    double cursor = 0;
    int n = 0;
    for (const Distortion& d : words) {
        for (Stroke s : {glyphO(0), glyphL(0.9), glyphO(1.4)}) {
            for (Pt& p : s) {
                const double x = (p.x + p.y * d.shear) * d.scale + cursor, y = p.y * d.scale + d.dy;
                const double jx = 0.03 * std::sin(++n * 2.3), jy = 0.03 * std::cos(n * 1.7);
                p.x = Xh * (x * std::cos(tilt) - y * std::sin(tilt) + jx);
                p.y = Xh * (x * std::sin(tilt) + y * std::cos(tilt) + jy) + baseline;
                p.w *= 1 + 0.5 * std::sin(n * 0.9);  // Druck schwankt
            }
            out.push_back(s);
        }
        cursor += 2.2 * d.scale + 0.9 + 0.4 * (n % 3);
    }
    return out;
}

double bottom(const Stroke& s)
{
    double v = INFINITY;
    for (const Pt& p : s) {
        v = std::min(v, p.y);
    }
    return v;
}
double height(const Stroke& s)
{
    double lo = INFINITY, hi = -INFINITY;
    for (const Pt& p : s) {
        lo = std::min(lo, p.y);
        hi = std::max(hi, p.y);
    }
    return hi - lo;
}
double left(const std::vector<Stroke>& S, size_t from, size_t to)
{
    double v = INFINITY;
    for (size_t i = from; i < to; ++i) {
        for (const Pt& p : S[i]) {
            v = std::min(v, p.x);
        }
    }
    return v;
}
double right(const std::vector<Stroke>& S, size_t from, size_t to)
{
    double v = -INFINITY;
    for (size_t i = from; i < to; ++i) {
        for (const Pt& p : S[i]) {
            v = std::max(v, p.x);
        }
    }
    return v;
}
/// Schräge des "l": waagrechter Versatz je Höhe
double slant(const Stroke& l)
{
    return (l.front().x - l.back().x) / (l.front().y - l.back().y);
}
double spread(const std::vector<double>& v)
{
    return *std::max_element(v.begin(), v.end()) - *std::min_element(v.begin(), v.end());
}

struct Metrics
{
    std::vector<double> bases, sizes, slants, gaps;
};
Metrics measure(const std::vector<Stroke>& S, size_t firstWord, size_t words)
{
    Metrics m;
    for (size_t w = firstWord; w < firstWord + words; ++w) {
        const size_t i = 3 * w;
        m.bases.push_back((bottom(S[i]) + bottom(S[i + 1]) + bottom(S[i + 2])) / 3);
        m.sizes.push_back((height(S[i]) + height(S[i + 2])) / 2);
        m.slants.push_back(slant(S[i + 1]));
        if (w > firstWord) {
            m.gaps.push_back(left(S, i, i + 3) - right(S, i - 3, i));
        }
    }
    return m;
}

}  // namespace

int main()
{
    std::vector<Stroke> page = line(0, 0.07, {{0.3, 1.0, 0.0}, {-0.25, 1.35, 0.25}, {0.15, 0.8, -0.1}});
    const std::vector<Stroke> second = line(-3.2 * Xh, -0.05, {{0.0, 1.1, 0.1}, {0.2, 0.9, 0.0}, {-0.1, 1.2, 0.15}});
    page.insert(page.end(), second.begin(), second.end());

    const Metrics before = measure(page, 0, 3);
    std::printf("vorher:  Grundlinien %.2f mm, x-Höhen %.2f mm, Schrägen %.3f, Lücken %.2f mm\n", spread(before.bases),
                spread(before.sizes), spread(before.slants), spread(before.gaps));
    assert(spread(before.bases) > 3 && spread(before.sizes) > 4 && spread(before.slants) > 0.25);

    const std::vector<Stroke> neat = tidy(page);
    assert(neat.size() == page.size());
    for (size_t i = 0; i < page.size(); ++i) {
        assert(neat[i].size() == page[i].size());  // gleiche Punktzahl: Überblenden geht
        for (const Pt& p : neat[i]) {
            assert(std::isfinite(p.x) && std::isfinite(p.y) && std::isfinite(p.w) && p.w > 0);
        }
    }
    for (size_t line = 0; line < 2; ++line) {
        const Metrics after = measure(neat, 3 * line, 3);
        std::printf("Zeile %zu: Grundlinien %.2f mm, x-Höhen %.2f mm, Schrägen %.3f, Lücken %.2f mm\n", line + 1,
                    spread(after.bases), spread(after.sizes), spread(after.slants), spread(after.gaps));
        assert(spread(after.bases) < 0.1 * Xh);    // auf einer Linie
        assert(spread(after.sizes) < 0.08 * Xh);   // gleich groß
        assert(spread(after.slants) < 0.05);       // gleich schräg
        assert(spread(after.gaps) < 0.05 * Xh);    // gleiche Wortabstände
    }
    // zwei Zeilen bleiben zwei Zeilen und beginnen am selben Rand
    const double lineStep = measure(neat, 0, 1).bases[0] - measure(neat, 3, 1).bases[0];
    std::printf("Zeilenabstand %.2f mm, linke Ränder %.2f / %.2f mm\n", lineStep, left(neat, 0, 9), left(neat, 9, 18));
    assert(lineStep > 2.5 * Xh && lineStep < 4 * Xh);
    assert(std::abs(left(neat, 0, 9) - left(neat, 9, 18)) < 0.05 * Xh);

    // Strichstärke gleichmäßiger
    double lo = INFINITY, hi = 0, nlo = INFINITY, nhi = 0;
    for (size_t i = 0; i < page.size(); ++i) {
        for (size_t j = 0; j < page[i].size(); ++j) {
            lo = std::min(lo, page[i][j].w), hi = std::max(hi, page[i][j].w);
            nlo = std::min(nlo, neat[i][j].w), nhi = std::max(nhi, neat[i][j].w);
        }
    }
    assert(nhi - nlo < 0.3 * (hi - lo));

    // aufrecht statt der eigenen Schräge
    Options upright;
    upright.upright = true;
    for (double s : measure(tidy(page, upright), 0, 3).slants) {
        assert(std::abs(s) < 0.05);
    }

    // Stärke: halb überblendet liegt zwischen vorher und nachher
    const Stroke half = blend(page[1], neat[1], 0.5);
    assert(std::abs(half[5].x - (page[1][5].x + neat[1][5].x) / 2) < 1e-9);

    // Schrift oder Zeichnung? 10 mm x-Höhe bei 0,5 mm je Pixel = 20 px: Schrift. Zwei große Striche: keine.
    assert(looksLikeWriting(page, 0.5));
    assert(!looksLikeWriting(page, 0.05));  // so nah herangezoomt ist das keine Schrift mehr
    assert(!looksLikeWriting({page[1]}, 0.5));  // ein Strich allein
    assert(tidy({}).empty());
    assert(tidy({{{1, 2, 0.3}}, {{4, 2, 0.3}}}).size() == 2);  // nur Punkte: bleibt heil

    std::puts("ok");
    return 0;
}
