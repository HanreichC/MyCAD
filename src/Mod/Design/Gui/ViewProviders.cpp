// SPDX-License-Identifier: LGPL-2.1-or-later

#include "ViewProviders.h"

#include <App/Document.h>
#include <App/DocumentObjectGroup.h>
#include <App/Part.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/MainWindow.h>
#include <Gui/QuantitySpinBox.h>
#include <Gui/Selection/Selection.h>
#include <Gui/ViewProviderDocumentObject.h>
#include <Mod/Sketcher/App/SketchObject.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/Design/App/Features.h>

#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <cstring>
#include <regex>
#include <QLineEdit>
#include <QKeyEvent>
#include <App/ObjectIdentifier.h>
#include <App/Expression.h>
#include <App/VarSet.h>
#include <QDoubleSpinBox>
#include <QFontMetricsF>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QPainter>
#include <QPainterPath>
#include <QPointer>
#include <QStyleHints>

#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <Inventor/SbVec3f.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoFragmentShader.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoPolygonOffset.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoShaderParameter.h>
#include <Inventor/nodes/SoShaderProgram.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoVertexShader.h>
#include <QBrush>
#include <QHBoxLayout>
#include <QPixmap>
#include <QVBoxLayout>

#include <BRepAdaptor_Surface.hxx>
#include <BRepGProp.hxx>
#include <BRep_Builder.hxx>
#include <GProp_GProps.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>

#include <functional>

#include <algorithm>
#include <Gui/Shell/GlassPanel.h>
#include <Gui/Shell/Shell.h>
#include <Gui/Shell/Theme.h>

using Gui::Shell::T;

using namespace DesignGui;

PROPERTY_SOURCE(DesignGui::ViewProviderBody, PartGui::ViewProviderPartExt)

ViewProviderBody::ViewProviderBody()
{
    // Farben kommen über die View-Parameter, die Textur der Vorgabe hier. Beim Laden überschreibt die Datei beides.
    if (const char* texture = Gui::Shell::defaultBodyTexture()) {
        App::Material material = ShapeAppearance[0];
        material.imagePath = texture;
        ShapeAppearance.setValue(material);
    }
}

QIcon ViewProviderBody::getIcon() const
{
    return Gui::BitmapFactory().pixmap("PartDesign_Body");
}

namespace
{
bool printViewOn = false;

/// Muster der Druckansicht, damit nicht nur die Farbe trägt: 1 Schraffur (Überhang), 2 Punkte (Bett), 3 Kreuz (Wand).
/// Lücken zeigen den Körper darunter.
const char* const PrintVertex = R"(
#version 120
void main()
{
    gl_FrontColor = gl_Color;
    gl_Position = ftransform();
}
)";
const char* const PrintFragment = R"(
#version 120
uniform int pattern;
void main()
{
    vec2 p = gl_FragCoord.xy;
    if (pattern == 1 && mod(p.x + p.y, 9.0) >= 4.0) discard;
    if (pattern == 2 && (mod(p.x, 6.0) >= 3.0 || mod(p.y, 6.0) >= 3.0)) discard;
    if (pattern == 3 && mod(p.x + p.y, 9.0) >= 3.0 && mod(p.x - p.y, 9.0) >= 3.0) discard;
    gl_FragColor = gl_Color;
}
)";

SoSeparator* printLayer(const std::vector<Base::Vector3f>& triangles, const QColor& color, int pattern)
{
    auto sep = new SoSeparator;
    auto material = new SoMaterial;
    material->diffuseColor.setValue(float(color.redF()), float(color.greenF()), float(color.blueF()));
    sep->addChild(material);
    auto program = new SoShaderProgram;
    auto vertex = new SoVertexShader;
    vertex->sourceType = SoShaderObject::GLSL_PROGRAM;
    vertex->sourceProgram = PrintVertex;
    auto fragment = new SoFragmentShader;
    fragment->sourceType = SoShaderObject::GLSL_PROGRAM;
    fragment->sourceProgram = PrintFragment;
    auto kind = new SoShaderParameter1i;
    kind->name = "pattern";
    kind->value = pattern;
    fragment->parameter.addNode(kind);
    program->shaderObject.addNode(vertex);
    program->shaderObject.addNode(fragment);
    sep->addChild(program);
    auto coords = new SoCoordinate3;
    coords->point.setNum(int(triangles.size()));
    SbVec3f* points = coords->point.startEditing();
    for (size_t i = 0; i < triangles.size(); ++i) {
        points[i].setValue(triangles[i].x, triangles[i].y, triangles[i].z);
    }
    coords->point.finishEditing();
    sep->addChild(coords);
    auto faces = new SoFaceSet;
    faces->numVertices.setNum(int(triangles.size() / 3));
    int32_t* counts = faces->numVertices.startEditing();
    std::fill(counts, counts + triangles.size() / 3, 3);
    faces->numVertices.finishEditing();
    sep->addChild(faces);
    return sep;
}

/// Musterfeld für die Legende, wie in der Ansicht
QPixmap swatch(const QColor& color, Qt::BrushStyle style)
{
    QPixmap pix(18, 18);
    pix.fill(Qt::transparent);
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(color, 1.5));
    p.setBrush(QBrush(color, style));
    p.drawRoundedRect(QRectF(1, 1, 16, 16), 3, 3);
    return pix;
}

/// Legende der Druckansicht unten rechts in der aktiven Ansicht, mit den Knöpfen "Diese Fläche nach unten" und "Drucken"
class PrintLegend
{
public:
    void show(bool on)
    {
        auto view = qobject_cast<Gui::View3DInventor*>(Gui::getMainWindow()->activeWindow());
        Gui::View3DInventorViewer* viewer = view ? view->getViewer() : nullptr;
        if (!on || !viewer) {
            if (panel) {
                panel->hide();
            }
            timer.stop();
            return;
        }
        if (!panel) {
            build();
        }
        if (panel->scene() != viewer->scene()) {
            if (panel->scene()) {
                panel->scene()->removeItem(panel);
            }
            viewer->scene()->addItem(panel);
        }
        this->viewer = viewer;
        const auto params = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
        texts[0]->setText(T("Overhang over %1°").arg(params->GetFloat("OverhangAngle", 45)));
        texts[2]->setText(T("Wall thinner than %1 mm").arg(params->GetFloat("MinWall", 0.8)));
        place();
        panel->show();
        timer.start();
    }

private:
    void build()
    {
        const auto& theme = Gui::Shell::theme();
        auto content = new QWidget;
        content->setObjectName(QStringLiteral("PrintLegend"));
        auto lay = new QVBoxLayout(content);
        lay->setContentsMargins(14, 12, 14, 12);
        lay->setSpacing(6);
        auto title = new QLabel(T("Print View"));
        Gui::Shell::setTextStyle(title, Gui::Shell::Text::Headline);
        lay->addWidget(title);
        const std::pair<QColor, Qt::BrushStyle> rows[] = {
            {theme.red, Qt::BDiagPattern}, {theme.green, Qt::Dense5Pattern}, {theme.yellow, Qt::DiagCrossPattern}};
        for (int i = 0; i < 3; ++i) {
            auto line = new QHBoxLayout;
            auto icon = new QLabel;
            icon->setPixmap(swatch(rows[i].first, rows[i].second));
            line->addWidget(icon);
            texts[i] = new QLabel(i == 1 ? T("Lies on the bed") : QString());  // Grenzen setzt show()
            line->addWidget(texts[i], 1);
            lay->addLayout(line);
        }
        auto buttons = new QHBoxLayout;
        for (const auto& [text, command] : {std::pair {T("Choose Bottom Face"), "Design_PrintDown"},
                                            std::pair {T("Print"), "Design_Print"}}) {
            auto button = new QPushButton(text);
            button->setAutoDefault(false);
            QObject::connect(button, &QPushButton::clicked, button, [command] {
                Gui::Application::Instance->commandManager().runCommandByName(command);
            });
            buttons->addWidget(button);
        }
        lay->addLayout(buttons);
        panel = new Gui::Shell::GlassPanel(content, Gui::Shell::Token::RadiusPanel, true);
        panel->setZValue(8);
        timer.setInterval(250);  // Fenstergröße und Panels ändern sich: nachziehen
        QObject::connect(&timer, &QTimer::timeout, [this] { place(); });
    }

    void place()
    {
        if (!panel || !viewer || !panel->scene()) {
            return;
        }
        const QRectF area = panel->scene()->sceneRect();
        const QSizeF size = panel->content()->sizeHint();
        // unten rechts über der Timeline
        panel->setGeometry(QRectF(area.right() - size.width() - 24, area.bottom() - size.height() - 96, size.width(), size.height()));
    }

    Gui::Shell::GlassPanel* panel = nullptr;
    QLabel* texts[3] = {};
    QPointer<Gui::View3DInventorViewer> viewer;
    QTimer timer;
};

PrintLegend& legend()
{
    static PrintLegend l;
    return l;
}

template<class F>
void forEachBody(F f)
{
    for (App::Document* doc : App::GetApplication().getDocuments()) {
        Gui::Document* gdoc = Gui::Application::Instance->getDocument(doc);
        for (auto obj : gdoc ? doc->getObjectsOfType(Design::Body::getClassTypeId()) : std::vector<App::DocumentObject*>()) {
            if (auto vp = dynamic_cast<ViewProviderBody*>(gdoc->getViewProvider(obj))) {
                f(vp);
            }
        }
    }
}
}  // namespace

namespace
{
/// Text der Karte (übersetzt)
QString correctionText(const Design::Correction& c)
{
    const auto n = [](double v) { return QString::number(v, 'g', 6); };
    const double v = c.command.value;
    const bool round = c.body && c.element.rfind("Face", 0) == 0
        && BRepAdaptor_Surface(TopoDS::Face(c.body->Shape.getShape().getSubShape(c.element.c_str()))).GetType()
            == GeomAbs_Cylinder;
    switch (c.command.kind) {
        case RedPen::Kind::Fillet: return T("Fillet R%1 on 1 edge").arg(n(v));
        case RedPen::Kind::Chamfer: return T("Chamfer %1 mm on 1 edge").arg(n(v));
        case RedPen::Kind::Offset: return (v > 0 ? T("Pull face by %1 mm") : T("Push face by %1 mm")).arg(n(std::abs(v)));
        case RedPen::Kind::Thread: return (round ? T("Thread %1") : T("Tapped hole %1")).arg(QString::fromStdString(c.command.size));
        case RedPen::Kind::Diameter: return (round ? T("Diameter %1 mm") : T("Hole Ø%1 mm")).arg(n(v));
        case RedPen::Kind::Fit: return c.command.fit == "print" ? T("3D print fit") : T("Fit %1").arg(QString::fromStdString(c.command.fit));
        case RedPen::Kind::Pattern: return T("Pattern %1×").arg(c.command.count);
        case RedPen::Kind::Value: return T("Dimension %1 mm").arg(n(v));
        case RedPen::Kind::Remove: return T("Remove face");
        default: return QString::fromStdString(c.text);
    }
}

/// Zeigen auf eine Karte hebt ihr Ziel im Modell hervor (Vorschau, wo es wirkt)
class HoverSelect: public QObject
{
public:
    HoverSelect(QWidget* row, std::function<void(bool)> hover)
        : QObject(row)
        , hover(std::move(hover))
    {
        row->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject*, QEvent* event) override
    {
        if (event->type() == QEvent::Enter || event->type() == QEvent::Leave) {
            hover(event->type() == QEvent::Enter);
        }
        return false;
    }

private:
    std::function<void(bool)> hover;
};

class CorrectionCards
{
public:
    void show(App::Document* doc, const std::vector<Design::Correction>& list)
    {
        auto view = qobject_cast<Gui::View3DInventor*>(Gui::getMainWindow()->activeWindow());
        if (list.empty() || !view) {
            if (panel) {
                panel->hide();
            }
            return;
        }
        hidePreview();
        corrections = list;
        docName = doc->getName();
        if (!panel) {
            content = new QWidget;
            content->setObjectName(QStringLiteral("Corrections"));
            panel = new Gui::Shell::GlassPanel(content, Gui::Shell::Token::RadiusPanel, true);
            panel->setZValue(9);
        }
        delete content->layout();
        for (QWidget* w : content->findChildren<QWidget*>(Qt::FindDirectChildrenOnly)) {
            delete w;
        }
        auto lay = new QVBoxLayout(content);
        lay->setContentsMargins(14, 12, 14, 12);
        lay->setSpacing(8);
        auto title = new QLabel(T("Corrections"));
        Gui::Shell::setTextStyle(title, Gui::Shell::Text::Headline);
        lay->addWidget(title);
        rows.clear();
        for (size_t i = 0; i < corrections.size(); ++i) {
            lay->addWidget(row(i));
        }
        auto bottom = new QHBoxLayout;
        auto all = new QPushButton(T("Apply All"));
        all->setAutoDefault(false);
        QObject::connect(all, &QPushButton::clicked, all, [this] {
            if (previewing >= 0) {
                apply(size_t(previewing));  // die gezeigte zuerst übernehmen
            }
            for (size_t i = 0; i < corrections.size(); ++i) {
                apply(i);
            }
        });
        auto close = new QPushButton(T("Close"));
        close->setAutoDefault(false);
        QObject::connect(close, &QPushButton::clicked, close, [this] {
            hidePreview();
            QTimer::singleShot(0, [this] { panel->hide(); });
        });
        bottom->addWidget(all);
        bottom->addWidget(close);
        lay->addLayout(bottom);
        Gui::View3DInventorViewer* viewer = view->getViewer();
        if (panel->scene() != viewer->scene()) {
            if (panel->scene()) {
                panel->scene()->removeItem(panel);
            }
            viewer->scene()->addItem(panel);
        }
        // rechts unter dem ViewCube; neue Zeilen haben ihre Größe erst, wenn sie gezeigt sind: danach nochmal messen
        const auto place = [this, viewer] {
            const QRectF area = viewer->scene()->sceneRect();
            const QSizeF size = content->sizeHint().expandedTo(QSize(320, 0));
            panel->setGeometry(QRectF(area.right() - size.width() - 24, area.top() + 300, size.width(), size.height()));
        };
        place();
        panel->show();
        QTimer::singleShot(0, panel, place);
    }

private:
    struct Row
    {
        QLabel* status = nullptr;
        QPushButton* apply = nullptr;
        QPushButton* show = nullptr;
        QComboBox* choice = nullptr;
        bool done = false;
    };

    QWidget* row(size_t i)
    {
        const Design::Correction& c = corrections[i];
        auto w = new QWidget;
        auto lay = new QVBoxLayout(w);
        lay->setContentsMargins(0, 0, 0, 0);
        lay->setSpacing(4);
        auto line = new QHBoxLayout;
        auto text = new QLabel(QStringLiteral("%1  →  %2").arg(QString::fromStdString(c.text), correctionText(c)));
        line->addWidget(text, 1);
        Row r;
        r.apply = new QPushButton(T("Apply"));
        r.apply->setAutoDefault(false);
        r.apply->setAccessibleName(T("Apply") + QLatin1Char(' ') + QString::fromStdString(c.text));
        QObject::connect(r.apply, &QPushButton::clicked, r.apply, [this, i] { apply(i); });
        auto discard = new QPushButton(T("Discard"));
        discard->setAutoDefault(false);
        r.show = new QPushButton(T("Show"));
        r.show->setAutoDefault(false);
        r.show->setAccessibleName(T("Show") + QLatin1Char(' ') + QString::fromStdString(c.text));
        r.show->setToolTip(T("Show the result in the model; Apply keeps it"));
        QObject::connect(r.show, &QPushButton::clicked, r.show, [this, i] {
            if (previewing == int(i)) {
                hidePreview();
            }
            else {
                showPreview(i);
            }
        });
        line->addWidget(r.show);
        QObject::connect(discard, &QPushButton::clicked, discard, [this, i] {
            if (previewing == int(i)) {
                hidePreview();
            }
            rows[i].done = true;
            rows[i].show->setEnabled(false);
            rows[i].apply->setEnabled(false);
            rows[i].status->setText(T("Discarded"));
            rows[i].status->show();
        });
        line->addWidget(r.apply);
        line->addWidget(discard);
        lay->addLayout(line);
        if (!c.alternatives.empty()) {  // gleich nah: wählen statt raten, die Wahl zeigt sich im Modell
            r.choice = new QComboBox;
            r.choice->setAccessibleName(T("Which one?"));
            for (const auto& a : c.alternatives) {
                r.choice->addItem(QString::fromStdString(a));
            }
            QObject::connect(r.choice, &QComboBox::currentIndexChanged, r.choice, [this, i](int) { highlight(i, true); });
            auto pick = new QHBoxLayout;
            pick->addWidget(new QLabel(T("Which one?")));
            pick->addWidget(r.choice, 1);
            lay->addLayout(pick);
        }
        r.status = new QLabel(c.error.empty() ? QString() : T(c.error.c_str()));
        r.status->setWordWrap(true);
        r.status->setVisible(!c.error.empty());
        r.apply->setEnabled(c.error.empty());
        r.show->setEnabled(c.error.empty());
        lay->addWidget(r.status);
        rows.push_back(r);
        new HoverSelect(w, [this, i](bool on) { highlight(i, on); });
        return w;
    }

    std::string target(size_t i) const
    {
        return rows[i].choice ? rows[i].choice->currentText().toStdString() : corrections[i].element;
    }

    void highlight(size_t i, bool on)
    {
        Gui::Selection().clearSelection();
        const Design::Correction& c = corrections[i];
        if (on && c.body && c.body->isAttachedToDocument() && !target(i).empty() && target(i).find('.') == std::string::npos) {
            Gui::Selection().addSelection(docName.c_str(), c.body->getNameInDocument(), target(i).c_str());
        }
    }

    /// Vorschau: das Feature probehalber anlegen (offene Transaktion); Ausblenden nimmt es zurück, Ausführen behält es.
    /// Solange sie offen ist, speichert MyCAD nicht (Shell: keine offene Transaktion).
    void showPreview(size_t i)
    {
        hidePreview();
        App::Document* doc = App::GetApplication().getDocument(docName.c_str());
        if (!doc || rows[i].done) {
            return;
        }
        Design::Correction c = corrections[i];
        c.element = target(i);
        std::string error;
        Gui::Selection().clearSelection();
        doc->openTransaction("Red Pen");
        if (!Design::applyCorrection(c, error)) {
            doc->abortTransaction();
            rows[i].status->setText(T(error.c_str()));
            rows[i].status->show();
            return;
        }
        previewing = int(i);
        rows[i].show->setText(T("Hide"));
    }

    void hidePreview()
    {
        if (previewing < 0) {
            return;
        }
        rows[size_t(previewing)].show->setText(T("Show"));
        previewing = -1;
        if (App::Document* doc = App::GetApplication().getDocument(docName.c_str())) {
            doc->abortTransaction();
        }
    }

    void apply(size_t i)
    {
        Row& r = rows[i];
        if (r.done || !corrections[i].error.empty()) {
            return;
        }
        App::Document* doc = App::GetApplication().getDocument(docName.c_str());
        if (!doc) {
            return;
        }
        if (previewing == int(i)) {  // gezeigt: genau das behalten
            previewing = -1;
            doc->commitTransaction();
            r.done = true;
            r.apply->setEnabled(false);
            r.show->setEnabled(false);
            r.show->setText(T("Show"));
            r.status->setText(T("Done"));
            r.status->show();
            return;
        }
        hidePreview();
        Design::Correction c = corrections[i];
        c.element = target(i);
        std::string error;
        Gui::Selection().clearSelection();
        doc->openTransaction("Red Pen");
        if (Design::applyCorrection(c, error)) {
            doc->commitTransaction();
            r.done = true;
            r.apply->setEnabled(false);
            r.show->setEnabled(false);
            r.status->setText(T("Done"));
            r.status->show();
        }
        else {
            doc->abortTransaction();
            r.status->setText(T(error.c_str()));
            r.status->show();
        }
    }

    std::vector<Design::Correction> corrections;
    std::vector<Row> rows;
    int previewing = -1;  ///< Karte, deren Ergebnis gerade probehalber im Modell steht
    std::string docName;
    Gui::Shell::GlassPanel* panel = nullptr;
    QWidget* content = nullptr;
};
}  // namespace

namespace
{
std::vector<Base::Vector3f> triangles(Part::TopoShape shape)
{
    std::vector<Base::Vector3f> out;
    if (shape.isNull()) {
        return out;
    }
    std::vector<Base::Vector3d> points;
    std::vector<Data::ComplexGeoData::Facet> facets;
    shape.getFaces(points, facets, 0.05);
    for (const auto& f : facets) {
        for (uint32_t i : {f.I1, f.I2, f.I3}) {
            out.emplace_back(float(points[i].x), float(points[i].y), float(points[i].z));
        }
    }
    return out;
}

/// Geisterbild des Vergleichs in der Szene der aktiven Ansicht, mit Legende
class Comparison
{
public:
    void show(const QString& title, const Part::TopoShape& added, const Part::TopoShape& removed, const QStringList& steps)
    {
        clear();
        auto view = qobject_cast<Gui::View3DInventor*>(Gui::getMainWindow()->activeWindow());
        if (!view || (added.isNull() && removed.isNull())) {
            return;
        }
        viewer = view->getViewer();
        const auto& theme = Gui::Shell::theme();
        node = new SoSeparator;
        node->ref();
        auto pick = new SoPickStyle;
        pick->style = SoPickStyle::UNPICKABLE;
        node->addChild(pick);
        auto light = new SoLightModel;
        light->model = SoLightModel::BASE_COLOR;
        node->addChild(light);
        auto offset = new SoPolygonOffset;
        offset->factor = -2;
        offset->units = -2;
        node->addChild(offset);
        node->addChild(printLayer(triangles(added), theme.green, 2));
        node->addChild(printLayer(triangles(removed), theme.red, 1));
        if (auto root = dynamic_cast<SoGroup*>(viewer->getSceneGraph())) {
            root->addChild(node);
        }

        auto content = new QWidget;
        content->setObjectName(QStringLiteral("Comparison"));
        auto lay = new QVBoxLayout(content);
        lay->setContentsMargins(14, 12, 14, 12);
        lay->setSpacing(6);
        auto head = new QLabel(title);
        Gui::Shell::setTextStyle(head, Gui::Shell::Text::Headline);
        lay->addWidget(head);
        const std::tuple<QColor, Qt::BrushStyle, QString> rows[] = {
            {theme.green, Qt::Dense5Pattern, T("Added since then")}, {theme.red, Qt::BDiagPattern, T("Removed since then")}};
        for (const auto& [color, style, text] : rows) {
            auto line = new QHBoxLayout;
            auto icon = new QLabel;
            icon->setPixmap(swatch(color, style));
            line->addWidget(icon);
            line->addWidget(new QLabel(text), 1);
            lay->addLayout(line);
        }
        for (const QString& step : steps) {
            auto label = new QLabel(step);
            label->setWordWrap(true);
            lay->addWidget(label);
        }
        auto close = new QPushButton(T("Close"));
        close->setAutoDefault(false);
        QObject::connect(close, &QPushButton::clicked, close, [this] { QTimer::singleShot(0, [this] { clear(); }); });
        lay->addWidget(close);
        panel = new Gui::Shell::GlassPanel(content, Gui::Shell::Token::RadiusPanel, true);
        panel->setZValue(9);
        viewer->scene()->addItem(panel);
        const auto place = [this, content] {
            if (!panel || !viewer) {
                return;
            }
            const QRectF area = viewer->scene()->sceneRect();
            const QSizeF size = content->sizeHint().expandedTo(QSize(260, 0));
            panel->setGeometry(QRectF(area.right() - size.width() - 24, area.top() + 300, size.width(), size.height()));
        };
        place();
        panel->show();
        QTimer::singleShot(0, panel, place);
    }

    void clear()
    {
        if (node) {
            if (viewer) {
                if (auto root = dynamic_cast<SoGroup*>(viewer->getSceneGraph())) {
                    root->removeChild(node);
                }
            }
            node->unref();
            node = nullptr;
        }
        if (panel) {
            if (panel->scene()) {
                panel->scene()->removeItem(panel);
            }
            panel->deleteLater();
            panel = nullptr;
        }
    }

private:
    QPointer<Gui::View3DInventorViewer> viewer;
    SoSeparator* node = nullptr;
    Gui::Shell::GlassPanel* panel = nullptr;
};
}  // namespace

void DesignGui::showComparison(const QString& title, const Part::TopoShape& added, const Part::TopoShape& removed,
                               const QStringList& steps)
{
    static Comparison comparison;
    comparison.show(title, added, removed, steps);
}

void DesignGui::showCorrections(App::Document* doc, const std::vector<Design::Correction>& corrections)
{
    static CorrectionCards cards;
    cards.show(doc, corrections);
}

void DesignGui::setPrintView(bool on)
{
    printViewOn = on;
    refreshPrintView();
    legend().show(on);
}

bool DesignGui::printView()
{
    return printViewOn;
}

void DesignGui::refreshPrintView()
{
    forEachBody([](ViewProviderBody* vp) { vp->refreshPrintOverlay(); });
}

void ViewProviderBody::attach(App::DocumentObject* obj)
{
    PartGui::ViewProviderPartExt::attach(obj);
    printSwitch = new SoSwitch;
    printSwitch->whichChild = SO_SWITCH_NONE;
    pcRoot->addChild(printSwitch);
}

void ViewProviderBody::updateData(const App::Property* prop)
{
    PartGui::ViewProviderPartExt::updateData(prop);
    if (printViewOn && prop == &static_cast<Design::Body*>(getObject())->Shape) {
        refreshPrintOverlay();
    }
}

void ViewProviderBody::onChanged(const App::Property* prop)
{
    PartGui::ViewProviderPartExt::onChanged(prop);
    if (printViewOn && prop == &Visibility) {
        refreshPrintOverlay();
    }
}

void ViewProviderBody::refreshPrintOverlay()
{
    if (!printSwitch) {
        return;
    }
    printSwitch->removeAllChildren();
    printSwitch->whichChild = SO_SWITCH_NONE;
    auto body = freecad_cast<Design::Body*>(getObject());
    if (!printViewOn || !body || !isShow() || body->Shape.getShape().isNull()) {
        return;
    }
    const Design::PrintCheckResult check = Design::printCheck(body);
    const auto& theme = Gui::Shell::theme();
    auto sep = new SoSeparator;
    auto pick = new SoPickStyle;
    pick->style = SoPickStyle::UNPICKABLE;
    sep->addChild(pick);
    auto light = new SoLightModel;
    light->model = SoLightModel::BASE_COLOR;
    sep->addChild(light);
    auto offset = new SoPolygonOffset;  // vor die Fläche, die es markiert (andere Dreiecke, sonst Z-Kampf)
    offset->factor = -2;
    offset->units = -2;
    sep->addChild(offset);
    sep->addChild(printLayer(check.bed, theme.green, 2));
    sep->addChild(printLayer(check.overhang, theme.red, 1));
    sep->addChild(printLayer(check.thin, theme.yellow, 3));
    printSwitch->addChild(sep);
    printSwitch->whichChild = 0;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(DesignGui::ViewProviderProfiles, PartGui::ViewProviderPartExt)

ViewProviderProfiles::ViewProviderProfiles()
{
    ShowInTree.setValue(false);
    ShapeAppearance.setDiffuseColor(1.0F, 0.78F, 0.52F);  // helles Orange wie in Fusion, gewählt wird es blau
    Transparency.setValue(55);
}

void ViewProviderProfiles::attach(App::DocumentObject* obj)
{
    ViewProviderPartExt::attach(obj);
    DisplayMode.setValue("Shaded");  // nur Flächen, die Linien zeigt die Skizze selbst
}

void ViewProviderProfiles::finishRestoring()
{
    ViewProviderPartExt::finishRestoring();
    // ältere Dokumente: Innenflächen der Skizze fangen sonst den Klick auf die Profile ab
    auto profiles = static_cast<Design::Profiles*>(getObject());
    auto sketch = freecad_cast<Sketcher::SketchObject*>(profiles->Sketch.getValue());
    if (sketch && sketch->MakeInternals.getValue()) {
        sketch->MakeInternals.setValue(false);
    }
    if (sketch && profiles->Visibility.getValue() != sketch->Visibility.getValue()) {
        profiles->Visibility.setValue(sketch->Visibility.getValue());  // sichtbare Skizze = anklickbare Profile
    }
}

// ---------------------------------------------------------------------------------------------

namespace
{

/// Ziehpfeil im 3D-Fenster wie in Fusion: Griff an der Spitze entlang einer Achse ziehen ändert den Abstand
class DragArrow: public QGraphicsItem
{
public:
    DragArrow(Gui::View3DInventorViewer* viewer, const SbVec3f& base, const SbVec3f& dir,
              std::function<double()> get, std::function<void(double)> set)
        : viewer(viewer)
        , base(base)
        , dir(dir)
        , get(std::move(get))
        , set(std::move(set))
    {
        setZValue(5);  // unter den Glass-Panels
        setAcceptHoverEvents(true);
        viewer->scene()->addItem(this);
    }

    QRectF boundingRect() const override
    {
        return scene() ? scene()->sceneRect() : QRectF();  // zeichnet überall, greift nur am Griff
    }
    QPainterPath shape() const override
    {
        QPainterPath path;
        path.addEllipse(tip, 15, 15);
        return path;
    }

    void paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) override
    {
        if (!viewer) {
            return;
        }
        const double d = get();
        const QPointF from = viewer->toQPoint(viewer->getPointOnViewport(base));
        tip = viewer->toQPoint(viewer->getPointOnViewport(base + dir * float(d)));
        const Gui::Shell::Theme& th = Gui::Shell::theme();
        const QColor accent = th.accent;
        p->setRenderHint(QPainter::Antialiasing);
        p->setPen(QPen(accent, 2.5, Qt::SolidLine, Qt::RoundCap));
        p->drawLine(from, tip);
        p->setBrush(accent);
        p->setPen(Qt::NoPen);
        p->drawEllipse(from, 3.5, 3.5);

        // Griff: Glas-Kreis mit Pfeil in Zugrichtung
        p->setBrush(hovered || dragging ? accent : th.glassOpaqueTop);
        p->setPen(QPen(accent, 2));
        p->drawEllipse(tip, 11, 11);
        QLineF axis(from, tip);
        if (axis.length() < 1) {
            axis = QLineF(from, from + QPointF(0, -1));
        }
        QLineF unit = axis.unitVector();
        const QPointF u = (unit.p2() - unit.p1()) * (d < 0 ? -1 : 1);
        const QPointF n(-u.y(), u.x());
        QPainterPath chevron;
        chevron.moveTo(tip - u * 2.5 + n * 4);
        chevron.lineTo(tip + u * 3.5);
        chevron.lineTo(tip - u * 2.5 - n * 4);
        p->setBrush(Qt::NoBrush);
        p->setPen(QPen(hovered || dragging ? th.labelOnAccent : th.accentText, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        p->drawPath(chevron);

        // Maß-Kapsel neben dem Griff
        QFont font = Gui::Shell::textFont(Gui::Shell::Text::Caption, 600);
        font.setFeature(QFont::Tag("tnum"), 1);  // Tabellenziffern: der Wert ändert sich beim Ziehen (T-5)
        p->setFont(font);
        const QString text = QString::fromStdString(Base::Quantity(d, Base::Unit::Length).getUserString());
        const QRectF label(tip + QPointF(18, -12), QSizeF(QFontMetricsF(font).horizontalAdvance(text) + 18, 24));
        p->setPen(QPen(th.glassPopupBorder, 1));
        p->setBrush(th.glassOpaqueTop);
        p->drawRoundedRect(label, 12, 12);
        p->setPen(th.labelPrimary);
        p->drawText(label, Qt::AlignCenter, text);
    }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override
    {
        hovered = true;
        setCursor(Qt::SizeAllCursor);
        update();
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override
    {
        hovered = false;
        update();
    }
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        dragging = true;
        event->accept();
    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override
    {
        if (!dragging || !viewer) {
            return;
        }
        // Punkt auf der Zugachse, der dem Mausstrahl am nächsten liegt
        const SbVec3f onAxis = viewer->getPointOnLine(viewer->fromQPoint(event->scenePos().toPoint()), base, dir);
        const double d = std::round((onAxis - base).dot(dir) * 10.0) / 10.0;  // auf 0,1 mm rasten
        set(d);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override
    {
        dragging = false;
        update();
    }

private:
    QPointer<Gui::View3DInventorViewer> viewer;
    SbVec3f base, dir;
    std::function<double()> get;
    std::function<void(double)> set;
    QPointF tip;
    bool hovered = false;
    bool dragging = false;
};

Gui::View3DInventorViewer* activeViewer(App::Document* doc)
{
    auto gdoc = Gui::Application::Instance->getDocument(doc);
    auto view = gdoc ? dynamic_cast<Gui::View3DInventor*>(gdoc->getActiveView()) : nullptr;
    return view ? view->getViewer() : nullptr;
}

QString featureTitle(const Design::Feature* f)
{
    if (f->isDerivedFrom<Design::Revolve>()) {
        return T("Revolve");
    }
    if (f->isDerivedFrom<Design::Fillet>()) {
        return T("Fillet");
    }
    if (f->isDerivedFrom<Design::Chamfer>()) {
        return T("Chamfer");
    }
    if (f->isDerivedFrom<Design::Shell>()) {
        return T("Shell");
    }
    if (f->isDerivedFrom<Design::Combine>()) {
        return T("Combine");
    }
    if (f->isDerivedFrom<Design::Move>()) {
        return T("Move");
    }
    if (f->isDerivedFrom<Design::Mirror>()) {
        return T("Mirror");
    }
    if (f->isDerivedFrom<Design::Pattern>()) {
        return T("Pattern");
    }
    if (f->isDerivedFrom<Design::Hole>()) {
        return T("Hole");
    }
    if (f->isDerivedFrom<Design::Fitting>()) {
        return T("Fit");
    }
    if (f->isDerivedFrom<Design::Fastener>()) {
        return T("Screw Here");
    }
    if (f->isDerivedFrom<Design::PressPull>()) {
        return T("Press Pull");
    }
    if (f->isDerivedFrom<Design::Import>()) {
        return T("Insert");
    }
    if (f->isDerivedFrom<Design::Sweep>()) {
        return T("Sweep");
    }
    if (f->isDerivedFrom<Design::Loft>()) {
        return T("Loft");
    }
    if (auto primitive = freecad_cast<const Design::Primitive*>(f)) {
        return T(primitive->Type.getValueAsString());
    }
    if (f->isDerivedFrom<Design::Draft>()) {
        return T("Draft");
    }
    if (f->isDerivedFrom<Design::Scale>()) {
        return T("Scale");
    }
    if (f->isDerivedFrom<Design::Split>()) {
        return T("Split Body");
    }
    if (f->isDerivedFrom<Design::Thread>()) {
        return T("Thread");
    }
    if (f->isDerivedFrom<Design::ReplaceFace>()) {
        return T("Replace Face");
    }
    if (f->isDerivedFrom<Design::SplitFace>()) {
        return T("Split Face");
    }
    if (auto emboss = freecad_cast<const Design::Emboss*>(f)) {
        return T(emboss->Type.getValueAsString());
    }
    if (auto rib = freecad_cast<const Design::Rib*>(f)) {
        return T(rib->Mode.getValueAsString());
    }
    return T("Extrude");
}

Gui::QuantitySpinBox* quantityBox(const Base::Unit& unit, double value)
{
    auto box = new Gui::QuantitySpinBox;
    box->setUnit(unit);
    box->setRange(-1e7, 1e7);
    box->setValue(Base::Quantity(value, unit));
    return box;
}

/// Commit eines Maßfelds (Enter oder Fokus weg); true = Ereignis verbraucht
class CommitFilter: public QObject
{
public:
    std::function<bool()> commit;

protected:
    bool eventFilter(QObject*, QEvent* event) override
    {
        if (event->type() == QEvent::KeyPress) {
            const int key = static_cast<QKeyEvent*>(event)->key();
            return (key == Qt::Key_Return || key == Qt::Key_Enter) && commit();
        }
        if (event->type() == QEvent::FocusOut) {
            commit();  // Spinbox stellt danach den gültigen Wert dar
        }
        return false;
    }
};

/// Wartet im Feature-Dialog auf einen Klick auf eine Fläche, Kante oder Ebene und setzt damit einen Bezug.
/// Körperflächen werden auf den Timeline-Zustand vor diesem Feature umgehängt (sonst hinge das Feature an sich selbst).
class ReferencePicker: public Gui::SelectionObserver
{
public:
    /// context: läuft der verzögerte Abschluss erst, nachdem der Dialog zu ist, fällt er mit context weg
    ReferencePicker(Design::Feature* feature, App::PropertyLinkSub* link, QObject* context, std::function<void()> done)
        : feature(feature)
        , link(link)
        , context(context)
        , done(std::move(done))
    {
        Gui::getMainWindow()->showMessage(T("Click a face, edge or plane…"));
    }

private:
    void onSelectionChanged(const Gui::SelectionChanges& msg) override
    {
        if (msg.Type != Gui::SelectionChanges::AddSelection) {
            return;
        }
        App::DocumentObject* obj = msg.Object.getSubObject();
        std::string element = msg.Object.getOldElementName();
        if (!obj) {
            return;
        }
        // Ein Body, den dieses Feature selbst verändert: Fläche im Zustand davor suchen
        const auto& bodies = feature->Bodies.getValues();
        const auto& bases = feature->BaseFeatures.getValues();
        const auto idx = std::ranges::find(bodies, obj) - bodies.begin();
        if (idx < static_cast<long>(bases.size()) && !element.empty()) {
            auto base = freecad_cast<Design::Feature*>(bases[idx]);
            const TopoDS_Shape sub = static_cast<Design::Body*>(obj)->Shape.getShape().getSubShape(element.c_str(), true);
            const std::string name = base ? Design::elementName(base->shapeFor(obj).getShape(), sub) : std::string();
            if (name.empty()) {
                Gui::getMainWindow()->showMessage(T("Pick a face that exists before this feature"));
                return;
            }
            obj = base;
            element = name;
        }
        else {
            Design::stableRef(obj, element);
        }
        if (obj == feature) {
            return;
        }
        const App::DocumentObjectT target(obj);
        auto finish = done;
        auto property = link;
        // Nicht im Selektions-Callback rechnen; done() löscht diesen Picker
        QTimer::singleShot(0, context, [target, element, finish, property] {
            Gui::Selection().clearSelection();
            if (auto o = target.getObject()) {
                property->setValue(o, std::vector<std::string> {element});
                finish();
            }
        });
    }

    Design::Feature* feature;
    App::PropertyLinkSub* link;
    QObject* context;
    std::function<void()> done;
};

/// Dialog für alle Features im Inspector. Läuft in einer eigenen Transaktion: Abbrechen macht alles rückgängig.
/// Extrude/Revolve haben zusätzlich Operation (New Body/Join/Cut/Intersect) und Ziel-Body.
class TaskFeature: public Gui::TaskView::TaskDialog
{
public:
    TaskFeature(Design::Feature* feature, bool create, Design::Body* target)
        : feature(feature)
        , generic(hasParameters(feature))
        , extrude(freecad_cast<Design::Extrude*>(feature))
        , revolve(freecad_cast<Design::Revolve*>(feature))
        // Rundung und Fase behalten ihre Kanten- und Größenzeile, auch mit eigenen Parametern
        , dressUp(generic && !feature->isDerivedFrom<Design::Fillet>() && !feature->isDerivedFrom<Design::Chamfer>()
                      ? nullptr
                      : freecad_cast<Design::DressUp*>(feature))
        , shell(freecad_cast<Design::Shell*>(feature))
        , combine(freecad_cast<Design::Combine*>(feature))
        , move(freecad_cast<Design::Move*>(feature))
        , mirror(freecad_cast<Design::Mirror*>(feature))
        , pattern(freecad_cast<Design::Pattern*>(feature))
        , hole(freecad_cast<Design::Hole*>(feature))
        , create(create)
    {
        auto w = new QWidget;
        w->setWindowTitle(featureTitle(feature));
        form = new QFormLayout(w);
        form->setLabelAlignment(Qt::AlignRight);

        if (extrude) {
            extent = new QComboBox;
            extent->addItems({T("One Side"), T("Symmetric"), T("Two Sides"), T("To Object"), T("All")});
            extent->setCurrentIndex(extrude->Extent.getValue());
            distance = quantityBox(Base::Unit::Length, extrude->Distance.getValue());
            bindExpression(distance, &extrude->Distance);
            distance2 = quantityBox(Base::Unit::Length, extrude->Distance2.getValue());
            bindExpression(distance2, &extrude->Distance2);
            form->addRow(T("Direction"), extent);
            form->addRow(T("Distance"), distance);
            form->addRow(T("Distance 2"), distance2);
            QObject::connect(extent, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (revolve) {
            axis = new QComboBox;
            axis->addItems({T("Sketch X axis"), T("Sketch Y axis"),
                            T("X axis"), T("Y axis"), T("Z axis")});
            axis->setCurrentIndex(revolve->Axis.getValue());
            distance = quantityBox(Base::Unit::Angle, revolve->Angle.getValue());
            bindExpression(distance, &revolve->Angle);
            form->addRow(T("Axis"), axis);
            form->addRow(T("Angle"), distance);
            QObject::connect(axis, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (auto pull = freecad_cast<Design::PressPull*>(feature)) {
            form->addRow(T("Faces"), new QLabel(T("%1 selected").arg(pull->Edges.getSize())));
            distance = quantityBox(Base::Unit::Length, pull->Distance.getValue());
            bindExpression(distance, &pull->Distance);
            form->addRow(T("Distance"), distance);
        }
        else if (dressUp) {
            auto edges = new QLabel(T("%1 selected").arg(dressUp->Edges.getSize()));
            distance = quantityBox(Base::Unit::Length, dressUp->Size.getValue());
            bindExpression(distance, &dressUp->Size);
            form->addRow(shell ? T("Open faces") : T("Edges"), edges);
            form->addRow(shell                                         ? T("Thickness")
                             : feature->isDerivedFrom<Design::Fillet>() ? T("Radius")
                                                                        : T("Distance"),
                         distance);
        }
        if (shell) {
            check = new QCheckBox(T("Wall outside"));
            check->setChecked(shell->Outside.getValue());
            form->addRow(QString(), check);
        }
        if (combine) {
            simpleOp = new QComboBox;
            simpleOp->addItems({T("Join"), T("Cut"), T("Intersect")});
            simpleOp->setCurrentIndex(std::max(0L, combine->Operation.getValue() - 1));
            form->addRow(T("Tools"),
                         new QLabel(T("%1 bodies").arg(combine->ToolBodies.getSize())));
            form->addRow(T("Operation"), simpleOp);
            check = new QCheckBox(T("Keep tools"));
            check->setChecked(combine->KeepTools.getValue());
            form->addRow(QString(), check);
            QObject::connect(simpleOp, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (move) {
            const Base::Vector3d t = move->Translation.getValue();
            moveX = quantityBox(Base::Unit::Length, t.x);
            moveY = quantityBox(Base::Unit::Length, t.y);
            moveZ = quantityBox(Base::Unit::Length, t.z);
            axis = new QComboBox;
            axis->addItems({T("X axis"), T("Y axis"), T("Z axis")});
            axis->setCurrentIndex(move->RotationAxis.getValue());
            distance = quantityBox(Base::Unit::Angle, move->Angle.getValue());
            bindExpression(distance, &move->Angle);
            form->addRow(T("X distance"), moveX);
            form->addRow(T("Y distance"), moveY);
            form->addRow(T("Z distance"), moveZ);
            form->addRow(T("Rotate around"), axis);
            form->addRow(T("Angle"), distance);
            for (auto box : {moveX, moveY, moveZ}) {
                QObject::connect(box, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
            }
            QObject::connect(axis, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (mirror) {
            axis = new QComboBox;
            axis->addItems({T("XY plane"), T("XZ plane"), T("YZ plane")});
            axis->setCurrentIndex(mirror->Plane.getValue());
            form->addRow(T("Mirror plane"), axis);
            QObject::connect(axis, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (hole && generic) {
            addParameterRows();  // Norm, Größe, Art zuerst: sie bestimmen die Maße darunter
        }
        if (hole) {
            holeType = new QComboBox;
            holeType->addItems({T("Simple"), T("Counterbore"), T("Countersink")});
            holeType->setCurrentIndex(hole->HoleType.getValue());
            distance = quantityBox(Base::Unit::Length, hole->Diameter.getValue());
            bindExpression(distance, &hole->Diameter);
            distance2 = quantityBox(Base::Unit::Length, hole->Depth.getValue());
            bindExpression(distance2, &hole->Depth);
            check = new QCheckBox(T("Through all"));
            check->setChecked(hole->ThroughAll.getValue());
            headDiameter = quantityBox(Base::Unit::Length, hole->HeadDiameter.getValue());
            bindExpression(headDiameter, &hole->HeadDiameter);
            headDepth = quantityBox(Base::Unit::Length, hole->HeadDepth.getValue());
            bindExpression(headDepth, &hole->HeadDepth);
            sinkAngle = quantityBox(Base::Unit::Angle, hole->CountersinkAngle.getValue());
            bindExpression(sinkAngle, &hole->CountersinkAngle);
            flip = new QCheckBox(T("Flip direction"));
            flip->setChecked(hole->Reversed.getValue());
            form->addRow(T("Type"), holeType);
            form->addRow(T("Diameter"), distance);
            form->addRow(T("Depth"), distance2);
            form->addRow(QString(), check);
            form->addRow(T("Head diameter"), headDiameter);
            form->addRow(T("Head depth"), headDepth);
            form->addRow(T("Countersink angle"), sinkAngle);
            form->addRow(QString(), flip);
            QObject::connect(holeType, &QComboBox::currentIndexChanged, [this] { apply(); });
            QObject::connect(flip, &QCheckBox::toggled, [this] { apply(); });
            for (auto box : {headDiameter, headDepth, sinkAngle}) {
                QObject::connect(box, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
            }
        }
        if (pattern) {
            holeType = new QComboBox;
            holeType->addItems({T("Rectangular"), T("Circular"), T("Along Path")});
            holeType->setCurrentIndex(pattern->Type.getValue());
            auto xyz = [](long index) {
                auto box = new QComboBox;
                box->addItems({QStringLiteral("X"), QStringLiteral("Y"), QStringLiteral("Z")});
                box->setCurrentIndex(index);
                return box;
            };
            auto count = [](long value) {
                auto box = new QSpinBox;
                box->setRange(1, 1000);
                box->setValue(value);
                return box;
            };
            dir1 = xyz(pattern->Direction1.getValue());
            count1 = count(pattern->Count1.getValue());
            distance = quantityBox(Base::Unit::Length, pattern->Spacing1.getValue());
            bindExpression(distance, &pattern->Spacing1);
            dir2 = xyz(pattern->Direction2.getValue());
            count2 = count(pattern->Count2.getValue());
            distance2 = quantityBox(Base::Unit::Length, pattern->Spacing2.getValue());
            bindExpression(distance2, &pattern->Spacing2);
            axis = xyz(pattern->Axis.getValue());
            sinkAngle = quantityBox(Base::Unit::Angle, pattern->Angle.getValue());
            bindExpression(sinkAngle, &pattern->Angle);
            simpleOp = new QComboBox;
            simpleOp->addItems({T("Join"), T("Cut"), T("Intersect")});
            simpleOp->setCurrentIndex(std::max(0L, pattern->Operation.getValue() - 1));
            form->addRow(T("Type"), holeType);
            form->addRow(T("Direction"), dir1);
            form->addRow(T("Count"), count1);
            form->addRow(T("Spacing"), distance);
            form->addRow(T("Direction 2"), dir2);
            form->addRow(T("Count 2"), count2);
            form->addRow(T("Spacing 2"), distance2);
            form->addRow(T("Axis"), axis);
            form->addRow(T("Angle"), sinkAngle);
            form->addRow(T("Operation"), simpleOp);
            for (auto box : {holeType, dir1, dir2, axis, simpleOp}) {
                QObject::connect(box, &QComboBox::currentIndexChanged, [this] { apply(); });
            }
            for (auto box : {count1, count2}) {
                QObject::connect(box, &QSpinBox::valueChanged, [this] { apply(); });
            }
            QObject::connect(sinkAngle, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        }
        if (generic && !hole) {
            addParameterRows();
        }
        if (check) {
            QObject::connect(check, &QCheckBox::toggled, [this] { apply(); });
        }
        if (extrude || revolve) {
            flip = new QCheckBox(T("Flip direction"));
            flip->setChecked(extrude ? extrude->Reversed.getValue() : revolve->Reversed.getValue());
            form->addRow(QString(), flip);
            QObject::connect(flip, &QCheckBox::toggled, [this] { apply(); });
        }
        // Features, die Körper erzeugen: New Body / Join / Cut / Intersect und Ziel-Body
        if (extrude || revolve || feature->isDerivedFrom<Design::Sweep>() || feature->isDerivedFrom<Design::Loft>()
            || feature->isDerivedFrom<Design::Primitive>()) {
            setupOperation(target);
        }

        if (distance) {
            QObject::connect(distance, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        }
        if (distance2) {
            QObject::connect(distance2, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        }
        status = new QLabel;
        status->setWordWrap(true);
        status->setStyleSheet(QStringLiteral("color: %1;").arg(Gui::Shell::theme().red.name()));
        form->addRow(status);
        fixBox = new QWidget;  // Idee 6: ein Klick setzt den vorgeschlagenen Wert
        fixLayout = new QVBoxLayout(fixBox);
        fixLayout->setContentsMargins(0, 0, 0, 0);
        form->addRow(fixBox);
        addTaskBox(w, false);
        apply();
        createArrow();
    }

    ~TaskFeature() override
    {
        delete arrow;
    }

    QDialogButtonBox::StandardButtons getStandardButtons() const override
    {
        return QDialogButtonBox::Ok | QDialogButtonBox::Cancel;
    }

    bool accept() override
    {
        if (feature->isError()) {
            QMessageBox::warning(nullptr, featureTitle(feature), T(feature->getStatusString()));
            return false;
        }
        // Wie in Fusion: die verwendete Skizze danach ausblenden
        if (hole && hole->Sketch.getValue()) {
            hole->Sketch.getValue()->Visibility.setValue(false);
            if (auto profiles = Design::Profiles::forSketch(hole->Sketch.getValue())) {
                profiles->Visibility.setValue(false);
            }
        }
        // verwendete Profile, Pfade und Querschnitte (Extrude, Revolve, Sweep, Loft)
        std::vector<App::DocumentObject*> used;
        for (const char* name : {"Profile", "Path", "Curves"}) {  // auch Emboss (Profile)
            if (auto link = freecad_cast<App::PropertyLinkSub*>(feature->getPropertyByName(name))) {
                used.push_back(link->getValue());
            }
        }
        if (auto sections = freecad_cast<App::PropertyLinkSubList*>(feature->getPropertyByName("Sections"))) {
            for (auto obj : sections->getValues()) {
                used.push_back(obj);
            }
        }
        for (auto obj : used) {
            if (auto profiles = freecad_cast<Design::Profiles*>(obj)) {
                profiles->Visibility.setValue(false);
                obj = profiles->Sketch.getValue();
            }
            if (obj && obj->isDerivedFrom<Sketcher::SketchObject>()) {
                obj->Visibility.setValue(false);
                if (auto profiles = Design::Profiles::forSketch(obj)) {
                    profiles->Visibility.setValue(false);
                }
            }
        }
        // Combine ohne "Keep tools": Werkzeug-Bodies verschwinden wie in Fusion
        if (combine) {
            for (auto tool : combine->ToolBodies.getValues()) {
                tool->Visibility.setValue(combine->KeepTools.getValue());
            }
        }
        App::Document* doc = feature->getDocument();
        doc->commitTransaction();
        Gui::Application::Instance->getDocument(doc)->resetEdit();
        return true;
    }

    bool reject() override
    {
        App::Document* doc = feature->getDocument();
        Gui::Application::Instance->getDocument(doc)->resetEdit();
        doc->abortTransaction();
        doc->recompute();
        return true;
    }

private:
    /// Ziehpfeil für Extrude (vom Profil-Schwerpunkt entlang der Skizzennormalen) und Press Pull (Flächennormale)
    void createArrow()
    {
        Gui::View3DInventorViewer* viewer = activeViewer(feature->getDocument());
        if (!viewer || !distance) {
            return;
        }
        TopoDS_Shape faces;
        gp_Dir normal;
        if (extrude) {
            auto profiles = freecad_cast<Design::Profiles*>(extrude->Profile.getValue());
            auto sketch = profiles ? freecad_cast<Part::Feature*>(profiles->Sketch.getValue()) : nullptr;
            if (!sketch) {
                return;
            }
            const Part::TopoShape all = profiles->Shape.getShape();
            BRep_Builder builder;
            TopoDS_Compound compound;
            builder.MakeCompound(compound);
            for (const auto& sub : extrude->Profile.getSubValues()) {
                builder.Add(compound, all.getSubShape(sub.c_str(), true));
            }
            faces = extrude->Profile.getSubValues().empty() ? all.getShape() : TopoDS_Shape(compound);
            const Base::Vector3d n = sketch->Placement.getValue().getRotation().multVec(Base::Vector3d(0, 0, 1));
            normal = gp_Dir(n.x, n.y, n.z);
        }
        else if (auto pull = freecad_cast<Design::PressPull*>(feature)) {
            const auto& bases = pull->BaseFeatures.getValues();
            auto base = bases.empty() ? nullptr : freecad_cast<Design::Feature*>(bases.front());
            if (!base || pull->Edges.getSize() == 0) {
                return;
            }
            const TopoDS_Shape face = base->shapeFor(pull->Bodies.getValues().front())
                                          .getSubShape(pull->Edges.getValues().front().c_str(), true);
            if (face.IsNull() || BRepAdaptor_Surface(TopoDS::Face(face)).GetType() != GeomAbs_Plane) {
                return;
            }
            faces = face;
            normal = BRepAdaptor_Surface(TopoDS::Face(face)).Plane().Axis().Direction();
            if (face.Orientation() == TopAbs_REVERSED) {
                normal.Reverse();
            }
        }
        else {
            return;
        }
        GProp_GProps props;
        BRepGProp::SurfaceProperties(faces, props);
        const gp_Pnt c = props.CentreOfMass();
        arrow = new DragArrow(
            viewer, SbVec3f(float(c.X()), float(c.Y()), float(c.Z())),
            SbVec3f(float(normal.X()), float(normal.Y()), float(normal.Z())),
            [this] {
                const double d = distance->value().getValue();
                return extrude && flip->isChecked() ? -d : d;
            },
            [this](double d) {
                distance->setValue(Base::Quantity(extrude && flip->isChecked() ? -d : d, Base::Unit::Length));
            }
        );
        arrow->setVisible(distance->isVisibleTo(distance->parentWidget()));
    }

    void setupOperation(Design::Body* target)
    {
        operation = new QComboBox;
        operation->addItems({T("New Body"), T("Join"), T("Cut"),
                             T("Intersect")});
        if (create) {
            operation->addItem(T("New Component"));  // wie New Body, aber in einer neuen Komponente
        }
        operation->setCurrentIndex(feature->Operation.getValue());
        body = new QComboBox;
        form->addRow(T("Operation"), operation);
        bodyLabel = new QLabel(T("Body"));
        form->addRow(bodyLabel, body);

        for (auto obj : feature->getDocument()->getObjectsOfType(Design::Body::getClassTypeId())) {
            if (create || std::ranges::find(feature->Bodies.getValues(), obj) != feature->Bodies.getValues().end()) {
                body->addItem(QString::fromUtf8(obj->Label.getValue()), QString::fromLatin1(obj->getNameInDocument()));
            }
        }
        if (create) {
            setOperation(target ? Design::Feature::Op::Join : Design::Feature::Op::NewBody, target);
        }
        else {
            // Beim Bearbeiten bleibt der Ziel-Body fest; Join/Cut/Intersect lassen sich umschalten.
            body->setEnabled(false);
            operation->model()->setData(operation->model()->index(0, 0), 0, Qt::UserRole - 1);  // New Body aus
            if (feature->op() == Design::Feature::Op::NewBody) {
                operation->setEnabled(false);
            }
        }

        QObject::connect(operation, &QComboBox::currentIndexChanged, [this](int idx) {
            if (this->create) {
                const bool component = idx == NewComponentIndex;
                setOperation(component ? Design::Feature::Op::NewBody : static_cast<Design::Feature::Op>(idx),
                             selectedBody(), component);
                // Wie Fusion: Cut zeigt standardmäßig in den Körper hinein (unabhängig vom eingegebenen Abstand)
                const bool cut = static_cast<Design::Feature::Op>(idx) == Design::Feature::Op::Cut;
                if (extrude && cut != autoFlipped) {
                    autoFlipped = cut;
                    flip->blockSignals(true);
                    flip->setChecked(!flip->isChecked());
                    flip->blockSignals(false);
                }
            }
            else {
                this->feature->Operation.setValue(idx);
            }
            apply();
        });
        QObject::connect(body, &QComboBox::currentIndexChanged, [this] {
            if (this->create && this->feature->op() != Design::Feature::Op::NewBody) {
                setOperation(this->feature->op(), selectedBody());
                apply();
            }
        });
    }

    Design::Body* selectedBody() const
    {
        const QString name = body->currentData().toString();
        return freecad_cast<Design::Body*>(feature->getDocument()->getObject(name.toLatin1().constData()));
    }

    static constexpr int NewComponentIndex = 4;

    /// Nur im Erstell-Modus: stellt Operation und Ziel-Body um und legt bei New Body den neuen Body an
    /// (bei inComponent in einer neuen Komponente).
    void setOperation(Design::Feature::Op op, Design::Body* target, bool inComponent = false)
    {
        // vorherigen Ziel-Body wieder freigeben (New Body verwaltet newBody selbst)
        if (!(feature->op() == Design::Feature::Op::NewBody && newBody) && feature->BaseFeatures.getSize() > 0) {
            Design::detachFromBodies(feature);
        }

        App::Document* doc = feature->getDocument();
        // Body/Komponente passen nicht mehr zur gewünschten Variante: neu anlegen
        if (newBody && (op != Design::Feature::Op::NewBody || inComponent != (newComponent != nullptr))) {
            doc->removeObject(newBody->getNameInDocument());
            newBody = nullptr;
        }
        if (newComponent && !(op == Design::Feature::Op::NewBody && inComponent)) {
            newComponent->removeObjectsFromDocument();
            doc->removeObject(newComponent->getNameInDocument());
            newComponent = nullptr;
        }
        if (op == Design::Feature::Op::NewBody) {
            if (inComponent && !newComponent) {
                newComponent = Design::newComponent(Design::componentOf(feature));
            }
            if (!newBody) {
                newBody = Design::newBody(feature, newComponent);
            }
            else {
                feature->Bodies.setValues({newBody});
                feature->BaseFeatures.setValues({});
                newBody->Tip.setValue(feature);
            }
        }
        else {
            if (newBody) {
                doc->removeObject(newBody->getNameInDocument());
                newBody = nullptr;
            }
            if (target) {
                Design::attachToBodies(feature, {target});
                body->blockSignals(true);
                body->setCurrentIndex(body->findData(QString::fromLatin1(target->getNameInDocument())));
                body->blockSignals(false);
            }
            else {
                feature->Bodies.setValues({});
                feature->BaseFeatures.setValues({});
            }
        }
        feature->Operation.setValue(static_cast<long>(op));
        operation->blockSignals(true);
        operation->setCurrentIndex(newComponent ? NewComponentIndex : static_cast<int>(op));
        operation->blockSignals(false);
    }

    /// Maßfeld nimmt auch Ausdrücke mit Parametern an ("Width * 2"); eine Zahl mit Einheit löst den Ausdruck wieder
    void bindExpression(Gui::QuantitySpinBox* box, App::Property* prop)
    {
        auto quantity = freecad_cast<App::PropertyQuantity*>(prop);
        auto edit = box->findChild<QLineEdit*>();
        if (!quantity || !edit) {
            return;
        }
        const App::ObjectIdentifier path(*prop);
        App::Document* doc = feature->getDocument();
        auto show = [this, box, path, doc] {
            const auto info = feature->getExpression(path);
            box->setToolTip(info.expression ? QStringLiteral("= %1").arg(QString::fromStdString(
                                                  displayExpression(doc, info.expression->toString())))
                                            : QString());
        };
        show();
        auto filter = new CommitFilter;
        filter->setParent(box);
        filter->commit = [this, box, edit, quantity, path, doc, show] {
            const QString text = edit->text().trimmed();
            try {
                Base::Quantity::parse(text.toStdString());
                if (feature->getExpression(path).expression) {
                    feature->setExpression(path, nullptr);  // feste Zahl ersetzt den Ausdruck
                    show();
                }
                return false;  // normale Eingabe
            }
            catch (const Base::Exception&) {
            }
            try {
                App::ExpressionPtr expr = App::Expression::parse(feature, parameterExpression(doc, text.toStdString()));
                feature->setExpression(path, std::shared_ptr<App::Expression>(expr.release()));
                doc->recompute();
                box->setValue(quantity->getQuantityValue());
                show();
                apply();
            }
            catch (const Base::Exception& e) {
                status->setText(T("Unknown parameter or invalid expression: %1").arg(text));
            }
            return true;
        };
        edit->installEventFilter(filter);
        box->installEventFilter(filter);
    }

    /// Hat das Feature Eigenschaften in der Gruppe "Parameters"? Dann baut der Dialog seine Felder daraus.
    static bool hasParameters(Design::Feature* feature)
    {
        std::vector<App::Property*> props;
        feature->getPropertyList(props);
        return std::ranges::any_of(props, [](App::Property* p) {
            return p->getGroup() && std::strcmp(p->getGroup(), "Parameters") == 0;
        });
    }

    /// "Radius2" -> "Radius 2", "PositionX" -> "Position X"
    static QString propertyLabel(const char* name)
    {
        QString label;
        for (const QChar c : QString::fromLatin1(name)) {
            if (!label.isEmpty() && (c.isUpper() || (c.isDigit() && !label.back().isDigit()))) {
                label += QLatin1Char(' ');
            }
            label += c;
        }
        return T(label);
    }

    /// Felder für Länge, Winkel, Auswahl, Haken, Anzahl und Zahl; Sichtbarkeit folgt dem Hidden-Status
    void addParameterRows()
    {
        std::vector<App::Property*> props;
        feature->getPropertyList(props);
        for (App::Property* prop : props) {
            if (!prop->getGroup() || std::strcmp(prop->getGroup(), "Parameters") != 0) {
                continue;
            }
            const QString label = propertyLabel(prop->getName());
            QWidget* field = nullptr;
            if (auto q = freecad_cast<App::PropertyQuantity*>(prop)) {
                auto box = quantityBox(q->getUnit(), q->getValue());
                bindExpression(box, q);
                const bool positive = prop->isDerivedFrom<App::PropertyLength>();
                QObject::connect(box, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this, q, positive](double v) {
                    q->setValue(positive ? std::abs(v) : v);
                    apply();
                });
                field = box;
            }
            else if (auto e = freecad_cast<App::PropertyEnumeration*>(prop)) {
                auto box = new QComboBox;
                for (const auto& item : e->getEnumVector()) {
                    box->addItem(T(item.c_str()));
                }
                box->setCurrentIndex(e->getValue());
                QObject::connect(box, &QComboBox::currentIndexChanged, [this, e](int i) {
                    e->setValue(i);
                    apply();
                });
                field = box;
            }
            else if (auto b = freecad_cast<App::PropertyBool*>(prop)) {
                auto box = new QCheckBox(T(prop->getDocumentation()));
                box->setChecked(b->getValue());
                QObject::connect(box, &QCheckBox::toggled, [this, b](bool on) {
                    b->setValue(on);
                    apply();
                });
                form->addRow(QString(), box);
                paramRows.emplace_back(prop, box);
                continue;
            }
            else if (auto f = freecad_cast<App::PropertyFloatConstraint*>(prop)) {
                auto box = new QDoubleSpinBox;
                if (const auto* c = f->getConstraints()) {
                    box->setRange(c->LowerBound, c->UpperBound);
                    box->setSingleStep(c->StepSize);
                }
                box->setDecimals(3);
                box->setValue(f->getValue());
                QObject::connect(box, &QDoubleSpinBox::valueChanged, [this, f](double v) {
                    f->setValue(v);
                    apply();
                });
                field = box;
            }
            else if (auto n = freecad_cast<App::PropertyInteger*>(prop)) {
                auto box = new QSpinBox;
                box->setRange(1, 10000);
                box->setValue(int(n->getValue()));
                QObject::connect(box, &QSpinBox::valueChanged, [this, n](int v) {
                    n->setValue(v);
                    apply();
                });
                field = box;
            }
            else if (auto link = freecad_cast<App::PropertyLinkSub*>(prop)) {
                field = referenceButton(link);
            }
            else if (auto text = freecad_cast<App::PropertyString*>(prop)) {
                field = new QLabel(QString::fromUtf8(text->getValue()));  // Ausgabe, z. B. Spiel einer Passung
            }
            if (field) {
                form->addRow(label, field);
                paramRows.emplace_back(prop, field);
            }
        }
    }

    /// Bezugszeile: der Knopf zeigt den Bezug; gedrückt wartet er auf einen Klick auf Fläche, Kante oder Ebene.
    /// Wird die Zeile sichtbar und ist noch leer, wartet sie gleich (wie Fusion bei "To Object").
    QPushButton* referenceButton(App::PropertyLinkSub* link)
    {
        auto button = new QPushButton;
        button->setCheckable(true);
        button->setAutoDefault(false);
        const auto text = [link, button] {
            App::DocumentObject* obj = link->getValue();
            const auto& subs = link->getSubValues();
            button->setText(button->isChecked() ? T("Click a face, edge or plane…")
                            : !obj             ? T("Select")
                                               : QString::fromUtf8(obj->Label.getValue())
                                                     + (subs.empty() || subs.front().empty()
                                                            ? QString()
                                                            : QStringLiteral(" · ") + QString::fromStdString(subs.front())));
        };
        text();
        QObject::connect(button, &QPushButton::toggled, button, [this, link, button, text](bool on) {
            picker.reset();
            if (on) {
                for (auto& [other, b] : referenceButtons) {
                    if (b != button && b->isChecked()) {
                        b->setChecked(false);
                    }
                }
                Gui::Selection().clearSelection();
                picker = std::make_unique<ReferencePicker>(feature, link, button, [this, button] {
                    button->setChecked(false);
                    apply();
                });
            }
            text();
        });
        referenceButtons.emplace_back(link, button);
        return button;
    }

    void showRow(QWidget* field, bool show)
    {
        field->setVisible(show);
        if (QWidget* label = form->labelForField(field)) {
            label->setVisible(show);
        }
    }

    void apply()
    {
        if (extrude) {
            // Negativer Abstand dreht die Richtung um, wie in Fusion
            const double d = distance->value().getValue();
            extrude->Extent.setValue(extent->currentIndex());
            extrude->Distance.setValue(std::abs(d));
            extrude->Distance2.setValue(std::abs(distance2->value().getValue()));
            extrude->Reversed.setValue(flip->isChecked() != (d < 0));
            const int ext = extent->currentIndex();
            const bool byDistance = ext != Design::Extrude::ExtentToObject && ext != Design::Extrude::ExtentAll;
            showRow(distance, byDistance);
            showRow(distance2, ext == Design::Extrude::ExtentTwoSides);
            if (arrow) {
                arrow->setVisible(byDistance);  // ohne Abstand gibt es nichts zu ziehen
            }
        }
        if (revolve) {
            revolve->Axis.setValue(axis->currentIndex());
            revolve->Angle.setValue(std::abs(distance->value().getValue()));
            revolve->Reversed.setValue(flip->isChecked() != (distance->value().getValue() < 0));
        }
        if (auto pull = freecad_cast<Design::PressPull*>(feature)) {
            pull->Distance.setValue(distance->value().getValue());
        }
        else if (dressUp) {
            dressUp->Size.setValue(std::abs(distance->value().getValue()));
        }
        if (shell) {
            shell->Outside.setValue(check->isChecked());
        }
        if (combine) {
            combine->Operation.setValue(simpleOp->currentIndex() + 1L);
            combine->KeepTools.setValue(check->isChecked());
        }
        if (move) {
            move->Translation.setValue(Base::Vector3d(moveX->value().getValue(), moveY->value().getValue(),
                                                      moveZ->value().getValue()));
            move->RotationAxis.setValue(axis->currentIndex());
            axis->setEnabled(!move->AxisReference.getValue());  // eine gewählte Achse ersetzt X/Y/Z
            move->Angle.setValue(distance->value().getValue());
        }
        if (mirror) {
            mirror->Plane.setValue(axis->currentIndex());
            axis->setEnabled(!mirror->PlaneReference.getValue());  // eine gewählte Ebene ersetzt XY/XZ/YZ
        }
        if (hole) {
            const int type = holeType->currentIndex();
            hole->HoleType.setValue(type);
            hole->Depth.setValue(std::abs(distance2->value().getValue()));
            hole->ThroughAll.setValue(check->isChecked());
            hole->Reversed.setValue(flip->isChecked());
            distance2->setEnabled(!check->isChecked());
            // Maße aus der Norm (ReadOnly) zeigen, eigene Maße übernehmen
            const std::pair<App::PropertyQuantity*, Gui::QuantitySpinBox*> sized[] = {
                {&hole->Diameter, distance}, {&hole->HeadDiameter, headDiameter},
                {&hole->HeadDepth, headDepth}, {&hole->CountersinkAngle, sinkAngle}};
            for (const auto& [prop, box] : sized) {
                const bool fromStandard = prop->testStatus(App::Property::ReadOnly);
                if (fromStandard) {
                    box->blockSignals(true);
                    box->setValue(prop->getQuantityValue());
                    box->blockSignals(false);
                }
                else {
                    prop->setValue(std::abs(box->value().getValue()));
                }
                box->setEnabled(!fromStandard);
            }
            showRow(headDiameter, type != 0);
            showRow(headDepth, type == 1);
            showRow(sinkAngle, type == 2);
        }
        if (pattern) {
            const bool rect = holeType->currentIndex() == 0, circular = holeType->currentIndex() == 1;
            pattern->Type.setValue(holeType->currentIndex());
            pattern->Direction1.setValue(dir1->currentIndex());
            pattern->Count1.setValue(count1->value());
            pattern->Spacing1.setValue(std::abs(distance->value().getValue()));
            pattern->Direction2.setValue(dir2->currentIndex());
            pattern->Count2.setValue(count2->value());
            pattern->Spacing2.setValue(std::abs(distance2->value().getValue()));
            pattern->Axis.setValue(axis->currentIndex());
            pattern->Angle.setValue(std::abs(sinkAngle->value().getValue()));
            pattern->Operation.setValue(simpleOp->currentIndex() + 1L);
            for (QWidget* w : std::initializer_list<QWidget*> {dir1, dir2, count2, distance2}) {
                showRow(w, rect);
            }
            showRow(distance, !circular);  // Abstand: rechteckig und entlang Pfad
            showRow(axis, circular);
            showRow(sinkAngle, circular);
            dir1->setEnabled(!pattern->Direction1Reference.getValue());
            dir2->setEnabled(!pattern->Direction2Reference.getValue());
            axis->setEnabled(!pattern->AxisReference.getValue());
            showRow(simpleOp, pattern->SourceBodies.getSize() == 0);  // Körper-Muster: neue Bodies, keine Operation
        }
        for (const auto& [prop, field] : paramRows) {
            showRow(field, !prop->testStatus(App::Property::Hidden));
            field->setEnabled(!prop->testStatus(App::Property::ReadOnly));
            // Auswahllisten, die vom Rest abhängen (Größen einer Norm), nachladen
            auto e = freecad_cast<App::PropertyEnumeration*>(prop);
            auto box = qobject_cast<QComboBox*>(field);
            if (e && box) {
                QStringList items;
                for (const auto& item : e->getEnumVector()) {
                    items << T(item.c_str());
                }
                QStringList shown;
                for (int i = 0; i < box->count(); ++i) {
                    shown << box->itemText(i);
                }
                box->blockSignals(true);
                if (items != shown) {
                    box->clear();
                    box->addItems(items);
                }
                box->setCurrentIndex(e->getValue());
                box->blockSignals(false);
            }
        }
        for (auto& [link, button] : referenceButtons) {
            if (!link->testStatus(App::Property::Hidden) && !link->getValue() && !picker
                && !button->property("autoStarted").toBool()) {
                button->setProperty("autoStarted", true);  // nur einmal von selbst, nicht nach jedem Abbrechen
                QTimer::singleShot(0, button, [button] { button->setChecked(true); });
            }
        }
        if (generic) {  // Titel folgt z. B. dem Grundkörper-Typ
            if (auto box = form->parentWidget()) {
                box->setWindowTitle(featureTitle(feature));
            }
        }
        if (body) {
            const bool showBody = feature->op() != Design::Feature::Op::NewBody;
            body->setVisible(showBody);
            bodyLabel->setVisible(showBody);
        }

        feature->getDocument()->recompute();
        // Werte, die das Feature selbst setzt (Spiel der Passung, Länge nach Norm, Spiel aus den Einstellungen)
        for (const auto& [prop, field] : paramRows) {
            if (auto text = freecad_cast<App::PropertyString*>(prop); text && qobject_cast<QLabel*>(field)) {
                static_cast<QLabel*>(field)->setText(QString::fromUtf8(text->getValue()));
            }
            auto q = freecad_cast<App::PropertyQuantity*>(prop);
            auto box = qobject_cast<Gui::QuantitySpinBox*>(field);
            if (q && box && !box->hasFocus() && std::abs(box->rawValue() - q->getValue()) > 1e-9) {
                const QSignalBlocker block(box);
                box->setValue(q->getValue());
            }
        }
        status->setText(feature->isError() ? T(feature->getStatusString()) : QString());
        showFixes();
    }

    /// Vorschläge des Features als Knöpfe; ein Klick setzt den Wert im Feature und im Feld des Dialogs
    void showFixes()
    {
        while (QLayoutItem* item = fixLayout->takeAt(0)) {
            delete item->widget();
            delete item;
        }
        for (const auto& entry : feature->Fixes.getValues()) {
            const QStringList parts = QString::fromStdString(entry).split(QLatin1Char('\t'));
            if (parts.size() != 3) {
                continue;
            }
            auto button = new QPushButton(Gui::Shell::fixText(parts[0]));
            button->setAutoDefault(false);
            const std::string prop = parts[1].toStdString();
            const double value = parts[2].toDouble();
            QObject::connect(button, &QPushButton::clicked, fixBox, [this, prop, value] {
                QTimer::singleShot(0, fixBox, [this, prop, value] { applyFix(prop, value); });
            });
            fixLayout->addWidget(button);
        }
        fixBox->setVisible(fixLayout->count() > 0);
    }

    void applyFix(const std::string& prop, double value)
    {
        if (prop == "Size" && distance) {  // Radius, Abstand, Dicke stehen im ersten Maßfeld
            distance->setValue(Base::Quantity(value, Base::Unit::Length));
        }
        else if (prop == "Axis" && axis) {
            axis->setCurrentIndex(int(value));
        }
        else if (auto p = feature->getPropertyByName(prop.c_str())) {
            if (auto e = freecad_cast<App::PropertyEnumeration*>(p)) {
                e->setValue(long(value));
            }
            else if (auto q = freecad_cast<App::PropertyFloat*>(p)) {
                q->setValue(value);
            }
            else if (auto b = freecad_cast<App::PropertyBool*>(p)) {
                b->setValue(value != 0);
            }
        }
        apply();
    }

    Design::Feature* feature;
    bool generic;
    std::vector<std::pair<App::Property*, QWidget*>> paramRows;
    std::vector<std::pair<App::PropertyLinkSub*, QPushButton*>> referenceButtons;
    std::unique_ptr<ReferencePicker> picker;
    Design::Extrude* extrude;
    Design::Revolve* revolve;
    Design::DressUp* dressUp;
    Design::Shell* shell;
    Design::Combine* combine;
    Design::Move* move;
    Design::Mirror* mirror;
    Design::Pattern* pattern;
    Design::Hole* hole;
    bool create;
    bool autoFlipped = false;
    Design::Body* newBody = nullptr;
    App::Part* newComponent = nullptr;
    QFormLayout* form = nullptr;
    QComboBox* extent = nullptr;
    QComboBox* axis = nullptr;
    Gui::QuantitySpinBox* distance = nullptr;
    Gui::QuantitySpinBox* distance2 = nullptr;
    QCheckBox* flip = nullptr;
    QCheckBox* check = nullptr;
    QComboBox* simpleOp = nullptr;
    QComboBox* holeType = nullptr;
    QComboBox* dir1 = nullptr;
    QComboBox* dir2 = nullptr;
    QSpinBox* count1 = nullptr;
    QSpinBox* count2 = nullptr;
    Gui::QuantitySpinBox* headDiameter = nullptr;
    Gui::QuantitySpinBox* headDepth = nullptr;
    Gui::QuantitySpinBox* sinkAngle = nullptr;
    Gui::QuantitySpinBox* moveX = nullptr;
    Gui::QuantitySpinBox* moveY = nullptr;
    Gui::QuantitySpinBox* moveZ = nullptr;
    QComboBox* operation = nullptr;
    QComboBox* body = nullptr;
    QLabel* bodyLabel = nullptr;
    QLabel* status = nullptr;
    QWidget* fixBox = nullptr;
    QVBoxLayout* fixLayout = nullptr;
    DragArrow* arrow = nullptr;
};

}  // namespace

PROPERTY_SOURCE(DesignGui::ViewProviderFeature, PartGui::ViewProviderPartExt)

ViewProviderFeature::ViewProviderFeature()
{
    ShowInTree.setValue(false);
}

void ViewProviderFeature::attach(App::DocumentObject* obj)
{
    ViewProviderPartExt::attach(obj);
    Visibility.setValue(false);  // das Ergebnis zeigt der Body
}

QIcon ViewProviderFeature::getIcon() const
{
    const App::DocumentObject* obj = getObject();
    const char* icon = "PartDesign_Pad";
    if (obj->isDerivedFrom<Design::Revolve>()) {
        icon = "PartDesign_Revolution";
    }
    else if (obj->isDerivedFrom<Design::Fillet>()) {
        icon = "PartDesign_Fillet";
    }
    else if (obj->isDerivedFrom<Design::Chamfer>()) {
        icon = "PartDesign_Chamfer";
    }
    else if (obj->isDerivedFrom<Design::Shell>()) {
        icon = "PartDesign_Thickness";
    }
    else if (obj->isDerivedFrom<Design::Combine>()) {
        icon = "Part_Fuse";
    }
    else if (obj->isDerivedFrom<Design::Move>()) {
        icon = "Std_TransformManip";
    }
    else if (obj->isDerivedFrom<Design::Mirror>()) {
        icon = "PartDesign_Mirrored";
    }
    else if (obj->isDerivedFrom<Design::Pattern>()) {
        icon = static_cast<const Design::Pattern*>(obj)->Type.getValue() ? "PartDesign_PolarPattern"
                                                                          : "PartDesign_LinearPattern";
    }
    else if (obj->isDerivedFrom<Design::Hole>()) {
        icon = "PartDesign_Hole";
    }
    else if (obj->isDerivedFrom<Design::PressPull>()) {
        icon = "Part_Extrude";
    }
    else if (obj->isDerivedFrom<Design::Import>()) {
        icon = "document-open";
    }
    return Gui::BitmapFactory().pixmap(icon);
}

bool ViewProviderFeature::doubleClicked()
{
    return Gui::Application::Instance->getDocument(getObject()->getDocument())->setEdit(this);
}

bool ViewProviderFeature::setEdit(int)
{
    auto feature = freecad_cast<Design::Feature*>(getObject());
    if (!feature || feature->isDerivedFrom<Design::Import>() || feature->isDerivedFrom<Design::Split>()
        || feature->isDerivedFrom<Design::ReplaceFace>() || feature->isDerivedFrom<Design::SplitFace>()
        || Gui::Control().activeDialog()) {
        return false;  // eingefügte Geometrie und Split haben keine Einstellungen
    }
    App::Document* doc = feature->getDocument();
    if (!doc->hasPendingTransaction()) {
        doc->openTransaction("Edit " + featureTitle(feature).toStdString());
    }
    Gui::Control().showDialog(new TaskFeature(feature, createMode, defaultTarget));
    createMode = false;
    defaultTarget = nullptr;
    return true;
}

void ViewProviderFeature::unsetEdit(int)
{
    Gui::Control().closeDialog();
}

App::DocumentObject* DesignGui::parameters(App::Document* doc, bool create)
{
    App::DocumentObject* set = Design::parameterSet(doc, create);
    // wie in Fusion nur über "Change Parameters" erreichbar, nicht im Browser
    if (auto vp = set ? freecad_cast<Gui::ViewProviderDocumentObject*>(Gui::Application::Instance->getViewProvider(set))
                      : nullptr) {
        vp->ShowInTree.setValue(false);
    }
    return set;
}

namespace
{
/// Bezeichner im Text, die Parameter sind, ersetzen (nicht nach einem Punkt, also keine Objekt.Eigenschaft-Pfade)
}  // namespace

std::string DesignGui::parameterExpression(App::Document* doc, const std::string& text)
{
    return Design::toParameterExpression(doc, text);
}

std::string DesignGui::displayExpression(App::Document* doc, const std::string& text)
{
    return Design::fromParameterExpression(doc, text);
}

// ---------------------------------------------------------------------------------------------

namespace
{
/// Joint-Dialog: Typ, Winkel (Revolute/Cylindrical), Abstand (Slider/Cylindrical), Flip; wirkt sofort
class TaskJoint: public Gui::TaskView::TaskDialog
{
public:
    TaskJoint(Design::Joint* joint, bool create)
        : joint(joint)
        , create(create)
    {
        auto w = new QWidget;
        w->setWindowTitle(T("Joint"));
        form = new QFormLayout(w);
        form->setLabelAlignment(Qt::AlignRight);
        type = new QComboBox;
        for (const auto& item : joint->Type.getEnumVector()) {
            type->addItem(T(item.c_str()));
        }
        type->setCurrentIndex(joint->Type.getValue());
        form->addRow(T("Type"), type);
        QObject::connect(type, &QComboBox::currentIndexChanged, [this] { apply(); });
        // Werte des Gelenks: Felder sind sichtbar, wenn der Typ sie braucht (Joint::onChanged setzt Hidden)
        const std::pair<App::PropertyQuantity*, const char*> fields[] = {
            {&joint->Angle, "Angle"},        {&joint->Offset, "Offset"},        {&joint->Offset2, "Offset 2"},
            {&joint->Angle2, "Tilt"},       {&joint->Angle3, "Roll"},          {&joint->AngleMin, "Angle min"},
            {&joint->AngleMax, "Angle max"}, {&joint->OffsetMin, "Offset min"}, {&joint->OffsetMax, "Offset max"}};
        for (const auto& [prop, label] : fields) {
            auto box = quantityBox(prop->getUnit(), prop->getValue());
            form->addRow(T(label), box);
            boxes.emplace_back(prop, box);
            if (prop == &joint->Offset2) {  // Grenzen nach den Werten, mit ihrem Haken davor
                limited = new QCheckBox(T("Keep angle and distance within limits"));
                limited->setChecked(joint->Limited.getValue());
                QObject::connect(limited, &QCheckBox::toggled, [this] { apply(); });
            }
            QObject::connect(box, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        }
        form->insertRow(form->rowCount() - 4, QString(), limited);
        flip = new QCheckBox(T("Flip"));
        flip->setChecked(joint->Flip.getValue());
        form->addRow(QString(), flip);
        QObject::connect(flip, &QCheckBox::toggled, [this] { apply(); });
        // Bewegen: zwischen den Grenzen hin und her (ohne Grenzen eine Umdrehung bzw. 0 bis 20 mm)
        animate = new QPushButton(T("Animate"));
        animate->setCheckable(true);
        animate->setAutoDefault(false);
        collide = new QCheckBox(T("Show collisions"));
        form->addRow(QString(), animate);
        form->addRow(QString(), collide);
        timer = new QTimer(w);
        timer->setInterval(40);
        QObject::connect(timer, &QTimer::timeout, [this] { step(); });
        QObject::connect(animate, &QPushButton::toggled, [this](bool on) {
            on ? timer->start() : timer->stop();
            animate->setText(on ? T("Stop") : T("Animate"));
        });
        status = new QLabel;
        status->setWordWrap(true);
        status->setStyleSheet(QStringLiteral("color: %1;").arg(Gui::Shell::theme().red.name()));
        form->addRow(status);
        addTaskBox(w, false);
        apply();
    }
    QDialogButtonBox::StandardButtons getStandardButtons() const override
    {
        return QDialogButtonBox::Ok | QDialogButtonBox::Cancel;
    }
    bool accept() override
    {
        timer->stop();
        App::Document* doc = joint->getDocument();
        doc->commitTransaction();
        Gui::Application::Instance->getDocument(doc)->resetEdit();
        return true;
    }
    bool reject() override
    {
        timer->stop();
        App::Document* doc = joint->getDocument();
        Gui::Application::Instance->getDocument(doc)->resetEdit();
        doc->abortTransaction();
        doc->recompute();
        return true;
    }

private:
    void showRow(QWidget* field, bool show)
    {
        field->setVisible(show);
        if (QWidget* label = form->labelForField(field)) {
            label->setVisible(show);
        }
    }
    void apply()
    {
        joint->Type.setValue(type->currentIndex());
        joint->Limited.setValue(limited->isChecked());
        joint->Flip.setValue(flip->isChecked());
        for (const auto& [prop, box] : boxes) {
            prop->setValue(box->value().getValue());
        }
        const bool turns = joint->turns(), slides = joint->slides(), rigid = joint->Type.getValue() == Design::Joint::Rigid;
        for (const auto& [prop, box] : boxes) {
            bool show = !prop->testStatus(App::Property::Hidden);
            if (prop == &joint->Angle) {
                show = turns || rigid;  // Rigid: beide Werte als feste Lage
            }
            else if (prop == &joint->Offset) {
                show = slides || rigid;
            }
            showRow(box, show);
        }
        limited->setVisible(!rigid);
        animate->setVisible(!rigid);
        collide->setVisible(!rigid);
        recompute();
    }
    void recompute()
    {
        joint->getDocument()->recompute();
        QString text = joint->isError() ? T(joint->getStatusString()) : QString();
        if (collide->isChecked() && !joint->isError()) {
            if (auto moving = freecad_cast<App::Part*>(joint->Moving.getValue())) {
                const auto hits = Design::collisions(moving);
                if (!hits.empty()) {  // Farbe nie allein (C-5): als Text mit den Namen
                    text = T("Collision: %1 touches %2")
                               .arg(QString::fromUtf8(hits.front().first->Label.getValue()),
                                    QString::fromUtf8(hits.front().second->Label.getValue()));
                }
            }
        }
        status->setText(text);
    }
    /// ein Schritt der Animation: Winkel (bzw. Weg) zwischen Grenzen hin und her
    void step()
    {
        const bool turns = joint->turns();
        App::PropertyQuantity& value = turns ? static_cast<App::PropertyQuantity&>(joint->Angle) : joint->Offset;
        double lo = turns ? -180 : 0, hi = turns ? 180 : 20;
        if (joint->Limited.getValue()) {
            lo = turns ? joint->AngleMin.getValue() : joint->OffsetMin.getValue();
            hi = turns ? joint->AngleMax.getValue() : joint->OffsetMax.getValue();
        }
        const double stepSize = (turns ? 3.0 : 0.5) * direction;
        double v = value.getValue() + stepSize;
        if (v > hi || v < lo) {
            direction = -direction;
            v = std::clamp(v, std::min(lo, hi), std::max(lo, hi));
        }
        value.setValue(v);
        for (const auto& [prop, box] : boxes) {
            if (prop == &value) {
                box->blockSignals(true);
                box->setValue(Base::Quantity(v, prop->getUnit()));
                box->blockSignals(false);
            }
        }
        recompute();
    }
    Design::Joint* joint;
    bool create;
    QFormLayout* form;
    QComboBox* type;
    std::vector<std::pair<App::PropertyQuantity*, Gui::QuantitySpinBox*>> boxes;
    QCheckBox* limited = nullptr;
    QCheckBox* flip;
    QPushButton* animate;
    QCheckBox* collide;
    QTimer* timer;
    QLabel* status;
    double direction = 1;
};
}  // namespace

PROPERTY_SOURCE(DesignGui::ViewProviderNote, Gui::ViewProviderDocumentObject)

QIcon ViewProviderNote::getIcon() const
{
    return QIcon(Gui::BitmapFactory().pixmapFromSvg(":/mycad/icons/Design_Note.svg", QSize(32, 32)));
}

bool ViewProviderNote::doubleClicked()
{
    getObject()->Visibility.setValue(true);
    return true;
}

PROPERTY_SOURCE(DesignGui::ViewProviderJoint, Gui::ViewProviderDocumentObject)

QIcon ViewProviderJoint::getIcon() const
{
    return QIcon(Gui::BitmapFactory().pixmapFromSvg(":/mycad/icons/Design_Joint.svg", QSize(32, 32)));
}

bool ViewProviderJoint::doubleClicked()
{
    return Gui::Application::Instance->getDocument(getObject()->getDocument())->setEdit(this);
}

bool ViewProviderJoint::setEdit(int)
{
    auto joint = freecad_cast<Design::Joint*>(getObject());
    if (!joint || Gui::Control().activeDialog()) {
        return false;
    }
    App::Document* doc = joint->getDocument();
    if (!doc->hasPendingTransaction()) {
        doc->openTransaction("Edit Joint");
    }
    Gui::Control().showDialog(new TaskJoint(joint, createMode));
    createMode = false;
    return true;
}

void ViewProviderJoint::unsetEdit(int)
{
    Gui::Control().closeDialog();
}

// --- Idee 2: Fläche antippen, Zahl ändern ------------------------------------------------------------------------

namespace
{
/// Enter im Feld: übernehmen (Fokus weg übernimmt bewusst nicht)
class EnterFilter: public QObject
{
public:
    using QObject::QObject;
    std::function<void()> enter;

protected:
    bool eventFilter(QObject*, QEvent* event) override
    {
        if (event->type() == QEvent::KeyPress) {
            const int key = static_cast<QKeyEvent*>(event)->key();
            if (key == Qt::Key_Return || key == Qt::Key_Enter) {
                enter();
                return true;
            }
        }
        return false;
    }
};

/// Glas-Karte neben der angetippten Fläche: je treibendem Maß ein Feld. Enter rechnet neu (eine Transaktion, Strg+Z
/// nimmt sie zurück), Esc lässt den Wert stehen. Hängt ein Maß an einem Parameter, ändert sich der Parameter.
class FaceDimensions: public Gui::SelectionObserver
{
public:
    FaceDimensions()
    {
        timer.setInterval(50);  // ponytail: folgt der Kamera im Takt statt über einen Coin-Sensor
        QObject::connect(&timer, &QTimer::timeout, [this] { place(); });
    }

private:
    void onSelectionChanged(const Gui::SelectionChanges& msg) override
    {
        if (msg.Type == Gui::SelectionChanges::AddSelection || msg.Type == Gui::SelectionChanges::RmvSelection
            || msg.Type == Gui::SelectionChanges::ClrSelection || msg.Type == Gui::SelectionChanges::SetSelection) {
            QTimer::singleShot(0, [this] { refresh(); });
        }
    }

    void hide()
    {
        timer.stop();
        if (panel) {
            panel->hide();
        }
    }

    /// genau eine Körperfläche gewählt, kein Werkzeug offen: Maße zeigen
    void refresh()
    {
        hide();
        const auto sel = Gui::Selection().getSelectionEx();
        if (sel.size() != 1 || sel.front().getSubNames().size() != 1 || Gui::Control().activeDialog()) {
            return;
        }
        auto body = freecad_cast<Design::Body*>(const_cast<App::DocumentObject*>(sel.front().getObject()));
        const std::string face = sel.front().getSubNames().front();
        auto gdoc = body ? Gui::Application::Instance->getDocument(body->getDocument()) : nullptr;
        if (!body || face.rfind("Face", 0) != 0 || !gdoc || gdoc->getInEdit()) {
            return;
        }
        dims = Design::drivingDimensions(body, face);
        viewer = activeViewer(body->getDocument());
        if (dims.empty() || !viewer) {
            return;
        }
        build();
        place();
        panel->show();
        timer.start();
    }

    void build()
    {
        if (!panel) {
            content = new QWidget;
            content->setObjectName(QStringLiteral("FaceDimensions"));
            form = new QFormLayout(content);
            form->setContentsMargins(12, 10, 12, 10);
            form->setLabelAlignment(Qt::AlignRight);
            panel = new Gui::Shell::GlassPanel(content, Gui::Shell::Token::RadiusPanel, true);
            panel->setZValue(9);
        }
        if (panel->scene() != viewer->scene()) {
            viewer->scene()->addItem(panel);
        }
        while (form->rowCount() > 0) {
            form->removeRow(0);
        }
        error = new QLabel;
        error->setWordWrap(true);
        error->setStyleSheet(QStringLiteral("color: %1;").arg(Gui::Shell::theme().red.name()));
        for (size_t i = 0; i < dims.size(); ++i) {
            const auto& d = dims[i];
            auto box = quantityBox(d.angle ? Base::Unit::Angle : Base::Unit::Length, d.value);
            box->setAccessibleName(T(d.label.c_str()));
            box->setMinimumWidth(110);
            if (!d.expression.empty()) {  // Formel oder Parameter sichtbar machen
                box->setToolTip(QStringLiteral("= ") + QString::fromStdString(d.expression));
            }
            const App::DocumentObjectT owner(d.owner);
            const std::string path = d.path;
            auto commit = [this, box, owner, path] {
                auto o = owner.getObject();
                if (!o) {
                    return;
                }
                App::Document* doc = o->getDocument();
                std::string message;
                doc->openTransaction("Change Dimension");
                if (Design::setDrivingDimension(o, path, box->value().getValue(), message)) {
                    doc->commitTransaction();
                    QTimer::singleShot(0, [this] { refresh(); });  // neue Werte, Fläche kann neu heißen
                }
                else {
                    doc->abortTransaction();
                    error->setText(T(message.c_str()));
                    error->show();
                }
            };
            auto enter = new EnterFilter(box);  // nur Enter übernimmt; Verlassen des Felds ändert nichts
            enter->enter = commit;
            box->installEventFilter(enter);
            form->addRow(T(d.label.c_str()), box);
        }
        form->addRow(error);
        error->hide();
        content->adjustSize();
    }

    /// neben der Flächenmitte, im Fenster gehalten
    void place()
    {
        if (!panel || !viewer || dims.empty()) {
            return;
        }
        const Base::Vector3d& a = dims.front().anchor;
        const QPoint p = viewer->toQPoint(viewer->getPointOnViewport(SbVec3f(float(a.x), float(a.y), float(a.z))));
        const QSizeF s = content->sizeHint();
        const QRectF view = viewer->scene()->sceneRect();
        const qreal x = std::clamp<qreal>(p.x() + 24, view.left() + 12, view.right() - s.width() - 12);
        const qreal y = std::clamp<qreal>(p.y() - s.height() / 2, view.top() + 80, view.bottom() - s.height() - 80);
        panel->setGeometry(QRectF(x, y, s.width(), s.height()));
    }

    std::vector<Design::DrivingDimension> dims;
    Gui::View3DInventorViewer* viewer = nullptr;
    Gui::Shell::GlassPanel* panel = nullptr;
    QWidget* content = nullptr;
    QFormLayout* form = nullptr;
    QLabel* error = nullptr;
    QTimer timer;
};
}  // namespace

void DesignGui::startFaceDimensions()
{
    static FaceDimensions observer;
}
