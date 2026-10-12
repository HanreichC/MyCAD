/********************************************************************************
** Form generated from reading UI file 'DlgSettingsReportView.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSREPORTVIEW_H
#define UI_DLGSETTINGSREPORTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsReportView
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox1;
    QGridLayout *gridLayout;
    Gui::PrefCheckBox *checkMessage;
    Gui::PrefCheckBox *checkLogging;
    Gui::PrefCheckBox *checkWarning;
    Gui::PrefCheckBox *checkError;
    Gui::PrefCheckBox *checkShowReportViewOnError;
    Gui::PrefCheckBox *checkShowReportViewOnWarning;
    Gui::PrefCheckBox *checkShowReportViewOnNormalMessage;
    Gui::PrefCheckBox *checkShowReportViewOnLogMessage;
    Gui::PrefCheckBox *checkShowReportTimecode;
    QGroupBox *groupBox2;
    QGridLayout *gridLayout1;
    QGridLayout *gridLayout2;
    QLabel *textLabel1;
    QSpacerItem *spacerItem;
    Gui::PrefColorButton *colorText;
    QLabel *textLabel2;
    QSpacerItem *spacerItem1;
    Gui::PrefColorButton *colorLogging;
    QLabel *textLabel3;
    QSpacerItem *spacerItem2;
    Gui::PrefColorButton *colorWarning;
    QLabel *textLabel4;
    QSpacerItem *spacerItem3;
    Gui::PrefColorButton *colorError;
    QSpacerItem *spacerItem4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    Gui::PrefCheckBox *pythonOutput;
    Gui::PrefCheckBox *pythonError;
    QSpacerItem *spacerItem5;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsReportView)
    {
        if (Gui__Dialog__DlgSettingsReportView->objectName().isEmpty())
            Gui__Dialog__DlgSettingsReportView->setObjectName("Gui__Dialog__DlgSettingsReportView");
        Gui__Dialog__DlgSettingsReportView->resize(432, 500);
        gridLayout_3 = new QGridLayout(Gui__Dialog__DlgSettingsReportView);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox1 = new QGroupBox(Gui__Dialog__DlgSettingsReportView);
        groupBox1->setObjectName("groupBox1");
        gridLayout = new QGridLayout(groupBox1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(11, 11, 11, 11);
        checkMessage = new Gui::PrefCheckBox(groupBox1);
        checkMessage->setObjectName("checkMessage");
        checkMessage->setChecked(true);
        checkMessage->setProperty("prefEntry", QVariant(QByteArray("checkMessage")));
        checkMessage->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout->addWidget(checkMessage, 0, 0, 1, 1);

        checkLogging = new Gui::PrefCheckBox(groupBox1);
        checkLogging->setObjectName("checkLogging");
        checkLogging->setProperty("prefEntry", QVariant(QByteArray("checkLogging")));
        checkLogging->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout->addWidget(checkLogging, 1, 0, 1, 1);

        checkWarning = new Gui::PrefCheckBox(groupBox1);
        checkWarning->setObjectName("checkWarning");
        checkWarning->setChecked(true);
        checkWarning->setProperty("prefEntry", QVariant(QByteArray("checkWarning")));
        checkWarning->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout->addWidget(checkWarning, 2, 0, 1, 1);

        checkError = new Gui::PrefCheckBox(groupBox1);
        checkError->setObjectName("checkError");
        checkError->setChecked(true);
        checkError->setProperty("prefEntry", QVariant(QByteArray("checkError")));
        checkError->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout->addWidget(checkError, 3, 0, 1, 1);

        checkShowReportViewOnError = new Gui::PrefCheckBox(groupBox1);
        checkShowReportViewOnError->setObjectName("checkShowReportViewOnError");
        checkShowReportViewOnError->setChecked(false);
        checkShowReportViewOnError->setProperty("prefEntry", QVariant(QByteArray("checkShowReportViewOnError")));
        checkShowReportViewOnError->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout->addWidget(checkShowReportViewOnError, 4, 0, 1, 1);

        checkShowReportViewOnWarning = new Gui::PrefCheckBox(groupBox1);
        checkShowReportViewOnWarning->setObjectName("checkShowReportViewOnWarning");
        checkShowReportViewOnWarning->setProperty("prefEntry", QVariant(QByteArray("checkShowReportViewOnWarning")));
        checkShowReportViewOnWarning->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout->addWidget(checkShowReportViewOnWarning, 5, 0, 1, 1);

        checkShowReportViewOnNormalMessage = new Gui::PrefCheckBox(groupBox1);
        checkShowReportViewOnNormalMessage->setObjectName("checkShowReportViewOnNormalMessage");
        checkShowReportViewOnNormalMessage->setChecked(false);
        checkShowReportViewOnNormalMessage->setProperty("prefEntry", QVariant(QByteArray("checkShowReportViewOnNormalMessage")));
        checkShowReportViewOnNormalMessage->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout->addWidget(checkShowReportViewOnNormalMessage, 6, 0, 1, 1);

        checkShowReportViewOnLogMessage = new Gui::PrefCheckBox(groupBox1);
        checkShowReportViewOnLogMessage->setObjectName("checkShowReportViewOnLogMessage");
        checkShowReportViewOnLogMessage->setChecked(false);
        checkShowReportViewOnLogMessage->setProperty("prefEntry", QVariant(QByteArray("checkShowReportViewOnLogMessage")));
        checkShowReportViewOnLogMessage->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout->addWidget(checkShowReportViewOnLogMessage, 7, 0, 1, 1);

        checkShowReportTimecode = new Gui::PrefCheckBox(groupBox1);
        checkShowReportTimecode->setObjectName("checkShowReportTimecode");
        checkShowReportTimecode->setChecked(true);
        checkShowReportTimecode->setProperty("prefEntry", QVariant(QByteArray("checkShowReportTimecode")));
        checkShowReportTimecode->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout->addWidget(checkShowReportTimecode, 8, 0, 1, 1);


        gridLayout_3->addWidget(groupBox1, 0, 0, 1, 1);

        groupBox2 = new QGroupBox(Gui__Dialog__DlgSettingsReportView);
        groupBox2->setObjectName("groupBox2");
        gridLayout1 = new QGridLayout(groupBox2);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setObjectName("gridLayout2");
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        textLabel1 = new QLabel(groupBox2);
        textLabel1->setObjectName("textLabel1");

        gridLayout2->addWidget(textLabel1, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(214, 23, QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem, 0, 1, 1, 1);

        colorText = new Gui::PrefColorButton(groupBox2);
        colorText->setObjectName("colorText");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(colorText->sizePolicy().hasHeightForWidth());
        colorText->setSizePolicy(sizePolicy);
        colorText->setMinimumSize(QSize(75, 0));
        colorText->setColor(QColor(0, 0, 0));
        colorText->setProperty("prefEntry", QVariant(QByteArray("colorText")));
        colorText->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout2->addWidget(colorText, 0, 2, 1, 1);

        textLabel2 = new QLabel(groupBox2);
        textLabel2->setObjectName("textLabel2");

        gridLayout2->addWidget(textLabel2, 1, 0, 1, 1);

        spacerItem1 = new QSpacerItem(211, 23, QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem1, 1, 1, 1, 1);

        colorLogging = new Gui::PrefColorButton(groupBox2);
        colorLogging->setObjectName("colorLogging");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(colorLogging->sizePolicy().hasHeightForWidth());
        colorLogging->setSizePolicy(sizePolicy1);
        colorLogging->setMinimumSize(QSize(75, 0));
        colorLogging->setColor(QColor(0, 0, 255));
        colorLogging->setProperty("prefEntry", QVariant(QByteArray("colorLogging")));
        colorLogging->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout2->addWidget(colorLogging, 1, 2, 1, 1);

        textLabel3 = new QLabel(groupBox2);
        textLabel3->setObjectName("textLabel3");

        gridLayout2->addWidget(textLabel3, 2, 0, 1, 1);

        spacerItem2 = new QSpacerItem(211, 23, QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem2, 2, 1, 1, 1);

        colorWarning = new Gui::PrefColorButton(groupBox2);
        colorWarning->setObjectName("colorWarning");
        sizePolicy1.setHeightForWidth(colorWarning->sizePolicy().hasHeightForWidth());
        colorWarning->setSizePolicy(sizePolicy1);
        colorWarning->setMinimumSize(QSize(75, 0));
        colorWarning->setColor(QColor(255, 170, 0));
        colorWarning->setProperty("prefEntry", QVariant(QByteArray("colorWarning")));
        colorWarning->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout2->addWidget(colorWarning, 2, 2, 1, 1);

        textLabel4 = new QLabel(groupBox2);
        textLabel4->setObjectName("textLabel4");

        gridLayout2->addWidget(textLabel4, 3, 0, 1, 1);

        spacerItem3 = new QSpacerItem(211, 23, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem3, 3, 1, 1, 1);

        colorError = new Gui::PrefColorButton(groupBox2);
        colorError->setObjectName("colorError");
        sizePolicy1.setHeightForWidth(colorError->sizePolicy().hasHeightForWidth());
        colorError->setSizePolicy(sizePolicy1);
        colorError->setMinimumSize(QSize(75, 0));
        colorError->setColor(QColor(255, 0, 0));
        colorError->setProperty("prefEntry", QVariant(QByteArray("colorError")));
        colorError->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout2->addWidget(colorError, 3, 2, 1, 1);


        gridLayout1->addLayout(gridLayout2, 0, 0, 1, 1);

        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

        gridLayout1->addItem(spacerItem4, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox2, 1, 0, 1, 1);

        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsReportView);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        pythonOutput = new Gui::PrefCheckBox(groupBox);
        pythonOutput->setObjectName("pythonOutput");
        pythonOutput->setChecked(true);
        pythonOutput->setProperty("prefEntry", QVariant(QByteArray("RedirectPythonOutput")));
        pythonOutput->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout_2->addWidget(pythonOutput, 0, 0, 1, 1);

        pythonError = new Gui::PrefCheckBox(groupBox);
        pythonError->setObjectName("pythonError");
        pythonError->setChecked(true);
        pythonError->setProperty("prefEntry", QVariant(QByteArray("RedirectPythonErrors")));
        pythonError->setProperty("prefPath", QVariant(QByteArray("OutputWindow")));

        gridLayout_2->addWidget(pythonError, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 1);

        spacerItem5 = new QSpacerItem(410, 71, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(spacerItem5, 3, 0, 1, 1);

        QWidget::setTabOrder(checkLogging, checkWarning);
        QWidget::setTabOrder(checkWarning, checkError);
        QWidget::setTabOrder(checkError, checkShowReportViewOnWarning);
        QWidget::setTabOrder(checkShowReportViewOnWarning, checkShowReportViewOnError);
        QWidget::setTabOrder(checkShowReportViewOnError, checkShowReportViewOnNormalMessage);
        QWidget::setTabOrder(checkShowReportViewOnNormalMessage, checkShowReportViewOnLogMessage);
        QWidget::setTabOrder(checkShowReportViewOnLogMessage, checkShowReportTimecode);
        QWidget::setTabOrder(checkShowReportTimecode, colorText);
        QWidget::setTabOrder(colorText, colorLogging);
        QWidget::setTabOrder(colorLogging, colorWarning);
        QWidget::setTabOrder(colorWarning, colorError);
        QWidget::setTabOrder(colorError, pythonOutput);
        QWidget::setTabOrder(pythonOutput, pythonError);

        retranslateUi(Gui__Dialog__DlgSettingsReportView);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsReportView);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsReportView)
    {
        Gui__Dialog__DlgSettingsReportView->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Report View", nullptr));
        groupBox1->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Output", nullptr));
#if QT_CONFIG(tooltip)
        checkMessage->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Normal messages will be recorded", nullptr));
#endif // QT_CONFIG(tooltip)
        checkMessage->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Record normal messages", nullptr));
#if QT_CONFIG(tooltip)
        checkLogging->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Log messages will be recorded", nullptr));
#endif // QT_CONFIG(tooltip)
        checkLogging->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Record log messages", nullptr));
#if QT_CONFIG(tooltip)
        checkWarning->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Warnings will be recorded", nullptr));
#endif // QT_CONFIG(tooltip)
        checkWarning->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Record warnings", nullptr));
#if QT_CONFIG(tooltip)
        checkError->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Error messages will be recorded", nullptr));
#endif // QT_CONFIG(tooltip)
        checkError->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Record error messages", nullptr));
#if QT_CONFIG(tooltip)
        checkShowReportViewOnError->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "When an error has occurred, the Report View dialog becomes visible\n"
"on-screen while displaying the error", nullptr));
#endif // QT_CONFIG(tooltip)
        checkShowReportViewOnError->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Show report view on error", nullptr));
#if QT_CONFIG(tooltip)
        checkShowReportViewOnWarning->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "When a warning has occurred, the Report View dialog becomes visible\n"
"on-screen while displaying the warning", nullptr));
#endif // QT_CONFIG(tooltip)
        checkShowReportViewOnWarning->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Show report view on warning", nullptr));
#if QT_CONFIG(tooltip)
        checkShowReportViewOnNormalMessage->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "When a normal message has occurred, the Report View dialog becomes visible\n"
"on-screen while displaying the message", nullptr));
#endif // QT_CONFIG(tooltip)
        checkShowReportViewOnNormalMessage->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Show report view on normal message", nullptr));
#if QT_CONFIG(tooltip)
        checkShowReportViewOnLogMessage->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "When a log message has occurred, the Report View dialog becomes visible\n"
"on-screen while displaying the log message", nullptr));
#endif // QT_CONFIG(tooltip)
        checkShowReportViewOnLogMessage->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Show report view on log message", nullptr));
#if QT_CONFIG(tooltip)
        checkShowReportTimecode->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Include a timecode for each report", nullptr));
#endif // QT_CONFIG(tooltip)
        checkShowReportTimecode->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Include a timecode for each entry", nullptr));
        groupBox2->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Colors", nullptr));
        textLabel1->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Normal messages", nullptr));
#if QT_CONFIG(tooltip)
        colorText->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Font color for normal messages in Report view panel", nullptr));
#endif // QT_CONFIG(tooltip)
        colorText->setText(QString());
        textLabel2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Log messages", nullptr));
#if QT_CONFIG(tooltip)
        colorLogging->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Font color for log messages in Report view panel", nullptr));
#endif // QT_CONFIG(tooltip)
        colorLogging->setText(QString());
        textLabel3->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Warnings", nullptr));
#if QT_CONFIG(tooltip)
        colorWarning->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Font color for warning messages in Report view panel", nullptr));
#endif // QT_CONFIG(tooltip)
        colorWarning->setText(QString());
        textLabel4->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Errors", nullptr));
#if QT_CONFIG(tooltip)
        colorError->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Font color for error messages in Report view panel", nullptr));
#endif // QT_CONFIG(tooltip)
        colorError->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Python Interpreter", nullptr));
#if QT_CONFIG(tooltip)
        pythonOutput->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Internal Python output will be redirected\n"
"from Python console to Report view panel", nullptr));
#endif // QT_CONFIG(tooltip)
        pythonOutput->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Redirect internal Python output to report view", nullptr));
#if QT_CONFIG(tooltip)
        pythonError->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Internal Python error messages will be redirected\n"
"from Python console to Report view panel", nullptr));
#endif // QT_CONFIG(tooltip)
        pythonError->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsReportView", "Redirect internal Python errors to report view", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsReportView: public Ui_DlgSettingsReportView {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSREPORTVIEW_H
