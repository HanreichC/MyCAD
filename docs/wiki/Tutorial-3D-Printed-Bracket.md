# Tutorial: a bracket for 3D printing

In about 20 minutes you build a mounting plate with rounded corners and two screw holes, drive it from a note, correct
it with the Red Pen, check it for printing and send it to your slicer. Along the way you meet the ideas that make MyCAD
different.

> Tip: every button mentioned here can also be found with **Ctrl+K**. Just type its name.

The built-in help has this tutorial too: **?** → Getting Started → *Tutorial: a bracket for 3D printing*.

---

## 1. New design, and no more saving

On the start page, click **New Design**. From now on MyCAD saves by itself, after every step as soon as you pause for a
moment. The design gets its own folder in your projects folder (Settings → General → Projects folder). There's no save
button to remember, and closing never asks.

## 2. Put the sizes in a note

In the toolbar, UTILITIES section, click **Note**. A yellow note appears. Type:

```
Width = 60 mm
Depth = 30 mm
Thickness = 4 mm
Slot = Width - 16 mm
```

After each **Enter** the lines become parameters. The formula shows its value right away:
`Slot = Width - 16 mm → 44.00 mm`. From now on you can type these names into any size field. **Change Parameters**
lists them too, marked "In note …".

> Calculating works as well: a line ending in `=` is worked out. `Width / 2 =` gives `30.00 mm`.

## 3. Sketch and body

1. **Create Sketch** (key **S**), then click the XY plane in the view.
2. Draw a **Rectangle**, roughly, anywhere around the origin.
3. With **Dimension**, click the width and type `Width` instead of a number, and `Depth` for the height.
4. **Finish Sketch**.
5. **Extrude** (key **E**), click the rectangle, type `Thickness` as the distance, click **OK** at the top of the panel.

You have a 60 × 30 × 4 mm plate.

## 4. Tap a face, change a number

With no tool active, click the **top face** of the plate. A small glass card appears next to it with the size that
makes this face: Distance = Thickness. Type `6` and press **Enter**. The plate gets thicker, and the note now says
`Thickness = 6 mm`. It works the other way round too: change the note to `Width = 80 mm`, click into the view, and the
plate gets wider. **Ctrl+Z** takes back any change.

## 5. Round the corners

Ctrl+click the four vertical edges, **Fillet** (key **F**), radius `3`, **OK**.

Go ahead and try a radius that's too big, `20` for example: the step gets a red badge in the timeline, the panel says
what doesn't work and offers a radius that still fits. One click on the suggestion and you're good again.

## 6. Correct it with the Red Pen

Instead of hunting for tools, write what you want right on the model:

1. In the UTILITIES section, click the small arrow ▾ next to **Scribble** and choose **Red Pen**. A see-through sheet lies in
   front of the model, and the pen is red.
2. Write (with a pen tablet or the mouse) **`Ø4.5`** twice on the top face, where the holes should go, and **`C1`** next to
   one of the long top edges.
3. In the palette, click **Apply Corrections**. Each correction becomes a card: `Ø4.5 → Hole Ø4.5 mm`,
   `C1 → Chamfer 1 mm on 1 edge`.
4. Point at a card with the mouse to highlight its target. **Show** tries the result on the model, **Apply** keeps it,
   **Apply All** does them all.

The ink stays in the scribble "Corrections", so later you can still see what you changed and why.

> The Red Pen also knows `R2` (fillet), `M5` (tapped hole or thread), `+5` / `−5` (pull or push a face), `H7` or
> `print` (fit), `3×` (pattern), a plain number (the face's size) and `remove` or a line through a face (remove the
> face). See [Red Pen and Scribble](Red-Pen-and-Scribble).

## 7. Check it for printing

1. In the INSPECT section, click **Print View**. Hatched red: overhangs that need supports. Dotted green: what lies on the
   bed. Cross-hatched yellow: walls thinner than 0.8 mm. The legend is at the bottom right.
2. To print it on another side, click that face and **Choose Bottom Face** in the legend.

## 8. Keep this state

In MyCAD **Ctrl+S** means **Save Version**: give the state a name, such as "First print". Everything is saved anyway;
the name just helps you find it again.

## 9. Print

Click **Print** in the legend (or in the FILE section). MyCAD finds your slicer (OrcaSlicer, Bambu Studio, PrusaSlicer
or Cura, Flatpak included) and opens the plate there as a 3MF, with the chosen face down. The first time, it asks which
slicer you want if you have more than one.

## 10. Look back

Make the plate wider (`Width = 100 mm` in the note). Then, in the FILE section, click the arrow ▾ next to **Save Version**,
then **Versions**: pick "First print" and **Compare**. What was added since then lies over the model dotted green,
what was removed hatched red, and the panel lists the changed steps. **Restore** brings the old state back without
deleting the new one.

---

**Next:** [Tutorial: an assembly with joints](Tutorial-Assembly) · [Features](Features)
