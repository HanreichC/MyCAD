/********************************************************************************
** Form generated from reading UI file 'DlgExportStep.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEXPORTSTEP_H
#define UI_DLGEXPORTSTEP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace PartGui {

class Ui_DlgExportStep
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QLabel *label;
    QComboBox *comboBoxUnits;
    QComboBox *comboBoxSchema;
    Gui::PrefCheckBox *checkBoxExportLegacy;
    Gui::PrefCheckBox *checkBoxKeepPlacement;
    Gui::PrefCheckBox *checkBoxExportHiddenObj;
    QCheckBox *checkBoxPcurves;

    void setupUi(QWidget *PartGui__DlgExportStep)
    {
        if (PartGui__DlgExportStep->objectName().isEmpty())
            PartGui__DlgExportStep->setObjectName("PartGui__DlgExportStep");
        PartGui__DlgExportStep->resize(445, 278);
        gridLayout_4 = new QGridLayout(PartGui__DlgExportStep);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_4->setObjectName("gridLayout_4");
        groupBox = new QGroupBox(PartGui__DlgExportStep);
        groupBox->setObjectName("groupBox");
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName("gridLayout_3");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout_3->addWidget(label_2, 6, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout_3->addWidget(label, 5, 0, 1, 1);

        comboBoxUnits = new QComboBox(groupBox);
        comboBoxUnits->addItem(QString());
        comboBoxUnits->addItem(QString());
        comboBoxUnits->addItem(QString());
        comboBoxUnits->setObjectName("comboBoxUnits");

        gridLayout_3->addWidget(comboBoxUnits, 5, 1, 1, 1);

        comboBoxSchema = new QComboBox(groupBox);
        comboBoxSchema->addItem(QString::fromUtf8("AP203"));
        comboBoxSchema->addItem(QString::fromUtf8("AP214 Committee Draft"));
        comboBoxSchema->addItem(QString::fromUtf8("AP214 Draft International Standard"));
        comboBoxSchema->addItem(QString::fromUtf8("AP214 International Standard"));
        comboBoxSchema->addItem(QString::fromUtf8("AP242 Draft International Standard"));
        comboBoxSchema->setObjectName("comboBoxSchema");

        gridLayout_3->addWidget(comboBoxSchema, 6, 1, 1, 1);

        checkBoxExportLegacy = new Gui::PrefCheckBox(groupBox);
        checkBoxExportLegacy->setObjectName("checkBoxExportLegacy");
        checkBoxExportLegacy->setProperty("prefEntry", QVariant(QByteArray("ExportLegacy")));
        checkBoxExportLegacy->setProperty("prefPath", QVariant(QByteArray("Mod/Import")));

        gridLayout_3->addWidget(checkBoxExportLegacy, 4, 0, 1, 2);

        checkBoxKeepPlacement = new Gui::PrefCheckBox(groupBox);
        checkBoxKeepPlacement->setObjectName("checkBoxKeepPlacement");
        checkBoxKeepPlacement->setProperty("prefEntry", QVariant(QByteArray("ExportKeepPlacement")));
        checkBoxKeepPlacement->setProperty("prefPath", QVariant(QByteArray("Mod/Import")));

        gridLayout_3->addWidget(checkBoxKeepPlacement, 3, 0, 1, 1);

        checkBoxExportHiddenObj = new Gui::PrefCheckBox(groupBox);
        checkBoxExportHiddenObj->setObjectName("checkBoxExportHiddenObj");
        checkBoxExportHiddenObj->setProperty("prefEntry", QVariant(QByteArray("ExportHiddenObject")));
        checkBoxExportHiddenObj->setProperty("prefPath", QVariant(QByteArray("Mod/Import")));

        gridLayout_3->addWidget(checkBoxExportHiddenObj, 2, 0, 1, 2);

        checkBoxPcurves = new QCheckBox(groupBox);
        checkBoxPcurves->setObjectName("checkBoxPcurves");

        gridLayout_3->addWidget(checkBoxPcurves, 1, 0, 1, 2);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        QWidget::setTabOrder(checkBoxPcurves, checkBoxExportHiddenObj);

        retranslateUi(PartGui__DlgExportStep);

        QMetaObject::connectSlotsByName(PartGui__DlgExportStep);
    } // setupUi

    void retranslateUi(QWidget *PartGui__DlgExportStep)
    {
        PartGui__DlgExportStep->setWindowTitle(QCoreApplication::translate("PartGui::DlgExportStep", "STEP Export Settings", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::DlgExportStep", "Export", nullptr));
        label_2->setText(QCoreApplication::translate("PartGui::DlgExportStep", "Scheme", nullptr));
        label->setText(QCoreApplication::translate("PartGui::DlgExportStep", "Units for export of STEP", nullptr));
        comboBoxUnits->setItemText(0, QCoreApplication::translate("PartGui::DlgExportStep", "Millimeter", nullptr));
        comboBoxUnits->setItemText(1, QCoreApplication::translate("PartGui::DlgExportStep", "Meter", nullptr));
        comboBoxUnits->setItemText(2, QCoreApplication::translate("PartGui::DlgExportStep", "Inch", nullptr));


        checkBoxExportLegacy->setText(QCoreApplication::translate("PartGui::DlgExportStep", "Use legacy export function", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxKeepPlacement->setToolTip(QCoreApplication::translate("PartGui::DlgExportStep", "Keeps the placement information when exporting\n"
"a single object. When importing back the STEP file, the\n"
"placement will be encoded into the shape geometry, instead of keeping\n"
"it inside the placement property.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxKeepPlacement->setText(QCoreApplication::translate("PartGui::DlgExportStep", "Export single object placement", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxExportHiddenObj->setToolTip(QCoreApplication::translate("PartGui::DlgExportStep", "Uncheck this to skip invisible objects when exporting, which is useful for CADs that do not support invisibility STEP styling.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxExportHiddenObj->setText(QCoreApplication::translate("PartGui::DlgExportStep", "Export invisible objects", nullptr));
        checkBoxPcurves->setText(QCoreApplication::translate("PartGui::DlgExportStep", "Write out curves in parametric space of surface", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgExportStep: public Ui_DlgExportStep {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGEXPORTSTEP_H
