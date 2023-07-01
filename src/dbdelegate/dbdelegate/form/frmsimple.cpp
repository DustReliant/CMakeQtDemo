#include "frmsimple.h"
#include "ui_frmsimple.h"
#include "dbdelegate.h"
#include "qdebug.h"

frmSimple::frmSimple(QWidget *parent) : QWidget(parent), ui(new Ui::frmSimple)
{
    ui->setupUi(this);
    this->initForm();
    this->initDelegate();
}

frmSimple::~frmSimple()
{
    delete ui;
}

void frmSimple::initForm()
{
    //设置行高
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);
    //设置选中行改变自动触发编辑状态,默认是双击,有时候需要切换行的时候自动切换到编辑状态
    ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);
    //设置选中单元格自动选中整行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置每次只允许选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

void frmSimple::initDelegate()
{
    QStringList portName;
    portName << "COM1" << "COM2" << "COM3" << "COM4" << "COM5";

    //下拉框
    DbDelegate *d_combobox = new DbDelegate(ui->tableWidget);
    d_combobox->setDelegateType("QComboBox");
    d_combobox->setDelegateValue(portName);
    ui->tableWidget->setItemDelegateForColumn(0, d_combobox);

    //自定义委托联动
    QStringList listFlor;
    listFlor << "1号楼" << "2号楼" << "3号楼" << "4号楼" << "5号楼";
    d_flor = new DbDelegate(ui->tableWidget);
    //核心 关联信号槽
    connect(d_flor, SIGNAL(valueChanged(QString)), this, SLOT(valueChanged(QString)));
    d_flor->setDelegateType("QComboBox");
    d_flor->setDelegateValue(listFlor);
    ui->tableWidget->setItemDelegateForColumn(1, d_flor);

    QStringList listLevel;
    listLevel << "1层";
    d_level = new DbDelegate(ui->tableWidget);
    d_level->setDelegateType("QComboBox");
    d_level->setDelegateValue(listLevel);
    ui->tableWidget->setItemDelegateForColumn(2, d_level);
}

void frmSimple::valueChanged(const QString &value)
{
    QStringList listLevel;
    if (value == "1号楼") {
        listLevel << "1层" << "2层" << "3层";
    } else if (value == "2号楼") {
        listLevel << "1层" << "3层" << "5层";
    }

    d_level->setDelegateValue(listLevel);
    qDebug() << "当前选择的是" << value;
}
