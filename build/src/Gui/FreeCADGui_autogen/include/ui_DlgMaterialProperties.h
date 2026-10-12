/********************************************************************************
** Form generated from reading UI file 'DlgMaterialProperties.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGMATERIALPROPERTIES_H
#define UI_DLGMATERIALPROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgMaterialProperties
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox4;
    QGridLayout *gridLayout1;
    QLabel *textLabel1;
    QLabel *textLabel4;
    Gui::ColorButton *ambientColor;
    QPushButton *buttonReset;
    QLabel *textLabel2;
    QSpinBox *shininess;
    Gui::ColorButton *emissiveColor;
    QLabel *textLabel3;
    Gui::ColorButton *specularColor;
    QPushButton *buttonDefault;
    Gui::ColorButton *diffuseColor;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *transparency;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgMaterialProperties)
    {
        if (Gui__Dialog__DlgMaterialProperties->objectName().isEmpty())
            Gui__Dialog__DlgMaterialProperties->setObjectName("Gui__Dialog__DlgMaterialProperties");
        Gui__Dialog__DlgMaterialProperties->resize(292, 296);
        Gui__Dialog__DlgMaterialProperties->setSizeGripEnabled(true);
        Gui__Dialog__DlgMaterialProperties->setModal(true);
        gridLayout = new QGridLayout(Gui__Dialog__DlgMaterialProperties);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        groupBox4 = new QGroupBox(Gui__Dialog__DlgMaterialProperties);
        groupBox4->setObjectName("groupBox4");
        gridLayout1 = new QGridLayout(groupBox4);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        textLabel1 = new QLabel(groupBox4);
        textLabel1->setObjectName("textLabel1");

        gridLayout1->addWidget(textLabel1, 1, 0, 1, 1);

        textLabel4 = new QLabel(groupBox4);
        textLabel4->setObjectName("textLabel4");

        gridLayout1->addWidget(textLabel4, 4, 0, 1, 1);

        ambientColor = new Gui::ColorButton(groupBox4);
        ambientColor->setObjectName("ambientColor");
        ambientColor->setAllowTransparency(true);

        gridLayout1->addWidget(ambientColor, 0, 1, 1, 1);

        buttonReset = new QPushButton(groupBox4);
        buttonReset->setObjectName("buttonReset");

        gridLayout1->addWidget(buttonReset, 6, 0, 1, 1);

        textLabel2 = new QLabel(groupBox4);
        textLabel2->setObjectName("textLabel2");

        gridLayout1->addWidget(textLabel2, 0, 0, 1, 1);

        shininess = new QSpinBox(groupBox4);
        shininess->setObjectName("shininess");
        shininess->setMinimumSize(QSize(122, 0));
        shininess->setSuffix(QString::fromUtf8("%"));
        shininess->setMaximum(100);
        shininess->setSingleStep(5);

        gridLayout1->addWidget(shininess, 4, 1, 1, 1);

        emissiveColor = new Gui::ColorButton(groupBox4);
        emissiveColor->setObjectName("emissiveColor");
        emissiveColor->setAllowTransparency(true);

        gridLayout1->addWidget(emissiveColor, 2, 1, 1, 1);

        textLabel3 = new QLabel(groupBox4);
        textLabel3->setObjectName("textLabel3");

        gridLayout1->addWidget(textLabel3, 3, 0, 1, 1);

        specularColor = new Gui::ColorButton(groupBox4);
        specularColor->setObjectName("specularColor");
        specularColor->setAllowTransparency(true);

        gridLayout1->addWidget(specularColor, 3, 1, 1, 1);

        buttonDefault = new QPushButton(groupBox4);
        buttonDefault->setObjectName("buttonDefault");

        gridLayout1->addWidget(buttonDefault, 6, 1, 1, 1);

        diffuseColor = new Gui::ColorButton(groupBox4);
        diffuseColor->setObjectName("diffuseColor");
        diffuseColor->setAllowTransparency(true);

        gridLayout1->addWidget(diffuseColor, 1, 1, 1, 1);

        label = new QLabel(groupBox4);
        label->setObjectName("label");

        gridLayout1->addWidget(label, 2, 0, 1, 1);

        label_2 = new QLabel(groupBox4);
        label_2->setObjectName("label_2");

        gridLayout1->addWidget(label_2, 5, 0, 1, 1);

        transparency = new QSpinBox(groupBox4);
        transparency->setObjectName("transparency");
        transparency->setMinimumSize(QSize(122, 0));
        transparency->setMaximum(100);

        gridLayout1->addWidget(transparency, 5, 1, 1, 1);


        gridLayout->addWidget(groupBox4, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgMaterialProperties);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        QWidget::setTabOrder(ambientColor, diffuseColor);
        QWidget::setTabOrder(diffuseColor, emissiveColor);
        QWidget::setTabOrder(emissiveColor, specularColor);

        retranslateUi(Gui__Dialog__DlgMaterialProperties);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgMaterialProperties, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgMaterialProperties);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgMaterialProperties)
    {
        Gui__Dialog__DlgMaterialProperties->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Material Properties", nullptr));
        groupBox4->setTitle(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Material", nullptr));
        textLabel1->setText(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Diffuse color", nullptr));
#if QT_CONFIG(tooltip)
        textLabel1->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Defines the base color of a surface when illuminated by light. It represents how the object scatters light evenly in all directions, independent of the viewer\342\200\231s angle. This property will influence the material color the most.", nullptr));
#endif // QT_CONFIG(tooltip)
        textLabel4->setText(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Shininess", nullptr));
#if QT_CONFIG(tooltip)
        textLabel4->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Defines the size and sharpness of specular highlights on a surface. Higher values produce small, sharp highlights, while lower values create broad, soft highlights. Note that the highlight intensity is defined by specular color.", nullptr));
#endif // QT_CONFIG(tooltip)
        ambientColor->setText(QString());
        buttonReset->setText(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        buttonReset->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Reverts changes done in the dialogue.", nullptr));
#endif // QT_CONFIG(tooltip)
        textLabel2->setText(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Ambient color", nullptr));
#if QT_CONFIG(tooltip)
        textLabel2->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Defines the color of a surface under indirect, uniform lighting, representing how it appears when illuminated only by ambient light in a scene, without directional light, shading, or highlights", nullptr));
#endif // QT_CONFIG(tooltip)
        emissiveColor->setText(QString());
        textLabel3->setText(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Specular color", nullptr));
#if QT_CONFIG(tooltip)
        textLabel3->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Defines the color and intensity of the bright, mirror-like highlights that appear on shiny or reflective surfaces when light hits them directly. Set to bright colors for shiny objects.", nullptr));
#endif // QT_CONFIG(tooltip)
        specularColor->setText(QString());
        buttonDefault->setText(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Default", nullptr));
#if QT_CONFIG(tooltip)
        buttonDefault->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Changes all values to default values", nullptr));
#endif // QT_CONFIG(tooltip)
        diffuseColor->setText(QString());
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Emissive color", nullptr));
#if QT_CONFIG(tooltip)
        label->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Defines the color of a surface that appears to emit as if it were a light source, independent of external lighting, making the object look self-illuminated. Set to black to have no emissive color.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Transparency", nullptr));
#if QT_CONFIG(tooltip)
        label_2->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "Defines how much light passes through an object, making it partially or fully see-through", nullptr));
#endif // QT_CONFIG(tooltip)
        transparency->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgMaterialProperties", "%", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgMaterialProperties: public Ui_DlgMaterialProperties {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGMATERIALPROPERTIES_H
