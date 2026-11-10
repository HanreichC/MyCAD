// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung des Zeilen-Parsers für Parameter in Notizen (Idee 3), ohne FreeCAD:
//   g++ -std=c++20 -I src tests/note_parameters_check.cpp -o /tmp/notes && /tmp/notes

#include <Mod/Design/App/NoteParameters.h>

#include <cassert>
#include <cstdio>

using namespace NoteParameters;

int main()
{
    // Definition
    Line l = parse("Wand = 2 mm");
    assert(l.definition && l.name == "Wand" && l.id == "Wand" && l.expression == "2 mm");
    l = parse("  Breite=Wand * 20  ");
    assert(l.definition && l.name == "Breite" && l.expression == "Wand * 20");
    l = parse("Länge_2 = 2,5 mm");  // Dezimalkomma bleibt im Ausdruck (der Parser von FreeCAD versteht es nicht: Sync)
    assert(l.definition && l.id == "Laenge_2" && l.expression == "2,5 mm");

    // Umlaute und ß
    assert(identifier("Wandstärke") == "Wandstaerke");
    assert(identifier("Öffnung") == "Oeffnung");
    assert(identifier("Größe") == "Groesse");

    // keine Definition: Rechenzeile, Satz, Ziffer am Anfang, mehrere "=", leer
    assert(!parse("120 / 4 =").definition);
    assert(!parse("Breite: 120 / 4 =").definition);
    assert(!parse("Wand = 2 =").definition);
    assert(!parse("Die Wand ist = dick").definition);
    assert(!parse("2x = 4").definition);
    assert(!parse("Wand =").definition);
    assert(!parse("= 4").definition);
    assert(!parse("Einkaufsliste").definition);

    // Hinweise werden beim Lesen ignoriert und beim Schreiben ersetzt
    l = parse("Breite = Wand * 20 \xE2\x86\x92 40 mm");
    assert(l.definition && l.expression == "Wand * 20");
    l = parse("Wand = 2 mm \xE2\x9A\xA0 already defined");
    assert(l.definition && l.expression == "2 mm");
    assert(withHint("Breite = Wand * 20 \xE2\x86\x92 40 mm", "60 mm", "") == "Breite = Wand * 20 \xE2\x86\x92 60 mm");
    assert(withHint("Wand = 2 mm", "", "Name is used twice") == "Wand = 2 mm \xE2\x9A\xA0 Name is used twice");
    assert(withHint("Wand = 2 mm \xE2\x9A\xA0 old", "", "") == "Wand = 2 mm");

    std::puts("note parameters ok");
    return 0;
}
