/********************************************************************************
** Form generated from reading UI file 'DlgPartImportIges.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPARTIMPORTIGES_H
#define UI_DLGPARTIMPORTIGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

namespace PartGui {

class Ui_DlgPartImportIges
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *GroupBox5;
    QGridLayout *gridLayout;
    QLineEdit *FileName;
    QPushButton *SearchFile;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PartGui__DlgPartImportIges)
    {
        if (PartGui__DlgPartImportIges->objectName().isEmpty())
            PartGui__DlgPartImportIges->setObjectName("PartGui__DlgPartImportIges");
        PartGui__DlgPartImportIges->resize(342, 112);
        gridLayout_2 = new QGridLayout(PartGui__DlgPartImportIges);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        GroupBox5 = new QGroupBox(PartGui__DlgPartImportIges);
        GroupBox5->setObjectName("GroupBox5");
        gridLayout = new QGridLayout(GroupBox5);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        FileName = new QLineEdit(GroupBox5);
        FileName->setObjectName("FileName");

        gridLayout->addWidget(FileName, 0, 0, 1, 1);

        SearchFile = new QPushButton(GroupBox5);
        SearchFile->setObjectName("SearchFile");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SearchFile->sizePolicy().hasHeightForWidth());
        SearchFile->setSizePolicy(sizePolicy);
        SearchFile->setMinimumSize(QSize(30, 0));
        SearchFile->setMaximumSize(QSize(30, 32767));

        gridLayout->addWidget(SearchFile, 0, 1, 1, 1);


        gridLayout_2->addWidget(GroupBox5, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(PartGui__DlgPartImportIges);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 1);

        QWidget::setTabOrder(FileName, SearchFile);

        retranslateUi(PartGui__DlgPartImportIges);

        QMetaObject::connectSlotsByName(PartGui__DlgPartImportIges);
    } // setupUi

    void retranslateUi(QDialog *PartGui__DlgPartImportIges)
    {
        PartGui__DlgPartImportIges->setWindowTitle(QCoreApplication::translate("PartGui::DlgPartImportIges", "IGES Input File", nullptr));
        GroupBox5->setTitle(QCoreApplication::translate("PartGui::DlgPartImportIges", "File Name", nullptr));
        FileName->setText(QString());
        SearchFile->setText(QCoreApplication::translate("PartGui::DlgPartImportIges", "Search File", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgPartImportIges: public Ui_DlgPartImportIges {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGPARTIMPORTIGES_H
