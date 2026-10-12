# SPDX-License-Identifier: LGPL-2.1-or-later


class DesignWorkbench(Workbench):
    "Fusion-artige Arbeitsweise: Skizzen und Körper"

    MenuText = "Design"
    ToolTip = "Sketches and bodies"

    def Initialize(self):
        import SketcherGui  # Skizzen-Werkzeuge
        import PartDesignGui  # Icons und Ursprungs-Ebenen-Darstellung
        import DesignGui

    def GetClassName(self):
        return "Gui::PythonWorkbench"


Gui.addWorkbench(DesignWorkbench())
