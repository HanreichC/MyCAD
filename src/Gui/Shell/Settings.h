// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QObject>
#include <QPoint>
#include <QPointer>
#include <QWidget>

#include <Base/Parameter.h>

#include <vector>

namespace Gui::Shell
{

/// Einstellungen-Fenster: Navigation (Zoomen, Scrollen, Drehen) und Tasten als Maustasten
void showSettings();
/// Befehl MyCAD_Settings (Ctrl+,) anlegen, Standard-Navigation setzen, Tasten-Zuordnung starten
void registerSettings();

/// Tasten als Maustasten im 3D-Fenster (wie cad.helper, aber nur innerhalb von MyCAD und ohne Sonderrechte):
/// z. B. Leertaste halten = mittlere Maustaste, damit sich die Ansicht per Trackpad verschieben/drehen lässt.
class MouseKeyMapper: public QObject, public ParameterGrp::ObserverType
{
public:
    static MouseKeyMapper& instance();
    void reload();  ///< Zuordnungen aus den Einstellungen lesen
    void OnChange(Base::Subject<const char*>&, const char* name) override;

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    struct Mapping
    {
        int key;
        Qt::MouseButton button;
        QString mode;  ///< hold, click, double, toggle
    };
    void send(int type, Qt::MouseButton button);
    const Mapping* find(int key) const;
    std::vector<Mapping> mappings;
    QPointer<QWidget> hover;  ///< 3D-Fenster unter dem Mauszeiger
    QPoint hoverPos;
    Qt::MouseButtons held;
    bool sending = false;
};

}  // namespace Gui::Shell
