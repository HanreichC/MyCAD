// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <vector>

namespace Gui::Shell
{

/// Ersetzt die klassische FreeCAD-Oberfläche durch die MyCAD-Oberfläche:
/// 3D-Ansicht über das ganze Fenster, darüber schwebende Liquid-Glass-Panels.
void install();
/// Namen unter den Symbolen der Toolbar ein-/ausblenden (Einstellung "Show tool names")
void setToolNames(bool on);
/// Aussehen der Körper (Einstellung "Body material"): Auswahl und Wahl; färbt Körper mit Standard-Look gleich um
std::vector<const char*> bodyMaterialNames();
void setBodyMaterial(int index);

}  // namespace Gui::Shell
