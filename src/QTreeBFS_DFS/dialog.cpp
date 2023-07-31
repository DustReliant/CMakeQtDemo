#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&Dialog::onOK);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onOK()
{
    QString strName = ui->lineEdit->text();
    QString strValue = ui->lineEdit_2->text();

    emit sendData(strName,strValue);
}


void Dialog::on_pushButton_2_clicked()
{

}

