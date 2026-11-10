// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Idee 1: Handschrift ist der Befehl. Grammatik der Rotstift-Korrekturen, robust gegen typische Lesefehler der
/// Handschrifterkennung (S/5, O/0, l/1, Z/2, B/8, x/×, Leerzeichen, Dezimalkomma):
///   M5 Gewinde/Gewindebohrung · Ø8 Durchmesser/Bohrung · R2 Rundung · C2 oder 2×45° Fase · 3× Muster
///   +5 / −5 Fläche ziehen/drücken · H7 oder "Druck" Passung · 12 Maß setzen
/// Ohne FreeCAD, damit es sich allein prüfen lässt: tests/red_pen_check.cpp

#include <cstdlib>
#include <regex>
#include <string>

namespace RedPen
{

enum class Kind
{
    None,
    Thread,    ///< size = "M5", value = Nenndurchmesser
    Diameter,  ///< value
    Fillet,    ///< value = Radius
    Chamfer,   ///< value = Abstand
    Pattern,   ///< count
    Offset,    ///< value mit Vorzeichen
    Fit,       ///< fit = "H7" oder "print"
    Value      ///< value: Maß der Fläche setzen
};

struct Command
{
    Kind kind = Kind::None;
    double value = 0;
    int count = 0;
    std::string size;  ///< Gewinde, z. B. "M2.5"
    std::string fit;   ///< "H7" oder "print"
};

/// Ziffern, die die Erkennung als Buchstaben las: nur in Zahlen ersetzen
inline std::string digits(std::string s)
{
    for (char& c : s) {
        switch (c) {
            case 'S': case 's': c = '5'; break;
            case 'O': case 'o': case 'D': c = '0'; break;
            case 'l': case 'I': case '|': case 'i': c = '1'; break;
            case 'Z': case 'z': c = '2'; break;
            case 'B': c = '8'; break;
            case 'G': c = '6'; break;
            case ',': c = '.'; break;
            default: break;
        }
    }
    return s;
}

inline Command parse(const std::string& raw)
{
    // Leerzeichen und "mm" weg, Sonderzeichen vereinheitlichen
    std::string t;
    for (size_t i = 0; i < raw.size(); ++i) {
        const auto c = static_cast<unsigned char>(raw[i]);
        if (c == ' ' || c == '\t') {
            continue;
        }
        if (c == 0xC3 && i + 1 < raw.size() && (static_cast<unsigned char>(raw[i + 1]) == 0x98 || static_cast<unsigned char>(raw[i + 1]) == 0xB8)) {
            t += '@';  // Ø, ø
            ++i;
        }
        else if (c == 0xC3 && i + 1 < raw.size() && static_cast<unsigned char>(raw[i + 1]) == 0x97) {
            t += 'x';  // ×
            ++i;
        }
        else if (c == 0xE2 && i + 2 < raw.size() && static_cast<unsigned char>(raw[i + 1]) == 0x8C && static_cast<unsigned char>(raw[i + 2]) == 0x80) {
            t += '@';  // ⌀
            i += 2;
        }
        else if (c == 0xE2 && i + 2 < raw.size() && static_cast<unsigned char>(raw[i + 1]) == 0x88 && static_cast<unsigned char>(raw[i + 2]) == 0x92) {
            t += '-';  // − (Minuszeichen)
            i += 2;
        }
        else if (c == 0xC2 && i + 1 < raw.size() && static_cast<unsigned char>(raw[i + 1]) == 0xB0) {
            ++i;  // ° fällt weg: 2×45 heißt dasselbe
        }
        else {
            t += char(c);
        }
    }
    if (t.size() > 2 && (t.ends_with("mm") || t.ends_with("MM"))) {
        t.resize(t.size() - 2);
    }
    Command cmd;
    if (t.empty()) {
        return cmd;
    }
    std::string lower;
    for (char c : t) {
        lower += char(std::tolower(static_cast<unsigned char>(c)));
    }
    if (lower == "druck" || lower == "print" || lower == "3d" || lower == "3ddruck") {
        cmd.kind = Kind::Fit;
        cmd.fit = "print";
        return cmd;
    }
    static const std::regex number(R"(\d+(\.\d+)?)");
    std::smatch m;
    const auto isNumber = [&](const std::string& s, double& v) {
        const std::string d = digits(s);
        if (!std::regex_match(d, number)) {
            return false;
        }
        v = std::atof(d.c_str());
        return v > 0;
    };
    const char first = t[0];
    const std::string rest = t.substr(1);
    double v = 0;
    // Passung H7 (Bohrung): H mit einer Ziffer 5 … 11
    if ((first == 'H') && isNumber(rest, v) && v >= 5 && v <= 11 && v == int(v)) {
        cmd.kind = Kind::Fit;
        cmd.fit = "H" + std::to_string(int(v));
        return cmd;
    }
    // Gewinde M5, M2.5, M5x0.8 (auch m5, MS); die Steigung steht in der Norm
    const std::string nominal = rest.substr(0, std::min(rest.find_first_of("xX*"), rest.size()));
    if ((first == 'M' || first == 'm') && isNumber(nominal, v) && v >= 1 && v <= 64) {
        cmd.kind = Kind::Thread;
        cmd.value = v;
        cmd.size = "M" + digits(nominal);
        return cmd;
    }
    // Durchmesser Ø8 (o8, O8 vor einer Zahl)
    if ((first == '@' || first == 'o' || first == 'O' || first == '0') && rest.size() && isNumber(rest, v) && first != '0') {
        cmd.kind = Kind::Diameter;
        cmd.value = v;
        return cmd;
    }
    if (first == '@' && isNumber(rest, v)) {
        cmd.kind = Kind::Diameter;
        cmd.value = v;
        return cmd;
    }
    // Rundung R2
    if ((first == 'R' || first == 'r') && isNumber(rest, v)) {
        cmd.kind = Kind::Fillet;
        cmd.value = v;
        return cmd;
    }
    // Fase C2 oder 2×45
    if ((first == 'C' || first == 'c') && isNumber(rest, v)) {
        cmd.kind = Kind::Chamfer;
        cmd.value = v;
        return cmd;
    }
    const size_t times = lower.find_first_of("x*");
    if (times != std::string::npos) {
        const std::string a = t.substr(0, times), b = t.substr(times + 1);
        double angle = 0;
        if (isNumber(a, v) && isNumber(b, angle) && std::abs(angle - 45) < 1e-9) {
            cmd.kind = Kind::Chamfer;
            cmd.value = v;
            return cmd;
        }
        // Muster 3× oder ×3
        const std::string n = a.empty() ? b : b.empty() ? a : std::string();
        if (!n.empty() && isNumber(n, v) && v >= 2 && v == int(v)) {
            cmd.kind = Kind::Pattern;
            cmd.count = int(v);
            return cmd;
        }
        return cmd;
    }
    // Fläche ziehen/drücken
    if ((first == '+' || first == '-') && isNumber(rest, v)) {
        cmd.kind = Kind::Offset;
        cmd.value = first == '-' ? -v : v;
        return cmd;
    }
    // bloße Zahl: Maß setzen (Buchstaben-Verwechsler nur, wenn eine echte Ziffer dabei ist)
    if (std::regex_search(t, std::regex(R"(\d)")) && isNumber(t, v)) {
        cmd.kind = Kind::Value;
        cmd.value = v;
    }
    return cmd;
}

}  // namespace RedPen
