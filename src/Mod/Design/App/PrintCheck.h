// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Idee 5: Druckansicht. Einteilung einer Fläche (Dreieck) nach ihrer Normale gegen die Druckrichtung: liegt sie auf
/// dem Bett, hängt sie über (zeigt nach unten, flacher als der Grenzwinkel zur Waagerechten) oder geht sie.
/// Ohne FreeCAD, damit es sich allein prüfen lässt: tests/print_check_check.cpp

#include <cmath>

namespace PrintCheck
{

enum class Kind
{
    Fine,
    Overhang,
    Bed
};

/// n: Normale (Länge 1, aus dem Körper heraus), up: Druckrichtung (Länge 1), height: Höhe des höchsten Eckpunkts
/// über dem Bett (tiefster Punkt des Körpers). Überhang: die Normale liegt näher als maxAngle (Grad) an "nach unten";
/// genau maxAngle druckt noch. Waagerechte Decke ist Überhang, außer sie liegt auf dem Bett.
inline Kind classify(const double n[3], const double up[3], double maxAngle, double height)
{
    const double down = -(n[0] * up[0] + n[1] * up[1] + n[2] * up[2]);  // cos des Winkels zu "nach unten"
    if (down > 1 - 1e-6 && height < 1e-3) {
        return Kind::Bed;
    }
    return down > std::cos(maxAngle * M_PI / 180) + 1e-9 ? Kind::Overhang : Kind::Fine;
}

}  // namespace PrintCheck
