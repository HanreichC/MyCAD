/********************************************************************************
** Form generated from reading UI file 'DemoMode.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMOMODE_H
#define UI_DEMOMODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

namespace Gui {
namespace Dialog {

class Ui_DemoMode
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout2;
    QLabel *label_3;
    QSlider *angleSlider;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout3;
    QLabel *label;
    QSlider *speedSlider;
    QLabel *label_2;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout;
    QCheckBox *fullscreen;
    QCheckBox *timerCheck;
    QSpinBox *timeout;
    QHBoxLayout *hboxLayout1;
    QPushButton *playButton;
    QSpacerItem *spacerItem1;
    QPushButton *okButton;

    void setupUi(QDialog *Gui__Dialog__DemoMode)
    {
        if (Gui__Dialog__DemoMode->objectName().isEmpty())
            Gui__Dialog__DemoMode->setObjectName("Gui__Dialog__DemoMode");
        Gui__Dialog__DemoMode->resize(269, 267);
        gridLayout = new QGridLayout(Gui__Dialog__DemoMode);
#ifndef Q_OS_MACOS
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(Gui__Dialog__DemoMode);
        groupBox->setObjectName("groupBox");
        gridLayout1 = new QGridLayout(groupBox);
#ifndef Q_OS_MACOS
        gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        gridLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout1->setObjectName("gridLayout1");
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout2 = new QGridLayout(groupBox_3);
#ifndef Q_OS_MACOS
        gridLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        gridLayout2->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout2->setObjectName("gridLayout2");
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");
        label_3->setText(QString::fromUtf8("-90\302\260"));

        gridLayout2->addWidget(label_3, 0, 0, 1, 1);

        angleSlider = new QSlider(groupBox_3);
        angleSlider->setObjectName("angleSlider");
        angleSlider->setMinimum(-90);
        angleSlider->setMaximum(90);
        angleSlider->setOrientation(Qt::Horizontal);

        gridLayout2->addWidget(angleSlider, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");
        label_4->setText(QString::fromUtf8("90\302\260"));

        gridLayout2->addWidget(label_4, 0, 2, 1, 1);


        gridLayout1->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout3 = new QGridLayout(groupBox_2);
#ifndef Q_OS_MACOS
        gridLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        gridLayout3->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout3->setObjectName("gridLayout3");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        gridLayout3->addWidget(label, 0, 0, 1, 1);

        speedSlider = new QSlider(groupBox_2);
        speedSlider->setObjectName("speedSlider");
        speedSlider->setMinimum(1);
        speedSlider->setMaximum(100);
        speedSlider->setValue(5);
        speedSlider->setOrientation(Qt::Horizontal);

        gridLayout3->addWidget(speedSlider, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        gridLayout3->addWidget(label_2, 0, 2, 1, 1);


        gridLayout1->addWidget(groupBox_2, 1, 0, 1, 1);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout1->addItem(spacerItem, 2, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MACOS
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName("hboxLayout");
        fullscreen = new QCheckBox(groupBox);
        fullscreen->setObjectName("fullscreen");

        hboxLayout->addWidget(fullscreen);

        timerCheck = new QCheckBox(groupBox);
        timerCheck->setObjectName("timerCheck");

        hboxLayout->addWidget(timerCheck);

        timeout = new QSpinBox(groupBox);
        timeout->setObjectName("timeout");
        timeout->setEnabled(false);
        timeout->setMaximum(600);
        timeout->setValue(30);

        hboxLayout->addWidget(timeout);


        gridLayout1->addLayout(hboxLayout, 3, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MACOS
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName("hboxLayout1");
        playButton = new QPushButton(Gui__Dialog__DemoMode);
        playButton->setObjectName("playButton");

        hboxLayout1->addWidget(playButton);

        spacerItem1 = new QSpacerItem(81, 31, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout1->addItem(spacerItem1);

        okButton = new QPushButton(Gui__Dialog__DemoMode);
        okButton->setObjectName("okButton");

        hboxLayout1->addWidget(okButton);


        gridLayout->addLayout(hboxLayout1, 1, 0, 1, 1);

        QWidget::setTabOrder(angleSlider, speedSlider);
        QWidget::setTabOrder(speedSlider, fullscreen);
        QWidget::setTabOrder(fullscreen, timerCheck);
        QWidget::setTabOrder(timerCheck, playButton);
        QWidget::setTabOrder(playButton, okButton);

        retranslateUi(Gui__Dialog__DemoMode);
        QObject::connect(okButton, &QPushButton::clicked, Gui__Dialog__DemoMode, qOverload<>(&QDialog::accept));
        QObject::connect(timerCheck, &QCheckBox::toggled, timeout, &QSpinBox::setEnabled);

        QMetaObject::connectSlotsByName(Gui__Dialog__DemoMode);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DemoMode)
    {
        Gui__Dialog__DemoMode->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DemoMode", "View Turntable", nullptr));
        groupBox->setTitle(QString());
        groupBox_3->setTitle(QCoreApplication::translate("Gui::Dialog::DemoMode", "Angle", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Gui::Dialog::DemoMode", "Speed", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DemoMode", "Minimum", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DemoMode", "Maximum", nullptr));
        fullscreen->setText(QCoreApplication::translate("Gui::Dialog::DemoMode", "Fullscreen", nullptr));
        timerCheck->setText(QCoreApplication::translate("Gui::Dialog::DemoMode", "Enable timer", nullptr));
        timeout->setSuffix(QCoreApplication::translate("Gui::Dialog::DemoMode", " s", nullptr));
        playButton->setText(QCoreApplication::translate("Gui::Dialog::DemoMode", "Play", nullptr));
        okButton->setText(QCoreApplication::translate("Gui::Dialog::DemoMode", "Close", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DemoMode: public Ui_DemoMode {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DEMOMODE_H
