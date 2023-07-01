/********************************************************************************
** Form generated from reading UI file 'frmtableview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTABLEVIEW_H
#define UI_FRMTABLEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmTableView
{
public:
    QGridLayout *gridLayout;
    QTextEdit *txtMain;
    QLabel *labInfo;
    QPushButton *btnSetData;
    QPushButton *btnGetData;
    QTableView *tableView;

    void setupUi(QWidget *frmTableView)
    {
        if (frmTableView->objectName().isEmpty())
            frmTableView->setObjectName(QString::fromUtf8("frmTableView"));
        frmTableView->resize(800, 600);
        gridLayout = new QGridLayout(frmTableView);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        txtMain = new QTextEdit(frmTableView);
        txtMain->setObjectName(QString::fromUtf8("txtMain"));
        txtMain->setReadOnly(true);

        gridLayout->addWidget(txtMain, 1, 0, 1, 3);

        labInfo = new QLabel(frmTableView);
        labInfo->setObjectName(QString::fromUtf8("labInfo"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labInfo->sizePolicy().hasHeightForWidth());
        labInfo->setSizePolicy(sizePolicy);
        labInfo->setFrameShape(QFrame::Box);
        labInfo->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(labInfo, 2, 0, 1, 1);

        btnSetData = new QPushButton(frmTableView);
        btnSetData->setObjectName(QString::fromUtf8("btnSetData"));

        gridLayout->addWidget(btnSetData, 2, 1, 1, 1);

        btnGetData = new QPushButton(frmTableView);
        btnGetData->setObjectName(QString::fromUtf8("btnGetData"));

        gridLayout->addWidget(btnGetData, 2, 2, 1, 1);

        tableView = new QTableView(frmTableView);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 3);


        retranslateUi(frmTableView);

        QMetaObject::connectSlotsByName(frmTableView);
    } // setupUi

    void retranslateUi(QWidget *frmTableView)
    {
        frmTableView->setWindowTitle(QCoreApplication::translate("frmTableView", "Form", nullptr));
        labInfo->setText(QString());
        btnSetData->setText(QCoreApplication::translate("frmTableView", "\350\256\276\347\275\256\346\225\260\346\215\256", nullptr));
        btnGetData->setText(QCoreApplication::translate("frmTableView", "\350\216\267\345\217\226\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmTableView: public Ui_frmTableView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTABLEVIEW_H
