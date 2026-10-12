/********************************************************************************
** Form generated from reading UI file 'DlgExtrusion.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEXTRUSION_H
#define UI_DLGEXTRUSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include "Gui/QuantitySpinBox.h"

namespace PartGui {

class Ui_DlgExtrusion
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QRadioButton *rbDirModeNormal;
    QRadioButton *rbDirModeEdge;
    QCheckBox *chkReversed;
    QLineEdit *txtLink;
    QPushButton *btnSelectEdge;
    QRadioButton *rbDirModeCustom;
    QGridLayout *gridLayout_3;
    QPushButton *btnX;
    QDoubleSpinBox *dirX;
    QPushButton *btnY;
    QDoubleSpinBox *dirY;
    QPushButton *btnZ;
    QDoubleSpinBox *dirZ;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_5;
    Gui::QuantitySpinBox *spinLenFwd;
    QLabel *label_6;
    Gui::QuantitySpinBox *spinLenRev;
    QCheckBox *chkSymmetric;
    QGridLayout *gridLayout_4;
    QLabel *label;
    Gui::QuantitySpinBox *spinTaperAngle;
    QLabel *label_2;
    Gui::QuantitySpinBox *spinTaperAngleRev;
    QCheckBox *chkSolid;
    QFrame *line;
    QTreeWidget *treeWidget;
    QLabel *statusLabel;

    void setupUi(QDialog *PartGui__DlgExtrusion)
    {
        if (PartGui__DlgExtrusion->objectName().isEmpty())
            PartGui__DlgExtrusion->setObjectName("PartGui__DlgExtrusion");
        PartGui__DlgExtrusion->resize(300, 564);
        verticalLayout = new QVBoxLayout(PartGui__DlgExtrusion);
        verticalLayout->setObjectName("verticalLayout");
        groupBox_2 = new QGroupBox(PartGui__DlgExtrusion);
        groupBox_2->setObjectName("groupBox_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        rbDirModeNormal = new QRadioButton(groupBox_2);
        rbDirModeNormal->setObjectName("rbDirModeNormal");
        rbDirModeNormal->setChecked(true);

        gridLayout_2->addWidget(rbDirModeNormal, 3, 0, 1, 1);

        rbDirModeEdge = new QRadioButton(groupBox_2);
        rbDirModeEdge->setObjectName("rbDirModeEdge");

        gridLayout_2->addWidget(rbDirModeEdge, 4, 0, 1, 1);

        chkReversed = new QCheckBox(groupBox_2);
        chkReversed->setObjectName("chkReversed");

        gridLayout_2->addWidget(chkReversed, 4, 2, 1, 1);

        txtLink = new QLineEdit(groupBox_2);
        txtLink->setObjectName("txtLink");

        gridLayout_2->addWidget(txtLink, 5, 0, 1, 1);

        btnSelectEdge = new QPushButton(groupBox_2);
        btnSelectEdge->setObjectName("btnSelectEdge");

        gridLayout_2->addWidget(btnSelectEdge, 5, 2, 1, 1);

        rbDirModeCustom = new QRadioButton(groupBox_2);
        rbDirModeCustom->setObjectName("rbDirModeCustom");

        gridLayout_2->addWidget(rbDirModeCustom, 6, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        btnX = new QPushButton(groupBox_2);
        btnX->setObjectName("btnX");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnX->sizePolicy().hasHeightForWidth());
        btnX->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(btnX, 0, 0, 1, 1);

        dirX = new QDoubleSpinBox(groupBox_2);
        dirX->setObjectName("dirX");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dirX->sizePolicy().hasHeightForWidth());
        dirX->setSizePolicy(sizePolicy2);
        dirX->setMinimum(-2147480000.000000000000000);
        dirX->setMaximum(2147480000.000000000000000);

        gridLayout_3->addWidget(dirX, 0, 1, 1, 1);

        btnY = new QPushButton(groupBox_2);
        btnY->setObjectName("btnY");

        gridLayout_3->addWidget(btnY, 1, 0, 1, 1);

        dirY = new QDoubleSpinBox(groupBox_2);
        dirY->setObjectName("dirY");
        sizePolicy2.setHeightForWidth(dirY->sizePolicy().hasHeightForWidth());
        dirY->setSizePolicy(sizePolicy2);
        dirY->setMinimum(-2147480000.000000000000000);
        dirY->setMaximum(2147480000.000000000000000);

        gridLayout_3->addWidget(dirY, 1, 1, 1, 1);

        btnZ = new QPushButton(groupBox_2);
        btnZ->setObjectName("btnZ");

        gridLayout_3->addWidget(btnZ, 2, 0, 1, 1);

        dirZ = new QDoubleSpinBox(groupBox_2);
        dirZ->setObjectName("dirZ");
        sizePolicy2.setHeightForWidth(dirZ->sizePolicy().hasHeightForWidth());
        dirZ->setSizePolicy(sizePolicy2);
        dirZ->setKeyboardTracking(false);
        dirZ->setMinimum(-2147480000.000000000000000);
        dirZ->setMaximum(2147480000.000000000000000);
        dirZ->setValue(1.000000000000000);

        gridLayout_3->addWidget(dirZ, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 7, 0, 1, 3);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(PartGui__DlgExtrusion);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        spinLenFwd = new Gui::QuantitySpinBox(groupBox);
        spinLenFwd->setObjectName("spinLenFwd");
        sizePolicy2.setHeightForWidth(spinLenFwd->sizePolicy().hasHeightForWidth());
        spinLenFwd->setSizePolicy(sizePolicy2);
        spinLenFwd->setMinimumSize(QSize(0, 0));
        spinLenFwd->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spinLenFwd->setMinimum(-2147480000.000000000000000);
        spinLenFwd->setMaximum(2147480000.000000000000000);
        spinLenFwd->setValue(10.000000000000000);

        gridLayout->addWidget(spinLenFwd, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        spinLenRev = new Gui::QuantitySpinBox(groupBox);
        spinLenRev->setObjectName("spinLenRev");
        sizePolicy2.setHeightForWidth(spinLenRev->sizePolicy().hasHeightForWidth());
        spinLenRev->setSizePolicy(sizePolicy2);
        spinLenRev->setMinimumSize(QSize(0, 0));
        spinLenRev->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spinLenRev->setMinimum(-2147480000.000000000000000);
        spinLenRev->setMaximum(2147480000.000000000000000);
        spinLenRev->setValue(0.000000000000000);

        gridLayout->addWidget(spinLenRev, 1, 1, 1, 1);

        chkSymmetric = new QCheckBox(groupBox);
        chkSymmetric->setObjectName("chkSymmetric");

        gridLayout->addWidget(chkSymmetric, 2, 0, 1, 2);


        verticalLayout->addWidget(groupBox);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        label = new QLabel(PartGui__DlgExtrusion);
        label->setObjectName("label");

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        spinTaperAngle = new Gui::QuantitySpinBox(PartGui__DlgExtrusion);
        spinTaperAngle->setObjectName("spinTaperAngle");
        sizePolicy2.setHeightForWidth(spinTaperAngle->sizePolicy().hasHeightForWidth());
        spinTaperAngle->setSizePolicy(sizePolicy2);
        spinTaperAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        spinTaperAngle->setMinimum(-89.999999000000003);
        spinTaperAngle->setMaximum(89.999999000000003);

        gridLayout_4->addWidget(spinTaperAngle, 0, 1, 1, 1);

        label_2 = new QLabel(PartGui__DlgExtrusion);
        label_2->setObjectName("label_2");

        gridLayout_4->addWidget(label_2, 1, 0, 1, 1);

        spinTaperAngleRev = new Gui::QuantitySpinBox(PartGui__DlgExtrusion);
        spinTaperAngleRev->setObjectName("spinTaperAngleRev");
        sizePolicy2.setHeightForWidth(spinTaperAngleRev->sizePolicy().hasHeightForWidth());
        spinTaperAngleRev->setSizePolicy(sizePolicy2);
        spinTaperAngleRev->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        spinTaperAngleRev->setMinimum(-89.999999000000003);
        spinTaperAngleRev->setMaximum(89.999999000000003);

        gridLayout_4->addWidget(spinTaperAngleRev, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_4);

        chkSolid = new QCheckBox(PartGui__DlgExtrusion);
        chkSolid->setObjectName("chkSolid");

        verticalLayout->addWidget(chkSolid);

        line = new QFrame(PartGui__DlgExtrusion);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        treeWidget = new QTreeWidget(PartGui__DlgExtrusion);
        treeWidget->setObjectName("treeWidget");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy3);
        treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        treeWidget->setIndentation(20);
        treeWidget->setRootIsDecorated(false);

        verticalLayout->addWidget(treeWidget);

        statusLabel = new QLabel(PartGui__DlgExtrusion);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setText(QString::fromUtf8("StatusLabel"));

        verticalLayout->addWidget(statusLabel);

        groupBox_2->raise();
        chkSolid->raise();
        treeWidget->raise();
        statusLabel->raise();
        groupBox->raise();
        line->raise();
        QWidget::setTabOrder(rbDirModeNormal, rbDirModeEdge);
        QWidget::setTabOrder(rbDirModeEdge, chkReversed);
        QWidget::setTabOrder(chkReversed, txtLink);
        QWidget::setTabOrder(txtLink, btnSelectEdge);
        QWidget::setTabOrder(btnSelectEdge, rbDirModeCustom);
        QWidget::setTabOrder(rbDirModeCustom, btnX);
        QWidget::setTabOrder(btnX, dirX);
        QWidget::setTabOrder(dirX, btnY);
        QWidget::setTabOrder(btnY, dirY);
        QWidget::setTabOrder(dirY, btnZ);
        QWidget::setTabOrder(btnZ, dirZ);
        QWidget::setTabOrder(dirZ, spinLenFwd);
        QWidget::setTabOrder(spinLenFwd, spinLenRev);
        QWidget::setTabOrder(spinLenRev, chkSymmetric);
        QWidget::setTabOrder(chkSymmetric, spinTaperAngle);
        QWidget::setTabOrder(spinTaperAngle, spinTaperAngleRev);
        QWidget::setTabOrder(spinTaperAngleRev, chkSolid);
        QWidget::setTabOrder(chkSolid, treeWidget);

        retranslateUi(PartGui__DlgExtrusion);

        QMetaObject::connectSlotsByName(PartGui__DlgExtrusion);
    } // setupUi

    void retranslateUi(QDialog *PartGui__DlgExtrusion)
    {
        PartGui__DlgExtrusion->setWindowTitle(QCoreApplication::translate("PartGui::DlgExtrusion", "Extrude", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PartGui::DlgExtrusion", "Direction", nullptr));
#if QT_CONFIG(tooltip)
        rbDirModeNormal->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Extrudes perpendicularly to the plane of the input shape", nullptr));
#endif // QT_CONFIG(tooltip)
        rbDirModeNormal->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Along normal", nullptr));
#if QT_CONFIG(tooltip)
        rbDirModeEdge->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Set direction to match a direction of straight edge. Hint: to account for length of the edge too, set both lengths to zero.", nullptr));
#endif // QT_CONFIG(tooltip)
        rbDirModeEdge->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Along edge", nullptr));
#if QT_CONFIG(tooltip)
        chkReversed->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Reverses the direction of the extrusion", nullptr));
#endif // QT_CONFIG(tooltip)
        chkReversed->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Reversed", nullptr));
#if QT_CONFIG(tooltip)
        btnSelectEdge->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Starts the selection of edges in the 3D view", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSelectEdge->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Select", nullptr));
#if QT_CONFIG(tooltip)
        rbDirModeCustom->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Specify direction manually using X, Y, Z values", nullptr));
#endif // QT_CONFIG(tooltip)
        rbDirModeCustom->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Custom direction", nullptr));
#if QT_CONFIG(tooltip)
        btnX->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        btnX->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "X", nullptr));
        btnY->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Y", nullptr));
        btnZ->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Z", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::DlgExtrusion", "Length", nullptr));
        label_5->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Along", nullptr));
#if QT_CONFIG(tooltip)
        spinLenFwd->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Length to extrude along direction (can be negative).\n"
"If both lengths are zero, magnitude of direction is used.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_6->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Against", nullptr));
#if QT_CONFIG(tooltip)
        spinLenRev->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Length to extrude against the direction (can be negative)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        chkSymmetric->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Distributes the extrusion length equally to both sides", nullptr));
#endif // QT_CONFIG(tooltip)
        chkSymmetric->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Symmetric", nullptr));
        label->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Taper angle along", nullptr));
#if QT_CONFIG(tooltip)
        spinTaperAngle->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Taper (draft) angle along extrusion direction", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Taper angle against", nullptr));
#if QT_CONFIG(tooltip)
        spinTaperAngleRev->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Taper (draft) angle against extrusion direction", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        chkSolid->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Results in solids if wires are closed, otherwise in shells", nullptr));
#endif // QT_CONFIG(tooltip)
        chkSolid->setText(QCoreApplication::translate("PartGui::DlgExtrusion", "Create solid", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("PartGui::DlgExtrusion", "Shape", nullptr));
#if QT_CONFIG(tooltip)
        treeWidget->setToolTip(QCoreApplication::translate("PartGui::DlgExtrusion", "Select shape(s) that should be extruded", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgExtrusion: public Ui_DlgExtrusion {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGEXTRUSION_H
