/********************************************************************************
** Form generated from reading UI file 'DlgPreferences.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPREFERENCES_H
#define UI_DLGPREFERENCES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace Gui {
namespace Dialog {

class Ui_DlgPreferences
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QFrame *sidebar;
    QVBoxLayout *verticalLayout_4;
    QTreeView *groupsTreeView;
    QVBoxLayout *actions;
    QPushButton *buttonReset;
    QFrame *verticalFrame;
    QVBoxLayout *content;
    QHBoxLayout *horizontalLayout_3;
    QLabel *headerLabel;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *searchInputLayout;
    QLineEdit *searchBox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QStackedWidget *groupWidgetStack;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgPreferences)
    {
        if (Gui__Dialog__DlgPreferences->objectName().isEmpty())
            Gui__Dialog__DlgPreferences->setObjectName("Gui__Dialog__DlgPreferences");
        Gui__Dialog__DlgPreferences->setStyleSheet(QString::fromUtf8("#sidebar { background-color: rgba(0, 0, 0, 25); }\n"
"      #groupsTreeView { background-color: transparent; }\n"
"      #groupsTreeView::item { padding: 6px 0px; }"));
        Gui__Dialog__DlgPreferences->resize(900, 900);
        Gui__Dialog__DlgPreferences->setMinimumSize(QSize(600, 500));
        Gui__Dialog__DlgPreferences->setSizeGripEnabled(true);
        Gui__Dialog__DlgPreferences->setModal(true);
        gridLayout = new QGridLayout(Gui__Dialog__DlgPreferences);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        sidebar = new QFrame(Gui__Dialog__DlgPreferences);
        sidebar->setObjectName("sidebar");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sidebar->sizePolicy().hasHeightForWidth());
        sidebar->setSizePolicy(sizePolicy);
        sidebar->setMinimumSize(QSize(180, 0));
        sidebar->setMaximumSize(QSize(240, 16777215));
        sidebar->setAutoFillBackground(false);
        sidebar->setFrameShape(QFrame::NoFrame);
        sidebar->setFrameShadow(QFrame::Raised);
        sidebar->setLineWidth(0);
        verticalLayout_4 = new QVBoxLayout(sidebar);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 12, 0, 0);
        groupsTreeView = new QTreeView(sidebar);
        groupsTreeView->setObjectName("groupsTreeView");
        groupsTreeView->setContextMenuPolicy(Qt::NoContextMenu);
        groupsTreeView->setAutoFillBackground(false);
        groupsTreeView->setFrameShape(QFrame::NoFrame);
        groupsTreeView->setLineWidth(0);
        groupsTreeView->setAutoScroll(false);
        groupsTreeView->setIconSize(QSize(24, 24));
        groupsTreeView->header()->setVisible(false);

        verticalLayout_4->addWidget(groupsTreeView);

        actions = new QVBoxLayout();
        actions->setSpacing(8);
        actions->setObjectName("actions");
        actions->setContentsMargins(16, 16, 16, 16);
        buttonReset = new QPushButton(sidebar);
        buttonReset->setObjectName("buttonReset");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonReset->sizePolicy().hasHeightForWidth());
        buttonReset->setSizePolicy(sizePolicy1);

        actions->addWidget(buttonReset);


        verticalLayout_4->addLayout(actions);


        horizontalLayout->addWidget(sidebar);

        verticalFrame = new QFrame(Gui__Dialog__DlgPreferences);
        verticalFrame->setObjectName("verticalFrame");
        content = new QVBoxLayout(verticalFrame);
        content->setSpacing(12);
        content->setContentsMargins(11, 11, 11, 11);
        content->setObjectName("content");
        content->setContentsMargins(16, 16, 16, 16);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        headerLabel = new QLabel(verticalFrame);
        headerLabel->setObjectName("headerLabel");
        QFont font;
        font.setPointSize(18);
        headerLabel->setFont(font);

        horizontalLayout_3->addWidget(headerLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        searchInputLayout = new QHBoxLayout();
        searchInputLayout->setSpacing(4);
        searchInputLayout->setObjectName("searchInputLayout");
        searchBox = new QLineEdit(verticalFrame);
        searchBox->setObjectName("searchBox");
        searchBox->setMinimumSize(QSize(200, 0));
        searchBox->setMaximumSize(QSize(200, 16777215));
        searchBox->setClearButtonEnabled(true);

        searchInputLayout->addWidget(searchBox);


        horizontalLayout_3->addLayout(searchInputLayout);


        content->addLayout(horizontalLayout_3);

        scrollArea = new QScrollArea(verticalFrame);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy2);
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 626, 772));
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupWidgetStack = new QStackedWidget(scrollAreaWidgetContents);
        groupWidgetStack->setObjectName("groupWidgetStack");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(groupWidgetStack->sizePolicy().hasHeightForWidth());
        groupWidgetStack->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(groupWidgetStack);

        scrollArea->setWidget(scrollAreaWidgetContents);

        content->addWidget(scrollArea);

        buttonBox = new QDialogButtonBox(verticalFrame);
        buttonBox->setObjectName("buttonBox");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy4);
        buttonBox->setAutoFillBackground(false);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        content->addWidget(buttonBox);


        horizontalLayout->addWidget(verticalFrame);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgPreferences);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgPreferences, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgPreferences, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgPreferences);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgPreferences)
    {
        Gui__Dialog__DlgPreferences->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgPreferences", "Preferences", nullptr));
        buttonReset->setText(QCoreApplication::translate("Gui::Dialog::DlgPreferences", "Reset", nullptr));
        headerLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgPreferences", "Header", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("Gui::Dialog::DlgPreferences", "Search preferences\342\200\246", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgPreferences: public Ui_DlgPreferences {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGPREFERENCES_H
