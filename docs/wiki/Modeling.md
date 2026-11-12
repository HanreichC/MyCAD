# Modeling

## The workflow

As in Fusion 360: a **sketch** on a plane or face, click a profile, **Extrude** or **Revolve**, then keep going with
tools like Fillet, Hole and Pattern. Every step lands in the **timeline**.

![Your first design](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/start_first.gif)

A design is made of **bodies** in **components**. The root component is the design itself; further components are for
[assemblies](Assemblies).

## Sketches

- **Create Sketch** (S), then click a plane or flat face. The camera looks straight at it.

  ![Create Sketch](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_CreateSketch.gif)

- Every closed region is its own profile. Two circles inside each other give a ring and a disc.

  ![Sketching basics](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_basics.gif)

- **Dimension** works out from the selection what to measure (length, distance, radius, angle). Every size field takes
  formulas and parameter names.

  ![Dimension](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_dimension.gif)

- **Esc** puts the active tool away, **Finish Sketch** takes you back to the model.

  ![Finish Sketch](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_finish.gif)

- Edges of the model can be projected into the sketch and reused.

  ![Project](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_project.gif)

- The **Sketch Palette** on the right: **Look At** turns the view straight onto the sketch again, **Slice** cuts away
  what lies in front of the sketch plane, **Grid** and **Snap** switch the grid and snapping, **Construction** draws
  helper lines, and the blue **Finish Sketch** leaves the sketch.

  ![Sketch Palette](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_palette.gif)

The other sketch tools:

**Draw**

| | |
|---|---|
| **Line**<br>![Line](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_line.gif) | **Polyline**<br>![Polyline](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_polyline.gif) |
| **Rectangle**<br>![Rectangle](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_rectangle.gif) | **Circle and Ellipse**<br>![Circle and Ellipse](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_circle.gif) |
| **Arc**<br>![Arc](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_arc.gif) | **Slot**<br>![Slot](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_slot.gif) |
| **Polygon**<br>![Polygon](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_polygon.gif) | **B-Spline**<br>![B-Spline](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_bspline.gif) |
| **Conic**<br>![Conic](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_conic.gif) | **Point**<br>![Point](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_point.gif) |
| **Text**<br>![Text](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_text.gif) |   |

**Modify**

| | |
|---|---|
| **Sketch Fillet and Chamfer**<br>![Sketch Fillet and Chamfer](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_fillet.gif) | **Trim, Extend and Split**<br>![Trim, Extend and Split](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_trim.gif) |
| **Offset**<br>![Offset](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_offset.gif) | **Mirror**<br>![Mirror](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_mirror.gif) |
| **Pattern**<br>![Pattern](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_pattern.gif) | **Move and Scale**<br>![Move and Scale](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_move.gif) |
| **Construction Geometry**<br>![Construction Geometry](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_construction.gif) |   |

**Constraints**

| | |
|---|---|
| **Coincident**<br>![Coincident](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_coincident.gif) | **Horizontal and Vertical**<br>![Horizontal and Vertical](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_horver.gif) |
| **Parallel and Perpendicular**<br>![Parallel and Perpendicular](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_parallel.gif) | **Tangent**<br>![Tangent](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_tangent.gif) |
| **Equal**<br>![Equal](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_equal.gif) | **Symmetric**<br>![Symmetric](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_symmetric.gif) |
| **Block**<br>![Block](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_block.gif) |   |

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

The other tools in short clips; the ones with more to say have their own section below.

**CREATE**

| | |
|---|---|
| **Revolve**<br>![Revolve](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Revolve.gif) | **Sweep**<br>![Sweep](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Sweep.gif) |
| **Loft**<br>![Loft](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Loft.gif) | **Rib**<br>![Rib](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Rib.gif) |
| **Web**<br>![Web](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Web.gif) | **Emboss**<br>![Emboss](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Emboss.gif) |
| **Box, Cylinder and more**<br>![Box, Cylinder and more](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/primitives.gif) |   |

**MODIFY**

| | |
|---|---|
| **Press Pull**<br>![Press Pull](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_PressPull.gif) | **Replace Face**<br>![Replace Face](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_ReplaceFace.gif) |
| **Split Face**<br>![Split Face](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_SplitFace.gif) | **Draft**<br>![Draft](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Draft.gif) |
| **Combine**<br>![Combine](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Combine.gif) | **Split Body**<br>![Split Body](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_SplitBody.gif) |
| **Align**<br>![Align](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Align.gif) | **Scale**<br>![Scale](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Scale.gif) |
| **Delete**<br>![Delete](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Delete.gif) |   |

**CONSTRUCT**

| | |
|---|---|
| **Offset Plane**<br>![Offset Plane](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_OffsetPlane.gif) | **Plane at Angle**<br>![Plane at Angle](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_AnglePlane.gif) |
| **Midplane**<br>![Midplane](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Midplane.gif) | **Plane**<br>![Plane](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Plane.gif) |
| **Axis**<br>![Axis](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Axis.gif) | **Point**<br>![Point](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Point.gif) |

**INSPECT**

| | |
|---|---|
| **Section Analysis**<br>![Section Analysis](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Section.gif) | **Fit All**<br>![Fit All](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Std_ViewFitAll.gif) |

### Extrude

Direction **One Side**, **Symmetric**, **Two Sides**, **To Object** (up to a face or plane) or **All** (through
everything). Plus a **Taper Angle** (positive narrows) and **thin wall** (just a rim of a given thickness). Operation:
new body, join, cut, intersect. Clicking a flat face of a body and extruding it works like Press Pull.

![Extrude](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Extrude.gif)

### Hole

Place points in a sketch on the face, then **Hole**. With a **Standard** (ISO metric, ISO metric fine, UNC, UNF) MyCAD
fills in everything: a **clearance hole** with fine/medium/coarse fit, or a **tapped hole** (core hole, optionally with
a real thread), and the counterbore or countersink of the screw. With **Custom** every value is free.

![Hole](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Hole.gif)

### Thread

Click the cylindrical face of a bolt or a hole, **Thread**. The ISO size follows the diameter. **Clearance** per side for
printed threads, or tick "Clearance for 3D printing" and let MyCAD pick it.

![Thread](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Thread.gif)

### Fillet, Chamfer, Shell

- **Fillet** with a constant or variable radius (start/end).
- **Chamfer** with equal distance, two distances or distance and angle; side can be flipped.
- **Shell** hollows a body out; choose the open faces.

| | |
|---|---|
| **Fillet**<br>![Fillet](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Fillet.gif) | **Chamfer**<br>![Chamfer](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Chamfer.gif) |
| **Shell**<br>![Shell](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Shell.gif) |   |

### Pattern, Mirror, Move

- **Pattern** rectangular, circular or along a path (edges); directions and axis from edges, axes or face normals; copies
  can turn along the path. Works for features (extrusion, hole) and whole bodies.
- **Mirror** across any plane or flat face.
- **Move** by distances and rotations, also around a chosen axis.

| | |
|---|---|
| **Pattern**<br>![Pattern](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Pattern.gif) | **Mirror**<br>![Mirror](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Mirror.gif) |
| **Move**<br>![Move](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Move.gif) |   |

### Remove Face

Select faces, **Remove Face**: the faces around them grow over the gap. Fillets, chamfers, holes or pockets disappear
again, which is handy for imported STEP parts that have no history.

![Remove Face](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_RemoveFace.gif)

## Timeline

- At the bottom center, one entry per step; double-click to open it again.
- **Roll back:** the arrows, or a click, move the marker back; later steps rest until you move forward again.
- **Reorder:** drag an entry. If it needs another step, MyCAD says which.
- **Groups:** Ctrl+click several entries, right-click → **Group Selected Steps**. Groups fold into a chip, and can be
  renamed and ungrouped.

  ![Timeline and changes](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/start_timeline.gif)

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

![Change a size on the model](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/start_dimensions.gif)

## Typing numbers

Every size field takes a number (`12,5` and `12.5` are the same, millimetres unless you say otherwise), a unit
(`1 in`, `3 cm`), a calculation (`2 * 7,5`) or a parameter name (`Width / 2`, then **Enter**: the field stays linked).
The model follows while you type; **Enter** after a plain number is the same as OK. Inside brackets a comma separates
values, so write `2 * (1.5 + 1)` with a point there.

![Typing numbers](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/numbers.gif)

## Command search

**Ctrl+K** opens the search at the top center. It finds commands, bodies and sketches, forgives typos, understands
English and German, and words from other programs (*pocket*, *pad*, *thread*, *fit*, *slicer*). **Enter** runs the
first hit; the ones you used last are at the top.

![Search](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/search.gif)
