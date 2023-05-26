
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCompleter>

#include "../core/QProgressBarDelegate.h"
#include "../core/QItemTableModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QProgressBarDelegate* m_pDelegate = nullptr;
    QItemTableModel* m_pModel = nullptr;
};

#endif // MAINWINDOW_H
