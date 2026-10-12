/********************************************************************************
** Form generated from reading UI file 'DlgVersionMigrator.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGVERSIONMIGRATOR_H
#define UI_DLGVERSIONMIGRATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "Gui/SplitButton.h"

namespace Gui {
namespace Dialog {

class Ui_DlgVersionMigrator
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *welcomeLabel;
    QLabel *questionLabel;
    QLabel *explanationLabel;
    QLabel *sizeLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *helpButton;
    QSpacerItem *horizontalSpacer;
    Gui::SplitButton *copyButton;

    void setupUi(QDialog *Gui__Dialog__DlgVersionMigrator)
    {
        if (Gui__Dialog__DlgVersionMigrator->objectName().isEmpty())
            Gui__Dialog__DlgVersionMigrator->setObjectName("Gui__Dialog__DlgVersionMigrator");
        Gui__Dialog__DlgVersionMigrator->setWindowModality(Qt::WindowModal);
        Gui__Dialog__DlgVersionMigrator->resize(556, 233);
        Gui__Dialog__DlgVersionMigrator->setModal(true);
        verticalLayout = new QVBoxLayout(Gui__Dialog__DlgVersionMigrator);
        verticalLayout->setObjectName("verticalLayout");
        welcomeLabel = new QLabel(Gui__Dialog__DlgVersionMigrator);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setTextFormat(Qt::AutoText);

        verticalLayout->addWidget(welcomeLabel);

        questionLabel = new QLabel(Gui__Dialog__DlgVersionMigrator);
        questionLabel->setObjectName("questionLabel");
        questionLabel->setTextFormat(Qt::PlainText);
        questionLabel->setWordWrap(true);

        verticalLayout->addWidget(questionLabel);

        explanationLabel = new QLabel(Gui__Dialog__DlgVersionMigrator);
        explanationLabel->setObjectName("explanationLabel");
        explanationLabel->setTextFormat(Qt::PlainText);
        explanationLabel->setWordWrap(true);

        verticalLayout->addWidget(explanationLabel);

        sizeLabel = new QLabel(Gui__Dialog__DlgVersionMigrator);
        sizeLabel->setObjectName("sizeLabel");
        sizeLabel->setTextFormat(Qt::AutoText);

        verticalLayout->addWidget(sizeLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        helpButton = new QPushButton(Gui__Dialog__DlgVersionMigrator);
        helpButton->setObjectName("helpButton");

        horizontalLayout->addWidget(helpButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        copyButton = new Gui::SplitButton(Gui__Dialog__DlgVersionMigrator);
        copyButton->setObjectName("copyButton");

        horizontalLayout->addWidget(copyButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Gui__Dialog__DlgVersionMigrator);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgVersionMigrator);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgVersionMigrator)
    {
        Gui__Dialog__DlgVersionMigrator->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgVersionMigrator", "Dialog", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgVersionMigrator", "TextLabel", nullptr));
        questionLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgVersionMigrator", "Configuration data and addons from a previous program version were found. Migrate the configuration to a new directory for this version?", nullptr));
        explanationLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgVersionMigrator", "Copying the configuration will ensure that any changes from the new version will not affect the previous installation. Sharing configuration between versions can cause problems and is not recommended.", nullptr));
        sizeLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgVersionMigrator", "TextLabel", nullptr));
        helpButton->setText(QCoreApplication::translate("Gui::Dialog::DlgVersionMigrator", "Help", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgVersionMigrator: public Ui_DlgVersionMigrator {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGVERSIONMIGRATOR_H
