/********************************************************************************
** Form generated from reading UI file 'DlgSettingsDefaultMaterial.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSDEFAULTMATERIAL_H
#define UI_DLGSETTINGSDEFAULTMATERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Mod/Material/Gui/MaterialTreeWidget.h"

namespace MatGui {

class Ui_DlgSettingsDefaultMaterial
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    MatGui::PrefMaterialTreeWidget *widgetMaterial;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MatGui__DlgSettingsDefaultMaterial)
    {
        if (MatGui__DlgSettingsDefaultMaterial->objectName().isEmpty())
            MatGui__DlgSettingsDefaultMaterial->setObjectName("MatGui__DlgSettingsDefaultMaterial");
        MatGui__DlgSettingsDefaultMaterial->resize(400, 300);
        verticalLayout = new QVBoxLayout(MatGui__DlgSettingsDefaultMaterial);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(MatGui__DlgSettingsDefaultMaterial);
        groupBox->setObjectName("groupBox");
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widgetMaterial = new MatGui::PrefMaterialTreeWidget(groupBox);
        widgetMaterial->setObjectName("widgetMaterial");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetMaterial->sizePolicy().hasHeightForWidth());
        widgetMaterial->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(widgetMaterial);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(MatGui__DlgSettingsDefaultMaterial);

        QMetaObject::connectSlotsByName(MatGui__DlgSettingsDefaultMaterial);
    } // setupUi

    void retranslateUi(QWidget *MatGui__DlgSettingsDefaultMaterial)
    {
        MatGui__DlgSettingsDefaultMaterial->setWindowTitle(QCoreApplication::translate("MatGui::DlgSettingsDefaultMaterial", "Default Material", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MatGui::DlgSettingsDefaultMaterial", "Default Material", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class DlgSettingsDefaultMaterial: public Ui_DlgSettingsDefaultMaterial {};
} // namespace Ui
} // namespace MatGui

#endif // UI_DLGSETTINGSDEFAULTMATERIAL_H
