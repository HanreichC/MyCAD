/********************************************************************************
** Form generated from reading UI file 'DlgSettingsLightSources.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSLIGHTSOURCES_H
#define UI_DLGSETTINGSLIGHTSOURCES_H

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
#include "Gui/QuantitySpinBox.h"
#include "Gui/View3DInventorViewer.h"
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsLightSources
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBoxDirection;
    QGridLayout *gridLayout_3;
    Gui::View3DInventorViewer *viewer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QToolButton *zoomInButton;
    QToolButton *zoomOutButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *bottomSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *light1Label;
    Gui::PrefSpinBox *ambientLightIntensitySpinBox;
    Gui::PrefColorButton *backLightColor;
    Gui::PrefCheckBox *mainLightEnable;
    Gui::QuantitySpinBox *backLightHorizontalAngle;
    Gui::QuantitySpinBox *backLightVerticalAngle;
    Gui::PrefCheckBox *backLightEnable;
    Gui::QuantitySpinBox *fillLightHorizontalAngle;
    QLabel *light1Label_2;
    Gui::PrefColorButton *ambientLightColor;
    QLabel *light1Label_3;
    Gui::PrefSpinBox *mainLightIntensitySpinBox;
    Gui::QuantitySpinBox *mainLightHorizontalAngle;
    Gui::QuantitySpinBox *fillLightVerticalAngle;
    Gui::PrefSpinBox *backLightIntensitySpinBox;
    Gui::PrefCheckBox *fillLightEnable;
    Gui::PrefSpinBox *fillLightIntensitySpinBox;
    QLabel *light1Label_4;
    QSpacerItem *horizontalSpacer_2;
    Gui::PrefColorButton *fillLightColor;
    Gui::QuantitySpinBox *mainLightVerticalAngle;
    Gui::PrefColorButton *mainLightColor;
    QLabel *label;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsLightSources)
    {
        if (Gui__Dialog__DlgSettingsLightSources->objectName().isEmpty())
            Gui__Dialog__DlgSettingsLightSources->setObjectName("Gui__Dialog__DlgSettingsLightSources");
        Gui__Dialog__DlgSettingsLightSources->resize(743, 515);
        gridLayout_2 = new QGridLayout(Gui__Dialog__DlgSettingsLightSources);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBoxDirection = new QGroupBox(Gui__Dialog__DlgSettingsLightSources);
        groupBoxDirection->setObjectName("groupBoxDirection");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(groupBoxDirection->sizePolicy().hasHeightForWidth());
        groupBoxDirection->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(groupBoxDirection);
        gridLayout_3->setObjectName("gridLayout_3");
        viewer = new Gui::View3DInventorViewer(groupBoxDirection);
        viewer->setObjectName("viewer");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(viewer->sizePolicy().hasHeightForWidth());
        viewer->setSizePolicy(sizePolicy1);
        viewer->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        horizontalLayout = new QHBoxLayout(viewer);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, -1, 2, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        zoomInButton = new QToolButton(viewer);
        zoomInButton->setObjectName("zoomInButton");
        zoomInButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/FreeCAD-default/scalable/zoom-in.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        zoomInButton->setIcon(icon);
        zoomInButton->setIconSize(QSize(32, 32));

        verticalLayout->addWidget(zoomInButton);

        zoomOutButton = new QToolButton(viewer);
        zoomOutButton->setObjectName("zoomOutButton");
        zoomOutButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/FreeCAD-default/scalable/zoom-out.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        zoomOutButton->setIcon(icon1);
        zoomOutButton->setIconSize(QSize(32, 32));

        verticalLayout->addWidget(zoomOutButton);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_3->addWidget(viewer, 0, 0, 2, 1);


        gridLayout_2->addWidget(groupBoxDirection, 1, 0, 2, 1);

        bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(bottomSpacer, 3, 0, 1, 1);

        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsLightSources);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        light1Label = new QLabel(groupBox);
        light1Label->setObjectName("light1Label");

        gridLayout->addWidget(light1Label, 0, 4, 1, 1);

        ambientLightIntensitySpinBox = new Gui::PrefSpinBox(groupBox);
        ambientLightIntensitySpinBox->setObjectName("ambientLightIntensitySpinBox");
        ambientLightIntensitySpinBox->setMaximum(100);
        ambientLightIntensitySpinBox->setValue(20);
        ambientLightIntensitySpinBox->setProperty("prefEntry", QVariant(QByteArray("AmbientLightIntensity")));
        ambientLightIntensitySpinBox->setProperty("prefPath", QVariant(QByteArray("View/LightSources")));

        gridLayout->addWidget(ambientLightIntensitySpinBox, 4, 6, 1, 1);

        backLightColor = new Gui::PrefColorButton(groupBox);
        backLightColor->setObjectName("backLightColor");
        backLightColor->setColor(QColor(245, 245, 238));
        backLightColor->setProperty("prefEntry", QVariant(QByteArray("BacklightColor")));
        backLightColor->setProperty("prefPath", QVariant(QByteArray("View/LightSources")));

        gridLayout->addWidget(backLightColor, 2, 4, 1, 1);

        mainLightEnable = new Gui::PrefCheckBox(groupBox);
        mainLightEnable->setObjectName("mainLightEnable");
        mainLightEnable->setChecked(true);
        mainLightEnable->setProperty("prefEntry", QVariant(QByteArray("EnableHeadlight")));
        mainLightEnable->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(mainLightEnable, 1, 0, 1, 1);

        backLightHorizontalAngle = new Gui::QuantitySpinBox(groupBox);
        backLightHorizontalAngle->setObjectName("backLightHorizontalAngle");
        backLightHorizontalAngle->setProperty("unit", QVariant(QString::fromUtf8("")));
        backLightHorizontalAngle->setValue(-130.000000000000000);

        gridLayout->addWidget(backLightHorizontalAngle, 2, 2, 1, 1);

        backLightVerticalAngle = new Gui::QuantitySpinBox(groupBox);
        backLightVerticalAngle->setObjectName("backLightVerticalAngle");
        backLightVerticalAngle->setProperty("unit", QVariant(QString::fromUtf8("")));
        backLightVerticalAngle->setValue(-10.000000000000000);

        gridLayout->addWidget(backLightVerticalAngle, 2, 3, 1, 1);

        backLightEnable = new Gui::PrefCheckBox(groupBox);
        backLightEnable->setObjectName("backLightEnable");
        backLightEnable->setChecked(true);
        backLightEnable->setProperty("prefEntry", QVariant(QByteArray("EnableBacklight")));
        backLightEnable->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(backLightEnable, 2, 0, 1, 1);

        fillLightHorizontalAngle = new Gui::QuantitySpinBox(groupBox);
        fillLightHorizontalAngle->setObjectName("fillLightHorizontalAngle");
        fillLightHorizontalAngle->setProperty("unit", QVariant(QString::fromUtf8("")));
        fillLightHorizontalAngle->setValue(-40.000000000000000);

        gridLayout->addWidget(fillLightHorizontalAngle, 3, 2, 1, 1);

        light1Label_2 = new QLabel(groupBox);
        light1Label_2->setObjectName("light1Label_2");

        gridLayout->addWidget(light1Label_2, 0, 3, 1, 1);

        ambientLightColor = new Gui::PrefColorButton(groupBox);
        ambientLightColor->setObjectName("ambientLightColor");
        ambientLightColor->setColor(QColor(255, 255, 255));
        ambientLightColor->setProperty("prefEntry", QVariant(QByteArray("AmbientLightColor")));
        ambientLightColor->setProperty("prefPath", QVariant(QByteArray("View/LightSources")));

        gridLayout->addWidget(ambientLightColor, 4, 4, 1, 1);

        light1Label_3 = new QLabel(groupBox);
        light1Label_3->setObjectName("light1Label_3");

        gridLayout->addWidget(light1Label_3, 0, 2, 1, 1);

        mainLightIntensitySpinBox = new Gui::PrefSpinBox(groupBox);
        mainLightIntensitySpinBox->setObjectName("mainLightIntensitySpinBox");
        mainLightIntensitySpinBox->setMaximum(100);
        mainLightIntensitySpinBox->setValue(90);
        mainLightIntensitySpinBox->setProperty("prefEntry", QVariant(QByteArray("HeadlightIntensity")));
        mainLightIntensitySpinBox->setProperty("prefPath", QVariant(QByteArray("View/LightSources")));

        gridLayout->addWidget(mainLightIntensitySpinBox, 1, 6, 1, 1);

        mainLightHorizontalAngle = new Gui::QuantitySpinBox(groupBox);
        mainLightHorizontalAngle->setObjectName("mainLightHorizontalAngle");
        mainLightHorizontalAngle->setProperty("unit", QVariant(QString::fromUtf8("")));
        mainLightHorizontalAngle->setValue(100.000000000000000);

        gridLayout->addWidget(mainLightHorizontalAngle, 1, 2, 1, 1);

        fillLightVerticalAngle = new Gui::QuantitySpinBox(groupBox);
        fillLightVerticalAngle->setObjectName("fillLightVerticalAngle");
        fillLightVerticalAngle->setProperty("unit", QVariant(QString::fromUtf8("")));
        fillLightVerticalAngle->setValue(5.000000000000000);

        gridLayout->addWidget(fillLightVerticalAngle, 3, 3, 1, 1);

        backLightIntensitySpinBox = new Gui::PrefSpinBox(groupBox);
        backLightIntensitySpinBox->setObjectName("backLightIntensitySpinBox");
        backLightIntensitySpinBox->setMaximum(100);
        backLightIntensitySpinBox->setValue(60);
        backLightIntensitySpinBox->setProperty("prefEntry", QVariant(QByteArray("BacklightIntensity")));
        backLightIntensitySpinBox->setProperty("prefPath", QVariant(QByteArray("View/LightSources")));

        gridLayout->addWidget(backLightIntensitySpinBox, 2, 6, 1, 1);

        fillLightEnable = new Gui::PrefCheckBox(groupBox);
        fillLightEnable->setObjectName("fillLightEnable");
        fillLightEnable->setChecked(true);
        fillLightEnable->setProperty("prefEntry", QVariant(QByteArray("EnableFillLight")));
        fillLightEnable->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(fillLightEnable, 3, 0, 1, 1);

        fillLightIntensitySpinBox = new Gui::PrefSpinBox(groupBox);
        fillLightIntensitySpinBox->setObjectName("fillLightIntensitySpinBox");
        fillLightIntensitySpinBox->setMaximum(100);
        fillLightIntensitySpinBox->setValue(40);
        fillLightIntensitySpinBox->setProperty("prefEntry", QVariant(QByteArray("FillLightIntensity")));
        fillLightIntensitySpinBox->setProperty("prefPath", QVariant(QByteArray("View/LightSources")));

        gridLayout->addWidget(fillLightIntensitySpinBox, 3, 6, 1, 1);

        light1Label_4 = new QLabel(groupBox);
        light1Label_4->setObjectName("light1Label_4");

        gridLayout->addWidget(light1Label_4, 0, 6, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        fillLightColor = new Gui::PrefColorButton(groupBox);
        fillLightColor->setObjectName("fillLightColor");
        fillLightColor->setColor(QColor(230, 250, 255));
        fillLightColor->setProperty("prefEntry", QVariant(QByteArray("FillLightColor")));
        fillLightColor->setProperty("prefPath", QVariant(QByteArray("View/LightSources")));

        gridLayout->addWidget(fillLightColor, 3, 4, 1, 1);

        mainLightVerticalAngle = new Gui::QuantitySpinBox(groupBox);
        mainLightVerticalAngle->setObjectName("mainLightVerticalAngle");
        mainLightVerticalAngle->setProperty("unit", QVariant(QString::fromUtf8("")));
        mainLightVerticalAngle->setValue(-46.000000000000000);

        gridLayout->addWidget(mainLightVerticalAngle, 1, 3, 1, 1);

        mainLightColor = new Gui::PrefColorButton(groupBox);
        mainLightColor->setObjectName("mainLightColor");
        mainLightColor->setColor(QColor(255, 255, 255));
        mainLightColor->setProperty("prefEntry", QVariant(QByteArray("HeadlightColor")));
        mainLightColor->setProperty("prefPath", QVariant(QByteArray("View/LightSources")));

        gridLayout->addWidget(mainLightColor, 1, 4, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 4, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        QWidget::setTabOrder(mainLightEnable, mainLightHorizontalAngle);
        QWidget::setTabOrder(mainLightHorizontalAngle, mainLightVerticalAngle);
        QWidget::setTabOrder(mainLightVerticalAngle, mainLightColor);
        QWidget::setTabOrder(mainLightColor, mainLightIntensitySpinBox);
        QWidget::setTabOrder(mainLightIntensitySpinBox, backLightEnable);
        QWidget::setTabOrder(backLightEnable, backLightHorizontalAngle);
        QWidget::setTabOrder(backLightHorizontalAngle, backLightVerticalAngle);
        QWidget::setTabOrder(backLightVerticalAngle, backLightColor);
        QWidget::setTabOrder(backLightColor, backLightIntensitySpinBox);
        QWidget::setTabOrder(backLightIntensitySpinBox, fillLightEnable);
        QWidget::setTabOrder(fillLightEnable, fillLightHorizontalAngle);
        QWidget::setTabOrder(fillLightHorizontalAngle, fillLightVerticalAngle);
        QWidget::setTabOrder(fillLightVerticalAngle, fillLightColor);
        QWidget::setTabOrder(fillLightColor, fillLightIntensitySpinBox);
        QWidget::setTabOrder(fillLightIntensitySpinBox, ambientLightColor);
        QWidget::setTabOrder(ambientLightColor, ambientLightIntensitySpinBox);

        retranslateUi(Gui__Dialog__DlgSettingsLightSources);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsLightSources);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsLightSources)
    {
        Gui__Dialog__DlgSettingsLightSources->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Light Sources", nullptr));
        groupBoxDirection->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Preview", nullptr));
#if QT_CONFIG(tooltip)
        zoomInButton->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Pushes in", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        zoomOutButton->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Pulls out", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Light Sources", nullptr));
        light1Label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Color", nullptr));
        ambientLightIntensitySpinBox->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "%", nullptr));
        mainLightEnable->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Main light", nullptr));
        backLightEnable->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Backlight", nullptr));
        light1Label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Vertical angle", nullptr));
        light1Label_3->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Horizontal angle", nullptr));
        mainLightIntensitySpinBox->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "%", nullptr));
        backLightIntensitySpinBox->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "%", nullptr));
        fillLightEnable->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Fill light", nullptr));
        fillLightIntensitySpinBox->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "%", nullptr));
        light1Label_4->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Intensity", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsLightSources", "Ambient light", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsLightSources: public Ui_DlgSettingsLightSources {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSLIGHTSOURCES_H
