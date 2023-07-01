#include "qtreewidgetext.h"
#include "qtreeitemcheckwidget.h"

#include <QTreeWidgetItem>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>

QTreeWidgetExt::QTreeWidgetExt(QWidget *parent) : QWidget(parent)
{
    m_pQTreeWidget = new QTreeWidget(this);
    QHBoxLayout* pHLayout = new QHBoxLayout(this);
    pHLayout->setContentsMargins(0, 0, 0, 0);
    pHLayout->addWidget(m_pQTreeWidget);

    setItemLeftMargin(10);

    m_bHideFlag = false;

    //隐藏头部
    m_pQTreeWidget->setHeaderHidden(true);
    m_pQTreeWidget->setIndentation(0);
    m_pQTreeWidget->setRootIsDecorated(false);

    //隐藏所有子节点下拉箭头
    m_pQTreeWidget->setStyleSheet("QTreeWidget::branch:has-children:!has-siblings:closed,\
                                  QTreeWidget::branch:closed:has-children:has-siblings{border-image: none; image: none;}\
                                  QTreeWidget::branch:open:has-children:!has-siblings,\
                                  QTreeWidget::branch:open:has-children:has-siblings{border-image: none; image: none;}\\");

}

QTreeWidgetExt::~QTreeWidgetExt()
{

}

void QTreeWidgetExt::setItemLeftMargin(int nLeftMargin)
{
    m_nItemLeftMargin = nLeftMargin;
}

int QTreeWidgetExt::getItemLeftMargin() const
{
    return m_nItemLeftMargin;
}

//添加最顶层节点
QTreeWidgetItem* QTreeWidgetExt::addRootItem(const QString &strText, int nColumn)
{
    QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pQTreeWidget);
//    pItem->setText(nColumn, strText);

    QTreeItemCheckWidget* pCheckWidget = new QTreeItemCheckWidget(strText, pItem, m_pQTreeWidget);
    pCheckWidget->setLeftMargin(getItemLeftMargin());


    if (m_bIsAllowChecked)
    {
        pCheckWidget->getCheckBox()->setStyleSheet("");
    }
    else
    {
        pCheckWidget->getCheckBox()->setStyleSheet("QCheckBox#checkBox_treeitem_title::indicator{width: 0px;}");
    }
    if(m_bHideFlag==true){
        pCheckWidget->getCheckBox()->setStyleSheet("#checkBox::indicator{width: 0px;}");
        pCheckWidget->getBtnExtra()->hide();
    }
    m_pQTreeWidget->setItemWidget(pItem, nColumn, pCheckWidget);
    m_mapTreeItem2CheckWidget[pItem] = pCheckWidget;

    connect(pCheckWidget, SIGNAL(signalCheckBoxClicked(QTreeWidgetItem*, bool)), this, SLOT(slotCheckBoxClicked(QTreeWidgetItem*, bool)));
    connect(pCheckWidget, SIGNAL(signalBtnExtraClick(QTreeWidgetItem*)), this, SIGNAL(slotClickedBtnExtra(QTreeWidgetItem*)));
    connect(pCheckWidget, SIGNAL(signalMouseEnter(QTreeWidgetItem*)), this, SIGNAL(signalMouseEnterItem(QTreeWidgetItem*)));
    connect(pCheckWidget, SIGNAL(signalMouseLeave(QTreeWidgetItem*)), this, SIGNAL(signalMouseLeaveItem(QTreeWidgetItem*)));
    //connect(pCheckWidget,SIGNAL(signalBtnExtraClick(QTreeWidgetItem*)),this,SLOT(slotClickedBtnExpend(QTreeWidgetItem*)));


	updateItemExpandedIcon(pItem);



    return pItem;
}

//添加节点
QTreeWidgetItem* QTreeWidgetExt::addItem(QTreeWidgetItem* pParentItem, const QString &strText, int nColumn)
{
    QTreeWidgetItem* pItem = new QTreeWidgetItem(pParentItem);
//    pItem->setText(nColumn, strText);

    QTreeItemCheckWidget* pCheckWidget = new QTreeItemCheckWidget(strText, pItem, m_pQTreeWidget);
    if (m_bIsAllowChecked)
    {
        pCheckWidget->getCheckBox()->setStyleSheet("");
    }
    else
    {
        pCheckWidget->getCheckBox()->setStyleSheet("QCheckBox#checkBox_treeitem_title::indicator{width: 0px;}");
    }
    if(m_bHideFlag==true)
    {
        pCheckWidget->getCheckBox()->setStyleSheet("#checkBox::indicator{width: 0px;}");
        pCheckWidget->getBtnExtra()->hide();
    }
    m_pQTreeWidget->setItemWidget(pItem, nColumn, pCheckWidget);
    m_mapTreeItem2CheckWidget[pItem] = pCheckWidget;

    connect(pCheckWidget, SIGNAL(signalCheckBoxClicked(QTreeWidgetItem*, bool)), this, SLOT(slotCheckBoxClicked(QTreeWidgetItem*, bool)));
    connect(pCheckWidget, SIGNAL(signalBtnExtraClick(QTreeWidgetItem*)), this, SLOT(slotClickedBtnExtra(QTreeWidgetItem*)));
    connect(pCheckWidget, SIGNAL(signalMouseEnter(QTreeWidgetItem*)), this, SIGNAL(signalMouseEnterItem(QTreeWidgetItem*)));
    connect(pCheckWidget, SIGNAL(signalMouseLeave(QTreeWidgetItem*)), this, SIGNAL(signalMouseLeaveItem(QTreeWidgetItem*)));

	updateItemExpandedIcon(pItem);

	int nLeftMargin = getItemLeftMargin();
	while (pParentItem != NULL) {
		nLeftMargin += getItemLeftMargin();
		pParentItem = pParentItem->parent();
	}

	pCheckWidget->setLeftMargin(nLeftMargin);
    

    return pItem;
}

//根据checkbox的文本内容获取节点
QTreeWidgetItem* QTreeWidgetExt::getItemByText(const QString &strText)
{
    QTreeWidgetItem* pRv = NULL;
    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
    {
        if (it.value()->getCheckBox()->text() == strText)
        {
            pRv = it.key();
        }
    }
    return pRv;
}

//根据item获取customItem
QTreeItemCheckWidget* QTreeWidgetExt::getCheckWidget(QTreeWidgetItem* pItem)
{
    if (false == m_mapTreeItem2CheckWidget.contains(pItem))
    {
        return NULL;
    }

    return m_mapTreeItem2CheckWidget.value(pItem);

    //    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
    //    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
    //    {
    //        if (it.key() == pItem)
    //        {
    //            return it.value();
    //        }
    //    }
    //    return NULL;
}

QString QTreeWidgetExt::getItemText(QTreeWidgetItem* pItem)
{
    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pItem);
    if (NULL == pCheckWidget)
    {
        return "";
    }

    return pCheckWidget->getText();
}

bool QTreeWidgetExt::setItemText(QTreeWidgetItem *pItem, const QString &strText)
{
    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pItem);
    if (NULL == pCheckWidget)
    {
        return false;
    }

    pCheckWidget->setText(strText);
    return true;
}

//获取当前选中的节点
QTreeWidgetItem* QTreeWidgetExt::getCurrentSelectedItem()
{
    return m_pQTreeWidget->currentItem();
}

//获取所有checkbox勾选的节点
QList<QTreeWidgetItem*> QTreeWidgetExt::getAllCheckedItem()
{
    QList<QTreeWidgetItem*> listCheckedItem;
    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
    {
        if (it.value()->getCheckBox()->checkState() == Qt::Checked)
        {
            listCheckedItem.append(it.key());
        }
    }
    return listCheckedItem;
}

//获取所有节点
QList<QTreeWidgetItem*> QTreeWidgetExt::getAllItem()
{
    QList<QTreeWidgetItem*> listItem;
    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
    {
        listItem.append(it.key());
    }
    return listItem;
}

//获取某个节点的最顶层父节点
QTreeWidgetItem* QTreeWidgetExt::getTopParentItem(QTreeWidgetItem* pItem)
{
    QTreeWidgetItem* pParent = pItem;
    while(pParent->parent() != NULL)
    {
        pParent = pParent->parent();
    }
    return pParent;
}

//设置一个节点为当前节点
void QTreeWidgetExt::setCurrentItem(QTreeWidgetItem* pItem)
{
    if (pItem == NULL && m_mapTreeItem2CheckWidget.contains(pItem) == false)
    {
        return;
    }
    m_pQTreeWidget->setCurrentItem(pItem);
    emit signalItemClick(pItem, 0);
}

////获取checkbox的文本内容
QString QTreeWidgetExt::getCheckBoxTitle(QTreeWidgetItem* pItem)
{
    return m_mapTreeItem2CheckWidget[pItem]->getCheckBox()->text();
}

////设置checkbox的文本内容
void QTreeWidgetExt::setCheckBoxTitle(QTreeWidgetItem* pItem, QString sTitle)
{
    m_mapTreeItem2CheckWidget[pItem]->getCheckBox()->setText(sTitle);
}

//判断checkbox是否勾选
bool QTreeWidgetExt::isChecked(QTreeWidgetItem* pItem)
{
    QTreeItemCheckWidget* pCheckWidget = getCheckWidget(pItem);
    if (NULL == pCheckWidget)
    {
        return false;
    }

    return pCheckWidget->isChecked();
}

//设置checkbox勾选状态
void QTreeWidgetExt::setChecked(QTreeWidgetItem* pItem, bool bChecked)
{
    QTreeItemCheckWidget* pCheckWidget = getCheckWidget(pItem);
    if (NULL == pCheckWidget)
    {
        return;
    }

    pCheckWidget->setChecked(bChecked);
}

//设置单个checkbox是否允许勾选
void QTreeWidgetExt::setCheckable(QTreeWidgetItem* pItem, bool bCheckable)
{
    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pItem);
    if (NULL == pCheckWidget)
    {
        return;
    }

    pCheckWidget->setCheckable(bCheckable);
    //    m_bIsAllowChecked = bIsAllow;

    //    if (m_bIsAllowChecked)
    //    {
    //        m_mapTreeItem2CheckWidget[pItem]->getCheckBox()->setStyleSheet("");
    //    }
    //    else
    //    {
    //        m_mapTreeItem2CheckWidget[pItem]->getCheckBox()->setStyleSheet("QCheckBox#checkBox_treeitem_title::indicator{width: 0px;}");
    //    }
}

//设置所有checkbox是否允许勾选
void QTreeWidgetExt::setAllCheckable(bool bCheckable)
{
    //    m_bIsAllowChecked = bIsAllow;


    QList<QTreeItemCheckWidget*> listTreeItem = m_mapTreeItem2CheckWidget.values();
    QListIterator<QTreeItemCheckWidget*> iter(listTreeItem);
    while (iter.hasNext())
    {
        QTreeItemCheckWidget *pCheckWidget = iter.next();
        if (pCheckWidget)
        {
            pCheckWidget->setCheckable(bCheckable);
        }
    }

    //    QList<QTreeItemCheckWidget*>::iterator it = listTreeItem.begin();
    //    for(; it != listTreeItem.end(); it++)
    //    {
    //        if (m_bIsAllowChecked)
    //        {
    //            (*it)->getCheckBox()->setStyleSheet("");
    //        }
    //        else
    //        {
    //            (*it)->getCheckBox()->setStyleSheet("QCheckBox#checkBox_treeitem_title::indicator{width: 0px;}");
    //        }
    //    }
}


//设置checkbox左边距
void QTreeWidgetExt::setCheckBoxLeftMargin(int nLength)
{
    QString sLength = QString::number(nLength);
    QString sNewStyleSheet = "QTreeWidget::item{margin-left:" + sLength + "px;}";
    QString sStyleSheet = m_pQTreeWidget->styleSheet();
    m_pQTreeWidget->setStyleSheet(sStyleSheet + sNewStyleSheet);
}


//设置单个checkbox勾选和未勾选的图标
//void QTreeWidgetExt::setCheckBoxIcon(QTreeWidgetItem* pItem, QString sImgPathChecked, QString sImgPathUnchecked)
//{
//    QString sStyleSheet = "QCheckBox#checkBox_treeitem_title::indicator:checked{image:url(" + sImgPathChecked + ");} \
//            QCheckBox#checkBox_treeitem_title::indicator:unchecked{image:url(" + sImgPathUnchecked + ");}";

//            m_mapTreeItem2CheckWidget[pItem]->getCheckBox()->setStyleSheet(sStyleSheet);
//}

//设置所有checkbox勾选和未勾选图标
//void QTreeWidgetExt::setCheckBoxIconAll(QString sImgPathChecked, QString sImgPathUnchecked)
//{
//    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
//    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
//    {
//        setCheckBoxIcon(it.key(), sImgPathChecked, sImgPathUnchecked);
//    }
//}

//设置单个节点的展开箭头按钮图标
void QTreeWidgetExt::setBtnArrowIcon(QTreeWidgetItem* pItem, const QString &strImgPath)
{
    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pItem);
    if (NULL == pCheckWidget)
    {
        return;
    }

    pCheckWidget->getBtnArrow()->setIcon(QIcon(strImgPath));
    //    m_mapTreeItem2CheckWidget[pItem]->getBtnArrow()->setIcon(QIcon(strImgPath));
}

//设置所有节点的展开箭头按钮图标
void QTreeWidgetExt::setAllBtnArrowIcon(const QString &strImgPath)
{
    QList<QTreeWidgetItem*> listItem = m_mapTreeItem2CheckWidget.keys();
    QListIterator<QTreeWidgetItem*> iter(listItem);
    while (iter.hasNext())
    {
        QTreeWidgetItem* pItem = iter.next();
        setBtnArrowIcon(pItem, strImgPath);
    }

    //    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
    //    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
    //    {
    //        setBtnArrowIcon(it.key(), strImgPath);
    //    }
}

//设置单个节点的展开箭头按钮可见
void QTreeWidgetExt::setBtnArrowVisible(QTreeWidgetItem* pItem, bool bVisible)
{
    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pItem);
    if (NULL == pCheckWidget)
    {
        return;
    }

    pCheckWidget->getBtnArrow()->setVisible(bVisible);

    //    m_mapTreeItem2CheckWidget[pItem]->getBtnArrow()->hide();
}

//设置所有节点的展开箭头按钮可见
void QTreeWidgetExt::setAllBtnArrowVisible(bool bVisible)
{
    QList<QTreeWidgetItem*> listItem = m_mapTreeItem2CheckWidget.keys();
    QListIterator<QTreeWidgetItem*> iter(listItem);
    while (iter.hasNext())
    {
        QTreeWidgetItem* pItem = iter.next();
        setBtnArrowVisible(pItem, bVisible);
    }

    //    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
    //    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
    //    {
    //        hideExpendBtn(it.key());
    //    }
}

//隐藏最底层节点的展开按钮
void QTreeWidgetExt::setLowertChildenBtnArrowVisible(bool bVisible)
{
    QList<QTreeWidgetItem*> listItem = m_mapTreeItem2CheckWidget.keys();
    QListIterator<QTreeWidgetItem*> iter(listItem);
    while (iter.hasNext())
    {
        QTreeWidgetItem* pItem = iter.next();
        if (pItem->childCount() == 0)
        {
            setBtnArrowVisible(pItem, bVisible);
        }
    }

    //    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
    //    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
    //    {
    //        if (it.key()->childCount() == 0)
    //        {
    //            hideExpendBtn(it.key());
    //        }
    //    }
}

//显示单个节点的展开按钮
//void QTreeWidgetExt::showExpendBtn(QTreeWidgetItem* pItem)
//{
//    m_mapTreeItem2CheckWidget[pItem]->getBtnArrow()->show();
//}

//显示所有节点的展开按钮
//void QTreeWidgetExt::showExpendBtnAll()
//{
//    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
//    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
//    {
//        showExpendBtn(it.key());
//    }
//}

//设置单个节点额外按钮的图标
void QTreeWidgetExt::setBtnExtraIcon(QTreeWidgetItem* pItem, const QString &strImgPath)
{
    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pItem);
    if (NULL == pCheckWidget)
    {
        return;
    }

    pCheckWidget->getBtnExtra()->setIcon(QIcon(strImgPath));
//    m_mapTreeItem2CheckWidget[pItem]->getBtnExtra()->setIcon(QIcon(strImgPath));
}

//设置所有节点额外按钮的图标
void QTreeWidgetExt::setAllExtraBtnIcon(const QString &strImgPath)
{
    QList<QTreeWidgetItem*> listItem = m_mapTreeItem2CheckWidget.keys();
    QListIterator<QTreeWidgetItem*> iter(listItem);
    while (iter.hasNext())
    {
        QTreeWidgetItem* pItem = iter.next();
        setBtnExtraIcon(pItem, strImgPath);
    }


//    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
//    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
//    {
//        setExtraBtnIcon(it.key(), sImgPath);
//    }
}

//设置单个节点的额外按钮可见
void QTreeWidgetExt::setBtnExtraVisible(QTreeWidgetItem* pItem, bool bVisible)
{
    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pItem);
    if (NULL == pCheckWidget)
    {
        return;
    }

    pCheckWidget->getBtnExtra()->setVisible(bVisible);
//    m_mapTreeItem2CheckWidget[pItem]->getBtnExtra()->hide();
}

//设置所有节点的额外按钮可见
void QTreeWidgetExt::setAllBtnExtraVisible(bool bVisible)
{
    QList<QTreeWidgetItem*> listItem = m_mapTreeItem2CheckWidget.keys();
    QListIterator<QTreeWidgetItem*> iter(listItem);
    while (iter.hasNext())
    {
        QTreeWidgetItem* pItem = iter.next();
        setBtnExtraVisible(pItem, bVisible);
    }

//    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
//    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
//    {
//        setBtnExtraVisible(it.key());
//    }
}

////显示单个节点的额外按钮
//void QTreeWidgetExt::showExtraBtn(QTreeWidgetItem* pItem)
//{
//    m_mapTreeItem2CheckWidget[pItem]->getBtnExtra()->show();
//}

////显示所有节点的额外按钮
//void QTreeWidgetExt::showExtraBtnAll()
//{
//    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
//    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
//    {
//        showExtraBtn(it.key());
//    }
//}


//设置单个节点的文本颜色
void QTreeWidgetExt::setTextColor(QTreeWidgetItem* pItem, const QColor &oColor)
{
    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pItem);
    if (!pCheckWidget)
    {
        return;
    }

    pCheckWidget->setTextColor(oColor);


//    if(m_bHideFlag==true)
//    {
//        pCheckWidget->getCheckBox()->setStyleSheet(QString("#checkBox::indicator{width: 0px;} QCheckBox{color:%1;}").arg(oColor.name()));
//        pCheckWidget->getBtnExtra()->hide();
//    }
//    else
//    {
//        pCheckWidget->getCheckBox()->setStyleSheet(QString("QCheckBox{color:%1;}").arg(oColor.name()));
//        pCheckWidget->getBtnExtra()->hide();
//    }
}

//设置所有节点的文本颜色
void QTreeWidgetExt::setAllTextColor(const QColor &oColor)
{
    QList<QTreeWidgetItem*> listItem = m_mapTreeItem2CheckWidget.keys();
    QListIterator<QTreeWidgetItem*> iter(listItem);
    while (iter.hasNext())
    {
        QTreeWidgetItem* pItem = iter.next();
        setTextColor(pItem, oColor);
    }

//    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*>::iterator it = m_mapTreeItem2CheckWidget.begin();
//    for (; it != m_mapTreeItem2CheckWidget.end(); it++)
//    {
//        setTextColor(it.key(), oColor);
//    }
}

//设置所有子项是否展开
void QTreeWidgetExt::setAllExpendItem(bool bExpand)
{
    QMapIterator<QTreeWidgetItem*, QTreeItemCheckWidget*> iter(m_mapTreeItem2CheckWidget);

    while (iter.hasNext())
    {
        iter.next();
        QTreeWidgetItem* pItem = iter.key();
        pItem->setExpanded(bExpand);
        QTreeItemCheckWidget *pCheckWidget = iter.value();
        pCheckWidget->updateBtnExpandedIcon();
    }
}
//处理checkbox勾选
void QTreeWidgetExt::doCheckBoxChanged(QTreeWidgetItem *pItem)
{
    treeItemChanged(pItem);
}



void QTreeWidgetExt::slotCheckBoxClicked(QTreeWidgetItem *pItem, bool bChecked)
{
    if (pItem == NULL || m_mapTreeItem2CheckWidget.contains(pItem) == false)
    {
        return;
    }

    setCurrentItem(pItem);

    //设置子节点
    updateChilderCheckState(pItem, bChecked);

    //设置父节点
    updateParentCheckState(pItem);

    emit signalClickCheckBox(pItem);
}

//void QTreeWidgetExt::slotClickedBtnExpend(QTreeWidgetItem *pItem)
//{
//    m_pQTreeWidget->setCurrentItem(pItem);

//    if (pItem->isExpanded())
//    {
//        this->setBtnArrowIcon(pItem, ":img/images/14px-16收起.png");
//        pItem->setExpanded(false);
//    }
//    else
//    {
//        this->setBtnArrowIcon(pItem, ":img/images/14px-16展开.png");
//        pItem->setExpanded(true);

//    }
//}

void QTreeWidgetExt::slotClickedBtnExtra(QTreeWidgetItem *pItem)
{

}

void QTreeWidgetExt::updateChilderCheckState(QTreeWidgetItem *pItem, bool bChecked)
{
    if (pItem == NULL || pItem->childCount() == 0)
    {
        return;
    }

    int nChildCount = pItem->childCount();
    for (int nChildIndex = 0; nChildIndex < nChildCount; nChildIndex++)
    {
        QTreeWidgetItem* pChildItem = pItem->child(nChildIndex);
        QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pChildItem);
        if (pCheckWidget)
        {
            pCheckWidget->setChecked(bChecked);
            updateChilderCheckState(pChildItem, bChecked);
        }
    }
}

void QTreeWidgetExt::updateParentCheckState(QTreeWidgetItem *pItem)
{
    QTreeWidgetItem *pParentItem = pItem->parent();
    if (pItem == NULL || pParentItem == NULL)
    {
        return;
    }

    //子节点勾选中的数量
    int nChildCheckedCount = 0;
    int nChildCount = pParentItem->childCount();
    for (int nChildIndex = 0; nChildIndex < nChildCount; nChildIndex++)
    {
        QTreeWidgetItem* pChildItem = pParentItem->child(nChildIndex);
        QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pChildItem);
        if (pCheckWidget)
        {
            if (pCheckWidget->isChecked())
            {
                nChildCheckedCount++;
            }
        }
    }


    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pParentItem);
    if (pCheckWidget == NULL)
    {
        return;
    }

    //子节点全部勾选
    if (nChildCheckedCount == nChildCount)
    {
        pCheckWidget->setChecked(true);
    }
    else
    {
        pCheckWidget->setChecked(false);
    }

    updateParentCheckState(pParentItem);

}

void QTreeWidgetExt::updateItemExpandedIcon(QTreeWidgetItem *pItem)
{
    QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pItem);
    if (pCheckWidget == NULL)
    {
        return;
    }	

	//更新自己
	pCheckWidget->updateBtnExpandedIcon();	

	//更新子节点
    updateChilderExpandedIcon(pItem);

	//更新父节点
    updateParentExpandedIcon(pItem);


}

void QTreeWidgetExt::updateChilderExpandedIcon(QTreeWidgetItem *pItem)
{
    if (pItem == NULL)
    {
        return;
    }

    int nChildCount = pItem->childCount();
    for (int nChildIndex = 0; nChildIndex < nChildCount; nChildIndex++)
    {
        QTreeWidgetItem* pChildItem = pItem->child(nChildIndex);
        QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pChildItem);
        if (pCheckWidget != NULL)
        {
            pCheckWidget->updateBtnExpandedIcon();
        }

        updateChilderExpandedIcon(pChildItem);
    }
}

void QTreeWidgetExt::updateParentExpandedIcon(QTreeWidgetItem *pItem)
{
    if (pItem == NULL)
    {
        return;
    }

    QTreeWidgetItem *pParentItem = pItem->parent();
    while (pParentItem)
    {
        QTreeItemCheckWidget *pCheckWidget = getCheckWidget(pParentItem);
        if (pCheckWidget != NULL)
        {
            pCheckWidget->updateBtnExpandedIcon();
        }
        pParentItem = pParentItem->parent();
    }
}

void QTreeWidgetExt::treeItemChanged(QTreeWidgetItem *pItem)
{
    if (Qt::Checked == m_mapTreeItem2CheckWidget[pItem]->getCheckBox()->checkState())
    {
        int count = pItem->childCount();
        if (count > 0)
        {
            for (int i = 0; i < count; i++)
            {
                QTreeWidgetItem* pItemChild = pItem->child(i);
                m_mapTreeItem2CheckWidget[pItemChild]->getCheckBox()->setCheckState(Qt::Checked);
                treeItemChanged(pItemChild);
            }
        }
        else
        {
            updateParentCheckState(pItem);
        }
    }
    else if (Qt::Unchecked == m_mapTreeItem2CheckWidget[pItem]->getCheckBox()->checkState())
    {
        int count = pItem->childCount();
        if (count > 0)
        {
            for (int i = 0; i < count; i++)
            {
                QTreeWidgetItem* pItemChild = pItem->child(i);
                m_mapTreeItem2CheckWidget[pItemChild]->getCheckBox()->setCheckState(Qt::Unchecked);
                treeItemChanged(pItemChild);
            }
        }
        else
        {
            updateParentCheckState(pItem);
        }
    }
}
