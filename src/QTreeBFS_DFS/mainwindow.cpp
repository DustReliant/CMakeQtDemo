
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->mButtonLoad,&QPushButton::clicked,this,&MainWindow::onLoadButtonClicked);
    connect(ui->mButtonSave,&QPushButton::clicked,this,&MainWindow::onSaveButtonClicked);

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);   //使得该控件可以支持右键菜单
    connect(ui->treeWidget,&QTreeWidget::customContextMenuRequested,this,&MainWindow::onCustomContextMenuRequested);
    m_pMenu = new QMenu();
    add_menu = m_pMenu->addAction(u8"添加");
    delete_menu = m_pMenu->addAction(u8"删除");

    connect(add_menu,&QAction::triggered,this,&MainWindow::onADD);
    connect(delete_menu,&QAction::triggered,this,&MainWindow::onDelete);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveItem(TiXmlElement *xmlElement, QTreeWidgetItem *item)
{
    TiXmlElement *element = new TiXmlElement("Item");
    element->SetAttribute("text", item->text(0).toStdString().c_str());
    xmlElement->LinkEndChild(element);

    for (int i = 0; i < item->childCount(); ++i)
    {
        saveItem(element, item->child(i));
    }
}

void MainWindow::saveTreeToXML(QTreeWidget *treeWidget, const std::string &filename)
{
    TiXmlDocument doc;
    TiXmlElement *root = new TiXmlElement("Items");
    doc.LinkEndChild(root);

    int topCount = treeWidget->topLevelItemCount();
    for (int i = 0; i < topCount; ++i)
    {
        saveItem(root, treeWidget->topLevelItem(i));
    }

    doc.SaveFile(filename.c_str());
}

void MainWindow::loadItem(TiXmlElement *xmlElement, QTreeWidgetItem *item)
{
    for (TiXmlElement *element = xmlElement->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
    {
        QTreeWidgetItem *childItem = new QTreeWidgetItem(item);
        childItem->setText(0, QString::fromStdString(element->Attribute("text")));
        loadItem(element, childItem);
    }
}

void MainWindow::loadTreeFromXML(QTreeWidget *treeWidget, const std::string &filename)
{
    TiXmlDocument doc(filename.c_str());
    if (!doc.LoadFile())
    {

        return;
    }

    TiXmlElement *root = doc.RootElement();
    for (TiXmlElement *element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
        item->setText(0, QString::fromStdString(element->Attribute("text")));
        loadItem(element, item);
    }
}

void MainWindow::loadTreeFromXML_BFS(QTreeWidget *treeWidget, const std::string &filename)
{
    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str()))
    {
        //std::cerr << "Could not load file " << filename << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement("Items");
    if (root == nullptr)
    {
        //std::cerr << "No root element named 'Items' found" << std::endl;
        return;
    }

    std::queue<std::pair<QTreeWidgetItem *, TiXmlElement *>> queue;
    for (TiXmlElement *child = root->FirstChildElement("Item"); child != nullptr; child = child->NextSiblingElement("Item"))
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, QString::fromStdString(child->Attribute("text")));
        treeWidget->addTopLevelItem(item);
        queue.push({item, child});
    }

    while (!queue.empty())
    {
        auto [item, xmlElement] = queue.front();
        queue.pop();

        for (TiXmlElement *xmlChild = xmlElement->FirstChildElement("Item"); xmlChild != nullptr; xmlChild = xmlChild->NextSiblingElement("Item"))
        {
            QTreeWidgetItem *child = new QTreeWidgetItem;
            child->setText(0, QString::fromStdString(xmlChild->Attribute("text")));
            item->addChild(child);
            queue.push({child, xmlChild});
        }
    }
}

void MainWindow::saveTreeToXML_BFS(QTreeWidget *treeWidget, const std::string &filename)
{
    TiXmlDocument doc;
    TiXmlElement *root = new TiXmlElement("Items");
    doc.LinkEndChild(root);

    std::queue<std::pair<QTreeWidgetItem *, TiXmlElement *>> queue;
    int topCount = treeWidget->topLevelItemCount();
    for (int i = 0; i < topCount; ++i)
    {
        QTreeWidgetItem *item = treeWidget->topLevelItem(i);
        TiXmlElement *element = new TiXmlElement("Item");
        element->SetAttribute("text", item->text(0).toStdString().c_str());
        root->LinkEndChild(element);
        queue.push({item, element});
    }

    while (!queue.empty())
    {
        auto [item, xmlElement] = queue.front();
        queue.pop();

        for (int i = 0; i < item->childCount(); ++i)
        {
            QTreeWidgetItem *child = item->child(i);
            TiXmlElement *childElement = new TiXmlElement("Item");
            childElement->SetAttribute("text", child->text(0).toStdString().c_str());
            xmlElement->LinkEndChild(childElement);
            queue.push({child, childElement});
        }
    }

    doc.SaveFile(filename.c_str());
}

void MainWindow::loadTreeFromXML_DFS(QTreeWidget *treeWidget, const std::string &filename)
{

    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str()))
    {
        return;
    }

    TiXmlElement *root = doc.FirstChildElement("Items");
    if (root == nullptr)
    {
        return;
    }

    std::stack<std::pair<QTreeWidgetItem *, TiXmlElement *>> stack;
    for (TiXmlElement *child = root->FirstChildElement("Item"); child != nullptr; child = child->NextSiblingElement("Item"))
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, QString::fromStdString(child->Attribute("text")));
        treeWidget->addTopLevelItem(item);
        stack.push({item, child});
    }

    while (!stack.empty())
    {
        auto [item, xmlElement] = stack.top();
        stack.pop();

        for (TiXmlElement *xmlChild = xmlElement->FirstChildElement("Item"); xmlChild != nullptr; xmlChild = xmlChild->NextSiblingElement("Item"))
        {
            QTreeWidgetItem *child = new QTreeWidgetItem;
            child->setText(0, QString::fromStdString(xmlChild->Attribute("text")));
            item->addChild(child);
            stack.push({child, xmlChild});
        }
    }
}

void MainWindow::saveTreeToXML_DFS(QTreeWidget *treeWidget, const std::string &filename)
{
    TiXmlDocument doc;
    TiXmlElement *root = new TiXmlElement("Items");
    doc.LinkEndChild(root);

    std::stack<std::pair<QTreeWidgetItem *, TiXmlElement *>> stack;
    int topCount = treeWidget->topLevelItemCount();
    for (int i = 0; i < topCount; ++i)
    {
        QTreeWidgetItem *item = treeWidget->topLevelItem(i);
        TiXmlElement *element = new TiXmlElement("Item");
        element->SetAttribute("text", item->text(0).toStdString().c_str());
        root->LinkEndChild(element);
        stack.push({item, element});
    }

    while (!stack.empty())
    {
        auto [item, xmlElement] = stack.top();
        stack.pop();

        for (int i = item->childCount() - 1; i >= 0; --i)
        {
            QTreeWidgetItem *child = item->child(i);
            TiXmlElement *childElement = new TiXmlElement("Item");
            childElement->SetAttribute("text", child->text(0).toStdString().c_str());
            xmlElement->LinkEndChild(childElement);
            stack.push({child, childElement});
        }
    }

    doc.SaveFile(filename.c_str());
}



void MainWindow::onLoadButtonClicked()
{
    ui->treeWidget->clear();
    //loadTreeFromXML(ui->treeWidget,"test.xml");

    //loadTreeFromXML_BFS(ui->treeWidget,"testBFS.xml");

    loadTreeFromXML_DFS(ui->treeWidget,"testDFS.xml");
}


void MainWindow::onSaveButtonClicked()
{
    saveTreeToXML(ui->treeWidget,"test.xml");

    saveTreeToXML_BFS(ui->treeWidget,"testBFS.xml");

    saveTreeToXML_DFS(ui->treeWidget,"testDFS.xml");
}

void MainWindow::onCustomContextMenuRequested(const QPoint &pos)
{
    m_pMenu->exec(QCursor::pos());
}

void MainWindow::onADD()
{
//    Dialog* dlg = new Dialog(this);
//    dlg->setModal(true);
//    connect(dlg,&Dialog::sendData,this,&MainWindow::onData);
//    dlg->show();
}

void MainWindow::onDelete()
{

}

void MainWindow::onData(const QString &name, const QString &value)
{
    // 创建根节点


    //（未完成 不重要）
    QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0, name);
    root->setText(1, value);
    root->setData(2, Qt::UserRole, "root data");


    QTreeWidgetItem* currentItem = ui->treeWidget->currentItem();
    ui->treeWidget->addTopLevelItem(currentItem);

}

