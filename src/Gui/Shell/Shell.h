// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QCoreApplication>
#include <QPixmap>
#include <QRectF>
#include <QSize>
#include <QString>
#include <functional>
#include <vector>

namespace App
{
class Material;
}

namespace Gui::Shell
{

/// Ersetzt die klassische FreeCAD-Oberfläche durch die MyCAD-Oberfläche:
/// 3D-Ansicht über das ganze Fenster, darüber schwebende Liquid-Glass-Panels.
void install();
/// Vor dem ersten Anzeigen des Hauptfensters: rahmenlos und mit Alphakanal für die gerundeten Ecken
void prepareWindow();
/// Namen unter den Symbolen der Toolbar ein-/ausblenden (Einstellung "Show tool names")
void setToolNames(bool on);
/// Handschrift suchen in Scribbles: das Design-Modul meldet hier die Suche an (nur mit Handschrift-Modell), dann zeigt
/// die Scribble-Palette ein Suchfeld. Die Suche bekommt den Text und sagt, ob sie ihn gefunden hat.
void setScribbleFind(std::function<bool(const QString&)> find);
/// Scribble "Nur das Blatt": Toolbar, Seitenleiste, Palette und ViewCube klappen zu einer kleinen Pille oben ein
/// (Rückgängig, Stift, Radierer, Ausklappen). Endet mit dem Scribble.
void setScribbleFocus(bool on);
bool scribbleFocus();
/// Glasleiste mit den Farben und Löschen unter der Auswahl eines Scribbles (Rechteck in Ansichts-Koordinaten,
/// ohne Auswahl leer: dann verschwindet sie)
void showScribbleActions(const QRectF& selection);
/// Erscheinungsbild neu anwenden, nachdem die Einstellungen (MyCAD/Appearance, GlassLevel, IncreaseContrast,
/// ReduceTransparency, ReduceMotion) geändert wurden; wirkt sofort auf alle Fenster
void applyAppearance();
/// Aussehen der Körper (Einstellung "Body material"): Auswahl und Wahl; färbt Körper mit Standard-Look gleich um
struct BodyMaterialEntry
{
    const char* name;     ///< englisch, über T() anzeigen
    const char* texture;   ///< Ressource der Textur oder nullptr
    bool wood;
    const char* category;  ///< englisch: Colors, Metal, Anodized, Coatings, Plastic, 3D Print, Rubber, Glass, Wood …
    const char* family;    ///< Varianten (Farben, Finish) teilen sich eine Familie
};
std::vector<BodyMaterialEntry> bodyMaterialList();
App::Material bodyMaterialAppearance(int index);
const char* defaultBodyTexture();  ///< Textur neuer Körper oder nullptr
/// Kugel mit dem Material, gerendert wie im Modell (alle auf einmal beim ersten Aufruf), rund ausgeschnitten
QPixmap materialPreview(int index, int size, qreal ratio);
/// Eintrag der Bibliothek, der genau so aussieht, oder -1
int bodyMaterialIndex(const App::Material& mat);
void setBodyMaterial(int index);
/// Ordner mit den Designs des Benutzers (Startseite "Projects", Einstellung "Projects folder")
QString projectsFolder();
/// Stand dieses Builds aus Commit-Datum und -Hash, z. B. "2026.10.21 · b9d3cde" (Startseite, Einstellungen)
QString version();

/// Sichtbarer Text in der eingestellten Sprache (englischer Originaltext ist der Schlüssel, siehe Translations.cpp)
inline QString T(const char* english)
{
    return QCoreApplication::translate("MyCAD", english);
}
inline QString T(const QString& english)
{
    return T(english.toUtf8().constData());
}
/// Sprache der Oberfläche (Einstellung "Language"): "English" oder "German"; wirkt nach einem Neustart
QString language();
void setLanguage(const QString& name);
/// MyCADs deutsche Texte als Qt-Übersetzer einhängen (FreeCADs eigene lädt FreeCAD selbst)
void installTranslations();

}  // namespace Gui::Shell
