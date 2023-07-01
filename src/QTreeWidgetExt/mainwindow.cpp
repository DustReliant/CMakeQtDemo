
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pTreeWidget = new QTreeWidgetExt(this);

    pTreeWidget->m_bHideFlag=true;
    QTreeWidgetItem* pRoot1 = NULL;
    //QTreeWidgetItem* pRoot2 = NULL;

    pRoot1 = pTreeWidget->addRootItem(u8"基本检查");
    pTreeWidget->addItem(pRoot1, u8"主机信息");
    pTreeWidget->addItem(pRoot1, u8"账户信息");
    pTreeWidget->addItem(pRoot1, u8"本地组");
    pTreeWidget->addItem(pRoot1, u8"内存信息");

    //pRoot1->setTextColor(2,Qt::green);
    pTreeWidget->setTextColor(pRoot1,Qt::green);

    pTreeWidget->setAllCheckable(false);
    pTreeWidget->setCheckBoxLeftMargin(15);
    pTreeWidget->setAllExtraBtnIcon(u8":/image/开始.png");


    QList<QTreeWidgetItem*> listA = pTreeWidget->getAllItem();
    for(int i = 0;i<listA.size();++i)
    {
        pTreeWidget->setTextColor(listA.at(i),Qt::red);
    }

    ui->verticalLayout->addWidget(pTreeWidget);






    m_pQTreeWidgetExt = new QTreeWidgetExt(this);

    QTreeWidgetItem* pRoot2 = NULL;

    pRoot1 = m_pQTreeWidgetExt->addRootItem(u8"网页浏览记录");
    pRoot1 = m_pQTreeWidgetExt->addRootItem(u8"邮件记录");
    pRoot1 = m_pQTreeWidgetExt->addRootItem(u8"下载记录");
    pRoot1 = m_pQTreeWidgetExt->addRootItem(u8"IM信息");
    pRoot1 = m_pQTreeWidgetExt->addRootItem(u8"云盘记录");
    pRoot1 = m_pQTreeWidgetExt->addRootItem(u8"网页连接情况");
    pRoot1 = m_pQTreeWidgetExt->addRootItem(u8"WIFI连接记录");
    pRoot1 = m_pQTreeWidgetExt->addRootItem(u8"COOKIE");
    pRoot1 = m_pQTreeWidgetExt->addRootItem(u8"收藏夹记录");


    //m_pQTreeWidgetExt->hideLowestChildenExpendBtn();
    m_pQTreeWidgetExt->setAllCheckable(true);
    m_pQTreeWidgetExt->setCheckBoxLeftMargin(15);
    //m_pQTreeWidgetExt->setAllBtnArrowIcon(":/img/images/14px-16收起.png");
    m_pQTreeWidgetExt->setAllExtraBtnIcon(u8":/image/开始.png");

    //设置无边框
    ui->widget->layout()->addWidget(m_pQTreeWidgetExt);
    //ui->widget_itemcheck_left->setWindowFlags(Qt::FramelessWindowHint);
    m_pQTreeWidgetExt->setWindowFlags(Qt::FramelessWindowHint);


}

MainWindow::~MainWindow()
{
    delete ui;
}


