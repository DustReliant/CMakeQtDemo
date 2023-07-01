/********************************************************************************
** Form generated from reading UI file 'frmtablewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTABLEWIDGET_H
#define UI_FRMTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmTableWidget
{
public:
    QGridLayout *gridLayout;
    QTextEdit *txtMain;
    QLabel *labInfo;
    QPushButton *btnSetData;
    QPushButton *btnGetData;
    QTableWidget *tableWidget;

    void setupUi(QWidget *frmTableWidget)
    {
        if (frmTableWidget->objectName().isEmpty())
            frmTableWidget->setObjectName(QString::fromUtf8("frmTableWidget"));
        frmTableWidget->resize(800, 600);
        gridLayout = new QGridLayout(frmTableWidget);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        txtMain = new QTextEdit(frmTableWidget);
        txtMain->setObjectName(QString::fromUtf8("txtMain"));
        txtMain->setReadOnly(true);

        gridLayout->addWidget(txtMain, 1, 0, 1, 3);

        labInfo = new QLabel(frmTableWidget);
        labInfo->setObjectName(QString::fromUtf8("labInfo"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labInfo->sizePolicy().hasHeightForWidth());
        labInfo->setSizePolicy(sizePolicy);
        labInfo->setFrameShape(QFrame::Box);
        labInfo->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(labInfo, 2, 0, 1, 1);

        btnSetData = new QPushButton(frmTableWidget);
        btnSetData->setObjectName(QString::fromUtf8("btnSetData"));

        gridLayout->addWidget(btnSetData, 2, 1, 1, 1);

        btnGetData = new QPushButton(frmTableWidget);
        btnGetData->setObjectName(QString::fromUtf8("btnGetData"));

        gridLayout->addWidget(btnGetData, 2, 2, 1, 1);

        tableWidget = new QTableWidget(frmTableWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 3);


        retranslateUi(frmTableWidget);

        QMetaObject::connectSlotsByName(frmTableWidget);
    } // setupUi

    void retranslateUi(QWidget *frmTableWidget)
    {
        frmTableWidget->setWindowTitle(QCoreApplication::translate("frmTableWidget", "Form", nullptr));
        labInfo->setText(QString());
        btnSetData->setText(QCoreApplication::translate("frmTableWidget", "\350\256\276\347\275\256\346\225\260\346\215\256", nullptr));
        btnGetData->setText(QCoreApplication::translate("frmTableWidget", "\350\216\267\345\217\226\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmTableWidget: public Ui_frmTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTABLEWIDGET_H
