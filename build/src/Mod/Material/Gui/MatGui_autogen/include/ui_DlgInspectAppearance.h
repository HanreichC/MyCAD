/********************************************************************************
** Form generated from reading UI file 'DlgInspectAppearance.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGINSPECTAPPEARANCE_H
#define UI_DLGINSPECTAPPEARANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace MatGui {

class Ui_DlgInspectAppearance
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
    QTabWidget *tabAppearance;
    QWidget *tab;
    QWidget *tab_2;

    void setupUi(QWidget *MatGui__DlgInspectAppearance)
    {
        if (MatGui__DlgInspectAppearance->objectName().isEmpty())
            MatGui__DlgInspectAppearance->setObjectName("MatGui__DlgInspectAppearance");
        MatGui__DlgInspectAppearance->resize(739, 1556);
        verticalLayout = new QVBoxLayout(MatGui__DlgInspectAppearance);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(MatGui__DlgInspectAppearance);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 711, 1528));
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
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tabAppearance = new QTabWidget(groupBox_2);
        tabAppearance->setObjectName("tabAppearance");
        tab = new QWidget();
        tab->setObjectName("tab");
        tabAppearance->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabAppearance->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabAppearance);


        verticalLayout_2->addWidget(groupBox_2);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(MatGui__DlgInspectAppearance);

        QMetaObject::connectSlotsByName(MatGui__DlgInspectAppearance);
    } // setupUi

    void retranslateUi(QWidget *MatGui__DlgInspectAppearance)
    {
        MatGui__DlgInspectAppearance->setWindowTitle(QCoreApplication::translate("MatGui::DlgInspectAppearance", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MatGui::DlgInspectAppearance", "Document", nullptr));
        label->setText(QCoreApplication::translate("MatGui::DlgInspectAppearance", "Document name", nullptr));
#if QT_CONFIG(tooltip)
        editDocument->setToolTip(QCoreApplication::translate("MatGui::DlgInspectAppearance", "Name of the active document", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("MatGui::DlgInspectAppearance", "Label / internal name", nullptr));
        label_3->setText(QCoreApplication::translate("MatGui::DlgInspectAppearance", "Sub.Shape / Type", nullptr));
        label_4->setText(QCoreApplication::translate("MatGui::DlgInspectAppearance", "Shape.TypeID / TypeID", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MatGui::DlgInspectAppearance", "Appearance", nullptr));
        tabAppearance->setTabText(tabAppearance->indexOf(tab), QCoreApplication::translate("MatGui::DlgInspectAppearance", "Tab 1", nullptr));
        tabAppearance->setTabText(tabAppearance->indexOf(tab_2), QCoreApplication::translate("MatGui::DlgInspectAppearance", "Tab 2", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class DlgInspectAppearance: public Ui_DlgInspectAppearance {};
} // namespace Ui
} // namespace MatGui

#endif // UI_DLGINSPECTAPPEARANCE_H
