/********************************************************************************
** Form generated from reading UI file 'ImageEdit.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEEDIT_H
#define UI_IMAGEEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "Mod/Material/Gui/ImageEdit.h"

namespace MatGui {

class Ui_ImageEdit
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    MatGui::ImageLabel *labelThumb;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QPushButton *buttonFileSelect;
    QGridLayout *gridLayout;
    QLabel *labelHeight;
    QLabel *labelWidth;
    QLineEdit *editHeight;
    QLineEdit *editWidth;
    QSpacerItem *verticalSpacer;
    MatGui::ImageLabel *labelImage;
    QDialogButtonBox *standardButtons;

    void setupUi(QDialog *MatGui__ImageEdit)
    {
        if (MatGui__ImageEdit->objectName().isEmpty())
            MatGui__ImageEdit->setObjectName("MatGui__ImageEdit");
        MatGui__ImageEdit->resize(498, 626);
        verticalLayout = new QVBoxLayout(MatGui__ImageEdit);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(MatGui__ImageEdit);
        label->setObjectName("label");

        verticalLayout_4->addWidget(label, 0, Qt::AlignTop);

        labelThumb = new MatGui::ImageLabel(MatGui__ImageEdit);
        labelThumb->setObjectName("labelThumb");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelThumb->sizePolicy().hasHeightForWidth());
        labelThumb->setSizePolicy(sizePolicy);
        labelThumb->setMinimumSize(QSize(64, 64));
        labelThumb->setFrameShape(QFrame::Box);

        verticalLayout_4->addWidget(labelThumb, 0, Qt::AlignLeft|Qt::AlignTop);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        buttonFileSelect = new QPushButton(MatGui__ImageEdit);
        buttonFileSelect->setObjectName("buttonFileSelect");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonFileSelect->sizePolicy().hasHeightForWidth());
        buttonFileSelect->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(buttonFileSelect, 0, Qt::AlignRight|Qt::AlignTop);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        labelHeight = new QLabel(MatGui__ImageEdit);
        labelHeight->setObjectName("labelHeight");

        gridLayout->addWidget(labelHeight, 1, 0, 1, 1);

        labelWidth = new QLabel(MatGui__ImageEdit);
        labelWidth->setObjectName("labelWidth");

        gridLayout->addWidget(labelWidth, 0, 0, 1, 1);

        editHeight = new QLineEdit(MatGui__ImageEdit);
        editHeight->setObjectName("editHeight");
        editHeight->setEnabled(false);
        editHeight->setReadOnly(true);

        gridLayout->addWidget(editHeight, 1, 1, 1, 1);

        editWidth = new QLineEdit(MatGui__ImageEdit);
        editWidth->setObjectName("editWidth");
        editWidth->setEnabled(false);
        editWidth->setReadOnly(true);

        gridLayout->addWidget(editWidth, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout);

        labelImage = new MatGui::ImageLabel(MatGui__ImageEdit);
        labelImage->setObjectName("labelImage");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelImage->sizePolicy().hasHeightForWidth());
        labelImage->setSizePolicy(sizePolicy2);
        labelImage->setMinimumSize(QSize(480, 480));
        labelImage->setFrameShape(QFrame::Box);

        verticalLayout->addWidget(labelImage, 0, Qt::AlignTop);

        standardButtons = new QDialogButtonBox(MatGui__ImageEdit);
        standardButtons->setObjectName("standardButtons");
        standardButtons->setOrientation(Qt::Horizontal);
        standardButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(standardButtons);


        retranslateUi(MatGui__ImageEdit);
        QObject::connect(standardButtons, &QDialogButtonBox::accepted, MatGui__ImageEdit, qOverload<>(&QDialog::accept));
        QObject::connect(standardButtons, &QDialogButtonBox::rejected, MatGui__ImageEdit, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(MatGui__ImageEdit);
    } // setupUi

    void retranslateUi(QDialog *MatGui__ImageEdit)
    {
        MatGui__ImageEdit->setWindowTitle(QCoreApplication::translate("MatGui::ImageEdit", "Image", nullptr));
        label->setText(QCoreApplication::translate("MatGui::ImageEdit", "Thumbnail", nullptr));
        labelThumb->setText(QString());
        buttonFileSelect->setText(QCoreApplication::translate("MatGui::ImageEdit", "File", nullptr));
        labelHeight->setText(QCoreApplication::translate("MatGui::ImageEdit", "Height", nullptr));
        labelWidth->setText(QCoreApplication::translate("MatGui::ImageEdit", "Width", nullptr));
        labelImage->setText(QString());
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class ImageEdit: public Ui_ImageEdit {};
} // namespace Ui
} // namespace MatGui

#endif // UI_IMAGEEDIT_H
