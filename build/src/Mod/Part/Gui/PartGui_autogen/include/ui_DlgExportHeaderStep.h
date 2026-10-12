/********************************************************************************
** Form generated from reading UI file 'DlgExportHeaderStep.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEXPORTHEADERSTEP_H
#define UI_DLGEXPORTHEADERSTEP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

namespace PartGui {

class Ui_DlgExportHeaderStep
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBoxHeader;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditCompany;
    QLabel *label_3;
    QLineEdit *lineEditAuthor;
    QLabel *label_4;
    QLineEdit *lineEditProduct;

    void setupUi(QWidget *PartGui__DlgExportHeaderStep)
    {
        if (PartGui__DlgExportHeaderStep->objectName().isEmpty())
            PartGui__DlgExportHeaderStep->setObjectName("PartGui__DlgExportHeaderStep");
        PartGui__DlgExportHeaderStep->resize(445, 149);
        PartGui__DlgExportHeaderStep->setWindowTitle(QString::fromUtf8("STEP"));
        gridLayout_4 = new QGridLayout(PartGui__DlgExportHeaderStep);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_4->setObjectName("gridLayout_4");
        groupBoxHeader = new QGroupBox(PartGui__DlgExportHeaderStep);
        groupBoxHeader->setObjectName("groupBoxHeader");
        gridLayout_2 = new QGridLayout(groupBoxHeader);
        gridLayout_2->setObjectName("gridLayout_2");
        label_2 = new QLabel(groupBoxHeader);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        lineEditCompany = new QLineEdit(groupBoxHeader);
        lineEditCompany->setObjectName("lineEditCompany");

        gridLayout_2->addWidget(lineEditCompany, 0, 1, 1, 1);

        label_3 = new QLabel(groupBoxHeader);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        lineEditAuthor = new QLineEdit(groupBoxHeader);
        lineEditAuthor->setObjectName("lineEditAuthor");

        gridLayout_2->addWidget(lineEditAuthor, 1, 1, 1, 1);

        label_4 = new QLabel(groupBoxHeader);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        lineEditProduct = new QLineEdit(groupBoxHeader);
        lineEditProduct->setObjectName("lineEditProduct");

        gridLayout_2->addWidget(lineEditProduct, 2, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxHeader, 1, 0, 1, 1);

        QWidget::setTabOrder(lineEditCompany, lineEditAuthor);
        QWidget::setTabOrder(lineEditAuthor, lineEditProduct);

        retranslateUi(PartGui__DlgExportHeaderStep);

        QMetaObject::connectSlotsByName(PartGui__DlgExportHeaderStep);
    } // setupUi

    void retranslateUi(QWidget *PartGui__DlgExportHeaderStep)
    {
#if QT_CONFIG(tooltip)
        groupBoxHeader->setToolTip(QCoreApplication::translate("PartGui::DlgExportHeaderStep", "If not empty, field contents will be used in the STEP file header", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBoxHeader->setTitle(QCoreApplication::translate("PartGui::DlgExportHeaderStep", "Header", nullptr));
        label_2->setText(QCoreApplication::translate("PartGui::DlgExportHeaderStep", "Company", nullptr));
        label_3->setText(QCoreApplication::translate("PartGui::DlgExportHeaderStep", "Author", nullptr));
        label_4->setText(QCoreApplication::translate("PartGui::DlgExportHeaderStep", "Product", nullptr));
        (void)PartGui__DlgExportHeaderStep;
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgExportHeaderStep: public Ui_DlgExportHeaderStep {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGEXPORTHEADERSTEP_H
