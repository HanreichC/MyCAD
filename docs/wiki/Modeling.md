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

- **Dimension** works out from the selection what to measure (length, distance, radius, angle). Place it, and a field
  opens right on the dimension: type the value, **Enter** applies, **Esc** keeps the old one, **Tab** applies and jumps
  to the next dimension of the sketch. Every size field takes formulas and parameter names.

  ![Dimension](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_dimension.gif)

- **Esc** puts the active tool away, **Finish Sketch** takes you back to the model.

  ![Finish Sketch](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_finish.gif)

- Edges of the model can be projected into the sketch and reused.

  ![Project](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_project.gif)

- The **Sketch Palette** on the right: **Look At** turns the view straight onto the sketch again, **Slice** cuts away
  what lies in front of the sketch plane, **Grid** and **Snap** switch the grid and snapping, **Construction** draws
  helper lines, and the blue **Finish Sketch** leaves the sketch. One row says how many **dimensions are missing**
  (or *Fully defined*); click it and MyCAD adds them by intent: symmetric when the shape is centered on the origin,
  then the sizes, then its distance to the origin. **Show What Can Move** selects what is still free.

  ![Sketch Palette](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/sketch_palette.gif)

- **Duplicate:** right-click a sketch in the browser → **Duplicate** copies it, on the same plane, as a new step.
- **Pen in the sketch:** with a pen tablet, draw straight into the sketch. Hold still at the end and the stroke becomes a
  clean line, circle or rectangle; scratch over lines to delete them; a tick finishes the sketch.

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
| CREATE | Sketch · Extrude · Revolve · Sweep · Loft · Rib · Web · Emboss · Box · Cylinder · Sphere · Torus · Coil · Standard Part · Gear · Hinge · Snap Hook · Snap Recess · Hole · Screw Here · Thread · Pattern · Mirror · Photo to Sketch · Code Step |
| MODIFY | Press Pull · Fillet · Chamfer · Shell · Draft · Fit · Remove Face · Replace Face · Split Face · Combine · Split Body · Move · Align · Scale |
| CONSTRUCT | Offset Plane · Plane at Angle · Midplane · Plane · Axis · Point |
| ASSEMBLE | New Component · Joint |
| INSPECT | Measure · Section Analysis · Check References · Fit All |
| PRINT | Print View · Suggest Orientation · Choose Bottom Face · Split for Printing · Fit · Printer Test · Export · Print |
| UTILITIES | Search · Change Parameters · Parts List · Appearance · Scribble · Red Pen · Note |

Align and Midplane stay true to what you picked: an aligned body follows its target when that moves or grows, a midplane
stays in the middle when one of its two faces moves.

The toolbar shows the tools you use most; click a heading such as **CREATE ▾** and the whole group opens as a grid with
names (Settings › Toolbar › All Tools shows every tool at once). Click a face, an edge or a profile and the tools that
fit float right above it.

Buttons with a small arrow ▾ hold more tools (for example Hole ▾ Screw Here, Thread).

The other tools in short clips; the ones with more to say have their own section below.

**CREATE**

| | |
|---|---|
| **Revolve**<br>![Revolve](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Revolve.gif) | **Sweep**<br>![Sweep](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Sweep.gif) |
| **Loft**<br>![Loft](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Loft.gif) | **Rib**<br>![Rib](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Rib.gif) |
| **Web**<br>![Web](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Web.gif) | **Emboss**<br>![Emboss](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Emboss.gif) |
| **Box, Cylinder and more**<br>![Box, Cylinder and more](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/primitives.gif) | **Standard Part**<br>![Standard Part](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_StandardPart.gif) |
| **Gear**<br>![Gear](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Gear.gif) | **Hinge**<br>![Hinge](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Hinge.gif) |
| **Snap Hook and Snap Recess**<br>![Snap Hook and Snap Recess](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_SnapHook.gif) | **Code Step**<br>![Code Step](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_CodeStep.gif) |

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

### Photo to Sketch

Lay a flat part on plain light paper, photograph it from straight above, then FILE → **Import** and choose the photo
(PNG or JPG; also Ctrl+K → **Photo to Sketch**). Easiest: the part on a whole white **A4 sheet** on a darker table,
all four corners in the photo, angle doesn't matter: MyCAD straightens the perspective and asks nothing. On grid paper it
finds the squares and only asks their size (usually 5 mm); on plain paper type how wide the part really is: MyCAD traces the outline and every hole
as a sketch to scale, ready to extrude. Round holes become real circles, everything else straight lines.

### Extrude

Direction **One Side**, **Symmetric**, **Two Sides**, **To Object** (up to a face or plane) or **All** (through
everything). Plus a **Taper angle** (positive narrows) and **thin wall** (just a rim of a given thickness). Operation:
new body, join, cut, intersect. Clicking a flat face of a body and extruding it works like Press Pull. A **cut goes
through everything in its way, also bodies of other components** (a hole through a part and the plate it sits on);
a new part in its own component that only overlaps other components stays a body of its own.

![Extrude](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/Design_Extrude.gif)

### Hole

Click **Hole**, then the face where it goes. Near the middle of the face (or the centre of a round face) the hole snaps
there, elsewhere to the nearest 0.5 mm, and it gets dimensions to the two nearest edges by itself: to move it later,
change them in its sketch. While the panel is open, click more spots for more holes: one at the same distance from an
edge as an earlier one snaps to it and is bound to it, so the row moves together. For several holes at exact spots, place points in a sketch on the face, select it, then
**Hole**. With a **Standard** (ISO metric, ISO metric fine, UNC, UNF) MyCAD
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
- **What depends on it:** hold the mouse over a step and the steps that depend on it light up; the tooltip names them.
  The body it changes lights up in the model; select a body and the steps of all other bodies fade.
- **Delete with a preview:** if something else depends on what you delete, MyCAD asks first and lists it: bodies that
  go along, sketches that lose their face (they stay in place, with a warning), steps that lose their input. For a
  whole body its own steps go along quietly; named are its mirror/pattern copies, a Combine that used it as the only
  tool, and other bodies' sketches or steps built on its faces.
- **Check References** (Ctrl+K, or right-click a step with a warning) lists in one place every step that no longer finds its edges or faces for certain:
  lost profiles and faces, edges found again by their position, references to elements that are gone. Each row has
  **Show**, **Edit** (choose again) and, for a guess, **Looks Right**.
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

A red step never stops the rest, like in Fusion: the body goes on without it, and the steps after it compute normally.
Fix it or delete it when you are ready; Ctrl+K → *Why is this red?* finds it.

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

It also takes sentences: *4 holes M3 in the corners*, *edges 2 mm fillet*, *Box 40 x 30 x 10*, *Shell 2 mm*, *10 mm up*,
in English or German; Enter opens the tool with those values and its preview. And you can ask: *Why is this red?*,
*What depends on this?*

![Search](https://raw.githubusercontent.com/HanreichC/MyCAD/main/src/Gui/Shell/help/images/search.gif)
