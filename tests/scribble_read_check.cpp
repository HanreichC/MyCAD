// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung des Handschrift-Lesens von Scribbles mit dem echten Modell, ohne FreeCAD (im Dev-Container, onnxruntime-cpu):
//   g++ -std=c++20 -fPIC -DMYCAD_HTR -I src -I src/Mod/Design/Gui $(pkg-config --cflags Qt6Gui)
//       tests/scribble_read_check.cpp src/Mod/Design/Gui/ScribbleRead.cpp -I /usr/include/onnxruntime
//       $(pkg-config --libs Qt6Gui) -lonnxruntime -o /tmp/read && /tmp/read build/htr/model.onnx [/tmp/bilder]
// Schreibt synthetische Druckschrift (sauber und verkrakelt) und liest sie; der zweite Pfad speichert die Zeilenbilder.

#include <Mod/Design/App/RedPen.h>
#include <Mod/Design/Gui/ScribbleRead.h>

#include <QDir>

#include <cassert>
#include <cstdio>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <tuple>

using namespace ScribbleTidy;

namespace
{

using Poly = std::vector<std::pair<double, double>>;  // Einheit x-Höhe, y nach unten, Grundlinie 0

Poly arc(double cx, double cy, double rx, double ry, double t0, double t1, int n = 14)
{
    Poly p;
    for (int i = 0; i <= n; ++i) {
        const double t = (t0 + (t1 - t0) * i / n) * M_PI / 180;
        p.push_back({cx + rx * std::cos(t), cy + ry * std::sin(t)});
    }
    return p;
}
Poly cat(Poly a, const Poly& b)
{
    a.insert(a.end(), b.begin(), b.end());
    return a;
}
/// Catmull-Rom durch die Stützpunkte; doppelte Punkte ergeben Ecken
Poly spline(const Poly& P)
{
    Poly out;
    for (size_t i = 0; i + 1 < P.size(); ++i) {
        const auto& p0 = P[i ? i - 1 : 0];
        const auto& p1 = P[i];
        const auto& p2 = P[i + 1];
        const auto& p3 = P[std::min(P.size() - 1, i + 2)];
        const double len = std::hypot(p2.first - p1.first, p2.second - p1.second);
        if (len < 1e-9) {
            continue;
        }
        const int n = std::max(2, int(std::ceil(len / 0.05)));
        for (int k = 0; k < n; ++k) {
            const double t = double(k) / n, t2 = t * t, t3 = t2 * t;
            const auto f = [&](double a0, double a1, double a2, double a3) {
                return 0.5 * (2 * a1 + (-a0 + a2) * t + (2 * a0 - 5 * a1 + 4 * a2 - a3) * t2 + (-a0 + 3 * a1 - 3 * a2 + a3) * t3);
            };
            out.push_back({f(p0.first, p1.first, p2.first, p3.first), f(p0.second, p1.second, p2.second, p3.second)});
        }
    }
    out.push_back(P.back());
    return out;
}

struct Glyph
{
    double w;
    std::vector<Poly> strokes;
};
const std::map<QChar, Glyph>& glyphs()
{
    static const std::map<QChar, Glyph> g = [] {
        std::map<QChar, Glyph> m;
        const auto arch = [](double x0, double x1) { return cat(cat({{x0, -.55}}, arc((x0 + x1) / 2, -.55, (x1 - x0) / 2, .42, 180, 360, 10)), {{x1, 0}}); };
        m[QLatin1Char('o')] = {.85, {arc(.4, -.5, .32, .5, -80, -430, 20)}};
        m[QLatin1Char('a')] = {.9, {arc(.4, -.5, .32, .5, -30, -370, 18), {{.74, -1}, {.74, -.3}, {.78, -.05}, {.88, 0}}}};
        m[QLatin1Char('e')] = {.85, {cat({{.1, -.5}, {.72, -.52}}, arc(.41, -.5, .32, .5, -5, -310, 16))}};
        m[QLatin1Char('n')] = {.85, {{{.1, -1}, {.1, 0}}, arch(.1, .66)}};
        m[QLatin1Char('m')] = {1.3, {{{.1, -1}, {.1, 0}}, arch(.1, .6), arch(.6, 1.1)}};
        m[QLatin1Char('h')] = {.85, {{{.1, -1.7}, {.1, 0}}, arch(.1, .66)}};
        m[QLatin1Char('r')] = {.62, {{{.1, -1}, {.1, 0}}, cat({{.1, -.5}}, arc(.38, -.55, .26, .42, 180, 290, 6))}};
        m[QLatin1Char('u')] = {.85, {cat({{.1, -1}}, arc(.38, -.45, .28, .45, 180, 0, 10)), {{.66, -1}, {.66, 0}}}};
        m[QLatin1Char('g')] = {.9, {arc(.4, -.5, .32, .5, -30, -370, 18), cat({{.74, -1}, {.74, .35}}, arc(.42, .35, .32, .3, 0, 150, 8))}};
        m[QLatin1Char('l')] = {.45, {cat({{.15, -1.7}, {.14, -.25}}, arc(.3, -.25, .16, .25, 180, 90, 5))}};
        m[QLatin1Char('s')] = {.75, {{{.62, -.88}, {.42, -1}, {.18, -.9}, {.16, -.68}, {.4, -.52}, {.62, -.35}, {.6, -.1}, {.38, 0}, {.1, -.1}}}};
        m[QLatin1Char('B')] = {.85, {{{.1, -1.6}, {.1, 0}}, {{.1, -1.6}, {.45, -1.6}, {.65, -1.45}, {.63, -1.02}, {.4, -.86}, {.12, -.86}, {.12, -.86}, {.5, -.84}, {.74, -.6}, {.72, -.2}, {.5, -.02}, {.1, 0}}}};
        m[QLatin1Char('W')] = {1.15, {{{0, -1.6}, {.27, 0}, {.27, 0}, {.55, -1.05}, {.55, -1.05}, {.82, 0}, {.82, 0}, {1.1, -1.6}}}};
        m[QLatin1Char('F')] = {.72, {{{.1, -1.6}, {.1, 0}}, {{.1, -1.6}, {.68, -1.62}}, {{.1, -.85}, {.52, -.86}}}};
        m[QChar(0x00D8)] = {1.05, {arc(.5, -.8, .38, .8, -90, -450, 24), {{.05, .12}, {.95, -1.72}}}};  // Ø
        m[QLatin1Char('1')] = {.55, {{{.08, -1.25}, {.36, -1.6}, {.36, -1.6}, {.36, 0}}}};
        m[QLatin1Char('2')] = {.82, {{{.1, -1.25}, {.3, -1.58}, {.58, -1.5}, {.65, -1.1}, {.1, 0}, {.1, 0}, {.75, 0}}}};
        m[QLatin1Char('4')] = {.9, {{{.58, 0}, {.58, -1.6}, {.58, -1.6}, {.05, -.5}, {.05, -.5}, {.82, -.5}}}};
        m[QLatin1Char('5')] = {.8, {{{.68, -1.6}, {.18, -1.6}, {.18, -1.6}, {.13, -.88}, {.13, -.88}, {.45, -.98}, {.7, -.72}, {.68, -.22}, {.42, 0}, {.08, -.14}}}};
        m[QLatin1Char('R')] = {.82, {{{.1, 0}, {.1, -1.6}}, {{.1, -1.6}, {.45, -1.6}, {.68, -1.42}, {.66, -1.0}, {.42, -.84}, {.1, -.84}},
                                     {{.36, -.84}, {.76, 0}}}};
        m[QLatin1Char('M')] = {1.15, {{{.08, 0}, {.12, -1.6}, {.12, -1.6}, {.55, -.6}, {.55, -.6}, {.98, -1.6}, {.98, -1.6}, {1.02, 0}}}};
        m[QLatin1Char('8')] = {.8, {arc(.4, -1.22, .24, .36, -90, -450, 14), arc(.4, -.42, .3, .42, -90, -450, 16)}};
        m[QLatin1Char('3')] = {.78, {{{.12, -1.5}, {.35, -1.62}, {.6, -1.5}, {.62, -1.15}, {.35, -.88}, {.62, -.72}, {.68, -.35},
                                     {.45, -.02}, {.12, -.1}}}};
        m[QChar(0x00D7)] = {.72, {{{.12, -.82}, {.58, -.18}}, {{.58, -.82}, {.12, -.18}}}};  // ×
        m[QChar(0x00B0)] = {.42, {arc(.2, -1.45, .13, .16, -90, -450, 12)}};               // °
        m[QLatin1Char('C')] = {.85, {arc(.45, -.8, .38, .8, -45, -315, 16)}};
        m[QLatin1Char('.')] = {.3, {arc(.12, -.06, .05, .05, -90, -450, 8)}};
        m[QLatin1Char(',')] = {.3, {{{.16, -.1}, {.14, .05}, {.06, .25}}}};
        for (auto& [c, glyph] : m) {
            for (Poly& s : glyph.strokes) {
                s = spline(s);
            }
        }
        return m;
    }();
    return g;
}

/// Text als Striche (Blatt-Koordinaten in mm, y nach oben); messy 0 = sauber, 1 = Sauklaue
std::vector<Stroke> write(const QStringList& lines, double messy, unsigned seed)
{
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> uni(-1, 1);
    const auto r = [&] { return uni(rng); };
    constexpr double U = 4;  // x-Höhe 4 mm
    std::vector<Stroke> out;
    for (int li = 0; li < lines.size(); ++li) {
        const double tilt = messy * (r() * 2.5 + 2.5) * M_PI / 180;
        double cx = 0;
        for (const QString& word : lines[li].split(QLatin1Char(' '))) {
            const double ws = 1 + messy * r() * 0.2, wdy = messy * r() * 0.25, wsl = 0.12 + messy * r() * 0.2;
            double gx = 0;
            for (const QChar ch : word) {
                const Glyph& g = glyphs().at(ch);
                const double gs = 1 + messy * r() * 0.1, grot = messy * r() * 5 * M_PI / 180;
                const double gdx = messy * r() * 0.05, gdy = messy * r() * 0.08;
                for (const Poly& st : g.strokes) {
                    Stroke s;
                    int k = 0;
                    for (auto [x, y] : st) {
                        double px = (x - g.w / 2) * gs, py = (y + 0.5) * gs;
                        const double rx = px * std::cos(grot) - py * std::sin(grot), ry = px * std::sin(grot) + py * std::cos(grot);
                        px = rx + g.w / 2 + gdx + gx, py = ry - 0.5 + gdy;
                        px *= ws, py *= ws, px += -py * wsl, py += wdy, px += cx;
                        const double tx = px * std::cos(tilt) - py * std::sin(tilt), ty = px * std::sin(tilt) + py * std::cos(tilt);
                        const double jitter = messy * 0.03 * std::sin(++k * 1.3 + seed);
                        s.push_back({U * (tx + jitter), -U * (ty + jitter) - li * 3.2 * U, 0.35});
                    }
                    out.push_back(s);
                }
                gx += g.w * gs + 0.08;
            }
            cx += gx * ws + 0.55 + messy * std::abs(r()) * 0.5;
        }
    }
    return out;
}

/// Anteil falscher Zeichen (Levenshtein / Länge)
double cer(const QString& got, const QString& want)
{
    std::vector<int> d(size_t(want.size()) + 1);
    for (int j = 0; j <= want.size(); ++j) {
        d[size_t(j)] = j;
    }
    for (int i = 1; i <= got.size(); ++i) {
        int diag = d[0];
        d[0] = i;
        for (int j = 1; j <= want.size(); ++j) {
            const int up = d[size_t(j)];
            d[size_t(j)] = std::min({d[size_t(j)] + 1, d[size_t(j - 1)] + 1, diag + (got[i - 1] == want[j - 1] ? 0 : 1)});
            diag = up;
        }
    }
    return double(d.back()) / std::max<qsizetype>(1, want.size());
}

/// CAD-Korrektur eines Texts; Zeichen-x = Position im Text
std::pair<QString, std::vector<ScribbleRead::InkEdit>> fixed(const QString& s)
{
    ScribbleRead::Line l;
    l.text = s;
    for (qsizetype i = 0; i < s.size(); ++i) {
        l.chars.push_back({s[i], double(i), 1});
    }
    auto edits = ScribbleRead::correct(l);
    assert(l.chars.size() == size_t(l.text.size()));
    return {l.text, edits};
}

bool has(const std::vector<ScribbleRead::InkEdit>& edits, ScribbleRead::InkEdit::Kind kind)
{
    return std::any_of(edits.begin(), edits.end(), [kind](const auto& e) { return e.kind == kind; });
}

void checkNotation()
{
    using K = ScribbleRead::InkEdit;
    const auto expect = [](const char* in, const char* out) {
        const auto [text, edits] = fixed(QString::fromUtf8(in));
        if (text != QString::fromUtf8(out)) {
            std::printf("  %s -> %s (erwartet %s)\n", in, text.toUtf8().constData(), out);
        }
        assert(text == QString::fromUtf8(out));
        return edits;
    };
    assert(has(expect("Bohrung o12", "Bohrung Ø12"), K::Slash));
    assert(has(expect("Bohrung b12", "Bohrung Ø12"), K::Slash));
    assert(has(expect("012", "Ø12"), K::Slash));
    assert(has(expect("Bohrung ol2", "Bohrung Ø12"), K::Slash));
    assert(has(expect("D12", "Ø12"), K::Slash));  // durchgestrichener Kreis, als D gelesen (applyInk sieht den Strich)
    assert(has(expect("DA.5", "Ø4.5"), K::Slash));  // Ø4.5: die 4 als A gelesen
    assert(has(expect("BA,5", "Ø4,5"), K::Slash));
    assert(expect("Bohrung Ø12", "Bohrung Ø12").empty());
    assert(has(expect("Fase 2xA5", "Fase 2×45°"), K::Degree));
    assert(expect("Fase 2x45o", "Fase 2×45°").empty());  // ° war schon da, als o gelesen
    assert(expect("Fase 2×45°", "Fase 2×45°").empty());
    assert(has(expect("Welle 25mm", "Welle 25 mm"), K::Space));
    assert(expect("Welle 25 mm", "Welle 25 mm").empty());
    assert(expect("Toleranz +-0,1", "Toleranz ±0,1").empty());
    assert(expect("Toleranz +/-0,1", "Toleranz ±0,1").empty());
    assert(expect("Stift 0,5", "Stift 0,5").empty());
    assert(expect("Welle", "Welle").empty());
    assert(expect("Lager l2", "Lager l2").empty());  // am Wortanfang bleibt ein Buchstabe ein Buchstabe
    assert(expect("Blech 1S", "Blech 15").empty());
    assert(expect("Platte 3x4", "Platte 3×4").empty());    // Abmessung, keine Fase
    assert(expect("Platte 20x30", "Platte 20×30").empty());
    assert(has(expect("Kante 1,5x45", "Kante 1,5×45°"), K::Degree));
    assert(has(expect("Fase 2x40", "Fase 2×40°"), K::Degree));
}

}  // namespace

int main(int argc, char** argv)
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);  // bei einem assert soll alles Gelesene schon dastehen
    checkNotation();
    std::puts("CAD-Schreibweise: ok");
    assert(argc > 1);
    ScribbleRead::setModelFile(QString::fromLocal8Bit(argv[1]));
    assert(ScribbleRead::available());
    const QString images = argc > 2 ? QString::fromLocal8Bit(argv[2]) : QString();
    if (!images.isEmpty()) {
        QDir().mkpath(images);
    }

    // Ø kennt das Modell nicht: dort steht erst nach der CAD-Korrektur wieder Ø
    const QStringList text = {QStringLiteral("Welle 25 mm"), QStringLiteral("Fase 2×45°"), QString::fromUtf8("Bohrung Ø12")};
    double total = 0;
    int n = 0;
    for (const double messy : {0.0, 0.6, 1.0}) {
        for (const unsigned seed : {1U, 2U, 3U}) {
            const std::vector<Stroke> ink = write(text, messy, seed);
            const auto lines = ScribbleRead::read(ink);
            std::printf("messy %.1f seed %u:", messy, seed);
            for (const auto& l : lines) {
                std::printf("  [%s]", l.text.toUtf8().constData());
            }
            std::printf("\n");
            assert(lines.size() == 3);  // drei Zeilen erkannt
            for (int i = 0; i < 3; ++i) {
                const auto& l = lines[size_t(i)];
                assert(l.chars.size() == size_t(l.text.size()));
                for (size_t c = 1; c < l.chars.size(); ++c) {
                    assert(l.chars[c].x >= l.chars[c - 1].x);  // Zeichen von links nach rechts
                }
                total += i < 2 ? cer(l.text, text[i]) : 0;
                n += i < 2;
                if (!images.isEmpty() && seed == 1) {
                    double x0, scale;
                    ScribbleRead::render(ink, l.strokes, x0, scale)
                        .save(QStringLiteral("%1/messy%2-line%3.png").arg(images).arg(messy).arg(i));
                }
            }
        }
    }
    std::printf("mittlere Zeichenfehlerrate (ohne Ø-Zeile): %.1f %%\n", 100 * total / n);
    assert(total / n < 0.25);

    // M von vorn bis hinten: "o12" ohne Schrägstrich bekommt einen in die Tinte, ein geschriebenes Ø keinen zweiten
    int diameters = 0;
    for (const unsigned seed : {1U, 2U, 3U}) {
        for (const bool slashed : {false, true}) {
            std::vector<Stroke> ink = write({slashed ? QString::fromUtf8("Bohrung Ø12") : QStringLiteral("Bohrung o12")}, 0.5, seed);
            auto lines = ScribbleRead::read(ink);
            assert(lines.size() == 1);
            const QString raw = lines[0].text;
            const auto edits = ScribbleRead::correct(lines[0]);
            const size_t before = ink.size();
            const auto origins = ScribbleRead::applyInk(ink, lines[0], edits);
            assert(origins.size() == ink.size() - before);
            std::printf("%s: [%s] -> [%s], %zu neue Striche\n", slashed ? "Ø12" : "o12", raw.toUtf8().constData(),
                        lines[0].text.toUtf8().constData(), ink.size() - before);
            if (lines[0].text.contains(QString::fromUtf8("Ø12"))) {
                ++diameters;
                assert(ink.size() - before == (slashed ? 0U : 1U));
            }
            if (!images.isEmpty() && !slashed) {
                std::vector<size_t> all(ink.size());
                std::iota(all.begin(), all.end(), 0);
                double x0, scale;
                ScribbleRead::render(ink, all, x0, scale).save(QStringLiteral("%1/m-o12-seed%2.png").arg(images).arg(seed));
            }
        }
    }
    assert(diameters >= 4);

    // Fase ohne Gradzeichen geschrieben: die Tinte bekommt eins
    int degrees = 0;
    for (const unsigned seed : {1U, 2U, 3U}) {
        std::vector<Stroke> ink = write({QString::fromUtf8("Fase 2×45")}, 0.3, seed);
        auto lines = ScribbleRead::read(ink);
        assert(lines.size() == 1);
        const auto edits = ScribbleRead::correct(lines[0]);
        const size_t before = ink.size();
        ScribbleRead::applyInk(ink, lines[0], edits);
        std::printf("Fase: [%s], %zu neue Striche\n", lines[0].text.toUtf8().constData(), ink.size() - before);
        if (lines[0].text.endsWith(QString::fromUtf8("×45°"))) {
            ++degrees;
            assert(ink.size() - before == 1);
        }
        if (!images.isEmpty() && seed == 1) {
            std::vector<size_t> all(ink.size());
            std::iota(all.begin(), all.end(), 0);
            double x0, scale;
            ScribbleRead::render(ink, all, x0, scale).save(QStringLiteral("%1/m-fase.png").arg(images));
        }
    }
    assert(degrees >= 2);

    // Rotstift (Idee 1): kurze Korrekturen lesen und als Befehl verstehen; die Erkennung darf mal danebenliegen
    const std::tuple<const char*, RedPen::Kind, double> corrections[] = {
        {"R2", RedPen::Kind::Fillet, 2},     {"M5", RedPen::Kind::Thread, 5},     {"Ø8", RedPen::Kind::Diameter, 8},
        {"3×", RedPen::Kind::Pattern, 0},    {"Ø5", RedPen::Kind::Diameter, 5},   {"Ø4.5", RedPen::Kind::Diameter, 4.5},
        {"Ø4,5", RedPen::Kind::Diameter, 4.5}, {"C1", RedPen::Kind::Chamfer, 1}};
    for (const auto& [text, kind, value] : corrections) {
        int understood = 0;
        for (const unsigned seed : {1U, 2U, 3U}) {
            std::vector<Stroke> ink = write({QString::fromUtf8(text)}, 0.3, seed);
            auto lines = ScribbleRead::read(ink);
            assert(lines.size() == 1);
            const QString raw = lines[0].text;
            ScribbleRead::correct(lines[0]);
            const RedPen::Command c = RedPen::parse(lines[0].text.toStdString());
            const bool ok = c.kind == kind && (value == 0 || std::abs(c.value - value) < 1e-9);
            understood += ok;
            std::printf("Rotstift %s: [%s] -> [%s] %s\n", text, raw.toUtf8().constData(), lines[0].text.toUtf8().constData(),
                        ok ? "ok" : "falsch");
        }
        assert(understood >= 2);
    }
    // Mehrere Korrekturen auf einer Höhe (zwei Bohrungen links und rechts): jede ist eine eigene Zeile, sonst liest
    // es "Ø4.5 Ø4.5" und versteht keine
    int separate = 0;
    for (const unsigned seed : {1U, 2U, 3U}) {
        std::vector<Stroke> ink = write({QString::fromUtf8("Ø4.5")}, 0.3, seed);
        for (Stroke s : write({QStringLiteral("R2")}, 0.3, seed + 10)) {
            for (auto& p : s) {
                p.x += 60;  // 15 x-Höhen weiter rechts
            }
            ink.push_back(s);
        }
        auto lines = ScribbleRead::read(ink);
        std::printf("zwei auf einer Höhe:");
        for (auto& l : lines) {
            ScribbleRead::correct(l);
            std::printf(" [%s]", l.text.toUtf8().constData());
        }
        std::printf("\n");
        std::multiset<RedPen::Kind> kinds;
        for (const auto& l : lines) {
            kinds.insert(RedPen::parse(l.text.toStdString()).kind);
        }
        separate += kinds == std::multiset<RedPen::Kind> {RedPen::Kind::Diameter, RedPen::Kind::Fillet};
    }
    assert(separate >= 2);
    std::puts("ok");
    return 0;
}
