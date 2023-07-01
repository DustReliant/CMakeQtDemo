#include "TableView.h"
#include "ui_tableview.h"
#include <QCheckBox>
#include <QStandardItemModel>
#include <QComboBox>
#include <QColorDialog>

TableView::TableView(QWidget* parent) : QWidget(parent), ui(new Ui::TableView)
{
	ui->setupUi(this);
	initForm();
	initData();
}

TableView::~TableView()
{
	delete ui;
}

void TableView::initForm()
{
	//复选框用于全选
	ckPressed = false;
	ckbox = new QCheckBox(ui->tableView);
	ckbox->setCheckState(Qt::PartiallyChecked);
	connect(ckbox, &QCheckBox::stateChanged, this, &TableView::stateChanged);
	ckbox->move(6, 6);

	connect(ui->tableView, &QTableView::pressed, this, &TableView::pressed);
}

void TableView::initData()
{
	itemModel = new QStandardItemModel(this);
	itemModel->setRowCount(rowCount);
	itemModel->setColumnCount(columnCount);
	itemModel->setHorizontalHeaderLabels(columnNames);
	ui->tableView->setModel(itemModel);
	initTableView(ui->tableView);

	//设置列宽,一定要放在后面,不然如果还没有setModel就设置列宽是不行的
	for (int i = 0; i < columnCount; ++i)
	{
		ui->tableView->setColumnWidth(i, columnWidth.at(i));
	}

	//设置行内容
	for (int i = 0; i < rowCount; ++i)
	{
		insertStandardItem(itemModel, i);
	}

	//设置委托
	initDelegate(this, ui->tableView);

	//一直显示下拉框 其他控件可以依葫芦画瓢
	for (int row = 0; row < rowCount; row++) 
	{
		QComboBox* cbox = new QComboBox;
		cbox->addItems(portName);
		QStandardItem* item = itemModel->item(row, 11);
		cbox->setCurrentIndex(cbox->findText(item->text()));
		ui->tableView->setIndexWidget(item->index(), cbox);
	}
}

void TableView::valueChanged(const QString& value)
{
	QModelIndex index = ui->tableView->currentIndex();
	QString text = QString(u8"当前数据: %1  行: %2  列: %3").arg(value).arg(index.row()).arg(index.column());
	//ui->labInfo->setText(text);

	//其他处理比如自动计算全选复选框状态,联动设定其他值等
	QTableViewDelegate* delegate = qobject_cast<QTableViewDelegate*>(sender());
	QString objName = delegate->objectName();
	if (objName == "d_checkbox") 
	{
		//统计有多少选中的设置全选复选框不同的样式
		int count = 0;
		for (int i = 0; i < rowCount; ++i)
		{
			QString text = itemModel->item(i, 0)->text();
			if (text == checkBoxChecked) 
			{
				count++;
			}
		}

		//定义标志位防止重复选择
		ckPressed = true;
		if (count == 0) 
		{
			ckbox->setCheckState(Qt::Unchecked);
		}
		else if (rowCount == count) 
		{
			ckbox->setCheckState(Qt::Checked);
		}
		else 
		{
			ckbox->setCheckState(Qt::PartiallyChecked);
		}
		ckPressed = false;
	}
	else if (objName == "d_spinbox") 
	{
		//演示将对应的值设置成到进度条
		QStandardItem* item = itemModel->item(index.row(), 12);
		item->setText(value);
	}
}

void TableView::buttonClicked(int btnIndex, const QModelIndex& index)
{
	//自己拿到按钮对应的索引+行列 处理操作
	QString text = QString(u8"按钮索引: %1  行: %2  列: %3").arg(btnIndex).arg(index.row()).arg(index.column());
	//ui->labInfo->setText(text);
}

void TableView::stateChanged(int arg1)
{
	//过滤委托中的复选框按下触发的改变
	if (ckPressed) 
	{
		ckPressed = false;
		return;
	}

	//设置只能两态
	ckbox->setTristate(false);
	//如果选中则设置不选中的值
	QString text = (arg1 != 0 ? checkBoxChecked : checkBoxUnchecked);
	for (int i = 0; i < rowCount; ++i) 
	{
		itemModel->item(i, 0)->setText(text);
	}
}

void TableView::pressed(const QModelIndex& index)
{
	if (index.column() == 4)
	{
		int row = index.row();
		QColor color = QColorDialog::getColor(index.data().toString(), this, u8"选择颜色");
		if (color.isValid()) 
		{
			QString name = color.name().toUpper();
			itemModel->item(row, 4)->setText(name);
		}
	}
}

void TableView::setData()
{
	//设置好以后会自动反应到界面上
	QString text = itemModel->item(0, 0)->text();
	text = (text == checkBoxChecked ? checkBoxUnchecked : checkBoxChecked);
	itemModel->item(0, 0)->setText(text);

	text = QString::number(rand() % 100);
	itemModel->item(0, 9)->setText(text);
	itemModel->item(0, 12)->setText(text);
}

void TableView::getData()
{
	//    ui->txtMain->clear();
	//    for (int i = 0; i < AppFun::rowCount; ++i) {
	//        QStringList list;
	//        for (int j = 0; j < AppFun::columnCount; ++j) {
	//            QString text;
	//            if (j == 11) {
	//                //常驻列要单独获取
	//                QComboBox *cbox = (QComboBox *)ui->tableView->indexWidget(itemModel->index(i, j));
	//                text = cbox->currentText();
	//            } else {
	//                text = itemModel->item(i, j)->text();
	//            }
	//            text = text + ((j >= 3 && j <= 9) ? "\t" : "  ");
	//            list << text;
	//        }
	//        //ui->txtMain->append(list.join(""));
		//    }
}

void TableView::initTableView(QTableView* tableView)
{
	//设置固定高度和行高一行
	tableView->horizontalHeader()->setFixedHeight(rowHeight);
	//设置默认行高
	tableView->verticalHeader()->setDefaultSectionSize(rowHeight);
	//设置居中对齐
	tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
	//设置行头不可见
	tableView->verticalHeader()->setVisible(false);
	//点击表头不对表头行光亮
	tableView->verticalHeader()->setHighlightSections(false);
	tableView->horizontalHeader()->setHighlightSections(false);
	//设置最后一样自动拉伸填充
	tableView->horizontalHeader()->setStretchLastSection(true);
	//设置选中行改变自动触发编辑状态,默认是双击,有时候需要切换行的时候自动切换到编辑状态
	tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
	//设置选中单元格自动选中整行
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	//设置每次只允许选择一行
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	//禁用列拖动
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
	tableView->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
#else
	tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
#endif

	//设置选中高亮颜色
	QPalette pa = tableView->palette();
	pa.setColor(QPalette::Highlight, qApp->palette().color(QPalette::Window).name());
	pa.setColor(QPalette::HighlightedText, qApp->palette().color(QPalette::WindowText).name());
	tableView->setPalette(pa);
}

void TableView::initDelegate(QWidget* widget, QAbstractItemView* itemView, int delegateLevel)
{
	//复选框委托
	QTableViewDelegate* d_checkbox = new QTableViewDelegate(itemView);
	d_checkbox->setObjectName("d_checkbox");
	d_checkbox->setDelegateType("QCheckBox");
	//设置复选框的选中不选中文字
	d_checkbox->setCheckBoxText(checkBoxChecked, checkBoxUnchecked);
	d_checkbox->setDelegateColumn(0);
	itemView->setItemDelegateForColumn(0, d_checkbox);

	//图片委托
	QTableViewDelegate* d_pixmap = new QTableViewDelegate(itemView);
	d_pixmap->setDelegateType("QPixmap");
	d_pixmap->setCheckColumn(6);
	d_pixmap->setCheckType("contains");
	d_pixmap->setCheckValue(u8"离线|故障|报警");
	d_pixmap->setDelegateColumn(1);
	itemView->setItemDelegateForColumn(1, d_pixmap);

	//下拉框委托
	QTableViewDelegate* d_combobox = new QTableViewDelegate(itemView);
	d_combobox->setObjectName("d_combobox");
	d_combobox->setDelegateType("QComboBox");
	d_combobox->setDelegateValue(portName);
	itemView->setItemDelegateForColumn(2, d_combobox);

	//密码框委托
	QTableViewDelegate* d_lineedit = new QTableViewDelegate(itemView);
	d_lineedit->setDelegateType("QLineEdit");
	d_lineedit->setDelegatePwd(true);
	d_lineedit->setDelegateColumn(3);
	itemView->setItemDelegateForColumn(3, d_lineedit);

	//颜色委托
	QTableViewDelegate* d_color = new QTableViewDelegate(itemView);
	d_color->setDelegateType("QColor");
	d_color->setDelegateColumn(4);
	itemView->setItemDelegateForColumn(4, d_color);

	//日期时间委托
	QTableViewDelegate* d_datetime = new QTableViewDelegate(itemView);
	d_datetime->setDelegateType("QDateTimeEdit");
	itemView->setItemDelegateForColumn(5, d_datetime);

	//校验列委托
	QTableViewDelegate* d_check = new QTableViewDelegate(itemView);
	d_check->setCheckText(true);
	d_check->setCheckType("contains");
	d_check->setCheckValue(u8"离线|故障|报警");
	d_check->setDelegateColumn(6);
	itemView->setItemDelegateForColumn(6, d_check);

	//禁用列
	QTableViewDelegate* d_disable = new QTableViewDelegate(itemView);
	d_disable->setObjectName("d_disable");
	d_disable->setDelegateEnable(false);
	d_disable->setDelegateColumn(7);
	itemView->setItemDelegateForColumn(7, d_disable);

	//按钮操作委托
	QTableViewDelegate* d_button = new QTableViewDelegate(itemView);
	d_button->setDelegateType("QPushButton");
	d_button->setDelegateColumn(8);
	itemView->setItemDelegateForColumn(8, d_button);

	//数值微调框委托
	QTableViewDelegate* d_spinbox = new QTableViewDelegate(itemView);
	d_spinbox->setDelegateMin(0);
	d_spinbox->setDelegateMax(100);
	d_spinbox->setObjectName("d_spinbox");
	d_spinbox->setDelegateType("QSpinBox");
	itemView->setItemDelegateForColumn(9, d_spinbox);

	//关键字映射委托
	QStringList key, value;
	key << u8"0|禁用" << u8"1|启用";
	value << u8"启用" << u8"禁用";
	QTableViewDelegate* d_keyvalue = new QTableViewDelegate(itemView);
	d_keyvalue->setDelegateType("QComboBox");
	d_keyvalue->setDelegateKey(key);
	d_keyvalue->setDelegateValue(value);
	d_keyvalue->setDelegateColumn(10);
	itemView->setItemDelegateForColumn(10, d_keyvalue);

	//进度条委托
	QTableViewDelegate* d_progressbar = new QTableViewDelegate(itemView);
	d_progressbar->setDelegateMin(0);
	d_progressbar->setDelegateMax(100);
	d_progressbar->setDelegateType("QProgressBar");
	d_progressbar->setDelegateColumn(12);
	itemView->setItemDelegateForColumn(12, d_progressbar);

	//不需要找到对应哪个窗体,绑定委托信号到槽函数进行判断处理
	QObject::connect(d_lineedit, SIGNAL(valueChanged(QString)), widget, SLOT(valueChanged(QString)));
	QObject::connect(d_checkbox, SIGNAL(valueChanged(QString)), widget, SLOT(valueChanged(QString)));
	QObject::connect(d_combobox, SIGNAL(valueChanged(QString)), widget, SLOT(valueChanged(QString)));
	QObject::connect(d_spinbox, SIGNAL(valueChanged(QString)), widget, SLOT(valueChanged(QString)));
	QObject::connect(d_button, SIGNAL(buttonClicked(int, QModelIndex)), widget, SLOT(buttonClicked(int, QModelIndex)));

	//设置委托最小层级 一般是树状控件才需要设置
	if (delegateLevel > 0)
	{
		d_checkbox->setDelegateLevel(delegateLevel);
		d_pixmap->setDelegateLevel(delegateLevel);
		d_combobox->setDelegateLevel(delegateLevel);
		d_lineedit->setDelegateLevel(delegateLevel);
		d_color->setDelegateLevel(delegateLevel);
		d_datetime->setDelegateLevel(delegateLevel);
		d_check->setDelegateLevel(delegateLevel);
		d_disable->setDelegateLevel(delegateLevel);
		d_button->setDelegateLevel(delegateLevel);
		d_spinbox->setDelegateLevel(delegateLevel);
		d_keyvalue->setDelegateLevel(delegateLevel);
		d_progressbar->setDelegateLevel(delegateLevel);
	}
}

QStandardItem* TableView::getStandardItem(int column)
{
	QStandardItem* item = new QStandardItem();
	item->setText(getText(column));
	//指定列对齐
	if (column == 7) 
	{
		item->setTextAlignment(Qt::AlignCenter);
	}
	return item;
}

void TableView::insertStandardItem(QStandardItemModel* itemModel, int row)
{
	for (int column = 0; column < columnCount; column++) 
	{
		itemModel->setItem(row, column, getStandardItem(column));
	}
}

QString TableView::getText(int column)
{
	//用随机数模拟数据
	QString text;
	int temp = rand() % 100;
	if (column == 0) {
		text = ((rand() % 100) % 2 == 0) ? checkBoxChecked : checkBoxUnchecked;
	}
	else if (column == 1)
	{
	}
	else if (column == 2)
	{
		text = QString("COM%1").arg(rand() % 5 + 1);
	}
	else if (column == 3)
	{
		text = QString("admin%1").arg(temp);
	}
	else if (column == 4)
	{
		static QStringList colors = QColor::colorNames();
		text = colors.at(rand() % colors.count());
		text = QColor(text).name().toUpper();
	}
	else if (column == 5)
	{
		QDateTime now = QDateTime::currentDateTime().addSecs(rand() % 1000);
		text = now.toString("yyyy-MM-dd HH:mm:ss");
	}
	else if (column == 6)
	{
		static QStringList content;
		content << u8"设备上线" << u8"设备离线" << u8"设备正常" << u8"设备故障" << u8"设备报警";
		text = content.at(rand() % content.count());
	}
	else if (column == 7)
	{
		text = u8"测试";
	}
	else if (column == 8)
	{
		text = (temp % 2) ? u8"打开" : u8"编辑|删除";
	}
	else if (column == 9)
	{
		text = QString("%1").arg(temp);
	}
	else if (column == 10)
	{
		text = (temp % 2) ? "0" : "1";
	}
	else if (column == 11)
	{
		text = QString("COM%1").arg(rand() % 5 + 1);
	}
	else if (column == 12)
	{
		text = QString("%1").arg(temp);
		//text = QString("20");
	}

	return text;
}
