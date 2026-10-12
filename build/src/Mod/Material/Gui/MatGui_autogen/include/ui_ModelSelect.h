/********************************************************************************
** Form generated from reading UI file 'ModelSelect.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELSELECT_H
#define UI_MODELSELECT_H

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
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace MatGui {

class Ui_ModelSelect
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTreeView *treeModels;
    QTabWidget *tabWidget;
    QWidget *tabGeneral;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *labelURL;
    QLabel *label;
    QLabel *labelDOI;
    QTextEdit *editDescription;
    QLineEdit *editName;
    QLabel *labelName;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *editDOI;
    QPushButton *buttonDOI;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *editURL;
    QPushButton *buttonURL;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonFavorite;
    QWidget *tabProperties;
    QVBoxLayout *verticalLayout_3;
    QTableView *tableProperties;
    QDialogButtonBox *standardButtons;

    void setupUi(QDialog *MatGui__ModelSelect)
    {
        if (MatGui__ModelSelect->objectName().isEmpty())
            MatGui__ModelSelect->setObjectName("MatGui__ModelSelect");
        MatGui__ModelSelect->resize(705, 489);
        verticalLayout = new QVBoxLayout(MatGui__ModelSelect);
        verticalLayout->setObjectName("verticalLayout");
        splitter = new QSplitter(MatGui__ModelSelect);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        treeModels = new QTreeView(splitter);
        treeModels->setObjectName("treeModels");
        splitter->addWidget(treeModels);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName("tabWidget");
        tabGeneral = new QWidget();
        tabGeneral->setObjectName("tabGeneral");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabGeneral->sizePolicy().hasHeightForWidth());
        tabGeneral->setSizePolicy(sizePolicy);
        tabGeneral->setMaximumSize(QSize(365, 409));
        verticalLayout_2 = new QVBoxLayout(tabGeneral);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        labelURL = new QLabel(tabGeneral);
        labelURL->setObjectName("labelURL");

        gridLayout->addWidget(labelURL, 1, 0, 1, 1);

        label = new QLabel(tabGeneral);
        label->setObjectName("label");

        gridLayout->addWidget(label, 3, 0, 1, 1);

        labelDOI = new QLabel(tabGeneral);
        labelDOI->setObjectName("labelDOI");

        gridLayout->addWidget(labelDOI, 2, 0, 1, 1);

        editDescription = new QTextEdit(tabGeneral);
        editDescription->setObjectName("editDescription");
        editDescription->setReadOnly(true);

        gridLayout->addWidget(editDescription, 3, 1, 1, 1);

        editName = new QLineEdit(tabGeneral);
        editName->setObjectName("editName");
        editName->setEnabled(true);
        editName->setReadOnly(true);

        gridLayout->addWidget(editName, 0, 1, 1, 1);

        labelName = new QLabel(tabGeneral);
        labelName->setObjectName("labelName");

        gridLayout->addWidget(labelName, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        editDOI = new QLineEdit(tabGeneral);
        editDOI->setObjectName("editDOI");
        editDOI->setReadOnly(true);

        horizontalLayout_3->addWidget(editDOI);

        buttonDOI = new QPushButton(tabGeneral);
        buttonDOI->setObjectName("buttonDOI");
        buttonDOI->setMaximumSize(QSize(22, 22));

        horizontalLayout_3->addWidget(buttonDOI);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        editURL = new QLineEdit(tabGeneral);
        editURL->setObjectName("editURL");
        editURL->setReadOnly(true);

        horizontalLayout_2->addWidget(editURL);

        buttonURL = new QPushButton(tabGeneral);
        buttonURL->setObjectName("buttonURL");
        buttonURL->setMaximumSize(QSize(22, 22));

        horizontalLayout_2->addWidget(buttonURL);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonFavorite = new QPushButton(tabGeneral);
        buttonFavorite->setObjectName("buttonFavorite");

        horizontalLayout->addWidget(buttonFavorite);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(tabGeneral, QString());
        tabProperties = new QWidget();
        tabProperties->setObjectName("tabProperties");
        verticalLayout_3 = new QVBoxLayout(tabProperties);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tableProperties = new QTableView(tabProperties);
        tableProperties->setObjectName("tableProperties");

        verticalLayout_3->addWidget(tableProperties);

        tabWidget->addTab(tabProperties, QString());
        splitter->addWidget(tabWidget);

        verticalLayout->addWidget(splitter);

        standardButtons = new QDialogButtonBox(MatGui__ModelSelect);
        standardButtons->setObjectName("standardButtons");
        standardButtons->setOrientation(Qt::Horizontal);
        standardButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(standardButtons);


        retranslateUi(MatGui__ModelSelect);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MatGui__ModelSelect);
    } // setupUi

    void retranslateUi(QDialog *MatGui__ModelSelect)
    {
        MatGui__ModelSelect->setWindowTitle(QCoreApplication::translate("MatGui::ModelSelect", "Material Models", nullptr));
        labelURL->setText(QCoreApplication::translate("MatGui::ModelSelect", "URL", nullptr));
        label->setText(QCoreApplication::translate("MatGui::ModelSelect", "Description", nullptr));
        labelDOI->setText(QCoreApplication::translate("MatGui::ModelSelect", "DOI", nullptr));
        labelName->setText(QCoreApplication::translate("MatGui::ModelSelect", "Name", nullptr));
        buttonDOI->setText(QString());
        buttonURL->setText(QString());
#if QT_CONFIG(tooltip)
        buttonFavorite->setToolTip(QCoreApplication::translate("MatGui::ModelSelect", "Adds or removes to/from favorites", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonFavorite->setText(QCoreApplication::translate("MatGui::ModelSelect", "Toggle Favorites", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneral), QCoreApplication::translate("MatGui::ModelSelect", "General", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabProperties), QCoreApplication::translate("MatGui::ModelSelect", "Properties", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class ModelSelect: public Ui_ModelSelect {};
} // namespace Ui
} // namespace MatGui

#endif // UI_MODELSELECT_H
