/********************************************************************************
** Form generated from reading UI file 'DlgSettingsCacheDirectory.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSCACHEDIRECTORY_H
#define UI_DLGSETTINGSCACHEDIRECTORY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsCacheDirectory
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *GroupBox5;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *cacheLocation;
    QPushButton *openButton;
    QLabel *labelPeriod;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBoxPeriod;
    QLabel *labelCache;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *comboBoxLimit;
    QLabel *labelCurrentCache;
    QPushButton *pushButtonCheck;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsCacheDirectory)
    {
        if (Gui__Dialog__DlgSettingsCacheDirectory->objectName().isEmpty())
            Gui__Dialog__DlgSettingsCacheDirectory->setObjectName("Gui__Dialog__DlgSettingsCacheDirectory");
        Gui__Dialog__DlgSettingsCacheDirectory->resize(425, 360);
        gridLayout_2 = new QGridLayout(Gui__Dialog__DlgSettingsCacheDirectory);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        GroupBox5 = new QGroupBox(Gui__Dialog__DlgSettingsCacheDirectory);
        GroupBox5->setObjectName("GroupBox5");
        gridLayout_3 = new QGridLayout(GroupBox5);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(GroupBox5);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cacheLocation = new QLineEdit(GroupBox5);
        cacheLocation->setObjectName("cacheLocation");
        cacheLocation->setReadOnly(true);

        gridLayout->addWidget(cacheLocation, 0, 1, 1, 2);

        openButton = new QPushButton(GroupBox5);
        openButton->setObjectName("openButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openButton->sizePolicy().hasHeightForWidth());
        openButton->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/document-open.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        openButton->setIcon(icon);

        gridLayout->addWidget(openButton, 0, 3, 1, 1);

        labelPeriod = new QLabel(GroupBox5);
        labelPeriod->setObjectName("labelPeriod");

        gridLayout->addWidget(labelPeriod, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(118, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        comboBoxPeriod = new QComboBox(GroupBox5);
        comboBoxPeriod->addItem(QString());
        comboBoxPeriod->addItem(QString());
        comboBoxPeriod->addItem(QString());
        comboBoxPeriod->addItem(QString());
        comboBoxPeriod->addItem(QString());
        comboBoxPeriod->addItem(QString());
        comboBoxPeriod->setObjectName("comboBoxPeriod");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxPeriod->sizePolicy().hasHeightForWidth());
        comboBoxPeriod->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBoxPeriod, 1, 2, 1, 2);

        labelCache = new QLabel(GroupBox5);
        labelCache->setObjectName("labelCache");

        gridLayout->addWidget(labelCache, 2, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(118, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 1, 1, 1);

        comboBoxLimit = new QComboBox(GroupBox5);
        comboBoxLimit->setObjectName("comboBoxLimit");
        sizePolicy1.setHeightForWidth(comboBoxLimit->sizePolicy().hasHeightForWidth());
        comboBoxLimit->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboBoxLimit, 2, 2, 1, 2);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 3);

        labelCurrentCache = new QLabel(GroupBox5);
        labelCurrentCache->setObjectName("labelCurrentCache");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelCurrentCache->sizePolicy().hasHeightForWidth());
        labelCurrentCache->setSizePolicy(sizePolicy2);
        labelCurrentCache->setText(QString::fromUtf8("Current cache size"));

        gridLayout_3->addWidget(labelCurrentCache, 1, 0, 1, 1);

        pushButtonCheck = new QPushButton(GroupBox5);
        pushButtonCheck->setObjectName("pushButtonCheck");

        gridLayout_3->addWidget(pushButtonCheck, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(150, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        gridLayout_2->addWidget(GroupBox5, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 169, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgSettingsCacheDirectory);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsCacheDirectory);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsCacheDirectory)
    {
        Gui__Dialog__DlgSettingsCacheDirectory->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Cache", nullptr));
        GroupBox5->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Cache Directory", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Location (read-only)", nullptr));
#if QT_CONFIG(tooltip)
        openButton->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Browse cache directory", nullptr));
#endif // QT_CONFIG(tooltip)
        labelPeriod->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Check periodically at program start", nullptr));
        comboBoxPeriod->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Always", nullptr));
        comboBoxPeriod->setItemText(1, QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Daily", nullptr));
        comboBoxPeriod->setItemText(2, QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Weekly", nullptr));
        comboBoxPeriod->setItemText(3, QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Monthly", nullptr));
        comboBoxPeriod->setItemText(4, QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Yearly", nullptr));
        comboBoxPeriod->setItemText(5, QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Never", nullptr));

        labelCache->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Cache size limit", nullptr));
        pushButtonCheck->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsCacheDirectory", "Check Now", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsCacheDirectory: public Ui_DlgSettingsCacheDirectory {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSCACHEDIRECTORY_H
