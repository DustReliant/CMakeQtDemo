#include "appfun.h"
#include "quihelper.h"
#include "dbdelegate.h"

QStringList AppFun::portName = QStringList() << "COM1" << "COM2" << "COM3" << "COM4" << "COM5";
QStringList AppFun::columnNames = QStringList() << QString::fromUtf8("|状态|下拉框|密码框|颜色|日期时间|校验列|禁用|按钮|数值|映射|常驻列|进度条").split("|");
QList<int> AppFun::columnWidth = QList<int>() << 25 << 45 << 80 << 80 << 90 << 170 << 80 << 45 << 90 << 50 << 60 << 80 << 50;

int AppFun::rowHeight = 25;
int AppFun::rowCount = 12;
int AppFun::columnCount = AppFun::columnWidth.count();

//复选框选中不选中对应的数据源关键字
QString AppFun::checkBoxChecked = QString::fromUtf8("打开");
QString AppFun::checkBoxUnchecked = QString::fromUtf8("关闭");

QString AppFun::getText(int column)
{
    //用随机数模拟数据
    QString text;
    int temp = rand() % 100;
    if (column == 0) {
        text = ((rand() % 100) % 2 == 0) ? checkBoxChecked : checkBoxUnchecked;
    } else if (column == 1) {
    } else if (column == 2) {
        text = QString("COM%1").arg(rand() % 5 + 1);
    } else if (column == 3) {
        text = QString("admin%1").arg(temp);
    } else if (column == 4) {
        static QStringList colors = QColor::colorNames();
        text = colors.at(rand() % colors.count());
        text = QColor(text).name().toUpper();
    } else if (column == 5) {
        QDateTime now = QDateTime::currentDateTime().addSecs(rand() % 1000);
        text = now.toString("yyyy-MM-dd HH:mm:ss");
    } else if (column == 6) {
        static QStringList content;
        content << "设备上线" << "设备离线" << "设备正常" << "设备故障" << "设备报警";
        text = content.at(rand() % content.count());
    } else if (column == 7) {
        text = "测试";
    } else if (column == 8) {
        text = (temp % 2) ? "打开" : "编辑|删除";
    } else if (column == 9) {
        text = QString("%1").arg(temp);
    } else if (column == 10) {
        text = (temp % 2) ? "0" : "1";
    } else if (column == 11) {
        text = QString("COM%1").arg(rand() % 5 + 1);
    } else if (column == 12) {
        text = QString("%1").arg(temp);
    }

    return text;
}

QStandardItem *AppFun::getStandardItem(int column)
{
    QStandardItem *item = new QStandardItem;
    item->setText(AppFun::getText(column));
    //指定列对齐
    if (column == 7) {
        item->setTextAlignment(Qt::AlignCenter);
    }
    return item;
}

void AppFun::insertStandardItem(QStandardItemModel *itemModel, int row)
{
    for (int column = 0; column < AppFun::columnCount; column++) {
        itemModel->setItem(row, column, AppFun::getStandardItem(column));
    }
}

QTableWidgetItem *AppFun::getTableWidgetItem(int column)
{
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(AppFun::getText(column));
    //指定列对齐
    if (column == 7) {
        item->setTextAlignment(Qt::AlignCenter);
    }
    return item;
}

void AppFun::insertTableWidgetItem(QTableWidget *tableWidget, int row)
{
    for (int column = 0; column < AppFun::columnCount; column++) {
        tableWidget->setItem(row, column, AppFun::getTableWidgetItem(column));
    }
}

QTreeWidgetItem *AppFun::getTreeWidgetItem(int column)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(column, AppFun::getText(column));
    //指定列对齐
    if (column == 7) {
        item->setTextAlignment(column, Qt::AlignCenter);
    }
    return item;
}

void AppFun::insertTreeWidgetItem(QTreeWidget *treeWidget, int row)
{

}

void AppFun::initTableView(QTableView *tableView)
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

void AppFun::initTreeView(QTreeView *treeView)
{
    //设置固定高度和行高一行
    treeView->header()->setFixedHeight(rowHeight);
    //设置默认行高
    treeView->header()->setDefaultSectionSize(rowHeight);
    //设置居中对齐
    treeView->header()->setDefaultAlignment(Qt::AlignCenter);
    //点击表头不对表头行光亮
    treeView->header()->setHighlightSections(false);
    //设置最后一样自动拉伸填充
    treeView->header()->setStretchLastSection(true);
    //设置选中行改变自动触发编辑状态,默认是双击,有时候需要切换行的时候自动切换到编辑状态
    treeView->setEditTriggers(QAbstractItemView::CurrentChanged);
    //设置选中单元格自动选中整行
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置每次只允许选择一行
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);

    //禁用列拖动
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
    treeView->header()->setResizeMode(0, QHeaderView::Fixed);
#else
    //treeView->header()->setSectionResizeMode(0, QHeaderView::Fixed);
#endif

    //设置选中高亮颜色
    QPalette pa = treeView->palette();
    pa.setColor(QPalette::Highlight, qApp->palette().color(QPalette::Window).name());
    pa.setColor(QPalette::HighlightedText, qApp->palette().color(QPalette::WindowText).name());
    treeView->setPalette(pa);
}

QList<DbDelegate *> AppFun::delegates = QList<DbDelegate *>();
void AppFun::initDelegate(QWidget *widget, QAbstractItemView *itemView, int delegateLevel)
{
    //复选框委托
    DbDelegate *d_checkbox = new DbDelegate(itemView);
    d_checkbox->setObjectName("d_checkbox");
    d_checkbox->setDelegateType("QCheckBox");
    //设置复选框的选中不选中文字
    d_checkbox->setCheckBoxText(checkBoxChecked, checkBoxUnchecked);
    d_checkbox->setDelegateColumn(0);
    itemView->setItemDelegateForColumn(0, d_checkbox);

    //图片委托
    DbDelegate *d_pixmap = new DbDelegate(itemView);
    d_pixmap->setDelegateType("QPixmap");
    d_pixmap->setCheckColumn(6);
    d_pixmap->setCheckType("contains");
    d_pixmap->setCheckValue("离线|故障|报警");
    d_pixmap->setDelegateColumn(1);
    itemView->setItemDelegateForColumn(1, d_pixmap);

    //下拉框委托
    DbDelegate *d_combobox = new DbDelegate(itemView);
    d_combobox->setObjectName("d_combobox");
    d_combobox->setDelegateType("QComboBox");
    d_combobox->setDelegateValue(portName);
    itemView->setItemDelegateForColumn(2, d_combobox);

    //密码框委托
    DbDelegate *d_lineedit = new DbDelegate(itemView);
    d_lineedit->setDelegateType("QLineEdit");
    d_lineedit->setDelegatePwd(true);
    d_lineedit->setDelegateColumn(3);
    itemView->setItemDelegateForColumn(3, d_lineedit);

    //颜色委托
    DbDelegate *d_color = new DbDelegate(itemView);
    d_color->setDelegateType("QColor");
    d_color->setDelegateColumn(4);
    itemView->setItemDelegateForColumn(4, d_color);

    //日期时间委托
    DbDelegate *d_datetime = new DbDelegate(itemView);
    d_datetime->setDelegateType("QDateTimeEdit");
    itemView->setItemDelegateForColumn(5, d_datetime);

    //校验列委托
    DbDelegate *d_check = new DbDelegate(itemView);
    d_check->setCheckText(true);
    d_check->setCheckType("contains");
    d_check->setCheckValue("离线|故障|报警");
    d_check->setDelegateColumn(6);
    itemView->setItemDelegateForColumn(6, d_check);

    //禁用列
    DbDelegate *d_disable = new DbDelegate(itemView);
    d_disable->setObjectName("d_disable");
    d_disable->setDelegateEnable(false);
    d_disable->setDelegateColumn(7);
    itemView->setItemDelegateForColumn(7, d_disable);

    //按钮操作委托
    DbDelegate *d_button = new DbDelegate(itemView);
    d_button->setDelegateType("QPushButton");
    d_button->setDelegateColumn(8);
    itemView->setItemDelegateForColumn(8, d_button);

    //数值微调框委托
    DbDelegate *d_spinbox = new DbDelegate(itemView);
    d_spinbox->setDelegateMin(0);
    d_spinbox->setDelegateMax(100);
    d_spinbox->setObjectName("d_spinbox");
    d_spinbox->setDelegateType("QSpinBox");
    itemView->setItemDelegateForColumn(9, d_spinbox);

    //关键字映射委托
    QStringList key, value;
    key << "0|禁用" << "1|启用";
    value << "启用" << "禁用";
    DbDelegate *d_keyvalue = new DbDelegate(itemView);
    d_keyvalue->setDelegateType("QComboBox");
    d_keyvalue->setDelegateKey(key);
    d_keyvalue->setDelegateValue(value);
    d_keyvalue->setDelegateColumn(10);
    itemView->setItemDelegateForColumn(10, d_keyvalue);

    //进度条委托
    DbDelegate *d_progressbar = new DbDelegate(itemView);
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
    if (delegateLevel > 0) {
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

    //添加到委托列集合方便统一设置颜色 不需要的话可以不用这个处理
    AppFun::delegates << d_checkbox;
    AppFun::delegates << d_pixmap;
    AppFun::delegates << d_combobox;
    AppFun::delegates << d_lineedit;
    AppFun::delegates << d_color;
    AppFun::delegates << d_datetime;
    AppFun::delegates << d_check;
    AppFun::delegates << d_disable;
    AppFun::delegates << d_button;
    AppFun::delegates << d_keyvalue;
    AppFun::delegates << d_progressbar;
}
