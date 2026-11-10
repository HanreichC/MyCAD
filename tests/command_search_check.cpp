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

    std::puts("command search ok");
    return 0;
}
