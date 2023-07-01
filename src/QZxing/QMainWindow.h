#ifndef QMAINWINDOW_H
#define QMAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow ui;
};
#endif // QMAINWINDOW_H