/********************************************************************************
** Form generated from reading UI file 'TextureMapping.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTUREMAPPING_H
#define UI_TEXTUREMAPPING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include "Gui/FileDialog.h"

namespace Gui {
namespace Dialog {

class Ui_TextureMapping
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *checkGlobal;
    QCheckBox *checkEnv;
    Gui::FileChooser *fileChooser;

    void setupUi(QDialog *Gui__Dialog__TextureMapping)
    {
        if (Gui__Dialog__TextureMapping->objectName().isEmpty())
            Gui__Dialog__TextureMapping->setObjectName("Gui__Dialog__TextureMapping");
        Gui__Dialog__TextureMapping->resize(218, 122);
        gridLayout_2 = new QGridLayout(Gui__Dialog__TextureMapping);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(Gui__Dialog__TextureMapping);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        checkGlobal = new QCheckBox(groupBox);
        checkGlobal->setObjectName("checkGlobal");

        gridLayout->addWidget(checkGlobal, 0, 0, 1, 1);

        checkEnv = new QCheckBox(groupBox);
        checkEnv->setObjectName("checkEnv");

        gridLayout->addWidget(checkEnv, 0, 1, 1, 1);

        fileChooser = new Gui::FileChooser(groupBox);
        fileChooser->setObjectName("fileChooser");

        gridLayout->addWidget(fileChooser, 1, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(Gui__Dialog__TextureMapping);

        QMetaObject::connectSlotsByName(Gui__Dialog__TextureMapping);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__TextureMapping)
    {
        Gui__Dialog__TextureMapping->setWindowTitle(QCoreApplication::translate("Gui::Dialog::TextureMapping", "Texture", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::TextureMapping", "Texture Mapping", nullptr));
        checkGlobal->setText(QCoreApplication::translate("Gui::Dialog::TextureMapping", "Global", nullptr));
        checkEnv->setText(QCoreApplication::translate("Gui::Dialog::TextureMapping", "Environment", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class TextureMapping: public Ui_TextureMapping {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_TEXTUREMAPPING_H
