/********************************************************************************
** Form generated from reading UI file 'TaskMirroredParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKMIRROREDPARAMETERS_H
#define UI_TASKMIRROREDPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskMirroredParameters
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPlane;
    QComboBox *comboPlane;

    void setupUi(QWidget *PartDesignGui__TaskMirroredParameters)
    {
        if (PartDesignGui__TaskMirroredParameters->objectName().isEmpty())
            PartDesignGui__TaskMirroredParameters->setObjectName("PartDesignGui__TaskMirroredParameters");
        PartDesignGui__TaskMirroredParameters->resize(253, 55);
        PartDesignGui__TaskMirroredParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskMirroredParameters);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelPlane = new QLabel(PartDesignGui__TaskMirroredParameters);
        labelPlane->setObjectName("labelPlane");

        horizontalLayout->addWidget(labelPlane);

        comboPlane = new QComboBox(PartDesignGui__TaskMirroredParameters);
        comboPlane->setObjectName("comboPlane");

        horizontalLayout->addWidget(comboPlane);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PartDesignGui__TaskMirroredParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskMirroredParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskMirroredParameters)
    {
        labelPlane->setText(QCoreApplication::translate("PartDesignGui::TaskMirroredParameters", "Plane", nullptr));
        (void)PartDesignGui__TaskMirroredParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskMirroredParameters: public Ui_TaskMirroredParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKMIRROREDPARAMETERS_H
