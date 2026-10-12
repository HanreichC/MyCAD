/********************************************************************************
** Form generated from reading UI file 'DlgSettingsDocument.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSDOCUMENT_H
#define UI_DLGSETTINGSDOCUMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsDocument
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *GroupBox5;
    QGridLayout *gridLayout_4;
    QFrame *line;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel1_2;
    Gui::PrefSpinBox *prefUndoRedoSize;
    QFrame *line1;
    Gui::PrefCheckBox *prefEnableAsyncRecompute;
    Gui::PrefCheckBox *prefCanAbortRecompute;
    QFrame *line1_2;
    Gui::PrefCheckBox *prefCheckNewDoc;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel1;
    Gui::PrefSpinBox *prefCompression;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *FormatTimeDocsLabel;
    Gui::PrefCheckBox *prefDiscardTransaction;
    QFrame *line1_2_3;
    QHBoxLayout *horizontalLayout_3;
    Gui::PrefCheckBox *prefSaveThumbnail;
    QSpacerItem *spacerItem;
    QLabel *label_6;
    Gui::PrefSpinBox *prefThumbnailSize;
    QHBoxLayout *hboxLayout2;
    Gui::PrefCheckBox *prefSaveBackupFiles;
    QSpacerItem *spacerItem1;
    Gui::PrefSpinBox *prefCountBackupFiles;
    Gui::PrefCheckBox *prefRecovery;
    Gui::PrefCheckBox *prefSaveTransaction;
    Gui::PrefCheckBox *prefAddLogo;
    QHBoxLayout *horizontalLayout;
    Gui::PrefCheckBox *prefAutoSaveEnabled;
    Gui::PrefSpinBox *prefAutoSaveTimeout;
    QHBoxLayout *hboxLayout3;
    Gui::PrefCheckBox *prefSaveBackupExtension;
    QLabel *label_5;
    Gui::PrefLineEdit *prefSaveBackupDateFormat;
    Gui::PrefCheckBox *prefDisableVersionCheckOnSave;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    Gui::PrefCheckBox *prefDuplicateLabel;
    Gui::PrefCheckBox *prefPartialLoading;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QLabel *label_3;
    Gui::PrefLineEdit *prefAuthor;
    Gui::PrefCheckBox *prefSetAuthorOnSave;
    QLabel *label_4;
    Gui::PrefLineEdit *prefCompany;
    QLabel *label;
    Gui::PrefComboBox *prefLicenseType;
    QLabel *label_2;
    Gui::PrefLineEdit *prefLicenseUrl;
    QSpacerItem *spacerItem2;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsDocument)
    {
        if (Gui__Dialog__DlgSettingsDocument->objectName().isEmpty())
            Gui__Dialog__DlgSettingsDocument->setObjectName("Gui__Dialog__DlgSettingsDocument");
        Gui__Dialog__DlgSettingsDocument->resize(607, 871);
        gridLayout_3 = new QGridLayout(Gui__Dialog__DlgSettingsDocument);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        GroupBox5 = new QGroupBox(Gui__Dialog__DlgSettingsDocument);
        GroupBox5->setObjectName("GroupBox5");
        gridLayout_4 = new QGridLayout(GroupBox5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(9, 9, 9, 9);
        line = new QFrame(GroupBox5);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_4->addWidget(line, 5, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        textLabel1_2 = new QLabel(GroupBox5);
        textLabel1_2->setObjectName("textLabel1_2");

        hboxLayout->addWidget(textLabel1_2);

        prefUndoRedoSize = new Gui::PrefSpinBox(GroupBox5);
        prefUndoRedoSize->setObjectName("prefUndoRedoSize");
        prefUndoRedoSize->setValue(20);
        prefUndoRedoSize->setProperty("prefEntry", QVariant(QByteArray("MaxUndoSize")));
        prefUndoRedoSize->setProperty("prefPath", QVariant(QByteArray("Document")));

        hboxLayout->addWidget(prefUndoRedoSize);


        gridLayout_4->addLayout(hboxLayout, 4, 0, 1, 1);

        line1 = new QFrame(GroupBox5);
        line1->setObjectName("line1");
        line1->setFrameShape(QFrame::Shape::HLine);
        line1->setFrameShadow(QFrame::Shadow::Sunken);
        line1->setFrameShape(QFrame::Shape::HLine);

        gridLayout_4->addWidget(line1, 1, 0, 1, 1);

        prefEnableAsyncRecompute = new Gui::PrefCheckBox(GroupBox5);
        prefEnableAsyncRecompute->setObjectName("prefEnableAsyncRecompute");
        prefEnableAsyncRecompute->setChecked(true);
        prefEnableAsyncRecompute->setProperty("prefEntry", QVariant(QByteArray("EnableAsyncRecompute")));
        prefEnableAsyncRecompute->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_4->addWidget(prefEnableAsyncRecompute, 7, 0, 1, 1);

        prefCanAbortRecompute = new Gui::PrefCheckBox(GroupBox5);
        prefCanAbortRecompute->setObjectName("prefCanAbortRecompute");
        prefCanAbortRecompute->setProperty("prefEntry", QVariant(QByteArray("CanAbortRecompute")));
        prefCanAbortRecompute->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_4->addWidget(prefCanAbortRecompute, 6, 0, 1, 1);

        line1_2 = new QFrame(GroupBox5);
        line1_2->setObjectName("line1_2");
        line1_2->setFrameShape(QFrame::Shape::HLine);
        line1_2->setFrameShadow(QFrame::Shadow::Sunken);
        line1_2->setFrameShape(QFrame::Shape::HLine);

        gridLayout_4->addWidget(line1_2, 3, 0, 1, 1);

        prefCheckNewDoc = new Gui::PrefCheckBox(GroupBox5);
        prefCheckNewDoc->setObjectName("prefCheckNewDoc");
        prefCheckNewDoc->setChecked(false);
        prefCheckNewDoc->setProperty("prefEntry", QVariant(QByteArray("CreateNewDoc")));
        prefCheckNewDoc->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_4->addWidget(prefCheckNewDoc, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName("hboxLayout1");
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        textLabel1 = new QLabel(GroupBox5);
        textLabel1->setObjectName("textLabel1");

        hboxLayout1->addWidget(textLabel1);

        prefCompression = new Gui::PrefSpinBox(GroupBox5);
        prefCompression->setObjectName("prefCompression");
        prefCompression->setValue(7);
        prefCompression->setProperty("prefEntry", QVariant(QByteArray("CompressionLevel")));
        prefCompression->setProperty("prefPath", QVariant(QByteArray("Document")));

        hboxLayout1->addWidget(prefCompression);


        gridLayout_4->addLayout(hboxLayout1, 2, 0, 1, 1);


        gridLayout_3->addWidget(GroupBox5, 0, 0, 1, 1);

        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsDocument);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        FormatTimeDocsLabel = new QLabel(groupBox);
        FormatTimeDocsLabel->setObjectName("FormatTimeDocsLabel");
        QFont font;
        font.setItalic(true);
        FormatTimeDocsLabel->setFont(font);
        FormatTimeDocsLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        FormatTimeDocsLabel->setOpenExternalLinks(true);

        gridLayout_2->addWidget(FormatTimeDocsLabel, 9, 0, 1, 1);

        prefDiscardTransaction = new Gui::PrefCheckBox(groupBox);
        prefDiscardTransaction->setObjectName("prefDiscardTransaction");
        prefDiscardTransaction->setEnabled(false);
        prefDiscardTransaction->setProperty("prefEntry", QVariant(QByteArray("TransactionsDiscard")));
        prefDiscardTransaction->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_2->addWidget(prefDiscardTransaction, 1, 0, 1, 1);

        line1_2_3 = new QFrame(groupBox);
        line1_2_3->setObjectName("line1_2_3");
        line1_2_3->setFrameShape(QFrame::Shape::HLine);
        line1_2_3->setFrameShadow(QFrame::Shadow::Sunken);
        line1_2_3->setFrameShape(QFrame::Shape::HLine);

        gridLayout_2->addWidget(line1_2_3, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, -1, -1);
        prefSaveThumbnail = new Gui::PrefCheckBox(groupBox);
        prefSaveThumbnail->setObjectName("prefSaveThumbnail");
        prefSaveThumbnail->setChecked(true);
        prefSaveThumbnail->setProperty("prefEntry", QVariant(QByteArray("SaveThumbnail")));
        prefSaveThumbnail->setProperty("prefPath", QVariant(QByteArray("Document")));

        horizontalLayout_3->addWidget(prefSaveThumbnail);

        spacerItem = new QSpacerItem(91, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(spacerItem);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        horizontalLayout_3->addWidget(label_6);

        prefThumbnailSize = new Gui::PrefSpinBox(groupBox);
        prefThumbnailSize->setObjectName("prefThumbnailSize");
        prefThumbnailSize->setMinimum(64);
        prefThumbnailSize->setMaximum(512);
        prefThumbnailSize->setValue(256);
        prefThumbnailSize->setProperty("prefEntry", QVariant(QByteArray("ThumbnailSize")));
        prefThumbnailSize->setProperty("prefPath", QVariant(QByteArray("Document")));

        horizontalLayout_3->addWidget(prefThumbnailSize);


        gridLayout_2->addLayout(horizontalLayout_3, 5, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName("hboxLayout2");
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        prefSaveBackupFiles = new Gui::PrefCheckBox(groupBox);
        prefSaveBackupFiles->setObjectName("prefSaveBackupFiles");
        prefSaveBackupFiles->setChecked(true);
        prefSaveBackupFiles->setProperty("prefEntry", QVariant(QByteArray("CreateBackupFiles")));
        prefSaveBackupFiles->setProperty("prefPath", QVariant(QByteArray("Document")));

        hboxLayout2->addWidget(prefSaveBackupFiles);

        spacerItem1 = new QSpacerItem(91, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem1);

        prefCountBackupFiles = new Gui::PrefSpinBox(groupBox);
        prefCountBackupFiles->setObjectName("prefCountBackupFiles");
        prefCountBackupFiles->setMinimum(1);
        prefCountBackupFiles->setProperty("prefEntry", QVariant(QByteArray("CountBackupFiles")));
        prefCountBackupFiles->setProperty("prefPath", QVariant(QByteArray("Document")));

        hboxLayout2->addWidget(prefCountBackupFiles);


        gridLayout_2->addLayout(hboxLayout2, 7, 0, 1, 1);

        prefRecovery = new Gui::PrefCheckBox(groupBox);
        prefRecovery->setObjectName("prefRecovery");
        prefRecovery->setChecked(true);
        prefRecovery->setProperty("prefEntry", QVariant(QByteArray("RecoveryEnabled")));
        prefRecovery->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_2->addWidget(prefRecovery, 2, 0, 1, 1);

        prefSaveTransaction = new Gui::PrefCheckBox(groupBox);
        prefSaveTransaction->setObjectName("prefSaveTransaction");
        prefSaveTransaction->setEnabled(false);
        prefSaveTransaction->setProperty("prefEntry", QVariant(QByteArray("SaveTransactions")));
        prefSaveTransaction->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_2->addWidget(prefSaveTransaction, 0, 0, 1, 1);

        prefAddLogo = new Gui::PrefCheckBox(groupBox);
        prefAddLogo->setObjectName("prefAddLogo");
        prefAddLogo->setChecked(false);
        prefAddLogo->setProperty("prefEntry", QVariant(QByteArray("AddThumbnailLogo")));
        prefAddLogo->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_2->addWidget(prefAddLogo, 6, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        prefAutoSaveEnabled = new Gui::PrefCheckBox(groupBox);
        prefAutoSaveEnabled->setObjectName("prefAutoSaveEnabled");
        prefAutoSaveEnabled->setChecked(true);
        prefAutoSaveEnabled->setProperty("prefEntry", QVariant(QByteArray("AutoSaveEnabled")));
        prefAutoSaveEnabled->setProperty("prefPath", QVariant(QByteArray("Document")));

        horizontalLayout->addWidget(prefAutoSaveEnabled);

        prefAutoSaveTimeout = new Gui::PrefSpinBox(groupBox);
        prefAutoSaveTimeout->setObjectName("prefAutoSaveTimeout");
        prefAutoSaveTimeout->setSuffix(QString::fromUtf8(" min"));
        prefAutoSaveTimeout->setMinimum(1);
        prefAutoSaveTimeout->setMaximum(60);
        prefAutoSaveTimeout->setValue(15);
        prefAutoSaveTimeout->setProperty("prefEntry", QVariant(QByteArray("AutoSaveTimeout")));
        prefAutoSaveTimeout->setProperty("prefPath", QVariant(QByteArray("Document")));

        horizontalLayout->addWidget(prefAutoSaveTimeout);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName("hboxLayout3");
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        prefSaveBackupExtension = new Gui::PrefCheckBox(groupBox);
        prefSaveBackupExtension->setObjectName("prefSaveBackupExtension");
        prefSaveBackupExtension->setChecked(true);
        prefSaveBackupExtension->setProperty("prefEntry", QVariant(QByteArray("UseFCBakExtension")));
        prefSaveBackupExtension->setProperty("prefPath", QVariant(QByteArray("Document")));

        hboxLayout3->addWidget(prefSaveBackupExtension);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        hboxLayout3->addWidget(label_5);

        prefSaveBackupDateFormat = new Gui::PrefLineEdit(groupBox);
        prefSaveBackupDateFormat->setObjectName("prefSaveBackupDateFormat");
        prefSaveBackupDateFormat->setText(QString::fromUtf8("%Y%m%d-%H%M%S"));
        prefSaveBackupDateFormat->setProperty("prefEntry", QVariant(QByteArray("SaveBackupDateFormat")));
        prefSaveBackupDateFormat->setProperty("prefPath", QVariant(QByteArray("Document")));

        hboxLayout3->addWidget(prefSaveBackupDateFormat);


        gridLayout_2->addLayout(hboxLayout3, 8, 0, 1, 1);

        prefDisableVersionCheckOnSave = new Gui::PrefCheckBox(groupBox);
        prefDisableVersionCheckOnSave->setObjectName("prefDisableVersionCheckOnSave");
        prefDisableVersionCheckOnSave->setChecked(false);
        prefDisableVersionCheckOnSave->setProperty("prefEntry", QVariant(QByteArray("DisableVersionCheckOnSave")));
        prefDisableVersionCheckOnSave->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_2->addWidget(prefDisableVersionCheckOnSave, 10, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(Gui__Dialog__DlgSettingsDocument);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        prefDuplicateLabel = new Gui::PrefCheckBox(groupBox_2);
        prefDuplicateLabel->setObjectName("prefDuplicateLabel");
        prefDuplicateLabel->setProperty("prefEntry", QVariant(QByteArray("DuplicateLabels")));
        prefDuplicateLabel->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout->addWidget(prefDuplicateLabel, 0, 0, 1, 1);

        prefPartialLoading = new Gui::PrefCheckBox(groupBox_2);
        prefPartialLoading->setObjectName("prefPartialLoading");
        prefPartialLoading->setProperty("prefEntry", QVariant(QByteArray("NoPartialLoading")));
        prefPartialLoading->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout->addWidget(prefPartialLoading, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(Gui__Dialog__DlgSettingsDocument);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName("gridLayout_5");
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");

        gridLayout_5->addWidget(label_3, 0, 0, 1, 1);

        prefAuthor = new Gui::PrefLineEdit(groupBox_3);
        prefAuthor->setObjectName("prefAuthor");
        prefAuthor->setProperty("prefEntry", QVariant(QByteArray("prefAuthor")));
        prefAuthor->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_5->addWidget(prefAuthor, 0, 1, 1, 1);

        prefSetAuthorOnSave = new Gui::PrefCheckBox(groupBox_3);
        prefSetAuthorOnSave->setObjectName("prefSetAuthorOnSave");
        prefSetAuthorOnSave->setProperty("prefEntry", QVariant(QByteArray("prefSetAuthorOnSave")));
        prefSetAuthorOnSave->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_5->addWidget(prefSetAuthorOnSave, 0, 2, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");

        gridLayout_5->addWidget(label_4, 1, 0, 1, 1);

        prefCompany = new Gui::PrefLineEdit(groupBox_3);
        prefCompany->setObjectName("prefCompany");
        prefCompany->setProperty("prefEntry", QVariant(QByteArray("prefCompany")));
        prefCompany->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_5->addWidget(prefCompany, 1, 1, 1, 2);

        label = new QLabel(groupBox_3);
        label->setObjectName("label");

        gridLayout_5->addWidget(label, 2, 0, 1, 1);

        prefLicenseType = new Gui::PrefComboBox(groupBox_3);
        prefLicenseType->setObjectName("prefLicenseType");
        prefLicenseType->setEnabled(true);
        prefLicenseType->setEditable(false);
        prefLicenseType->setProperty("prefEntry", QVariant(QByteArray("prefLicenseType")));
        prefLicenseType->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_5->addWidget(prefLicenseType, 2, 1, 1, 2);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");

        gridLayout_5->addWidget(label_2, 3, 0, 1, 1);

        prefLicenseUrl = new Gui::PrefLineEdit(groupBox_3);
        prefLicenseUrl->setObjectName("prefLicenseUrl");
        prefLicenseUrl->setText(QString::fromUtf8("https://en.wikipedia.org/wiki/All_rights_reserved"));
        prefLicenseUrl->setReadOnly(false);
        prefLicenseUrl->setProperty("prefEntry", QVariant(QByteArray("prefLicenseUrl")));
        prefLicenseUrl->setProperty("prefPath", QVariant(QByteArray("Document")));

        gridLayout_5->addWidget(prefLicenseUrl, 3, 1, 1, 2);


        gridLayout_3->addWidget(groupBox_3, 3, 0, 1, 1);

        spacerItem2 = new QSpacerItem(429, 37, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(spacerItem2, 4, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgSettingsDocument);
        QObject::connect(prefSaveBackupFiles, SIGNAL(toggled(bool)), prefCountBackupFiles, SLOT(setEnabled(bool)));
        QObject::connect(prefAutoSaveEnabled, SIGNAL(toggled(bool)), prefAutoSaveTimeout, SLOT(setEnabled(bool)));
        QObject::connect(prefSaveBackupFiles, SIGNAL(toggled(bool)), prefSaveBackupExtension, SLOT(setEnabled(bool)));
        QObject::connect(prefSaveBackupFiles, SIGNAL(toggled(bool)), prefSaveBackupDateFormat, SLOT(setEnabled(bool)));
        QObject::connect(prefSaveThumbnail, SIGNAL(toggled(bool)), prefThumbnailSize, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsDocument);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsDocument)
    {
        Gui__Dialog__DlgSettingsDocument->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Document", nullptr));
        GroupBox5->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "General", nullptr));
        textLabel1_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Maximum undo/redo steps", nullptr));
#if QT_CONFIG(tooltip)
        prefUndoRedoSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "How many undo/redo steps should be recorded", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        prefEnableAsyncRecompute->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "This experimental feature allows more responsive GUI while recomputing features.", nullptr));
#endif // QT_CONFIG(tooltip)
        prefEnableAsyncRecompute->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Enables async document recomputation", nullptr));
#if QT_CONFIG(tooltip)
        prefCanAbortRecompute->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Allow user aborting document recomputation by pressing Esc.\n"
"This feature may slightly increase recomputation time.", nullptr));
#endif // QT_CONFIG(tooltip)
        prefCanAbortRecompute->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Allow aborting recomputation", nullptr));
#if QT_CONFIG(tooltip)
        prefCheckNewDoc->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "The application will create a new document when started", nullptr));
#endif // QT_CONFIG(tooltip)
        prefCheckNewDoc->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Create new document at start up", nullptr));
        textLabel1->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Document save compression level\n"
"(0 = none, 9 = highest, 7 = default)", nullptr));
#if QT_CONFIG(tooltip)
        prefCompression->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Compression level for FCStd files", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Storage", nullptr));
        FormatTimeDocsLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Show format documentation", nullptr));
        prefDiscardTransaction->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Discard saved transaction after saving document", nullptr));
#if QT_CONFIG(tooltip)
        prefSaveThumbnail->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "A thumbnail will be stored when document is saved", nullptr));
#endif // QT_CONFIG(tooltip)
        prefSaveThumbnail->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Add thumbnail to project file when saving", nullptr));
        label_6->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Size", nullptr));
#if QT_CONFIG(tooltip)
        prefThumbnailSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Sets the size of the thumbnail that is stored in the document.\n"
"Common sizes are 128, 256 and 512.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        prefSaveBackupFiles->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "How many backup files will be kept when saving document", nullptr));
#endif // QT_CONFIG(tooltip)
        prefSaveBackupFiles->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Maximum number of backup files to keep when resaving document", nullptr));
#if QT_CONFIG(tooltip)
        prefRecovery->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "If there is a recovery file available, the application will\n"
"automatically run a file recovery when it is started", nullptr));
#endif // QT_CONFIG(tooltip)
        prefRecovery->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Run AutoRecovery at startup", nullptr));
        prefSaveTransaction->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Saving transactions (Auto-save)", nullptr));
#if QT_CONFIG(tooltip)
        prefAddLogo->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "The program icon will be added to the thumbnail", nullptr));
#endif // QT_CONFIG(tooltip)
        prefAddLogo->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Add program icon to the generated thumbnail", nullptr));
#if QT_CONFIG(tooltip)
        prefAutoSaveEnabled->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "How often a recovery file is written", nullptr));
#endif // QT_CONFIG(tooltip)
        prefAutoSaveEnabled->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Save auto-recovery information every", nullptr));
#if QT_CONFIG(tooltip)
        prefSaveBackupExtension->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Backup files will get extension '.FCbak' and file names\n"
"get date suffix according to the specified format", nullptr));
#endif // QT_CONFIG(tooltip)
        prefSaveBackupExtension->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Use date and FCBak extension", nullptr));
        label_5->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Date format", nullptr));
#if QT_CONFIG(tooltip)
        prefDisableVersionCheckOnSave->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Suppresses the version mismatch warning when saving files created with an older FreeCAD version", nullptr));
#endif // QT_CONFIG(tooltip)
        prefDisableVersionCheckOnSave->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Suppress older version warning on save", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Document Objects", nullptr));
#if QT_CONFIG(tooltip)
        prefDuplicateLabel->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Allow objects to have same label", nullptr));
#endif // QT_CONFIG(tooltip)
        prefDuplicateLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Allow duplicate object labels in one document", nullptr));
#if QT_CONFIG(tooltip)
        prefPartialLoading->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Disable partial loading of external linked documents.\n"
"Then only referenced objects and their dependencies will be loaded\n"
"when a linked document is auto-opened together with the main document.\n"
"A partially loaded document cannot be edited. Double click the document\n"
"icon in the tree view to fully reload it.", nullptr));
#endif // QT_CONFIG(tooltip)
        prefPartialLoading->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Disable partial loading of external linked objects", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Authoring and License", nullptr));
        label_3->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Author name", nullptr));
#if QT_CONFIG(tooltip)
        prefAuthor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "All documents that will be created will get the specified author name.\n"
"Keep blank for anonymous.\n"
"You can also use the form: John Doe <john@doe.com>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        prefSetAuthorOnSave->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "The field 'Last modified by' will be set to specified author when saving the file", nullptr));
#endif // QT_CONFIG(tooltip)
        prefSetAuthorOnSave->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Set on save", nullptr));
        label_4->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Company", nullptr));
#if QT_CONFIG(tooltip)
        prefCompany->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Default company name to use for new files", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Default license", nullptr));
#if QT_CONFIG(tooltip)
        prefLicenseType->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "Default license for new documents", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "License URL", nullptr));
#if QT_CONFIG(tooltip)
        prefLicenseUrl->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsDocument", "URL describing more about the license", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsDocument: public Ui_DlgSettingsDocument {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSDOCUMENT_H
