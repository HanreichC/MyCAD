/********************************************************************************
** Form generated from reading UI file 'ShapeFromMesh.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAPEFROMMESH_H
#define UI_SHAPEFROMMESH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

namespace PartGui {

class Ui_ShapeFromMesh
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBoxSew;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PartGui__ShapeFromMesh)
    {
        if (PartGui__ShapeFromMesh->objectName().isEmpty())
            PartGui__ShapeFromMesh->setObjectName("PartGui__ShapeFromMesh");
        PartGui__ShapeFromMesh->resize(349, 148);
        gridLayout_2 = new QGridLayout(PartGui__ShapeFromMesh);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBoxSew = new QGroupBox(PartGui__ShapeFromMesh);
        groupBoxSew->setObjectName("groupBoxSew");
        groupBoxSew->setCheckable(true);
        groupBoxSew->setChecked(true);
        gridLayout = new QGridLayout(groupBoxSew);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBoxSew);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(groupBoxSew);
        doubleSpinBox->setObjectName("doubleSpinBox");

        gridLayout->addWidget(doubleSpinBox, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBoxSew, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(PartGui__ShapeFromMesh);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(PartGui__ShapeFromMesh);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, PartGui__ShapeFromMesh, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, PartGui__ShapeFromMesh, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(PartGui__ShapeFromMesh);
    } // setupUi

    void retranslateUi(QDialog *PartGui__ShapeFromMesh)
    {
        PartGui__ShapeFromMesh->setWindowTitle(QCoreApplication::translate("PartGui::ShapeFromMesh", "Shape From Mesh", nullptr));
        groupBoxSew->setTitle(QCoreApplication::translate("PartGui::ShapeFromMesh", "Sew Shape", nullptr));
        label->setText(QCoreApplication::translate("PartGui::ShapeFromMesh", "Tolerance for sewing the shape", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class ShapeFromMesh: public Ui_ShapeFromMesh {};
} // namespace Ui
} // namespace PartGui

#endif // UI_SHAPEFROMMESH_H
