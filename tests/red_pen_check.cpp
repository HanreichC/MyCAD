// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung der Rotstift-Grammatik (Idee 1) mit typischen Lesefehlern, ohne FreeCAD:
//   g++ -std=c++20 -I src tests/red_pen_check.cpp -o /tmp/redpen && /tmp/redpen

#include <Mod/Design/App/RedPen.h>

#include <cassert>
#include <cstdio>

using namespace RedPen;

static bool is(const Command& c, Kind k, double v)
{
    return c.kind == k && std::abs(c.value - v) < 1e-9;
}

int main()
{
    // Gewinde
    assert(is(parse("M5"), Kind::Thread, 5) && parse("M5").size == "M5");
    assert(is(parse("MS"), Kind::Thread, 5) && parse("MS").size == "M5");  // S statt 5
    assert(is(parse("m 3"), Kind::Thread, 3));
    assert(is(parse("M2,5"), Kind::Thread, 2.5) && parse("M2,5").size == "M2.5");
    assert(is(parse("M5x0.8"), Kind::Thread, 5));
    // Durchmesser
    assert(is(parse("\xC3\x98" "8"), Kind::Diameter, 8));   // Ø8
    assert(is(parse("\xC3\xB8 8"), Kind::Diameter, 8));     // ø 8
    assert(is(parse("o8"), Kind::Diameter, 8));            // Kreis ohne Strich
    assert(is(parse("O12mm"), Kind::Diameter, 12));
    // Rundung und Fase
    assert(is(parse("R2"), Kind::Fillet, 2));
    assert(is(parse("R 2"), Kind::Fillet, 2));
    assert(is(parse("r1,5"), Kind::Fillet, 1.5));
    assert(is(parse("Rl"), Kind::Fillet, 1));              // l statt 1
    assert(is(parse("C2"), Kind::Chamfer, 2));
    assert(is(parse("2x45"), Kind::Chamfer, 2));
    assert(is(parse("2\xC3\x97" "45\xC2\xB0"), Kind::Chamfer, 2));  // 2×45°
    assert(is(parse("Z x 45"), Kind::Chamfer, 2));         // Z statt 2
    // Muster
    assert(parse("3x").kind == Kind::Pattern && parse("3x").count == 3);
    assert(parse("3\xC3\x97").count == 3);                  // 3×
    assert(parse("x4").count == 4);
    // Fläche ziehen/drücken
    assert(is(parse("+5"), Kind::Offset, 5));
    assert(is(parse("-5"), Kind::Offset, -5));
    assert(is(parse("\xE2\x88\x92" "2,5"), Kind::Offset, -2.5));  // −2,5
    // Passung
    assert(parse("H7").kind == Kind::Fit && parse("H7").fit == "H7");
    assert(parse("Druck").kind == Kind::Fit && parse("Druck").fit == "print");
    assert(parse("DRUCK").fit == "print");
    // Fläche entfernen
    assert(parse("weg").kind == Kind::Remove && parse("Entfernen").kind == Kind::Remove);
    assert(parse("l\xC3\xB6schen").kind == Kind::Remove && parse("remove").kind == Kind::Remove);
    // Maß
    assert(is(parse("12"), Kind::Value, 12));
    assert(is(parse("12,5 mm"), Kind::Value, 12.5));
    assert(is(parse("1O"), Kind::Value, 10));              // O statt 0 in einer Zahl

    // ungültig
    for (const char* bad : {"", "R", "M", "Hallo", "R0", "1x", "x", "h7", "M99", "H3", "Rundung", "+", "3x7x2"}) {
        assert(parse(bad).kind == Kind::None);
    }
    std::puts("red pen ok");
    return 0;
}
