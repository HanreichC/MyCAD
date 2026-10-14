// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QCoreApplication>
#include <QString>
#include <vector>

namespace Gui::Shell
{

/// Ersetzt die klassische FreeCAD-Oberfläche durch die MyCAD-Oberfläche:
/// 3D-Ansicht über das ganze Fenster, darüber schwebende Liquid-Glass-Panels.
void install();
/// Namen unter den Symbolen der Toolbar ein-/ausblenden (Einstellung "Show tool names")
void setToolNames(bool on);
/// Glas wie in iOS 26.1: 0 = Tinted (besser lesbar), 1 = Clear (durchsichtiger)
void setGlass(int clear);
/// Aussehen der Körper (Einstellung "Body material"): Auswahl und Wahl; färbt Körper mit Standard-Look gleich um
std::vector<const char*> bodyMaterialNames();
void setBodyMaterial(int index);
/// Ordner mit den Designs des Benutzers (Startseite "Projects", Einstellung "Projects folder")
QString projectsFolder();

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
