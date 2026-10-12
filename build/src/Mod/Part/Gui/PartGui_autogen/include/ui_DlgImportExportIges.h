/********************************************************************************
** Form generated from reading UI file 'DlgImportExportIges.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGIMPORTEXPORTIGES_H
#define UI_DLGIMPORTEXPORTIGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

namespace PartGui {

class Ui_DlgImportExportIges
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QSpacerItem *spacerItem;
    QComboBox *comboBoxUnits;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonBRepOff;
    QRadioButton *radioButtonBRepOn;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QCheckBox *checkSkipBlank;
    QGroupBox *groupBoxHeader;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditCompany;
    QLabel *label_4;
    QLineEdit *lineEditAuthor;
    QLabel *label_3;
    QLineEdit *lineEditProduct;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PartGui__DlgImportExportIges)
    {
        if (PartGui__DlgImportExportIges->objectName().isEmpty())
            PartGui__DlgImportExportIges->setObjectName("PartGui__DlgImportExportIges");
        PartGui__DlgImportExportIges->resize(515, 446);
        gridLayout_5 = new QGridLayout(PartGui__DlgImportExportIges);
        gridLayout_5->setObjectName("gridLayout_5");
        groupBox = new QGroupBox(PartGui__DlgImportExportIges);
        groupBox->setObjectName("groupBox");
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName("gridLayout_4");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(spacerItem, 0, 1, 1, 1);

        comboBoxUnits = new QComboBox(groupBox);
        comboBoxUnits->addItem(QString());
        comboBoxUnits->addItem(QString());
        comboBoxUnits->addItem(QString());
        comboBoxUnits->setObjectName("comboBoxUnits");

        gridLayout_4->addWidget(comboBoxUnits, 0, 2, 1, 1);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName("gridLayout");
        radioButtonBRepOff = new QRadioButton(groupBox_3);
        radioButtonBRepOff->setObjectName("radioButtonBRepOff");
        radioButtonBRepOff->setChecked(true);

        gridLayout->addWidget(radioButtonBRepOff, 0, 0, 1, 1);

        radioButtonBRepOn = new QRadioButton(groupBox_3);
        radioButtonBRepOn->setObjectName("radioButtonBRepOn");

        gridLayout->addWidget(radioButtonBRepOn, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 1, 0, 1, 3);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(PartGui__DlgImportExportIges);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName("gridLayout_3");
        checkSkipBlank = new QCheckBox(groupBox_2);
        checkSkipBlank->setObjectName("checkSkipBlank");

        gridLayout_3->addWidget(checkSkipBlank, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBoxHeader = new QGroupBox(PartGui__DlgImportExportIges);
        groupBoxHeader->setObjectName("groupBoxHeader");
        gridLayout_2 = new QGridLayout(groupBoxHeader);
        gridLayout_2->setObjectName("gridLayout_2");
        label_2 = new QLabel(groupBoxHeader);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        lineEditCompany = new QLineEdit(groupBoxHeader);
        lineEditCompany->setObjectName("lineEditCompany");

        gridLayout_2->addWidget(lineEditCompany, 0, 1, 1, 1);

        label_4 = new QLabel(groupBoxHeader);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        lineEditAuthor = new QLineEdit(groupBoxHeader);
        lineEditAuthor->setObjectName("lineEditAuthor");

        gridLayout_2->addWidget(lineEditAuthor, 1, 1, 1, 1);

        label_3 = new QLabel(groupBoxHeader);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lineEditProduct = new QLineEdit(groupBoxHeader);
        lineEditProduct->setObjectName("lineEditProduct");

        gridLayout_2->addWidget(lineEditProduct, 2, 1, 1, 1);


        gridLayout_5->addWidget(groupBoxHeader, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 82, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 3, 0, 1, 1);

        QWidget::setTabOrder(comboBoxUnits, radioButtonBRepOff);
        QWidget::setTabOrder(radioButtonBRepOff, radioButtonBRepOn);
        QWidget::setTabOrder(radioButtonBRepOn, checkSkipBlank);
        QWidget::setTabOrder(checkSkipBlank, lineEditCompany);
        QWidget::setTabOrder(lineEditCompany, lineEditAuthor);
        QWidget::setTabOrder(lineEditAuthor, lineEditProduct);

        retranslateUi(PartGui__DlgImportExportIges);

        QMetaObject::connectSlotsByName(PartGui__DlgImportExportIges);
    } // setupUi

    void retranslateUi(QWidget *PartGui__DlgImportExportIges)
    {
        PartGui__DlgImportExportIges->setWindowTitle(QCoreApplication::translate("PartGui::DlgImportExportIges", "IGES", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::DlgImportExportIges", "Export", nullptr));
        label->setText(QCoreApplication::translate("PartGui::DlgImportExportIges", "Units for export of IGES", nullptr));
        comboBoxUnits->setItemText(0, QCoreApplication::translate("PartGui::DlgImportExportIges", "Millimeter", nullptr));
        comboBoxUnits->setItemText(1, QCoreApplication::translate("PartGui::DlgImportExportIges", "Meter", nullptr));
        comboBoxUnits->setItemText(2, QCoreApplication::translate("PartGui::DlgImportExportIges", "Inch", nullptr));

        groupBox_3->setTitle(QCoreApplication::translate("PartGui::DlgImportExportIges", "Export Solids and Shells As", nullptr));
#if QT_CONFIG(tooltip)
        radioButtonBRepOff->setToolTip(QCoreApplication::translate("PartGui::DlgImportExportIges", "Solids and shells will be exported as trimmed surface", nullptr));
#endif // QT_CONFIG(tooltip)
        radioButtonBRepOff->setText(QCoreApplication::translate("PartGui::DlgImportExportIges", "Groups of Trimmed Surfaces (type 144)", nullptr));
#if QT_CONFIG(tooltip)
        radioButtonBRepOn->setToolTip(QCoreApplication::translate("PartGui::DlgImportExportIges", "Solids will be exported as manifold solid B-rep object, shells as shell", nullptr));
#endif // QT_CONFIG(tooltip)
        radioButtonBRepOn->setText(QCoreApplication::translate("PartGui::DlgImportExportIges", "Solids (type 186) and shells (type 514) / B-rep mode", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PartGui::DlgImportExportIges", "Import", nullptr));
#if QT_CONFIG(tooltip)
        checkSkipBlank->setToolTip(QCoreApplication::translate("PartGui::DlgImportExportIges", "Blank entities will not be imported", nullptr));
#endif // QT_CONFIG(tooltip)
        checkSkipBlank->setText(QCoreApplication::translate("PartGui::DlgImportExportIges", "Skip blank entities", nullptr));
#if QT_CONFIG(tooltip)
        groupBoxHeader->setToolTip(QCoreApplication::translate("PartGui::DlgImportExportIges", "If not empty, field contents will be used in the IGES file header", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBoxHeader->setTitle(QCoreApplication::translate("PartGui::DlgImportExportIges", "Header", nullptr));
        label_2->setText(QCoreApplication::translate("PartGui::DlgImportExportIges", "Company", nullptr));
        label_4->setText(QCoreApplication::translate("PartGui::DlgImportExportIges", "Author", nullptr));
        label_3->setText(QCoreApplication::translate("PartGui::DlgImportExportIges", "Product", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgImportExportIges: public Ui_DlgImportExportIges {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGIMPORTEXPORTIGES_H
