#include "frmtreeview.h"
#include "ui_frmtreeview.h"
#include "quihelper.h"

frmTreeView::frmTreeView(QWidget *parent) : QWidget(parent), ui(new Ui::frmTreeView)
{
    ui->setupUi(this);
    this->initForm();
    this->initData();
}

frmTreeView::~frmTreeView()
{
    delete ui;
}

void frmTreeView::initForm()
{
    //复选框用于全选
    ckPressed = false;
    ckbox = new QCheckBox(ui->treeView);
    ckbox->setCheckState(Qt::PartiallyChecked);
    connect(ckbox, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    ckbox->move(6, 6);

    connect(ui->treeView, SIGNAL(pressed(QModelIndex)), this, SLOT(pressed(QModelIndex)));
    connect(ui->btnSetData, SIGNAL(clicked(bool)), this, SLOT(setData()));
    connect(ui->btnGetData, SIGNAL(clicked(bool)), this, SLOT(getData()));
}

void frmTreeView::initData()
{
    itemModel = new QStandardItemModel;
    itemModel->setRowCount(2);
    itemModel->setColumnCount(AppFun::columnCount);
    itemModel->setHorizontalHeaderLabels(AppFun::columnNames);
    ui->treeView->setModel(itemModel);
    AppFun::initTreeView(ui->treeView);

    //这里有个左侧距离要注意下
    ui->treeView->setIndentation(0);
    int indentation = ui->treeView->indentation();
    ui->treeView->setColumnWidth(0, AppFun::columnWidth.at(0) + indentation * 2);
    ckbox->move(6 + indentation, 6);

    //设置列宽,一定要放在后面,不然如果还没有setModel就设置列宽是不行的
    for (int i = 1; i < AppFun::columnCount; ++i) {
        ui->treeView->setColumnWidth(i, AppFun::columnWidth.at(i));
    }

    //设置层级1
    AppFun::insertStandardItem(itemModel, 0);
    AppFun::insertStandardItem(itemModel, 1);

    itemModel->item(0, 0)->setText("");
    itemModel->item(1, 0)->setText("");

    //设置层级2
    for (int i = 0; i < AppFun::rowCount; ++i) {
        QList<QStandardItem *> items;
        for (int column = 0; column < AppFun::columnCount; column++) {
            items << AppFun::getStandardItem(column);
        }
        itemModel->item(0, 0)->appendRow(items);
    }

    //设置委托,带设置委托的层级,1表示从第二层开始应用委托
    AppFun::initDelegate(this, ui->treeView, 1);

    //一直显示下拉框 其他控件可以依葫芦画瓢
    for (int row = 0; row < AppFun::rowCount; row++) {
        QComboBox *cbox = new QComboBox;
        cbox->addItems(AppFun::portName);
        QStandardItem *item = itemModel->item(0, 0)->child(row, 11);
        cbox->setCurrentIndex(cbox->findText(item->text()));
        ui->treeView->setIndexWidget(item->index(), cbox);
    }

    //设置离左侧的距离+展开所有节点
    ui->treeView->setIndentation(0);
    ui->treeView->expandAll();    
}

void frmTreeView::valueChanged(const QString &value)
{
    QModelIndex index = ui->treeView->currentIndex();
    QString text = QString("当前数据: %1  行: %2  列: %3").arg(value).arg(index.row()).arg(index.column());
    ui->labInfo->setText(text);

    //其他处理比如自动计算全选复选框状态,联动设定其他值等
    DbDelegate *delegate = (DbDelegate *)sender();
    QString objName = delegate->objectName();
    QStandardItem *item0 = itemModel->item(0, 0);
    if (objName == "d_checkbox") {
        //统计有多少选中的设置全选复选框不同的样式
        int count = 0;
        for (int i = 0; i < AppFun::rowCount; ++i) {
            QString text = item0->child(i, 0)->text();
            if (text == AppFun::checkBoxChecked) {
                count++;
            }
        }

        //定义标志位防止重复选择
        ckPressed = true;
        if (count == 0) {
            ckbox->setCheckState(Qt::Unchecked);
        } else if (AppFun::rowCount == count) {
            ckbox->setCheckState(Qt::Checked);
        } else {
            ckbox->setCheckState(Qt::PartiallyChecked);
        }
        ckPressed = false;
    } else if (objName == "d_spinbox") {
        //演示将对应的值设置成到进度条
        QStandardItem *item = item0->child(index.row(), 12);
        item->setText(value);
    }
}

void frmTreeView::buttonClicked(int btnIndex, const QModelIndex &index)
{
    //自己拿到按钮对应的索引+行列 处理操作
    QString text = QString("按钮索引: %1  行: %2  列: %3").arg(btnIndex).arg(index.row()).arg(index.column());
    ui->labInfo->setText(text);
}

void frmTreeView::stateChanged(int arg1)
{
    //过滤委托中的复选框按下触发的改变
    if (ckPressed) {
        ckPressed = false;
        return;
    }

    //设置只能两态
    ckbox->setTristate(false);
    //如果选中则设置不选中的值
    QString text = (arg1 != 0 ? AppFun::checkBoxChecked : AppFun::checkBoxUnchecked);
    QStandardItem *item0 = itemModel->item(0, 0);
    for (int i = 0; i < AppFun::rowCount; ++i) {
        item0->child(i, 0)->setText(text);
    }
}

void frmTreeView::pressed(const QModelIndex &index)
{
    if (index.column() == 4 && index.parent().isValid()) {
        int row = index.row();
        QColor color = QColorDialog::getColor(index.data().toString(), this, "选择颜色");
        if (color.isValid()) {
            QString name = color.name().toUpper();
            QStandardItem *item0 = itemModel->item(0, 0);
            item0->child(row, 4)->setText(name);
        }
    }
}

void frmTreeView::setData()
{
    //设置好以后会自动反应到界面上
    QStandardItem *item0 = itemModel->item(0, 0);
    QString text = item0->child(0, 0)->text();
    text = (text == AppFun::checkBoxChecked ? AppFun::checkBoxUnchecked : AppFun::checkBoxChecked);
    item0->child(0, 0)->setText(text);

    text = QString::number(rand() % 100);
    item0->child(0, 9)->setText(text);
    item0->child(0, 12)->setText(text);
}

void frmTreeView::getData()
{
    ui->txtMain->clear();
    QStandardItem *item0 = itemModel->item(0, 0);
    for (int i = 0; i < AppFun::rowCount; ++i) {
        QStringList list;
        for (int j = 0; j < AppFun::columnCount; ++j) {
            QString text;
            if (j == 11) {
                //常驻列要单独获取
                QComboBox *cbox = (QComboBox *)ui->treeView->indexWidget(item0->child(i, j)->index());
                text = cbox->currentText();
            } else {
                text = item0->child(i, j)->text();
            }
            text = text + ((j >= 3 && j <= 9) ? "\t" : "  ");
            list << text;
        }
        ui->txtMain->append(list.join(""));
    }
}
