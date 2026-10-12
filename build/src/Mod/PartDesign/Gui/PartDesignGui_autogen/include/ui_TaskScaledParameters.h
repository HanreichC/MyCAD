/********************************************************************************
** Form generated from reading UI file 'TaskScaledParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKSCALEDPARAMETERS_H
#define UI_TASKSCALEDPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"
#include "Gui/SpinBox.h"

namespace PartDesignGui {

class Ui_TaskScaledParameters
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    Gui::QuantitySpinBox *spinFactor;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    Gui::UIntSpinBox *spinOccurrences;

    void setupUi(QWidget *PartDesignGui__TaskScaledParameters)
    {
        if (PartDesignGui__TaskScaledParameters->objectName().isEmpty())
            PartDesignGui__TaskScaledParameters->setObjectName("PartDesignGui__TaskScaledParameters");
        PartDesignGui__TaskScaledParameters->resize(253, 85);
        PartDesignGui__TaskScaledParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskScaledParameters);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(PartDesignGui__TaskScaledParameters);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        spinFactor = new Gui::QuantitySpinBox(PartDesignGui__TaskScaledParameters);
        spinFactor->setObjectName("spinFactor");

        horizontalLayout_2->addWidget(spinFactor);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(PartDesignGui__TaskScaledParameters);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        spinOccurrences = new Gui::UIntSpinBox(PartDesignGui__TaskScaledParameters);
        spinOccurrences->setObjectName("spinOccurrences");

        horizontalLayout->addWidget(spinOccurrences);


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(spinFactor, spinOccurrences);

        retranslateUi(PartDesignGui__TaskScaledParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskScaledParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskScaledParameters)
    {
        label_2->setText(QCoreApplication::translate("PartDesignGui::TaskScaledParameters", "Factor", nullptr));
        label->setText(QCoreApplication::translate("PartDesignGui::TaskScaledParameters", "Occurrences", nullptr));
        (void)PartDesignGui__TaskScaledParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskScaledParameters: public Ui_TaskScaledParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKSCALEDPARAMETERS_H
