/********************************************************************************
** Form generated from reading UI file 'DlgLocationAngle.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLOCATIONANGLE_H
#define UI_DLGLOCATIONANGLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Angle
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *vectorA;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *vectorB;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *vectorC;
    QCheckBox *checkBoxSnap;
    QComboBox *comboGridSize;

    void setupUi(QWidget *Angle)
    {
        if (Angle->objectName().isEmpty())
            Angle->setObjectName("Angle");
        Angle->resize(145, 147);
        Angle->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(Angle);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Angle);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        vectorA = new QDoubleSpinBox(Angle);
        vectorA->setObjectName("vectorA");
        vectorA->setMinimum(-2147480000.000000000000000);
        vectorA->setMaximum(2147480000.000000000000000);

        horizontalLayout->addWidget(vectorA);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(Angle);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        vectorB = new QDoubleSpinBox(Angle);
        vectorB->setObjectName("vectorB");
        vectorB->setMinimum(-2147480000.000000000000000);
        vectorB->setMaximum(2147480000.000000000000000);

        horizontalLayout_2->addWidget(vectorB);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(Angle);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        vectorC = new QDoubleSpinBox(Angle);
        vectorC->setObjectName("vectorC");
        vectorC->setMinimum(-2147480000.000000000000000);
        vectorC->setMaximum(2147480000.000000000000000);
        vectorC->setValue(1.000000000000000);

        horizontalLayout_3->addWidget(vectorC);


        verticalLayout->addLayout(horizontalLayout_3);

        checkBoxSnap = new QCheckBox(Angle);
        checkBoxSnap->setObjectName("checkBoxSnap");

        verticalLayout->addWidget(checkBoxSnap);

        comboGridSize = new QComboBox(Angle);
        comboGridSize->addItem(QString::fromUtf8("1 \302\260"));
        comboGridSize->addItem(QString::fromUtf8("2 \302\260"));
        comboGridSize->addItem(QString::fromUtf8("5 \302\260"));
        comboGridSize->addItem(QString::fromUtf8("10 \302\260"));
        comboGridSize->addItem(QString::fromUtf8("20 \302\260"));
        comboGridSize->addItem(QString::fromUtf8("45 \302\260"));
        comboGridSize->addItem(QString::fromUtf8("90 \302\260"));
        comboGridSize->addItem(QString::fromUtf8("180 \302\260"));
        comboGridSize->setObjectName("comboGridSize");
        comboGridSize->setEditable(true);

        verticalLayout->addWidget(comboGridSize);


        retranslateUi(Angle);

        QMetaObject::connectSlotsByName(Angle);
    } // setupUi

    void retranslateUi(QWidget *Angle)
    {
        label->setText(QCoreApplication::translate("Angle", "A", nullptr));
        label_2->setText(QCoreApplication::translate("Angle", "B", nullptr));
        label_3->setText(QCoreApplication::translate("Angle", "C", nullptr));
        checkBoxSnap->setText(QCoreApplication::translate("Angle", "Angle snap", nullptr));

        (void)Angle;
    } // retranslateUi

};

namespace Ui {
    class Angle: public Ui_Angle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLOCATIONANGLE_H
