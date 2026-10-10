#!/usr/bin/env python3
# SPDX-License-Identifier: LGPL-2.1-or-later
"""MyCAD-Icons im SF-Symbols-Stil: 24er-Raster, Strich 1.7, runde Enden, Farbe = currentColor.
Die Shell färbt currentColor beim Laden in die Textfarbe des Themes.
Erzeugt src/Gui/Shell/icons/<Befehl>.svg und icons.qrc.   python3 tools/make_icons.py"""
import pathlib

OUT = pathlib.Path(__file__).resolve().parent.parent / "src/Gui/Shell/icons"

DOT = '<circle cx="{}" cy="{}" r="1.7" fill="currentColor" stroke="none"/>'
DASH = ' stroke-dasharray="2 2.6"'

ICONS = {
    # Datei / Bearbeiten
    "Std_New": '<path d="M6 3h8l4 4v14H6z"/><path d="M14 3v4h4"/><path d="M12 11v6M9 14h6"/>',
    "Std_Open": '<path d="M3 7.5A2 2 0 0 1 5 5.5h4l2 2h8a2 2 0 0 1 2 2V17a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z"/>',
    "Std_Save": '<path d="M12 4v10M8 10l4 4 4-4"/><path d="M4 16v2a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2v-2"/>',
    "Design_Export": '<path d="M12 15V4M8 8l4-4 4 4"/><path d="M5 12v6a2 2 0 0 0 2 2h10a2 2 0 0 0 2-2v-6"/>',
    "Std_Undo": '<path d="M9 7l-4 4 4 4"/><path d="M5 11h9a5 5 0 0 1 0 10h-2"/>',
    "Std_Redo": '<path d="M15 7l4 4-4 4"/><path d="M19 11h-9a5 5 0 0 0 0 10h2"/>',
    "Std_ViewFitAll": '<path d="M4 9V4h5M15 4h5v5M20 15v5h-5M9 20H4v-5"/>',
    # Erstellen
    "Design_CreateSketch": '<path d="M4 20h4L19 9a2.1 2.1 0 0 0-3-3L5 17z"/><path d="M14 8l3 3"/><path d="M13 20h7"/>',
    "Design_Extrude": '<path d="M3 18l5-3h13l-5 3z"/><path d="M13 12V3M10 6l3-3 3 3"/>',
    "Design_Revolve": '<path d="M12 4v16"' + DASH + '/><path d="M19 12a7 7 0 1 1-2.05-4.95"/><path d="M19 4v4h-4"/>',
    "Design_Hole": '<ellipse cx="12" cy="7" rx="8" ry="3"/><ellipse cx="12" cy="7" rx="3.4" ry="1.3"/>'
                   '<path d="M8.6 7v10M15.4 7v10"/><path d="M8.6 17a3.4 1.3 0 0 0 6.8 0"/>',
    # Ändern
    "Design_PressPull": '<path d="M4 14l8-4 8 4-8 4z"/><path d="M12 13V3M9 6l3-3 3 3"/>',
    "Design_Fillet": '<path d="M4 20v-6A10 10 0 0 1 14 4h6"/><path d="M4 4h3M4 4v3"/>',
    "Design_Chamfer": '<path d="M4 20v-8l8-8h8"/><path d="M4 4h3M4 4v3"/>',
    "Design_Shell": '<path d="M4 7.5l8-4 8 4v9l-8 4-8-4z"/><path d="M7.5 8.5l4.5-2.2 4.5 2.2-4.5 2.2z"/>',
    "Design_Pattern": '<rect x="4" y="4" width="6.5" height="6.5" rx="1.6"/><rect x="13.5" y="4" width="6.5" height="6.5" rx="1.6"/>'
                      '<rect x="4" y="13.5" width="6.5" height="6.5" rx="1.6"/><rect x="13.5" y="13.5" width="6.5" height="6.5" rx="1.6"/>',
    "Design_Mirror": '<path d="M12 3v18"' + DASH + '/><path d="M9 6L3 18h6z"/><path d="M15 6l6 12h-6z"/>',
    "Design_Combine": '<circle cx="9" cy="12" r="6"/><circle cx="15" cy="12" r="6"/>',
    "Design_Move": '<path d="M12 3v18M3 12h18"/><path d="M9 6l3-3 3 3M9 18l3 3 3-3M6 9l-3 3 3 3M18 9l3 3-3 3"/>',
    "Design_OffsetPlane": '<path d="M3 20l5-3h13l-5 3z"/><path d="M3 8l5-3h13l-5 3z"/><path d="M12 15.5v-5M10 12.5l2-2 2 2"/>',
    # Skizze: Erstellen
    "Sketcher_CreateLine": '<path d="M6 18L18 6"/>' + DOT.format(6, 18) + DOT.format(18, 6),
    "Sketcher_CreatePolyline": '<path d="M4 18l5-9 6 6 5-9"/>' + DOT.format(4, 18) + DOT.format(20, 6),
    "Sketcher_CreateRectangle": '<rect x="4" y="6" width="16" height="12" rx="1"/>',
    "Sketcher_CreateCircle": '<circle cx="12" cy="12" r="8"/>' + DOT.format(12, 12),
    "Sketcher_CreateArc": '<path d="M5 17a8 8 0 0 1 14 0"/>' + DOT.format(5, 17) + DOT.format(19, 17),
    "Sketcher_CreateSlot": '<rect x="3" y="8" width="18" height="8" rx="4"/>',
    "Sketcher_CompCreateRegularPolygon": '<path d="M12 3l7.8 4.5v9L12 21l-7.8-4.5v-9z"/>',
    "Sketcher_CreateBSpline": '<path d="M4 18C8 6 12 22 20 6"/>' + DOT.format(4, 18) + DOT.format(20, 6),
    "Sketcher_CreatePoint": '<circle cx="12" cy="12" r="2.6" fill="currentColor"/><path d="M12 4v3M12 17v3M4 12h3M17 12h3"/>',
    # Skizze: Ändern
    "Sketcher_CreateFillet": '<path d="M5 19v-8a6 6 0 0 1 6-6h8"/>',
    "Sketcher_Trimming": '<circle cx="6" cy="7" r="2.5"/><circle cx="6" cy="17" r="2.5"/><path d="M8.2 8.4L20 16M8.2 15.6L20 8"/>',
    "Sketcher_Extend": '<path d="M4 12h9"/><path d="M13 12h6"' + DASH + '/><path d="M17 9l3 3-3 3"/>',
    "Sketcher_Split": '<path d="M3 12h5.5M15.5 12H21"/>' + DOT.format(9.5, 12) + DOT.format(14.5, 12),
    "Sketcher_ToggleConstruction": '<path d="M5 19L19 5"' + DASH + '/>',
    # Skizze: Bemaßung & Bedingungen
    "Sketcher_Dimension": '<path d="M4 7v10M20 7v10M5 12h14"/><path d="M8 9l-3 3 3 3M16 9l3 3-3 3"/>',
    "Sketcher_ConstrainCoincidentUnified": '<path d="M4 20l8-8M20 20l-8-8"/>' + DOT.format(12, 12),
    "Sketcher_ConstrainHorizontal": '<path d="M4 15h16"/><rect x="8.5" y="7" width="7" height="3.4" rx="1.7"/>',
    "Sketcher_ConstrainVertical": '<path d="M9 4v16"/><rect x="13.6" y="8.5" width="3.4" height="7" rx="1.7"/>',
    "Sketcher_ConstrainParallel": '<path d="M7 19L13 5M11 19L17 5"/>',
    "Sketcher_ConstrainPerpendicular": '<path d="M5 19h14M10 19V5"/><path d="M10 15h4v4"/>',
    "Sketcher_ConstrainTangent": '<circle cx="12" cy="14" r="5.5"/><path d="M3 8.5h18"/>',
    "Sketcher_ConstrainEqual": '<path d="M6 9h12M6 15h12"/>',
    "Sketcher_ConstrainSymmetric": '<path d="M12 4v16"' + DASH + '/>' + DOT.format(6, 12) + DOT.format(18, 12),
    "Sketcher_ConstrainBlock": '<rect x="6" y="11" width="12" height="9" rx="2"/><path d="M9 11V8a3 3 0 0 1 6 0v3"/>',
}


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    for name, body in ICONS.items():
        (OUT / f"{name}.svg").write_text(
            '<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" '
            'stroke="currentColor" stroke-width="1.7" stroke-linecap="round" stroke-linejoin="round">'
            + body + "</svg>\n"
        )
    files = "\n".join(f"        <file>{n}.svg</file>" for n in ICONS)
    (OUT / "icons.qrc").write_text(f'<RCC>\n    <qresource prefix="/mycad/icons">\n{files}\n    </qresource>\n</RCC>\n')
    print(f"{len(ICONS)} icons -> {OUT}")


if __name__ == "__main__":
    main()
