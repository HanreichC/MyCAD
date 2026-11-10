// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Idee 3: Die Notiz ist die Parameterliste. Eine Zeile "Name = Ausdruck" legt einen Parameter an ("Wand = 2 mm",
/// "Breite = Wand * 20"); Rechenzeilen enden mit "=" und bleiben Rechnungen. Hinter einer Formel schreibt MyCAD den
/// Wert als "→ 40 mm", hinter einen Fehler "⚠ …"; beides gehört nicht zum Ausdruck. Ohne FreeCAD, damit es sich allein
/// prüfen lässt: tests/note_parameters_check.cpp

#include <string>

namespace NoteParameters
{

struct Line
{
    bool definition = false;
    std::string name;        ///< wie geschrieben, z. B. "Wandstärke"
    std::string id;          ///< als Property-Name, z. B. "Wandstaerke"
    std::string expression;  ///< ohne Wert- und Fehlerhinweis
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

/// "Name = Ausdruck"? Name: Buchstaben (auch Umlaute), Ziffern und _, nicht mit einer Ziffer am Anfang
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
    if (name.empty() || expression.empty() || (name[0] >= '0' && name[0] <= '9')) {
        return line;
    }
    for (size_t i = 0; i < name.size(); ++i) {
        const auto c = static_cast<unsigned char>(name[i]);
        const bool ascii = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
        if (c == 0xC3 && i + 1 < name.size()) {  // Umlaut, zweites Byte überspringen
            ++i;
            continue;
        }
        if (!ascii) {
            return line;  // Leerzeichen, Satzzeichen …: ein Satz, keine Zuweisung
        }
    }
    line.definition = true;
    line.name = name;
    line.id = identifier(name);
    line.expression = expression;
    return line;
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
