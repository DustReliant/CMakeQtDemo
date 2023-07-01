#include "qtreeitemcheckwidget.h"
#include "ui_qtreeitemcheckwidget.h"

#include <QTreeWidgetItem>

QTreeItemCheckWidget::QTreeItemCheckWidget(const QString &strText, QTreeWidgetItem* pQTreeWidgetItem,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTreeItemCheckWidget),
    m_pQTreeWidgetItem(pQTreeWidgetItem)
{
    ui->setupUi(this);
    //m_pQTreeWidgetItem = pQTreeWidgetItem;
    ui->checkBox->setText(strText);
    ui->checkBox->setStyleSheet("#checkBox::indicator{width: 0px;}"); //隐藏QCheckBox的复选框
    connect(ui->checkBox, SIGNAL(clicked(bool)), this, SLOT(slotCheckBoxClicked(bool)));
    connect(ui->btnExpanded, SIGNAL(clicked()), this, SLOT(slotBtnExpandedClick()));
    connect(ui->btnExtra, SIGNAL(clicked()), this, SLOT(slotBtnExtraClick()));
    connect(this,SIGNAL(signalHideBox()),this,SLOT(slotHideBox()));

    setMinimumHeight(30);

}

QTreeItemCheckWidget::~QTreeItemCheckWidget()
{
    delete ui;
}

QString QTreeItemCheckWidget::getText() const
{
    return ui->checkBox->text();
}

void QTreeItemCheckWidget::setText(const QString &strText)
{
    ui->checkBox->setText(strText);
}

void QTreeItemCheckWidget::setTextColor(const QColor &oQColor)
{
    QPalette oQPalette = ui->checkBox->palette();
    oQPalette.setColor(QPalette::WindowText, oQColor);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
    //oQPalette.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    ui->checkBox->setPalette(oQPalette);

    //ui->checkBox->setStyleSheet(QString("QCheckBox{color:%1;}").arg(oQColor.name()));
}

void QTreeItemCheckWidget::setLeftMargin(int nLeftMargin)
{
    QMargins oQMargins = layout()->contentsMargins();
    oQMargins.setLeft(nLeftMargin);
    layout()->setContentsMargins(oQMargins);
}

bool QTreeItemCheckWidget::isChecked() const
{
    return ui->checkBox->isChecked();
}

void QTreeItemCheckWidget::setChecked(bool bChecked)
{
    ui->checkBox->setChecked(bChecked);
}

void QTreeItemCheckWidget::setCheckable(bool bCheckable)
{
    ui->checkBox->setCheckable(bCheckable);
}


QCheckBox* QTreeItemCheckWidget::getCheckBox()
{
    return ui->checkBox;
}

QPushButton* QTreeItemCheckWidget::getBtnArrow()
{
    return ui->btnExpanded;
}

QPushButton* QTreeItemCheckWidget::getBtnExtra()
{
    return ui->btnExtra;
}

void QTreeItemCheckWidget::updateBtnExpandedIcon()
{
    //底层节点不显示按钮
    if (m_pQTreeWidgetItem->childCount() == 0)
    {
        ui->btnExpanded->hide();
    }
	else
	{
		ui->btnExpanded->show();
	}

    if (ui->btnExpanded->icon().isNull())
    {
        if (m_pQTreeWidgetItem->isExpanded())
        {
            ui->btnExpanded->setStyleSheet(u8"background-image: url(:/image/14px-16展开.png);");
        }
        else
        {
            ui->btnExpanded->setStyleSheet(u8"background-image: url(:/image/14px-16收起.png);");
        }
    }
}

bool QTreeItemCheckWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this)
    {
        if (event->type() == QEvent::HoverEnter)
        {
            emit signalMouseEnter(m_pQTreeWidgetItem);
        }
        else if (event->type() == QEvent::HoverLeave)
        {
            emit signalMouseLeave(m_pQTreeWidgetItem);
        }
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void QTreeItemCheckWidget::slotCheckBoxClicked(bool bChecked)
{
    emit signalCheckBoxClicked(m_pQTreeWidgetItem, bChecked);
}

void QTreeItemCheckWidget::slotBtnExpandedClick()
{
    if (m_pQTreeWidgetItem == NULL)
    {
        return;
    }

    bool bExpanded = !m_pQTreeWidgetItem->isExpanded();
    m_pQTreeWidgetItem->setExpanded(bExpanded);
    updateBtnExpandedIcon();
}

void QTreeItemCheckWidget::slotBtnExtraClick()
{
    emit signalBtnExtraClick(m_pQTreeWidgetItem);
}


