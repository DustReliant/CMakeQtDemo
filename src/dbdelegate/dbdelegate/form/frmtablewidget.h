#ifndef FRMTABLEWIDGET_H
#define FRMTABLEWIDGET_H

#include <QWidget>
#include <QModelIndex>
class QCheckBox;

namespace Ui {
class frmTableWidget;
}

class frmTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmTableWidget(QWidget *parent = 0);
    ~frmTableWidget();

private:
    Ui::frmTableWidget *ui;
    //记住是否按下委托中的复选框
    bool ckPressed;
    //全选复选框
    QCheckBox *ckbox;

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
};

#endif // FRMTABLEWIDGET_H
