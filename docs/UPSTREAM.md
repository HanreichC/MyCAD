# Herkunft

MyCAD basiert auf [FreeCAD](https://github.com/FreeCAD/FreeCAD) (LGPL-2.1-or-later).

- Quelle: FreeCAD 27.1-dev, Commit `e9b474306f` ("fix: chamfer line always connects to endpoints of fillet")
- Kopiert am 2026-10-10, ohne Git-Historie

## Übernommene Pfade

| MyCAD | FreeCAD |
|---|---|
| `CMakeLists.txt`, `LICENSE`, `version.json`, `cMake/` | gleich |
| `src/{App,Base,Build,Ext,Gui,Main,Tools,XDGData}` | gleich |
| `src/Mod/{Part,Sketcher,PartDesign,Material,Import,Measure,Mesh,MeshPart}` | gleich |
| `src/3rdParty/{FastSignals,GSL,json,lazy_loader,PyCXX,WildMagic4,zipios++,libkdtree,Clipper2,lru-cache}` | gleich |
| `tests/src/{App,Base,Gui,zipios++}`, `tests/src/Mod/{Part,Sketcher,PartDesign,Material,Measure,Mesh,MeshPart}` | gleich |
| `data/tests/` (Teilmenge) | gleich |

Coin3D und Pivy kommen aus den Arch-Systempaketen, nicht aus den FreeCAD-Submodulen.

## Fixes von FreeCAD nachziehen

```sh
git -C ../FreeCAD log --oneline e9b474306f..origin/main -- src/Mod/Sketcher/App/planegcs
git -C ../FreeCAD diff e9b474306f origin/main -- <pfad> | git apply --directory=. -p1
```
