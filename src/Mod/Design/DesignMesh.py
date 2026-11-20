# SPDX-License-Identifier: LGPL-2.1-or-later
"""Mesh-Brücke (Plan 12.1): STL, 3MF und OBJ werden zu einem Körper, mit dem man arbeiten kann. Gleiche Ebenen werden
zu je einer Fläche (fangen, messen, skizzieren wie an jedem Körper), Bohrungen zu echten Zylindern mit Kreisen als Rand
(Mittelpunkt, Durchmesser, Passung, Screw Here). Alles Zusammenfassen geschieht am Mesh, bevor OCCT Flächen sieht:
OCCT vernäht dann nur noch wenige Flächen (das Vernähen Tausender Dreiecke wuchs überproportional, 30 000 brauchten
über zwei Minuten). Zapfen, Rundungen und Freiformen bleiben aus Dreiecken."""
import math

MAX_TRIANGLES = 200000  # Python-Schleifen laufen linear: 100 000 Dreiecke einer Bohrplatte in unter 1 s
# ponytail: einzeln bleibende Dreiecke (Freiform) vernäht OCCT mit rund 0,45 ms je Stück (50 000 in 19 s); darüber
# lieber eine klare Meldung als eine stehende Oberfläche. Größer ginge erst mit Vereinfachen (Mesh.decimate) davor
MAX_LOOSE = 40000


class MeshError(Exception):
    """Fehler mit einem Satz für den Benutzer; %1, %2 … füllt die Oberfläche nach dem Übersetzen (key(): Satz und Werte)"""

    def __init__(self, text, *values):
        super().__init__(text, *values)
        self.text, self.values = text, [str(v) for v in values]

    def __str__(self):
        out = self.text
        for i, v in enumerate(self.values, 1):
            out = out.replace("%%%d" % i, v)
        return out

    def key(self):
        return "\x1f".join([self.text] + self.values)


def _axis(normals):
    """Achse eines Zylinders aus den Normalen seiner Facetten: alle stehen senkrecht auf ihr"""
    ref = normals[0]
    total = None
    for n in normals[1:]:
        c = ref.cross(n)
        if c.Length < 1e-6:
            continue
        if total is not None and total.dot(c) < 0:
            c = -c
        total = c if total is None else total + c
    if total is None or total.Length < 1e-9:
        return None
    total.normalize()
    return total


def _circle(points):
    """Kreis durch Punkte in der Ebene (Kasa-Fit): Mittelpunkt (u, v), Radius; None, wenn sie auf einer Geraden liegen"""
    sx = sy = sxx = syy = sxy = sz = sxz = syz = 0.0
    for u, v in points:
        z = u * u + v * v
        sx += u; sy += v; sxx += u * u; syy += v * v; sxy += u * v; sz += z; sxz += u * z; syz += v * z
    # Kreis u² + v² = a u + b v + c, kleinste Quadrate: m · (a, b, c) = r
    m = [[sxx, sxy, sx], [sxy, syy, sy], [sx, sy, len(points)]]
    r = [sxz, syz, sz]

    def det(q):
        return (q[0][0] * (q[1][1] * q[2][2] - q[1][2] * q[2][1]) - q[0][1] * (q[1][0] * q[2][2] - q[1][2] * q[2][0])
                + q[0][2] * (q[1][0] * q[2][1] - q[1][1] * q[2][0]))
    d = det(m)
    if abs(d) < 1e-9:
        return None
    a, b, c = (det([[r[i] if j == k else m[i][j] for j in range(3)] for i in range(3)]) / d for k in range(3))
    cu, cv = a / 2, b / 2
    rr = c + cu * cu + cv * cv
    return (cu, cv, math.sqrt(rr)) if rr > 0 else None


def _find(parent, i):
    while parent[i] != i:
        parent[i] = parent[parent[i]]
        i = parent[i]
    return i


def _loops(edges):
    """gerichtete Randkanten (a, b) zu geschlossenen Ketten von Punkt-Indizes"""
    following = {}
    for a, b in edges:
        following.setdefault(a, []).append(b)
    loops = []
    while following:
        start = next(iter(following))
        loop, at = [], start
        while True:
            loop.append(at)
            ends = following.get(at)
            if not ends:
                return None  # offen: kein sauberer Rand
            nxt = ends.pop()
            if not ends:
                del following[at]
            at = nxt
            if at == start:
                break
        loops.append(loop)
    return loops


class _Mesh:
    """Dreiecke mit Nachbarschaft, nach außen gerichtet"""

    def __init__(self, mesh):
        import FreeCAD as App
        V = App.Vector
        points, tris = mesh.Topology
        self.p = [V(q) for q in points]
        self.t = [tuple(x) for x in tris]
        volume = sum(self.p[a].dot(self.p[b].cross(self.p[c])) for a, b, c in self.t)
        if volume < 0:  # nach innen gerichtet: umdrehen
            self.t = [(a, c, b) for a, b, c in self.t]
        self.n = []
        for a, b, c in self.t:
            n = (self.p[b] - self.p[a]).cross(self.p[c] - self.p[a])
            self.n.append(n.normalize() if n.Length > 1e-15 else n)
        self.side = {}  # gerichtete Kante -> Dreieck
        for i, (a, b, c) in enumerate(self.t):
            for e in ((a, b), (b, c), (c, a)):
                self.side[e] = i

    def other(self, a, b):
        """Dreieck auf der anderen Seite der Kante a -> b"""
        return self.side.get((b, a))


def _patches(m):
    """Ebenen: zusammenhängende Dreiecke mit gleicher Normale; Rückgabe Patch-Nummer je Dreieck"""
    parent = list(range(len(m.t)))
    for (a, b), i in m.side.items():
        j = m.other(a, b)
        if j is not None and j > i and m.n[i].getAngle(m.n[j]) < 1e-4:
            parent[_find(parent, i)] = _find(parent, j)
    return [_find(parent, i) for i in range(len(m.t))]


def _boundary(m, members):
    """gerichtete Randkanten einer Menge von Dreiecken"""
    inside = set(members)
    out = []
    for i in members:
        a, b, c = m.t[i]
        for e in ((a, b), (b, c), (c, a)):
            if m.other(*e) not in inside:
                out.append(e)
    return out


def _holes(m, patch, members):
    """Bohrungen: gekrümmte Bereiche (Ebenen mit leichtem Knick zueinander), die einen vollen Kreis bilden, nach innen
    zeigen und an beiden Enden genau eine Ebene treffen. Rückgabe [(Dreiecke, Mittelpunkt unten, Achse, Radius, Länge,
    {Rand-Punkte: Höhe})]"""
    import FreeCAD as App
    V = App.Vector
    parent = {k: k for k in members}
    for (a, b), i in m.side.items():
        j = m.other(a, b)
        if j is None or patch[i] == patch[j]:
            continue
        bend = m.n[i].getAngle(m.n[j])
        if 1e-3 < bend < math.radians(30):
            parent[_find(parent, patch[i])] = _find(parent, patch[j])
    regions = {}
    for k in members:
        regions.setdefault(_find(parent, k), []).append(k)
    size = max((p - m.p[0]).Length for p in m.p) + 1e-9
    found = []
    for keys in regions.values():
        if len(keys) < 6:
            continue
        tris = [i for k in keys for i in members[k]]
        axis = _axis([m.n[members[k][0]] for k in keys])
        if axis is None:
            continue
        idx = {v for i in tris for v in m.t[i]}
        u = axis.cross(V(1, 0, 0) if abs(axis.x) < 0.9 else V(0, 1, 0))
        u.normalize()
        w = axis.cross(u)
        flat = {v: (m.p[v].dot(u), m.p[v].dot(w)) for v in idx}
        fit = _circle(list(flat.values()))
        if not fit:
            continue
        cu, cv, _ = fit
        dist = [math.hypot(a - cu, b - cv) for a, b in flat.values()]
        radius = max(dist)  # die Ecken der Facetten liegen auf dem echten Kreis
        if radius > size or radius - min(dist) > 0.02 * radius + 0.01:
            continue  # kein Zylinder (Kegel, Kugel, Freiform)
        angles = sorted(math.atan2(b - cv, a - cu) for a, b in flat.values())
        gaps = [y - x for x, y in zip(angles, angles[1:])] + [angles[0] + 2 * math.pi - angles[-1]]
        if max(gaps) > math.radians(45):
            continue  # nur ein Teil des Umfangs (Rundung an einer Kante)
        heights = {v: m.p[v].dot(axis) for v in idx}
        lo, hi = min(heights.values()), max(heights.values())
        base = u * cu + w * cv + axis * lo
        inward = 0
        for i in tris:
            c = (m.p[m.t[i][0]] + m.p[m.t[i][1]] + m.p[m.t[i][2]]) * (1 / 3)
            inward += m.n[i].dot(c - (base + axis * (c - base).dot(axis))) < 0
        if inward * 2 <= len(tris) or hi - lo < 1e-3:
            continue  # Zapfen: bleibt aus Dreiecken
        loops = _loops(_boundary(m, tris))
        # jedes Ende: flach (eine Höhe) und ganz an einer einzigen Ebene, sonst lieber Dreiecke behalten
        if not loops or len(loops) != 2:
            continue
        ends = {}
        for loop in loops:
            h = [heights[v] for v in loop]
            neighbours = {patch[m.other(loop[k], loop[(k + 1) % len(loop)])] for k in range(len(loop))}
            if max(h) - min(h) > 1e-3 or len(neighbours) != 1:
                break
            ends[frozenset(loop)] = (lo if abs(h[0] - lo) < abs(h[0] - hi) else hi) - lo
        else:
            found.append((tris, base, axis, radius, hi - lo, ends))
    return found


def solid(mesh):
    """Körper aus einem geschlossenen Mesh: Ebenen als eine Fläche, Bohrungen als echte Zylinder"""
    import FreeCAD as App
    import Part
    V = App.Vector
    if mesh.CountFacets == 0:
        raise MeshError("The file contains no triangles.")
    if mesh.CountFacets > MAX_TRIANGLES:
        raise MeshError("The mesh has %1 triangles; MyCAD turns meshes of up to %2 into bodies. Reduce it in your "
                        "slicer or mesh tool first.", mesh.CountFacets, MAX_TRIANGLES)
    mesh = mesh.copy()
    mesh.harmonizeNormals()
    if not mesh.isSolid():
        raise MeshError("The mesh is not closed, so it cannot become a body. Repair it in your slicer or mesh tool.")
    m = _Mesh(mesh)
    patch = _patches(m)
    members = {}
    for i, k in enumerate(patch):
        members.setdefault(k, []).append(i)
    loose = sum(1 for tris in members.values() if len(tris) == 1)  # Freiform: bleibt Dreieck für Dreieck
    if loose > MAX_LOOSE:
        raise MeshError("The mesh is mostly free-form (%1 single triangles); MyCAD turns meshes with up to %2 into "
                        "bodies. Reduce it in your slicer or mesh tool first.", loose, MAX_LOOSE)
    faces, circles, gone = [], {}, set()
    for tris, base, axis, radius, length, ends in _holes(m, patch, members):
        cylinder = Part.makeCylinder(radius, length, base, axis)
        faces.append([f for f in cylinder.Faces if f.Surface.TypeId == "Part::GeomCylinder"][0])
        rims = [e for e in cylinder.Edges if e.Curve.TypeId == "Part::GeomCircle"]
        for loop, height in ends.items():
            circles[loop] = min(rims, key=lambda e: abs((e.Curve.Center - base).dot(axis) - height))
        gone.update(patch[i] for i in tris)
    for k, tris in members.items():
        if k in gone:
            continue
        if len(tris) == 1:
            if m.n[tris[0]].Length > 0.5:  # entartete Dreiecke (Fläche 0) überspringen: ihre Kanten fallen zusammen
                faces.append(Part.Face(Part.makePolygon([m.p[v] for v in m.t[tris[0]]] + [m.p[m.t[tris[0]][0]]])))
            continue
        loops = _loops(_boundary(m, tris))
        if loops is None:
            raise MeshError("The mesh could not be turned into a body.")
        wires = [Part.Wire(circles[frozenset(loop)]) if frozenset(loop) in circles
                 else Part.makePolygon([m.p[v] for v in loop] + [m.p[loop[0]]]) for loop in loops]
        faces.append(Part.makeFace(wires, "Part::FaceMakerBullseye") if len(wires) > 1 else Part.Face(wires[0]))
    shape = Part.makeCompound(faces)
    shape.sewShape(1e-4)
    try:
        body = Part.Solid(shape.Shells[0]) if len(shape.Shells) == 1 else None
    except Part.OCCError:
        body = None
    if body is None or not body.isClosed():
        raise MeshError("The mesh could not be turned into a body.")
    if body.Volume < 0:
        body.reverse()
    if not body.isValid() or body.Volume <= 0:
        raise MeshError("The mesh could not be turned into a body.")
    return body


def read(path):
    """Mesh aus STL, 3MF oder OBJ (Millimeter)"""
    import os
    import Mesh
    if not os.path.isfile(path):
        raise MeshError("The file could not be read: %1", path)
    try:
        return Mesh.Mesh(path)
    except Exception as e:  # Mesh meldet Lesefehler als Base.FreeCADError
        raise MeshError("The file could not be read: %1", e)
