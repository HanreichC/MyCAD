/********************************************************************************
** Form generated from reading UI file 'SketcherRegularPolygonDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKETCHERREGULARPOLYGONDIALOG_H
#define UI_SKETCHERREGULARPOLYGONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "Gui/PrefWidgets.h"

namespace SketcherGui {

class Ui_SketcherRegularPolygonDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    Gui::PrefSpinBox *sidesQuantitySpinBox;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SketcherGui__SketcherRegularPolygonDialog)
    {
        if (SketcherGui__SketcherRegularPolygonDialog->objectName().isEmpty())
            SketcherGui__SketcherRegularPolygonDialog->setObjectName("SketcherGui__SketcherRegularPolygonDialog");
        SketcherGui__SketcherRegularPolygonDialog->setWindowModality(Qt::ApplicationModal);
        SketcherGui__SketcherRegularPolygonDialog->resize(287, 86);
        verticalLayout = new QVBoxLayout(SketcherGui__SketcherRegularPolygonDialog);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(SketcherGui__SketcherRegularPolygonDialog);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        sidesQuantitySpinBox = new Gui::PrefSpinBox(SketcherGui__SketcherRegularPolygonDialog);
        sidesQuantitySpinBox->setObjectName("sidesQuantitySpinBox");
        sidesQuantitySpinBox->setMinimum(3);
        sidesQuantitySpinBox->setValue(9);
        sidesQuantitySpinBox->setProperty("prefEntry", QVariant(QByteArray("DefaultRegularPolygonSides")));
        sidesQuantitySpinBox->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        horizontalLayout->addWidget(sidesQuantitySpinBox);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(SketcherGui__SketcherRegularPolygonDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SketcherGui__SketcherRegularPolygonDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SketcherGui__SketcherRegularPolygonDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SketcherGui__SketcherRegularPolygonDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SketcherGui__SketcherRegularPolygonDialog);
    } // setupUi

    void retranslateUi(QDialog *SketcherGui__SketcherRegularPolygonDialog)
    {
        SketcherGui__SketcherRegularPolygonDialog->setWindowTitle(QCoreApplication::translate("SketcherGui::SketcherRegularPolygonDialog", "Create Regular Polygon", nullptr));
        label->setText(QCoreApplication::translate("SketcherGui::SketcherRegularPolygonDialog", "Number of sides", nullptr));
#if QT_CONFIG(tooltip)
        sidesQuantitySpinBox->setToolTip(QCoreApplication::translate("SketcherGui::SketcherRegularPolygonDialog", "Number of columns of the linear array", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class SketcherRegularPolygonDialog: public Ui_SketcherRegularPolygonDialog {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_SKETCHERREGULARPOLYGONDIALOG_H
