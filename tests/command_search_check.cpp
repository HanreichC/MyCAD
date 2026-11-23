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

    // Bohrmuster, je Deutsch und Englisch
    for (const char* s : {"6 Löcher M4 auf Lochkreis 40", "six holes M4 on a bolt circle 40 mm",
                          "6 Bohrungen M4 im Kreis, \xC3\x98" "40", "6 holes M4 around a 40 mm circle"}) {
        i = intent(s);
        assert(i.kind == Intent::Kind::CircleHoles && i.count == 6 && i.size == "M4" && i.pitch == 40);
    }
    i = intent("6 Löcher im Kreis, \xC3\x98" "40");  // ohne Bohrungsmaß: Ø5 (wie das Werkzeug)
    assert(i.kind == Intent::Kind::CircleHoles && i.count == 6 && i.pitch == 40 && i.diameter == 5);
    i = intent("8 holes \xC3\x98" "3.4 on a 50 mm circle");
    assert(i.kind == Intent::Kind::CircleHoles && i.count == 8 && i.diameter == 3.4 && i.pitch == 50);
    i = intent("acht Bohrungen \xC3\x98" "6,5 auf Teilkreis 80");
    assert(i.kind == Intent::Kind::CircleHoles && i.count == 8 && i.diameter == 6.5 && i.pitch == 80);
    for (const char* s : {"5 Löcher M3 in einer Reihe, 10 mm Abstand", "5 holes M3 in a row, 10 mm apart",
                          "fünf Bohrungen M3 in einer Reihe im Abstand von 10 mm", "five holes M3 in a line 10 mm spacing"}) {
        i = intent(s);
        assert(i.kind == Intent::Kind::RowHoles && i.count == 5 && i.size == "M3" && i.pitch == 10);
    }
    i = intent("3 holes \xC3\x98" "4 in a row");  // ohne Abstand: gleichmäßig verteilt
    assert(i.kind == Intent::Kind::RowHoles && i.count == 3 && i.diameter == 4 && i.pitch == 0);
    assert(intent("Lochkreis").kind == Intent::Kind::None);
    assert(intent("1 Loch M3 in einer Reihe").kind == Intent::Kind::None);  // eins ist kein Muster

    // 12.9 Fragen ans Modell, DE und EN; Befehle bleiben Befehle
    for (const char* s : {"Warum ist das rot?", "warum rot", "why is this red?", "Was ist falsch?", "what's wrong",
                          "wieso rechnet das nicht", "why does it fail"}) {
        assert(intent(s).kind == Intent::Kind::WhyRed);
    }
    for (const char* s : {"Was hängt daran?", "was haengt davon ab", "what depends on this?", "wer benutzt die Skizze",
                          "which steps use this"}) {
        assert(intent(s).kind == Intent::Kind::DependsOn);
    }
    assert(intent("rot").kind == Intent::Kind::None);  // Farbe allein ist keine Frage
    assert(intent("rotate").kind == Intent::Kind::None);
    assert(intent("Kanten 2 mm abrunden").kind == Intent::Kind::Fillet);

    // 12.9 Grundkörper und Wand, DE und EN
    for (const char* s : {"Quader 40 x 30 x 10", "box 40x30x10", "Quader 40 \xC3\x97 30 \xC3\x97 10 mm", "block 40mm 30mm 10mm"}) {
        i = intent(s);
        assert(i.kind == Intent::Kind::Box && i.dims[0] == 40 && i.dims[1] == 30 && i.dims[2] == 10);
    }
    i = intent("Würfel 20");
    assert(i.kind == Intent::Kind::Box && i.dims[0] == 20 && i.dims[1] == 20 && i.dims[2] == 20);
    for (const char* s : {"Zylinder \xC3\x98" "20 x 30", "cylinder d20 h30", "Zylinder Durchmesser 20, 30 hoch", "cylinder r10 h30",
                          "Zylinder 20 x 30"}) {
        i = intent(s);
        assert(i.kind == Intent::Kind::Cylinder && i.dims[0] == 20 && i.dims[1] == 30);
    }
    i = intent("Scheibe \xC3\x98" "40 x 3");
    assert(i.kind == Intent::Kind::Cylinder && i.dims[0] == 40 && i.dims[1] == 3);
    for (const char* s : {"Wand 2 mm", "aushöhlen 2", "shell 2 mm", "hollow 2mm"}) {
        i = intent(s);
        assert(i.kind == Intent::Kind::Shell && i.value == 2);
    }
    assert(intent("Wand 1,5 mm").value == 1.5);
    assert(intent("Quader").kind == Intent::Kind::None);         // ohne Maße: der Befehl, kein Satz
    assert(intent("Quader 40 x 30").kind == Intent::Kind::None);  // ein Maß fehlt
    assert(intent("Wandhalter").kind == Intent::Kind::None);
    assert(intent("6 Löcher M4 auf Lochkreis 40").kind == Intent::Kind::CircleHoles);  // Bohrmuster bleiben

    // 12.9 Verschieben, DE und EN; ohne Richtung kein Satz
    i = intent("10 mm nach oben verschieben");
    assert(i.kind == Intent::Kind::Move && i.dims[0] == 0 && i.dims[1] == 0 && i.dims[2] == 10);
    i = intent("move 20 mm left");
    assert(i.kind == Intent::Kind::Move && i.dims[0] == -20 && i.dims[2] == 0);
    i = intent("um 5 nach vorne schieben");
    assert(i.kind == Intent::Kind::Move && i.dims[1] == -5);
    i = intent("verschieben x 10 y -5");
    assert(i.kind == Intent::Kind::Move && i.dims[0] == 10 && i.dims[1] == -5 && i.dims[2] == 0);
    assert(intent("verschieben 10").kind == Intent::Kind::None);  // wohin?
    i = intent("10 mm nach oben");  // ohne Verb: das Richtungswort sagt es
    assert(i.kind == Intent::Kind::Move && i.dims[2] == 10);
    assert(intent("x 10").kind == Intent::Kind::None);  // Achse ohne Verb: keine Verschiebung
    assert(intent("Verschieben").kind == Intent::Kind::None);
    assert(intent("Quader 40 x 30 x 10").kind == Intent::Kind::Box);  // x als Mal-Zeichen bleibt beim Quader

    std::puts("command search ok");
    return 0;
}
