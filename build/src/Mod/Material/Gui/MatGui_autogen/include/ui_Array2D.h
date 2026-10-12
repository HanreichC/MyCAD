/********************************************************************************
** Form generated from reading UI file 'Array2D.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARRAY2D_H
#define UI_ARRAY2D_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

namespace MatGui {

class Ui_Array2D
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QDialogButtonBox *standardButtons;

    void setupUi(QDialog *MatGui__Array2D)
    {
        if (MatGui__Array2D->objectName().isEmpty())
            MatGui__Array2D->setObjectName("MatGui__Array2D");
        MatGui__Array2D->resize(578, 557);
        verticalLayout = new QVBoxLayout(MatGui__Array2D);
        verticalLayout->setObjectName("verticalLayout");
        tableView = new QTableView(MatGui__Array2D);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);

        standardButtons = new QDialogButtonBox(MatGui__Array2D);
        standardButtons->setObjectName("standardButtons");
        standardButtons->setOrientation(Qt::Horizontal);
        standardButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(standardButtons);


        retranslateUi(MatGui__Array2D);
        QObject::connect(standardButtons, &QDialogButtonBox::accepted, MatGui__Array2D, qOverload<>(&QDialog::accept));
        QObject::connect(standardButtons, &QDialogButtonBox::rejected, MatGui__Array2D, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(MatGui__Array2D);
    } // setupUi

    void retranslateUi(QDialog *MatGui__Array2D)
    {
        MatGui__Array2D->setWindowTitle(QCoreApplication::translate("MatGui::Array2D", "2D Array", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class Array2D: public Ui_Array2D {};
} // namespace Ui
} // namespace MatGui

#endif // UI_ARRAY2D_H
