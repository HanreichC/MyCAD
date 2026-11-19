// SPDX-License-Identifier: LGPL-2.1-or-later
// Tasten am Grafiktablett (Einstellungen › Tablett), ohne FreeCAD:
//   g++ -std=c++20 -I src tests/tablet_keys_check.cpp -o /tmp/tablet && /tmp/tablet

#include <Gui/Shell/TabletKeys.h>

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

using namespace Gui::Shell::TabletKeys;

int main()
{
    // Modell am Gerätenamen: die H640P mit 6 Tasten, Unbekanntes lernt die Seite
    assert(std::strcmp(detect("HUION Huion Tablet_H640P Pad").id, "h640p") == 0);
    assert(detect("huion huion tablet_h640p pad").buttons == 6);
    assert(std::strcmp(detect("Wacom Intuos S Pad").id, "intuosS") == 0);
    assert(std::strcmp(detect("UGTABLET 10 inch PenTablet Pad").id, "other") == 0);
    assert(std::strcmp(detect("").id, "other") == 0);
    assert(std::strcmp(model("gibt es nicht").id, "other") == 0);

    // Vorschlag (H640P): 1 Rückgängig, 2 Radierer, 3 Auswählen, 4 Nur das Blatt, 5 Wiederholen, 6 Senkrecht ansehen;
    // Stift unten Ansicht drehen, oben Radierer, solange gedrückt
    const char* expected[] = {"undo", "eraser", "select", "sheet", "redo", "look"};
    for (int n = 1; n <= 6; ++n) {
        assert(suggestion(padKey(n)) == expected[n - 1]);
    }
    assert(suggestion("pad7") == "none");
    assert(actionFor({}, "penLow").kind == Kind::Rotate);
    assert(actionFor({}, "penHigh").kind == Kind::Hold);
    assert(std::strcmp(actionFor({}, "pad1").command, "Std_Undo") == 0);
    // jede Aktion mit Befehl hat einen, Rotate/Pan/Nichts keinen
    for (const Action& a : Actions) {
        assert((a.kind == Kind::Command || a.kind == Kind::Hold) == (*a.command != 0));
    }

    // Belegung speichern: nur Abweichungen vom Vorschlag, wieder gelesen gleich
    Assignment a;
    a["pad1"] = "undo";       // wie der Vorschlag: steht nicht in der Datei
    a["pad2"] = "marker";
    a["penLow"] = "pan";
    const std::string text = format(a);
    assert(text == "pad2=marker;penLow=pan");
    const Assignment back = parse(text);
    assert(actionFor(back, "pad2").id == std::string("marker"));
    assert(actionFor(back, "pad1").id == std::string("undo"));
    assert(actionFor(back, "penLow").kind == Kind::Pan);
    assert(parse("").empty() && parse(";;=x;pad3").empty());
    assert(actionFor(parse("pad1=kaputt"), "pad1").kind == Kind::None);  // alte/fremde Werte: Nichts

    // Drehen und Verschieben je Navigationsstil (Beschreibungen wie in Settings.cpp)
    Drag d = drag("Shift+Middle drag | Left+Right drag");  // Fusion 360: drehen
    assert(d.ok && d.button == 'M' && d.shift && !d.ctrl);
    d = drag("Middle drag | Left+Right drag");  // Fusion 360: verschieben
    assert(d.ok && d.button == 'M' && !d.shift);
    d = drag("Middle+Left drag | Shift+Right drag");  // CAD: zwei Tasten zugleich geht nicht, also die zweite
    assert(d.ok && d.button == 'R' && d.shift);
    d = drag("Left drag | One-finger drag");  // Gesture
    assert(d.ok && d.button == 'L');
    assert(!drag("Alt+Move").ok && !drag("One-finger drag").ok && !drag("").ok);  // Touchpad-Stil: ohne Maustaste

    std::puts("ok");
    return 0;
}
