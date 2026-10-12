/********************************************************************************
** Form generated from reading UI file 'DlgMaterial.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGMATERIAL_H
#define UI_DLGMATERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include "Mod/Material/Gui/MaterialTreeWidget.h"

namespace MatGui {

class Ui_DlgMaterial
{
public:
    QGridLayout *gridLayout_4;
    QHBoxLayout *hboxLayout;
    MatGui::MaterialTreeWidget *widgetMaterial;

    void setupUi(QDialog *MatGui__DlgMaterial)
    {
        if (MatGui__DlgMaterial->objectName().isEmpty())
            MatGui__DlgMaterial->setObjectName("MatGui__DlgMaterial");
        MatGui__DlgMaterial->resize(290, 503);
        gridLayout_4 = new QGridLayout(MatGui__DlgMaterial);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        widgetMaterial = new MatGui::MaterialTreeWidget(MatGui__DlgMaterial);
        widgetMaterial->setObjectName("widgetMaterial");

        hboxLayout->addWidget(widgetMaterial);


        gridLayout_4->addLayout(hboxLayout, 0, 0, 1, 1);


        retranslateUi(MatGui__DlgMaterial);

        QMetaObject::connectSlotsByName(MatGui__DlgMaterial);
    } // setupUi

    void retranslateUi(QDialog *MatGui__DlgMaterial)
    {
        MatGui__DlgMaterial->setWindowTitle(QCoreApplication::translate("MatGui::DlgMaterial", "Material", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class DlgMaterial: public Ui_DlgMaterial {};
} // namespace Ui
} // namespace MatGui

#endif // UI_DLGMATERIAL_H
