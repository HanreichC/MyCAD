/********************************************************************************
** Form generated from reading UI file 'DlgSettingsObjectColor.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSOBJECTCOLOR_H
#define UI_DLGSETTINGSOBJECTCOLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/Widgets.h"

namespace PartGui {

class Ui_DlgSettingsObjectColor
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxDefaultColors;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_6;
    Gui::PrefColorButton *DefaultShapeColor;
    Gui::PrefCheckBox *checkRandomColor;
    QLabel *label_ambient;
    Gui::PrefColorButton *DefaultAmbientColor;
    QLabel *label_emissive;
    Gui::PrefColorButton *DefaultEmissiveColor;
    QLabel *label_specular;
    Gui::PrefColorButton *DefaultSpecularColor;
    QLabel *label_transparency;
    Gui::PrefSpinBox *DefaultShapeTransparency;
    QLabel *label_shininess;
    Gui::PrefSpinBox *DefaultShapeShininess;
    QLabel *label_7;
    Gui::PrefColorButton *DefaultShapeLineColor;
    QLabel *label_9;
    Gui::PrefSpinBox *DefaultShapeLineWidth;
    QLabel *label_10;
    Gui::PrefColorButton *DefaultShapeVertexColor;
    QLabel *label_11;
    Gui::PrefSpinBox *DefaultShapeVertexSize;
    QLabel *label_8;
    Gui::PrefColorButton *BoundingBoxColor;
    QLabel *label_fontsize;
    Gui::PrefDoubleSpinBox *BoundingBoxFontSize;
    Gui::PrefCheckBox *twosideRendering;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    Gui::PrefColorButton *AnnotationTextColor;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PartGui__DlgSettingsObjectColor)
    {
        if (PartGui__DlgSettingsObjectColor->objectName().isEmpty())
            PartGui__DlgSettingsObjectColor->setObjectName("PartGui__DlgSettingsObjectColor");
        PartGui__DlgSettingsObjectColor->resize(476, 378);
        verticalLayout = new QVBoxLayout(PartGui__DlgSettingsObjectColor);
        verticalLayout->setObjectName("verticalLayout");
        groupBoxDefaultColors = new QGroupBox(PartGui__DlgSettingsObjectColor);
        groupBoxDefaultColors->setObjectName("groupBoxDefaultColors");
        horizontalLayout = new QHBoxLayout(groupBoxDefaultColors);
        horizontalLayout->setObjectName("horizontalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_6 = new QLabel(groupBoxDefaultColors);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        DefaultShapeColor = new Gui::PrefColorButton(groupBoxDefaultColors);
        DefaultShapeColor->setObjectName("DefaultShapeColor");
        DefaultShapeColor->setColor(QColor(204, 204, 230));
        DefaultShapeColor->setProperty("prefEntry", QVariant(QByteArray("DefaultShapeColor")));
        DefaultShapeColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultShapeColor, 0, 1, 1, 1);

        checkRandomColor = new Gui::PrefCheckBox(groupBoxDefaultColors);
        checkRandomColor->setObjectName("checkRandomColor");
        checkRandomColor->setProperty("prefEntry", QVariant(QByteArray("RandomColor")));
        checkRandomColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(checkRandomColor, 0, 2, 1, 1);

        label_ambient = new QLabel(groupBoxDefaultColors);
        label_ambient->setObjectName("label_ambient");
        label_ambient->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_ambient, 1, 0, 1, 1);

        DefaultAmbientColor = new Gui::PrefColorButton(groupBoxDefaultColors);
        DefaultAmbientColor->setObjectName("DefaultAmbientColor");
        DefaultAmbientColor->setColor(QColor(85, 85, 85));
        DefaultAmbientColor->setProperty("prefEntry", QVariant(QByteArray("DefaultAmbientColor")));
        DefaultAmbientColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultAmbientColor, 1, 1, 1, 1);

        label_emissive = new QLabel(groupBoxDefaultColors);
        label_emissive->setObjectName("label_emissive");
        label_emissive->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_emissive, 2, 0, 1, 1);

        DefaultEmissiveColor = new Gui::PrefColorButton(groupBoxDefaultColors);
        DefaultEmissiveColor->setObjectName("DefaultEmissiveColor");
        DefaultEmissiveColor->setColor(QColor(0, 0, 0));
        DefaultEmissiveColor->setProperty("prefEntry", QVariant(QByteArray("DefaultEmissiveColor")));
        DefaultEmissiveColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultEmissiveColor, 2, 1, 1, 1);

        label_specular = new QLabel(groupBoxDefaultColors);
        label_specular->setObjectName("label_specular");
        label_specular->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_specular, 3, 0, 1, 1);

        DefaultSpecularColor = new Gui::PrefColorButton(groupBoxDefaultColors);
        DefaultSpecularColor->setObjectName("DefaultSpecularColor");
        DefaultSpecularColor->setColor(QColor(136, 136, 136));
        DefaultSpecularColor->setProperty("prefEntry", QVariant(QByteArray("DefaultSpecularColor")));
        DefaultSpecularColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultSpecularColor, 3, 1, 1, 1);

        label_transparency = new QLabel(groupBoxDefaultColors);
        label_transparency->setObjectName("label_transparency");
        label_transparency->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_transparency, 4, 0, 1, 1);

        DefaultShapeTransparency = new Gui::PrefSpinBox(groupBoxDefaultColors);
        DefaultShapeTransparency->setObjectName("DefaultShapeTransparency");
        DefaultShapeTransparency->setSuffix(QString::fromUtf8(" %"));
        DefaultShapeTransparency->setMaximum(100);
        DefaultShapeTransparency->setSingleStep(5);
        DefaultShapeTransparency->setProperty("prefEntry", QVariant(QByteArray("DefaultShapeTransparency")));
        DefaultShapeTransparency->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultShapeTransparency, 4, 1, 1, 1);

        label_shininess = new QLabel(groupBoxDefaultColors);
        label_shininess->setObjectName("label_shininess");
        label_shininess->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_shininess, 5, 0, 1, 1);

        DefaultShapeShininess = new Gui::PrefSpinBox(groupBoxDefaultColors);
        DefaultShapeShininess->setObjectName("DefaultShapeShininess");
        DefaultShapeShininess->setSuffix(QString::fromUtf8(" %"));
        DefaultShapeShininess->setMaximum(100);
        DefaultShapeShininess->setValue(90);
        DefaultShapeShininess->setSingleStep(5);
        DefaultShapeShininess->setProperty("prefEntry", QVariant(QByteArray("DefaultShapeShininess")));
        DefaultShapeShininess->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultShapeShininess, 5, 1, 1, 1);

        label_7 = new QLabel(groupBoxDefaultColors);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        DefaultShapeLineColor = new Gui::PrefColorButton(groupBoxDefaultColors);
        DefaultShapeLineColor->setObjectName("DefaultShapeLineColor");
        DefaultShapeLineColor->setColor(QColor(25, 25, 25));
        DefaultShapeLineColor->setProperty("prefEntry", QVariant(QByteArray("DefaultShapeLineColor")));
        DefaultShapeLineColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultShapeLineColor, 6, 1, 1, 1);

        label_9 = new QLabel(groupBoxDefaultColors);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_9, 7, 0, 1, 1);

        DefaultShapeLineWidth = new Gui::PrefSpinBox(groupBoxDefaultColors);
        DefaultShapeLineWidth->setObjectName("DefaultShapeLineWidth");
        DefaultShapeLineWidth->setSuffix(QString::fromUtf8(" px"));
        DefaultShapeLineWidth->setMaximum(64);
        DefaultShapeLineWidth->setValue(2);
        DefaultShapeLineWidth->setProperty("prefEntry", QVariant(QByteArray("DefaultShapeLineWidth")));
        DefaultShapeLineWidth->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultShapeLineWidth, 7, 1, 1, 1);

        label_10 = new QLabel(groupBoxDefaultColors);
        label_10->setObjectName("label_10");
        label_10->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_10, 8, 0, 1, 1);

        DefaultShapeVertexColor = new Gui::PrefColorButton(groupBoxDefaultColors);
        DefaultShapeVertexColor->setObjectName("DefaultShapeVertexColor");
        DefaultShapeVertexColor->setColor(QColor(25, 25, 25));
        DefaultShapeVertexColor->setProperty("prefEntry", QVariant(QByteArray("DefaultShapeVertexColor")));
        DefaultShapeVertexColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultShapeVertexColor, 8, 1, 1, 1);

        label_11 = new QLabel(groupBoxDefaultColors);
        label_11->setObjectName("label_11");
        label_11->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_11, 9, 0, 1, 1);

        DefaultShapeVertexSize = new Gui::PrefSpinBox(groupBoxDefaultColors);
        DefaultShapeVertexSize->setObjectName("DefaultShapeVertexSize");
        DefaultShapeVertexSize->setSuffix(QString::fromUtf8(" px"));
        DefaultShapeVertexSize->setMaximum(64);
        DefaultShapeVertexSize->setValue(2);
        DefaultShapeVertexSize->setProperty("prefEntry", QVariant(QByteArray("DefaultShapePointSize")));
        DefaultShapeVertexSize->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(DefaultShapeVertexSize, 9, 1, 1, 1);

        label_8 = new QLabel(groupBoxDefaultColors);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_8, 10, 0, 1, 1);

        BoundingBoxColor = new Gui::PrefColorButton(groupBoxDefaultColors);
        BoundingBoxColor->setObjectName("BoundingBoxColor");
        BoundingBoxColor->setColor(QColor(255, 255, 255));
        BoundingBoxColor->setProperty("prefEntry", QVariant(QByteArray("BoundingBoxColor")));
        BoundingBoxColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(BoundingBoxColor, 10, 1, 1, 1);

        label_fontsize = new QLabel(groupBoxDefaultColors);
        label_fontsize->setObjectName("label_fontsize");
        label_fontsize->setMinimumSize(QSize(182, 0));

        gridLayout->addWidget(label_fontsize, 11, 0, 1, 1);

        BoundingBoxFontSize = new Gui::PrefDoubleSpinBox(groupBoxDefaultColors);
        BoundingBoxFontSize->setObjectName("BoundingBoxFontSize");
        BoundingBoxFontSize->setSuffix(QString::fromUtf8(" pt"));
        BoundingBoxFontSize->setDecimals(1);
        BoundingBoxFontSize->setMinimum(2.000000000000000);
        BoundingBoxFontSize->setMaximum(64.000000000000000);
        BoundingBoxFontSize->setValue(10.000000000000000);
        BoundingBoxFontSize->setProperty("prefEntry", QVariant(QByteArray("BoundingBoxFontSize")));
        BoundingBoxFontSize->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(BoundingBoxFontSize, 11, 1, 1, 1);

        twosideRendering = new Gui::PrefCheckBox(groupBoxDefaultColors);
        twosideRendering->setObjectName("twosideRendering");
        twosideRendering->setMinimumSize(QSize(182, 0));
        twosideRendering->setChecked(true);
        twosideRendering->setProperty("prefEntry", QVariant(QByteArray("TwoSideRendering")));
        twosideRendering->setProperty("prefPath", QVariant(QByteArray("Mod/Part")));

        gridLayout->addWidget(twosideRendering, 12, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(groupBoxDefaultColors);

        groupBox = new QGroupBox(PartGui__DlgSettingsObjectColor);
        groupBox->setObjectName("groupBox");
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setMinimumSize(QSize(182, 0));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        AnnotationTextColor = new Gui::PrefColorButton(groupBox);
        AnnotationTextColor->setObjectName("AnnotationTextColor");
        AnnotationTextColor->setProperty("prefEntry", QVariant(QByteArray("AnnotationTextColor")));
        AnnotationTextColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(AnnotationTextColor, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_2);

        horizontalSpacer_2 = new QSpacerItem(28, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 217, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        QWidget::setTabOrder(DefaultShapeColor, DefaultShapeLineWidth);
        QWidget::setTabOrder(DefaultShapeLineWidth, DefaultShapeLineColor);
        QWidget::setTabOrder(DefaultShapeLineColor, BoundingBoxColor);

        retranslateUi(PartGui__DlgSettingsObjectColor);
        QObject::connect(checkRandomColor, SIGNAL(toggled(bool)), DefaultShapeColor, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(PartGui__DlgSettingsObjectColor);
    } // setupUi

    void retranslateUi(QWidget *PartGui__DlgSettingsObjectColor)
    {
        PartGui__DlgSettingsObjectColor->setWindowTitle(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Shape Appearance", nullptr));
        groupBoxDefaultColors->setTitle(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Default Shape Appearance Properties", nullptr));
        label_6->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Shape color", nullptr));
#if QT_CONFIG(tooltip)
        DefaultShapeColor->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default color for new shapes", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkRandomColor->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Use random color instead", nullptr));
#endif // QT_CONFIG(tooltip)
        checkRandomColor->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Random", nullptr));
        label_ambient->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Ambient shape color", nullptr));
#if QT_CONFIG(tooltip)
        DefaultAmbientColor->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default ambient color for new shapes", nullptr));
#endif // QT_CONFIG(tooltip)
        label_emissive->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Emissive shape color", nullptr));
#if QT_CONFIG(tooltip)
        DefaultEmissiveColor->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default emissive color for new shapes", nullptr));
#endif // QT_CONFIG(tooltip)
        label_specular->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Specular shape color", nullptr));
#if QT_CONFIG(tooltip)
        DefaultSpecularColor->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default specular color for new shapes", nullptr));
#endif // QT_CONFIG(tooltip)
        label_transparency->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Shape transparency", nullptr));
#if QT_CONFIG(tooltip)
        DefaultShapeTransparency->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default transparency for new shapes", nullptr));
#endif // QT_CONFIG(tooltip)
        label_shininess->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Shape shininess", nullptr));
#if QT_CONFIG(tooltip)
        DefaultShapeShininess->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default shininess for new shapes", nullptr));
#endif // QT_CONFIG(tooltip)
        label_7->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Line color", nullptr));
#if QT_CONFIG(tooltip)
        DefaultShapeLineColor->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default line color for new shapes", nullptr));
#endif // QT_CONFIG(tooltip)
        label_9->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Line width", nullptr));
#if QT_CONFIG(tooltip)
        DefaultShapeLineWidth->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default line thickness for new shapes", nullptr));
#endif // QT_CONFIG(tooltip)
        label_10->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Vertex color", nullptr));
#if QT_CONFIG(tooltip)
        DefaultShapeVertexColor->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default color for new vertices", nullptr));
#endif // QT_CONFIG(tooltip)
        label_11->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Vertex size", nullptr));
#if QT_CONFIG(tooltip)
        DefaultShapeVertexSize->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The default size for new vertices", nullptr));
#endif // QT_CONFIG(tooltip)
        label_8->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Bounding box color", nullptr));
#if QT_CONFIG(tooltip)
        BoundingBoxColor->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The color of bounding boxes in the 3D view", nullptr));
#endif // QT_CONFIG(tooltip)
        label_fontsize->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Bounding box font size", nullptr));
#if QT_CONFIG(tooltip)
        BoundingBoxFontSize->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The font size of bounding boxes in the 3D view", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        twosideRendering->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "The bottom side of the surface will be rendered the same way as the top.\n"
"If not checked, it depends on the option \"Backlight color\"\n"
"(preferences section Display -> 3D View); either the backlight color\n"
"will be used or black.", nullptr));
#endif // QT_CONFIG(tooltip)
        twosideRendering->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Two-side rendering", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Default Annotation Color", nullptr));
        label->setText(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Text color", nullptr));
#if QT_CONFIG(tooltip)
        AnnotationTextColor->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsObjectColor", "Text color for document annotations", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgSettingsObjectColor: public Ui_DlgSettingsObjectColor {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGSETTINGSOBJECTCOLOR_H
