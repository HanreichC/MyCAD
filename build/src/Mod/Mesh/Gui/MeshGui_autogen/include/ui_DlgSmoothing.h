/********************************************************************************
** Form generated from reading UI file 'DlgSmoothing.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSMOOTHING_H
#define UI_DLGSMOOTHING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

namespace MeshGui {

class Ui_DlgSmoothing
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonTaubin;
    QRadioButton *radioButtonLaplace;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSpinBox *iterations;
    QLabel *labelLambda;
    QDoubleSpinBox *spinLambda;
    QLabel *labelMu;
    QDoubleSpinBox *spinMicro;
    QCheckBox *checkBoxSelection;

    void setupUi(QWidget *MeshGui__DlgSmoothing)
    {
        if (MeshGui__DlgSmoothing->objectName().isEmpty())
            MeshGui__DlgSmoothing->setObjectName("MeshGui__DlgSmoothing");
        MeshGui__DlgSmoothing->resize(210, 227);
        MeshGui__DlgSmoothing->setProperty("sizeGripEnabled", QVariant(true));
        gridLayout_3 = new QGridLayout(MeshGui__DlgSmoothing);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox_3 = new QGroupBox(MeshGui__DlgSmoothing);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        radioButtonTaubin = new QRadioButton(groupBox_3);
        radioButtonTaubin->setObjectName("radioButtonTaubin");
        radioButtonTaubin->setChecked(true);

        gridLayout->addWidget(radioButtonTaubin, 0, 0, 1, 1);

        radioButtonLaplace = new QRadioButton(groupBox_3);
        radioButtonLaplace->setObjectName("radioButtonLaplace");

        gridLayout->addWidget(radioButtonLaplace, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(MeshGui__DlgSmoothing);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        iterations = new QSpinBox(groupBox_2);
        iterations->setObjectName("iterations");
        iterations->setMinimum(1);
        iterations->setValue(4);

        gridLayout_2->addWidget(iterations, 0, 1, 1, 1);

        labelLambda = new QLabel(groupBox_2);
        labelLambda->setObjectName("labelLambda");

        gridLayout_2->addWidget(labelLambda, 1, 0, 1, 1);

        spinLambda = new QDoubleSpinBox(groupBox_2);
        spinLambda->setObjectName("spinLambda");
        spinLambda->setDecimals(4);
        spinLambda->setMaximum(1.000000000000000);
        spinLambda->setSingleStep(0.001000000000000);
        spinLambda->setValue(0.630700000000000);

        gridLayout_2->addWidget(spinLambda, 1, 1, 1, 1);

        labelMu = new QLabel(groupBox_2);
        labelMu->setObjectName("labelMu");

        gridLayout_2->addWidget(labelMu, 2, 0, 1, 1);

        spinMicro = new QDoubleSpinBox(groupBox_2);
        spinMicro->setObjectName("spinMicro");
        spinMicro->setDecimals(4);
        spinMicro->setMaximum(1.000000000000000);
        spinMicro->setSingleStep(0.001000000000000);
        spinMicro->setValue(0.042400000000000);

        gridLayout_2->addWidget(spinMicro, 2, 1, 1, 1);

        checkBoxSelection = new QCheckBox(groupBox_2);
        checkBoxSelection->setObjectName("checkBoxSelection");

        gridLayout_2->addWidget(checkBoxSelection, 3, 0, 1, 2);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(MeshGui__DlgSmoothing);

        QMetaObject::connectSlotsByName(MeshGui__DlgSmoothing);
    } // setupUi

    void retranslateUi(QWidget *MeshGui__DlgSmoothing)
    {
        MeshGui__DlgSmoothing->setWindowTitle(QCoreApplication::translate("MeshGui::DlgSmoothing", "Smoothing", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MeshGui::DlgSmoothing", "Method", nullptr));
        radioButtonTaubin->setText(QCoreApplication::translate("MeshGui::DlgSmoothing", "Taubin", nullptr));
        radioButtonLaplace->setText(QCoreApplication::translate("MeshGui::DlgSmoothing", "Laplace", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MeshGui::DlgSmoothing", "Parameter", nullptr));
        label->setText(QCoreApplication::translate("MeshGui::DlgSmoothing", "Iterations", nullptr));
        labelLambda->setText(QCoreApplication::translate("MeshGui::DlgSmoothing", "Lambda", nullptr));
        labelMu->setText(QCoreApplication::translate("MeshGui::DlgSmoothing", "Mu", nullptr));
        checkBoxSelection->setText(QCoreApplication::translate("MeshGui::DlgSmoothing", "Only selection", nullptr));
    } // retranslateUi

};

} // namespace MeshGui

namespace MeshGui {
namespace Ui {
    class DlgSmoothing: public Ui_DlgSmoothing {};
} // namespace Ui
} // namespace MeshGui

#endif // UI_DLGSMOOTHING_H
