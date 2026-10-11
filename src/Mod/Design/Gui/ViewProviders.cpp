// SPDX-License-Identifier: LGPL-2.1-or-later

#include "ViewProviders.h"

#include <App/Document.h>
#include <App/DocumentObjectGroup.h>
#include <App/Part.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/QuantitySpinBox.h>
#include <Gui/ViewProviderDocumentObject.h>
#include <Mod/Sketcher/App/SketchObject.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/Design/App/Features.h>

#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
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

#include <BRepAdaptor_Surface.hxx>
#include <BRepGProp.hxx>
#include <BRep_Builder.hxx>
#include <GProp_GProps.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>

#include <functional>

#include <algorithm>

using namespace DesignGui;

PROPERTY_SOURCE(DesignGui::ViewProviderBody, PartGui::ViewProviderPartExt)

QIcon ViewProviderBody::getIcon() const
{
    return Gui::BitmapFactory().pixmap("PartDesign_Body");
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(DesignGui::ViewProviderProfiles, PartGui::ViewProviderPartExt)

ViewProviderProfiles::ViewProviderProfiles()
{
    ShowInTree.setValue(false);
    ShapeAppearance.setDiffuseColor(0.55F, 0.72F, 1.0F);
    Transparency.setValue(65);
}

void ViewProviderProfiles::attach(App::DocumentObject* obj)
{
    ViewProviderPartExt::attach(obj);
    DisplayMode.setValue("Shaded");  // nur Flächen, die Linien zeigt die Skizze selbst
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
        const bool dark = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
        const QColor accent = dark ? QColor(10, 132, 255) : QColor(0, 122, 255);
        p->setRenderHint(QPainter::Antialiasing);
        p->setPen(QPen(accent, 2.5, Qt::SolidLine, Qt::RoundCap));
        p->drawLine(from, tip);
        p->setBrush(accent);
        p->setPen(Qt::NoPen);
        p->drawEllipse(from, 3.5, 3.5);

        // Griff: Glas-Kreis mit Pfeil in Zugrichtung
        p->setBrush(hovered || dragging ? accent : (dark ? QColor(44, 44, 48, 235) : QColor(255, 255, 255, 240)));
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
        p->setPen(QPen(hovered || dragging ? QColor(Qt::white) : accent, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        p->drawPath(chevron);

        // Maß-Kapsel neben dem Griff
        QFont font(QStringLiteral("Inter"));
        font.setPixelSize(12);
        font.setWeight(QFont::DemiBold);
        p->setFont(font);
        const QString text = QString::fromStdString(Base::Quantity(d, Base::Unit::Length).getUserString());
        const QRectF label(tip + QPointF(18, -12), QSizeF(QFontMetricsF(font).horizontalAdvance(text) + 18, 24));
        p->setPen(QPen(dark ? QColor(255, 255, 255, 40) : QColor(0, 0, 0, 30), 1));
        p->setBrush(dark ? QColor(44, 44, 48, 235) : QColor(255, 255, 255, 240));
        p->drawRoundedRect(label, 12, 12);
        p->setPen(dark ? QColor(245, 245, 247) : QColor(29, 29, 31));
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
        return QStringLiteral("Revolve");
    }
    if (f->isDerivedFrom<Design::Fillet>()) {
        return QStringLiteral("Fillet");
    }
    if (f->isDerivedFrom<Design::Chamfer>()) {
        return QStringLiteral("Chamfer");
    }
    if (f->isDerivedFrom<Design::Shell>()) {
        return QStringLiteral("Shell");
    }
    if (f->isDerivedFrom<Design::Combine>()) {
        return QStringLiteral("Combine");
    }
    if (f->isDerivedFrom<Design::Move>()) {
        return QStringLiteral("Move");
    }
    if (f->isDerivedFrom<Design::Mirror>()) {
        return QStringLiteral("Mirror");
    }
    if (f->isDerivedFrom<Design::Pattern>()) {
        return QStringLiteral("Pattern");
    }
    if (f->isDerivedFrom<Design::Hole>()) {
        return QStringLiteral("Hole");
    }
    if (f->isDerivedFrom<Design::PressPull>()) {
        return QStringLiteral("Press Pull");
    }
    if (f->isDerivedFrom<Design::Import>()) {
        return QStringLiteral("Insert");
    }
    if (f->isDerivedFrom<Design::Sweep>()) {
        return QStringLiteral("Sweep");
    }
    if (f->isDerivedFrom<Design::Loft>()) {
        return QStringLiteral("Loft");
    }
    if (auto primitive = freecad_cast<const Design::Primitive*>(f)) {
        return QString::fromLatin1(primitive->Type.getValueAsString());
    }
    if (f->isDerivedFrom<Design::Draft>()) {
        return QStringLiteral("Draft");
    }
    if (f->isDerivedFrom<Design::Scale>()) {
        return QStringLiteral("Scale");
    }
    if (f->isDerivedFrom<Design::Split>()) {
        return QStringLiteral("Split Body");
    }
    if (f->isDerivedFrom<Design::Thread>()) {
        return QStringLiteral("Thread");
    }
    if (auto rib = freecad_cast<const Design::Rib*>(f)) {
        return QString::fromLatin1(rib->Mode.getValueAsString());
    }
    return QStringLiteral("Extrude");
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
        , dressUp(generic ? nullptr : freecad_cast<Design::DressUp*>(feature))
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
            extent->addItems({QStringLiteral("One Side"), QStringLiteral("Symmetric"), QStringLiteral("Two Sides")});
            extent->setCurrentIndex(extrude->Extent.getValue());
            distance = quantityBox(Base::Unit::Length, extrude->Distance.getValue());
            bindExpression(distance, &extrude->Distance);
            distance2 = quantityBox(Base::Unit::Length, extrude->Distance2.getValue());
            bindExpression(distance2, &extrude->Distance2);
            form->addRow(QStringLiteral("Direction"), extent);
            form->addRow(QStringLiteral("Distance"), distance);
            form->addRow(QStringLiteral("Distance 2"), distance2);
            QObject::connect(extent, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (revolve) {
            axis = new QComboBox;
            axis->addItems({QStringLiteral("Sketch X axis"), QStringLiteral("Sketch Y axis"),
                            QStringLiteral("X axis"), QStringLiteral("Y axis"), QStringLiteral("Z axis")});
            axis->setCurrentIndex(revolve->Axis.getValue());
            distance = quantityBox(Base::Unit::Angle, revolve->Angle.getValue());
            bindExpression(distance, &revolve->Angle);
            form->addRow(QStringLiteral("Axis"), axis);
            form->addRow(QStringLiteral("Angle"), distance);
            QObject::connect(axis, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (auto pull = freecad_cast<Design::PressPull*>(feature)) {
            form->addRow(QStringLiteral("Faces"), new QLabel(QStringLiteral("%1 selected").arg(pull->Edges.getSize())));
            distance = quantityBox(Base::Unit::Length, pull->Distance.getValue());
            bindExpression(distance, &pull->Distance);
            form->addRow(QStringLiteral("Distance"), distance);
        }
        else if (dressUp) {
            auto edges = new QLabel(QStringLiteral("%1 selected").arg(dressUp->Edges.getSize()));
            distance = quantityBox(Base::Unit::Length, dressUp->Size.getValue());
            bindExpression(distance, &dressUp->Size);
            form->addRow(shell ? QStringLiteral("Open faces") : QStringLiteral("Edges"), edges);
            form->addRow(shell                                         ? QStringLiteral("Thickness")
                             : feature->isDerivedFrom<Design::Fillet>() ? QStringLiteral("Radius")
                                                                        : QStringLiteral("Distance"),
                         distance);
        }
        if (shell) {
            check = new QCheckBox(QStringLiteral("Wall outside"));
            check->setChecked(shell->Outside.getValue());
            form->addRow(QString(), check);
        }
        if (combine) {
            simpleOp = new QComboBox;
            simpleOp->addItems({QStringLiteral("Join"), QStringLiteral("Cut"), QStringLiteral("Intersect")});
            simpleOp->setCurrentIndex(std::max(0L, combine->Operation.getValue() - 1));
            form->addRow(QStringLiteral("Tools"),
                         new QLabel(QStringLiteral("%1 bodies").arg(combine->ToolBodies.getSize())));
            form->addRow(QStringLiteral("Operation"), simpleOp);
            check = new QCheckBox(QStringLiteral("Keep tools"));
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
            axis->addItems({QStringLiteral("X axis"), QStringLiteral("Y axis"), QStringLiteral("Z axis")});
            axis->setCurrentIndex(move->RotationAxis.getValue());
            distance = quantityBox(Base::Unit::Angle, move->Angle.getValue());
            bindExpression(distance, &move->Angle);
            form->addRow(QStringLiteral("X distance"), moveX);
            form->addRow(QStringLiteral("Y distance"), moveY);
            form->addRow(QStringLiteral("Z distance"), moveZ);
            form->addRow(QStringLiteral("Rotate around"), axis);
            form->addRow(QStringLiteral("Angle"), distance);
            for (auto box : {moveX, moveY, moveZ}) {
                QObject::connect(box, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
            }
            QObject::connect(axis, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (mirror) {
            axis = new QComboBox;
            axis->addItems({QStringLiteral("XY plane"), QStringLiteral("XZ plane"), QStringLiteral("YZ plane")});
            axis->setCurrentIndex(mirror->Plane.getValue());
            form->addRow(QStringLiteral("Mirror plane"), axis);
            QObject::connect(axis, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (hole) {
            holeType = new QComboBox;
            holeType->addItems({QStringLiteral("Simple"), QStringLiteral("Counterbore"), QStringLiteral("Countersink")});
            holeType->setCurrentIndex(hole->HoleType.getValue());
            distance = quantityBox(Base::Unit::Length, hole->Diameter.getValue());
            bindExpression(distance, &hole->Diameter);
            distance2 = quantityBox(Base::Unit::Length, hole->Depth.getValue());
            bindExpression(distance2, &hole->Depth);
            check = new QCheckBox(QStringLiteral("Through all"));
            check->setChecked(hole->ThroughAll.getValue());
            headDiameter = quantityBox(Base::Unit::Length, hole->HeadDiameter.getValue());
            bindExpression(headDiameter, &hole->HeadDiameter);
            headDepth = quantityBox(Base::Unit::Length, hole->HeadDepth.getValue());
            bindExpression(headDepth, &hole->HeadDepth);
            sinkAngle = quantityBox(Base::Unit::Angle, hole->CountersinkAngle.getValue());
            bindExpression(sinkAngle, &hole->CountersinkAngle);
            flip = new QCheckBox(QStringLiteral("Flip direction"));
            flip->setChecked(hole->Reversed.getValue());
            form->addRow(QStringLiteral("Type"), holeType);
            form->addRow(QStringLiteral("Diameter"), distance);
            form->addRow(QStringLiteral("Depth"), distance2);
            form->addRow(QString(), check);
            form->addRow(QStringLiteral("Head diameter"), headDiameter);
            form->addRow(QStringLiteral("Head depth"), headDepth);
            form->addRow(QStringLiteral("Countersink angle"), sinkAngle);
            form->addRow(QString(), flip);
            QObject::connect(holeType, &QComboBox::currentIndexChanged, [this] { apply(); });
            QObject::connect(flip, &QCheckBox::toggled, [this] { apply(); });
            for (auto box : {headDiameter, headDepth, sinkAngle}) {
                QObject::connect(box, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
            }
        }
        if (pattern) {
            holeType = new QComboBox;
            holeType->addItems({QStringLiteral("Rectangular"), QStringLiteral("Circular")});
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
            simpleOp->addItems({QStringLiteral("Join"), QStringLiteral("Cut"), QStringLiteral("Intersect")});
            simpleOp->setCurrentIndex(std::max(0L, pattern->Operation.getValue() - 1));
            form->addRow(QStringLiteral("Type"), holeType);
            form->addRow(QStringLiteral("Direction"), dir1);
            form->addRow(QStringLiteral("Count"), count1);
            form->addRow(QStringLiteral("Spacing"), distance);
            form->addRow(QStringLiteral("Direction 2"), dir2);
            form->addRow(QStringLiteral("Count 2"), count2);
            form->addRow(QStringLiteral("Spacing 2"), distance2);
            form->addRow(QStringLiteral("Axis"), axis);
            form->addRow(QStringLiteral("Angle"), sinkAngle);
            form->addRow(QStringLiteral("Operation"), simpleOp);
            for (auto box : {holeType, dir1, dir2, axis, simpleOp}) {
                QObject::connect(box, &QComboBox::currentIndexChanged, [this] { apply(); });
            }
            for (auto box : {count1, count2}) {
                QObject::connect(box, &QSpinBox::valueChanged, [this] { apply(); });
            }
            QObject::connect(sinkAngle, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        }
        if (generic) {
            addParameterRows();
        }
        if (check) {
            QObject::connect(check, &QCheckBox::toggled, [this] { apply(); });
        }
        if (extrude || revolve) {
            flip = new QCheckBox(QStringLiteral("Flip direction"));
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
        status->setStyleSheet(QStringLiteral("color: #FF3B30;"));
        form->addRow(status);
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
            QMessageBox::warning(nullptr, featureTitle(feature), QString::fromUtf8(feature->getStatusString()));
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
        for (const char* name : {"Profile", "Path", "Curves"}) {
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
    }

    void setupOperation(Design::Body* target)
    {
        operation = new QComboBox;
        operation->addItems({QStringLiteral("New Body"), QStringLiteral("Join"), QStringLiteral("Cut"),
                             QStringLiteral("Intersect")});
        if (create) {
            operation->addItem(QStringLiteral("New Component"));  // wie New Body, aber in einer neuen Komponente
        }
        operation->setCurrentIndex(feature->Operation.getValue());
        body = new QComboBox;
        form->addRow(QStringLiteral("Operation"), operation);
        bodyLabel = new QLabel(QStringLiteral("Body"));
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
                const auto count = doc->getObjectsOfType(Design::Body::getClassTypeId()).size();
                newBody = static_cast<Design::Body*>(doc->addObject("Design::Body", "Body"));
                newBody->Label.setValue("Body" + std::to_string(count + 1));
                Design::folder(newComponent ? newComponent : Design::componentOf(feature), "Bodies")->addObject(newBody);
            }
            feature->Bodies.setValues({newBody});
            feature->BaseFeatures.setValues({});
            newBody->Tip.setValue(feature);
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
                status->setText(QStringLiteral("Unknown parameter or invalid expression: %1").arg(text));
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
        return label;
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
                    box->addItem(QString::fromStdString(item));
                }
                box->setCurrentIndex(e->getValue());
                QObject::connect(box, &QComboBox::currentIndexChanged, [this, e](int i) {
                    e->setValue(i);
                    apply();
                });
                field = box;
            }
            else if (auto b = freecad_cast<App::PropertyBool*>(prop)) {
                auto box = new QCheckBox(QString::fromUtf8(prop->getDocumentation()));
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
            if (field) {
                form->addRow(label, field);
                paramRows.emplace_back(prop, field);
            }
        }
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
            const bool twoSides = extent->currentIndex() == 2;
            distance2->setVisible(twoSides);
            form->labelForField(distance2)->setVisible(twoSides);
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
            move->Angle.setValue(distance->value().getValue());
        }
        if (mirror) {
            mirror->Plane.setValue(axis->currentIndex());
        }
        if (hole) {
            const int type = holeType->currentIndex();
            hole->HoleType.setValue(type);
            hole->Diameter.setValue(std::abs(distance->value().getValue()));
            hole->Depth.setValue(std::abs(distance2->value().getValue()));
            hole->ThroughAll.setValue(check->isChecked());
            hole->HeadDiameter.setValue(std::abs(headDiameter->value().getValue()));
            hole->HeadDepth.setValue(std::abs(headDepth->value().getValue()));
            hole->CountersinkAngle.setValue(std::abs(sinkAngle->value().getValue()));
            hole->Reversed.setValue(flip->isChecked());
            distance2->setEnabled(!check->isChecked());
            showRow(headDiameter, type != 0);
            showRow(headDepth, type == 1);
            showRow(sinkAngle, type == 2);
        }
        if (pattern) {
            const bool rect = holeType->currentIndex() == 0;
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
            for (QWidget* w : std::initializer_list<QWidget*> {dir1, distance, dir2, count2, distance2}) {
                showRow(w, rect);
            }
            showRow(axis, !rect);
            showRow(sinkAngle, !rect);
            showRow(simpleOp, pattern->SourceBodies.getSize() == 0);  // Körper-Muster: neue Bodies, keine Operation
        }
        for (const auto& [prop, field] : paramRows) {
            showRow(field, !prop->testStatus(App::Property::Hidden));
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
        status->setText(feature->isError() ? QString::fromUtf8(feature->getStatusString()) : QString());
    }

    Design::Feature* feature;
    bool generic;
    std::vector<std::pair<App::Property*, QWidget*>> paramRows;
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
    App::Part* root = Design::root(doc, create);
    if (!root) {
        return nullptr;
    }
    for (auto obj : root->Group.getValues()) {
        if (obj->isDerivedFrom<App::VarSet>() && std::strcmp(obj->Label.getValue(), "Parameters") == 0) {
            return obj;
        }
    }
    if (!create) {
        return nullptr;
    }
    App::DocumentObject* set = doc->addObject("App::VarSet", "Parameters");
    set->Label.setValue("Parameters");
    root->addObject(set);
    // wie in Fusion nur über "Change Parameters" erreichbar, nicht im Browser
    if (auto vp = freecad_cast<Gui::ViewProviderDocumentObject*>(Gui::Application::Instance->getViewProvider(set))) {
        vp->ShowInTree.setValue(false);
    }
    return set;
}

namespace
{
/// Bezeichner im Text, die Parameter sind, ersetzen (nicht nach einem Punkt, also keine Objekt.Eigenschaft-Pfade)
std::string mapParameters(App::Document* doc, const std::string& text, bool toTable)
{
    App::DocumentObject* set = DesignGui::parameters(doc, false);
    if (!set) {
        return text;
    }
    const std::string prefix = std::string(set->getNameInDocument()) + ".";
    if (!toTable) {
        std::string out = text;
        for (size_t pos; (pos = out.find(prefix)) != std::string::npos;) {
            out.erase(pos, prefix.size());
        }
        return out;
    }
    static const std::regex word(R"([A-Za-z_]\w*)");
    std::string out;
    size_t last = 0;
    for (auto it = std::sregex_iterator(text.begin(), text.end(), word); it != std::sregex_iterator(); ++it) {
        const size_t at = it->position();
        const bool afterDot = at > 0 && text[at - 1] == '.';
        App::Property* prop = afterDot ? nullptr : set->getPropertyByName(it->str().c_str());
        out += text.substr(last, at - last);
        out += prop && prop->getGroup() && std::strcmp(prop->getGroup(), "Parameters") == 0 ? prefix + it->str()
                                                                                          : it->str();
        last = at + it->length();
    }
    return out + text.substr(last);
}
}  // namespace

std::string DesignGui::parameterExpression(App::Document* doc, const std::string& text)
{
    return mapParameters(doc, text, true);
}

std::string DesignGui::displayExpression(App::Document* doc, const std::string& text)
{
    return mapParameters(doc, text, false);
}
