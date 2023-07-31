
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tinyxml.h"
#include "tinystr.h"
#include <QMenu>
//#include "dialog.h"
#include <QTreeWidget>
#include <queue>
#include <stack>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void saveItem(TiXmlElement *xmlElement, QTreeWidgetItem *item);
    void saveTreeToXML(QTreeWidget *treeWidget, const std::string &filename);

    void loadItem(TiXmlElement *xmlElement, QTreeWidgetItem *item);
    void loadTreeFromXML(QTreeWidget *treeWidget, const std::string &filename);


    void loadTreeFromXML_BFS(QTreeWidget *treeWidget, const std::string &filename);
    void saveTreeToXML_BFS(QTreeWidget *treeWidget, const std::string &filename);


    void loadTreeFromXML_DFS(QTreeWidget *treeWidget, const std::string &filename);
    void saveTreeToXML_DFS(QTreeWidget *treeWidget, const std::string &filename);


private slots:
    void onLoadButtonClicked();

    void onSaveButtonClicked();

    void onCustomContextMenuRequested(const QPoint &pos);

    void onADD();

    void onDelete();

    void onData(const QString& name,const QString& value);

private:
    Ui::MainWindow *ui;
    QMenu* m_pMenu = nullptr;
    QAction* add_menu = nullptr;
    QAction* delete_menu = nullptr;
};

#endif // MAINWINDOW_H
