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

    // Phase 11.7 Konfigurationen: Kopfzeile, Spalten je Wert, Auswahlzeile
    Configuration c;
    assert(parseHeader("Größe: S | M | L", c) && c.id == "Groesse" && c.options == std::vector<std::string>({"S", "M", "L"}));
    assert(parseHeader("Länge: 10 | 20", c) && c.options.size() == 2);  // Zahlen als Spalten
    assert(!parseHeader("Breite: 120 / 4 =", c));  // Rechenzeile
    assert(!parseHeader("Größe: S", c));           // nur eine Spalte
    assert(!parseHeader("Notiz: das ist | ein Satz", c));
    assert(!parseHeader("Einkaufsliste", c));
    std::vector<std::string> note = {"Größe: S | M | L", "Breite = 40 mm | 60 mm | 80 mm", "Wand = 2 mm"};
    std::map<size_t, std::string> errors;
    auto r = resolve(note, errors);
    assert(errors.empty() && r[1].definition && r[1].expression == "40 mm" && r[1].column == 0 && r[1].columns.size() == 3);
    assert(r[2].definition && r[2].expression == "2 mm" && r[2].column == -1);  // ohne "|" wie bisher
    choose(note, configurations(note)[0], 2);  // keine Auswahlzeile: unter die Kopfzeile
    assert(note.size() == 4 && note[1] == "Größe = L");
    r = resolve(note, errors);
    assert(errors.empty() && !r[1].definition && r[2].expression == "80 mm");  // Auswahl ist kein Parameter
    choose(note, configurations(note)[0], 1);  // Auswahlzeile ersetzt
    assert(note.size() == 4 && note[1] == "Größe = M" && resolve(note, errors)[2].expression == "60 mm");
    assert(withColumn(resolve(note, errors)[2], "65 mm") == "Breite = 40 mm | 65 mm | 80 mm");
    // Fehler: falsche Spaltenzahl, Werte ohne Kopfzeile, unbekannte Spalte
    errors.clear();
    resolve({"Größe: S | M", "Breite = 1 mm | 2 mm | 3 mm"}, errors);
    assert(errors.at(1) == "Needs one value per configuration");
    errors.clear();
    resolve({"Breite = 1 mm | 2 mm"}, errors);
    assert(errors.at(0) == "Needs one value per configuration");
    errors.clear();
    resolve({"Größe: S | M", "Größe = XL"}, errors);
    assert(errors.at(1) == "Not one of the configurations");
    // je Zeile gilt die nächste Kopfzeile darüber
    errors.clear();
    r = resolve({"Größe: S | M", "Größe = M", "A = 1 mm | 2 mm", "Farbe: Rot | Grün | Blau", "B = 1 | 2 | 3"}, errors);
    assert(errors.empty() && r[2].expression == "2 mm" && r[4].expression == "1");

    std::puts("note parameters ok");
    return 0;
}
