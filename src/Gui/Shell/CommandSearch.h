// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Befehlssuche (Strg+K): wie gut passt eine Eingabe zu einem Befehl? Ohne Qt und FreeCAD, damit sie sich allein prüfen
/// lässt: tests/command_search_check.cpp. Reihenfolge: ganzer Name vor Namensanfang vor Wortanfang vor Synonym vor
/// Teilwort vor Tippfehler. Groß/klein und Umlaute zählen nicht ("bohrung" findet "Bohrung", "groesse" "Größe").

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>

namespace CommandSearch
{

/// klein, ohne Umlaute (ä -> ae, ö -> oe, ü -> ue, ß -> ss), UTF-8
inline std::string fold(const std::string& s)
{
    std::string out;
    for (size_t i = 0; i < s.size(); ++i) {
        const auto c = static_cast<unsigned char>(s[i]);
        if (c == 0xC3 && i + 1 < s.size()) {
            const auto d = static_cast<unsigned char>(s[i + 1]);
            const char* r = (d == 0xA4 || d == 0x84) ? "ae" : (d == 0xB6 || d == 0x96) ? "oe"
                          : (d == 0xBC || d == 0x9C) ? "ue" : d == 0x9F ? "ss" : nullptr;
            if (r) {
                out += r;
                ++i;
                continue;
            }
        }
        out += c < 0x80 ? static_cast<char>(std::tolower(c)) : static_cast<char>(c);
    }
    return out;
}

/// Abstand zweier kurzer Texte; zwei vertauschte Nachbarbuchstaben zählen als ein Fehler (Damerau, OSA)
inline size_t distance(const std::string& a, const std::string& b)
{
    std::vector<std::vector<size_t>> d(a.size() + 1, std::vector<size_t>(b.size() + 1));
    for (size_t i = 0; i <= a.size(); ++i) {
        d[i][0] = i;
    }
    for (size_t j = 0; j <= b.size(); ++j) {
        d[0][j] = j;
    }
    for (size_t i = 1; i <= a.size(); ++i) {
        for (size_t j = 1; j <= b.size(); ++j) {
            d[i][j] = std::min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? 0 : 1)});
            if (i > 1 && j > 1 && a[i - 1] == b[j - 2] && a[i - 2] == b[j - 1]) {
                d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + 1);
            }
        }
    }
    return d[a.size()][b.size()];
}

inline std::vector<std::string> words(const std::string& s)
{
    std::vector<std::string> out(1);
    for (char c : s) {
        if (c == ' ' || c == '-' || c == '_' || c == '/' || c == ',' || c == '(' || c == ')') {
            if (!out.back().empty()) {
                out.emplace_back();
            }
        }
        else {
            out.back() += c;
        }
    }
    if (out.back().empty()) {
        out.pop_back();
    }
    return out;
}

/// Punkte für query; names = Anzeigenamen (z. B. Deutsch und Englisch), synonyms = weitere Suchwörter.
/// 0 = kein Treffer. Leere Eingabe passt zu allem (1), dann entscheidet "zuletzt benutzt".
inline int score(const std::string& query, const std::vector<std::string>& names,
                 const std::vector<std::string>& synonyms = {})
{
    std::string q = fold(query);
    q.erase(0, q.find_first_not_of(' '));
    q.erase(q.find_last_not_of(' ') + 1);
    if (q.empty()) {
        return 1;
    }
    int best = 0;
    const auto starts = [](const std::string& t, const std::string& p) { return t.compare(0, p.size(), p) == 0; };
    const auto typo = [&q](const std::string& w) {  // ein vertipptes, fehlendes, überzähliges oder vertauschtes Zeichen
        if (q.size() < 4) {
            return false;
        }
        for (size_t n = q.size() - 1; n <= q.size() + 1 && n <= w.size(); ++n) {
            if (distance(q, w.substr(0, n)) <= 1) {
                return true;
            }
        }
        return false;
    };
    for (const auto& name : names) {
        const std::string t = fold(name);
        if (t == q) {
            return 100;
        }
        if (starts(t, q)) {
            best = std::max(best, 90);
        }
        for (const auto& w : words(t)) {
            if (starts(w, q)) {
                best = std::max(best, 70);
            }
            else if (typo(w)) {
                best = std::max(best, 25);
            }
        }
        if (t.find(q) != std::string::npos) {
            best = std::max(best, 40);
        }
    }
    for (const auto& synonym : synonyms) {
        const std::string t = fold(synonym);
        if (starts(t, q)) {
            best = std::max(best, 60);
        }
        else if (t.find(q) != std::string::npos) {
            best = std::max(best, 35);
        }
        else if (typo(t)) {
            best = std::max(best, 20);
        }
    }
    return best;
}

/// Phase 11.10 "Absicht statt Befehl": ein Satz statt eines Befehls, z. B. "4 Löcher M3 in die Ecken, 5 mm vom Rand"
/// oder "four holes Ø3.4 in the corners 6 mm from the edge". Bisher verstanden: Bohrungen in die vier Ecken.
struct Intent
{
    enum class Kind
    {
        None,
        CornerHoles,
        Fillet,
        Chamfer,
        CircleHoles,  ///< Lochkreis: count Bohrungen auf einem Kreis mit pitch Durchmesser um die Mitte der Fläche
        RowHoles,     ///< Reihe: count Bohrungen durch die Mitte der Fläche, pitch Abstand (0: gleichmäßig verteilt)
        WhyRed,       ///< 12.9 "Warum ist das rot?": was nicht rechnet oder warnt
        DependsOn,    ///< 12.9 "Was hängt daran?": was die Auswahl benutzt
        Box,          ///< 12.9 "Quader 40 x 30 x 10": dims = Länge, Breite, Höhe
        Cylinder,     ///< 12.9 "Zylinder Ø20 x 30": dims = Durchmesser, Höhe
        Shell         ///< 12.9 "Wand 2 mm": aushöhlen, value = Wanddicke
    };
    Kind kind = Kind::None;
    std::string size;     ///< ISO-Gewinde, z. B. "M3"; leer bei Durchmesser
    double diameter = 0;  ///< mm, wenn kein M-Maß
    double offset = 0;    ///< Abstand der Mitten zum Rand, mm (ohne Angabe: zweimal der Nenndurchmesser)
    double value = 0;     ///< Rundung: Radius, Fase: Abstand (mm)
    bool all = false;     ///< "alle Kanten": jede Kante des Körpers statt der gewählten
    int count = 0;        ///< Muster: Anzahl der Bohrungen
    double pitch = 0;     ///< Lochkreis: Durchmesser; Reihe: Abstand (mm)
    double dims[3] = {};  ///< Grundkörper: Quader l, b, h; Zylinder Ø, h
};

/// 12.9 Grundkörper und Wand aus den Wörtern (gefaltet, "×" schon als " x "): "Quader 40 x 30 x 10", "Würfel 20",
/// "box 40x30x10", "Zylinder Ø20 x 30", "cylinder d20 h30", "Wand 2 mm", "aushöhlen 1,5", "shell 2 mm"
inline Intent bodyIntent(const std::vector<std::string>& ws)
{
    const auto starts = [](const std::string& w, std::initializer_list<const char*> stems) {
        return std::ranges::any_of(stems, [&w](const char* s) { return w.rfind(s, 0) == 0; });
    };
    enum { None, Box, Cube, Cylinder, Shell } what = None;
    // Zahlen mit Vorzeichen-Buchstaben (d20, h30, r10) und Maße wie 40x30x10 auseinandernehmen
    std::vector<std::pair<char, double>> nums;  // (Kennbuchstabe oder 0, Wert)
    char pending = 0;                           // "Ø 20", "Durchmesser 20": die nächste Zahl ist ein Durchmesser
    for (const std::string& w : ws) {
        if (starts(w, {"quader", "box", "block"})) {
            what = Box;
        }
        else if (starts(w, {"wuerfel", "cube"})) {
            what = Cube;
        }
        else if (starts(w, {"zylinder", "cylinder", "rundstab", "scheibe", "disc", "disk"})) {
            what = Cylinder;
        }
        else if (starts(w, {"wand", "aushoehl", "hohl", "shell", "hollow"})) {
            what = Shell;
        }
        else if (w == "dia" || starts(w, {"durchmesser", "diameter"})) {
            pending = 'd';
        }
        else {
            for (size_t at = 0; at < w.size();) {
                size_t end = w.find('x', at);
                std::string part = w.substr(at, end == std::string::npos ? std::string::npos : end - at);
                at = end == std::string::npos ? w.size() : end + 1;
                char tag = pending;
                if (!part.empty() && (part[0] == 'd' || part[0] == 'h' || part[0] == 'r' || part[0] == 'l')
                    && part.size() > 1 && std::isdigit(static_cast<unsigned char>(part[1]))) {
                    tag = part[0];
                    part = part.substr(1);
                }
                char* stop = nullptr;
                const double v = std::strtod(part.c_str(), &stop);
                if (stop != part.c_str() && v > 0) {
                    nums.emplace_back(tag, v);
                    pending = 0;
                }
            }
        }
    }
    Intent out;
    if (what == Shell && !nums.empty()) {
        out.kind = Intent::Kind::Shell;
        out.value = nums.front().second;
    }
    else if ((what == Box && nums.size() >= 3) || (what == Cube && !nums.empty())) {
        out.kind = Intent::Kind::Box;
        for (int i = 0; i < 3; ++i) {
            out.dims[i] = nums[what == Cube ? 0 : i].second;
        }
    }
    else if (what == Cylinder && nums.size() >= 2) {
        out.kind = Intent::Kind::Cylinder;
        double d = 0, h = 0;
        for (const auto& [tag, v] : nums) {  // gekennzeichnet zuerst: d/Ø, r, h/l
            d = tag == 'd' ? v : tag == 'r' ? 2 * v : d;
            h = tag == 'h' || tag == 'l' ? v : h;
        }
        for (const auto& [tag, v] : nums) {  // sonst der Reihe nach: erst Durchmesser, dann Höhe
            if (tag == 0 && d <= 0) {
                d = v;
            }
            else if (tag == 0 && h <= 0) {
                h = v;
            }
        }
        out.dims[0] = d;
        out.dims[1] = h;
        if (d <= 0 || h <= 0) {
            return {};
        }
    }
    return out;
}

/// Bohrmuster aus den Wörtern (gefaltet): "6 Löcher M4 auf Lochkreis 40", "six holes M4 on a 40 mm circle",
/// "5 Löcher M3 in einer Reihe, 10 mm Abstand", "5 holes M3 in a row 10 mm apart". Kind::None, wenn es keins ist.
inline Intent patternIntent(const std::vector<std::string>& ws)
{
    const auto starts = [](const std::string& w, std::initializer_list<const char*> stems) {
        return std::ranges::any_of(stems, [&w](const char* s) { return w.rfind(s, 0) == 0; });
    };
    static const std::vector<std::pair<const char*, int>> numerals = {
        {"zwei", 2}, {"two", 2},   {"drei", 3}, {"three", 3}, {"vier", 4},   {"four", 4},    {"fuenf", 5}, {"five", 5},
        {"sechs", 6}, {"six", 6},  {"sieben", 7}, {"seven", 7}, {"acht", 8}, {"eight", 8},  {"neun", 9},  {"nine", 9},
        {"zehn", 10}, {"ten", 10}, {"zwoelf", 12}, {"twelve", 12}};
    bool holes = false, circle = false, row = false;
    int circleWord = -1;
    Intent out;
    struct Num
    {
        double v;
        bool mm, dia;
        int at;
    };
    std::vector<Num> nums;
    for (int i = 0; i < static_cast<int>(ws.size()); ++i) {
        const std::string& w = ws[i];
        if (starts(w, {"lochkreis", "teilkreis", "kreis", "circle", "around"}) || w == "bolt") {  // vor "Loch": Lochkreis
            circle = true;
            circleWord = i;
        }
        else if (starts(w, {"loch", "loech", "bohrung", "hole"})) {
            holes = true;
        }
        else if (starts(w, {"reihe", "row", "line"})) {
            row = true;
        }
        else if (w.size() > 1 && w[0] == 'm' && std::isdigit(static_cast<unsigned char>(w[1]))) {
            out.size = "M" + w.substr(1, w.find('x') == std::string::npos ? std::string::npos : w.find('x') - 1);
        }
        else {
            for (const auto& [word, n] : numerals) {
                out.count = w == word ? n : out.count;
            }
            char* end = nullptr;
            const double v = std::strtod(w.c_str(), &end);
            if (end == w.c_str()) {
                continue;
            }
            const std::string unit = end;
            const bool mm = unit == "mm" || (unit.empty() && i + 1 < static_cast<int>(ws.size()) && ws[i + 1] == "mm");
            const bool dia = i > 0 && (ws[i - 1] == "dia" || starts(ws[i - 1], {"durchmesser", "diameter"}));
            nums.push_back({v, mm, dia, i});
        }
    }
    if (!holes || circle == row) {
        return {};
    }
    // Anzahl: eine ganze Zahl ohne Einheit vor dem Wort "Löcher" (oder als Wort geschrieben)
    std::vector<Num> sizes;
    for (const auto& n : nums) {
        if (!n.mm && !n.dia && n.v == static_cast<int>(n.v) && out.count == 0 && !(circle && n.at == circleWord + 1)) {
            out.count = static_cast<int>(n.v);
        }
        else {
            sizes.push_back(n);
        }
    }
    if (out.count < 2) {
        return {};
    }
    if (circle) {
        // Lochkreis: die größte Angabe (oder die Zahl direkt nach "Lochkreis"); eine kleinere Ø-Angabe ist die Bohrung
        double pitch = 0, hole = 0;
        for (const auto& n : nums) {
            if (circleWord >= 0 && n.at == circleWord + 1) {
                pitch = n.v;
            }
        }
        for (const auto& n : sizes) {
            if (n.v != pitch && (n.mm || n.dia)) {
                if (n.v > pitch && pitch == 0) {
                    pitch = n.v;
                }
                else if (n.v > pitch) {
                    hole = std::max(hole, pitch);
                    pitch = n.v;
                }
                else {
                    hole = std::max(hole, n.v);
                }
            }
        }
        if (pitch <= 0 || (out.size.empty() && hole <= 0 && sizes.size() > 1)) {
            return {};
        }
        out.kind = Intent::Kind::CircleHoles;
        out.pitch = pitch;
        out.diameter = out.size.empty() ? (hole > 0 ? hole : 5) : 0;
        return out;
    }
    // Reihe: Abstand ist eine mm-Angabe neben "Abstand/apart/spacing", die Bohrung ein Ø oder M-Maß
    for (const auto& n : sizes) {
        bool spacing = false;
        for (int k = std::max(0, n.at - 3); k < std::min(static_cast<int>(ws.size()), n.at + 4); ++k) {
            spacing = spacing || starts(ws[k], {"abstand", "apart", "spacing", "pitch", "distance", "teilung"});
        }
        if (spacing && !n.dia) {
            out.pitch = n.v;
        }
        else if (out.size.empty() && (n.dia || n.mm)) {
            out.diameter = n.v;
        }
    }
    if (out.size.empty() && out.diameter <= 0) {
        return {};
    }
    out.kind = Intent::Kind::RowHoles;
    return out;
}

inline Intent intent(const std::string& query)
{
    std::string f = fold(query);
    for (size_t i = 1; i + 1 < f.size(); ++i) {  // Dezimalkomma ("2,5 mm"), sonst trennt words() die Zahl
        if (f[i] == ',' && std::isdigit(static_cast<unsigned char>(f[i - 1])) && std::isdigit(static_cast<unsigned char>(f[i + 1]))) {
            f[i] = '.';
        }
    }
    for (const char* mark : {"\xC3\xB8", "\xE2\x8C\x80", "\xC3\x98"}) {  // ø, ⌀, Ø: eigenes Wort
        for (size_t at = f.find(mark); at != std::string::npos; at = f.find(mark)) {
            f.replace(at, std::string(mark).size(), " dia ");
        }
    }
    for (size_t at = f.find("\xC3\x97"); at != std::string::npos; at = f.find("\xC3\x97")) {  // ×
        f.replace(at, 2, " x ");
    }
    const auto ws = words(f);
    // 12.9 Fragen ans Modell statt Befehle
    const auto has = [&ws](std::initializer_list<const char*> stems) {
        return std::ranges::any_of(ws, [&stems](const std::string& w) {
            return std::ranges::any_of(stems, [&w](const char* s) { return w.rfind(s, 0) == 0; });
        });
    };
    Intent question;
    if ((has({"warum", "wieso", "weshalb", "why"}) || (has({"was", "what"}) && has({"falsch", "wrong", "kaputt", "broken"})))
        && has({"rot", "red", "fehler", "error", "falsch", "wrong", "kaputt", "broken", "warn", "gelb", "yellow", "rechnet",
                "fail", "geht"})) {
        question.kind = Intent::Kind::WhyRed;
        return question;
    }
    if (has({"was", "what", "wer", "who", "welche", "which"})
        && has({"haengt", "depend", "abhaeng", "benutzt", "verwendet", "use", "nutzt"})) {
        question.kind = Intent::Kind::DependsOn;
        return question;
    }
    if (const Intent body = bodyIntent(ws); body.kind != Intent::Kind::None) {
        return body;
    }
    if (const Intent pattern = patternIntent(ws); pattern.kind != Intent::Kind::None) {
        return pattern;
    }
    const auto starts = [](const std::string& w, std::initializer_list<const char*> stems) {
        return std::ranges::any_of(stems, [&w](const char* s) { return w.rfind(s, 0) == 0; });
    };
    static const std::vector<std::pair<const char*, int>> numerals = {
        {"vier", 4}, {"four", 4}, {"zwei", 2}, {"two", 2}, {"drei", 3}, {"three", 3}};
    bool holes = false;
    bool corners = false;
    bool fillet = false;
    bool chamfer = false;
    double firstMm = -1, firstPlain = -1, radius = -1;
    int count = -1;
    double offset = -1;
    Intent out;
    for (size_t i = 0; i < ws.size(); ++i) {
        const std::string& w = ws[i];
        if (starts(w, {"loch", "loech", "bohrung", "hole"})) {
            holes = true;
            continue;
        }
        if (starts(w, {"ecke", "corner"})) {
            corners = true;
            continue;
        }
        if (starts(w, {"rund", "abrund", "verrund", "fillet", "round"})) {
            fillet = true;
            continue;
        }
        if (starts(w, {"fase", "anfas", "abfas", "chamfer", "bevel"})) {
            chamfer = true;
            continue;
        }
        if (w == "alle" || w == "all" || w == "every" || starts(w, {"saemtlich", "jede"})) {
            out.all = true;
            continue;
        }
        if (w.size() > 1 && w[0] == 'r' && std::isdigit(static_cast<unsigned char>(w[1]))) {  // "R2"
            radius = std::strtod(w.c_str() + 1, nullptr);
            continue;
        }
        for (const auto& [word, n] : numerals) {
            count = w == word ? n : count;
        }
        if (w.size() > 1 && w[0] == 'm' && std::isdigit(static_cast<unsigned char>(w[1]))) {
            out.size = "M" + w.substr(1, w.find('x') == std::string::npos ? std::string::npos : w.find('x') - 1);
            continue;
        }
        char* end = nullptr;
        const double v = std::strtod(w.c_str(), &end);
        if (end == w.c_str()) {
            continue;
        }
        std::string unit = end;
        if (unit.empty() && i + 1 < ws.size() && ws[i + 1] == "mm") {
            unit = "mm";
        }
        if (unit == "mm" && firstMm < 0) {
            firstMm = v;
        }
        else if (unit.empty() && firstPlain < 0) {
            firstPlain = v;
        }
        const bool afterDia = i > 0 && (ws[i - 1] == "dia" || starts(ws[i - 1], {"durchmesser", "diameter", "d="}));
        bool edge = false;  // folgt ein Randwort ("5 mm vom Rand", "6 mm from the edge")?
        for (size_t k = i + 1; k < std::min(ws.size(), i + 5); ++k) {
            edge = edge || starts(ws[k], {"rand", "kante", "edge", "aussen", "border"});
        }
        if (afterDia) {
            out.diameter = v;
        }
        else if (unit == "mm" && (edge || out.diameter > 0 || !out.size.empty())) {
            offset = v;
        }
        else if (unit == "mm") {
            out.diameter = v;
        }
        else if (unit.empty() && v == static_cast<int>(v) && count < 0) {
            count = static_cast<int>(v);
        }
    }
    // Rundung oder Fase: Wert in mm (sonst die erste Zahl, oder R2)
    if (!holes && (fillet || chamfer) && !(fillet && chamfer)) {
        out.value = radius > 0 ? radius : firstMm > 0 ? firstMm : firstPlain;
        if (out.value <= 0) {
            return {};
        }
        out.kind = fillet ? Intent::Kind::Fillet : Intent::Kind::Chamfer;
        return out;
    }
    if (!holes || !corners || (out.size.empty() && out.diameter <= 0) || (count >= 0 && count != 4)) {
        return {};
    }
    out.kind = Intent::Kind::CornerHoles;
    const double nominal = out.size.empty() ? out.diameter : std::strtod(out.size.c_str() + 1, nullptr);
    out.offset = offset >= 0 ? offset : 2 * nominal;
    return out;
}

}  // namespace CommandSearch
