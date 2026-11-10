# SPDX-License-Identifier: LGPL-2.1-or-later
"""Idee 7: Keine Angst. Versionen, Wiederherstellen, Vergleich und Varianten eines Designs.

Ablage neben der Design-Datei <Ordner>/<Name>.mycad (ältere: .FCStd):
  versions/<Name>/JJJJMMTT-HHMMSS[ Titel].mycad   Versionen (mit Vorschaubild in der Datei)
  variants/<Name>/<Variante>.mycad               Varianten ("Was wäre wenn")
Aufbewahrung wie Time Machine: alles von den letzten 24 Stunden, danach eine je Stunde für eine Woche, danach eine je
Tag; benannte Versionen bleiben immer. Gelöscht wird nur beim Ausdünnen, nie beim Wiederherstellen.
ponytail: Versionen sind ganze Dateikopien; bei sehr großen Designs den Platz im Blick behalten.
"""
import os
import shutil
import time
import zipfile

import FreeCAD as App

HOUR, DAY = 3600, 86400
EXTENSIONS = (".mycad", ".FCStd")  # MyCAD speichert .mycad; Versionen und Varianten erben die Endung der Hauptdatei


def keep(times, now):
    """Welche Zeitpunkte (Sekunden) die Aufbewahrung behält: jünger als ein Tag alle, bis eine Woche die neueste je
    Stunde, danach die neueste je Tag"""
    kept, seen = set(), set()
    for t in sorted(times, reverse=True):
        age = now - t
        if age < DAY:
            kept.add(t)
            continue
        bucket = ("h", int(t // HOUR)) if age < 7 * DAY else ("d", int(t // DAY))
        if bucket not in seen:
            seen.add(bucket)
            kept.add(t)
    return kept


# --- Ablage ---------------------------------------------------------------------------------------------------------

def _stem(path):
    return os.path.splitext(os.path.basename(path))[0]


def _ext(path):
    return os.path.splitext(path)[1] or EXTENSIONS[0]


def _design_file(base):
    """<base>.mycad, sonst <base>.FCStd, wenn es die gibt"""
    for ext in EXTENSIONS:
        if os.path.exists(base + ext):
            return base + ext
    return base + EXTENSIONS[0]


def versions_folder(path):
    return os.path.join(os.path.dirname(path), "versions", _stem(path))


def variants_folder(path):
    return os.path.join(os.path.dirname(path), "variants", _stem(path))


def main_of(path):
    """Hauptdatei zu einer Variante (variants/<Name>/<Variante>.mycad), sonst path selbst"""
    folder = os.path.dirname(path)
    if os.path.basename(os.path.dirname(folder)) == "variants":
        return _design_file(os.path.join(os.path.dirname(os.path.dirname(folder)), os.path.basename(folder)))
    return path


def is_variant(path):
    return main_of(path) != path


def _version_name(now, title, ext):
    stamp = time.strftime("%Y%m%d-%H%M%S", time.localtime(now))
    title = "".join(c for c in title if c not in '/\\:*?"<>|').strip()
    return stamp + (" " + title if title else "") + ext


def _parse(file):
    """(Zeitpunkt, Titel) aus dem Dateinamen; None für fremde Dateien"""
    ext = os.path.splitext(file)[1]
    base = file[:-len(ext)] if ext in EXTENSIONS else None
    if not base or len(base) < 15:
        return None
    try:
        t = time.mktime(time.strptime(base[:15], "%Y%m%d-%H%M%S"))
    except ValueError:
        return None
    return t, base[16:]


def versions(path):
    """Versionen der Datei, neueste zuerst: [{"path", "time", "title"}]"""
    folder = versions_folder(path)
    out = []
    for f in os.listdir(folder) if os.path.isdir(folder) else []:
        parsed = _parse(f)
        if parsed:
            out.append({"path": os.path.join(folder, f), "time": parsed[0], "title": parsed[1]})
    return sorted(out, key=lambda v: (v["time"], v["path"]), reverse=True)


def thumbnail(path):
    """Vorschaubild (PNG-Bytes) aus der Datei, sonst None"""
    try:
        with zipfile.ZipFile(path) as z:
            return z.read("thumbnails/Thumbnail.png")
    except (KeyError, OSError, zipfile.BadZipFile):
        return None


def snapshot(doc, title="", now=None):
    """Version der gespeicherten Datei anlegen (nach dem Speichern) und ausdünnen; liefert den Pfad. Ohne Titel nur,
    wenn sich die Datei seit der letzten Version geändert hat."""
    path = doc.FileName
    if not path or not os.path.exists(path):
        return None
    now = time.time() if now is None else now
    folder = versions_folder(path)
    os.makedirs(folder, exist_ok=True)
    existing = versions(path)
    if not title and existing and _same(existing[0]["path"], path):
        return None
    target = os.path.join(folder, _version_name(now, title, _ext(path)))
    n = 2
    while os.path.exists(target):  # zwei Versionen in derselben Sekunde
        target = os.path.join(folder, _version_name(now, (title + " " if title else "") + str(n), _ext(path)))
        n += 1
    shutil.copy2(path, target)
    prune(path, now)
    return target


def _same(a, b):
    """gleicher Inhalt, ohne den Speicherzeitpunkt in Document.xml"""
    try:
        with zipfile.ZipFile(a) as za, zipfile.ZipFile(b) as zb:
            names = sorted(za.namelist())
            if names != sorted(zb.namelist()):
                return False
            for n in names:
                x, y = za.read(n), zb.read(n)
                if n == "Document.xml":
                    x, y = _without_dates(x), _without_dates(y)
                if n.startswith("thumbnails/"):
                    continue
                if x != y:
                    return False
            return True
    except (OSError, zipfile.BadZipFile):
        return False


def _without_dates(xml):
    import re
    return re.sub(rb'(LastModifiedDate|LastModifiedBy|Uid|SHA1)"[^/]*?value="[^"]*"', b"", xml)


def prune(path, now=None):
    """unbenannte Versionen nach der Aufbewahrungsregel löschen"""
    now = time.time() if now is None else now
    unnamed = [v for v in versions(path) if not v["title"]]
    kept = keep([v["time"] for v in unnamed], now)
    for v in unnamed:
        if v["time"] not in kept:
            os.remove(v["path"])
        else:
            kept.discard(v["time"])  # gleiche Sekunde: nur eine behalten


# --- Wiederherstellen und Vergleich ---------------------------------------------------------------------------------

def restore(doc, version_path):
    """Design auf den Stand der Version setzen; der Stand davor ist schon eine Version, der neue wird auch eine.
    Liefert das neu geöffnete Dokument."""
    path = doc.FileName
    if doc.isTouched() or getattr(doc, "Modified", False):
        doc.save()
    snapshot(doc)
    App.closeDocument(doc.Name)
    shutil.copy2(version_path, path)
    restored = App.openDocument(path)
    parsed = _parse(os.path.basename(version_path))
    snapshot(restored, "Restored " + time.strftime("%Y-%m-%d %H:%M", time.localtime(parsed[0])) if parsed else "Restored")
    return restored


def _bodies(doc):
    out = {}
    for o in doc.Objects:
        if o.TypeId == "Design::Body" and not o.Shape.isNull():
            s = o.Shape.copy()
            s.Placement = o.getGlobalPlacement()
            out[o.Name] = s
    return out


def _signature(obj):
    """Werte, die ein Feature ausmachen (ohne Ausgaben wie Shape)"""
    skip = {"Shape", "Label2", "Visibility", "ExpressionEngine", "Fixes", "ErrorElements", "Warning", "ElementMaps",
            "ElementHints", "Play", "ThreadDesignation", "Placement", "ShapeMaterial"}
    sig = []
    for p in obj.PropertiesList:
        if p in skip or "Output" in obj.getTypeOfProperty(p):
            continue
        try:
            v = getattr(obj, p)
        except Exception:
            continue
        if isinstance(v, (int, float, str, bool, App.Vector, App.Placement, App.Units.Quantity, list, tuple)):
            sig.append((p, repr(v)))
        elif hasattr(v, "Name"):
            sig.append((p, v.Name))
    return sig


def compare(doc, other_path):
    """Unterschied des Designs zu einer Version oder Variante: hinzugekommen (jetzt da, damals nicht) und entfernt,
    als Formen (global), dazu die Schritte der Timeline: hinzugefügt, entfernt, geändert (Beschriftungen)"""
    import Part
    import Design
    other = App.openDocument(other_path, True)
    try:
        now, then = _bodies(doc), _bodies(other)
        added, removed = [], []
        for name in set(now) | set(then):
            a, b = now.get(name), then.get(name)
            try:
                if a and not b:
                    added.append(a)
                elif b and not a:
                    removed.append(b)
                else:
                    plus, minus = a.cut(b), b.cut(a)
                    if plus.Volume > 1e-6:
                        added.append(plus)
                    if minus.Volume > 1e-6:
                        removed.append(minus)
            except Part.OCCError:
                pass
        steps_now = {o.Name: o for o in Design.timeline(doc)}
        steps_then = {o.Name: o for o in Design.timeline(other)}
        features = {
            "added": [steps_now[n].Label for n in steps_now if n not in steps_then],
            "removed": [steps_then[n].Label for n in steps_then if n not in steps_now],
            "changed": [steps_now[n].Label for n in steps_now
                        if n in steps_then and _signature(steps_now[n]) != _signature(steps_then[n])],
        }
        return {"added": Part.makeCompound(added), "removed": Part.makeCompound(removed),
                "addedVolume": sum(s.Volume for s in added), "removedVolume": sum(s.Volume for s in removed),
                "features": features}
    finally:
        App.closeDocument(other.Name)
        App.setActiveDocument(doc.Name)  # das versteckte Öffnen hatte die Version aktiv gemacht


# --- Varianten ------------------------------------------------------------------------------------------------------

def variants(path):
    """Varianten des Designs (auch von einer Variante aus): [{"name", "path"}]"""
    folder = variants_folder(main_of(path))
    files = sorted(f for f in os.listdir(folder) if os.path.splitext(f)[1] in EXTENSIONS) if os.path.isdir(folder) else []
    return [{"name": os.path.splitext(f)[0], "path": os.path.join(folder, f)} for f in files]


def make_variant(doc, name):
    """Kopie des jetzigen Stands als Variante; liefert ihren Pfad"""
    name = "".join(c for c in name if c not in '/\\:*?"<>|').strip() or "Variant"
    doc.save()
    folder = variants_folder(main_of(doc.FileName))
    os.makedirs(folder, exist_ok=True)
    target = os.path.join(folder, name + _ext(doc.FileName))
    if os.path.exists(target):
        raise ValueError("A variant with this name exists")
    shutil.copy2(doc.FileName, target)
    return target


def switch(doc, path):
    """Zu einer Variante (oder zurück zur Hauptdatei) wechseln: speichert, schließt, öffnet die andere"""
    doc.save()
    App.closeDocument(doc.Name)
    return App.openDocument(path)


def adopt(doc):
    """Variante wird der Hauptstand: der alte Hauptstand wird eine Version, die Variante verschwindet aus der Liste.
    Liefert das geöffnete Hauptdokument."""
    path = doc.FileName
    main = main_of(path)
    if main == path:
        raise ValueError("This is not a variant")
    doc.save()
    App.closeDocument(doc.Name)
    for d in list(App.listDocuments().values()):
        if os.path.normcase(os.path.abspath(d.FileName or "")) == os.path.normcase(os.path.abspath(main)):
            d.save()
            App.closeDocument(d.Name)
    old = App.openDocument(main, True)
    snapshot(old, "Before " + _stem(path))
    App.closeDocument(old.Name)
    shutil.copy2(path, main)
    os.remove(path)
    return App.openDocument(main)
