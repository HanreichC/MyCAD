// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <FCGlobal.h>

class SoNode;

namespace Gui::Shell
{

/// Physikalisches Material für Körper (PBR): Rauheit und Metall, Fresnel, die Umgebung "Raum" spiegelt sich, Tonwertkurve
/// Khronos PBR Neutral. Ein gemeinsamer Knoten für alle Körper, gehört in deren Flächen-Zweig vor die Flächen.
/// Rauheit und Metall stehen in den Phong-Werten, die jede Datei ohnehin hat (FreeCAD-kompatibel):
///   Rauheit = 1 - Glanz (shininess). Metall: Leuchtfarbe Blau 1/255 = nein, 2/255 = ja (unsichtbar, in jeder Datei);
///   ohne Markierung (alte Dateien) Metall, wenn das Glanzlicht hell und heller als die Grundfarbe ist.
///   Leuchtfarbe Rot 1/255: der Körper hat eine Textur (TextureExtension).
/// Qualität "Sparsam" (Einstellungen) schaltet ihn ab: dann wie früher Phong. Prüfung: tests/gui/test_materials.py
GuiExport SoNode* bodyShading();

/// Qualität neu lesen (MyCAD/RenderQuality: 0 Hoch, 1 Ausgewogen, 2 Sparsam) und anwenden
GuiExport void applyRenderQuality();

}  // namespace Gui::Shell
