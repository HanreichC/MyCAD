/********************************************************************************
** Form generated from reading UI file 'SketchMirrorDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKETCHMIRRORDIALOG_H
#define UI_SKETCHMIRRORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

namespace SketcherGui {

class Ui_SketchMirrorDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *XAxisRadioButton;
    QRadioButton *YAxisRadioButton;
    QRadioButton *OriginRadioButton;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SketcherGui__SketchMirrorDialog)
    {
        if (SketcherGui__SketchMirrorDialog->objectName().isEmpty())
            SketcherGui__SketchMirrorDialog->setObjectName("SketcherGui__SketchMirrorDialog");
        SketcherGui__SketchMirrorDialog->resize(220, 171);
        gridLayout = new QGridLayout(SketcherGui__SketchMirrorDialog);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(SketcherGui__SketchMirrorDialog);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        XAxisRadioButton = new QRadioButton(groupBox);
        XAxisRadioButton->setObjectName("XAxisRadioButton");
        XAxisRadioButton->setChecked(true);

        verticalLayout->addWidget(XAxisRadioButton);

        YAxisRadioButton = new QRadioButton(groupBox);
        YAxisRadioButton->setObjectName("YAxisRadioButton");

        verticalLayout->addWidget(YAxisRadioButton);

        OriginRadioButton = new QRadioButton(groupBox);
        OriginRadioButton->setObjectName("OriginRadioButton");

        verticalLayout->addWidget(OriginRadioButton);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SketcherGui__SketchMirrorDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(SketcherGui__SketchMirrorDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SketcherGui__SketchMirrorDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SketcherGui__SketchMirrorDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SketcherGui__SketchMirrorDialog);
    } // setupUi

    void retranslateUi(QDialog *SketcherGui__SketchMirrorDialog)
    {
        SketcherGui__SketchMirrorDialog->setWindowTitle(QCoreApplication::translate("SketcherGui::SketchMirrorDialog", "Select Mirror Axis or Point", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SketcherGui::SketchMirrorDialog", "Select Mirror Axis or Point", nullptr));
        XAxisRadioButton->setText(QCoreApplication::translate("SketcherGui::SketchMirrorDialog", "X-axis", nullptr));
        YAxisRadioButton->setText(QCoreApplication::translate("SketcherGui::SketchMirrorDialog", "Y-axis", nullptr));
        OriginRadioButton->setText(QCoreApplication::translate("SketcherGui::SketchMirrorDialog", "Origin", nullptr));
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class SketchMirrorDialog: public Ui_SketchMirrorDialog {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_SKETCHMIRRORDIALOG_H
