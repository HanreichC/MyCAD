/********************************************************************************
** Form generated from reading UI file 'DlgSettings3DViewPart.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGS3DVIEWPART_H
#define UI_DLGSETTINGS3DVIEWPART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace PartGui {

class Ui_DlgSettings3DViewPart
{
public:
    QGridLayout *gridLayout;
    QGroupBox *GroupBox12;
    QGridLayout *gridLayout1;
    QGridLayout *gridLayout2;
    QLabel *textLabel1;
    Gui::PrefDoubleSpinBox *maxDeviation;
    QLabel *label;
    Gui::PrefDoubleSpinBox *maxAngularDeflection;
    QSpacerItem *spacerItem;

    void setupUi(QWidget *PartGui__DlgSettings3DViewPart)
    {
        if (PartGui__DlgSettings3DViewPart->objectName().isEmpty())
            PartGui__DlgSettings3DViewPart->setObjectName("PartGui__DlgSettings3DViewPart");
        PartGui__DlgSettings3DViewPart->resize(539, 339);
        gridLayout = new QGridLayout(PartGui__DlgSettings3DViewPart);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        gridLayout->setObjectName("gridLayout");
        GroupBox12 = new QGroupBox(PartGui__DlgSettings3DViewPart);
        GroupBox12->setObjectName("GroupBox12");
        gridLayout1 = new QGridLayout(GroupBox12);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        gridLayout2->setObjectName("gridLayout2");
        textLabel1 = new QLabel(GroupBox12);
        textLabel1->setObjectName("textLabel1");

        gridLayout2->addWidget(textLabel1, 0, 0, 1, 1);

        maxDeviation = new Gui::PrefDoubleSpinBox(GroupBox12);
        maxDeviation->setObjectName("maxDeviation");
        maxDeviation->setSuffix(QString::fromUtf8(" %"));
        maxDeviation->setDecimals(4);
        maxDeviation->setMinimum(0.010000000000000);
        maxDeviation->setMaximum(100.000000000000000);
        maxDeviation->setSingleStep(0.010000000000000);
        maxDeviation->setValue(0.500000000000000);
        maxDeviation->setProperty("prefEntry", QVariant(QByteArray("MeshDeviation")));
        maxDeviation->setProperty("prefPath", QVariant(QByteArray("Mod/Part")));

        gridLayout2->addWidget(maxDeviation, 0, 1, 1, 1);

        label = new QLabel(GroupBox12);
        label->setObjectName("label");

        gridLayout2->addWidget(label, 1, 0, 1, 1);

        maxAngularDeflection = new Gui::PrefDoubleSpinBox(GroupBox12);
        maxAngularDeflection->setObjectName("maxAngularDeflection");
        maxAngularDeflection->setSuffix(QString::fromUtf8(" \302\260"));
        maxAngularDeflection->setDecimals(2);
        maxAngularDeflection->setMinimum(1.000000000000000);
        maxAngularDeflection->setMaximum(180.000000000000000);
        maxAngularDeflection->setSingleStep(0.500000000000000);
        maxAngularDeflection->setValue(28.500000000000000);
        maxAngularDeflection->setProperty("prefEntry", QVariant(QByteArray("MeshAngularDeflection")));
        maxAngularDeflection->setProperty("prefPath", QVariant(QByteArray("Mod/Part")));

        gridLayout2->addWidget(maxAngularDeflection, 1, 1, 1, 1);


        gridLayout1->addLayout(gridLayout2, 0, 0, 1, 1);


        gridLayout->addWidget(GroupBox12, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(20, 61, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(spacerItem, 1, 0, 1, 1);


        retranslateUi(PartGui__DlgSettings3DViewPart);

        QMetaObject::connectSlotsByName(PartGui__DlgSettings3DViewPart);
    } // setupUi

    void retranslateUi(QWidget *PartGui__DlgSettings3DViewPart)
    {
        PartGui__DlgSettings3DViewPart->setWindowTitle(QCoreApplication::translate("PartGui::DlgSettings3DViewPart", "Shape View", nullptr));
        GroupBox12->setTitle(QCoreApplication::translate("PartGui::DlgSettings3DViewPart", "Tessellation", nullptr));
#if QT_CONFIG(tooltip)
        textLabel1->setToolTip(QCoreApplication::translate("PartGui::DlgSettings3DViewPart", "Defines the deviation of tessellation to the actual surface", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        textLabel1->setWhatsThis(QCoreApplication::translate("PartGui::DlgSettings3DViewPart", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-size:7.8pt; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Tessellation</span></p><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"><span style=\" font-weight:400;\">Defines the maximum deviation of the tessellated mesh to the surface. The smaller the value is the slower the render speed which results in increased detail/resolution.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        textLabel1->setText(QCoreApplication::translate("PartGui::DlgSettings3DViewPart", "Maximum deviation depending on the model bounding box", nullptr));
        label->setText(QCoreApplication::translate("PartGui::DlgSettings3DViewPart", "Maximum angular deflection", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgSettings3DViewPart: public Ui_DlgSettings3DViewPart {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGSETTINGS3DVIEWPART_H
