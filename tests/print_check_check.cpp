// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung der Überhang-Einteilung der Druckansicht (Idee 5), ohne FreeCAD:
//   g++ -std=c++20 -I src tests/print_check_check.cpp -o /tmp/pc && /tmp/pc

#include <Mod/Design/App/PrintCheck.h>

#include <cassert>
#include <cstdio>

using namespace PrintCheck;

int main()
{
    const double up[3] = {0, 0, 1};
    const double down[3] = {0, 0, -1}, side[3] = {1, 0, 0}, top[3] = {0, 0, 1};
    const double s = std::sqrt(0.5);
    const double at45[3] = {s, 0, -s};                                          // genau 45°: druckt noch
    const double at40[3] = {std::sin(40 * M_PI / 180), 0, -std::cos(40 * M_PI / 180)};  // 40° zu "unten": hängt über
    const double at50[3] = {std::sin(50 * M_PI / 180), 0, -std::cos(50 * M_PI / 180)};

    assert(classify(down, up, 45, 0) == Kind::Bed);        // Unterseite auf dem Bett
    assert(classify(down, up, 45, 5) == Kind::Overhang);   // waagerechte Decke in 5 mm Höhe
    assert(classify(side, up, 45, 5) == Kind::Fine);       // senkrechte Wand
    assert(classify(top, up, 45, 5) == Kind::Fine);        // Oberseite
    assert(classify(at45, up, 45, 5) == Kind::Fine);
    assert(classify(at40, up, 45, 5) == Kind::Overhang);
    assert(classify(at50, up, 45, 5) == Kind::Fine);
    assert(classify(at50, up, 60, 5) == Kind::Overhang);   // strengerer Drucker: 60°

    // andere Druckrichtung: die Seite liegt jetzt unten
    const double sideways[3] = {-1, 0, 0};
    assert(classify(side, sideways, 45, 0) == Kind::Bed);
    assert(classify(down, sideways, 45, 5) == Kind::Fine);

    std::puts("print check ok");
    return 0;
}
