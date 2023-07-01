#ifndef QTREEWIDGETEXT_H
#define QTREEWIDGETEXT_H

#include <QWidget>
#include <QMap>

class QTreeWidget;
class QTreeWidgetItem;
class QTreeItemCheckWidget;

class QTreeWidgetExt : public QWidget
{
    Q_OBJECT
public:
    explicit QTreeWidgetExt(QWidget *parent = 0);
    ~QTreeWidgetExt();

    //设置节点左边距
    //顶级节点为nLeftMargin，二级节点为2*nLeftMargin···N级节点为N*nLeftMargin（自动运算设置）
    void setItemLeftMargin(int nLeftMargin);

    int getItemLeftMargin() const;

    //添加最顶层节点
    QTreeWidgetItem* addRootItem(const QString &strText, int nColumn = 0);

    //添加节点
    QTreeWidgetItem* addItem(QTreeWidgetItem* pParentItem, const QString &strText, int nColumn = 0);

    //删除单个节点（返回其父节点）
    QTreeWidgetItem* removeItem(QTreeWidgetItem* pItem, int nColumn = 0);

    //删除所有节点
    void removeAllItem();

    //根据checkbox的文本内容获取节点
    QTreeWidgetItem* getItemByText(const QString &strText);

    //根据item获取CheckWidget
    QTreeItemCheckWidget* getCheckWidget(QTreeWidgetItem* pItem);

    //获取文本内容
    QString getItemText(QTreeWidgetItem* pItem);

    bool setItemText(QTreeWidgetItem* pItem, const QString &strText);

    //获取当前选中的节点
    QTreeWidgetItem* getCurrentSelectedItem();

    //获取所有checkbox勾选的节点
    QList<QTreeWidgetItem*> getAllCheckedItem();

    //获取所有节点
    QList<QTreeWidgetItem*> getAllItem();

    //获取某个节点的最顶层父节点
    QTreeWidgetItem* getTopParentItem(QTreeWidgetItem* pItem);

    //设置一个节点为当前节点
    void setCurrentItem(QTreeWidgetItem* pItem);

    //获取checkbox的文本内容
    QString getCheckBoxTitle(QTreeWidgetItem* pItem);

    //设置checkbox的文本内容
    void setCheckBoxTitle(QTreeWidgetItem* pItem, QString sTitle);

    //判断checkbox是否勾选
    bool isChecked(QTreeWidgetItem* pItem);

    //设置checkbox勾选状态
    void setChecked(QTreeWidgetItem* pItem, bool bChecked);

    //设置单个checkbox是否允许勾选
    void setCheckable(QTreeWidgetItem* pItem, bool bCheckable);

    //设置所有checkbox是否允许勾选
    void setAllCheckable(bool bCheckable);

    //设置checkbox左边距
    void setCheckBoxLeftMargin(int nLength);

//    //设置单个checkbox勾选和未勾选的图标
//    void setCheckBoxIcon(QTreeWidgetItem* pItem, QString sImgPathChecked, QString sImgPathUnchecked);

    //设置所有checkbox勾选和未勾选图标
    //void setCheckBoxIconAll(QString sImgPathChecked, QString sImgPathUnchecked);

    //设置单个节点的展开箭头按钮图标
    void setBtnArrowIcon(QTreeWidgetItem* pItem, const QString &strImgPath);

    //设置所有节点的展开箭头按钮图标
    void setAllBtnArrowIcon(const QString &strImgPath);

    //设置单个节点的展开箭头按钮可见
    void setBtnArrowVisible(QTreeWidgetItem* pItem, bool bVisible);

    //设置所有节点的展开箭头按钮可见
    void setAllBtnArrowVisible(bool bVisible);

    //设置最底层节点的展开箭头按钮可见
    void setLowertChildenBtnArrowVisible(bool bVisible);/* hideLowestChildenExpendBtn();*/

//    //显示单个节点的展开按钮
//    void showExpendBtn(QTreeWidgetItem* pItem);

//    //显示所有节点的展开按钮
//    void showExpendBtnAll();

    //设置单个节点额外按钮的图标
    void setBtnExtraIcon(QTreeWidgetItem* pItem, const QString &strImgPath);

    //设置所有节点额外按钮的图标
    void setAllExtraBtnIcon(const QString &strImgPath);

    //设置单个节点的额外按钮可见
    void setBtnExtraVisible(QTreeWidgetItem* pItem, bool bVisible);

    //设置所有节点的额外按钮可见
    void setAllBtnExtraVisible(bool bVisible);

//    //显示单个节点的额外按钮
//    void showExtraBtn(QTreeWidgetItem* pItem);

//    //显示所有节点的额外按钮
//    void showExtraBtnAll();

    //设置单个节点的文本颜色
    void setTextColor(QTreeWidgetItem* pItem, const QColor &oColor);

    //设置所有节点的文本颜色
    void setAllTextColor(const QColor &oColor);

    //设置所有子项是否展开
    void setAllExpendItem(bool bExpand);

    //处理checkbox勾选
    void doCheckBoxChanged(QTreeWidgetItem* pItem);



signals:
    //单击item的信号
    void signalItemClick(QTreeWidgetItem*, int);

    //双击item的信号
    void signalItemDoubleClick(QTreeWidgetItem*, int);

    //点击checkbox的信号
    void signalClickCheckBox(QTreeWidgetItem*);

    //点击展开按钮的信号
    void signalClickBtnExpend(QTreeWidgetItem*);

    //点击额外按钮的信号
    void signalClickBtnExtra(QTreeWidgetItem*);

    //鼠标进入item的信号
    void signalMouseEnterItem(QTreeWidgetItem*);

    //鼠标离开item的信号
    void signalMouseLeaveItem(QTreeWidgetItem*);






public slots:
    //checkbox勾选
    void slotCheckBoxClicked(QTreeWidgetItem* pItem, bool bChecked);

    //点击展开按钮的信号
    //void slotClickedBtnExpend(QTreeWidgetItem* pItem);

    //点击额外按钮的信号
    void slotClickedBtnExtra(QTreeWidgetItem* pItem);

protected:
    //设置子节点checkbox勾选
    void updateChilderCheckState(QTreeWidgetItem *pItem, bool bChecked);

    //设置父节点checkbox勾选
    void updateParentCheckState(QTreeWidgetItem *pItem);

    //更新节点展开图标
    void updateItemExpandedIcon(QTreeWidgetItem *pItem);

    void updateChilderExpandedIcon(QTreeWidgetItem *pItem);

    //设置父节点checkbox勾选
    void updateParentExpandedIcon(QTreeWidgetItem *pItem);


    void treeItemChanged(QTreeWidgetItem*pItem);

protected:
    QTreeWidget *m_pQTreeWidget;
    bool m_bIsAllowChecked;
    QMap<QTreeWidgetItem*, QTreeItemCheckWidget*> m_mapTreeItem2CheckWidget;
    int m_nItemLeftMargin;
public:
    bool m_bHideFlag;
};

#endif // QTREEWIDGETEXT_H
