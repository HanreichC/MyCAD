/********************************************************************************
** Form generated from reading UI file 'DlgReference.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGREFERENCE_H
#define UI_DLGREFERENCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

namespace PartDesignGui {

class Ui_DlgReference
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioIndependent;
    QRadioButton *radioDependent;
    QRadioButton *radioXRef;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PartDesignGui__DlgReference)
    {
        if (PartDesignGui__DlgReference->objectName().isEmpty())
            PartDesignGui__DlgReference->setObjectName("PartDesignGui__DlgReference");
        PartDesignGui__DlgReference->resize(487, 243);
        verticalLayout_2 = new QVBoxLayout(PartDesignGui__DlgReference);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(PartDesignGui__DlgReference);
        label->setObjectName("label");
        label->setScaledContents(true);
        label->setWordWrap(true);

        verticalLayout_2->addWidget(label);

        frame = new QFrame(PartDesignGui__DlgReference);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        radioIndependent = new QRadioButton(frame);
        radioIndependent->setObjectName("radioIndependent");
        radioIndependent->setChecked(true);

        verticalLayout->addWidget(radioIndependent);

        radioDependent = new QRadioButton(frame);
        radioDependent->setObjectName("radioDependent");

        verticalLayout->addWidget(radioDependent);

        radioXRef = new QRadioButton(frame);
        radioXRef->setObjectName("radioXRef");

        verticalLayout->addWidget(radioXRef);


        verticalLayout_2->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(PartDesignGui__DlgReference);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(PartDesignGui__DlgReference);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, PartDesignGui__DlgReference, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, PartDesignGui__DlgReference, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(PartDesignGui__DlgReference);
    } // setupUi

    void retranslateUi(QDialog *PartDesignGui__DlgReference)
    {
        PartDesignGui__DlgReference->setWindowTitle(QCoreApplication::translate("PartDesignGui::DlgReference", "Reference", nullptr));
        label->setText(QCoreApplication::translate("PartDesignGui::DlgReference", "You selected geometries which are not part of the active body. Please define how to handle those selections. If you do not want those references, cancel the command.", nullptr));
        radioIndependent->setText(QCoreApplication::translate("PartDesignGui::DlgReference", "Make independent copy (recommended)", nullptr));
        radioDependent->setText(QCoreApplication::translate("PartDesignGui::DlgReference", "Make dependent copy", nullptr));
        radioXRef->setText(QCoreApplication::translate("PartDesignGui::DlgReference", "Create cross-reference", nullptr));
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class DlgReference: public Ui_DlgReference {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_DLGREFERENCE_H
