// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QCoreApplication>
#include <QPixmap>
#include <QSize>
#include <QString>
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
/// Erscheinungsbild neu anwenden, nachdem die Einstellungen (MyCAD/Appearance, GlassLevel, IncreaseContrast,
/// ReduceTransparency, ReduceMotion) geändert wurden; wirkt sofort auf alle Fenster
void applyAppearance();
/// Aussehen der Körper (Einstellung "Body material"): Auswahl und Wahl; färbt Körper mit Standard-Look gleich um
struct BodyMaterialEntry
{
    const char* name;     ///< englisch, über T() anzeigen
    const char* texture;  ///< Ressource der Textur oder nullptr
    bool wood;
};
std::vector<BodyMaterialEntry> bodyMaterialList();
App::Material bodyMaterialAppearance(int index);
const char* defaultBodyTexture();  ///< Textur neuer Körper oder nullptr
QPixmap materialThumbnail(const char* texture, QSize size, qreal ratio);
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
