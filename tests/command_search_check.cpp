// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung der Befehlssuche (Strg+K), ohne FreeCAD:
//   g++ -std=c++20 -I src tests/command_search_check.cpp -o /tmp/search && /tmp/search

#include <Gui/Shell/CommandSearch.h>

#include <cassert>
#include <cstdio>

using namespace CommandSearch;

int main()
{
    // Umlaute und Groß/klein
    assert(fold("Größe") == "groesse");
    assert(fold("ÄÖÜ") == "aeoeue");
    assert(score("groesse", {"Größe"}) == 100);
    assert(score("BOHRUNG", {"Bohrung", "Hole"}) == 100);

    // Rangfolge: ganzer Name > Namensanfang > Wortanfang > Synonym > Teilwort > Tippfehler
    const int exact = score("hole", {"Bohrung", "Hole"});
    const int prefix = score("boh", {"Bohrung", "Hole"});
    const int word = score("plane", {"Offset Plane"});
    const int synonym = score("loch", {"Bohrung", "Hole"}, {"Loch", "bohren"});
    const int inside = score("rung", {"Bohrung"});
    const int typo = score("bohrnug", {"Bohrung"});
    std::printf("exact %d prefix %d word %d synonym %d inside %d typo %d\n", exact, prefix, word, synonym, inside, typo);
    assert(exact > prefix && prefix > word && word > synonym && synonym > inside && inside > typo && typo > 0);

    // Tippfehler um ein Zeichen: vertauscht, fehlend, zu viel – erst ab 4 Zeichen
    assert(score("extrdue", {"Extrude"}) > 0);
    assert(score("extude", {"Extrude"}) > 0);
    assert(score("exttrude", {"Extrude"}) > 0);
    assert(score("xyz", {"Extrude"}) == 0);
    assert(score("abr", {"Abrunden"}) > 0);  // Anfang, kein Tippfehler nötig
    assert(score("abx", {"Abrunden"}) == 0);  // zu kurz für Tippfehler

    // leere Eingabe passt zu allem (Reihenfolge dann nach "zuletzt benutzt")
    assert(score("  ", {"Extrude"}) == 1);

    // Wörter mit Satzzeichen
    assert(score("oiled", {"Walnut, Oiled"}) == 70);

    // Phase 11.10: Sätze
    Intent i = intent("4 Löcher M3 in die Ecken, 5 mm vom Rand");
    assert(i.kind == Intent::Kind::CornerHoles && i.size == "M3" && i.offset == 5 && i.diameter == 0);
    i = intent("four holes \xC3\x98" "3.4 in the corners, 6 mm from the edge");
    assert(i.kind == Intent::Kind::CornerHoles && i.size.empty() && i.diameter == 3.4 && i.offset == 6);
    i = intent("Bohrungen M5x0.8 in die Ecken");  // ohne Abstand: zweimal der Nenndurchmesser
    assert(i.kind == Intent::Kind::CornerHoles && i.size == "M5" && i.offset == 10);
    i = intent("4 Löcher 3,5 mm in die Ecken 4,5 mm vom Rand");  // Dezimalkomma, Durchmesser ohne Ø
    assert(i.kind == Intent::Kind::CornerHoles && i.diameter == 3.5 && i.offset == 4.5);
    assert(intent("Bohrung").kind == Intent::Kind::None);                  // das ist ein Befehl, kein Satz
    assert(intent("4 Löcher M3").kind == Intent::Kind::None);              // wohin?
    assert(intent("6 Löcher M3 in die Ecken").kind == Intent::Kind::None); // vier Ecken
    assert(intent("Ecken abrunden").kind == Intent::Kind::None);  // Rundung ohne Maß: nichts Ausführbares
    // Rundung und Fase
    i = intent("Kanten 2 mm abrunden");
    assert(i.kind == Intent::Kind::Fillet && i.value == 2 && !i.all);
    i = intent("alle Kanten 1,5 mm verrunden");
    assert(i.kind == Intent::Kind::Fillet && i.value == 1.5 && i.all);
    i = intent("fillet all edges R3");
    assert(i.kind == Intent::Kind::Fillet && i.value == 3 && i.all);
    i = intent("Fase 0,5 mm");
    assert(i.kind == Intent::Kind::Chamfer && i.value == 0.5);
    i = intent("chamfer every edge 1 mm");
    assert(i.kind == Intent::Kind::Chamfer && i.value == 1 && i.all);
    i = intent("alle 4 Kanten 2 mm abrunden");  // die Anzahl ist nicht das Maß
    assert(i.kind == Intent::Kind::Fillet && i.value == 2);
    assert(intent("Rundung").kind == Intent::Kind::None);
    assert(intent("4 Löcher M3 in die Ecken, 5 mm vom Rand").kind == Intent::Kind::CornerHoles);  // weiter Bohrungen

    std::puts("command search ok");
    return 0;
}
