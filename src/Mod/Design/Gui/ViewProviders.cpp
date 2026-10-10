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

/// Extrude-Dialog im Inspector. Läuft komplett in einer eigenen Transaktion: Abbrechen macht alles rückgängig.
class TaskExtrude: public Gui::TaskView::TaskDialog
{
public:
    TaskExtrude(Design::Extrude* ext, bool create, Design::Body* target)
        : ext(ext)
        , create(create)
    {
        auto w = new QWidget;
        w->setWindowTitle(QStringLiteral("Extrude"));
        auto form = new QFormLayout(w);
        form->setLabelAlignment(Qt::AlignRight);

        extent = new QComboBox;
        extent->addItems({QStringLiteral("One Side"), QStringLiteral("Symmetric"), QStringLiteral("Two Sides")});
        distance = new Gui::QuantitySpinBox;
        distance2 = new Gui::QuantitySpinBox;
        for (auto box : {distance, distance2}) {
            box->setUnit(Base::Unit::Length);
            box->setRange(-1e7, 1e7);
        }
        flip = new QCheckBox(QStringLiteral("Flip direction"));
        operation = new QComboBox;
        operation->addItems({QStringLiteral("New Body"), QStringLiteral("Join"), QStringLiteral("Cut"),
                             QStringLiteral("Intersect")});
        body = new QComboBox;
        status = new QLabel;
        status->setWordWrap(true);
        status->setStyleSheet(QStringLiteral("color: #FF3B30;"));

        form->addRow(QStringLiteral("Direction"), extent);
        form->addRow(QStringLiteral("Distance"), distance);
        distance2Label = new QLabel(QStringLiteral("Distance 2"));
        form->addRow(distance2Label, distance2);
        form->addRow(QString(), flip);
        form->addRow(QStringLiteral("Operation"), operation);
        form->addRow(QStringLiteral("Body"), body);
        form->addRow(status);
        addTaskBox(w, false);

        extent->setCurrentIndex(ext->Extent.getValue());
        distance->setValue(Base::Quantity(ext->Distance.getValue(), Base::Unit::Length));
        distance2->setValue(Base::Quantity(ext->Distance2.getValue(), Base::Unit::Length));
        flip->setChecked(ext->Reversed.getValue());
        operation->setCurrentIndex(ext->Operation.getValue());

        for (auto obj : ext->getDocument()->getObjectsOfType(Design::Body::getClassTypeId())) {
            if (create || std::ranges::find(ext->Bodies.getValues(), obj) != ext->Bodies.getValues().end()) {
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
            if (ext->op() == Design::Feature::Op::NewBody) {
                operation->setEnabled(false);
            }
        }

        QObject::connect(extent, &QComboBox::currentIndexChanged, [this] { apply(); });
        QObject::connect(distance, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        QObject::connect(distance2, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        QObject::connect(flip, &QCheckBox::toggled, [this] { apply(); });
        QObject::connect(operation, &QComboBox::currentIndexChanged, [this](int idx) {
            if (this->create) {
                setOperation(static_cast<Design::Feature::Op>(idx), selectedBody());
                // Wie Fusion: Cut zeigt standardmäßig in den Körper hinein (unabhängig vom eingegebenen Abstand)
                const bool cut = static_cast<Design::Feature::Op>(idx) == Design::Feature::Op::Cut;
                if (cut != autoFlipped) {
                    autoFlipped = cut;
                    flip->blockSignals(true);
                    flip->setChecked(!flip->isChecked());
                    flip->blockSignals(false);
                }
            }
            else {
                this->ext->Operation.setValue(idx);
            }
            apply();
        });
        QObject::connect(body, &QComboBox::currentIndexChanged, [this] {
            if (this->create && this->ext->op() != Design::Feature::Op::NewBody) {
                setOperation(this->ext->op(), selectedBody());
                apply();
            }
        });
        apply();
    }

    QDialogButtonBox::StandardButtons getStandardButtons() const override
    {
        return QDialogButtonBox::Ok | QDialogButtonBox::Cancel;
    }

    bool accept() override
    {
        if (ext->isError()) {
            QMessageBox::warning(nullptr, QStringLiteral("Extrude"), QString::fromUtf8(ext->getStatusString()));
            return false;
        }
        // Wie in Fusion: die verwendete Skizze nach dem Extrudieren ausblenden
        if (auto profiles = freecad_cast<Design::Profiles*>(ext->Profile.getValue())) {
            profiles->Visibility.setValue(false);
            if (auto sketch = profiles->Sketch.getValue()) {
                sketch->Visibility.setValue(false);
            }
        }
        App::Document* doc = ext->getDocument();
        doc->commitTransaction();
        Gui::Application::Instance->getDocument(doc)->resetEdit();
        return true;
    }

    bool reject() override
    {
        App::Document* doc = ext->getDocument();
        Gui::Application::Instance->getDocument(doc)->resetEdit();
        doc->abortTransaction();
        doc->recompute();
        return true;
    }

private:
    Design::Body* selectedBody() const
    {
        const QString name = body->currentData().toString();
        return freecad_cast<Design::Body*>(ext->getDocument()->getObject(name.toLatin1().constData()));
    }

    /// Nur im Erstell-Modus: stellt Operation und Ziel-Body um und legt bei New Body den neuen Body an.
    void setOperation(Design::Feature::Op op, Design::Body* target)
    {
        for (auto& [b, tip] : savedTips) {
            b->Tip.setValue(tip);
        }
        savedTips.clear();

        App::Document* doc = ext->getDocument();
        if (op == Design::Feature::Op::NewBody) {
            if (!newBody) {
                const auto count = doc->getObjectsOfType(Design::Body::getClassTypeId()).size();
                newBody = static_cast<Design::Body*>(doc->addObject("Design::Body", "Body"));
                newBody->Label.setValue("Body" + std::to_string(count + 1));
                Design::folder(Design::root(doc, true), "Bodies")->addObject(newBody);
            }
            ext->Bodies.setValues({newBody});
            ext->BaseFeatures.setValues({});
            newBody->Tip.setValue(ext);
        }
        else {
            if (newBody) {
                doc->removeObject(newBody->getNameInDocument());
                newBody = nullptr;
            }
            if (target) {
                savedTips[target] = target->Tip.getValue();
                ext->Bodies.setValues({target});
                ext->BaseFeatures.setValues({target->Tip.getValue()});
                target->Tip.setValue(ext);
                body->blockSignals(true);
                body->setCurrentIndex(body->findData(QString::fromLatin1(target->getNameInDocument())));
                body->blockSignals(false);
            }
            else {
                ext->Bodies.setValues({});
                ext->BaseFeatures.setValues({});
            }
        }
        ext->Operation.setValue(static_cast<long>(op));
        operation->blockSignals(true);
        operation->setCurrentIndex(static_cast<int>(op));
        operation->blockSignals(false);
    }

    void apply()
    {
        // Negativer Abstand dreht die Richtung um, wie in Fusion
        const double d = distance->value().getValue();
        ext->Extent.setValue(extent->currentIndex());
        ext->Distance.setValue(std::abs(d));
        ext->Distance2.setValue(std::abs(distance2->value().getValue()));
        ext->Reversed.setValue(flip->isChecked() != (d < 0));
        const bool twoSides = extent->currentIndex() == 2;
        distance2->setVisible(twoSides);
        distance2Label->setVisible(twoSides);
        body->setVisible(ext->op() != Design::Feature::Op::NewBody);

        ext->getDocument()->recompute();
        status->setText(ext->isError() ? QString::fromUtf8(ext->getStatusString()) : QString());
    }

    Design::Extrude* ext;
    bool create;
    bool autoFlipped = false;
    Design::Body* newBody = nullptr;
    std::map<Design::Body*, App::DocumentObject*> savedTips;
    QComboBox* extent;
    Gui::QuantitySpinBox* distance;
    Gui::QuantitySpinBox* distance2;
    QLabel* distance2Label;
    QCheckBox* flip;
    QComboBox* operation;
    QComboBox* body;
    QLabel* status;
};

}  // namespace

PROPERTY_SOURCE(DesignGui::ViewProviderExtrude, PartGui::ViewProviderPartExt)

ViewProviderExtrude::ViewProviderExtrude()
{
    ShowInTree.setValue(false);
}

void ViewProviderExtrude::attach(App::DocumentObject* obj)
{
    ViewProviderPartExt::attach(obj);
    Visibility.setValue(false);  // das Ergebnis zeigt der Body
}

QIcon ViewProviderExtrude::getIcon() const
{
    return Gui::BitmapFactory().pixmap("PartDesign_Pad");
}

bool ViewProviderExtrude::doubleClicked()
{
    return Gui::Application::Instance->getDocument(getObject()->getDocument())->setEdit(this);
}

bool ViewProviderExtrude::setEdit(int)
{
    auto ext = freecad_cast<Design::Extrude*>(getObject());
    if (!ext || Gui::Control().activeDialog()) {
        return false;
    }
    App::Document* doc = ext->getDocument();
    if (!doc->hasPendingTransaction()) {
        doc->openTransaction("Edit Extrude");
    }
    Gui::Control().showDialog(new TaskExtrude(ext, createMode, defaultTarget));
    createMode = false;
    defaultTarget = nullptr;
    return true;
}

void ViewProviderExtrude::unsetEdit(int)
{
    Gui::Control().closeDialog();
}
