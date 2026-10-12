/********************************************************************************
** Form generated from reading UI file 'DlgSettingsMeshView.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSMESHVIEW_H
#define UI_DLGSETTINGSMESHVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/Widgets.h"

namespace MeshGui {

class Ui_DlgSettingsMeshView
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QGridLayout *gridLayout2;
    QLabel *labelFaceColor;
    Gui::PrefColorButton *buttonMeshColor;
    QSpacerItem *spacerItem;
    QLabel *labelMeshTransparency;
    Gui::PrefSpinBox *spinMeshTransparency;
    QLabel *labelLineColor;
    Gui::PrefColorButton *buttonLineColor;
    QSpacerItem *spacerItem1;
    QLabel *labelLineTransparency;
    Gui::PrefSpinBox *spinLineTransparency;
    QLabel *labelBackfaceColor;
    Gui::PrefColorButton *buttonBackfaceColor;
    QSpacerItem *spacerItem2;
    Gui::PrefCheckBox *checkboxRendering;
    Gui::PrefCheckBox *checkboxBoundbox;
    QSpacerItem *spacerItem3;
    QGroupBox *GroupBox12;
    QGridLayout *gridLayout3;
    Gui::PrefCheckBox *checkboxNormal;
    QLabel *labelAngle;
    Gui::PrefDoubleSpinBox *spinboxAngle;
    QSpacerItem *spacerItem4;
    QLabel *labelHint;
    QSpacerItem *spacerItem5;

    void setupUi(QWidget *MeshGui__DlgSettingsMeshView)
    {
        if (MeshGui__DlgSettingsMeshView->objectName().isEmpty())
            MeshGui__DlgSettingsMeshView->setObjectName("MeshGui__DlgSettingsMeshView");
        MeshGui__DlgSettingsMeshView->resize(559, 396);
        gridLayout = new QGridLayout(MeshGui__DlgSettingsMeshView);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(9, 9, 9, 9);
        groupBox = new QGroupBox(MeshGui__DlgSettingsMeshView);
        groupBox->setObjectName("groupBox");
        gridLayout1 = new QGridLayout(groupBox);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setObjectName("gridLayout2");
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        labelFaceColor = new QLabel(groupBox);
        labelFaceColor->setObjectName("labelFaceColor");

        gridLayout2->addWidget(labelFaceColor, 0, 0, 1, 1);

        buttonMeshColor = new Gui::PrefColorButton(groupBox);
        buttonMeshColor->setObjectName("buttonMeshColor");
        buttonMeshColor->setColor(QColor(204, 204, 204));
        buttonMeshColor->setProperty("prefEntry", QVariant(QByteArray("MeshColor")));
        buttonMeshColor->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout2->addWidget(buttonMeshColor, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(41, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem, 0, 2, 1, 1);

        labelMeshTransparency = new QLabel(groupBox);
        labelMeshTransparency->setObjectName("labelMeshTransparency");

        gridLayout2->addWidget(labelMeshTransparency, 0, 3, 1, 1);

        spinMeshTransparency = new Gui::PrefSpinBox(groupBox);
        spinMeshTransparency->setObjectName("spinMeshTransparency");
        spinMeshTransparency->setSuffix(QString::fromUtf8("%"));
        spinMeshTransparency->setMaximum(100);
        spinMeshTransparency->setSingleStep(5);
        spinMeshTransparency->setProperty("prefEntry", QVariant(QByteArray("MeshTransparency")));
        spinMeshTransparency->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout2->addWidget(spinMeshTransparency, 0, 4, 1, 1);

        labelLineColor = new QLabel(groupBox);
        labelLineColor->setObjectName("labelLineColor");

        gridLayout2->addWidget(labelLineColor, 1, 0, 1, 1);

        buttonLineColor = new Gui::PrefColorButton(groupBox);
        buttonLineColor->setObjectName("buttonLineColor");
        buttonLineColor->setColor(QColor(0, 0, 0));
        buttonLineColor->setProperty("prefEntry", QVariant(QByteArray("LineColor")));
        buttonLineColor->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout2->addWidget(buttonLineColor, 1, 1, 1, 1);

        spacerItem1 = new QSpacerItem(41, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem1, 1, 2, 1, 1);

        labelLineTransparency = new QLabel(groupBox);
        labelLineTransparency->setObjectName("labelLineTransparency");

        gridLayout2->addWidget(labelLineTransparency, 1, 3, 1, 1);

        spinLineTransparency = new Gui::PrefSpinBox(groupBox);
        spinLineTransparency->setObjectName("spinLineTransparency");
        spinLineTransparency->setSuffix(QString::fromUtf8("%"));
        spinLineTransparency->setMaximum(100);
        spinLineTransparency->setSingleStep(5);
        spinLineTransparency->setProperty("prefEntry", QVariant(QByteArray("LineTransparency")));
        spinLineTransparency->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout2->addWidget(spinLineTransparency, 1, 4, 1, 1);

        labelBackfaceColor = new QLabel(groupBox);
        labelBackfaceColor->setObjectName("labelBackfaceColor");

        gridLayout2->addWidget(labelBackfaceColor, 2, 0, 1, 1);

        buttonBackfaceColor = new Gui::PrefColorButton(groupBox);
        buttonBackfaceColor->setObjectName("buttonBackfaceColor");
        buttonBackfaceColor->setEnabled(false);
        buttonBackfaceColor->setColor(QColor(204, 204, 204));
        buttonBackfaceColor->setProperty("prefEntry", QVariant(QByteArray("BackfaceColor")));
        buttonBackfaceColor->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout2->addWidget(buttonBackfaceColor, 2, 1, 1, 1);

        spacerItem2 = new QSpacerItem(191, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem2, 2, 2, 1, 3);

        checkboxRendering = new Gui::PrefCheckBox(groupBox);
        checkboxRendering->setObjectName("checkboxRendering");
        checkboxRendering->setChecked(false);
        checkboxRendering->setProperty("prefEntry", QVariant(QByteArray("TwoSideRendering")));
        checkboxRendering->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout2->addWidget(checkboxRendering, 3, 0, 1, 1);

        checkboxBoundbox = new Gui::PrefCheckBox(groupBox);
        checkboxBoundbox->setObjectName("checkboxBoundbox");
        checkboxBoundbox->setChecked(false);
        checkboxBoundbox->setProperty("prefEntry", QVariant(QByteArray("ShowBoundingBox")));
        checkboxBoundbox->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout2->addWidget(checkboxBoundbox, 3, 1, 1, 4);


        gridLayout1->addLayout(gridLayout2, 0, 0, 1, 1);

        spacerItem3 = new QSpacerItem(71, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        gridLayout1->addItem(spacerItem3, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        GroupBox12 = new QGroupBox(MeshGui__DlgSettingsMeshView);
        GroupBox12->setObjectName("GroupBox12");
        gridLayout3 = new QGridLayout(GroupBox12);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName("gridLayout3");
        gridLayout3->setContentsMargins(9, 9, 9, 9);
        checkboxNormal = new Gui::PrefCheckBox(GroupBox12);
        checkboxNormal->setObjectName("checkboxNormal");
        checkboxNormal->setProperty("prefEntry", QVariant(QByteArray("VertexPerNormals")));
        checkboxNormal->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout3->addWidget(checkboxNormal, 0, 0, 1, 1);

        labelAngle = new QLabel(GroupBox12);
        labelAngle->setObjectName("labelAngle");

        gridLayout3->addWidget(labelAngle, 1, 0, 1, 1);

        spinboxAngle = new Gui::PrefDoubleSpinBox(GroupBox12);
        spinboxAngle->setObjectName("spinboxAngle");
        spinboxAngle->setEnabled(false);
        spinboxAngle->setSuffix(QString::fromUtf8(" \302\260"));
        spinboxAngle->setMaximum(180.000000000000000);
        spinboxAngle->setProperty("prefEntry", QVariant(QByteArray("CreaseAngle")));
        spinboxAngle->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout3->addWidget(spinboxAngle, 1, 1, 1, 1);

        spacerItem4 = new QSpacerItem(221, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout3->addItem(spacerItem4, 1, 2, 1, 1);

        labelHint = new QLabel(GroupBox12);
        labelHint->setObjectName("labelHint");

        gridLayout3->addWidget(labelHint, 2, 0, 1, 3);


        gridLayout->addWidget(GroupBox12, 1, 0, 1, 1);

        spacerItem5 = new QSpacerItem(541, 41, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(spacerItem5, 2, 0, 1, 1);

        QWidget::setTabOrder(buttonMeshColor, buttonLineColor);
        QWidget::setTabOrder(buttonLineColor, buttonBackfaceColor);
        QWidget::setTabOrder(buttonBackfaceColor, spinMeshTransparency);
        QWidget::setTabOrder(spinMeshTransparency, spinLineTransparency);
        QWidget::setTabOrder(spinLineTransparency, checkboxRendering);
        QWidget::setTabOrder(checkboxRendering, checkboxBoundbox);
        QWidget::setTabOrder(checkboxBoundbox, checkboxNormal);
        QWidget::setTabOrder(checkboxNormal, spinboxAngle);

        retranslateUi(MeshGui__DlgSettingsMeshView);
        QObject::connect(checkboxNormal, SIGNAL(toggled(bool)), spinboxAngle, SLOT(setEnabled(bool)));
        QObject::connect(checkboxRendering, SIGNAL(toggled(bool)), buttonBackfaceColor, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(MeshGui__DlgSettingsMeshView);
    } // setupUi

    void retranslateUi(QWidget *MeshGui__DlgSettingsMeshView)
    {
        MeshGui__DlgSettingsMeshView->setWindowTitle(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Mesh View", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Default Appearance for New Meshes", nullptr));
        labelFaceColor->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Default mesh color", nullptr));
#if QT_CONFIG(tooltip)
        buttonMeshColor->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Default color for new meshes", nullptr));
#endif // QT_CONFIG(tooltip)
        labelMeshTransparency->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Mesh transparency", nullptr));
        labelLineColor->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Default line color", nullptr));
#if QT_CONFIG(tooltip)
        buttonLineColor->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Default line color for new meshes", nullptr));
#endif // QT_CONFIG(tooltip)
        labelLineTransparency->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Line transparency", nullptr));
        labelBackfaceColor->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Backface color", nullptr));
#if QT_CONFIG(tooltip)
        checkboxRendering->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "The bottom side of the surface will be rendered the same way as the top side.\n"
"If not checked, it depends on the option \"Enable backlight color\"\n"
"(preferences section Display -> 3D View). Either the backlight color\n"
"will be used or black.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkboxRendering->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Two-side rendering", nullptr));
#if QT_CONFIG(tooltip)
        checkboxBoundbox->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "A bounding box will be displayed", nullptr));
#endif // QT_CONFIG(tooltip)
        checkboxBoundbox->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Show bounding-box for highlighted or selected meshes", nullptr));
        GroupBox12->setTitle(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Smoothing", nullptr));
#if QT_CONFIG(tooltip)
        checkboxNormal->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "If this option is set Phong shading is used, otherwise flat shading.\n"
"Shading defines the appearance of surfaces.\n"
"\n"
"With flat shading the surface normals are not defined per vertex that leads\n"
"to an unreal appearance for curved surfaces while using Phong shading leads\n"
"to a smoother appearance.\n"
"", nullptr));
#endif // QT_CONFIG(tooltip)
        checkboxNormal->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Define normal per vertex", nullptr));
#if QT_CONFIG(tooltip)
        labelAngle->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-size:7.8pt; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">This is the smallest angle between two faces where normals get calculated to do flat shading.</p><p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">If the angle between the normals of two neighbouring faces is less than the crease angle, the faces will be smoothshaded around their common edge.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        labelAngle->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Crease angle", nullptr));
#if QT_CONFIG(tooltip)
        spinboxAngle->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "Crease angle is a threshold angle between two faces.\n"
"\n"
" If face angle \342\211\245 crease angle, facet shading is used\n"
" If face angle < crease angle, smooth shading is used", nullptr));
#endif // QT_CONFIG(tooltip)
        labelHint->setText(QCoreApplication::translate("MeshGui::DlgSettingsMeshView", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-size:7.8pt; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><span style=\" font-weight:600;\">Hint</span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Defining the normals per vertex is also called <span style=\" font-style:italic;\">Phong shading</span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-style:italic;\"><span style=\" font-style:normal;\">while defining the normals per face is called </span>Flat shading<span style=\" font-style:normal;\">.</span></p></body></html>", nullptr));
    } // retranslateUi

};

} // namespace MeshGui

namespace MeshGui {
namespace Ui {
    class DlgSettingsMeshView: public Ui_DlgSettingsMeshView {};
} // namespace Ui
} // namespace MeshGui

#endif // UI_DLGSETTINGSMESHVIEW_H
