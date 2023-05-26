
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
    m_pModel = new QItemTableModel();
    m_pDelegate = new QProgressBarDelegate();
    ui->tableView->setModel(m_pModel);
    ui->tableView->setItemDelegateForColumn(1, m_pDelegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
