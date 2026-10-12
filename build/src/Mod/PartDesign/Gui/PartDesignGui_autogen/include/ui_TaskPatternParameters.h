/********************************************************************************
** Form generated from reading UI file 'TaskPatternParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKPATTERNPARAMETERS_H
#define UI_TASKPATTERNPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskPatternParameters
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *parametersWidgetPlaceholder;
    QWidget *parametersWidgetPlaceholder2;

    void setupUi(QWidget *PartDesignGui__TaskPatternParameters)
    {
        if (PartDesignGui__TaskPatternParameters->objectName().isEmpty())
            PartDesignGui__TaskPatternParameters->setObjectName("PartDesignGui__TaskPatternParameters");
        PartDesignGui__TaskPatternParameters->resize(270, 200);
        PartDesignGui__TaskPatternParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskPatternParameters);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        parametersWidgetPlaceholder = new QWidget(PartDesignGui__TaskPatternParameters);
        parametersWidgetPlaceholder->setObjectName("parametersWidgetPlaceholder");

        verticalLayout->addWidget(parametersWidgetPlaceholder);

        parametersWidgetPlaceholder2 = new QWidget(PartDesignGui__TaskPatternParameters);
        parametersWidgetPlaceholder2->setObjectName("parametersWidgetPlaceholder2");

        verticalLayout->addWidget(parametersWidgetPlaceholder2);


        retranslateUi(PartDesignGui__TaskPatternParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskPatternParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskPatternParameters)
    {
        (void)PartDesignGui__TaskPatternParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskPatternParameters: public Ui_TaskPatternParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKPATTERNPARAMETERS_H
