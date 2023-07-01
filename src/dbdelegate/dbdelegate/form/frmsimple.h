#ifndef FRMSIMPLE_H
#define FRMSIMPLE_H

#include <QWidget>
class DbDelegate;

namespace Ui {
class frmSimple;
}

class frmSimple : public QWidget
{
    Q_OBJECT

public:
    explicit frmSimple(QWidget *parent = 0);
    ~frmSimple();

private:
    Ui::frmSimple *ui;
    DbDelegate *d_flor;
    DbDelegate *d_level;

private slots:
    void initForm();
    void initDelegate();

private slots:
    //值改变信号
    void valueChanged(const QString &value);
};

#endif // FRMSIMPLE_H
