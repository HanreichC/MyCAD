/********************************************************************************
** Form generated from reading UI file 'TaskPreviewParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKPREVIEWPARAMETERS_H
#define UI_TASKPREVIEWPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskPreviewParameters
{
public:
    QVBoxLayout *verticalLayout_4;
    QCheckBox *showFinalCheckBox;
    QCheckBox *showTransparentPreviewCheckBox;

    void setupUi(QWidget *PartDesignGui__TaskPreviewParameters)
    {
        if (PartDesignGui__TaskPreviewParameters->objectName().isEmpty())
            PartDesignGui__TaskPreviewParameters->setObjectName("PartDesignGui__TaskPreviewParameters");
        PartDesignGui__TaskPreviewParameters->resize(364, 62);
        PartDesignGui__TaskPreviewParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout_4 = new QVBoxLayout(PartDesignGui__TaskPreviewParameters);
        verticalLayout_4->setObjectName("verticalLayout_4");
        showFinalCheckBox = new QCheckBox(PartDesignGui__TaskPreviewParameters);
        showFinalCheckBox->setObjectName("showFinalCheckBox");

        verticalLayout_4->addWidget(showFinalCheckBox);

        showTransparentPreviewCheckBox = new QCheckBox(PartDesignGui__TaskPreviewParameters);
        showTransparentPreviewCheckBox->setObjectName("showTransparentPreviewCheckBox");

        verticalLayout_4->addWidget(showTransparentPreviewCheckBox);


        retranslateUi(PartDesignGui__TaskPreviewParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskPreviewParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskPreviewParameters)
    {
        showFinalCheckBox->setText(QCoreApplication::translate("PartDesignGui::TaskPreviewParameters", "Show final result", nullptr));
        showTransparentPreviewCheckBox->setText(QCoreApplication::translate("PartDesignGui::TaskPreviewParameters", "Show preview overlay", nullptr));
        (void)PartDesignGui__TaskPreviewParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskPreviewParameters: public Ui_TaskPreviewParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKPREVIEWPARAMETERS_H
