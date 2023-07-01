#include "frmtreewidget.h"
#include "ui_frmtreewidget.h"
#include "quihelper.h"

frmTreeWidget::frmTreeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmTreeWidget)
{
    ui->setupUi(this);
    this->initForm();
    this->initData();
}

frmTreeWidget::~frmTreeWidget()
{
    delete ui;
}

void frmTreeWidget::initForm()
{
    //复选框用于全选
    ckPressed = false;
    ckbox = new QCheckBox(ui->treeWidget);
    ckbox->setCheckState(Qt::PartiallyChecked);
    connect(ckbox, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    ckbox->move(6, 6);

    connect(ui->treeWidget, SIGNAL(pressed(QModelIndex)), this, SLOT(pressed(QModelIndex)));
    connect(ui->btnSetData, SIGNAL(clicked(bool)), this, SLOT(setData()));
    connect(ui->btnGetData, SIGNAL(clicked(bool)), this, SLOT(getData()));
}

void frmTreeWidget::initData()
{
    //ui->treeWidget->setRowCount(2);
    ui->treeWidget->setColumnCount(AppFun::columnCount);
    ui->treeWidget->setHeaderLabels(AppFun::columnNames);
    AppFun::initTreeView(ui->treeWidget);

    //这里有个左侧距离要注意下
    ui->treeWidget->setIndentation(0);
    int indentation = ui->treeWidget->indentation();
    ui->treeWidget->setColumnWidth(0, AppFun::columnWidth.at(0) + indentation * 2);
    ckbox->move(6 + indentation, 6);

    //设置列宽,一定要放在后面,不然如果还没有setModel就设置列宽是不行的
    for (int i = 1; i < AppFun::columnCount; ++i) {
        ui->treeWidget->setColumnWidth(i, AppFun::columnWidth.at(i));
    }

    //设置层级1
    QStringList list1, list2;
    for (int i = 0; i < AppFun::columnCount; ++i) {
        list1 << AppFun::getText(i);
        list2 << AppFun::getText(i);
    }

    QTreeWidgetItem *item0 = new QTreeWidgetItem(list1);
    QTreeWidgetItem *item1 = new QTreeWidgetItem(list2);
    ui->treeWidget->addTopLevelItem(item0);
    ui->treeWidget->addTopLevelItem(item1);
    item0->setTextAlignment(7, Qt::AlignCenter);
    item0->setText(0, "");
    item1->setText(0, "");

    //设置层级2
    for (int i = 0; i < AppFun::rowCount; ++i) {
        QStringList list;
        for (int column = 0; column < AppFun::columnCount; column++) {
            list << AppFun::getText(column);
        }

        QTreeWidgetItem *item = new QTreeWidgetItem(list);
        //一定要手动设置可编辑否则不能应用委托
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setTextAlignment(7, Qt::AlignCenter);
        item0->addChild(item);
    }

    //设置委托,带设置委托的层级,1表示从第二层开始应用委托
    AppFun::initDelegate(this, ui->treeWidget, 1);

    //一直显示下拉框 其他控件可以依葫芦画瓢
    for (int row = 0; row < AppFun::rowCount; row++) {
        QComboBox *cbox = new QComboBox;
        cbox->addItems(AppFun::portName);
        QTreeWidgetItem *item = item0->child(row);
        cbox->setCurrentIndex(cbox->findText(item->text(11)));
        ui->treeWidget->setItemWidget(item, 11, cbox);
    }

    //展开所有节点
    ui->treeWidget->expandAll();
}

void frmTreeWidget::valueChanged(const QString &value)
{
    QModelIndex index = ui->treeWidget->currentIndex();
    QString text = QString("当前数据: %1  行: %2  列: %3").arg(value).arg(index.row()).arg(index.column());
    ui->labInfo->setText(text);

    //其他处理比如自动计算全选复选框状态,联动设定其他值等
    DbDelegate *delegate = (DbDelegate *)sender();
    QString objName = delegate->objectName();
    QTreeWidgetItem *item0 = ui->treeWidget->topLevelItem(0);
    if (objName == "d_checkbox") {
        //统计有多少选中的设置全选复选框不同的样式
        int count = 0;
        for (int i = 0; i < AppFun::rowCount; ++i) {
            QString text = item0->child(i)->text(0);
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
        QTreeWidgetItem *item = item0->child(index.row());
        item->setText(12, value);
    }
}

void frmTreeWidget::buttonClicked(int btnIndex, const QModelIndex &index)
{
    //自己拿到按钮对应的索引+行列 处理操作
    QString text = QString("按钮索引: %1  行: %2  列: %3").arg(btnIndex).arg(index.row()).arg(index.column());
    ui->labInfo->setText(text);
}

void frmTreeWidget::stateChanged(int arg1)
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
    QTreeWidgetItem *item0 = ui->treeWidget->topLevelItem(0);
    for (int i = 0; i < AppFun::rowCount; ++i) {
        item0->child(i)->setText(0, text);
    }
}

void frmTreeWidget::pressed(const QModelIndex &index)
{
    if (index.column() == 4 && index.parent().isValid()) {
        int row = index.row();
        QColor color = QColorDialog::getColor(index.data().toString(), this, "选择颜色");
        if (color.isValid()) {
            QString name = color.name().toUpper();
            QTreeWidgetItem *item0 = ui->treeWidget->topLevelItem(0);
            item0->child(row)->setText(4, name);
        }
    }
}

void frmTreeWidget::setData()
{
    //设置好以后会自动反应到界面上
    QTreeWidgetItem *item0 = ui->treeWidget->topLevelItem(0);
    QString text = item0->child(0)->text(0);
    text = (text == AppFun::checkBoxChecked ? AppFun::checkBoxUnchecked : AppFun::checkBoxChecked);
    item0->child(0)->setText(0, text);

    text = QString::number(rand() % 100);
    item0->child(0)->setText(9, text);
    item0->child(0)->setText(12, text);
}

void frmTreeWidget::getData()
{
    ui->txtMain->clear();
    QTreeWidgetItem *item0 = ui->treeWidget->topLevelItem(0);
    for (int i = 0; i < AppFun::rowCount; ++i) {
        QStringList list;
        for (int j = 0; j < AppFun::columnCount; ++j) {
            QString text;
            if (j == 11) {
                //常驻列要单独获取
                QComboBox *cbox = (QComboBox *)ui->treeWidget->itemWidget(item0->child(i), j);
                text = cbox->currentText();
            } else {
                text = item0->child(i)->text(j);
            }
            text = text + ((j >= 3 && j <= 9) ? "\t" : "  ");
            list << text;
        }
        ui->txtMain->append(list.join(""));
    }
}
