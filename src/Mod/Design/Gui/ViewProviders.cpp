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
        if (dressUp) {
            auto edges = new QLabel(QStringLiteral("%1 selected").arg(dressUp->Edges.getSize()));
            distance = quantityBox(Base::Unit::Length, dressUp->Size.getValue());
            form->addRow(QStringLiteral("Edges"), edges);
            form->addRow(feature->isDerivedFrom<Design::Fillet>() ? QStringLiteral("Radius")
                                                                  : QStringLiteral("Distance"),
                         distance);
        }
        if (distance) {
            QObject::connect(distance, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        }
        if (distance2) {
            QObject::connect(distance2, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        }
        if (extrude || revolve) {
            flip = new QCheckBox(QStringLiteral("Flip direction"));
            flip->setChecked(extrude ? extrude->Reversed.getValue() : revolve->Reversed.getValue());
            form->addRow(QString(), flip);
            QObject::connect(flip, &QCheckBox::toggled, [this] { apply(); });
            setupOperation(target);
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
        const App::PropertyLinkSub* profile = extrude ? &extrude->Profile : revolve ? &revolve->Profile : nullptr;
        if (auto profiles = profile ? freecad_cast<Design::Profiles*>(profile->getValue()) : nullptr) {
            profiles->Visibility.setValue(false);
            if (auto sketch = profiles->Sketch.getValue()) {
                sketch->Visibility.setValue(false);
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
        for (auto& [b, tip] : savedTips) {
            b->Tip.setValue(tip);
        }
        savedTips.clear();

        App::Document* doc = feature->getDocument();
        if (op == Design::Feature::Op::NewBody) {
            if (!newBody) {
                const auto count = doc->getObjectsOfType(Design::Body::getClassTypeId()).size();
                newBody = static_cast<Design::Body*>(doc->addObject("Design::Body", "Body"));
                newBody->Label.setValue("Body" + std::to_string(count + 1));
                Design::folder(Design::root(doc, true), "Bodies")->addObject(newBody);
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
                savedTips[target] = target->Tip.getValue();
                feature->Bodies.setValues({target});
                feature->BaseFeatures.setValues({target->Tip.getValue()});
                target->Tip.setValue(feature);
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
        if (dressUp) {
            dressUp->Size.setValue(std::abs(distance->value().getValue()));
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
    bool create;
    bool autoFlipped = false;
    Design::Body* newBody = nullptr;
    std::map<Design::Body*, App::DocumentObject*> savedTips;
    QFormLayout* form = nullptr;
    QComboBox* extent = nullptr;
    QComboBox* axis = nullptr;
    Gui::QuantitySpinBox* distance = nullptr;
    Gui::QuantitySpinBox* distance2 = nullptr;
    QCheckBox* flip = nullptr;
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
