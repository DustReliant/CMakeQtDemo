#include "frmtableview.h"
#include "ui_frmtableview.h"
#include "quihelper.h"

frmTableView::frmTableView(QWidget *parent) : QWidget(parent), ui(new Ui::frmTableView)
{
    ui->setupUi(this);
    this->initForm();
    this->initData();
}

frmTableView::~frmTableView()
{
    delete ui;
}

void frmTableView::initForm()
{
    //复选框用于全选
    ckPressed = false;
    ckbox = new QCheckBox(ui->tableView);
    ckbox->setCheckState(Qt::PartiallyChecked);
    connect(ckbox, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    ckbox->move(6, 6);

    connect(ui->tableView, SIGNAL(pressed(QModelIndex)), this, SLOT(pressed(QModelIndex)));
    connect(ui->btnSetData, SIGNAL(clicked(bool)), this, SLOT(setData()));
    connect(ui->btnGetData, SIGNAL(clicked(bool)), this, SLOT(getData()));
}

void frmTableView::initData()
{
    itemModel = new QStandardItemModel;
    itemModel->setRowCount(AppFun::rowCount);
    itemModel->setColumnCount(AppFun::columnCount);
    itemModel->setHorizontalHeaderLabels(AppFun::columnNames);
    ui->tableView->setModel(itemModel);
    AppFun::initTableView(ui->tableView);

    //设置列宽,一定要放在后面,不然如果还没有setModel就设置列宽是不行的
    for (int i = 0; i < AppFun::columnCount; ++i) {
        ui->tableView->setColumnWidth(i, AppFun::columnWidth.at(i));
    }

    //设置行内容
    for (int i = 0; i < AppFun::rowCount; ++i) {
        AppFun::insertStandardItem(itemModel, i);
    }

    //设置委托
    AppFun::initDelegate(this, ui->tableView);

    //一直显示下拉框 其他控件可以依葫芦画瓢
    for (int row = 0; row < AppFun::rowCount; row++) {
        QComboBox *cbox = new QComboBox;
        cbox->addItems(AppFun::portName);
        QStandardItem *item = itemModel->item(row, 11);
        cbox->setCurrentIndex(cbox->findText(item->text()));
        ui->tableView->setIndexWidget(item->index(), cbox);
    }
}

void frmTableView::valueChanged(const QString &value)
{
    QModelIndex index = ui->tableView->currentIndex();
    QString text = QString("当前数据: %1  行: %2  列: %3").arg(value).arg(index.row()).arg(index.column());
    ui->labInfo->setText(text);

    //其他处理比如自动计算全选复选框状态,联动设定其他值等
    DbDelegate *delegate = (DbDelegate *)sender();
    QString objName = delegate->objectName();
    if (objName == "d_checkbox") {
        //统计有多少选中的设置全选复选框不同的样式
        int count = 0;
        for (int i = 0; i < AppFun::rowCount; ++i) {
            QString text = itemModel->item(i, 0)->text();
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
        QStandardItem *item = itemModel->item(index.row(), 12);
        item->setText(value);
    }
}

void frmTableView::buttonClicked(int btnIndex, const QModelIndex &index)
{
    //自己拿到按钮对应的索引+行列 处理操作
    QString text = QString("按钮索引: %1  行: %2  列: %3").arg(btnIndex).arg(index.row()).arg(index.column());
    ui->labInfo->setText(text);
}

void frmTableView::stateChanged(int arg1)
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
    for (int i = 0; i < AppFun::rowCount; ++i) {
        itemModel->item(i, 0)->setText(text);
    }
}

void frmTableView::pressed(const QModelIndex &index)
{
    if (index.column() == 4) {
        int row = index.row();
        QColor color = QColorDialog::getColor(index.data().toString(), this, "选择颜色");
        if (color.isValid()) {
            QString name = color.name().toUpper();
            itemModel->item(row, 4)->setText(name);
        }
    }
}

void frmTableView::setData()
{
    //设置好以后会自动反应到界面上
    QString text = itemModel->item(0, 0)->text();
    text = (text == AppFun::checkBoxChecked ? AppFun::checkBoxUnchecked : AppFun::checkBoxChecked);
    itemModel->item(0, 0)->setText(text);

    text = QString::number(rand() % 100);
    itemModel->item(0, 9)->setText(text);
    itemModel->item(0, 12)->setText(text);
}

void frmTableView::getData()
{
    ui->txtMain->clear();
    for (int i = 0; i < AppFun::rowCount; ++i) {
        QStringList list;
        for (int j = 0; j < AppFun::columnCount; ++j) {
            QString text;
            if (j == 11) {
                //常驻列要单独获取
                QComboBox *cbox = (QComboBox *)ui->tableView->indexWidget(itemModel->index(i, j));
                text = cbox->currentText();
            } else {
                text = itemModel->item(i, j)->text();
            }
            text = text + ((j >= 3 && j <= 9) ? "\t" : "  ");
            list << text;
        }
        ui->txtMain->append(list.join(""));
    }
}
