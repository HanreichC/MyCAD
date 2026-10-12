/********************************************************************************
** Form generated from reading UI file 'MaterialsEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIALSEDITOR_H
#define UI_MATERIALSEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace MatGui {

class Ui_MaterialsEditor
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTreeView *treeMaterials;
    QTabWidget *tabWidget;
    QWidget *tabGeneral;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QLabel *labelParent;
    QTextEdit *editDescription;
    QLabel *label;
    QLabel *labelSourceURL;
    QLineEdit *editName;
    QLabel *labelDescription;
    QLabel *labelName;
    QLineEdit *editTags;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *editSourceURL;
    QPushButton *buttonURL;
    QLineEdit *editAuthor;
    QLabel *labelAuthor;
    QLineEdit *editParent;
    QLabel *labelSourceReference;
    QLineEdit *editSourceReference;
    QLineEdit *editLicense;
    QLabel *labelLicense;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *buttonNew;
    QPushButton *buttonInheritNew;
    QPushButton *buttonFavorite;
    QWidget *tabProperties;
    QVBoxLayout *verticalLayout_43;
    QHBoxLayout *horizontalLayout_23;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonPhysicalAdd;
    QPushButton *buttonPhysicalRemove;
    QTreeView *treePhysicalProperties;
    QWidget *tabAppearance;
    QVBoxLayout *verticalLayout_42;
    QHBoxLayout *layoutAppearance;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *buttonAppearanceAdd;
    QPushButton *buttonAppearanceRemove;
    QTreeView *treeAppearance;
    QDialogButtonBox *standardButtons;

    void setupUi(QDialog *MatGui__MaterialsEditor)
    {
        if (MatGui__MaterialsEditor->objectName().isEmpty())
            MatGui__MaterialsEditor->setObjectName("MatGui__MaterialsEditor");
        MatGui__MaterialsEditor->resize(835, 542);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MatGui__MaterialsEditor->sizePolicy().hasHeightForWidth());
        MatGui__MaterialsEditor->setSizePolicy(sizePolicy);
        MatGui__MaterialsEditor->setSizeGripEnabled(false);
        verticalLayout = new QVBoxLayout(MatGui__MaterialsEditor);
        verticalLayout->setObjectName("verticalLayout");
        splitter = new QSplitter(MatGui__MaterialsEditor);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        treeMaterials = new QTreeView(splitter);
        treeMaterials->setObjectName("treeMaterials");
        treeMaterials->setSelectionBehavior(QAbstractItemView::SelectItems);
        treeMaterials->setHeaderHidden(true);
        splitter->addWidget(treeMaterials);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName("tabWidget");
        tabGeneral = new QWidget();
        tabGeneral->setObjectName("tabGeneral");
        sizePolicy.setHeightForWidth(tabGeneral->sizePolicy().hasHeightForWidth());
        tabGeneral->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(tabGeneral);
        verticalLayout_3->setObjectName("verticalLayout_3");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout->setContentsMargins(7, 7, 7, 7);
        labelParent = new QLabel(tabGeneral);
        labelParent->setObjectName("labelParent");

        gridLayout->addWidget(labelParent, 3, 0, 1, 1);

        editDescription = new QTextEdit(tabGeneral);
        editDescription->setObjectName("editDescription");

        gridLayout->addWidget(editDescription, 8, 2, 1, 1);

        label = new QLabel(tabGeneral);
        label->setObjectName("label");

        gridLayout->addWidget(label, 6, 0, 1, 1);

        labelSourceURL = new QLabel(tabGeneral);
        labelSourceURL->setObjectName("labelSourceURL");

        gridLayout->addWidget(labelSourceURL, 4, 0, 1, 1);

        editName = new QLineEdit(tabGeneral);
        editName->setObjectName("editName");

        gridLayout->addWidget(editName, 0, 2, 1, 1);

        labelDescription = new QLabel(tabGeneral);
        labelDescription->setObjectName("labelDescription");

        gridLayout->addWidget(labelDescription, 8, 0, 1, 1);

        labelName = new QLabel(tabGeneral);
        labelName->setObjectName("labelName");

        gridLayout->addWidget(labelName, 0, 0, 1, 1);

        editTags = new QLineEdit(tabGeneral);
        editTags->setObjectName("editTags");

        gridLayout->addWidget(editTags, 6, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        editSourceURL = new QLineEdit(tabGeneral);
        editSourceURL->setObjectName("editSourceURL");

        horizontalLayout_2->addWidget(editSourceURL);

        buttonURL = new QPushButton(tabGeneral);
        buttonURL->setObjectName("buttonURL");
        buttonURL->setMaximumSize(QSize(22, 22));

        horizontalLayout_2->addWidget(buttonURL);


        gridLayout->addLayout(horizontalLayout_2, 4, 2, 1, 1);

        editAuthor = new QLineEdit(tabGeneral);
        editAuthor->setObjectName("editAuthor");

        gridLayout->addWidget(editAuthor, 1, 2, 1, 1);

        labelAuthor = new QLabel(tabGeneral);
        labelAuthor->setObjectName("labelAuthor");

        gridLayout->addWidget(labelAuthor, 1, 0, 1, 1);

        editParent = new QLineEdit(tabGeneral);
        editParent->setObjectName("editParent");

        gridLayout->addWidget(editParent, 3, 2, 1, 1);

        labelSourceReference = new QLabel(tabGeneral);
        labelSourceReference->setObjectName("labelSourceReference");

        gridLayout->addWidget(labelSourceReference, 5, 0, 1, 1);

        editSourceReference = new QLineEdit(tabGeneral);
        editSourceReference->setObjectName("editSourceReference");

        gridLayout->addWidget(editSourceReference, 5, 2, 1, 1);

        editLicense = new QLineEdit(tabGeneral);
        editLicense->setObjectName("editLicense");

        gridLayout->addWidget(editLicense, 2, 2, 1, 1);

        labelLicense = new QLabel(tabGeneral);
        labelLicense->setObjectName("labelLicense");

        gridLayout->addWidget(labelLicense, 2, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        buttonNew = new QPushButton(tabGeneral);
        buttonNew->setObjectName("buttonNew");

        horizontalLayout_3->addWidget(buttonNew);

        buttonInheritNew = new QPushButton(tabGeneral);
        buttonInheritNew->setObjectName("buttonInheritNew");

        horizontalLayout_3->addWidget(buttonInheritNew);

        buttonFavorite = new QPushButton(tabGeneral);
        buttonFavorite->setObjectName("buttonFavorite");

        horizontalLayout_3->addWidget(buttonFavorite);


        verticalLayout_3->addLayout(horizontalLayout_3);

        tabWidget->addTab(tabGeneral, QString());
        tabProperties = new QWidget();
        tabProperties->setObjectName("tabProperties");
        verticalLayout_43 = new QVBoxLayout(tabProperties);
        verticalLayout_43->setObjectName("verticalLayout_43");
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer);

        buttonPhysicalAdd = new QPushButton(tabProperties);
        buttonPhysicalAdd->setObjectName("buttonPhysicalAdd");
        buttonPhysicalAdd->setText(QString::fromUtf8("+"));

        horizontalLayout_23->addWidget(buttonPhysicalAdd);

        buttonPhysicalRemove = new QPushButton(tabProperties);
        buttonPhysicalRemove->setObjectName("buttonPhysicalRemove");
        buttonPhysicalRemove->setText(QString::fromUtf8("-"));

        horizontalLayout_23->addWidget(buttonPhysicalRemove);


        verticalLayout_43->addLayout(horizontalLayout_23);

        treePhysicalProperties = new QTreeView(tabProperties);
        treePhysicalProperties->setObjectName("treePhysicalProperties");

        verticalLayout_43->addWidget(treePhysicalProperties);

        tabWidget->addTab(tabProperties, QString());
        tabAppearance = new QWidget();
        tabAppearance->setObjectName("tabAppearance");
        verticalLayout_42 = new QVBoxLayout(tabAppearance);
        verticalLayout_42->setObjectName("verticalLayout_42");
        layoutAppearance = new QHBoxLayout();
        layoutAppearance->setObjectName("layoutAppearance");

        verticalLayout_42->addLayout(layoutAppearance);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        buttonAppearanceAdd = new QPushButton(tabAppearance);
        buttonAppearanceAdd->setObjectName("buttonAppearanceAdd");
        buttonAppearanceAdd->setText(QString::fromUtf8("+"));

        horizontalLayout->addWidget(buttonAppearanceAdd);

        buttonAppearanceRemove = new QPushButton(tabAppearance);
        buttonAppearanceRemove->setObjectName("buttonAppearanceRemove");
        buttonAppearanceRemove->setText(QString::fromUtf8("-"));

        horizontalLayout->addWidget(buttonAppearanceRemove);


        verticalLayout_42->addLayout(horizontalLayout);

        treeAppearance = new QTreeView(tabAppearance);
        treeAppearance->setObjectName("treeAppearance");

        verticalLayout_42->addWidget(treeAppearance);

        tabWidget->addTab(tabAppearance, QString());
        splitter->addWidget(tabWidget);

        verticalLayout->addWidget(splitter);

        standardButtons = new QDialogButtonBox(MatGui__MaterialsEditor);
        standardButtons->setObjectName("standardButtons");
        standardButtons->setOrientation(Qt::Horizontal);
        standardButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Save);

        verticalLayout->addWidget(standardButtons);


        retranslateUi(MatGui__MaterialsEditor);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MatGui__MaterialsEditor);
    } // setupUi

    void retranslateUi(QDialog *MatGui__MaterialsEditor)
    {
        MatGui__MaterialsEditor->setWindowTitle(QCoreApplication::translate("MatGui::MaterialsEditor", "Materials", nullptr));
        labelParent->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "Parent", nullptr));
        label->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "Tags", nullptr));
        labelSourceURL->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "Source URL", nullptr));
        labelDescription->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "Description", nullptr));
        labelName->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "Name", nullptr));
        buttonURL->setText(QString());
        labelAuthor->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "Author", nullptr));
        labelSourceReference->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "Source reference", nullptr));
        labelLicense->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "License", nullptr));
        buttonNew->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "&New", nullptr));
        buttonInheritNew->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "Inherit New", nullptr));
#if QT_CONFIG(tooltip)
        buttonFavorite->setToolTip(QCoreApplication::translate("MatGui::MaterialsEditor", "Adds or removes to/from favorites", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonFavorite->setText(QCoreApplication::translate("MatGui::MaterialsEditor", "Toggle Favorite", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneral), QCoreApplication::translate("MatGui::MaterialsEditor", "General", nullptr));
#if QT_CONFIG(tooltip)
        buttonPhysicalAdd->setToolTip(QCoreApplication::translate("MatGui::MaterialsEditor", "Add physical model", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        buttonPhysicalRemove->setToolTip(QCoreApplication::translate("MatGui::MaterialsEditor", "Delete physical model", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidget->setTabText(tabWidget->indexOf(tabProperties), QCoreApplication::translate("MatGui::MaterialsEditor", "Physical", nullptr));
#if QT_CONFIG(tooltip)
        buttonAppearanceAdd->setToolTip(QCoreApplication::translate("MatGui::MaterialsEditor", "Add appearance model", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        buttonAppearanceRemove->setToolTip(QCoreApplication::translate("MatGui::MaterialsEditor", "Delete appearance model", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidget->setTabText(tabWidget->indexOf(tabAppearance), QCoreApplication::translate("MatGui::MaterialsEditor", "Appearance", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class MaterialsEditor: public Ui_MaterialsEditor {};
} // namespace Ui
} // namespace MatGui

#endif // UI_MATERIALSEDITOR_H
