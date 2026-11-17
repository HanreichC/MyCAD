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
        Chamfer
    };
    Kind kind = Kind::None;
    std::string size;     ///< ISO-Gewinde, z. B. "M3"; leer bei Durchmesser
    double diameter = 0;  ///< mm, wenn kein M-Maß
    double offset = 0;    ///< Abstand der Mitten zum Rand, mm (ohne Angabe: zweimal der Nenndurchmesser)
    double value = 0;     ///< Rundung: Radius, Fase: Abstand (mm)
    bool all = false;     ///< "alle Kanten": jede Kante des Körpers statt der gewählten
};

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
    const auto ws = words(f);
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
