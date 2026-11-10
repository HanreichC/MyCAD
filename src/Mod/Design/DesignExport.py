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


def write_3mf(path, bodies, quality="normal", colors=None, rotation=None):
    """bodies: Design-Bodies (oder Objekte mit Shape und Label); colors: {Name: (r, g, b)} überschreibt die Appearance.
    Koordinaten global (Komponenten mit eigener Lage stehen richtig im Slicer); rotation dreht alles danach
    (Druckrichtung nach +Z)."""
    colors = colors or {}
    palette, objects, build = [], [], []
    for index, body in enumerate(bodies):
        shape = body.Shape.copy()
        if hasattr(body, "getGlobalPlacement"):
            shape.Placement = body.getGlobalPlacement()
        if rotation is not None:
            shape.Placement = App.Placement(App.Vector(), rotation).multiply(shape.Placement)
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


# --- Drucken: Slicer finden und mit dem 3MF öffnen (Idee 5) -----------------------------------------------------

# (Name, Programmnamen im PATH, Flatpak-ID, Anfänge des AppImage-Namens, Windows-Pfad unter Programme)
SLICERS = [
    ("OrcaSlicer", ["orca-slicer", "OrcaSlicer", "orcaslicer"], "io.github.softfever.OrcaSlicer", ["OrcaSlicer"],
     "OrcaSlicer/orca-slicer.exe"),
    ("Bambu Studio", ["bambu-studio", "BambuStudio"], "com.bambulab.BambuStudio", ["Bambu_Studio", "BambuStudio"],
     "Bambu Studio/bambu-studio.exe"),
    ("PrusaSlicer", ["prusa-slicer", "PrusaSlicer", "prusaslicer"], "com.prusa3d.PrusaSlicer", ["PrusaSlicer"],
     "Prusa3D/PrusaSlicer/prusa-slicer.exe"),
    ("UltiMaker Cura", ["cura", "UltiMaker-Cura", "ultimaker-cura", "Ultimaker-Cura"], "com.ultimaker.cura",
     ["UltiMaker-Cura", "Ultimaker-Cura", "Ultimaker_Cura", "Cura"], "UltiMaker Cura/UltiMaker-Cura.exe"),
]
FILE_FORWARDING = "--file-forwarding"  # Flatpak: die Datei kommt über das Dokumenten-Portal in die Sandbox


def find_slicers(environ=None, home=None):
    """Installierte Slicer als [(Name, Befehl als Liste)]: PATH, Flatpak, AppImage in ~/Applications, Programme"""
    import os
    import shutil
    environ = os.environ if environ is None else environ
    home = home or os.path.expanduser("~")
    path = environ.get("PATH", "")
    flatpaks = set()
    flatpak = shutil.which("flatpak", path=path)
    if flatpak:
        for root in ("/var/lib/flatpak/app", os.path.join(home, ".local/share/flatpak/app")):
            if os.path.isdir(root):
                flatpaks.update(os.listdir(root))
    apps = os.path.join(home, "Applications")
    images = sorted(os.listdir(apps)) if os.path.isdir(apps) else []
    found = []
    for name, programs, flatpak_id, image_names, windows in SLICERS:
        command = next(([p] for p in (shutil.which(n, path=path) for n in programs) if p), None)
        if not command and flatpak_id in flatpaks:
            command = [flatpak, "run", FILE_FORWARDING, flatpak_id]
        if not command:
            hit = next((f for f in images if f.lower().endswith(".appimage")
                        and any(f.lower().startswith(i.lower()) for i in image_names)), None)
            command = [os.path.join(apps, hit)] if hit else None
        if not command:
            for base in (environ.get("ProgramFiles"), environ.get("ProgramW6432")):
                if base and os.path.isfile(os.path.join(base, windows)):
                    command = [os.path.join(base, windows)]
                    break
        if command:
            found.append((name, command))
    return found


# Variablen, die MyCADs AppImage (AppRun) für sich setzt: der Slicer soll sie nicht erben
_OWN_PATHS = ("LD_LIBRARY_PATH", "PYTHONPATH", "QT_PLUGIN_PATH", "QT_QPA_PLATFORM_PLUGIN_PATH", "QML2_IMPORT_PATH",
              "GDK_PIXBUF_MODULE_FILE", "GIO_MODULE_DIR", "GSETTINGS_SCHEMA_DIR")


def slicer_environment(environ=None):
    """Umgebung für den Slicer: ohne die Bibliotheks- und Python-Pfade aus MyCADs AppImage, mit der Sprache des
    Desktops (AppRun hat sie für MyCAD auf C gestellt und in MYCAD_HOST_* gemerkt)"""
    import os
    env = dict(os.environ if environ is None else environ)
    appdir = env.get("APPDIR")
    if appdir:
        inside = lambda p: os.path.abspath(p).startswith(os.path.abspath(appdir) + os.sep)  # noqa: E731
        for key in _OWN_PATHS:
            if key in env:
                rest = [p for p in env[key].split(os.pathsep) if p and not inside(p)]
                if rest:
                    env[key] = os.pathsep.join(rest)
                else:
                    del env[key]
        if "PYTHONHOME" in env and inside(env["PYTHONHOME"]):
            del env["PYTHONHOME"]
    for key in ("LANG", "LC_ALL"):
        if "MYCAD_HOST_" + key in env:
            host = env.pop("MYCAD_HOST_" + key)
            if host:
                env[key] = host
            else:
                env.pop(key, None)
    return env


def slicer_arguments(command, path):
    """Befehl mit Datei; Flatpak bekommt sie über das Portal (@@ … @@), sonst sähe es die Datei in der Sandbox nicht"""
    return list(command) + (["@@", path, "@@"] if FILE_FORWARDING in command else [path])


def print_rotation(up):
    """Drehung, die die Druckrichtung up auf +Z legt"""
    return App.Rotation(up, App.Vector(0, 0, 1))


def open_in_slicer(bodies, folder, command, up=None, quality="normal"):
    """3MF der Bodies (Druckrichtung nach oben) in folder schreiben und den Slicer damit starten; liefert den Pfad"""
    import os
    import re
    import subprocess
    name = re.sub(r"[^\w.-]+", "_", bodies[0].Document.Label if bodies else "design") or "design"
    path = os.path.join(folder, name + ".3mf")
    write_3mf(path, bodies, quality, rotation=print_rotation(up) if up is not None else None)
    subprocess.Popen(slicer_arguments(command, path), env=slicer_environment(), start_new_session=True)
    return path
