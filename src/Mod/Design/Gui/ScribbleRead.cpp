// SPDX-License-Identifier: LGPL-2.1-or-later

#include "ScribbleRead.h"

#include <QFile>
#include <QPainter>
#include <QPainterPath>

#include <array>
#include <cmath>
#include <memory>

#ifdef MYCAD_HTR
#include <onnxruntime_cxx_api.h>
#endif

namespace
{

constexpr int Height = 64;     ///< Eingabehöhe des Modells (htr/config.json)
constexpr int MaxWidth = 1024;
constexpr int Stride = 4;      ///< so viele Pixel je Ausgabeschritt
constexpr double Margin = 6;   ///< px Rand links und rechts

/// Zeichen der Klassen 1…111 (0 ist CTC-blank), wörtlich aus htr/config.json
const QString& alphabet()
{
    static const QString a = QString::fromUtf8("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZäöüÄÖÜß0123456789 .,;:!?\"'()[]{}<>-–—_/\\@#%&*+=|€§°²³→←↑↓×÷");
    return a;
}

QString modelFile = QStringLiteral(":/mycad/htr/model.onnx");

#ifdef MYCAD_HTR
struct Model
{
    Ort::Env env {ORT_LOGGING_LEVEL_WARNING, "mycad-htr"};
    QByteArray bytes;  ///< muss leben, solange die Session lebt
    std::unique_ptr<Ort::Session> session;
};

Model* model()
{
    static std::unique_ptr<Model> loaded;
    static bool tried = false;
    if (!tried) {
        tried = true;
        QFile f(modelFile);
        if (f.open(QIODevice::ReadOnly)) {
            auto m = std::make_unique<Model>();
            m->bytes = f.readAll();
            try {
                Ort::SessionOptions options;
                options.SetIntraOpNumThreads(2);  // eine Zeile dauert so wenige ms; mehr Kerne bremsen eher
                m->session = std::make_unique<Ort::Session>(m->env, m->bytes.constData(), size_t(m->bytes.size()), options);
                loaded = std::move(m);
            }
            catch (const Ort::Exception&) {
            }
        }
    }
    return loaded.get();
}
#endif

}  // namespace

namespace ScribbleRead
{

void setModelFile(const QString& file)
{
    modelFile = file;
}

bool available()
{
#ifdef MYCAD_HTR
    return model() != nullptr;
#else
    return false;
#endif
}

QImage render(const std::vector<ScribbleTidy::Stroke>& strokes, const std::vector<size_t>& line, double& x0, double& scale)
{
    double minX = INFINITY, maxX = -INFINITY, minY = INFINITY, maxY = -INFINITY;
    std::vector<double> widths;
    for (size_t i : line) {
        for (const auto& p : strokes[i]) {
            minX = std::min(minX, p.x), maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y), maxY = std::max(maxY, p.y);
            widths.push_back(p.w);
        }
    }
    if (widths.empty()) {
        return {};
    }
    // die ganze Zeile mit Ober- und Unterlängen füllt 80 % der Höhe, wie die Zeilen, mit denen das Modell gelernt hat
    scale = Height * 0.8 / std::max(maxY - minY, 1e-9);
    if ((maxX - minX) * scale + 2 * Margin > MaxWidth) {
        scale = (MaxWidth - 2 * Margin) / std::max(maxX - minX, 1e-9);  // lange Zeile: kleiner, dafür ganz
    }
    int width = int(std::ceil((maxX - minX) * scale + 2 * Margin));
    width = std::clamp((width + Stride - 1) / Stride * Stride, 2 * Stride, MaxWidth);
    x0 = minX - Margin / scale;
    const double cy = (minY + maxY) / 2;
    const auto at = [&](const ScribbleTidy::Pt& p) { return QPointF((p.x - x0) * scale, Height / 2.0 - (p.y - cy) * scale); };

    QImage img(width, Height, QImage::Format_Grayscale8);
    img.fill(255);
    QPainter painter(&img);
    painter.setRenderHint(QPainter::Antialiasing);
    // Strichstärke wie ein gescannter Kugelschreiber: unabhängig vom Zoom, nur grob vom Druck
    std::nth_element(widths.begin(), widths.begin() + long(widths.size() / 2), widths.end());
    const double pen = std::clamp(widths[widths.size() / 2] * scale, 1.8, 3.0);
    painter.setPen(QPen(Qt::black, pen, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (size_t i : line) {
        const auto& s = strokes[i];
        if (s.size() == 1) {
            painter.drawPoint(at(s.front()));
            continue;
        }
        QPainterPath path(at(s.front()));
        for (size_t j = 1; j < s.size(); ++j) {
            path.lineTo(at(s[j]));
        }
        painter.drawPath(path);
    }
    return img;
}

std::vector<Line> read(const std::vector<ScribbleTidy::Stroke>& strokes)
{
    std::vector<Line> out;
#ifdef MYCAD_HTR
    Model* m = model();
    if (!m) {
        return out;
    }
    for (const std::vector<size_t>& idx : ScribbleTidy::lines(strokes)) {
        double x0 = 0, scale = 1;
        const QImage img = render(strokes, idx, x0, scale);
        if (img.isNull()) {
            continue;
        }
        // Graustufen 0…1, weiß = 1 (Normalisierung macht das Modell selbst)
        const int w = img.width();
        std::vector<float> pixels(size_t(w) * Height);
        for (int y = 0; y < Height; ++y) {
            const uchar* row = img.constScanLine(y);
            for (int x = 0; x < w; ++x) {
                pixels[size_t(y) * size_t(w) + size_t(x)] = row[x] / 255.0F;
            }
        }
        const std::array<int64_t, 4> shape {1, 1, Height, w};
        const Ort::MemoryInfo mem = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
        Ort::Value input = Ort::Value::CreateTensor<float>(mem, pixels.data(), pixels.size(), shape.data(), shape.size());
        const char* inName = "image";
        const char* outName = "logits";
        std::vector<Ort::Value> result;
        try {
            result = m->session->Run(Ort::RunOptions {nullptr}, &inName, &input, 1, &outName, 1);
        }
        catch (const Ort::Exception&) {
            continue;
        }
        // logits [1, Schritte, Klassen]: je Schritt die wahrscheinlichste Klasse, Wiederholungen und blank fallen weg
        const std::vector<int64_t> dims = result[0].GetTensorTypeAndShapeInfo().GetShape();
        if (dims.size() != 3) {
            continue;
        }
        const int64_t steps = dims[1], classes = dims[2];
        const float* logits = result[0].GetTensorData<float>();
        Line line;
        line.strokes = idx;
        int64_t prev = 0;
        for (int64_t t = 0; t < steps; ++t) {
            const float* row = logits + t * classes;
            const int64_t best = std::max_element(row, row + classes) - row;
            if (best != prev && best > 0 && best <= alphabet().size()) {
                double sum = 0;
                for (int64_t k = 0; k < classes; ++k) {
                    sum += std::exp(double(row[k] - row[best]));
                }
                const QChar c = alphabet()[int(best - 1)];
                if (!(c == QLatin1Char(' ') && (line.text.isEmpty() || line.text.endsWith(QLatin1Char(' '))))) {
                    line.text += c;
                    line.chars.push_back({c, x0 + (double(t) + 0.5) * Stride / scale, float(1 / sum)});
                }
            }
            prev = best;
        }
        while (line.text.endsWith(QLatin1Char(' '))) {
            line.text.chop(1);
            line.chars.pop_back();
        }
        if (!line.text.isEmpty()) {
            out.push_back(std::move(line));
        }
    }
#else
    Q_UNUSED(strokes);
#endif
    return out;
}

std::vector<InkEdit> correct(Line& line)
{
    std::vector<InkEdit> edits;
    std::vector<Char> c = line.chars;
    const auto at = [&c](qsizetype i) { return i >= 0 && i < qsizetype(c.size()) ? c[size_t(i)].c : QLatin1Char(' '); };
    const auto digit = [&](qsizetype i) { return at(i).isDigit(); };
    const auto insert = [&c](qsizetype i, QChar ch, double x) { c.insert(c.begin() + i, {ch, x, 1.0F}); };
    const QChar Dia(0x00D8), Times(0x00D7), Deg(0x00B0), PlusMinus(0x00B1);

    // Kreis am Wortanfang vor einer Ziffer ist ein Durchmesser (das Modell kennt Ø nicht): o12, O12, 012, b12, ø12;
    // die 1 dahinter liest es oft als l: ol2
    for (qsizetype i = 0; i < qsizetype(c.size()); ++i) {
        const QChar ch = at(i);
        const bool one = (at(i + 1) == QLatin1Char('l') || at(i + 1) == QLatin1Char('I')) && digit(i + 2);
        if (at(i - 1) == QLatin1Char(' ') && QStringLiteral("oO0bdøØ").contains(ch) && (digit(i + 1) || one)) {
            if (one) {
                c[size_t(i + 1)].c = QLatin1Char('1');
            }
            if (ch != Dia && ch != QChar(0x00F8)) {
                edits.push_back({InkEdit::Slash, c[size_t(i)].x, c[size_t(i + 1)].x});
            }
            c[size_t(i)].c = Dia;
        }
    }
    // o hinter einer Zahl am Wortende ist ein Gradzeichen: 45o → 45°
    for (qsizetype i = 1; i < qsizetype(c.size()); ++i) {
        if ((at(i) == QLatin1Char('o') || at(i) == QLatin1Char('O')) && digit(i - 1) && at(i + 1) == QLatin1Char(' ')) {
            c[size_t(i)].c = Deg;
        }
    }
    // ähnliche Buchstaben in Zahlen sind Ziffern: 2xA5 → 2x45, l2 → 12
    static const QString letters = QStringLiteral("AlISBZOo"), digits = QStringLiteral("41158200");
    for (qsizetype i = 0; i < qsizetype(c.size()); ++i) {
        const qsizetype k = letters.indexOf(at(i));
        const bool numberBefore = digit(i - 1) || ((at(i - 1).toLower() == QLatin1Char('x') || at(i - 1) == Times) && digit(i - 2));
        const bool numberAfter = digit(i + 1) || at(i + 1) == Deg || at(i + 1) == QLatin1Char(',') || at(i + 1) == QLatin1Char('.');
        if (k >= 0 && numberBefore && (numberAfter || (at(i + 1) == QLatin1Char(' ') && digit(i - 1)))) {
            c[size_t(i)].c = digits[k];
        }
    }
    // x zwischen Zahlen ist ein Mal: 2x45 → 2×45
    for (qsizetype i = 1; i < qsizetype(c.size()); ++i) {
        if (at(i).toLower() == QLatin1Char('x') && digit(i - 1) && digit(i + 1)) {
            c[size_t(i)].c = Times;
        }
    }
    // Fase: Maß × Winkel ohne Gradzeichen bekommt eins. Fase heißt: das Wort steht da, oder ein kleines Maß mal 30/45/60
    // (3×4 oder 20×30 bleiben Abmessungen)
    const bool chamfer = line.text.contains(QStringLiteral("fase"), Qt::CaseInsensitive);
    for (qsizetype i = 1; i < qsizetype(c.size()); ++i) {
        if (at(i) != Times || !digit(i - 1) || !digit(i + 1)) {
            continue;
        }
        qsizetype start = i - 1, end = i + 1;
        while (digit(start - 1) || at(start - 1) == QLatin1Char(',') || at(start - 1) == QLatin1Char('.')) {
            --start;
        }
        QString size, angle;
        for (qsizetype k = start; k < i; ++k) {
            size += at(k) == QLatin1Char(',') ? QLatin1Char('.') : at(k);
        }
        while (digit(end)) {
            angle += at(end++);
        }
        const int a = angle.toInt();
        const bool typical = (a == 30 || a == 45 || a == 60) && size.toDouble() <= 10;
        if (at(end) != Deg && a > 0 && a <= 90 && (chamfer || typical)) {
            edits.push_back({InkEdit::Degree, c[size_t(end - 1)].x});
            insert(end, Deg, c[size_t(end - 1)].x);
        }
    }
    // Einheit mit Abstand: 25mm → 25 mm
    for (qsizetype i = 1; i < qsizetype(c.size()); ++i) {
        const bool unit = (at(i) == QLatin1Char('m') && (at(i + 1) == QLatin1Char('m') || at(i + 1) == QLatin1Char(' ')))
            || (at(i) == QLatin1Char('c') && at(i + 1) == QLatin1Char('m'));
        if (unit && digit(i - 1)) {
            const double x = (c[size_t(i - 1)].x + c[size_t(i)].x) / 2;
            edits.push_back({InkEdit::Space, x});
            insert(i, QLatin1Char(' '), x);
        }
    }
    // +- und +/- sind ±
    for (qsizetype i = 0; i + 1 < qsizetype(c.size()); ++i) {
        if (at(i) == QLatin1Char('+') && (at(i + 1) == QLatin1Char('-') || (at(i + 1) == QLatin1Char('/') && at(i + 2) == QLatin1Char('-')))) {
            c[size_t(i)].c = PlusMinus;
            c.erase(c.begin() + i + 1, c.begin() + i + (at(i + 1) == QLatin1Char('/') ? 3 : 2));
        }
    }
    line.chars = c;
    line.text.clear();
    for (const Char& ch : c) {
        line.text += ch.c;
    }
    return edits;
}

std::vector<size_t> applyInk(std::vector<ScribbleTidy::Stroke>& strokes, const Line& line, const std::vector<InkEdit>& edits)
{
    using ScribbleTidy::Pt;
    struct Box
    {
        double minX = INFINITY, maxX = -INFINITY, minY = INFINITY, maxY = -INFINITY;
        double cx() const
        {
            return (minX + maxX) / 2;
        }
    };
    const auto box = [&strokes](size_t i) {
        Box b;
        for (const Pt& p : strokes[i]) {
            b.minX = std::min(b.minX, p.x), b.maxX = std::max(b.maxX, p.x);
            b.minY = std::min(b.minY, p.y), b.maxY = std::max(b.maxY, p.y);
        }
        return b;
    };
    std::vector<size_t> mine = line.strokes;  // die Zeile und was hier dazukommt
    std::vector<double> heights;
    for (size_t i : mine) {
        heights.push_back(box(i).maxY - box(i).minY);
    }
    std::sort(heights.begin(), heights.end());
    const double typical = heights.empty() ? 0 : heights[heights.size() / 2];
    if (typical <= 0) {
        return {};
    }
    /// der Strich, dessen Mitte am nächsten bei x liegt (Punkte und Querstriche zählen nicht)
    const auto nearest = [&](double x) {
        size_t best = mine.front();
        double d = INFINITY;
        for (size_t i : line.strokes) {
            const Box b = box(i);
            if (b.maxY - b.minY > 0.4 * typical && std::abs(b.cx() - x) < d) {
                d = std::abs(b.cx() - x);
                best = i;
            }
        }
        return best;
    };
    const auto width = [&strokes](size_t i) {
        std::vector<double> w;
        for (const Pt& p : strokes[i]) {
            w.push_back(p.w);
        }
        std::sort(w.begin(), w.end());
        return w[w.size() / 2];
    };
    std::vector<size_t> origins;
    std::vector<InkEdit> sorted = edits;  // von rechts nach links: eine Lücke verschiebt nur, was schon fertig ist
    std::sort(sorted.begin(), sorted.end(), [](const InkEdit& a, const InkEdit& b) { return a.x > b.x; });
    for (const InkEdit& e : sorted) {
        if (e.kind == InkEdit::Space) {
            for (size_t i : mine) {
                if (box(i).cx() > e.x) {
                    for (Pt& p : strokes[i]) {
                        p.x += 0.45 * typical;
                    }
                }
            }
            continue;
        }
        const size_t ref = nearest(e.x);
        Box b = box(ref);
        ScribbleTidy::Stroke s;
        if (e.kind == InkEdit::Slash) {
            // schon ein Strich im Kreis: das Ø hat seinen Schrägstrich, nur das Modell kennt es nicht
            const bool slashed = std::any_of(line.strokes.begin(), line.strokes.end(), [&](size_t i) {
                const Box o = box(i);
                return i != ref && o.cx() > b.minX && o.cx() < b.maxX && (o.minY + o.maxY) / 2 > b.minY && (o.minY + o.maxY) / 2 < b.maxY;
            });
            if (slashed) {
                continue;
            }
            // ein kleines o wird so hoch wie die Ziffer dahinter, sonst sähe es aus wie ø
            const Box digit = box(nearest(e.next));
            const double f = std::clamp((digit.maxY - digit.minY) / std::max(b.maxY - b.minY, 1e-9), 1.0, 2.0);
            const double cx = b.cx(), bottom = b.minY, fx = 1 + (f - 1) * 0.4;  // schmaler wachsen: Ø ist oval, Platz daneben knapp
            for (Pt& p : strokes[ref]) {
                p.x = cx + (p.x - cx) * fx;
                p.y = bottom + (p.y - bottom) * f;
            }
            b = box(ref);
        }
        const double w = b.maxX - b.minX, h = b.maxY - b.minY;
        if (e.kind == InkEdit::Slash) {
            for (int k = 0; k <= 12; ++k) {
                const double t = k / 12.0;
                s.push_back({b.minX - 0.15 * w + t * 1.3 * w, b.minY - 0.1 * h + t * 1.2 * h, width(ref)});
            }
        }
        else {  // Gradzeichen: kleiner Kreis oben rechts neben der Ziffer
            const double r = 0.15 * h;
            const Pt c {b.maxX + 0.15 * h + r, b.maxY - r, width(ref)};
            for (int k = 0; k <= 16; ++k) {
                const double t = 2 * M_PI * k / 16 + M_PI / 2;
                s.push_back({c.x + r * std::cos(t), c.y + r * std::sin(t), c.w});
            }
        }
        strokes.push_back(s);
        mine.push_back(strokes.size() - 1);
        origins.push_back(ref);
    }
    return origins;
}

}  // namespace ScribbleRead
