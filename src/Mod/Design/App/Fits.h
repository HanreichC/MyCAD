// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Idee 4: Passungen nach ISO 286-1/-2 für die gängigen Paarungen (Bohrung H, Welle d…p, Grade 5–11) bis 500 mm, und
/// das Spiel für den 3D-Druck. Werte in µm. Ohne FreeCAD, damit es sich allein prüfen lässt: tests/fits_check.cpp

#include <array>
#include <cmath>
#include <cstdlib>
#include <string>

namespace Fits
{

struct Deviation
{
    double upper = 0;  ///< oberes Abmaß in µm (ES bzw. es)
    double lower = 0;  ///< unteres Abmaß in µm (EI bzw. ei)
    double mean() const
    {
        return (upper + lower) / 2;
    }
};

/// Nennmaßbereiche "über … bis einschließlich": ≤3, 3–6, 6–10 … 400–500
constexpr std::array<double, 13> RangeTop {3, 6, 10, 18, 30, 50, 80, 120, 180, 250, 315, 400, 500};

/// Bereich zum Nennmaß, -1 außerhalb (0 oder über 500 mm)
inline int range(double nominal)
{
    if (nominal <= 0) {
        return -1;
    }
    for (int i = 0; i < int(RangeTop.size()); ++i) {
        if (nominal <= RangeTop[i] + 1e-9) {
            return i;
        }
    }
    return -1;
}

/// Grundtoleranz IT5 … IT11 in µm
inline double it(int grade, int r)
{
    static constexpr double table[7][13] = {
        {4, 5, 6, 8, 9, 11, 13, 15, 18, 20, 23, 25, 27},                  // IT5
        {6, 8, 9, 11, 13, 16, 19, 22, 25, 29, 32, 36, 40},                // IT6
        {10, 12, 15, 18, 21, 25, 30, 35, 40, 46, 52, 57, 63},             // IT7
        {14, 18, 22, 27, 33, 39, 46, 54, 63, 72, 81, 89, 97},             // IT8
        {25, 30, 36, 43, 52, 62, 74, 87, 100, 115, 130, 140, 155},        // IT9
        {40, 48, 58, 70, 84, 100, 120, 140, 160, 185, 210, 230, 250},     // IT10
        {60, 75, 90, 110, 130, 160, 190, 220, 250, 290, 320, 360, 400},   // IT11
    };
    return grade >= 5 && grade <= 11 && r >= 0 ? table[grade - 5][r] : NAN;
}

/// Grundabmaß der Welle in µm: d … h ist das obere (es, ≤ 0), k … p das untere (ei, ≥ 0)
inline double shaftFundamental(char letter, int grade, int r)
{
    static constexpr double d[] = {-20, -30, -40, -50, -65, -80, -100, -120, -145, -170, -190, -210, -230};
    static constexpr double e[] = {-14, -20, -25, -32, -40, -50, -60, -72, -85, -100, -110, -125, -135};
    static constexpr double f[] = {-6, -10, -13, -16, -20, -25, -30, -36, -43, -50, -56, -62, -68};
    static constexpr double g[] = {-2, -4, -5, -6, -7, -9, -10, -12, -14, -15, -17, -18, -20};
    static constexpr double k[] = {0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5};  // nur IT4 … IT7, darüber 0
    static constexpr double n[] = {4, 8, 10, 12, 15, 17, 20, 23, 27, 31, 34, 37, 40};
    static constexpr double p[] = {6, 12, 15, 18, 22, 26, 32, 37, 43, 50, 56, 62, 68};
    switch (letter) {
        case 'd': return d[r];
        case 'e': return e[r];
        case 'f': return f[r];
        case 'g': return g[r];
        case 'h': return 0;
        case 'k': return grade <= 7 ? k[r] : 0;
        case 'n': return n[r];
        case 'p': return p[r];
        default: return NAN;
    }
}

/// Toleranzfeld wie "H7" (Bohrung, nur H) oder "g6" (Welle); false bei unbekanntem Feld oder Nennmaß
inline bool field(const std::string& code, double nominal, Deviation& out)
{
    const int r = range(nominal);
    if (code.size() < 2 || r < 0) {
        return false;
    }
    const int grade = std::atoi(code.c_str() + 1);
    const double tol = it(grade, r);
    if (std::isnan(tol)) {
        return false;
    }
    if (code[0] == 'H') {
        out = {tol, 0};
        return true;
    }
    const double fundamental = shaftFundamental(code[0], grade, r);
    if (std::isnan(fundamental)) {
        return false;
    }
    out = code[0] <= 'h' ? Deviation {fundamental, fundamental - tol} : Deviation {fundamental + tol, fundamental};
    return true;
}

/// Passung "H7/g6": Bohrung und Welle; Spiel in µm (min, max; negativ = Übermaß)
inline bool fit(const std::string& code, double nominal, Deviation& hole, Deviation& shaft, double& minPlay, double& maxPlay)
{
    const size_t slash = code.find('/');
    if (slash == std::string::npos || !field(code.substr(0, slash), nominal, hole)
        || !field(code.substr(slash + 1), nominal, shaft)) {
        return false;
    }
    minPlay = hole.lower - shaft.upper;
    maxPlay = hole.upper - shaft.lower;
    return true;
}

}  // namespace Fits
