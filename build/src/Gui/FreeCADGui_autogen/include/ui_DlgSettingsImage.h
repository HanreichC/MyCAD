/********************************************************************************
** Form generated from reading UI file 'DlgSettingsImage.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSIMAGE_H
#define UI_DLGSETTINGSIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsImage
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBoxDim;
    QGridLayout *gridLayout1;
    QGridLayout *gridLayout2;
    QLabel *label;
    QComboBox *standardSizeBox;
    QLabel *textLabelWidth;
    QSpinBox *spinWidth;
    QLabel *label_2;
    QLabel *textLabelHeight;
    QSpinBox *spinHeight;
    QLabel *label_3;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel1;
    QToolButton *buttonRatioScreen;
    QToolButton *buttonRatio4x3;
    QToolButton *buttonRatio16x9;
    QToolButton *buttonRatio1x1;
    QGroupBox *groupBoxProp;
    QGridLayout *gridLayout3;
    QLabel *textLabelColor;
    QComboBox *comboBackground;
    QLabel *label_4;
    QComboBox *comboMethod;
    QGroupBox *buttonGroupComment;
    QGridLayout *gridLayout4;
    QRadioButton *radioButtonMiba;
    QRadioButton *radioButtonComment;
    QTextEdit *textEditComment;
    QCheckBox *checkWatermark;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsImage)
    {
        if (Gui__Dialog__DlgSettingsImage->objectName().isEmpty())
            Gui__Dialog__DlgSettingsImage->setObjectName("Gui__Dialog__DlgSettingsImage");
        Gui__Dialog__DlgSettingsImage->resize(291, 498);
        gridLayout = new QGridLayout(Gui__Dialog__DlgSettingsImage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(9, 9, 9, 9);
        groupBoxDim = new QGroupBox(Gui__Dialog__DlgSettingsImage);
        groupBoxDim->setObjectName("groupBoxDim");
        gridLayout1 = new QGridLayout(groupBoxDim);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setObjectName("gridLayout2");
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(groupBoxDim);
        label->setObjectName("label");

        gridLayout2->addWidget(label, 0, 0, 1, 1);

        standardSizeBox = new QComboBox(groupBoxDim);
        standardSizeBox->addItem(QString());
        standardSizeBox->addItem(QString());
        standardSizeBox->addItem(QString());
        standardSizeBox->addItem(QString());
        standardSizeBox->addItem(QString::fromUtf8("CGA       320 x 200"));
        standardSizeBox->addItem(QString::fromUtf8("QVGA     320 x 240"));
        standardSizeBox->addItem(QString::fromUtf8("VGA       640 x 480"));
        standardSizeBox->addItem(QString::fromUtf8("NTSC     720 x 480"));
        standardSizeBox->addItem(QString::fromUtf8("PAL        768 x 578"));
        standardSizeBox->addItem(QString::fromUtf8("SVGA     800 x 600"));
        standardSizeBox->addItem(QString::fromUtf8("XGA       1024 x 768"));
        standardSizeBox->addItem(QString::fromUtf8("HD720   1280 x 720"));
        standardSizeBox->addItem(QString::fromUtf8("SXGA     1280 x 1024"));
        standardSizeBox->addItem(QString::fromUtf8("SXGA+   1400 x 1050"));
        standardSizeBox->addItem(QString::fromUtf8("UXGA     1600 x 1200"));
        standardSizeBox->addItem(QString::fromUtf8("HD1080 1920 x 1080"));
        standardSizeBox->addItem(QString::fromUtf8("WUXGA  1920 x 1200"));
        standardSizeBox->addItem(QString::fromUtf8("QXGA     2048 x 1538"));
        standardSizeBox->addItem(QString::fromUtf8("WQXGA  2560 x 1600"));
        standardSizeBox->addItem(QString::fromUtf8("QSXGA   2560 x 2048"));
        standardSizeBox->addItem(QString::fromUtf8("QUXGA   3200 \303\227 2400"));
        standardSizeBox->addItem(QString::fromUtf8("HUXGA   6400 \303\227 4800"));
        standardSizeBox->addItem(QString::fromUtf8("!!!          10000 x 10000"));
        standardSizeBox->setObjectName("standardSizeBox");

        gridLayout2->addWidget(standardSizeBox, 0, 1, 1, 2);

        textLabelWidth = new QLabel(groupBoxDim);
        textLabelWidth->setObjectName("textLabelWidth");

        gridLayout2->addWidget(textLabelWidth, 1, 0, 1, 1);

        spinWidth = new QSpinBox(groupBoxDim);
        spinWidth->setObjectName("spinWidth");
        spinWidth->setMinimum(1);
        spinWidth->setMaximum(32767);

        gridLayout2->addWidget(spinWidth, 1, 1, 1, 1);

        label_2 = new QLabel(groupBoxDim);
        label_2->setObjectName("label_2");

        gridLayout2->addWidget(label_2, 1, 2, 1, 1);

        textLabelHeight = new QLabel(groupBoxDim);
        textLabelHeight->setObjectName("textLabelHeight");

        gridLayout2->addWidget(textLabelHeight, 2, 0, 1, 1);

        spinHeight = new QSpinBox(groupBoxDim);
        spinHeight->setObjectName("spinHeight");
        spinHeight->setMinimum(1);
        spinHeight->setMaximum(32767);

        gridLayout2->addWidget(spinHeight, 2, 1, 1, 1);

        label_3 = new QLabel(groupBoxDim);
        label_3->setObjectName("label_3");

        gridLayout2->addWidget(label_3, 2, 2, 1, 1);


        gridLayout1->addLayout(gridLayout2, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        textLabel1 = new QLabel(groupBoxDim);
        textLabel1->setObjectName("textLabel1");

        hboxLayout->addWidget(textLabel1);

        buttonRatioScreen = new QToolButton(groupBoxDim);
        buttonRatioScreen->setObjectName("buttonRatioScreen");

        hboxLayout->addWidget(buttonRatioScreen);

        buttonRatio4x3 = new QToolButton(groupBoxDim);
        buttonRatio4x3->setObjectName("buttonRatio4x3");

        hboxLayout->addWidget(buttonRatio4x3);

        buttonRatio16x9 = new QToolButton(groupBoxDim);
        buttonRatio16x9->setObjectName("buttonRatio16x9");

        hboxLayout->addWidget(buttonRatio16x9);

        buttonRatio1x1 = new QToolButton(groupBoxDim);
        buttonRatio1x1->setObjectName("buttonRatio1x1");

        hboxLayout->addWidget(buttonRatio1x1);


        gridLayout1->addLayout(hboxLayout, 1, 0, 1, 1);


        gridLayout->addWidget(groupBoxDim, 0, 0, 1, 1);

        groupBoxProp = new QGroupBox(Gui__Dialog__DlgSettingsImage);
        groupBoxProp->setObjectName("groupBoxProp");
        gridLayout3 = new QGridLayout(groupBoxProp);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName("gridLayout3");
        gridLayout3->setContentsMargins(9, 9, 9, 9);
        textLabelColor = new QLabel(groupBoxProp);
        textLabelColor->setObjectName("textLabelColor");

        gridLayout3->addWidget(textLabelColor, 0, 0, 1, 1);

        comboBackground = new QComboBox(groupBoxProp);
        comboBackground->addItem(QString());
        comboBackground->addItem(QString());
        comboBackground->addItem(QString());
        comboBackground->addItem(QString());
        comboBackground->setObjectName("comboBackground");

        gridLayout3->addWidget(comboBackground, 0, 1, 1, 1);

        label_4 = new QLabel(groupBoxProp);
        label_4->setObjectName("label_4");

        gridLayout3->addWidget(label_4, 1, 0, 1, 1);

        comboMethod = new QComboBox(groupBoxProp);
        comboMethod->setObjectName("comboMethod");

        gridLayout3->addWidget(comboMethod, 1, 1, 1, 1);


        gridLayout->addWidget(groupBoxProp, 1, 0, 1, 1);

        buttonGroupComment = new QGroupBox(Gui__Dialog__DlgSettingsImage);
        buttonGroupComment->setObjectName("buttonGroupComment");
        buttonGroupComment->setEnabled(false);
        gridLayout4 = new QGridLayout(buttonGroupComment);
        gridLayout4->setSpacing(6);
        gridLayout4->setContentsMargins(11, 11, 11, 11);
        gridLayout4->setObjectName("gridLayout4");
        gridLayout4->setContentsMargins(9, 9, 9, 9);
        radioButtonMiba = new QRadioButton(buttonGroupComment);
        radioButtonMiba->setObjectName("radioButtonMiba");
        radioButtonMiba->setChecked(true);

        gridLayout4->addWidget(radioButtonMiba, 0, 0, 1, 1);

        radioButtonComment = new QRadioButton(buttonGroupComment);
        radioButtonComment->setObjectName("radioButtonComment");

        gridLayout4->addWidget(radioButtonComment, 1, 0, 1, 1);

        textEditComment = new QTextEdit(buttonGroupComment);
        textEditComment->setObjectName("textEditComment");
        textEditComment->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEditComment->sizePolicy().hasHeightForWidth());
        textEditComment->setSizePolicy(sizePolicy);
        textEditComment->setMinimumSize(QSize(0, 70));

        gridLayout4->addWidget(textEditComment, 2, 0, 1, 1);

        checkWatermark = new QCheckBox(buttonGroupComment);
        checkWatermark->setObjectName("checkWatermark");

        gridLayout4->addWidget(checkWatermark, 3, 0, 1, 1);


        gridLayout->addWidget(buttonGroupComment, 2, 0, 1, 1);

#if QT_CONFIG(shortcut)
        textLabelWidth->setBuddy(spinWidth);
        textLabelHeight->setBuddy(spinHeight);
        textLabelColor->setBuddy(comboBackground);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(standardSizeBox, spinWidth);
        QWidget::setTabOrder(spinWidth, spinHeight);
        QWidget::setTabOrder(spinHeight, buttonRatioScreen);
        QWidget::setTabOrder(buttonRatioScreen, buttonRatio4x3);
        QWidget::setTabOrder(buttonRatio4x3, buttonRatio16x9);
        QWidget::setTabOrder(buttonRatio16x9, buttonRatio1x1);
        QWidget::setTabOrder(buttonRatio1x1, comboBackground);
        QWidget::setTabOrder(comboBackground, comboMethod);
        QWidget::setTabOrder(comboMethod, radioButtonMiba);
        QWidget::setTabOrder(radioButtonMiba, radioButtonComment);
        QWidget::setTabOrder(radioButtonComment, textEditComment);

        retranslateUi(Gui__Dialog__DlgSettingsImage);
        QObject::connect(radioButtonComment, &QRadioButton::toggled, textEditComment, &QTextEdit::setEnabled);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsImage);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsImage)
    {
        Gui__Dialog__DlgSettingsImage->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Image Settings", nullptr));
        groupBoxDim->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Image Dimensions", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Standard sizes", nullptr));
        standardSizeBox->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Current screen", nullptr));
        standardSizeBox->setItemText(1, QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Icon       32  x 32", nullptr));
        standardSizeBox->setItemText(2, QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Icon       64 x 64", nullptr));
        standardSizeBox->setItemText(3, QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Icon       128 x 128", nullptr));

        textLabelWidth->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "&Width", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Pixel", nullptr));
        textLabelHeight->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "&Height", nullptr));
        label_3->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Pixel", nullptr));
        textLabel1->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Aspect ratio", nullptr));
        buttonRatioScreen->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "&Screen", nullptr));
#if QT_CONFIG(shortcut)
        buttonRatioScreen->setShortcut(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Alt+S", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonRatio4x3->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "&4:3", nullptr));
#if QT_CONFIG(shortcut)
        buttonRatio4x3->setShortcut(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Alt+4", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonRatio16x9->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "1&6:9", nullptr));
#if QT_CONFIG(shortcut)
        buttonRatio16x9->setShortcut(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Alt+6", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonRatio1x1->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "&1:1", nullptr));
#if QT_CONFIG(shortcut)
        buttonRatio1x1->setShortcut(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Alt+1", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBoxProp->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Image Properties", nullptr));
        textLabelColor->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Back&ground", nullptr));
        comboBackground->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Current", nullptr));
        comboBackground->setItemText(1, QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "White", nullptr));
        comboBackground->setItemText(2, QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Black", nullptr));
        comboBackground->setItemText(3, QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Transparent", nullptr));

        label_4->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Creation method", nullptr));
        buttonGroupComment->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Image Comment", nullptr));
        radioButtonMiba->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Insert MIBA", nullptr));
        radioButtonComment->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Insert comment", nullptr));
        checkWatermark->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsImage", "Add watermark", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsImage: public Ui_DlgSettingsImage {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSIMAGE_H
