/********************************************************************************
** Form generated from reading UI file 'DlgInspectMaterial.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGINSPECTMATERIAL_H
#define UI_DLGINSPECTMATERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace MatGui {

class Ui_DlgInspectMaterial
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *editObjectName;
    QLineEdit *editObjectLabel;
    QLineEdit *editSubShape;
    QLabel *label;
    QLineEdit *editDocument;
    QLabel *label_2;
    QLineEdit *editSubShapeType;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *editShapeType;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QTreeView *treeMaterials;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonClipboard;

    void setupUi(QWidget *MatGui__DlgInspectMaterial)
    {
        if (MatGui__DlgInspectMaterial->objectName().isEmpty())
            MatGui__DlgInspectMaterial->setObjectName("MatGui__DlgInspectMaterial");
        MatGui__DlgInspectMaterial->resize(400, 432);
        verticalLayout = new QVBoxLayout(MatGui__DlgInspectMaterial);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(MatGui__DlgInspectMaterial);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 376, 408));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        editObjectName = new QLineEdit(groupBox);
        editObjectName->setObjectName("editObjectName");

        gridLayout->addWidget(editObjectName, 1, 2, 1, 1);

        editObjectLabel = new QLineEdit(groupBox);
        editObjectLabel->setObjectName("editObjectLabel");

        gridLayout->addWidget(editObjectLabel, 1, 1, 1, 1);

        editSubShape = new QLineEdit(groupBox);
        editSubShape->setObjectName("editSubShape");

        gridLayout->addWidget(editSubShape, 2, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        editDocument = new QLineEdit(groupBox);
        editDocument->setObjectName("editDocument");

        gridLayout->addWidget(editDocument, 0, 1, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        editSubShapeType = new QLineEdit(groupBox);
        editSubShapeType->setObjectName("editSubShapeType");

        gridLayout->addWidget(editSubShapeType, 2, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        editShapeType = new QLineEdit(groupBox);
        editShapeType->setObjectName("editShapeType");

        gridLayout->addWidget(editShapeType, 3, 1, 1, 2);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        treeMaterials = new QTreeView(groupBox_2);
        treeMaterials->setObjectName("treeMaterials");
        treeMaterials->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        verticalLayout_3->addWidget(treeMaterials);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonClipboard = new QPushButton(groupBox_2);
        buttonClipboard->setObjectName("buttonClipboard");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonClipboard->sizePolicy().hasHeightForWidth());
        buttonClipboard->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(buttonClipboard);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(groupBox_2);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(MatGui__DlgInspectMaterial);

        QMetaObject::connectSlotsByName(MatGui__DlgInspectMaterial);
    } // setupUi

    void retranslateUi(QWidget *MatGui__DlgInspectMaterial)
    {
        MatGui__DlgInspectMaterial->setWindowTitle(QCoreApplication::translate("MatGui::DlgInspectMaterial", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MatGui::DlgInspectMaterial", "Document", nullptr));
        label->setText(QCoreApplication::translate("MatGui::DlgInspectMaterial", "Document name", nullptr));
#if QT_CONFIG(tooltip)
        editDocument->setToolTip(QCoreApplication::translate("MatGui::DlgInspectMaterial", "Name of the active document", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("MatGui::DlgInspectMaterial", "Label / internal name", nullptr));
        label_3->setText(QCoreApplication::translate("MatGui::DlgInspectMaterial", "Sub.Shape / Type", nullptr));
        label_4->setText(QCoreApplication::translate("MatGui::DlgInspectMaterial", "Shape.TypeID / TypeID", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MatGui::DlgInspectMaterial", "Material", nullptr));
        buttonClipboard->setText(QCoreApplication::translate("MatGui::DlgInspectMaterial", "Copy to Clipboard", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class DlgInspectMaterial: public Ui_DlgInspectMaterial {};
} // namespace Ui
} // namespace MatGui

#endif // UI_DLGINSPECTMATERIAL_H
