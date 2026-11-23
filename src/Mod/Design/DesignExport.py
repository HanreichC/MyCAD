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


def step_ascii(text):
    """U6: Zeichen außerhalb von ASCII in einer STEP-Datei nach ISO 10303-21 kodieren (\\X2\\…\\X0\\ für UCS-2,
    \\X4\\…\\X0\\ darüber). OCCT schreibt Namen roh als UTF-8 (FreeCAD#33914, Fix nur in OCCT#1742); andere
    CAD-Programme zeigen dann Zeichensalat oder öffnen die Datei nicht. Außerhalb von Zeichenketten steht in STEP nur
    ASCII, darum genügt es, jede Folge von Nicht-ASCII-Zeichen zu ersetzen."""
    out, run = [], []

    def flush():
        if run:
            wide = any(ord(c) > 0xFFFF for c in run)
            out.append(("\\X4\\" if wide else "\\X2\\") + "".join(("%08X" if wide else "%04X") % ord(c) for c in run)
                       + "\\X0\\")
            run.clear()

    for c in text:
        if ord(c) < 128:
            flush()
            out.append(c)
        else:
            run.append(c)
    flush()
    return "".join(out)


def _in_world(objects):
    """U7 (FreeCAD#25150): der Export schreibt keine Lage, weder die übergeordneter Komponenten noch die eigene; ein
    Körper in einer verschobenen oder gedrehten Komponente käme an seiner lokalen Stelle an. Solche Körper gehen als
    vorübergehende Kopie hinaus, deren Geometrie selbst in Weltlage steht (starr kopiert, Zylinder bleiben Zylinder),
    mit Name und Aussehen des Originals; Liste (zu exportieren, wieder zu löschen)"""
    out, temps = [], []
    for o in objects:
        world = o.getGlobalPlacement() if hasattr(o, "getGlobalPlacement") else o.Placement
        if world.isIdentity(1e-12):
            out.append(o)
            continue
        t = o.Document.addObject("Part::Feature", "StepExport")
        shape = o.Shape.copy()
        shape.Placement = App.Placement()
        shape.transformShape(world.toMatrix(), True)  # copy: neue Geometrie statt einer Lage, die verloren ginge
        t.Shape = shape
        t.Label = o.Label
        if App.GuiUp and getattr(o, "ViewObject", None) and getattr(t, "ViewObject", None):
            t.ViewObject.ShapeAppearance = o.ViewObject.ShapeAppearance
        temps.append(t)
        out.append(t)
    return out, temps


def write_step(path, objects):
    """STEP mit Farben und Struktur (ImportGui, ohne Oberfläche Import), Körper in Weltlage (_in_world), danach reines
    ASCII (step_ascii)"""
    try:
        import ImportGui as step
    except ImportError:
        import Import as step
    params = App.ParamGet("User parameter:BaseApp/Preferences/Document")
    duplicates = params.GetBool("DuplicateLabels", False)
    params.SetBool("DuplicateLabels", True)  # die Kopie trägt den Namen des Originals, nicht "Gehäuse001"
    try:
        world, temps = _in_world(objects)
        try:
            step.export(world, path)
        finally:
            for t in temps:
                t.Document.removeObject(t.Name)
    finally:
        params.SetBool("DuplicateLabels", duplicates)
    with open(path, "rb") as f:
        data = f.read()
    try:
        text = data.decode("utf-8")
    except UnicodeDecodeError:
        return  # nicht UTF-8: so lassen, wie OCCT es schrieb
    if not text.isascii():
        with open(path, "w", encoding="ascii", newline="") as f:
            f.write(step_ascii(text))


def body_color(body):
    """Farbe der Appearance (nur mit Oberfläche bekannt), sonst None"""
    colors = face_colors(body)
    return colors[0] if colors else None


def face_colors(body):
    """Farbe je Fläche (Appearance, nur mit Oberfläche bekannt; eine Farbe für alle, wenn nur eine gesetzt ist)"""
    if not App.GuiUp or not getattr(body, "ViewObject", None):
        return []
    try:
        return [tuple(m.DiffuseColor[:3]) for m in body.ViewObject.ShapeAppearance]
    except AttributeError:
        return []


def hex_color(rgb):
    return "#%02X%02X%02X" % tuple(max(0, min(255, round(c * 255))) for c in rgb[:3])


def triangles(shape, quality):
    """(Punkte, Dreiecke, Fläche je Dreieck); die Flächennummer zählt wie shape.Faces"""
    import MeshPart
    deviation, angle = QUALITY.get(quality, QUALITY["normal"])
    mesh = MeshPart.meshFromShape(Shape=shape, LinearDeflection=deviation, AngularDeflection=angle * 3.14159265 / 180,
                                  Relative=False, Segments=True)
    points, facets = mesh.Topology
    face = [0] * len(facets)
    for index in range(mesh.countSegments()):
        for facet in mesh.getSegment(index):
            face[facet] = index
    return points, facets, face


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
        points, facets, face = triangles(shape, quality)
        # 12.8 Farbe je Fläche: jedes Dreieck bekommt die seiner Fläche (Slicer übernehmen sie als Filament-Vorschlag)
        rgbs = [colors[body.Name]] if body.Name in colors else face_colors(body) or [(0.6, 0.6, 0.62)]
        if len(rgbs) != len(shape.Faces):
            rgbs = rgbs[:1]  # Appearance passt nicht (mehr) zu den Flächen: die erste für alle
        index_of = []
        for rgb in rgbs:
            color = hex_color(rgb)
            if color not in palette:
                palette.append(color)
            index_of.append(palette.index(color))
        oid = index + 2  # 1 = Farbtabelle
        vertices = "".join('<vertex x="%.6f" y="%.6f" z="%.6f"/>' % (p.x, p.y, p.z) for p in points)
        if len(set(index_of)) > 1:
            tris = "".join('<triangle v1="%d" v2="%d" v3="%d" p1="%d"/>' % (t + (index_of[f],)) for t, f in zip(facets, face))
        else:
            tris = "".join('<triangle v1="%d" v2="%d" v3="%d"/>' % t for t in facets)
        objects.append('  <object id="%d" type="model" name="%s" pid="1" pindex="%d">\n   <mesh><vertices>%s</vertices>'
                       '<triangles>%s</triangles></mesh>\n  </object>\n'
                       % (oid, escape(body.Label, {'"': "&quot;"}), index_of[0], vertices, tris))
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


# --- Teile-Bibliothek (12.7): Körper aus einem anderen Design ------------------------------------------------------

def design_bodies(path):
    """[(Name, Form)] der sichtbaren Körper eines gespeicherten Designs (.mycad/.FCStd), in Weltkoordinaten. Das Design
    wird dafür unsichtbar geöffnet und wieder geschlossen; war es schon offen, bleibt es so."""
    import os
    before = {d.FileName: d for d in App.listDocuments().values()}
    target = os.path.abspath(path)
    doc = next((d for f, d in before.items() if f and os.path.abspath(f) == target), None)
    opened = doc is None
    active = App.ActiveDocument  # Öffnen macht das andere Design aktiv, Schließen ließe keins zurück
    if opened:
        doc = App.openDocument(path, hidden=True)
    try:  # nicht neu rechnen: die gespeicherten Formen gelten (ein fremder Code-Schritt liefe sonst nicht an)
        found = []
        for body in doc.Objects:
            if body.TypeId == "Design::Body" and body.Visibility and not body.Shape.isNull():
                shape = body.Shape.copy()
                if hasattr(body, "getGlobalPlacement"):
                    shape.Placement = body.getGlobalPlacement()
                found.append((body.Label, shape))
        return found
    finally:
        if opened:
            App.closeDocument(doc.Name)
        if active is not None:
            App.setActiveDocument(active.Name)


def design_bodies_to_brep(path, folder):
    """wie design_bodies, je Körper eine BREP-Datei in folder; liefert "Name\tDatei" je Zeile (für die Oberfläche)"""
    import os
    lines = []
    for i, (label, shape) in enumerate(design_bodies(path)):
        brep = os.path.join(folder, "mycad-part-%d-%d.brep" % (os.getpid(), i))
        shape.exportBrep(brep)
        lines.append(label.replace("\t", " ").replace("\n", " ") + "\t" + brep)
    return "\n".join(lines)


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
# MyCAD im Container (Starter aus install.sh): Programmordner des Rechners liegen nur lesend unter dieser Wurzel, starten
# geht über den Flatpak-Session-Helper des Rechners (host_spawn)
HOST_ROOT = "MYCAD_HOST_ROOT"


def find_slicers(environ=None, home=None):
    """Installierte Slicer als [(Name, Befehl als Liste)]: PATH, Flatpak, AppImage in ~/Applications, Programme.
    Im Container die des Rechners (unter HOST_ROOT eingebunden), mit Pfaden, wie der Rechner sie sieht"""
    import os
    import shutil
    environ = os.environ if environ is None else environ
    home = home or os.path.expanduser("~")
    host = environ.get(HOST_ROOT, "")
    path = os.pathsep.join(host + d for d in ("/usr/local/bin", "/usr/bin")) if host else environ.get("PATH", "")
    flatpaks = set()
    flatpak = shutil.which("flatpak", path=path)
    if flatpak:
        for root in (host + "/var/lib/flatpak/app", os.path.join(home, ".local/share/flatpak/app")):
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
            found.append((name, [c[len(host):] if host and c.startswith(host + "/") else c for c in command]))
    return found


def host_spawn(argv, environ=None):
    """Programm auf dem Rechner starten (aus dem Container): org.freedesktop.Flatpak.Development.HostCommand über die
    Sitzungs-D-Bus, wie flatpak-spawn --host. Argumente als Byte-Listen, so stören Leerzeichen und Anführungszeichen nicht"""
    import os
    import subprocess

    def ay(text):
        return "[" + ", ".join(str(b) for b in os.fsencode(text) + b"\0") + "]"
    done = subprocess.run(["gdbus", "call", "--session", "--dest", "org.freedesktop.Flatpak",
                           "--object-path", "/org/freedesktop/Flatpak/Development",
                           "--method", "org.freedesktop.Flatpak.Development.HostCommand",
                           "@ay " + ay(os.path.expanduser("~")), "@aay [" + ", ".join(ay(a) for a in argv) + "]",
                           "@a{uh} {}", "@a{ss} {}", "uint32 0"],
                          capture_output=True, text=True, env=environ)
    if done.returncode:
        raise RuntimeError(done.stderr.strip() or "flatpak session helper not reachable")


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
    if command is None:  # Flatpak: die Oberfläche öffnet die Datei über das Portal, das System fragt nach dem Slicer
        return path
    if os.environ.get(HOST_ROOT):
        host_spawn(slicer_arguments(command, path))  # liegt in ~, das der Rechner unter demselben Pfad sieht
    else:
        subprocess.Popen(slicer_arguments(command, path), env=slicer_environment(), start_new_session=True)
    return path
