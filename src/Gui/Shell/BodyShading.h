// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <FCGlobal.h>

#include <string>

class SoNode;

namespace Gui::Shell
{

/// Physikalisches Material für Körper (PBR): Rauheit und Metall, Fresnel, die Umgebung "Raum" spiegelt sich, Tonwertkurve
/// Khronos PBR Neutral. Ein gemeinsamer Knoten für alle Körper, gehört in deren Flächen-Zweig vor die Flächen.
/// Rauheit und Metall stehen in den Phong-Werten, die jede Datei ohnehin hat (FreeCAD-kompatibel):
///   Rauheit = 1 - Glanz (shininess). Metall: Leuchtfarbe Blau 1/255 = nein, 2/255 = ja (unsichtbar, in jeder Datei);
///   ohne Markierung (alte Dateien) Metall, wenn das Glanzlicht hell und heller als die Grundfarbe ist.
///   Leuchtfarbe Grün, Bits: 1 Klarlack, 2 Schliff entlang x, 4 Holz (Hirnholz an den x-Seiten), 8 Druckschichten entlang z.
///   Leuchtfarbe Rot (setzt die TextureExtension): 1/255 eigenes Bild, 2/255 Fotoscan aus bodyTexture.
/// Qualität "Sparsam" (Einstellungen) schaltet ihn ab: dann wie früher Phong. Prüfung: tests/gui/test_materials.py
GuiExport SoNode* bodyShading();

/// Fotoscan (":/mycad/textures/<name>.jpg") als Knoten für Stufe 0: Farbe im Maßstab aus dem Bild, dazu Normale und
/// Rauheit aus <name>_s.jpg auf Stufe 1. Geteilt von allen Körpern; nullptr für fremde Pfade oder fehlende Bilder.
GuiExport SoNode* bodyTexture(const std::string& path);

/// Kontaktschatten unter den Körpern einer Ansicht (nur Qualität "Hoch"): Was knapp über dem Boden liegt, von unten
/// gesehen als Maske, weich und halbdurchsichtig auf dem Boden. objects = die Körper der Ansicht (ObjectGroup des Viewers).
GuiExport SoNode* contactShadow(SoNode* objects);

/// Qualität neu lesen (MyCAD/RenderQuality: 0 Hoch, 1 Ausgewogen ohne Relief, Hirnholz und Kontaktschatten, 2 Sparsam) und anwenden
GuiExport void applyRenderQuality();

}  // namespace Gui::Shell
