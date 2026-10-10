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
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/Design/App/Features.h>

#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>

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

/// Dialog für alle Features im Inspector. Läuft in einer eigenen Transaktion: Abbrechen macht alles rückgängig.
/// Extrude/Revolve haben zusätzlich Operation (New Body/Join/Cut/Intersect) und Ziel-Body.
class TaskFeature: public Gui::TaskView::TaskDialog
{
public:
    TaskFeature(Design::Feature* feature, bool create, Design::Body* target)
        : feature(feature)
        , extrude(freecad_cast<Design::Extrude*>(feature))
        , revolve(freecad_cast<Design::Revolve*>(feature))
        , dressUp(freecad_cast<Design::DressUp*>(feature))
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
            distance2 = quantityBox(Base::Unit::Length, extrude->Distance2.getValue());
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
            form->addRow(QStringLiteral("Axis"), axis);
            form->addRow(QStringLiteral("Angle"), distance);
            QObject::connect(axis, &QComboBox::currentIndexChanged, [this] { apply(); });
        }
        if (auto pull = freecad_cast<Design::PressPull*>(feature)) {
            form->addRow(QStringLiteral("Faces"), new QLabel(QStringLiteral("%1 selected").arg(pull->Edges.getSize())));
            distance = quantityBox(Base::Unit::Length, pull->Distance.getValue());
            form->addRow(QStringLiteral("Distance"), distance);
        }
        else if (dressUp) {
            auto edges = new QLabel(QStringLiteral("%1 selected").arg(dressUp->Edges.getSize()));
            distance = quantityBox(Base::Unit::Length, dressUp->Size.getValue());
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
            distance2 = quantityBox(Base::Unit::Length, hole->Depth.getValue());
            check = new QCheckBox(QStringLiteral("Through all"));
            check->setChecked(hole->ThroughAll.getValue());
            headDiameter = quantityBox(Base::Unit::Length, hole->HeadDiameter.getValue());
            headDepth = quantityBox(Base::Unit::Length, hole->HeadDepth.getValue());
            sinkAngle = quantityBox(Base::Unit::Angle, hole->CountersinkAngle.getValue());
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
            dir2 = xyz(pattern->Direction2.getValue());
            count2 = count(pattern->Count2.getValue());
            distance2 = quantityBox(Base::Unit::Length, pattern->Spacing2.getValue());
            axis = xyz(pattern->Axis.getValue());
            sinkAngle = quantityBox(Base::Unit::Angle, pattern->Angle.getValue());
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
        if (check) {
            QObject::connect(check, &QCheckBox::toggled, [this] { apply(); });
        }
        if (extrude || revolve) {
            flip = new QCheckBox(QStringLiteral("Flip direction"));
            flip->setChecked(extrude ? extrude->Reversed.getValue() : revolve->Reversed.getValue());
            form->addRow(QString(), flip);
            QObject::connect(flip, &QCheckBox::toggled, [this] { apply(); });
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
        const App::PropertyLinkSub* profile = extrude ? &extrude->Profile : revolve ? &revolve->Profile : nullptr;
        if (auto profiles = profile ? freecad_cast<Design::Profiles*>(profile->getValue()) : nullptr) {
            profiles->Visibility.setValue(false);
            if (auto sketch = profiles->Sketch.getValue()) {
                sketch->Visibility.setValue(false);
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
    void setupOperation(Design::Body* target)
    {
        operation = new QComboBox;
        operation->addItems({QStringLiteral("New Body"), QStringLiteral("Join"), QStringLiteral("Cut"),
                             QStringLiteral("Intersect")});
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
                setOperation(static_cast<Design::Feature::Op>(idx), selectedBody());
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

    /// Nur im Erstell-Modus: stellt Operation und Ziel-Body um und legt bei New Body den neuen Body an.
    void setOperation(Design::Feature::Op op, Design::Body* target)
    {
        // vorherigen Ziel-Body wieder freigeben (New Body verwaltet newBody selbst)
        if (!(feature->op() == Design::Feature::Op::NewBody && newBody) && feature->BaseFeatures.getSize() > 0) {
            Design::detachFromBodies(feature);
        }

        App::Document* doc = feature->getDocument();
        if (op == Design::Feature::Op::NewBody) {
            if (!newBody) {
                const auto count = doc->getObjectsOfType(Design::Body::getClassTypeId()).size();
                newBody = static_cast<Design::Body*>(doc->addObject("Design::Body", "Body"));
                newBody->Label.setValue("Body" + std::to_string(count + 1));
                Design::folder(Design::componentOf(feature), "Bodies")->addObject(newBody);
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
        operation->setCurrentIndex(static_cast<int>(op));
        operation->blockSignals(false);
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
    return Gui::BitmapFactory().pixmap(icon);
}

bool ViewProviderFeature::doubleClicked()
{
    return Gui::Application::Instance->getDocument(getObject()->getDocument())->setEdit(this);
}

bool ViewProviderFeature::setEdit(int)
{
    auto feature = freecad_cast<Design::Feature*>(getObject());
    if (!feature || Gui::Control().activeDialog()) {
        return false;
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
