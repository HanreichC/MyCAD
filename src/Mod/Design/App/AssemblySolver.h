// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Gelenke mit geschlossenen Ketten lösen (L6): dünne Schnittstelle zum Mehrkörper-Solver. Heute OndselSolver (der
/// FreeCAD-Fork, src/3rdParty/OndselSolver); ein anderer Solver (z. B. Project Chrono) ersetzt nur AssemblySolver.cpp.

#include <Base/Placement.h>

#include <string>
#include <vector>

namespace Design::Solver
{

struct Part
{
    std::string name;
    Base::Placement pose;  ///< global; Startwert, nach dem Lösen das Ergebnis
    bool fixed = false;    ///< bleibt, wo es ist (Boden)
};

enum class Kind
{
    Fixed,        ///< Rahmen fallen zusammen
    Revolute,     ///< drehen um die gemeinsame Z-Achse
    Slider,       ///< schieben entlang Z
    Cylindrical,  ///< drehen um und schieben entlang Z
    Planar,       ///< in der XY-Ebene schieben, um Z drehen
    Ball          ///< um den gemeinsamen Ursprung drehen
};

/// Gelenk zwischen zwei Teilen: die Rahmen onA (in a) und onB (in b) liegen nach dem Lösen wie die Art es verlangt
struct Link
{
    std::string name;
    Kind kind = Kind::Fixed;
    std::string a, b;
    Base::Placement onA, onB;
};

/// false mit error (englisch), wenn es keine Lösung gibt; sonst stehen die Lagen der beweglichen Teile in parts
bool solve(std::vector<Part>& parts, const std::vector<Link>& links, std::string& error);

}  // namespace Design::Solver
