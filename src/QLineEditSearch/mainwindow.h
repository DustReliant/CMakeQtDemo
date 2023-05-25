
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCompleter>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAtions();
    void slotcompleter(QString str);

private:
    Ui::MainWindow *ui;
    QCompleter* m_MyInfor = nullptr;
};

#endif // MAINWINDOW_H
