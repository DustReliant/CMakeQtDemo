#ifndef QTREEITEMCHECKWIDGET_H
#define QTREEITEMCHECKWIDGET_H

#include <QWidget>

class QTreeWidgetItem;
class QCheckBox;
class QPushButton;

namespace Ui {
class QTreeItemCheckWidget;
}

class QTreeItemCheckWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QTreeItemCheckWidget(const QString &strText, QTreeWidgetItem* pQTreeWidgetItem, QWidget *parent = 0);
    ~QTreeItemCheckWidget();

    QString getText() const;
    void setText(const QString &strText);

    void setTextColor(const QColor &oQColor);

    //设置左边距
    void setLeftMargin(int nLeftMargin);

    bool isChecked() const;

    void setChecked(bool bChecked);

    void setCheckable(bool bCheckable);

    QCheckBox* getCheckBox();
    QPushButton* getBtnArrow();
    QPushButton* getBtnExtra();

    void updateBtnExpandedIcon();

    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void signalMouseEnter(QTreeWidgetItem*);
    void signalMouseLeave(QTreeWidgetItem*);

    void signalCheckBoxClicked(QTreeWidgetItem* pItem, bool bChecked);
    void signalBtnExtraClick(QTreeWidgetItem*);

    void signalHideBox(QTreeWidgetItem*);

public slots:
    void slotCheckBoxClicked(bool bChecked);
    void slotBtnExpandedClick();
    void slotBtnExtraClick();

protected:


private:
    Ui::QTreeItemCheckWidget *ui;
    QTreeWidgetItem* m_pQTreeWidgetItem;
};

#endif // QTREEITEMCHECKWIDGET_H
