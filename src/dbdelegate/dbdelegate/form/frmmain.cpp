#include "frmmain.h"
#include "ui_frmmain.h"
#include "quihelper.h"

#include "frmsimple.h"
#include "frmtableview.h"
#include "frmtablewidget.h"
#include "frmtreeview.h"
#include "frmtreewidget.h"

frmMain::frmMain(QWidget *parent) : QWidget(parent), ui(new Ui::frmMain)
{
    ui->setupUi(this);
    this->initForm();
    this->initStyle();
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::initForm()
{
    ui->tabWidget->addTab(new frmSimple, "最简单示例");
    ui->tabWidget->addTab(new frmTableView, "QTableView");
    ui->tabWidget->addTab(new frmTableWidget, "QTableWidget");
    ui->tabWidget->addTab(new frmTreeView, "QTreeView");
    ui->tabWidget->addTab(new frmTreeWidget, "QTreeWidget");
    ui->tabWidget->setCurrentIndex(4);

#if 0
    //QTreeWidgetItem和QListWidgetItem的item居然默认不可编辑
    QStandardItem *item0 = new QStandardItem;
    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTreeWidgetItem *item2 = new QTreeWidgetItem;
    QListWidgetItem *item3 = new QListWidgetItem;
    qDebug() << "QStandardItem" << item0->flags();
    qDebug() << "QTableWidgetItem" << item1->flags();
    qDebug() << "QTreeWidgetItem" << item2->flags();
    qDebug() << "QListWidgetItem" << item3->flags();
#endif
}

void frmMain::initStyle()
{
    QStringList list;
#if 0
    //可以采用默认的颜色,也可以重新设置选中行的颜色,重新设置以后也需要设置对应的委托的颜色
    list << "QTableView::item:hover{background:#DDDDDD;}";
    list << "QTableView::item:selected{background:#AAAAAA;}";
    foreach (DbDelegate *delegate, AppFun::delegates) {
        delegate->setTextColor("#FF00FF");
        delegate->setHoverBgColor("#DDDDDD");
        delegate->setSelectBgColor("#AAAAAA");        
    }
#endif

    //设置样式表,与委托无关,方便好看
    list << "QPushButton{background:#4D4D4D;border:1px solid #353535;color:#F0F0F0;}";
    list << "QPushButton{padding:0px;margin:1px;border-radius:0px;min-width:40px;}";
    list << "QPushButton:pressed{background:#383838;}";
    list << "QPushButton:hover{background:#636363;}";
    list << "QProgressBar{background:#FFFFFF;color:#000000;text-align:center;border:none;margin:1px;}";
    list << "QProgressBar:chunk{background:#22A3A9;}";

    //按钮
    list << "#btnSetData,#btnGetData{min-width:90px;min-height:30px;}";
    //复选框
    //list << QString("QCheckBox::indicator{width:%1px;height:%1px;}").arg(15);
    //树状控件
    list << QString("QTreeView::item{height:%1px;}").arg(AppFun::rowHeight);

    QString qss = list.join("");
    qApp->setStyleSheet(qss);
}
