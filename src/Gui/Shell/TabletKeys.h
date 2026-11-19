// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Tasten am Grafiktablett (Einstellungen › Tablett): Modelle, Aktionen, Belegungsvorschlag, gespeicherte Belegung.
/// Reine Logik ohne Qt und FreeCAD; das Lesen der Tasten und das Ausführen steht in Settings.cpp.
/// Prüfung: tests/tablet_keys_check.cpp

#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include <string_view>

namespace Gui::Shell::TabletKeys
{

/// Was eine Taste tut. Command: einmal ausführen. Hold: beim Drücken und beim Loslassen ausführen (Radierer, solange
/// gedrückt: der Befehl schaltet um und wieder zurück). Rotate/Pan: Ansicht, solange die Taste gedrückt ist.
enum class Kind
{
    None,
    Command,
    Hold,
    Rotate,
    Pan
};

struct Action
{
    const char* id;       ///< gespeichert in der Belegung
    const char* label;    ///< englisch, übersetzt mit T()
    const char* command;  ///< FreeCAD-Befehl (Command, Hold)
    Kind kind;
    int group;  ///< Trennlinie in der Liste, wenn die Gruppe wechselt
};

inline constexpr Action Actions[] = {
    {"eraser", "Eraser", "Design_ScribbleEraser", Kind::Command, 0},
    {"eraserHold", "Eraser while held", "Design_ScribbleEraser", Kind::Hold, 0},
    {"select", "Select", "Design_ScribbleSelect", Kind::Command, 0},
    {"pencil", "Pencil", "Design_ScribblePencil", Kind::Command, 1},
    {"fineliner", "Fineliner", "Design_ScribblePen", Kind::Command, 1},
    {"marker", "Marker", "Design_ScribbleMarker", Kind::Command, 1},
    {"color", "Next Color", "Design_ScribbleNextColor", Kind::Command, 1},
    {"undo", "Undo", "Std_Undo", Kind::Command, 2},
    {"redo", "Redo", "Std_Redo", Kind::Command, 2},
    {"sheet", "Only the Sheet", "Design_ScribbleFocus", Kind::Command, 3},
    {"look", "Look At", "Design_ScribbleLookAt", Kind::Command, 3},
    {"rotate", "Rotate View", "", Kind::Rotate, 3},
    {"pan", "Pan View", "", Kind::Pan, 3},
    {"none", "Nothing", "", Kind::None, 4},
};

inline const Action& action(std::string_view id)
{
    for (const Action& a : Actions) {
        if (id == a.id) {
            return a;
        }
    }
    return Actions[std::size(Actions) - 1];  // Nichts
}

struct Model
{
    const char* id;
    const char* label;
    const char* match;  ///< Teil des Gerätenamens, den libinput meldet (Groß-/Kleinschreibung egal)
    int buttons;        ///< Tasten am Tablett; 0 = unbekannt, die Seite lernt sie beim Drücken
};

/// ponytail: nur die H640P ist am echten Gerät geprüft (6 Tasten). Die übrigen erkennt MyCAD an einem Teil des Namens
/// und lernt ihre Tasten beim ersten Drücken; Tastenzahl eintragen, sobald jemand das Modell hat
inline constexpr Model Models[] = {
    {"h430p", "Huion H430P", "H430P", 0},
    {"h640p", "Huion H640P", "H640P", 6},
    {"h950p", "Huion H950P", "H950P", 0},
    {"h1060p", "Huion H1060P", "H1060P", 0},
    {"dial", "Huion Inspiroy Dial", "Inspiroy Dial", 0},
    {"keydial", "Huion Inspiroy Keydial", "Keydial", 0},
    {"intuosS", "Wacom Intuos S", "Intuos S", 0},
    {"intuosM", "Wacom Intuos M", "Intuos M", 0},
    {"one", "Wacom One", "Wacom One", 0},
    {"deco01", "XP-Pen Deco 01", "Deco 01", 0},
    {"mini7", "XP-Pen Deco Mini7", "Mini7", 0},
    {"g640", "XP-Pen Star G640", "G640", 0},
    {"other", "Other Model", "", 0},
};

inline const Model& model(std::string_view id)
{
    for (const Model& m : Models) {
        if (id == m.id) {
            return m;
        }
    }
    return Models[std::size(Models) - 1];  // Anderes Modell
}

/// Modell zum Gerätenamen von libinput ("HUION Huion Tablet_H640P Pad"), sonst "Anderes Modell"
inline const Model& detect(std::string_view deviceName)
{
    const auto lower = [](std::string_view s) {
        std::string r(s);
        std::transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { return char(std::tolower(c)); });
        return r;
    };
    const std::string name = lower(deviceName);
    for (const Model& m : Models) {
        if (*m.match && name.find(lower(m.match)) != std::string::npos) {
            return m;
        }
    }
    return Models[std::size(Models) - 1];
}

/// Tasten: "pad1" … "padN" am Tablett (1 = erste Taste, libinput zählt ab 0), "penLow"/"penHigh" am Stift
inline std::string padKey(int number)
{
    return "pad" + std::to_string(number);
}

/// Vorschlag (H640P, mit dem Benutzer abgestimmt); weitere Tasten anderer Modelle: Nichts
inline std::string suggestion(std::string_view key)
{
    static const std::map<std::string, std::string, std::less<>> s = {
        {"pad1", "undo"},   {"pad2", "eraser"},   {"pad3", "select"},     {"pad4", "sheet"},
        {"pad5", "redo"},   {"pad6", "look"},     {"penLow", "rotate"},   {"penHigh", "eraserHold"}};
    const auto it = s.find(key);
    return it == s.end() ? "none" : it->second;
}

/// Belegung, wie sie in den Einstellungen steht: "pad1=undo;penLow=rotate". Nur Abweichungen vom Vorschlag.
using Assignment = std::map<std::string, std::string, std::less<>>;

inline Assignment parse(std::string_view text)
{
    Assignment a;
    while (!text.empty()) {
        const size_t end = std::min(text.find(';'), text.size());
        const std::string_view item = text.substr(0, end);
        if (const size_t eq = item.find('='); eq != std::string_view::npos && eq > 0) {
            a[std::string(item.substr(0, eq))] = std::string(item.substr(eq + 1));
        }
        text.remove_prefix(std::min(end + 1, text.size()));
    }
    return a;
}

inline std::string format(const Assignment& a)
{
    std::string out;
    for (const auto& [key, id] : a) {
        if (id != suggestion(key)) {
            out += (out.empty() ? "" : ";") + key + "=" + id;
        }
    }
    return out;
}

/// Aktion einer Taste: gespeichert, sonst der Vorschlag; unbekannte gespeicherte Aktionen gelten als Nichts
inline const Action& actionFor(const Assignment& a, std::string_view key)
{
    const auto it = a.find(key);
    return action(it == a.end() ? suggestion(key) : it->second);
}

/// Mit welcher Maustaste (L, M, R) und welchen Modifiern ein Navigationsstil dreht oder verschiebt. Liest die erste
/// Alternative mit genau einer Maustaste aus der Beschreibung in Settings.cpp ("Shift+Middle drag | Left+Right drag").
/// ok = false: keine passende Alternative (dann tut die Taste nichts).
/// ponytail: Stile, die mit der linken Taste drehen (Gesture, Inventor, OpenSCAD), würden im Scribble dabei zeichnen
struct Drag
{
    bool ok = false;
    char button = 0;
    bool shift = false, ctrl = false, alt = false;
};

inline Drag drag(std::string_view description)
{
    while (!description.empty()) {
        const size_t bar = description.find(" | ");
        std::string_view alt = description.substr(0, bar);
        description = bar == std::string_view::npos ? std::string_view() : description.substr(bar + 3);
        if (const size_t d = alt.find(" drag"); d != std::string_view::npos) {
            alt = alt.substr(0, d);
        }
        else {
            continue;
        }
        Drag r;
        int buttons = 0;
        bool known = true;
        while (!alt.empty()) {
            const size_t plus = alt.find('+');
            const std::string_view part = alt.substr(0, plus);
            alt = plus == std::string_view::npos ? std::string_view() : alt.substr(plus + 1);
            if (part == "Shift") {
                r.shift = true;
            }
            else if (part == "Ctrl") {
                r.ctrl = true;
            }
            else if (part == "Alt") {
                r.alt = true;
            }
            else if (part == "Left" || part == "Middle" || part == "Right") {
                r.button = part[0];
                ++buttons;
            }
            else {
                known = false;  // "One-finger" u. Ä.
            }
        }
        if (known && buttons == 1) {
            r.ok = true;
            return r;
        }
    }
    return {};
}

}  // namespace Gui::Shell::TabletKeys
