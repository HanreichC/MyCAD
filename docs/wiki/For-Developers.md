# For Developers

## Get it and build it

MyCAD has a git submodule (OndselSolver, the joint solver), so clone with submodules:

```sh
git clone --recursive https://github.com/HanreichC/MyCAD.git
# already cloned:
git submodule update --init
```

The build runs in a Podman container (`.devcontainer/`); nothing lands on your system:

```sh
./install.sh   # builds MyCAD and adds the `mycad` launcher and a menu entry
mycad
```

`tools/appimage.sh` builds the release AppImage; CI (`.github/workflows/release.yml`) builds it after every commit,
once all tests pass.

## How the code is organized

| Where | What |
|---|---|
| `src/Gui/Shell/` | the interface: Liquid Glass, toolbar, timeline, notes, command search, settings, start page, help, always-save |
| `src/Mod/Design/App/` | the model: bodies, features, timeline, joints, Red Pen grammar, print check, fits |
| `src/Mod/Design/Gui/` | commands, feature panels, scribble, handwriting, Print View, correction cards, Versions window |
| `src/Mod/Design/DesignExport.py` | 3MF export, finding and starting slicers |
| `src/Mod/Design/DesignVersions.py` | versions, retention, compare, variants |
| `src/Mod/Design/App/AssemblySolver.*` | thin interface to OndselSolver (the only file that knows the solver) |
| `tools/help_content.py` | source of the built-in help (`python tools/help_content.py` writes `help.json`) |
| `tools/make_icons.py` | generates the icons |
| `docs/PLAN.md` | roadmap and status of everything |
| `docs/wiki/` | this wiki as Markdown in the repo |

Logic that doesn't need FreeCAD lives in small headers, each with its own check: `NoteParameters.h`, `Fits.h`
(ISO 286), `PrintCheck.h`, `RedPen.h`, `Gui/Shell/CommandSearch.h`, `Gui/ScribbleTidy.h`, `Gui/ScribbleShapes.h`.

## Tests

Everything at once (inside the container):

```sh
GUI=ci tests/run_all.sh
```

| Kind | Where | What |
|---|---|---|
| C checks | `tests/*_check.cpp` | logic without FreeCAD, e.g. the fit tables and the Red Pen grammar; `scribble_read_check` reads synthetic handwriting with the real model |
| Headless | `tests/design/test_*.py` | FreeCADCmd + unittest: features, volumes, errors and suggestions, joints, print check, slicer search, versions |
| GUI | `tests/gui/test_*.py` | click through the app like a person, with real mouse and keyboard events, under Xvfb |

Single tests:

```sh
PATTERN=test_joints.py tests/design/run.sh
tests/gui/run.sh tests/gui/test_red_pen_ui.py /tmp/redpen   # log /tmp/redpen.txt, pictures /tmp/redpen*.png
```

The GUI tests listed in `tests/gui/ci.txt` run in CI. `harness.py` turns always-save off so the test timing holds;
`test_versions_ui.py` turns it on on purpose. Steps that may take a while (animations, dialogs) belong in `in_order`
rather than `run`.

## Project rules

How we work is in `CLAUDE.md`: reuse what's there, shortest working diff, one runnable check for non-trivial logic, mark
deliberate simplifications with `ponytail:`. The interface follows the MyStyle style guide (values only from the design
tokens).
