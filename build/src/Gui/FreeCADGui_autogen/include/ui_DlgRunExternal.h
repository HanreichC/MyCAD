/********************************************************************************
** Form generated from reading UI file 'DlgRunExternal.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGRUNEXTERNAL_H
#define UI_DLGRUNEXTERNAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace Gui {
namespace Dialog {

class Ui_DlgRunExternal
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *programName;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonAdvanced;
    QWidget *extensionWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hboxLayout;
    QLineEdit *programPath;
    QPushButton *chooseProgram;
    QTextEdit *output;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *buttonAccept;
    QPushButton *buttonDiscard;
    QPushButton *buttonAbort;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *buttonHelp;

    void setupUi(QDialog *Gui__Dialog__DlgRunExternal)
    {
        if (Gui__Dialog__DlgRunExternal->objectName().isEmpty())
            Gui__Dialog__DlgRunExternal->setObjectName("Gui__Dialog__DlgRunExternal");
        Gui__Dialog__DlgRunExternal->resize(387, 363);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Gui__Dialog__DlgRunExternal->sizePolicy().hasHeightForWidth());
        Gui__Dialog__DlgRunExternal->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(Gui__Dialog__DlgRunExternal);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        programName = new QLabel(Gui__Dialog__DlgRunExternal);
        programName->setObjectName("programName");
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        programName->setFont(font);

        horizontalLayout->addWidget(programName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonAdvanced = new QPushButton(Gui__Dialog__DlgRunExternal);
        buttonAdvanced->setObjectName("buttonAdvanced");

        horizontalLayout->addWidget(buttonAdvanced);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        extensionWidget = new QWidget(Gui__Dialog__DlgRunExternal);
        extensionWidget->setObjectName("extensionWidget");
        verticalLayout = new QVBoxLayout(extensionWidget);
#ifndef Q_OS_MACOS
        verticalLayout->setSpacing(6);
#endif
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MACOS
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName("hboxLayout");
        programPath = new QLineEdit(extensionWidget);
        programPath->setObjectName("programPath");

        hboxLayout->addWidget(programPath);

        chooseProgram = new QPushButton(extensionWidget);
        chooseProgram->setObjectName("chooseProgram");
        chooseProgram->setText(QString::fromUtf8("Choose Program"));

        hboxLayout->addWidget(chooseProgram);


        verticalLayout->addLayout(hboxLayout);

        output = new QTextEdit(extensionWidget);
        output->setObjectName("output");

        verticalLayout->addWidget(output);


        gridLayout->addWidget(extensionWidget, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        buttonAccept = new QPushButton(Gui__Dialog__DlgRunExternal);
        buttonAccept->setObjectName("buttonAccept");

        horizontalLayout_2->addWidget(buttonAccept);

        buttonDiscard = new QPushButton(Gui__Dialog__DlgRunExternal);
        buttonDiscard->setObjectName("buttonDiscard");

        horizontalLayout_2->addWidget(buttonDiscard);

        buttonAbort = new QPushButton(Gui__Dialog__DlgRunExternal);
        buttonAbort->setObjectName("buttonAbort");

        horizontalLayout_2->addWidget(buttonAbort);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        buttonHelp = new QPushButton(Gui__Dialog__DlgRunExternal);
        buttonHelp->setObjectName("buttonHelp");

        horizontalLayout_2->addWidget(buttonHelp);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgRunExternal);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgRunExternal);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgRunExternal)
    {
        Gui__Dialog__DlgRunExternal->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgRunExternal", "Running External Program", nullptr));
        programName->setText(QCoreApplication::translate("Gui::Dialog::DlgRunExternal", "TextLabel", nullptr));
        buttonAdvanced->setText(QCoreApplication::translate("Gui::Dialog::DlgRunExternal", "Advanced >>", nullptr));
        buttonAccept->setText(QCoreApplication::translate("Gui::Dialog::DlgRunExternal", "Accept Changes", nullptr));
        buttonDiscard->setText(QCoreApplication::translate("Gui::Dialog::DlgRunExternal", "Discard Changes", nullptr));
        buttonAbort->setText(QCoreApplication::translate("Gui::Dialog::DlgRunExternal", "Abort Program", nullptr));
        buttonHelp->setText(QCoreApplication::translate("Gui::Dialog::DlgRunExternal", "Help", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgRunExternal: public Ui_DlgRunExternal {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGRUNEXTERNAL_H
