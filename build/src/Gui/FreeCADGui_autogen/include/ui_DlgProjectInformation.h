/********************************************************************************
** Form generated from reading UI file 'DlgProjectInformation.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPROJECTINFORMATION_H
#define UI_DLGPROJECTINFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>

namespace Gui {
namespace Dialog {

class Ui_DlgProjectInformation
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBoxInfo;
    QGridLayout *gridLayout1;
    QLabel *textLabelName;
    QLineEdit *lineEditName;
    QLabel *textLabelPath;
    QLineEdit *lineEditPath;
    QLabel *textLabelUuid;
    QLineEdit *lineEditUuid;
    QLabel *textLabelProgramVersion;
    QLineEdit *lineEditProgramVersion;
    QLabel *textLabelUnitSystem;
    QComboBox *comboBox_unitSystem;
    QLabel *textLabelCreator;
    QLineEdit *lineEditCreator;
    QLabel *textLabelCreateDate;
    QLineEdit *lineEditDate;
    QLabel *textLabelLastMod;
    QLineEdit *lineEditLastMod;
    QLabel *textLabelLastModDate;
    QLineEdit *lineEditLastModDate;
    QLabel *textLabelCompany;
    QLineEdit *lineEditCompany;
    QLabel *textLabelLicense;
    QComboBox *comboLicense;
    QLabel *textLabelLicenseURL;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEditLicenseURL;
    QPushButton *pushButtonOpenURL;
    QLabel *textLabelComment;
    QTextEdit *textEditComment;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgProjectInformation)
    {
        if (Gui__Dialog__DlgProjectInformation->objectName().isEmpty())
            Gui__Dialog__DlgProjectInformation->setObjectName("Gui__Dialog__DlgProjectInformation");
        Gui__Dialog__DlgProjectInformation->resize(597, 540);
        Gui__Dialog__DlgProjectInformation->setSizeGripEnabled(true);
        Gui__Dialog__DlgProjectInformation->setModal(true);
        gridLayout = new QGridLayout(Gui__Dialog__DlgProjectInformation);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        groupBoxInfo = new QGroupBox(Gui__Dialog__DlgProjectInformation);
        groupBoxInfo->setObjectName("groupBoxInfo");
        gridLayout1 = new QGridLayout(groupBoxInfo);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        textLabelName = new QLabel(groupBoxInfo);
        textLabelName->setObjectName("textLabelName");
        textLabelName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelName, 0, 0, 1, 1);

        lineEditName = new QLineEdit(groupBoxInfo);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setMinimumSize(QSize(0, 25));
        lineEditName->setReadOnly(true);

        gridLayout1->addWidget(lineEditName, 0, 1, 1, 1);

        textLabelPath = new QLabel(groupBoxInfo);
        textLabelPath->setObjectName("textLabelPath");
        textLabelPath->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelPath, 1, 0, 1, 1);

        lineEditPath = new QLineEdit(groupBoxInfo);
        lineEditPath->setObjectName("lineEditPath");
        lineEditPath->setMinimumSize(QSize(0, 25));
        lineEditPath->setReadOnly(true);

        gridLayout1->addWidget(lineEditPath, 1, 1, 1, 1);

        textLabelUuid = new QLabel(groupBoxInfo);
        textLabelUuid->setObjectName("textLabelUuid");
        textLabelUuid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelUuid, 2, 0, 1, 1);

        lineEditUuid = new QLineEdit(groupBoxInfo);
        lineEditUuid->setObjectName("lineEditUuid");
        lineEditUuid->setMinimumSize(QSize(0, 25));
        lineEditUuid->setReadOnly(true);

        gridLayout1->addWidget(lineEditUuid, 2, 1, 1, 1);

        textLabelProgramVersion = new QLabel(groupBoxInfo);
        textLabelProgramVersion->setObjectName("textLabelProgramVersion");
        textLabelProgramVersion->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelProgramVersion, 3, 0, 1, 1);

        lineEditProgramVersion = new QLineEdit(groupBoxInfo);
        lineEditProgramVersion->setObjectName("lineEditProgramVersion");
        lineEditProgramVersion->setMinimumSize(QSize(0, 25));
        lineEditProgramVersion->setReadOnly(true);

        gridLayout1->addWidget(lineEditProgramVersion, 3, 1, 1, 1);

        textLabelUnitSystem = new QLabel(groupBoxInfo);
        textLabelUnitSystem->setObjectName("textLabelUnitSystem");
        textLabelUnitSystem->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelUnitSystem, 4, 0, 1, 1);

        comboBox_unitSystem = new QComboBox(groupBoxInfo);
        comboBox_unitSystem->setObjectName("comboBox_unitSystem");

        gridLayout1->addWidget(comboBox_unitSystem, 4, 1, 1, 1);

        textLabelCreator = new QLabel(groupBoxInfo);
        textLabelCreator->setObjectName("textLabelCreator");
        textLabelCreator->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelCreator, 5, 0, 1, 1);

        lineEditCreator = new QLineEdit(groupBoxInfo);
        lineEditCreator->setObjectName("lineEditCreator");
        lineEditCreator->setMinimumSize(QSize(0, 25));

        gridLayout1->addWidget(lineEditCreator, 5, 1, 1, 1);

        textLabelCreateDate = new QLabel(groupBoxInfo);
        textLabelCreateDate->setObjectName("textLabelCreateDate");
        textLabelCreateDate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelCreateDate, 6, 0, 1, 1);

        lineEditDate = new QLineEdit(groupBoxInfo);
        lineEditDate->setObjectName("lineEditDate");
        lineEditDate->setMinimumSize(QSize(0, 25));
        lineEditDate->setReadOnly(true);

        gridLayout1->addWidget(lineEditDate, 6, 1, 1, 1);

        textLabelLastMod = new QLabel(groupBoxInfo);
        textLabelLastMod->setObjectName("textLabelLastMod");
        textLabelLastMod->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelLastMod, 7, 0, 1, 1);

        lineEditLastMod = new QLineEdit(groupBoxInfo);
        lineEditLastMod->setObjectName("lineEditLastMod");
        lineEditLastMod->setMinimumSize(QSize(0, 25));

        gridLayout1->addWidget(lineEditLastMod, 7, 1, 1, 1);

        textLabelLastModDate = new QLabel(groupBoxInfo);
        textLabelLastModDate->setObjectName("textLabelLastModDate");
        textLabelLastModDate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelLastModDate, 8, 0, 1, 1);

        lineEditLastModDate = new QLineEdit(groupBoxInfo);
        lineEditLastModDate->setObjectName("lineEditLastModDate");
        lineEditLastModDate->setMinimumSize(QSize(0, 25));
        lineEditLastModDate->setReadOnly(true);

        gridLayout1->addWidget(lineEditLastModDate, 8, 1, 1, 1);

        textLabelCompany = new QLabel(groupBoxInfo);
        textLabelCompany->setObjectName("textLabelCompany");
        textLabelCompany->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelCompany, 9, 0, 1, 1);

        lineEditCompany = new QLineEdit(groupBoxInfo);
        lineEditCompany->setObjectName("lineEditCompany");
        lineEditCompany->setMinimumSize(QSize(0, 25));

        gridLayout1->addWidget(lineEditCompany, 9, 1, 1, 1);

        textLabelLicense = new QLabel(groupBoxInfo);
        textLabelLicense->setObjectName("textLabelLicense");
        textLabelLicense->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelLicense, 10, 0, 1, 1);

        comboLicense = new QComboBox(groupBoxInfo);
        comboLicense->setObjectName("comboLicense");

        gridLayout1->addWidget(comboLicense, 10, 1, 1, 1);

        textLabelLicenseURL = new QLabel(groupBoxInfo);
        textLabelLicenseURL->setObjectName("textLabelLicenseURL");
        textLabelLicenseURL->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelLicenseURL, 11, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lineEditLicenseURL = new QLineEdit(groupBoxInfo);
        lineEditLicenseURL->setObjectName("lineEditLicenseURL");

        horizontalLayout_2->addWidget(lineEditLicenseURL);

        pushButtonOpenURL = new QPushButton(groupBoxInfo);
        pushButtonOpenURL->setObjectName("pushButtonOpenURL");

        horizontalLayout_2->addWidget(pushButtonOpenURL);


        gridLayout1->addLayout(horizontalLayout_2, 11, 1, 1, 1);

        textLabelComment = new QLabel(groupBoxInfo);
        textLabelComment->setObjectName("textLabelComment");
        textLabelComment->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(textLabelComment, 12, 0, 1, 1);

        textEditComment = new QTextEdit(groupBoxInfo);
        textEditComment->setObjectName("textEditComment");

        gridLayout1->addWidget(textEditComment, 12, 1, 2, 1);

        spacerItem = new QSpacerItem(91, 240, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout1->addItem(spacerItem, 13, 0, 1, 1);


        gridLayout->addWidget(groupBoxInfo, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgProjectInformation);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

#if QT_CONFIG(shortcut)
        textLabelName->setBuddy(lineEditName);
        textLabelCreator->setBuddy(lineEditCreator);
        textLabelCreateDate->setBuddy(lineEditDate);
        textLabelLastMod->setBuddy(lineEditLastMod);
        textLabelLastModDate->setBuddy(lineEditLastModDate);
        textLabelCompany->setBuddy(lineEditCompany);
        textLabelComment->setBuddy(textEditComment);
#endif // QT_CONFIG(shortcut)

        retranslateUi(Gui__Dialog__DlgProjectInformation);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgProjectInformation, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgProjectInformation, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgProjectInformation);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgProjectInformation)
    {
        Gui__Dialog__DlgProjectInformation->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Document Information", nullptr));
        groupBoxInfo->setTitle(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Information", nullptr));
        textLabelName->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "&Name", nullptr));
        textLabelPath->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Path", nullptr));
        textLabelUuid->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "UUID", nullptr));
        textLabelProgramVersion->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Program version", nullptr));
        textLabelUnitSystem->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Unit system", nullptr));
#if QT_CONFIG(tooltip)
        comboBox_unitSystem->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Unit system for this file", nullptr));
#endif // QT_CONFIG(tooltip)
        textLabelCreator->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Created &by", nullptr));
        textLabelCreateDate->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Creation &date", nullptr));
        textLabelLastMod->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "&Last modified by", nullptr));
        textLabelLastModDate->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Last &modification date", nullptr));
        textLabelCompany->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Com&pany", nullptr));
        textLabelLicense->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "License information", nullptr));
        textLabelLicenseURL->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "License URL", nullptr));
        pushButtonOpenURL->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "Open in Browser", nullptr));
        textLabelComment->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectInformation", "&Comment", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgProjectInformation: public Ui_DlgProjectInformation {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGPROJECTINFORMATION_H
