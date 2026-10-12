/********************************************************************************
** Form generated from reading UI file 'DlgProjectUtility.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPROJECTUTILITY_H
#define UI_DLGPROJECTUTILITY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include "Gui/FileDialog.h"

namespace Gui {
namespace Dialog {

class Ui_DlgProjectUtility
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    Gui::FileChooser *extractSource;
    QLabel *label_2;
    Gui::FileChooser *extractDest;
    QPushButton *extractButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    Gui::FileChooser *createSource;
    QLabel *label_4;
    Gui::FileChooser *createDest;
    QPushButton *createButton;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkLoadProject;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgProjectUtility)
    {
        if (Gui__Dialog__DlgProjectUtility->objectName().isEmpty())
            Gui__Dialog__DlgProjectUtility->setObjectName("Gui__Dialog__DlgProjectUtility");
        Gui__Dialog__DlgProjectUtility->resize(445, 262);
        gridLayout_4 = new QGridLayout(Gui__Dialog__DlgProjectUtility);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox = new QGroupBox(Gui__Dialog__DlgProjectUtility);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        extractSource = new Gui::FileChooser(groupBox);
        extractSource->setObjectName("extractSource");
        extractSource->setFilter(QString::fromUtf8("Document file (*.FCStd)"));

        gridLayout->addWidget(extractSource, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        extractDest = new Gui::FileChooser(groupBox);
        extractDest->setObjectName("extractDest");
        extractDest->setMode(Gui::FileChooser::Directory);

        gridLayout->addWidget(extractDest, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        extractButton = new QPushButton(Gui__Dialog__DlgProjectUtility);
        extractButton->setObjectName("extractButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(extractButton->sizePolicy().hasHeightForWidth());
        extractButton->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(extractButton, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(Gui__Dialog__DlgProjectUtility);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        createSource = new Gui::FileChooser(groupBox_2);
        createSource->setObjectName("createSource");
        createSource->setFilter(QString::fromUtf8("Document.xml"));

        gridLayout_2->addWidget(createSource, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        createDest = new Gui::FileChooser(groupBox_2);
        createDest->setObjectName("createDest");
        createDest->setMode(Gui::FileChooser::Directory);

        gridLayout_2->addWidget(createDest, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        createButton = new QPushButton(Gui__Dialog__DlgProjectUtility);
        createButton->setObjectName("createButton");
        sizePolicy.setHeightForWidth(createButton->sizePolicy().hasHeightForWidth());
        createButton->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(createButton, 1, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 1, 0, 1, 1);

        checkLoadProject = new QCheckBox(Gui__Dialog__DlgProjectUtility);
        checkLoadProject->setObjectName("checkLoadProject");

        gridLayout_4->addWidget(checkLoadProject, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgProjectUtility);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        gridLayout_4->addWidget(buttonBox, 2, 1, 1, 1);


        retranslateUi(Gui__Dialog__DlgProjectUtility);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgProjectUtility, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgProjectUtility, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgProjectUtility);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgProjectUtility)
    {
        Gui__Dialog__DlgProjectUtility->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Document Utility", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Extract Document", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Source", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Destination", nullptr));
        extractButton->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Extract", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Create Document", nullptr));
        label_3->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Source", nullptr));
        label_4->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Destination", nullptr));
        createButton->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Create", nullptr));
        checkLoadProject->setText(QCoreApplication::translate("Gui::Dialog::DlgProjectUtility", "Load document file after creation", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgProjectUtility: public Ui_DlgProjectUtility {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGPROJECTUTILITY_H
