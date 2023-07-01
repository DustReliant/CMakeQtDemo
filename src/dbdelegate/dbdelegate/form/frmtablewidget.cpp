#include "frmtablewidget.h"
#include "ui_frmtablewidget.h"
#include "quihelper.h"

frmTableWidget::frmTableWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmTableWidget)
{
    ui->setupUi(this);
    this->initForm();
    this->initData();
}

frmTableWidget::~frmTableWidget()
{
    delete ui;
}

void frmTableWidget::initForm()
{
    //复选框用于全选
    ckPressed = false;
    ckbox = new QCheckBox(ui->tableWidget);
    ckbox->setCheckState(Qt::PartiallyChecked);
    connect(ckbox, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    ckbox->move(6, 6);

    connect(ui->tableWidget, SIGNAL(pressed(QModelIndex)), this, SLOT(pressed(QModelIndex)));
    connect(ui->btnSetData, SIGNAL(clicked(bool)), this, SLOT(setData()));
    connect(ui->btnGetData, SIGNAL(clicked(bool)), this, SLOT(getData()));
}

void frmTableWidget::initData()
{
    ui->tableWidget->setRowCount(AppFun::rowCount);
    ui->tableWidget->setColumnCount(AppFun::columnCount);
    ui->tableWidget->setHorizontalHeaderLabels(AppFun::columnNames);
    AppFun::initTableView(ui->tableWidget);

    //设置列宽,一定要放在后面,不然如果还没有setModel就设置列宽是不行的
    for (int i = 0; i < AppFun::columnCount; ++i) {
        ui->tableWidget->setColumnWidth(i, AppFun::columnWidth.at(i));
    }

    //设置行内容
    for (int i = 0; i < AppFun::rowCount; ++i) {
        AppFun::insertTableWidgetItem(ui->tableWidget, i);
    }

    //设置委托
    AppFun::initDelegate(this, ui->tableWidget);

    //特殊样式方便测试
#if 1
    QFont font;
    font.setBold(true);
    font.setPixelSize(17);
    ui->tableWidget->item(3, 7)->setFont(font);
    ui->tableWidget->item(3, 7)->setForeground(Qt::red);
    ui->tableWidget->item(3, 7)->setBackground(Qt::green);
#endif

    //一直显示下拉框 其他控件可以依葫芦画瓢
    for (int row = 0; row < AppFun::rowCount; row++) {
        QComboBox *cbox = new QComboBox;
        cbox->addItems(AppFun::portName);
        QTableWidgetItem *item = ui->tableWidget->item(row, 11);
        cbox->setCurrentIndex(cbox->findText(item->text()));
        ui->tableWidget->setCellWidget(row, 11, cbox);
    }
}

void frmTableWidget::valueChanged(const QString &value)
{
    QModelIndex index = ui->tableWidget->currentIndex();
    QString text = QString("当前数据: %1  行: %2  列: %3").arg(value).arg(index.row()).arg(index.column());
    ui->labInfo->setText(text);

    //其他处理比如自动计算全选复选框状态,联动设定其他值等
    DbDelegate *delegate = (DbDelegate *)sender();
    QString objName = delegate->objectName();
    if (objName == "d_checkbox") {
        //统计有多少选中的设置全选复选框不同的样式
        int count = 0;
        for (int i = 0; i < AppFun::rowCount; ++i) {
            QString text = ui->tableWidget->item(i, 0)->text();
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
        QTableWidgetItem *item = ui->tableWidget->item(index.row(), 12);
        item->setText(value);
    }
}

void frmTableWidget::buttonClicked(int btnIndex, const QModelIndex &index)
{
    //自己拿到按钮对应的索引+行列 处理操作
    QString text = QString("按钮索引: %1  行: %2  列: %3").arg(btnIndex).arg(index.row()).arg(index.column());
    ui->labInfo->setText(text);
}

void frmTableWidget::stateChanged(int arg1)
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
        ui->tableWidget->item(i, 0)->setText(text);
    }
}

void frmTableWidget::pressed(const QModelIndex &index)
{
    if (index.column() == 4) {
        int row = index.row();
        QColor color = QColorDialog::getColor(index.data().toString(), this, "选择颜色");
        if (color.isValid()) {
            QString name = color.name().toUpper();
            ui->tableWidget->item(row, 4)->setText(name);
        }
    }
}

void frmTableWidget::setData()
{
    //设置好以后会自动反应到界面上
    QString text = ui->tableWidget->item(0, 0)->text();
    text = (text == AppFun::checkBoxChecked ? AppFun::checkBoxUnchecked : AppFun::checkBoxChecked);
    ui->tableWidget->item(0, 0)->setText(text);

    text = QString::number(rand() % 100);
    ui->tableWidget->item(0, 9)->setText(text);
    ui->tableWidget->item(0, 12)->setText(text);
}

void frmTableWidget::getData()
{
    ui->txtMain->clear();
    for (int i = 0; i < AppFun::rowCount; ++i) {
        QStringList list;
        for (int j = 0; j < AppFun::columnCount; ++j) {
            QString text;
            if (j == 11) {
                //常驻列要单独获取
                QComboBox *cbox = (QComboBox *)ui->tableWidget->cellWidget(i, j);
                text = cbox->currentText();
            } else {
                text = ui->tableWidget->item(i, j)->text();
            }
            text = text + ((j >= 3 && j <= 9) ? "\t" : "  ");
            list << text;
        }
        ui->txtMain->append(list.join(""));
    }
}
