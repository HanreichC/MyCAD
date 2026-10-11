#!/usr/bin/env python3
# SPDX-License-Identifier: LGPL-2.1-or-later
"""MyCAD-Icons im SF-Symbols-Stil: 24er-Raster, Strich 1.7, runde Enden, Farbe = currentColor.
Die Shell färbt currentColor beim Laden in die Textfarbe des Themes.
Erzeugt src/Gui/Shell/icons/<Befehl>.svg und icons.qrc.   python3 tools/make_icons.py"""
import math
import pathlib

OUT = pathlib.Path(__file__).resolve().parent.parent / "src/Gui/Shell/icons"

DOT = '<circle cx="{}" cy="{}" r="1.7" fill="currentColor" stroke="none"/>'
DASH = ' stroke-dasharray="2 2.6"'


def polygon(n, r=8.5):
    """regelmäßiges n-Eck um (12, 12), Spitze oben"""
    pts = [(12 + r * math.sin(2 * math.pi * k / n), 12 - r * math.cos(2 * math.pi * k / n)) for k in range(n)]
    return '<path d="M' + "L".join("%.2f %.2f" % p for p in pts) + 'z"/>'


ICONS = {
    # Datei / Bearbeiten
    "Std_New": '<path d="M6 3h8l4 4v14H6z"/><path d="M14 3v4h4"/><path d="M12 11v6M9 14h6"/>',
    "Std_Open": '<path d="M3 7.5A2 2 0 0 1 5 5.5h4l2 2h8a2 2 0 0 1 2 2V17a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z"/>',
    "Std_Save": '<path d="M12 4v10M8 10l4 4 4-4"/><path d="M4 16v2a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2v-2"/>',
    "Design_Plane": '<path d="M3 17l5-10h13l-5 10z"/>' + DOT.format(8, 7) + DOT.format(21, 7) + DOT.format(16, 17),
    "Design_Midplane": '<path d="M3 20l4-6h14l-4 6zM3 10l4-6h14l-4 6z"' + DASH + '/><path d="M3 15l4-6h14l-4 6z"/>',
    "Design_Axis": '<path d="M5 19L19 5"/><path d="M3 21l1.5-1.5M19.5 4.5L21 3"' + DASH + '/>' + DOT.format(12, 12),
    "Design_Point": '<circle cx="12" cy="12" r="3" fill="currentColor"/><path d="M12 3v4M12 17v4M3 12h4M17 12h4"/>',
    "Design_Measure": '<path d="M3 15.5L15.5 3 21 8.5 8.5 21z"/><path d="M7 12.5l2 2M10 9.5l1.5 1.5M13 6.5l2 2"/>',
    "Design_Section": '<path d="M12 3l8 4.5v9L12 21l-8-4.5v-9z"/><path d="M3 13l18-4" stroke-dasharray="2 2"/><path d="M4 7.5l8 4.5 8-4.5"/>',
    "Design_Sweep": '<path d="M4 19c6 0 4-14 14-14"/><ellipse cx="18" cy="5" rx="2" ry="3.2"/><ellipse cx="4" cy="19" rx="2" ry="3.2"/>',
    "Design_Loft": '<rect x="3" y="15" width="8" height="5" rx="1"/><circle cx="16" cy="6" r="3.5"/><path d="M3 15L12.6 5M11 15l8.5-7.5"/>',
    "Design_Box": '<path d="M12 3l8 4.5v9L12 21l-8-4.5v-9z"/><path d="M4 7.5l8 4.5 8-4.5M12 12v9"/>',
    "Design_Primitive": '<path d="M12 3l8 4.5v9L12 21l-8-4.5v-9z"/><path d="M4 7.5l8 4.5 8-4.5M12 12v9"/>',
    "Design_Cylinder": '<ellipse cx="12" cy="6" rx="7" ry="3"/><path d="M5 6v12c0 1.7 3.1 3 7 3s7-1.3 7-3V6"/>',
    "Design_Sphere": '<circle cx="12" cy="12" r="8.5"/><ellipse cx="12" cy="12" rx="8.5" ry="3"/>',
    "Design_Torus": '<ellipse cx="12" cy="12" rx="9.5" ry="5.5"/><ellipse cx="12" cy="11.5" rx="4" ry="1.8"/>',
    "Design_Coil": '<path d="M5 6c0-2 14-2 14 0s-14 2-14 4 14 2 14 4-14 2-14 4 14 2 14 4"/>',
    "Design_Draft": '<path d="M5 20h14M7 20l2-15h6l2 15"/><path d="M12 5v15"' + DASH + '/>',
    "Design_Scale": '<rect x="3" y="11" width="10" height="10" rx="1"/><path d="M13 11l8-8M15 3h6v6"/><rect x="3" y="3" width="18" height="18" rx="2"' + DASH + '/>',
    "Design_Align": '<rect x="3" y="14" width="8" height="7" rx="1"/><rect x="13" y="3" width="8" height="7" rx="1"/><path d="M7 14V6.5h6M10 4l3 2.5L10 9"/>',
    "Design_SplitBody": '<path d="M12 3l8 4.5v9L12 21l-8-4.5v-9z"/><path d="M3 14L21 10" stroke-dasharray="2.4 2"/>',
    "Design_Thread": '<path d="M8 3h8M8 21h8M8 6l8 2M8 10l8 2M8 14l8 2M8 18l8 2"/><path d="M8 3v18M16 3v18"/>',
    "Design_Appearance": '<path d="M12 3a9 9 0 1 0 0 18c1.4 0 2-.9 2-2 0-1.4-1.3-1.8-1.3-3 0-1 .8-1.8 1.8-1.8H17a4 4 0 0 0 4-4C21 6.6 17 3 12 3z"/>' + DOT.format(7.5, 11) + DOT.format(10, 7) + DOT.format(15, 7.5),
    "Design_Rib": '<path d="M4 4v16h16"/><path d="M4 9l11 11M4 13l7 7" stroke-width="2.6"/>',
    "Design_Import": '<path d="M14 3H6.5A1.5 1.5 0 0 0 5 4.5v15A1.5 1.5 0 0 0 6.5 21h11a1.5 1.5 0 0 0 1.5-1.5V8z"/><path d="M14 3v5h5"/><path d="M12 10.5v7M9 14.5l3 3 3-3"/>',
    "Design_Export": '<path d="M12 15V4M8 8l4-4 4 4"/><path d="M5 12v6a2 2 0 0 0 2 2h10a2 2 0 0 0 2-2v-6"/>',
    "Std_Undo": '<path d="M9 7l-4 4 4 4"/><path d="M5 11h9a5 5 0 0 1 0 10h-2"/>',
    "Std_Redo": '<path d="M15 7l4 4-4 4"/><path d="M19 11h-9a5 5 0 0 0 0 10h2"/>',
    "Std_ViewFitAll": '<path d="M4 9V4h5M15 4h5v5M20 15v5h-5M9 20H4v-5"/>',
    "MyCAD_Settings": '<circle cx="12" cy="12" r="3"/><path d="M12 2.8v2.4M12 18.8v2.4M2.8 12h2.4M18.8 12h2.4'
    'M5.5 5.5l1.7 1.7M16.8 16.8l1.7 1.7M5.5 18.5l1.7-1.7M16.8 7.2l1.7-1.7"/><circle cx="12" cy="12" r="6.6"/>',
    # Browser, Meldungen (ersetzen FreeCAD-Icons gleichen Zwecks, Zuordnung in Shell.cpp)
    "Tree_Document": '<path d="M6 3h8l4 4v14H6z"/><path d="M14 3v4h4"/>',
    "Tree_Component": '<path d="M12 3l8 4.5v9L12 21l-8-4.5v-9z"/><path d="M4 7.5l8 4.5 8-4.5M12 12v9"/>',
    "Tree_Folder": '<path d="M3 7.5A2 2 0 0 1 5 5.5h4l2 2h8a2 2 0 0 1 2 2V17a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z"/>',
    "Tree_Origin": '<path d="M6 18V5M6 18h13M6 18l9-9"/>' + DOT.format(6, 18),
    "Tree_Axis": '<path d="M5 19L19 5"/><path d="M13 5h6v6"/>',
    "Tree_Plane": '<path d="M3 17l5-10h13l-5 10z"/>',
    "Tree_Point": '<circle cx="12" cy="12" r="3.2" fill="currentColor"/>',
    "Tree_Body": '<path d="M12 3l8 4.5v9L12 21l-8-4.5v-9z" fill="currentColor" fill-opacity="0.18"/><path d="M4 7.5l8 4.5 8-4.5M12 12v9"/>',
    "Tree_Sketch": '<rect x="4" y="4" width="16" height="16" rx="2.5"/><path d="M8 15l3-6 3 4 2-3"/>',
    "Tree_Visible": '<path d="M2.5 12S6 5.5 12 5.5 21.5 12 21.5 12 18 18.5 12 18.5 2.5 12 2.5 12z"/><circle cx="12" cy="12" r="3"/>',
    "Tree_Invisible": '<path d="M2.5 12S6 5.5 12 5.5 21.5 12 21.5 12 18 18.5 12 18.5 2.5 12 2.5 12z"/><path d="M4 4l16 16"/>',
    "Badge_Warning": '<path d="M12 3.5L21.5 20h-19z"/><path d="M12 10v4.5"/>' + DOT.format(12, 17.3),
    "Badge_Info": '<circle cx="12" cy="12" r="9"/><path d="M12 11v6"/>' + DOT.format(12, 7.8),
    "Badge_Error": '<circle cx="12" cy="12" r="9"/><path d="M9 9l6 6M15 9l-6 6"/>',
    "Check": '<path d="M6 12.5l4 4 8-9" stroke="#FFFFFF" stroke-width="2.4"/>',
    "Badge_Dot": '<circle cx="12" cy="12" r="6.5" fill="currentColor" stroke="none"/>',
    # Meldungen (NotificationArea, fest eingefärbt wie die Systemfarben)
    "Notify_Error": '<circle cx="12" cy="12" r="10" fill="#FF3B30" stroke="none"/><path d="M8.5 8.5l7 7M15.5 8.5l-7 7" stroke="#FFFFFF" stroke-width="2.2"/>',
    "Notify_Warning": '<path d="M12 2.5L22.5 20.5h-21z" fill="#FF9500" stroke="#FF9500" stroke-width="1.5"/><path d="M12 9v5" stroke="#FFFFFF" stroke-width="2.2"/><circle cx="12" cy="17.3" r="1.3" fill="#FFFFFF" stroke="none"/>',
    "Notify_Info": '<circle cx="12" cy="12" r="10" fill="#007AFF" stroke="none"/><path d="M12 11v6" stroke="#FFFFFF" stroke-width="2.2"/><circle cx="12" cy="7.6" r="1.3" fill="#FFFFFF" stroke="none"/>',
    "Chevron_Down": '<path d="M6 9l6 6 6-6" stroke="#8E8E93" stroke-width="2.6"/>',
    # Timeline
    "Timeline_Start": '<path d="M7 5v14M17 6l-7 6 7 6"/>',
    "Timeline_Back": '<path d="M15 6l-6 6 6 6"/>',
    "Timeline_Forward": '<path d="M9 6l6 6-6 6"/>',
    "Timeline_End": '<path d="M17 5v14M7 6l7 6-7 6"/>',
    # Erstellen
    "Design_CreateSketch": '<path d="M4 20h4L19 9a2.1 2.1 0 0 0-3-3L5 17z"/><path d="M14 8l3 3"/><path d="M13 20h7"/>',
    "Design_Extrude": '<path d="M3 18l5-3h13l-5 3z"/><path d="M13 12V3M10 6l3-3 3 3"/>',
    "Design_Revolve": '<path d="M12 4v16"' + DASH + '/><path d="M19 12a7 7 0 1 1-2.05-4.95"/><path d="M19 4v4h-4"/>',
    "Design_Hole": '<ellipse cx="12" cy="7" rx="8" ry="3"/><ellipse cx="12" cy="7" rx="3.4" ry="1.3"/>'
                   '<path d="M8.6 7v10M15.4 7v10"/><path d="M8.6 17a3.4 1.3 0 0 0 6.8 0"/>',
    "Design_NewComponent": '<path d="M12 3l8 4.5v9L12 21l-8-4.5v-9z"/><path d="M4 7.5l8 4.5 8-4.5M12 12v9"/>',
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
    "Sketcher_CreateConic": '<path d="M4 18Q10 2 20 18"/><path d="M4 18L12 4l8 14"' + DASH + '/>' + DOT.format(4, 18) + DOT.format(20, 18),
    "Sketcher_Create3PointArc": '<path d="M5 17a8 8 0 0 1 14 0"/>' + DOT.format(5, 17) + DOT.format(12, 9.1) + DOT.format(19, 17),
    "Sketcher_CreateArcOfEllipse": '<path d="M3 15a9 5.5 0 0 1 18 0"/>' + DOT.format(3, 15) + DOT.format(21, 15),
    "Sketcher_CreateArcOfHyperbola": '<path d="M6 4q8 8 0 16M18 4q-8 8 0 16"/>',
    "Sketcher_CreateArcOfParabola": '<path d="M5 4q7 22 14 0"/>' + DOT.format(12, 14.8),
    "Sketcher_Create3PointCircle": '<circle cx="12" cy="12" r="8"/>' + DOT.format(12, 4) + DOT.format(5.1, 16) + DOT.format(18.9, 16),
    "Sketcher_CreateEllipseByCenter": '<ellipse cx="12" cy="12" rx="9" ry="5.5"/>' + DOT.format(12, 12),
    "Sketcher_CreateEllipseBy3Points": '<ellipse cx="12" cy="12" rx="9" ry="5.5"/>' + DOT.format(3, 12) + DOT.format(21, 12) + DOT.format(12, 6.5),
    "Sketcher_CreateRectangle_Center": '<rect x="4" y="6" width="16" height="12" rx="1"/>' + DOT.format(12, 12),
    "Sketcher_CreateOblong": '<rect x="4" y="6" width="16" height="12" rx="4"/>',
    "Sketcher_CreateTriangle": polygon(3, 9),
    "Sketcher_CreateSquare": polygon(4, 8.5),
    "Sketcher_CreatePentagon": polygon(5),
    "Sketcher_CreateHexagon": polygon(6),
    "Sketcher_CreateHeptagon": polygon(7),
    "Sketcher_CreateOctagon": polygon(8),
    "Sketcher_CreateRegularPolygon": polygon(9) + DOT.format(12, 12),
    "Sketcher_CreateArcSlot": '<path d="M4.5 16a8 8 0 0 1 15 0M8.5 16a4 4 0 0 1 7 0"/><path d="M4.5 16a2 2 0 0 0 4 0M15.5 16a2 2 0 0 0 4 0"/>',
    "Sketcher_CreatePeriodicBSpline": '<path d="M12 4c6 0 9 4 7 8s-2 8-7 8-9-3-8-8 2-8 8-8z"/>',
    "Sketcher_CreateBSplineByInterpolation": '<path d="M4 18C8 6 12 22 20 6"/>' + DOT.format(4, 18) + DOT.format(12, 13) + DOT.format(20, 6),
    "Sketcher_CreatePeriodicBSplineByInterpolation": '<path d="M12 4c6 0 9 4 7 8s-2 8-7 8-9-3-8-8 2-8 8-8z"/>' + DOT.format(12, 4) + DOT.format(12, 20),
    "Sketcher_CreateText": '<path d="M6 6h12M12 6v13M9.5 19h5"/>',
    "Sketcher_Projection": '<path d="M3 18l5-3h13l-5 3z"/><path d="M12 3v9M9 9l3 3 3-3"/>',
    "Sketcher_Intersection": '<path d="M3 18l5-3h13l-5 3z"/><path d="M8 5l8 8"/>' + DOT.format(14.5, 16.5),
    "Sketcher_CreatePoint": '<circle cx="12" cy="12" r="2.6" fill="currentColor"/><path d="M12 4v3M12 17v3M4 12h3M17 12h3"/>',
    "Sketcher_CompExternal": '<path d="M3 18l5-3h13l-5 3z"/><path d="M12 3v9M9 9l3 3 3-3"/>',
    "Palette_LookAt": '<circle cx="12" cy="12" r="3"/><path d="M12 3v3M12 18v3M3 12h3M18 12h3"/>',
    "Palette_Section": '<rect x="4" y="4" width="16" height="16" rx="2"/><path d="M4 12h16"' + DASH + '/>',
    "Palette_Grid": '<path d="M4 9h16M4 15h16M9 4v16M15 4v16"/>',
    "Palette_Snap": '<path d="M7 4v7a5 5 0 0 0 10 0V4"/><path d="M7 8h3M14 8h3"/>',
    # Skizze: Ändern
    "Sketcher_CreateFillet": '<path d="M5 19v-8a6 6 0 0 1 6-6h8"/>',
    "Sketcher_CreateChamfer": '<path d="M5 19v-8l6-6h8"/>',
    "Sketcher_Offset": '<rect x="7.5" y="7.5" width="9" height="9" rx="1"/><rect x="3.5" y="3.5" width="17" height="17" rx="3"' + DASH + '/>',
    "Sketcher_Symmetry": '<path d="M12 3v18"' + DASH + '/><path d="M9 7L4 17h5zM15 7l5 10h-5z"/>',
    "Sketcher_RectangularArray": '<rect x="4" y="4" width="6" height="6" rx="1"/><rect x="14" y="4" width="6" height="6" rx="1"/><rect x="4" y="14" width="6" height="6" rx="1"/><rect x="14" y="14" width="6" height="6" rx="1"/>',
    "Sketcher_Rotate": '<circle cx="12" cy="12" r="1.2" fill="currentColor"/>' + "".join(DOT.format(round(12 + 8 * math.sin(a), 2), round(12 - 8 * math.cos(a), 2)) for a in [k * math.pi / 3 for k in range(6)]),
    "Sketcher_Translate": '<path d="M12 3v18M3 12h18M9 6l3-3 3 3M9 18l3 3 3-3M6 9l-3 3 3 3M18 9l3 3-3 3"/>',
    "Sketcher_Scale": '<rect x="4" y="11" width="9" height="9" rx="1"/><path d="M13 11l7-7M14 4h6v6"/>',
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
