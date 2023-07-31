# 环境
+ Qt 5.15.2 
+ 开源TinyXML2.6.2

### 写入
深度优先遍历（Depth-First Search，DFS）和广度优先遍历（Breadth-First Search，BFS）是图的两种常见的遍历算法，都可以用于处理树状数据结构。

深度优先遍历: 在这种遍历方式中，我们首先访问节点的一个子节点，然后再访问这个子节点的一个子节点，即我们深入访问每一个节点的子节点，直到一个节点没有子节点，然后返回到上一层访问其他子节点。这种方法与递归实现的方式基本相同。
```C++
void loadTreeFromXML_BFS(QTreeWidget *treeWidget, const std::string &filename)
{
    TiXmlDocument doc;
    if (!doc.LoadFile(filename))
    {
        std::cerr << "Could not load file " << filename << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement("Items");
    if (root == nullptr)
    {
        std::cerr << "No root element named 'Items' found" << std::endl;
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

void saveTreeToXML_BFS(QTreeWidget *treeWidget, const std::string &filename)
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
        element->SetAttribute("text", item->text(0).toStdString());
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
            childElement->SetAttribute("text", child->text(0).toStdString());
            xmlElement->LinkEndChild(childElement);
            queue.push({child, childElement});
        }
    }

    doc.SaveFile(filename);
}

```
广度优先遍历: 在这种遍历方式中，我们首先访问节点的所有子节点，然后再访问这些子节点的所有子节点，即我们逐层向下访问节点的子节点。这种方法通常需要一个队列来保存待访问的节点。

### 读取

读取XML文件也可以使用深度优先遍历和广度优先遍历。

深度优先遍历：使用递归的方式进行深度优先遍历是最直观的。递归函数将处理当前XML元素（包括它的文本和属性），然后对其每一个子元素进行递归处理。

广度优先遍历：使用队列（Queue）进行广度优先遍历。我们首先将根元素入队，然后进入一个循环：在每次循环中，我们取出队首的元素，处理这个元素，然后将这个元素的所有子元素入队。
```CPP
void saveTreeToXML_DFS(QTreeWidget *treeWidget, const std::string &filename)
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
        element->SetAttribute("text", item->text(0).toStdString());
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
            childElement->SetAttribute("text", child->text(0).toStdString());
            xmlElement->LinkEndChild(childElement);
            stack.push({child, childElement});
        }
    }

    doc.SaveFile(filename);
}


void loadTreeFromXML_DFS(QTreeWidget *treeWidget, const std::string &filename)
{
    TiXmlDocument doc;
    if (!doc.LoadFile(filename))
    {
        std::cerr << "Could not load file " << filename << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement("Items");
    if (root == nullptr)
    {
        std::cerr << "No root element named 'Items' found" << std::endl;
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
```