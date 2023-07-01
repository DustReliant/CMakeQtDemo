/********************************************************************************
** Form generated from reading UI file 'frmsimple.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSIMPLE_H
#define UI_FRMSIMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmSimple
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *frmSimple)
    {
        if (frmSimple->objectName().isEmpty())
            frmSimple->setObjectName(QString::fromUtf8("frmSimple"));
        frmSimple->resize(800, 600);
        verticalLayout = new QVBoxLayout(frmSimple);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        tableWidget = new QTableWidget(frmSimple);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(3, 1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(3, 2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(4, 0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(4, 1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(4, 2, __qtablewidgetitem22);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        retranslateUi(frmSimple);

        QMetaObject::connectSlotsByName(frmSimple);
    } // setupUi

    void retranslateUi(QWidget *frmSimple)
    {
        frmSimple->setWindowTitle(QCoreApplication::translate("frmSimple", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("frmSimple", "\344\270\213\346\213\211\346\241\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("frmSimple", "\350\201\224\345\212\250\345\210\2271", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("frmSimple", "\350\201\224\345\212\250\345\210\2272", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("frmSimple", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("frmSimple", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("frmSimple", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("frmSimple", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("frmSimple", "\346\226\260\345\273\272\350\241\214", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("frmSimple", "COM1", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("frmSimple", "1\345\217\267\346\245\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(0, 2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("frmSimple", "1\345\261\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(1, 0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("frmSimple", "COM2", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(1, 1);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("frmSimple", "1\345\217\267\346\245\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(1, 2);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("frmSimple", "1\345\261\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(2, 0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("frmSimple", "COM2", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(2, 1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("frmSimple", "2\345\217\267\346\245\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(2, 2);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("frmSimple", "1\345\261\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(3, 0);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("frmSimple", "COM4", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(3, 1);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("frmSimple", "1\345\217\267\346\245\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(3, 2);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("frmSimple", "1\345\261\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(4, 0);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("frmSimple", "COM1", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(4, 1);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("frmSimple", "2\345\217\267\346\245\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(4, 2);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("frmSimple", "1\345\261\202", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class frmSimple: public Ui_frmSimple {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSIMPLE_H
