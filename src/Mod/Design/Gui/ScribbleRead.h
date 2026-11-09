// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/// Handschrift lesen in Scribbles, offline: jede Zeile aus Stift-Strichen wird als Graustufenbild gerendert und von
/// DE·HTR v2 gelesen (deutsche Handschrift, CTC, 10 MB, onnxruntime; Herkunft und Lizenz in htr/README.md).
/// Ohne onnxruntime oder Modell im Build liest es nichts: available() ist dann false.
/// Hängt nur von Qt ab, nicht von FreeCAD. Prüfung: tests/scribble_read_check.cpp

#include "ScribbleTidy.h"

#include <QImage>
#include <QString>

#include <vector>

namespace ScribbleRead
{

struct Char
{
    QChar c;
    double x = 0;          ///< Mitte des Zeichens auf dem Blatt (x wie die Striche)
    float confidence = 0;  ///< 0…1, wie sicher das Modell ist
};

struct Line
{
    QString text;
    std::vector<Char> chars;      ///< je Zeichen von text, gleiche Reihenfolge
    std::vector<size_t> strokes;  ///< Nummern der Striche dieser Zeile
};

bool available();

/// Striche in Blatt-Koordinaten (y nach oben), in Schreibreihenfolge → gelesene Zeilen von oben nach unten
std::vector<Line> read(const std::vector<ScribbleTidy::Stroke>& strokes);

/// Wo der Tinte ein Zeichen fehlt, das die Korrektur ergänzt hat
struct InkEdit
{
    enum Kind
    {
        Slash,   ///< Schrägstrich durch den Kreis bei x: o12 → Ø12
        Degree,  ///< Gradzeichen hinter der Ziffer bei x: 2×45 → 2×45°
        Space    ///< Lücke bei x: 25mm → 25 mm
    } kind;
    double x = 0;
    double next = 0;  ///< Slash: x der Ziffer dahinter, nach deren Höhe sich das Ø richtet
};

/// CAD-Schreibweise: korrigiert line.text (und chars) zu Ø, ×, °, ±, Einheit mit Abstand, Ziffern statt ähnlicher
/// Buchstaben in Zahlen. Gibt zurück, was die Tinte dafür braucht.
std::vector<InkEdit> correct(Line& line);

/// Ergänzt die Tinte der Zeile (Blatt-Koordinaten, y nach oben): neue Striche hinten an strokes, Lücken verschieben
/// Striche. Gibt je neuem Strich den Strich zurück, von dem er Stift, Farbe und Breite erbt.
std::vector<size_t> applyInk(std::vector<ScribbleTidy::Stroke>& strokes, const Line& line, const std::vector<InkEdit>& edits);

/// eine Zeile, wie das Modell sie sieht (64 px hoch, schwarz auf weiß); x0 und scale: Blatt-x = x0 + Pixel / scale
QImage render(const std::vector<ScribbleTidy::Stroke>& strokes, const std::vector<size_t>& line, double& x0, double& scale);

/// Modell aus einer Datei statt aus den Ressourcen (für den Check); vor dem ersten available() aufrufen
void setModelFile(const QString& file);

}  // namespace ScribbleRead
