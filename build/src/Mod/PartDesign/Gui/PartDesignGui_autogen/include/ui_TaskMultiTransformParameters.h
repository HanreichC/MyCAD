/********************************************************************************
** Form generated from reading UI file 'TaskMultiTransformParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKMULTITRANSFORMPARAMETERS_H
#define UI_TASKMULTITRANSFORMPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskMultiTransformParameters
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listTransformFeatures;
    QWidget *subFeatureWidget;
    QPushButton *buttonOK;

    void setupUi(QWidget *PartDesignGui__TaskMultiTransformParameters)
    {
        if (PartDesignGui__TaskMultiTransformParameters->objectName().isEmpty())
            PartDesignGui__TaskMultiTransformParameters->setObjectName("PartDesignGui__TaskMultiTransformParameters");
        PartDesignGui__TaskMultiTransformParameters->resize(229, 174);
        PartDesignGui__TaskMultiTransformParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskMultiTransformParameters);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(PartDesignGui__TaskMultiTransformParameters);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        listTransformFeatures = new QListWidget(PartDesignGui__TaskMultiTransformParameters);
        listTransformFeatures->setObjectName("listTransformFeatures");
        listTransformFeatures->setMaximumSize(QSize(16777215, 80));

        verticalLayout->addWidget(listTransformFeatures);

        subFeatureWidget = new QWidget(PartDesignGui__TaskMultiTransformParameters);
        subFeatureWidget->setObjectName("subFeatureWidget");

        verticalLayout->addWidget(subFeatureWidget);

        buttonOK = new QPushButton(PartDesignGui__TaskMultiTransformParameters);
        buttonOK->setObjectName("buttonOK");

        verticalLayout->addWidget(buttonOK);


        retranslateUi(PartDesignGui__TaskMultiTransformParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskMultiTransformParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskMultiTransformParameters)
    {
        label->setText(QCoreApplication::translate("PartDesignGui::TaskMultiTransformParameters", "Transformations", nullptr));
        buttonOK->setText(QCoreApplication::translate("PartDesignGui::TaskMultiTransformParameters", "OK", nullptr));
        (void)PartDesignGui__TaskMultiTransformParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskMultiTransformParameters: public Ui_TaskMultiTransformParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKMULTITRANSFORMPARAMETERS_H
