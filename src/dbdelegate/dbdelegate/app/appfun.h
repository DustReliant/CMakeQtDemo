#ifndef APPFUN_H
#define APPFUN_H

#include "head.h"

class AppFun
{
public:
    //委托下拉框串口号
    static QStringList portName;
    //列名集合
    static QStringList columnNames;
    //列宽集合
    static QList<int> columnWidth;

    //行高
    static int rowHeight;
    //行数
    static int rowCount;
    //列数
    static int columnCount;

    //复选框选中文本
    static QString checkBoxChecked;
    //复选框未选中文本
    static QString checkBoxUnchecked;
    //随机生成列对应文本值
    static QString getText(int column);

    //获取和插入标准项
    static QStandardItem *getStandardItem(int column);
    static void insertStandardItem(QStandardItemModel *itemModel, int row);

    //获取和插入表格项
    static QTableWidgetItem *getTableWidgetItem(int column);
    static void insertTableWidgetItem(QTableWidget *tableWidget, int row);

    //获取和插入树状项
    static QTreeWidgetItem *getTreeWidgetItem(int column);
    static void insertTreeWidgetItem(QTreeWidget *treeWidget, int row);

    //初始化表格控件
    static void initTableView(QTableView *tableView);
    //初始化树状控件
    static void initTreeView(QTreeView *treeView);

    //自定义委托集合
    static QList<DbDelegate *> delegates;
    //初始化自定义委托
    static void initDelegate(QWidget *widget, QAbstractItemView *itemView, int delegateLevel = 0);
};

#endif // APPFUN_H
