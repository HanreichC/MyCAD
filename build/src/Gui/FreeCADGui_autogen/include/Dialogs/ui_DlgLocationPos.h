/********************************************************************************
** Form generated from reading UI file 'DlgLocationPos.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLOCATIONPOS_H
#define UI_DLGLOCATIONPOS_H

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

class Ui_Position
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *vectorX;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *vectorY;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *vectorZ;
    QCheckBox *checkBox;
    QComboBox *comboBoxGridSize;

    void setupUi(QWidget *Position)
    {
        if (Position->objectName().isEmpty())
            Position->setObjectName("Position");
        Position->resize(171, 178);
        Position->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(Position);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Position);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        vectorX = new QDoubleSpinBox(Position);
        vectorX->setObjectName("vectorX");
        vectorX->setMinimum(-2147480000.000000000000000);
        vectorX->setMaximum(2147480000.000000000000000);

        horizontalLayout->addWidget(vectorX);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(Position);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        vectorY = new QDoubleSpinBox(Position);
        vectorY->setObjectName("vectorY");
        vectorY->setMinimum(-2147480000.000000000000000);
        vectorY->setMaximum(2147480000.000000000000000);

        horizontalLayout_2->addWidget(vectorY);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(Position);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        vectorZ = new QDoubleSpinBox(Position);
        vectorZ->setObjectName("vectorZ");
        vectorZ->setMinimum(-2147480000.000000000000000);
        vectorZ->setMaximum(2147480000.000000000000000);
        vectorZ->setValue(1.000000000000000);

        horizontalLayout_3->addWidget(vectorZ);


        verticalLayout->addLayout(horizontalLayout_3);

        checkBox = new QCheckBox(Position);
        checkBox->setObjectName("checkBox");

        verticalLayout->addWidget(checkBox);

        comboBoxGridSize = new QComboBox(Position);
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->addItem(QString());
        comboBoxGridSize->setObjectName("comboBoxGridSize");
        comboBoxGridSize->setEditable(true);

        verticalLayout->addWidget(comboBoxGridSize);


        retranslateUi(Position);

        QMetaObject::connectSlotsByName(Position);
    } // setupUi

    void retranslateUi(QWidget *Position)
    {
        label->setText(QCoreApplication::translate("Position", "X", nullptr));
        label_2->setText(QCoreApplication::translate("Position", "Y", nullptr));
        label_3->setText(QCoreApplication::translate("Position", "Z", nullptr));
        checkBox->setText(QCoreApplication::translate("Position", "Grid snap in", nullptr));
        comboBoxGridSize->setItemText(0, QCoreApplication::translate("Position", "0.1 mm", nullptr));
        comboBoxGridSize->setItemText(1, QCoreApplication::translate("Position", "0.5 mm", nullptr));
        comboBoxGridSize->setItemText(2, QCoreApplication::translate("Position", "1 mm", nullptr));
        comboBoxGridSize->setItemText(3, QCoreApplication::translate("Position", "2 mm", nullptr));
        comboBoxGridSize->setItemText(4, QCoreApplication::translate("Position", "5 mm", nullptr));
        comboBoxGridSize->setItemText(5, QCoreApplication::translate("Position", "10 mm", nullptr));
        comboBoxGridSize->setItemText(6, QCoreApplication::translate("Position", "20 mm", nullptr));
        comboBoxGridSize->setItemText(7, QCoreApplication::translate("Position", "50 mm", nullptr));
        comboBoxGridSize->setItemText(8, QCoreApplication::translate("Position", "100 mm", nullptr));
        comboBoxGridSize->setItemText(9, QCoreApplication::translate("Position", "200 mm", nullptr));
        comboBoxGridSize->setItemText(10, QCoreApplication::translate("Position", "500 mm", nullptr));
        comboBoxGridSize->setItemText(11, QCoreApplication::translate("Position", "1 m", nullptr));
        comboBoxGridSize->setItemText(12, QCoreApplication::translate("Position", "2 m", nullptr));
        comboBoxGridSize->setItemText(13, QCoreApplication::translate("Position", "5 m", nullptr));

        (void)Position;
    } // retranslateUi

};

namespace Ui {
    class Position: public Ui_Position {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLOCATIONPOS_H
