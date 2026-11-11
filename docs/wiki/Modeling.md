# Modeling

## The workflow

As in Fusion 360: a **sketch** on a plane or face, click a profile, **Extrude** or **Revolve**, then keep going with
tools like Fillet, Hole and Pattern. Every step lands in the **timeline**.

A design is made of **bodies** in **components**. The root component is the design itself; further components are for
[assemblies](Assemblies).

## Sketches

- **Create Sketch** (S), then click a plane or flat face. The camera looks straight at it.
- Every closed region is its own profile. Two circles inside each other give a ring and a disc.
- **Dimension** works out from the selection what to measure (length, distance, radius, angle). Every size field takes
  formulas and parameter names.
- **Esc** puts the active tool away, **Finish Sketch** takes you back to the model.
- Edges of the model can be projected into the sketch and reused.

## Tools at a glance

| Section | Tools |
|---|---|
| CREATE | Sketch · Extrude · Revolve · Sweep · Loft · Rib · Web · Emboss · Box · Cylinder · Sphere · Torus · Coil · Hole · Screw Here · Thread · Pattern · Mirror |
| MODIFY | Press Pull · Fit · Remove Face · Replace Face · Split Face · Fillet · Chamfer · Shell · Draft · Combine · Split Body · Move · Align · Scale |
| CONSTRUCT | Offset Plane · Plane at Angle · Midplane · Plane · Axis · Point |
| ASSEMBLE | New Component · Joint |
| INSPECT | Measure · Section Analysis · Print View · Fit All |
| UTILITIES | Search · Change Parameters · Appearance · Scribble / Red Pen · Note |

Buttons with a small arrow ▾ hold more tools (for example Hole ▾ Screw Here, Thread).

### Extrude

Direction **One Side**, **Symmetric**, **Two Sides**, **To Object** (up to a face or plane) or **All** (through
everything). Plus a **Taper Angle** (positive narrows) and **thin wall** (just a rim of a given thickness). Operation:
new body, join, cut, intersect. Clicking a flat face of a body and extruding it works like Press Pull.

### Hole

Place points in a sketch on the face, then **Hole**. With a **Standard** (ISO metric, ISO metric fine, UNC, UNF) MyCAD
fills in everything: a **clearance hole** with fine/medium/coarse fit, or a **tapped hole** (core hole, optionally with
a real thread), and the counterbore or countersink of the screw. With **Custom** every value is free.

### Thread

Click the cylindrical face of a bolt or a hole, **Thread**. The ISO size follows the diameter. **Clearance** per side for
printed threads, or tick "Clearance for 3D printing" and let MyCAD pick it.

### Fillet, Chamfer, Shell

- **Fillet** with a constant or variable radius (start/end).
- **Chamfer** with equal distance, two distances or distance and angle; side can be flipped.
- **Shell** hollows a body out; choose the open faces.

### Pattern, Mirror, Move

- **Pattern** rectangular, circular or along a path (edges); directions and axis from edges, axes or face normals; copies
  can turn along the path. Works for features (extrusion, hole) and whole bodies.
- **Mirror** across any plane or flat face.
- **Move** by distances and rotations, also around a chosen axis.

### Remove Face

Select faces, **Remove Face**: the faces around them grow over the gap. Fillets, chamfers, holes or pockets disappear
again, which is handy for imported STEP parts that have no history.

## Timeline

- At the bottom center, one entry per step; double-click to open it again.
- **Roll back:** the arrows, or a click, move the marker back; later steps rest until you move forward again.
- **Reorder:** drag an entry. If it needs another step, MyCAD says which.
- **Groups:** Ctrl+click several entries, right-click → **Group Selected Steps**. Groups fold into a chip, and can be
  renamed and ungrouped.

## Errors that explain themselves

When a step fails, it gets a badge in the timeline and a plain-language message in the panel. Where possible, MyCAD
works out a **suggestion** and shows it as a button:

- fillet or chamfer too big → the largest size that still works
- shell too thick, thread too short, revolve axis through the profile, screw too short
- the affected edges are marked on the model

If the model changes so that a selected edge may no longer be the same one, MyCAD takes the closest match and marks the
step orange: **Show Affected Edges** or **Looks Right**.

## Change sizes on the model

With no tool active, double-click a face (a single click only selects it): a glass card next to it shows the sizes
that make it: the extrusion length of a top face, the sketch dimension of a side face, a hole diameter, a fillet
radius. Type a number or formula, press **Enter**. If the size is a parameter, the parameter changes (and so does the
note it's written in). A formula can't be overwritten here; change the parameter instead.

## Command search

**Ctrl+K** opens the search at the top center. It finds commands, bodies and sketches, forgives typos, understands
English and German, and words from other programs (*pocket*, *pad*, *thread*, *fit*, *slicer*). **Enter** runs the
first hit; the ones you used last are at the top.
