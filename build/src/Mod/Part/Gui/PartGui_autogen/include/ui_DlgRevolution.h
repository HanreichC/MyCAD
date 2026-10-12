/********************************************************************************
** Form generated from reading UI file 'DlgRevolution.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGREVOLUTION_H
#define UI_DLGREVOLUTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include "Gui/QuantitySpinBox.h"

namespace PartGui {

class Ui_DlgRevolution
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_1;
    QLabel *label;
    Gui::QuantitySpinBox *xPos;
    QLabel *label_2;
    Gui::QuantitySpinBox *yPos;
    QLabel *label_3;
    Gui::QuantitySpinBox *zPos;
    QGridLayout *gridLayout_2;
    QPushButton *btnX;
    Gui::QuantitySpinBox *xDir;
    QPushButton *btnY;
    Gui::QuantitySpinBox *yDir;
    QPushButton *btnZ;
    Gui::QuantitySpinBox *zDir;
    QPushButton *selectLine;
    QLineEdit *txtAxisLink;
    QFormLayout *formLayout_3;
    QLabel *label_5;
    Gui::QuantitySpinBox *angle;
    QCheckBox *checkSymmetric;
    QCheckBox *checkSolid;

    void setupUi(QDialog *PartGui__DlgRevolution)
    {
        if (PartGui__DlgRevolution->objectName().isEmpty())
            PartGui__DlgRevolution->setObjectName("PartGui__DlgRevolution");
        PartGui__DlgRevolution->resize(426, 599);
        PartGui__DlgRevolution->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(PartGui__DlgRevolution);
#ifndef Q_OS_MACOS
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName("gridLayout");
        treeWidget = new QTreeWidget(PartGui__DlgRevolution);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        treeWidget->setIndentation(20);
        treeWidget->setRootIsDecorated(false);

        gridLayout->addWidget(treeWidget, 0, 3, 1, 1);

        groupBox = new QGroupBox(PartGui__DlgRevolution);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_1 = new QGridLayout();
        gridLayout_1->setObjectName("gridLayout_1");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout_1->addWidget(label, 0, 0, 1, 1);

        xPos = new Gui::QuantitySpinBox(groupBox);
        xPos->setObjectName("xPos");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(xPos->sizePolicy().hasHeightForWidth());
        xPos->setSizePolicy(sizePolicy);
        xPos->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_1->addWidget(xPos, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout_1->addWidget(label_2, 1, 0, 1, 1);

        yPos = new Gui::QuantitySpinBox(groupBox);
        yPos->setObjectName("yPos");
        sizePolicy.setHeightForWidth(yPos->sizePolicy().hasHeightForWidth());
        yPos->setSizePolicy(sizePolicy);
        yPos->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_1->addWidget(yPos, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout_1->addWidget(label_3, 2, 0, 1, 1);

        zPos = new Gui::QuantitySpinBox(groupBox);
        zPos->setObjectName("zPos");
        sizePolicy.setHeightForWidth(zPos->sizePolicy().hasHeightForWidth());
        zPos->setSizePolicy(sizePolicy);
        zPos->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_1->addWidget(zPos, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        btnX = new QPushButton(groupBox);
        btnX->setObjectName("btnX");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnX->sizePolicy().hasHeightForWidth());
        btnX->setSizePolicy(sizePolicy1);
        btnX->setMinimumSize(QSize(0, 0));
        btnX->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(btnX, 0, 0, 1, 1);

        xDir = new Gui::QuantitySpinBox(groupBox);
        xDir->setObjectName("xDir");
        sizePolicy.setHeightForWidth(xDir->sizePolicy().hasHeightForWidth());
        xDir->setSizePolicy(sizePolicy);
        xDir->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout_2->addWidget(xDir, 0, 1, 1, 1);

        btnY = new QPushButton(groupBox);
        btnY->setObjectName("btnY");
        sizePolicy1.setHeightForWidth(btnY->sizePolicy().hasHeightForWidth());
        btnY->setSizePolicy(sizePolicy1);
        btnY->setMinimumSize(QSize(0, 0));
        btnY->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(btnY, 1, 0, 1, 1);

        yDir = new Gui::QuantitySpinBox(groupBox);
        yDir->setObjectName("yDir");
        sizePolicy.setHeightForWidth(yDir->sizePolicy().hasHeightForWidth());
        yDir->setSizePolicy(sizePolicy);
        yDir->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout_2->addWidget(yDir, 1, 1, 1, 1);

        btnZ = new QPushButton(groupBox);
        btnZ->setObjectName("btnZ");
        sizePolicy1.setHeightForWidth(btnZ->sizePolicy().hasHeightForWidth());
        btnZ->setSizePolicy(sizePolicy1);
        btnZ->setMinimumSize(QSize(0, 0));
        btnZ->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(btnZ, 2, 0, 1, 1);

        zDir = new Gui::QuantitySpinBox(groupBox);
        zDir->setObjectName("zDir");
        sizePolicy.setHeightForWidth(zDir->sizePolicy().hasHeightForWidth());
        zDir->setSizePolicy(sizePolicy);
        zDir->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout_2->addWidget(zDir, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        selectLine = new QPushButton(groupBox);
        selectLine->setObjectName("selectLine");

        verticalLayout->addWidget(selectLine);

        txtAxisLink = new QLineEdit(groupBox);
        txtAxisLink->setObjectName("txtAxisLink");
        sizePolicy.setHeightForWidth(txtAxisLink->sizePolicy().hasHeightForWidth());
        txtAxisLink->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(txtAxisLink);


        gridLayout->addWidget(groupBox, 1, 3, 2, 1);

        formLayout_3 = new QFormLayout();
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        formLayout_3->setObjectName("formLayout_3");
        formLayout_3->setHorizontalSpacing(6);
        formLayout_3->setVerticalSpacing(6);
        label_5 = new QLabel(PartGui__DlgRevolution);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(0, QFormLayout::ItemRole::LabelRole, label_5);

        angle = new Gui::QuantitySpinBox(PartGui__DlgRevolution);
        angle->setObjectName("angle");
        sizePolicy.setHeightForWidth(angle->sizePolicy().hasHeightForWidth());
        angle->setSizePolicy(sizePolicy);
        angle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        angle->setMinimum(-360.000000000000000);
        angle->setMaximum(360.000000000000000);
        angle->setValue(360.000000000000000);

        formLayout_3->setWidget(0, QFormLayout::ItemRole::FieldRole, angle);


        gridLayout->addLayout(formLayout_3, 3, 3, 1, 1);

        checkSymmetric = new QCheckBox(PartGui__DlgRevolution);
        checkSymmetric->setObjectName("checkSymmetric");

        gridLayout->addWidget(checkSymmetric, 4, 3, 1, 1);

        checkSolid = new QCheckBox(PartGui__DlgRevolution);
        checkSolid->setObjectName("checkSolid");

        gridLayout->addWidget(checkSolid, 5, 3, 1, 1);

        QWidget::setTabOrder(treeWidget, btnX);
        QWidget::setTabOrder(btnX, btnY);
        QWidget::setTabOrder(btnY, btnZ);
        QWidget::setTabOrder(btnZ, selectLine);
        QWidget::setTabOrder(selectLine, txtAxisLink);
        QWidget::setTabOrder(txtAxisLink, checkSolid);

        retranslateUi(PartGui__DlgRevolution);

        QMetaObject::connectSlotsByName(PartGui__DlgRevolution);
    } // setupUi

    void retranslateUi(QDialog *PartGui__DlgRevolution)
    {
        PartGui__DlgRevolution->setWindowTitle(QCoreApplication::translate("PartGui::DlgRevolution", "Revolve", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("PartGui::DlgRevolution", "Shape", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::DlgRevolution", "Revolution Axis", nullptr));
        label->setText(QCoreApplication::translate("PartGui::DlgRevolution", "Center X", nullptr));
        label_2->setText(QCoreApplication::translate("PartGui::DlgRevolution", "Center Y", nullptr));
        label_3->setText(QCoreApplication::translate("PartGui::DlgRevolution", "Center Z", nullptr));
#if QT_CONFIG(tooltip)
        btnX->setToolTip(QCoreApplication::translate("PartGui::DlgRevolution", "Sets this as axis", nullptr));
#endif // QT_CONFIG(tooltip)
        btnX->setText(QCoreApplication::translate("PartGui::DlgRevolution", "X-Direction", nullptr));
#if QT_CONFIG(tooltip)
        btnY->setToolTip(QCoreApplication::translate("PartGui::DlgRevolution", "Sets this as axis", nullptr));
#endif // QT_CONFIG(tooltip)
        btnY->setText(QCoreApplication::translate("PartGui::DlgRevolution", "Y-Direction", nullptr));
        btnZ->setText(QCoreApplication::translate("PartGui::DlgRevolution", "Z-Direction", nullptr));
        selectLine->setText(QCoreApplication::translate("PartGui::DlgRevolution", "Select Reference", nullptr));
        label_5->setText(QCoreApplication::translate("PartGui::DlgRevolution", "Angle", nullptr));
#if QT_CONFIG(tooltip)
        checkSymmetric->setToolTip(QCoreApplication::translate("PartGui::DlgRevolution", "Extends the revolution forwards and backwards by half the angle", nullptr));
#endif // QT_CONFIG(tooltip)
        checkSymmetric->setText(QCoreApplication::translate("PartGui::DlgRevolution", "Symmetric angle", nullptr));
#if QT_CONFIG(tooltip)
        checkSolid->setToolTip(QCoreApplication::translate("PartGui::DlgRevolution", "Creates a solid. Otherwise it results in a shell.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkSolid->setText(QCoreApplication::translate("PartGui::DlgRevolution", "Create solid", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgRevolution: public Ui_DlgRevolution {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGREVOLUTION_H
