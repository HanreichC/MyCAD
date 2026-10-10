// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Shell.h"
#include "GlassPanel.h"

#include <App/Application.h>
#include <Gui/Action.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/DockWindowManager.h>
#include <Gui/MainWindow.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>

#include <QAbstractScrollArea>
#include <QApplication>
#include <QDockWidget>
#include <QFontDatabase>
#include <QFrame>
#include <QGraphicsScene>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QPointer>
#include <QStatusBar>
#include <QStyleHints>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>

#include <vector>

using namespace Gui;
using namespace Gui::Shell;

namespace
{

struct Theme
{
    bool dark;
    QString text, secondary, accent, hover, pressed, field, fieldBorder, separator;
};

Theme theme()
{
    if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark) {
        return {true, "#F5F5F7", "rgba(235,235,245,0.6)", "#0A84FF", "rgba(255,255,255,0.10)",
                "rgba(255,255,255,0.18)", "rgba(255,255,255,0.08)", "rgba(255,255,255,0.12)",
                "rgba(255,255,255,0.14)"};
    }
    return {false, "#1D1D1F", "rgba(60,60,67,0.6)", "#007AFF", "rgba(0,0,0,0.06)",
            "rgba(0,0,0,0.12)", "rgba(255,255,255,0.65)", "rgba(0,0,0,0.08)", "rgba(0,0,0,0.10)"};
}

QString styleSheet(const Theme& t)
{
    return QStringLiteral(R"(
* { color: %1; }
QToolButton#GlassButton { border: none; border-radius: 10px; background: transparent; }
QToolButton#GlassButton:hover { background: %4; }
QToolButton#GlassButton:pressed { background: %5; }
QToolButton#GlassButton:disabled { background: transparent; }
QFrame#GlassSeparator { background: %8; border: none; }
#GlassContent, #GlassContent QWidget { background: transparent; }
#GlassContent QAbstractScrollArea { border: none; }
#GlassContent QLineEdit, #GlassContent QAbstractSpinBox, #GlassContent QComboBox {
    background: %6; border: 1px solid %7; border-radius: 7px; padding: 3px 6px; min-height: 20px;
}
#GlassContent QLineEdit:focus, #GlassContent QAbstractSpinBox:focus { border: 2px solid %3; }
#GlassContent QPushButton {
    background: %6; border: 1px solid %7; border-radius: 7px; padding: 5px 12px;
}
#GlassContent QPushButton:hover { background: %4; }
#GlassContent QPushButton:default { background: %3; color: white; border: none; }
#GlassContent QTreeView::item { min-height: 26px; border-radius: 6px; }
#GlassContent QTreeView::item:hover { background: %4; }
#GlassContent QTreeView::item:selected { background: %3; color: white; }
#GlassContent QHeaderView::section {
    background: transparent; border: none; color: %2; font-weight: 600; padding: 4px 6px;
}
#GlassContent QTabWidget::pane { border: none; }
#GlassContent QTabBar::tab {
    background: transparent; border: none; border-radius: 7px; padding: 5px 12px; margin: 2px; color: %2;
}
#GlassContent QTabBar::tab:selected { background: %6; color: %1; }
#GlassContent QScrollBar:vertical { background: transparent; width: 8px; margin: 2px; }
#GlassContent QScrollBar:horizontal { background: transparent; height: 8px; margin: 2px; }
#GlassContent QScrollBar::handle { background: %5; border-radius: 3px; min-height: 24px; min-width: 24px; }
#GlassContent QScrollBar::add-line, #GlassContent QScrollBar::sub-line { width: 0; height: 0; }
#GlassContent QScrollBar::add-page, #GlassContent QScrollBar::sub-page { background: transparent; }
#GlassContent QSplitter::handle { background: %8; height: 1px; }
QToolTip { background: %6; color: %1; border: 1px solid %7; border-radius: 6px; padding: 4px 8px; }
)")
        .arg(t.text, t.secondary, t.accent, t.hover, t.pressed, t.field, t.fieldBorder, t.separator);
}

void applyTheme()
{
    const Theme t = theme();
    if (QFontDatabase::families().contains(QStringLiteral("Inter"))) {
        QFont font(QStringLiteral("Inter"));
        font.setPixelSize(13);
        QApplication::setFont(font);
    }
    qApp->setStyleSheet(styleSheet(t));

    // 3D-Hintergrund: ruhiger Verlauf passend zum Theme (Farben als 0xRRGGBBAA)
    auto view = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/View");
    view->SetBool("RadialGradient", false);
    view->SetBool("UseBackgroundColorMid", false);
    view->SetUnsigned("BackgroundColor2", t.dark ? 0x2A2C31FFUL : 0xF4F5F7FFUL);
    view->SetUnsigned("BackgroundColor3", t.dark ? 0x111214FFUL : 0xD5D9E0FFUL);
    view->SetBool("Gradient", true);
    view->SetUnsigned("DefaultShapeColor", t.dark ? 0x9EA3ADFFUL : 0xC8CCD4FFUL);
    view->SetUnsigned("DefaultShapeLineColor", t.dark ? 0x2A2D33FFUL : 0x6B717CFFUL);
    view->SetInt("DefaultShapeLineWidth", 1);
}

/// Bunte FreeCAD-Icons neutral einfärben, Schattierung bleibt erhalten.
/// ponytail: Übergang bis zum eigenen Icon-Set (Phase 3)
QIcon neutralIcon(const QIcon& icon, bool dark)
{
    QIcon out;
    for (int s : {22, 44}) {
        QImage img = icon.pixmap(s, s).toImage().convertToFormat(QImage::Format_ARGB32);
        for (int y = 0; y < img.height(); ++y) {
            auto line = reinterpret_cast<QRgb*>(img.scanLine(y));
            for (int x = 0; x < img.width(); ++x) {
                const QRgb c = line[x];
                const double lum = (0.299 * qRed(c) + 0.587 * qGreen(c) + 0.114 * qBlue(c)) / 255.0;
                const int g = dark ? int(120 + lum * 135) : int(35 + lum * 165);
                line[x] = qRgba(g, g, g, qAlpha(c));
            }
        }
        out.addPixmap(QPixmap::fromImage(img));
        // Deaktiviert: deutlich blasser, damit man sieht, was gerade nicht anklickbar ist
        QImage faded = img;
        for (int y = 0; y < faded.height(); ++y) {
            auto line = reinterpret_cast<QRgb*>(faded.scanLine(y));
            for (int x = 0; x < faded.width(); ++x) {
                line[x] = qRgba(qRed(line[x]), qGreen(line[x]), qBlue(line[x]), qAlpha(line[x]) * 3 / 10);
            }
        }
        out.addPixmap(QPixmap::fromImage(faded), QIcon::Disabled);
    }
    return out;
}

QWidget* content()
{
    auto w = new QWidget;
    w->setObjectName(QStringLiteral("GlassContent"));
    return w;
}

/// Kapsel-Toolbar mit Befehls-Buttons. "" = Trenner.
QWidget* toolbar(const std::vector<const char*>& commands)
{
    static QWidget sink;  // Command::addTo legt die QAction erst beim ersten Einfügen an
    auto& mgr = Application::Instance->commandManager();
    const bool dark = theme().dark;

    auto w = content();
    auto lay = new QHBoxLayout(w);
    lay->setContentsMargins(10, 6, 10, 6);
    lay->setSpacing(2);
    for (const char* name : commands) {
        if (!*name) {
            auto sep = new QFrame;
            sep->setObjectName(QStringLiteral("GlassSeparator"));
            sep->setFixedSize(1, 22);
            lay->addSpacing(6);
            lay->addWidget(sep);
            lay->addSpacing(6);
            continue;
        }
        Command* cmd = mgr.getCommandByName(name);
        if (!cmd) {
            continue;
        }
        if (!cmd->getAction()) {
            cmd->addTo(&sink);
        }
        QAction* action = cmd->getAction()->action();
        auto btn = new QToolButton;
        btn->setObjectName(QStringLiteral("GlassButton"));
        btn->setIcon(neutralIcon(action->icon(), dark));
        btn->setIconSize(QSize(22, 22));
        btn->setFixedSize(38, 38);
        btn->setToolTip(action->toolTip().isEmpty() ? action->text() : action->toolTip());
        btn->setEnabled(action->isEnabled());
        // Erst nach dem Mausklick auslösen: Befehle bauen die Oberfläche um (neue Ansicht, Dialog, Edit-Modus),
        // während Qt den Klick noch an das Proxy-Widget weiterreicht. Synchron führte das zum Absturz.
        QObject::connect(btn, &QToolButton::clicked, action, [action] {
            QTimer::singleShot(0, action, &QAction::trigger);
        });
        QObject::connect(action, &QAction::changed, btn, [btn, action] {
            btn->setEnabled(action->isEnabled());
        });
        lay->addWidget(btn);
    }
    w->adjustSize();
    return w;
}

/// FreeCAD-Dock-Fenster (Baum, Aufgaben) aus dem Dock lösen, damit es in ein Glass-Panel kann.
QWidget* takeDockWindow(const char* name)
{
    auto mgr = DockWindowManager::instance();
    QWidget* w = mgr->findRegisteredDockWindow(name);
    if (!w) {
        return nullptr;
    }
    w->setProperty("mycadEmbedded", true);  // DockWindowManager::setup dockt es dann nicht wieder an
    mgr->removeDockWindow(w);
    w->setParent(nullptr);

    auto box = content();
    auto lay = new QVBoxLayout(box);
    lay->setContentsMargins(8, 8, 8, 8);
    lay->addWidget(w);
    w->show();
    for (auto area : box->findChildren<QAbstractScrollArea*>()) {
        area->setFrameShape(QFrame::NoFrame);
        area->viewport()->setAutoFillBackground(false);
    }
    return box;
}

struct State
{
    GlassPanel* modelBar = nullptr;
    GlassPanel* sketchBar = nullptr;
    GlassPanel* browser = nullptr;
    GlassPanel* inspector = nullptr;
    bool sketchMode = false;
    QGraphicsScene* scene = nullptr;
} state;

std::vector<GlassPanel*> panels()
{
    std::vector<GlassPanel*> all;
    for (auto p : {state.modelBar, state.sketchBar, state.browser, state.inspector}) {
        if (p) {
            all.push_back(p);
        }
    }
    return all;
}

void layout()
{
    if (!state.scene) {
        return;
    }
    const QRectF r = state.scene->sceneRect();
    const qreal m = 12;
    GlassPanel* bar = state.sketchMode ? state.sketchBar : state.modelBar;
    state.modelBar->setVisible(!state.sketchMode);
    state.sketchBar->setVisible(state.sketchMode);
    const QSizeF bs = bar->content()->sizeHint();
    bar->setGeometry(QRectF(r.center().x() - bs.width() / 2, m, bs.width(), bs.height()));

    const qreal top = m + bs.height() + m;
    if (state.browser) {
        state.browser->setGeometry(QRectF(m, top, 290, r.height() - top - m));
    }
    if (state.inspector) {
        const qreal itop = 150;  // unter dem ViewCube
        state.inspector->setVisible(Control().activeDialog() != nullptr);
        state.inspector->setGeometry(QRectF(r.width() - 340 - m, itop, 340, r.height() - itop - m));
    }
}

void attach(View3DInventor* view)
{
    QGraphicsScene* scene = view->getViewer()->scene();
    if (scene == state.scene) {
        return;
    }
    state.scene = scene;
    for (auto p : panels()) {
        scene->addItem(p);  // entfernt es automatisch aus der vorherigen Szene
    }
    if (!scene->property("mycadShell").toBool()) {
        scene->setProperty("mycadShell", true);
        QObject::connect(scene, &QGraphicsScene::sceneRectChanged, scene, [scene] {
            if (scene == state.scene) {
                layout();
            }
        });
        QObject::connect(scene, &QObject::destroyed, [scene] {
            if (scene == state.scene) {
                state.scene = nullptr;
            }
        });
    }
    layout();
}

void addActionsRecursive(QWidget* target, const QList<QAction*>& actions)
{
    for (auto a : actions) {
        if (a->menu()) {
            addActionsRecursive(target, a->menu()->actions());
        }
        else if (!a->isSeparator()) {
            target->addAction(a);
        }
    }
}

/// Menüs, Toolbars, Statusleiste und Docks ausblenden. Ihre Tastenkürzel bleiben über das Hauptfenster aktiv.
void hideChrome()
{
    MainWindow* mw = getMainWindow();
    addActionsRecursive(mw, mw->menuBar()->actions());
    mw->menuBar()->hide();
    mw->statusBar()->hide();
    for (auto tb : mw->findChildren<QToolBar*>()) {
        addActionsRecursive(mw, tb->actions());
        tb->hide();
    }
    for (auto dw : mw->findChildren<QDockWidget*>()) {
        dw->hide();
    }
}

void hideChromeLater()
{
    QTimer::singleShot(0, hideChrome);
}

}  // namespace

void Gui::Shell::install()
{
    applyTheme();

    state.modelBar = new GlassPanel(
        toolbar({"Std_New", "Std_Open", "Std_Save", "", "Std_Undo", "Std_Redo", "",
                 "PartDesign_Body", "PartDesign_NewSketch", "", "PartDesign_Pad", "PartDesign_Pocket",
                 "PartDesign_Revolution", "PartDesign_Groove", "PartDesign_AdditiveLoft",
                 "PartDesign_AdditivePipe", "PartDesign_Hole", "", "PartDesign_Fillet",
                 "PartDesign_Chamfer", "PartDesign_Thickness", "PartDesign_Mirrored",
                 "PartDesign_LinearPattern", "PartDesign_PolarPattern", "", "Std_ViewFitAll"}),
        24);
    state.sketchBar = new GlassPanel(
        toolbar({"Sketcher_CreateLine", "Sketcher_CreatePolyline", "Sketcher_CreateRectangle",
                 "Sketcher_CreateCircle", "Sketcher_CreateArc", "Sketcher_CreateSlot",
                 "Sketcher_CompCreateRegularPolygon", "Sketcher_CreateBSpline", "Sketcher_CreatePoint", "",
                 "Sketcher_CreateFillet", "Sketcher_Trimming", "Sketcher_Extend", "Sketcher_Split",
                 "Sketcher_ToggleConstruction", "", "Sketcher_Dimension",
                 "Sketcher_ConstrainCoincidentUnified", "Sketcher_ConstrainHorizontal",
                 "Sketcher_ConstrainVertical", "Sketcher_ConstrainParallel",
                 "Sketcher_ConstrainPerpendicular", "Sketcher_ConstrainTangent", "Sketcher_ConstrainEqual",
                 "Sketcher_ConstrainSymmetric", "Sketcher_ConstrainBlock", "", "Sketcher_LeaveSketch"}),
        24);
    if (QWidget* tree = takeDockWindow("Std_ComboView")) {
        state.browser = new GlassPanel(tree, 20);
    }
    if (QWidget* tasks = takeDockWindow("Std_TaskView")) {
        state.inspector = new GlassPanel(tasks, 20);
    }

    hideChrome();
    Application::Instance->signalActivateWorkbench.connect([](const char*) { hideChromeLater(); });
    Application::Instance->signalInEdit.connect([](const ViewProviderDocumentObject&) {
        state.sketchMode = true;  // ponytail: jeder Edit-Modus gilt als Sketch; reicht, solange nur Skizzen editiert werden
        hideChromeLater();
        QTimer::singleShot(0, layout);
    });
    Application::Instance->signalResetEdit.connect([](const ViewProviderDocumentObject&) {
        state.sketchMode = false;
        hideChromeLater();
        QTimer::singleShot(0, layout);
    });

    QMdiArea* mdi = getMainWindow()->getMdiArea();
    QObject::connect(mdi, &QMdiArea::subWindowActivated, mdi, [](QMdiSubWindow* sub) {
        // Panels nicht mitten in einem Event in eine andere Szene umziehen
        QPointer<View3DInventor> view = sub ? qobject_cast<View3DInventor*>(sub->widget()) : nullptr;
        QTimer::singleShot(0, [view] {
            if (view) {
                attach(view);
            }
        });
        hideChromeLater();
    });

    // Inspector ein-/ausblenden, wenn ein Werkzeug-Dialog startet oder endet
    // ponytail: Polling, weil ControlSingleton kein Signal hat; 4 Hz reicht fürs Auge
    auto poll = new QTimer(qApp);
    QObject::connect(poll, &QTimer::timeout, [] {
        static bool active = false;
        if (active != (Control().activeDialog() != nullptr)) {
            active = !active;
            layout();
        }
    });
    poll->start(250);

    // Wie in Fusion: es ist immer ein Design offen
    QTimer::singleShot(0, [] {
        if (!App::GetApplication().getActiveDocument()) {
            Application::Instance->commandManager().runCommandByName("Std_New");
        }
    });
}
