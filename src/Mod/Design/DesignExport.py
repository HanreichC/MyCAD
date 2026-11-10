# SPDX-License-Identifier: LGPL-2.1-or-later
"""3MF für den 3D-Druck: ein Objekt je Body mit Namen und Farbe (3MF-Kernspezifikation, <basematerials>).

Slicer (PrusaSlicer, OrcaSlicer, Bambu Studio, Cura) übernehmen so Teile, Namen und Farben. Die Auflösung legt fest,
wie fein gekrümmte Flächen in Dreiecke zerlegt werden.
"""
import zipfile
from xml.sax.saxutils import escape

import FreeCAD as App

# (größte Abweichung in mm, größter Winkel zwischen Nachbardreiecken in Grad)
QUALITY = {"coarse": (0.1, 30), "normal": (0.02, 15), "fine": (0.005, 5)}

CONTENT_TYPES = """<?xml version="1.0" encoding="UTF-8"?>
<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">
 <Default Extension="rels" ContentType="application/vnd.openxmlformats-package.relationships+xml"/>
 <Default Extension="model" ContentType="application/vnd.ms-package.3dmanufacturing-3dmodel+xml"/>
</Types>
"""
RELS = """<?xml version="1.0" encoding="UTF-8"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
 <Relationship Target="/3D/3dmodel.model" Id="rel0" Type="http://schemas.microsoft.com/3dmanufacturing/2013/01/3dmodel"/>
</Relationships>
"""


def body_color(body):
    """Farbe der Appearance (nur mit Oberfläche bekannt), sonst None"""
    if not App.GuiUp or not getattr(body, "ViewObject", None):
        return None
    try:
        r, g, b = body.ViewObject.ShapeAppearance[0].DiffuseColor[:3]
        return (r, g, b)
    except (AttributeError, IndexError):
        return None


def hex_color(rgb):
    return "#%02X%02X%02X" % tuple(max(0, min(255, round(c * 255))) for c in rgb[:3])


def triangles(shape, quality):
    import MeshPart
    deviation, angle = QUALITY.get(quality, QUALITY["normal"])
    mesh = MeshPart.meshFromShape(Shape=shape, LinearDeflection=deviation, AngularDeflection=angle * 3.14159265 / 180,
                                  Relative=False)
    return mesh.Topology


def write_3mf(path, bodies, quality="normal", colors=None):
    """bodies: Design-Bodies (oder Objekte mit Shape und Label); colors: {Name: (r, g, b)} überschreibt die Appearance.
    Koordinaten global (Komponenten mit eigener Lage stehen richtig im Slicer)."""
    colors = colors or {}
    palette, objects, build = [], [], []
    for index, body in enumerate(bodies):
        shape = body.Shape.copy()
        if hasattr(body, "getGlobalPlacement"):
            shape.Placement = body.getGlobalPlacement()
        points, facets = triangles(shape, quality)
        rgb = colors.get(body.Name) or body_color(body) or (0.6, 0.6, 0.62)
        color = hex_color(rgb)
        if color not in palette:
            palette.append(color)
        oid = index + 2  # 1 = Farbtabelle
        vertices = "".join('<vertex x="%.6f" y="%.6f" z="%.6f"/>' % (p.x, p.y, p.z) for p in points)
        tris = "".join('<triangle v1="%d" v2="%d" v3="%d"/>' % t for t in facets)
        objects.append('  <object id="%d" type="model" name="%s" pid="1" pindex="%d">\n   <mesh><vertices>%s</vertices>'
                       '<triangles>%s</triangles></mesh>\n  </object>\n'
                       % (oid, escape(body.Label, {'"': "&quot;"}), palette.index(color), vertices, tris))
        build.append('  <item objectid="%d"/>\n' % oid)
    materials = "".join('   <base name="%s" displaycolor="%s"/>\n' % (c, c) for c in palette)
    model = ('<?xml version="1.0" encoding="UTF-8"?>\n'
             '<model unit="millimeter" xml:lang="en-US" xmlns="http://schemas.microsoft.com/3dmanufacturing/core/2015/02">\n'
             ' <metadata name="Application">MyCAD</metadata>\n'
             ' <resources>\n  <basematerials id="1">\n' + materials + '  </basematerials>\n' + "".join(objects)
             + ' </resources>\n <build>\n' + "".join(build) + ' </build>\n</model>\n')
    with zipfile.ZipFile(path, "w", zipfile.ZIP_DEFLATED) as z:
        z.writestr("[Content_Types].xml", CONTENT_TYPES)
        z.writestr("_rels/.rels", RELS)
        z.writestr("3D/3dmodel.model", model)
    return len(bodies)
