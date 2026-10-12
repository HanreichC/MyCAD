/********************************************************************************
** Form generated from reading UI file 'DlgSettingsViewColor.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSVIEWCOLOR_H
#define UI_DLGSETTINGSVIEWCOLOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsViewColor
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxColor;
    QGridLayout *gridLayout;
    QSpacerItem *spacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    Gui::PrefRadioButton *radioButtonSimple;
    Gui::PrefRadioButton *radioButtonGradient;
    Gui::PrefRadioButton *rbRadialGradient;
    Gui::PrefColorButton *SelectionColor_Background;
    QGridLayout *_4;
    QToolButton *SwitchGradientColors;
    QLabel *color1Label;
    Gui::PrefColorButton *backgroundColorFrom;
    QLabel *color2Label;
    Gui::PrefColorButton *backgroundColorMid;
    Gui::PrefCheckBox *checkMidColor;
    QLabel *color3Label;
    Gui::PrefColorButton *backgroundColorTo;
    QGroupBox *groupBoxTree;
    QGridLayout *gridLayout1;
    QGridLayout *gridLayout2;
    QLabel *label_2;
    Gui::PrefColorButton *TreeEditColor;
    QLabel *label_3;
    Gui::PrefColorButton *TreeActiveColor;
    QSpacerItem *spacer_5;
    QGroupBox *groupColorBar;
    QGridLayout *gridLayout3;
    QGridLayout *gridLayout4;
    QLabel *label_CbLabelColor;
    Gui::PrefColorButton *CbLabelColor;
    QLabel *label_CbLabelTextSize;
    Gui::PrefSpinBox *CbLabelTextSize;
    QSpacerItem *spacer_6;
    QSpacerItem *spacer_7;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsViewColor)
    {
        if (Gui__Dialog__DlgSettingsViewColor->objectName().isEmpty())
            Gui__Dialog__DlgSettingsViewColor->setObjectName("Gui__Dialog__DlgSettingsViewColor");
        Gui__Dialog__DlgSettingsViewColor->resize(405, 400);
        verticalLayout = new QVBoxLayout(Gui__Dialog__DlgSettingsViewColor);
        verticalLayout->setObjectName("verticalLayout");
        groupBoxColor = new QGroupBox(Gui__Dialog__DlgSettingsViewColor);
        groupBoxColor->setObjectName("groupBoxColor");
        gridLayout = new QGridLayout(groupBoxColor);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(9, 9, 9, 9);
        spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(spacer, 2, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        radioButtonSimple = new Gui::PrefRadioButton(groupBoxColor);
        radioButtonSimple->setObjectName("radioButtonSimple");
        radioButtonSimple->setProperty("prefEntry", QVariant(QByteArray("Simple")));
        radioButtonSimple->setProperty("prefPath", QVariant(QByteArray("View")));

        horizontalLayout_2->addWidget(radioButtonSimple);

        radioButtonGradient = new Gui::PrefRadioButton(groupBoxColor);
        radioButtonGradient->setObjectName("radioButtonGradient");
        radioButtonGradient->setChecked(true);
        radioButtonGradient->setProperty("prefEntry", QVariant(QByteArray("Gradient")));
        radioButtonGradient->setProperty("prefPath", QVariant(QByteArray("View")));

        horizontalLayout_2->addWidget(radioButtonGradient);

        rbRadialGradient = new Gui::PrefRadioButton(groupBoxColor);
        rbRadialGradient->setObjectName("rbRadialGradient");
        rbRadialGradient->setChecked(false);
        rbRadialGradient->setProperty("prefEntry", QVariant(QByteArray("RadialGradient")));
        rbRadialGradient->setProperty("prefPath", QVariant(QByteArray("View")));

        horizontalLayout_2->addWidget(rbRadialGradient);


        verticalLayout_3->addLayout(horizontalLayout_2);

        SelectionColor_Background = new Gui::PrefColorButton(groupBoxColor);
        SelectionColor_Background->setObjectName("SelectionColor_Background");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SelectionColor_Background->sizePolicy().hasHeightForWidth());
        SelectionColor_Background->setSizePolicy(sizePolicy);
        SelectionColor_Background->setProperty("color", QVariant(QColor(20, 20, 163)));
        SelectionColor_Background->setProperty("prefEntry", QVariant(QByteArray("BackgroundColor")));
        SelectionColor_Background->setProperty("prefPath", QVariant(QByteArray("View")));

        verticalLayout_3->addWidget(SelectionColor_Background);

        _4 = new QGridLayout();
        _4->setSpacing(6);
        _4->setObjectName("_4");
        _4->setContentsMargins(0, 0, 0, 0);
        SwitchGradientColors = new QToolButton(groupBoxColor);
        SwitchGradientColors->setObjectName("SwitchGradientColors");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/button_sort.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        SwitchGradientColors->setIcon(icon);

        _4->addWidget(SwitchGradientColors, 1, 0, 1, 1);

        color1Label = new QLabel(groupBoxColor);
        color1Label->setObjectName("color1Label");

        _4->addWidget(color1Label, 0, 1, 1, 1);

        backgroundColorFrom = new Gui::PrefColorButton(groupBoxColor);
        backgroundColorFrom->setObjectName("backgroundColorFrom");
        backgroundColorFrom->setProperty("color", QVariant(QColor(51, 51, 101)));
        backgroundColorFrom->setProperty("prefEntry", QVariant(QByteArray("BackgroundColor2")));
        backgroundColorFrom->setProperty("prefPath", QVariant(QByteArray("View")));

        _4->addWidget(backgroundColorFrom, 0, 2, 1, 1);

        color2Label = new QLabel(groupBoxColor);
        color2Label->setObjectName("color2Label");

        _4->addWidget(color2Label, 1, 1, 1, 1);

        backgroundColorMid = new Gui::PrefColorButton(groupBoxColor);
        backgroundColorMid->setObjectName("backgroundColorMid");
        backgroundColorMid->setProperty("color", QVariant(QColor(111, 111, 147)));
        backgroundColorMid->setProperty("prefEntry", QVariant(QByteArray("BackgroundColor4")));
        backgroundColorMid->setProperty("prefPath", QVariant(QByteArray("View")));

        _4->addWidget(backgroundColorMid, 1, 2, 1, 1);

        checkMidColor = new Gui::PrefCheckBox(groupBoxColor);
        checkMidColor->setObjectName("checkMidColor");
        checkMidColor->setProperty("prefEntry", QVariant(QByteArray("UseBackgroundColorMid")));
        checkMidColor->setProperty("prefPath", QVariant(QByteArray("View")));

        _4->addWidget(checkMidColor, 1, 3, 1, 1);

        color3Label = new QLabel(groupBoxColor);
        color3Label->setObjectName("color3Label");

        _4->addWidget(color3Label, 2, 1, 1, 1);

        backgroundColorTo = new Gui::PrefColorButton(groupBoxColor);
        backgroundColorTo->setObjectName("backgroundColorTo");
        backgroundColorTo->setProperty("color", QVariant(QColor(151, 151, 170)));
        backgroundColorTo->setProperty("prefEntry", QVariant(QByteArray("BackgroundColor3")));
        backgroundColorTo->setProperty("prefPath", QVariant(QByteArray("View")));

        _4->addWidget(backgroundColorTo, 2, 2, 1, 1);


        verticalLayout_3->addLayout(_4);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBoxColor);

        groupBoxTree = new QGroupBox(Gui__Dialog__DlgSettingsViewColor);
        groupBoxTree->setObjectName("groupBoxTree");
        gridLayout1 = new QGridLayout(groupBoxTree);
        gridLayout1->setSpacing(6);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setObjectName("gridLayout2");
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(groupBoxTree);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(240, 0));

        gridLayout2->addWidget(label_2, 0, 0, 1, 1);

        TreeEditColor = new Gui::PrefColorButton(groupBoxTree);
        TreeEditColor->setObjectName("TreeEditColor");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TreeEditColor->sizePolicy().hasHeightForWidth());
        TreeEditColor->setSizePolicy(sizePolicy1);
        TreeEditColor->setProperty("color", QVariant(QColor(0, 171, 255)));
        TreeEditColor->setProperty("prefEntry", QVariant(QByteArray("TreeEditColor")));
        TreeEditColor->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout2->addWidget(TreeEditColor, 0, 1, 1, 1);

        label_3 = new QLabel(groupBoxTree);
        label_3->setObjectName("label_3");

        gridLayout2->addWidget(label_3, 1, 0, 1, 1);

        TreeActiveColor = new Gui::PrefColorButton(groupBoxTree);
        TreeActiveColor->setObjectName("TreeActiveColor");
        sizePolicy1.setHeightForWidth(TreeActiveColor->sizePolicy().hasHeightForWidth());
        TreeActiveColor->setSizePolicy(sizePolicy1);
        TreeActiveColor->setProperty("color", QVariant(QColor(60, 145, 252)));
        TreeActiveColor->setProperty("prefEntry", QVariant(QByteArray("TreeActiveColor")));
        TreeActiveColor->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout2->addWidget(TreeActiveColor, 1, 1, 1, 1);


        gridLayout1->addLayout(gridLayout2, 0, 0, 1, 1);

        spacer_5 = new QSpacerItem(183, 23, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout1->addItem(spacer_5, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBoxTree);

        groupColorBar = new QGroupBox(Gui__Dialog__DlgSettingsViewColor);
        groupColorBar->setObjectName("groupColorBar");
        gridLayout3 = new QGridLayout(groupColorBar);
        gridLayout3->setSpacing(6);
        gridLayout3->setObjectName("gridLayout3");
        gridLayout3->setContentsMargins(9, 9, 9, 9);
        gridLayout4 = new QGridLayout();
        gridLayout4->setSpacing(6);
        gridLayout4->setObjectName("gridLayout4");
        gridLayout4->setContentsMargins(0, 0, 0, 0);
        label_CbLabelColor = new QLabel(groupColorBar);
        label_CbLabelColor->setObjectName("label_CbLabelColor");
        label_CbLabelColor->setMinimumSize(QSize(240, 0));

        gridLayout4->addWidget(label_CbLabelColor, 0, 0, 1, 1);

        CbLabelColor = new Gui::PrefColorButton(groupColorBar);
        CbLabelColor->setObjectName("CbLabelColor");
        CbLabelColor->setEnabled(true);
        sizePolicy1.setHeightForWidth(CbLabelColor->sizePolicy().hasHeightForWidth());
        CbLabelColor->setSizePolicy(sizePolicy1);
        CbLabelColor->setProperty("color", QVariant(QColor(255, 255, 255)));
        CbLabelColor->setProperty("prefEntry", QVariant(QByteArray("CbLabelColor")));
        CbLabelColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout4->addWidget(CbLabelColor, 0, 1, 1, 1);

        label_CbLabelTextSize = new QLabel(groupColorBar);
        label_CbLabelTextSize->setObjectName("label_CbLabelTextSize");

        gridLayout4->addWidget(label_CbLabelTextSize, 1, 0, 1, 1);

        CbLabelTextSize = new Gui::PrefSpinBox(groupColorBar);
        CbLabelTextSize->setObjectName("CbLabelTextSize");
        CbLabelTextSize->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        CbLabelTextSize->setMinimum(4);
        CbLabelTextSize->setMaximum(36);
        CbLabelTextSize->setValue(13);
        CbLabelTextSize->setProperty("prefEntry", QVariant(QByteArray("CbLabelTextSize")));
        CbLabelTextSize->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout4->addWidget(CbLabelTextSize, 1, 1, 1, 1);


        gridLayout3->addLayout(gridLayout4, 0, 0, 1, 1);

        spacer_6 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout3->addItem(spacer_6, 0, 1, 1, 1);


        verticalLayout->addWidget(groupColorBar);

        spacer_7 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacer_7);

        QWidget::setTabOrder(SelectionColor_Background, backgroundColorFrom);
        QWidget::setTabOrder(backgroundColorFrom, backgroundColorTo);
        QWidget::setTabOrder(backgroundColorTo, checkMidColor);
        QWidget::setTabOrder(checkMidColor, backgroundColorMid);

        retranslateUi(Gui__Dialog__DlgSettingsViewColor);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsViewColor);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsViewColor)
    {
        Gui__Dialog__DlgSettingsViewColor->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Colors", nullptr));
#if QT_CONFIG(tooltip)
        groupBoxColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Background color for the model view", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBoxColor->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Background Color", nullptr));
#if QT_CONFIG(tooltip)
        radioButtonSimple->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Background will have the selected color", nullptr));
#endif // QT_CONFIG(tooltip)
        radioButtonSimple->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Simple color", nullptr));
#if QT_CONFIG(tooltip)
        radioButtonGradient->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Background will have the selected color gradient", nullptr));
#endif // QT_CONFIG(tooltip)
        radioButtonGradient->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Linear gradient", nullptr));
#if QT_CONFIG(tooltip)
        rbRadialGradient->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Background will have the selected color gradient", nullptr));
#endif // QT_CONFIG(tooltip)
        rbRadialGradient->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Radial gradient", nullptr));
#if QT_CONFIG(tooltip)
        SelectionColor_Background->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Background will have the selected color", nullptr));
#endif // QT_CONFIG(tooltip)
        SelectionColor_Background->setText(QString());
#if QT_CONFIG(tooltip)
        SwitchGradientColors->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Switches the colors of the gradient", nullptr));
#endif // QT_CONFIG(tooltip)
        SwitchGradientColors->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Switch", nullptr));
        color1Label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Top", nullptr));
        backgroundColorFrom->setText(QString());
        color2Label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Middle", nullptr));
        backgroundColorMid->setText(QString());
#if QT_CONFIG(tooltip)
        checkMidColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Color gradient will get the selected color as middle color", nullptr));
#endif // QT_CONFIG(tooltip)
        checkMidColor->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Middle color", nullptr));
        color3Label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Bottom", nullptr));
        backgroundColorTo->setText(QString());
        groupBoxTree->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Tree View", nullptr));
#if QT_CONFIG(tooltip)
        label_2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Object being edited", nullptr));
#if QT_CONFIG(tooltip)
        TreeEditColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Background color for objects in the tree view that are currently edited", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Active container object", nullptr));
#if QT_CONFIG(tooltip)
        TreeActiveColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Background color for active containers (e.g. part or body) in the tree view", nullptr));
#endif // QT_CONFIG(tooltip)
        groupColorBar->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Color Bar", nullptr));
#if QT_CONFIG(tooltip)
        label_CbLabelColor->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_CbLabelColor->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Label text color", nullptr));
#if QT_CONFIG(tooltip)
        CbLabelColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Color bar label text color (e.g. in Mesh and FEM)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_CbLabelTextSize->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Label text size", nullptr));
#if QT_CONFIG(tooltip)
        CbLabelTextSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", "Color bar label text size (e.g. in Mesh and FEM)", nullptr));
#endif // QT_CONFIG(tooltip)
        CbLabelTextSize->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsViewColor", " pt", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsViewColor: public Ui_DlgSettingsViewColor {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSVIEWCOLOR_H
