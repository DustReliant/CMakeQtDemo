#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <QModelIndex>
#include <QTableView>
#include <QStandardItem>
#include <QDateTime>
#include <QCheckBox>
#include <QStandardItemModel>
#include "qtableviewdelegate.h"

namespace Ui {
class TableView;
}

class TableView : public QWidget
{
    Q_OBJECT

public:
    explicit TableView(QWidget *parent = 0);
    ~TableView();

private:
    Ui::TableView *ui;
    //记住是否按下委托中的复选框
    bool ckPressed;
    //全选复选框
    QCheckBox *ckbox;
    //数据模型
    QStandardItemModel *itemModel;

private slots:
    void initForm();
    void initData();

private slots:
    //值改变信号
    void valueChanged(const QString &value);
    //按钮单击信号
    void buttonClicked(int btnIndex, const QModelIndex &index);

    //全选复选框改变信号
    void stateChanged(int arg1);
    //数据视图控件按下
    void pressed(const QModelIndex &index);

    //设置数据和显示数据
    void setData();
    void getData();


private:
    //初始化表格控件
    void initTableView(QTableView *tableView);
    //初始化自定义委托
    void initDelegate(QWidget *widget, QAbstractItemView *itemView, int delegateLevel = 0);
    //获取标准项
    QStandardItem *getStandardItem(int column);
    //插入标准项
    void insertStandardItem(QStandardItemModel *itemModel, int row);


    //随机生成列对应文本值
    QString getText(int column);

private:
    //行高
    int rowHeight = 25;
    //行数
    int rowCount = 12;
    //复选框选中文本
    QString checkBoxChecked = QString(u8"打开");
    //复选框未选中文本
    QString checkBoxUnchecked = QString(u8"关闭");
    //委托下拉框串口号
    QStringList portName = QStringList() << "COM1" << "COM2" << "COM3" << "COM4" << "COM5";
    //列宽集合
    QList<int> columnWidth = QList<int>() << 25 << 45 << 80 << 80 << 90 << 170 << 80 << 45 << 90 << 50 << 60 << 80 << 50;
    //列名集合
    QStringList columnNames = QStringList() << QString(u8"|状态|下拉框|密码框|颜色|日期时间|校验列|禁用|按钮|数值|映射|常驻列|进度条").split("|");
    //列数
    int columnCount = columnWidth.size();
};

#endif // TABLEVIEW_H
