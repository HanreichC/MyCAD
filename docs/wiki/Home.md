# MyCAD Wiki

MyCAD is parametric CAD for Linux: the workflow of Fusion 360, the look of Liquid Glass, and a handful of ideas you
won't find in any other CAD program. It runs as an AppImage, nothing to install.

Inside the app, the built-in help (**?** at the bottom left) explains every tool step by step, in English or German,
depending on the language you picked. This wiki is the overview for everyone else.

## Where to start

| You want to … | Read |
|---|---|
| see everything MyCAD can do | **[Features](Features)**, all on one page |
| get going right away | **[Tutorial: a bracket for 3D printing](Tutorial-3D-Printed-Bracket)** (about 20 minutes) |
| connect parts that move | **[Tutorial: an assembly with joints](Tutorial-Assembly)** |
| look something up | the topic pages below |

## Topics

- [Modeling](Modeling): sketches, every tool, the timeline, sizes on the model, errors that explain themselves
- [Notes and Parameters](Notes-and-Parameters): calculate in a note and define parameters right there
- [Red Pen and Scribble](Red-Pen-and-Scribble): sketch ideas, handwriting, write corrections on the model
- [3D Printing](3D-Printing): Print View, printing to your slicer, fits, Screw Here, print threads
- [Versions and Variants](Versions-and-Variants): always saved, nothing gets lost
- [Assemblies](Assemblies): components, joints, closed loops
- [Controls and Settings](Controls-and-Settings): navigation, shortcuts, pen tablets, language, materials
- [For Developers](For-Developers): build, test, how the code is organized

## What makes MyCAD different, in one minute

- **Always saved.** No save button, no question when you close. Every state becomes a version you can compare and
  bring back.
- **Double-click a face, change a number.** Double-click a face and the sizes that make it appear right on the model.
- **Your note is your parameter list.** `Wall = 2 mm` in a note is a parameter any size field can use.
- **Red Pen.** Write `R2` next to an edge, `M5` on a face, and MyCAD turns them into a fillet and a tapped hole.
- **Errors explain themselves.** A fillet too big? MyCAD tells you which radius fits and sets it in one click.
- **Tools for a purpose.** Screw Here joins two parts in one step; Fit makes a hole and its pin fit, to ISO or for
  your printer.
- **Printing in the viewport.** Overhangs, bed faces and thin walls on the model; Print opens your slicer.
- **Ctrl+K** finds every command, body and sketch, typos included.
