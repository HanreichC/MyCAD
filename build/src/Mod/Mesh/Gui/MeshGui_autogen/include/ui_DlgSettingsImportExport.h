/********************************************************************************
** Form generated from reading UI file 'DlgSettingsImportExport.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSIMPORTEXPORT_H
#define UI_DLGSETTINGSIMPORTEXPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/QuantitySpinBox.h"

namespace MeshGui {

class Ui_DlgSettingsImportExport
{
public:
    QGridLayout *gridLayout;
    QGroupBox *GroupBox12;
    QGridLayout *gridLayout1;
    QGridLayout *gridLayout2;
    QLabel *textLabel1;
    Gui::QuantitySpinBox *maxDeviationExport;
    Gui::PrefCheckBox *exportAmfCompressed;
    Gui::PrefCheckBox *export3mfModel;
    QGroupBox *GroupBoxAsy;
    QGridLayout *gridLayout3;
    QGridLayout *gridLayout4;
    QLabel *labelAsyWidth;
    QLineEdit *asymptoteWidth;
    QSpacerItem *spacerItem;
    QLabel *labelAsyHeight;
    QLineEdit *asymptoteHeight;
    QSpacerItem *spacerItem1;

    void setupUi(QWidget *MeshGui__DlgSettingsImportExport)
    {
        if (MeshGui__DlgSettingsImportExport->objectName().isEmpty())
            MeshGui__DlgSettingsImportExport->setObjectName("MeshGui__DlgSettingsImportExport");
        MeshGui__DlgSettingsImportExport->resize(539, 339);
        gridLayout = new QGridLayout(MeshGui__DlgSettingsImportExport);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        GroupBox12 = new QGroupBox(MeshGui__DlgSettingsImportExport);
        GroupBox12->setObjectName("GroupBox12");
        gridLayout1 = new QGridLayout(GroupBox12);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setObjectName("gridLayout2");
        textLabel1 = new QLabel(GroupBox12);
        textLabel1->setObjectName("textLabel1");

        gridLayout2->addWidget(textLabel1, 0, 0, 1, 1);

        maxDeviationExport = new Gui::QuantitySpinBox(GroupBox12);
        maxDeviationExport->setObjectName("maxDeviationExport");
        maxDeviationExport->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        maxDeviationExport->setMinimum(0.000010000000000);
        maxDeviationExport->setMaximum(100000000.000000000000000);
        maxDeviationExport->setSingleStep(0.010000000000000);
        maxDeviationExport->setValue(0.100000000000000);

        gridLayout2->addWidget(maxDeviationExport, 0, 1, 1, 1);

        exportAmfCompressed = new Gui::PrefCheckBox(GroupBox12);
        exportAmfCompressed->setObjectName("exportAmfCompressed");
        exportAmfCompressed->setChecked(true);
        exportAmfCompressed->setProperty("prefEntry", QVariant(QByteArray("ExportAmfCompressed")));
        exportAmfCompressed->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout2->addWidget(exportAmfCompressed, 1, 0, 1, 1);

        export3mfModel = new Gui::PrefCheckBox(GroupBox12);
        export3mfModel->setObjectName("export3mfModel");
        export3mfModel->setChecked(true);
        export3mfModel->setProperty("prefEntry", QVariant(QByteArray("Export3mfModel")));
        export3mfModel->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh")));

        gridLayout2->addWidget(export3mfModel, 2, 0, 1, 1);


        gridLayout1->addLayout(gridLayout2, 0, 0, 1, 1);


        gridLayout->addWidget(GroupBox12, 0, 0, 1, 1);

        GroupBoxAsy = new QGroupBox(MeshGui__DlgSettingsImportExport);
        GroupBoxAsy->setObjectName("GroupBoxAsy");
        GroupBoxAsy->setTitle(QString::fromUtf8("Asymptote"));
        gridLayout3 = new QGridLayout(GroupBoxAsy);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName("gridLayout3");
        gridLayout4 = new QGridLayout();
        gridLayout4->setSpacing(6);
        gridLayout4->setObjectName("gridLayout4");
        labelAsyWidth = new QLabel(GroupBoxAsy);
        labelAsyWidth->setObjectName("labelAsyWidth");

        gridLayout4->addWidget(labelAsyWidth, 0, 0, 1, 1);

        asymptoteWidth = new QLineEdit(GroupBoxAsy);
        asymptoteWidth->setObjectName("asymptoteWidth");

        gridLayout4->addWidget(asymptoteWidth, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(61, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout4->addItem(spacerItem, 0, 2, 1, 1);

        labelAsyHeight = new QLabel(GroupBoxAsy);
        labelAsyHeight->setObjectName("labelAsyHeight");

        gridLayout4->addWidget(labelAsyHeight, 0, 3, 1, 1);

        asymptoteHeight = new QLineEdit(GroupBoxAsy);
        asymptoteHeight->setObjectName("asymptoteHeight");

        gridLayout4->addWidget(asymptoteHeight, 0, 4, 1, 1);


        gridLayout3->addLayout(gridLayout4, 0, 0, 1, 1);


        gridLayout->addWidget(GroupBoxAsy, 1, 0, 1, 1);

        spacerItem1 = new QSpacerItem(20, 61, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(spacerItem1, 2, 0, 1, 1);


        retranslateUi(MeshGui__DlgSettingsImportExport);

        QMetaObject::connectSlotsByName(MeshGui__DlgSettingsImportExport);
    } // setupUi

    void retranslateUi(QWidget *MeshGui__DlgSettingsImportExport)
    {
        MeshGui__DlgSettingsImportExport->setWindowTitle(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Mesh Formats", nullptr));
        GroupBox12->setTitle(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Export", nullptr));
#if QT_CONFIG(tooltip)
        textLabel1->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Deviation of tessellation to the actual surface", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        textLabel1->setWhatsThis(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-size:7.8pt; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Tessellation</span></p><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"><span style=\" font-weight:400;\">Defines the maximum deviation of the tessellated mesh to the surface. The smaller the value is the slower the render speed which results in increased detail/resolution.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        textLabel1->setText(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Maximum mesh deviation", nullptr));
#if QT_CONFIG(tooltip)
        maxDeviationExport->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Maximal deviation between mesh and object", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        exportAmfCompressed->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "ZIP compression is used when writing a mesh file in AMF format", nullptr));
#endif // QT_CONFIG(tooltip)
        exportAmfCompressed->setText(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Export AMF files using compression", nullptr));
#if QT_CONFIG(tooltip)
        export3mfModel->setToolTip(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Always export mesh as model type in 3MF format even if not a solid", nullptr));
#endif // QT_CONFIG(tooltip)
        export3mfModel->setText(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Export 3MF files as model type", nullptr));
        labelAsyWidth->setText(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Width", nullptr));
        labelAsyHeight->setText(QCoreApplication::translate("MeshGui::DlgSettingsImportExport", "Height", nullptr));
    } // retranslateUi

};

} // namespace MeshGui

namespace MeshGui {
namespace Ui {
    class DlgSettingsImportExport: public Ui_DlgSettingsImportExport {};
} // namespace Ui
} // namespace MeshGui

#endif // UI_DLGSETTINGSIMPORTEXPORT_H
