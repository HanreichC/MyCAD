/********************************************************************************
** Form generated from reading UI file 'InsertDatum.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERTDATUM_H
#define UI_INSERTDATUM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include "Gui/PrefWidgets.h"
#include "Gui/QuantitySpinBox.h"

namespace SketcherGui {

class Ui_InsertDatum
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    Gui::PrefQuantitySpinBox *labelEdit;
    QLabel *label_2;
    QLineEdit *name;
    QHBoxLayout *layoutType;
    QRadioButton *rbRadius;
    QRadioButton *rbDiameter;
    QCheckBox *cbDriving;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SketcherGui__InsertDatum)
    {
        if (SketcherGui__InsertDatum->objectName().isEmpty())
            SketcherGui__InsertDatum->setObjectName("SketcherGui__InsertDatum");
        SketcherGui__InsertDatum->setWindowModality(Qt::ApplicationModal);
        SketcherGui__InsertDatum->resize(254, 140);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SketcherGui__InsertDatum->sizePolicy().hasHeightForWidth());
        SketcherGui__InsertDatum->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(SketcherGui__InsertDatum);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(SketcherGui__InsertDatum);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        labelEdit = new Gui::PrefQuantitySpinBox(SketcherGui__InsertDatum);
        labelEdit->setObjectName("labelEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelEdit->sizePolicy().hasHeightForWidth());
        labelEdit->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(labelEdit, 0, 1, 1, 1);

        label_2 = new QLabel(SketcherGui__InsertDatum);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        name = new QLineEdit(SketcherGui__InsertDatum);
        name->setObjectName("name");
        sizePolicy1.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
        name->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(name, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        layoutType = new QHBoxLayout();
        layoutType->setObjectName("layoutType");
        rbRadius = new QRadioButton(SketcherGui__InsertDatum);
        rbRadius->setObjectName("rbRadius");

        layoutType->addWidget(rbRadius);

        rbDiameter = new QRadioButton(SketcherGui__InsertDatum);
        rbDiameter->setObjectName("rbDiameter");

        layoutType->addWidget(rbDiameter);


        verticalLayout->addLayout(layoutType);

        cbDriving = new QCheckBox(SketcherGui__InsertDatum);
        cbDriving->setObjectName("cbDriving");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cbDriving->sizePolicy().hasHeightForWidth());
        cbDriving->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(cbDriving);

        buttonBox = new QDialogButtonBox(SketcherGui__InsertDatum);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SketcherGui__InsertDatum);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SketcherGui__InsertDatum, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SketcherGui__InsertDatum, qOverload<>(&QDialog::reject));
        QObject::connect(labelEdit, SIGNAL(showFormulaDialog(bool)), buttonBox, SLOT(setHidden(bool)));

        QMetaObject::connectSlotsByName(SketcherGui__InsertDatum);
    } // setupUi

    void retranslateUi(QDialog *SketcherGui__InsertDatum)
    {
        SketcherGui__InsertDatum->setWindowTitle(QCoreApplication::translate("SketcherGui::InsertDatum", "Insert Datum", nullptr));
        label->setText(QCoreApplication::translate("SketcherGui::InsertDatum", "Datum", nullptr));
        label_2->setText(QCoreApplication::translate("SketcherGui::InsertDatum", "Name", nullptr));
#if QT_CONFIG(tooltip)
        name->setToolTip(QCoreApplication::translate("SketcherGui::InsertDatum", "Constraint name (available for expressions)", nullptr));
#endif // QT_CONFIG(tooltip)
        rbRadius->setText(QCoreApplication::translate("SketcherGui::InsertDatum", "Radius", nullptr));
        rbDiameter->setText(QCoreApplication::translate("SketcherGui::InsertDatum", "Diameter", nullptr));
#if QT_CONFIG(tooltip)
        cbDriving->setToolTip(QCoreApplication::translate("SketcherGui::InsertDatum", "Reference (or constraint) dimension", nullptr));
#endif // QT_CONFIG(tooltip)
        cbDriving->setText(QCoreApplication::translate("SketcherGui::InsertDatum", "Reference", nullptr));
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class InsertDatum: public Ui_InsertDatum {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_INSERTDATUM_H
