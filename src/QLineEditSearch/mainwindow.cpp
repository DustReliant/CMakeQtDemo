
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QDebug>
#include <QStyledItemDelegate>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	//初始化 QAction
	QAction* search_action = new QAction;
	search_action->setToolTip("搜索");//设置鼠标悬浮的提示
	search_action->setIcon(QIcon(":/search.png"));//加载显示图片
	connect(search_action, &QAction::triggered, this,&MainWindow::onAtions);

	//设置输入联想下拉框
	QStringList  word_list;
	word_list << "1" << "12" << "213" << "123" << "231" << "321" << "Java" << "C++" << "C#" << "PHP" << "Perl" << "Python" << "Delphi" << "Ruby";
	m_MyInfor = new QCompleter(word_list);
	m_MyInfor->setFilterMode(Qt::MatchContains);
	m_MyInfor->setCaseSensitivity(Qt::CaseInsensitive);
	QAbstractItemView* popup = m_MyInfor->popup();
	connect(m_MyInfor, SIGNAL(activated(QString)), this, SLOT(slotcompleter(QString)));
	//设置联想下拉框代理，这个关乎qss的是否生效
	QStyledItemDelegate* d = new QStyledItemDelegate(this);
	popup->setItemDelegate(d);
	popup->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	////设置联想下拉框样式
	QString stylestr = QString("QAbstractItemView::item:selected{ background:blue; height:20px; border-radius:5px;}"
								"QAbstractItemView::item{ color:white; background:red; min-height:30px; border-radius:5px; border-bottom:1px solid #DDDDDD; margin-bottom:10px;/*边缘间隔*/}"
								"QAbstractItemView{ background:rgb(81, 81, 81);outline:none; border-radius:10px; padding-left:10px; padding-right:30px; padding-top:10px;/*拓展距离*/}");
	this->setStyleSheet(stylestr);

	//设置Eidt的模糊查询对象
	ui->lineEdit->setCompleter(m_MyInfor);

	// 设置编辑框没有输入内容时的友好提示
	ui->lineEdit->setPlaceholderText("123");
	//TrailingPosition:将action放置在右边
	ui->lineEdit->addAction(search_action, QLineEdit::TrailingPosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAtions()
{
	qDebug() << ui->lineEdit->text();
}

//记录选择的联想内容
void MainWindow::slotcompleter(QString str)
{
	qDebug() << str << m_MyInfor->completionCount();
}