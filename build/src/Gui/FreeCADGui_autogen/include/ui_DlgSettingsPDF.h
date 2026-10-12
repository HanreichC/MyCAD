/********************************************************************************
** Form generated from reading UI file 'DlgSettingsPDF.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSPDF_H
#define UI_DLGSETTINGSPDF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsPDF
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    Gui::PrefComboBox *comboBox;
    QLabel *warningLabel;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsPDF)
    {
        if (Gui__Dialog__DlgSettingsPDF->objectName().isEmpty())
            Gui__Dialog__DlgSettingsPDF->setObjectName("Gui__Dialog__DlgSettingsPDF");
        Gui__Dialog__DlgSettingsPDF->resize(446, 462);
        vboxLayout = new QVBoxLayout(Gui__Dialog__DlgSettingsPDF);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        vboxLayout->setObjectName("vboxLayout");
        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsPDF);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        comboBox = new Gui::PrefComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setProperty("prefEntry", QVariant(QByteArray("PDFVersion")));
        comboBox->setProperty("prefPath", QVariant(QByteArray("Mod")));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        warningLabel = new QLabel(groupBox);
        warningLabel->setObjectName("warningLabel");
        warningLabel->setWordWrap(true);

        verticalLayout->addWidget(warningLabel);


        vboxLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(verticalSpacer);


        retranslateUi(Gui__Dialog__DlgSettingsPDF);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsPDF);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsPDF)
    {
        Gui__Dialog__DlgSettingsPDF->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsPDF", "PDF", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsPDF", "PDF Export", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsPDF", "PDF version", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettingsPDF", "PDF/1.4", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Gui::Dialog::DlgSettingsPDF", "PDF/A-1b", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Gui::Dialog::DlgSettingsPDF", "PDF/1.6", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Gui::Dialog::DlgSettingsPDF", "PDF/X-4", nullptr));

#if QT_CONFIG(tooltip)
        comboBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsPDF", "This is the PDF Version FreeCAD will use to export to PDF", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsPDF: public Ui_DlgSettingsPDF {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSPDF_H
