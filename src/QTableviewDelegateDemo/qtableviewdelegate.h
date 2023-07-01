
#ifndef QTABLEVIEWDELEGATE_H
#define QTABLEVIEWDELEGATE_H

#include <QPixmap>
#include <QCheckBox>
#include <QPushButton>
#include <QProgressBar>
#include <QStyledItemDelegate>

class QTableViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit QTableViewDelegate(QObject *parent = 0);

protected:
    //事件过滤器识别鼠标等动作发信号出去
    bool eventFilter(QObject *object, QEvent *event);

protected:
    //获取当前数据模型所在层级
    int getLevel(const QModelIndex &index) const;
    //创建委托控件对象
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //将数据源的值设置到委托控件
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //将委托控件的值设置到数据源
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    //更新委托控件的位置
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //编辑数据的处理
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

    //自定义绘制函数
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawBg(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawCheckBox(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawPushButton(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawProgressBar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawColor(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawLineEdit(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawPixmap(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawDisable(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //绘制关键字对照表
    QString getKeyValue(const QString &data, bool key) const;
    void drawKey(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //绘制校验数据不同颜色显示
    void checkData(const QString &data, bool *exist) const;
    void drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    bool delegatePwd;           //是否密码显示
    bool delegateEdit;          //可否允许编辑
    bool delegateEnable;        //是否可用,这样可以用来禁用列

    int delegateMin;            //委托中控件的范围值最小值
    int delegateMax;            //委托中控件的范围值最大值

    int delegateColumn;         //当前委托对应的列
    int delegateLevel;          //委托应用的最小层级
    QString delegateType;       //委托类型
    QStringList delegateKey;    //委托数据关键字
    QStringList delegateValue;  //委托数据集合

    QString checkBoxChecked;    //复选框选中对应的文字
    QString checkBoxUnchecked;  //复选框选中对应的文字

    int checkColumn;            //校验数据列
    QString checkType;          //校验规则,例如>=
    QString checkValue;         //检验值
    QPixmap checkOkImage;       //校验成功图标
    QPixmap checkNoImage;       //校验失败图标
    int checkImageWidth;        //图片宽度
    int checkImageHeight;       //图片高度

    bool checkText;             //是否校验数据显示不同的颜色
    QColor checkTextColor;      //校验文字颜色
    QColor checkBgColor;        //校验背景颜色
    QColor textColor;           //文本颜色
    QColor hoverBgColor;        //悬停背景颜色
    QColor selectBgColor;       //选中背景颜色

    QPoint mousePoint;          //鼠标按下处坐标
    bool mousePressed;          //鼠标是否按下
    QString checkedText;        //存储复选框当前文字

    //下面控件根据委托的类型new出来,为了应用样式表
    QCheckBox *checkBox;        //复选框
    QPushButton *pushButton;    //按钮
    QProgressBar *progressBar;  //进度条

private slots:
    //复选框切换状态延时发送值改变
    void slot_valueChanged();
    //下拉框微调框值改变
    void slot_valueChanged(int value);

signals:
    //鼠标相关动作 actionType = 0-未知 1-鼠标按下 2-鼠标松开 3-鼠标双击
    void mouseAction(int actionType, bool rightButton);
    //值改变信号
    void valueChanged(const QString &value);
    //按钮单击信号
    void buttonClicked(int btnIndex, const QModelIndex &index);

public slots:
    //设置密码显示+允许编辑+可用
    void setDelegatePwd(bool delegatePwd);
    void setDelegateEdit(bool delegateEdit);
    void setDelegateEnable(bool delegateEnable);

    //设置委托范围值比如微调框
    void setDelegateMin(int delegateMin);
    void setDelegateMax(int delegateMax);

    //需要额外绘制的需要调用 setDelegateColumn 来设置委托的列方便用于执行绘制
    void setDelegateColumn(int delegateColumn);
    void setDelegateLevel(int delegateLevel);
    void setDelegateType(const QString &delegateType);
    void setDelegateKey(const QStringList &delegateKey);
    void setDelegateValue(const QStringList &delegateValue);

    //设置复选框选中不选中对应文字
    void setCheckBoxText(const QString &checkBoxChecked, const QString &checkBoxUnchecked);

    //设置校验数据列+校验规则
    void setCheckColumn(int checkColumn);
    void setCheckType(const QString &checkType);
    void setCheckValue(const QString &checkValue);
    void setCheckOkImage(const QPixmap &checkOkImage);
    void setCheckNoImage(const QPixmap &checkNoImage);
    void setCheckImageWidth(int checkImageWidth);
    void setCheckImageHeight(int checkImageHeight);

    //设置是否校验文本
    void setCheckText(bool checkText);
    void setCheckTextColor(const QColor &checkTextColor);
    void setCheckBgColor(const QColor &checkBgColor);
    void setTextColor(const QColor &textColor);
    void setHoverBgColor(const QColor &hoverBgColor);
    void setSelectBgColor(const QColor &selectBgColor);
};

#endif // QTABLEVIEWDELEGATE_H
