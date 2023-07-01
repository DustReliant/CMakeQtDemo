/********************************************************************************
** Form generated from reading UI file 'frmtreewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMTREEWIDGET_H
#define UI_FRMTREEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmTreeWidget
{
public:
    QGridLayout *gridLayout;
    QTextEdit *txtMain;
    QLabel *labInfo;
    QPushButton *btnSetData;
    QPushButton *btnGetData;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *frmTreeWidget)
    {
        if (frmTreeWidget->objectName().isEmpty())
            frmTreeWidget->setObjectName(QString::fromUtf8("frmTreeWidget"));
        frmTreeWidget->resize(800, 600);
        gridLayout = new QGridLayout(frmTreeWidget);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        txtMain = new QTextEdit(frmTreeWidget);
        txtMain->setObjectName(QString::fromUtf8("txtMain"));
        txtMain->setReadOnly(true);

        gridLayout->addWidget(txtMain, 1, 0, 1, 3);

        labInfo = new QLabel(frmTreeWidget);
        labInfo->setObjectName(QString::fromUtf8("labInfo"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labInfo->sizePolicy().hasHeightForWidth());
        labInfo->setSizePolicy(sizePolicy);
        labInfo->setFrameShape(QFrame::Box);
        labInfo->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(labInfo, 2, 0, 1, 1);

        btnSetData = new QPushButton(frmTreeWidget);
        btnSetData->setObjectName(QString::fromUtf8("btnSetData"));

        gridLayout->addWidget(btnSetData, 2, 1, 1, 1);

        btnGetData = new QPushButton(frmTreeWidget);
        btnGetData->setObjectName(QString::fromUtf8("btnGetData"));

        gridLayout->addWidget(btnGetData, 2, 2, 1, 1);

        treeWidget = new QTreeWidget(frmTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        gridLayout->addWidget(treeWidget, 0, 0, 1, 3);


        retranslateUi(frmTreeWidget);

        QMetaObject::connectSlotsByName(frmTreeWidget);
    } // setupUi

    void retranslateUi(QWidget *frmTreeWidget)
    {
        frmTreeWidget->setWindowTitle(QCoreApplication::translate("frmTreeWidget", "Form", nullptr));
        labInfo->setText(QString());
        btnSetData->setText(QCoreApplication::translate("frmTreeWidget", "\350\256\276\347\275\256\346\225\260\346\215\256", nullptr));
        btnGetData->setText(QCoreApplication::translate("frmTreeWidget", "\350\216\267\345\217\226\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmTreeWidget: public Ui_frmTreeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMTREEWIDGET_H
