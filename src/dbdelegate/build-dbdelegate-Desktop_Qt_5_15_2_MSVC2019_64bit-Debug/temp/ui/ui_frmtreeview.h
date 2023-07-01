/********************************************************************************
** Form generated from reading UI file 'frmtreeview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTREEVIEW_H
#define UI_FRMTREEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmTreeView
{
public:
    QGridLayout *gridLayout;
    QTextEdit *txtMain;
    QLabel *labInfo;
    QPushButton *btnSetData;
    QPushButton *btnGetData;
    QTreeView *treeView;

    void setupUi(QWidget *frmTreeView)
    {
        if (frmTreeView->objectName().isEmpty())
            frmTreeView->setObjectName(QString::fromUtf8("frmTreeView"));
        frmTreeView->resize(800, 600);
        gridLayout = new QGridLayout(frmTreeView);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        txtMain = new QTextEdit(frmTreeView);
        txtMain->setObjectName(QString::fromUtf8("txtMain"));
        txtMain->setReadOnly(true);

        gridLayout->addWidget(txtMain, 1, 0, 1, 3);

        labInfo = new QLabel(frmTreeView);
        labInfo->setObjectName(QString::fromUtf8("labInfo"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labInfo->sizePolicy().hasHeightForWidth());
        labInfo->setSizePolicy(sizePolicy);
        labInfo->setFrameShape(QFrame::Box);
        labInfo->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(labInfo, 2, 0, 1, 1);

        btnSetData = new QPushButton(frmTreeView);
        btnSetData->setObjectName(QString::fromUtf8("btnSetData"));

        gridLayout->addWidget(btnSetData, 2, 1, 1, 1);

        btnGetData = new QPushButton(frmTreeView);
        btnGetData->setObjectName(QString::fromUtf8("btnGetData"));

        gridLayout->addWidget(btnGetData, 2, 2, 1, 1);

        treeView = new QTreeView(frmTreeView);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        gridLayout->addWidget(treeView, 0, 0, 1, 3);


        retranslateUi(frmTreeView);

        QMetaObject::connectSlotsByName(frmTreeView);
    } // setupUi

    void retranslateUi(QWidget *frmTreeView)
    {
        frmTreeView->setWindowTitle(QCoreApplication::translate("frmTreeView", "Form", nullptr));
        labInfo->setText(QString());
        btnSetData->setText(QCoreApplication::translate("frmTreeView", "\350\256\276\347\275\256\346\225\260\346\215\256", nullptr));
        btnGetData->setText(QCoreApplication::translate("frmTreeView", "\350\216\267\345\217\226\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmTreeView: public Ui_frmTreeView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTREEVIEW_H
