// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Befehlssuche (Strg+K): wie gut passt eine Eingabe zu einem Befehl? Ohne Qt und FreeCAD, damit sie sich allein prüfen
/// lässt: tests/command_search_check.cpp. Reihenfolge: ganzer Name vor Namensanfang vor Wortanfang vor Synonym vor
/// Teilwort vor Tippfehler. Groß/klein und Umlaute zählen nicht ("bohrung" findet "Bohrung", "groesse" "Größe").

#include <algorithm>
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

}  // namespace CommandSearch
