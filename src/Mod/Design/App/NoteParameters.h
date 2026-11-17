// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Idee 3: Die Notiz ist die Parameterliste. Eine Zeile "Name = Ausdruck" legt einen Parameter an ("Wand = 2 mm",
/// "Breite = Wand * 20"); Rechenzeilen enden mit "=" und bleiben Rechnungen. Hinter einer Formel schreibt MyCAD den
/// Wert als "→ 40 mm", hinter einen Fehler "⚠ …"; beides gehört nicht zum Ausdruck. Ohne FreeCAD, damit es sich allein
/// prüfen lässt: tests/note_parameters_check.cpp
///
/// Phase 11.7 Konfigurationen: eine Kopfzeile "Größe: S | M | L" nennt die Spalten, Werte mit "|" haben je Spalte einen
/// ("Breite = 40 mm | 60 mm | 80 mm"), die Zeile "Größe = M" wählt die Spalte (ohne sie die erste). Gilt jeweils die
/// nächste Kopfzeile darüber.

#include <map>
#include <string>
#include <vector>

namespace NoteParameters
{

struct Line
{
    bool definition = false;
    std::string name;        ///< wie geschrieben, z. B. "Wandstärke"
    std::string id;          ///< als Property-Name, z. B. "Wandstaerke"
    std::string expression;  ///< ohne Wert- und Fehlerhinweis; mit Konfigurationen (resolve) der der aktiven Spalte
    std::vector<std::string> columns;  ///< resolve: alle Spalten einer Zeile mit "|", sonst leer
    int column = -1;                   ///< resolve: aktive Spalte darin
};

/// Umlaute für Property-Namen (die nur ASCII kennen): ä -> ae, Ä -> Ae, ß -> ss …
inline std::string identifier(const std::string& name)
{
    std::string out;
    for (size_t i = 0; i < name.size(); ++i) {
        const auto c = static_cast<unsigned char>(name[i]);
        if (c == 0xC3 && i + 1 < name.size()) {
            const auto d = static_cast<unsigned char>(name[++i]);
            out += d == 0xA4 ? "ae" : d == 0xB6 ? "oe" : d == 0xBC ? "ue" : d == 0x84 ? "Ae" : d == 0x96 ? "Oe"
                 : d == 0x9C ? "Ue" : d == 0x9F ? "ss" : "_";
            continue;
        }
        out += static_cast<char>(c);
    }
    return out;
}

/// Teil vor dem Wert- (" → ") oder Fehlerhinweis (" ⚠ ")
inline std::string withoutHint(const std::string& line)
{
    size_t cut = line.size();
    for (const char* mark : {" \xE2\x86\x92 ", " \xE2\x9A\xA0 "}) {  // →, ⚠
        cut = std::min(cut, line.find(mark));
    }
    return line.substr(0, cut);
}

inline std::string trim(const std::string& s)
{
    const size_t a = s.find_first_not_of(" \t");
    const size_t b = s.find_last_not_of(" \t");
    return a == std::string::npos ? std::string() : s.substr(a, b - a + 1);
}

/// Ein Wort aus Buchstaben (auch Umlaute), Ziffern und _, nicht mit einer Ziffer am Anfang
inline bool isName(const std::string& name)
{
    if (name.empty() || (name[0] >= '0' && name[0] <= '9')) {
        return false;
    }
    for (size_t i = 0; i < name.size(); ++i) {
        const auto c = static_cast<unsigned char>(name[i]);
        const bool ascii = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
        if (c == 0xC3 && i + 1 < name.size()) {  // Umlaut, zweites Byte überspringen
            ++i;
            continue;
        }
        if (!ascii) {
            return false;  // Leerzeichen, Satzzeichen …: ein Satz
        }
    }
    return true;
}

/// "Name = Ausdruck"? Name: siehe isName
inline Line parse(const std::string& raw)
{
    Line line;
    const std::string text = trim(withoutHint(raw));
    const size_t eq = text.find('=');
    if (eq == std::string::npos || eq == 0 || text.back() == '=' || text.find('=', eq + 1) != std::string::npos) {
        return line;  // keine Zuweisung, Rechenzeile ("120 / 4 =") oder mehrere "="
    }
    const std::string name = trim(text.substr(0, eq));
    const std::string expression = trim(text.substr(eq + 1));
    if (expression.empty() || !isName(name)) {
        return line;
    }
    line.definition = true;
    line.name = name;
    line.id = identifier(name);
    line.expression = expression;
    return line;
}

/// Teile zwischen sep, ohne Leerraum drumherum
inline std::vector<std::string> split(const std::string& text, char sep)
{
    std::vector<std::string> parts;
    size_t start = 0;
    for (size_t at = text.find(sep); ; at = text.find(sep, start)) {
        parts.push_back(trim(text.substr(start, at == std::string::npos ? std::string::npos : at - start)));
        if (at == std::string::npos) {
            return parts;
        }
        start = at + 1;
    }
}

struct Configuration
{
    std::string name;                  ///< wie geschrieben, z. B. "Größe"
    std::string id;                    ///< wie bei Parametern, z. B. "Groesse"
    std::vector<std::string> options;  ///< Spalten, z. B. S, M, L
    size_t header = 0;                 ///< Zeile der Kopfzeile
    int selection = -1;                ///< Zeile "Größe = M", -1 ohne
    size_t active = 0;                 ///< gewählte Spalte (ohne Auswahlzeile die erste)
};

/// Kopfzeile "Name: A | B | C": Name und mindestens zwei Spalten, jede ein Wort (isName oder Zahl wie 10)
inline bool parseHeader(const std::string& raw, Configuration& c)
{
    const std::string text = trim(withoutHint(raw));
    const size_t colon = text.find(':');
    if (colon == std::string::npos || text.find('=') != std::string::npos) {
        return false;
    }
    const std::string name = trim(text.substr(0, colon));
    const auto options = split(text.substr(colon + 1), '|');
    if (!isName(name) || options.size() < 2) {
        return false;
    }
    for (const auto& o : options) {
        if (!isName(o) && (o.empty() || o.find_first_not_of("0123456789") != std::string::npos)) {
            return false;
        }
    }
    c.name = name;
    c.id = identifier(name);
    c.options = options;
    return true;
}

/// Alle Konfigurationen der Notiz mit ihrer gewählten Spalte
inline std::vector<Configuration> configurations(const std::vector<std::string>& lines)
{
    std::vector<Configuration> found;
    for (size_t i = 0; i < lines.size(); ++i) {
        Configuration c;
        if (parseHeader(lines[i], c)) {
            c.header = i;
            found.push_back(c);
        }
    }
    for (size_t i = 0; i < lines.size(); ++i) {
        const Line l = parse(lines[i]);
        for (auto& c : found) {
            if (l.definition && l.id == c.id) {
                c.selection = static_cast<int>(i);
                for (size_t k = 0; k < c.options.size(); ++k) {
                    if (c.options[k] == l.expression) {
                        c.active = k;
                    }
                }
            }
        }
    }
    return found;
}

/// Zeilen der Notiz gelesen, mit Konfigurationen: Auswahlzeilen ("Größe = M") sind keine Parameter, Zeilen mit "|"
/// bekommen den Ausdruck der aktiven Spalte der nächsten Kopfzeile darüber. Fehler (englisch) je Zeile in errors.
inline std::vector<Line> resolve(const std::vector<std::string>& lines, std::map<size_t, std::string>& errors)
{
    const auto configs = configurations(lines);
    std::vector<Line> out;
    for (size_t i = 0; i < lines.size(); ++i) {
        Line l = parse(lines[i]);
        const Configuration* above = nullptr;
        for (const auto& c : configs) {
            if (c.header < i) {
                above = &c;
            }
            if (l.definition && static_cast<int>(i) == c.selection) {
                bool known = false;
                for (const auto& o : c.options) {
                    known = known || o == l.expression;
                }
                if (!known) {
                    errors[i] = "Not one of the configurations";
                }
                l.definition = false;  // wählt nur die Spalte
            }
        }
        if (l.definition && l.expression.find('|') != std::string::npos) {
            l.columns = split(l.expression, '|');
            if (!above || l.columns.size() != above->options.size()) {
                errors[i] = "Needs one value per configuration";
                l.definition = false;
            }
            else {
                l.column = static_cast<int>(above->active);
                l.expression = l.columns[above->active];
            }
        }
        out.push_back(l);
    }
    return out;
}

/// Spalte option wählen: Auswahlzeile ersetzen oder unter die Kopfzeile schreiben
inline void choose(std::vector<std::string>& lines, const Configuration& c, size_t option)
{
    const std::string line = c.name + " = " + c.options.at(option);
    if (c.selection >= 0) {
        lines[c.selection] = line;
    }
    else {
        lines.insert(lines.begin() + static_cast<long>(c.header) + 1, line);
    }
}

/// Zeile mit neuer aktiver Spalte (Parameter woanders geändert): die anderen Spalten bleiben
inline std::string withColumn(const Line& line, const std::string& expression)
{
    std::string out = line.name + " =";
    for (size_t k = 0; k < line.columns.size(); ++k) {
        out += (k ? " | " : " ") + (static_cast<int>(k) == line.column ? expression : line.columns[k]);
    }
    return out;
}

/// Zeile mit neuem Hinweis (Wert nach einer Formel bzw. Fehler); leerer Hinweis nimmt einen alten weg
inline std::string withHint(const std::string& raw, const std::string& value, const std::string& error)
{
    std::string out = withoutHint(raw);
    out.erase(out.find_last_not_of(" \t") + 1);
    if (!error.empty()) {
        return out + " \xE2\x9A\xA0 " + error;
    }
    if (!value.empty()) {
        return out + " \xE2\x86\x92 " + value;
    }
    return out;
}

}  // namespace NoteParameters
