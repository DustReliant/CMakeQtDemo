#ifndef QITEMTABLEMODEL_H
#define QITEMTABLEMODEL_H

#include <QAbstractItemModel>

class QItemTableModel : public QAbstractItemModel
{
	Q_OBJECT
public:
    QItemTableModel(QObject* parent = nullptr);
    virtual ~QItemTableModel();

    // 返回行的数量
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    // 返回列的数量
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    // 返回数据
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    // 返回单元格的标志，就是通过此函数来实现CheckBox和SpinBox
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    // 数据变化后设置数据
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::DisplayRole) override;
    // 返回表头数据
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex& child) const override;
    // 自定义的数据插入函数
    //void setData(ItemData data);

private:
    struct ItemData 
    {
        QString text;
        int progress;
        bool checked; // 新增的复选框状态
    };

    QVector<ItemData> m_data = 
    {
        {"Item 1", 50,true},
        {"Item 2", 70,false},
        {"Item 3", 30,false},
    };
};
#endif // QITEMTABLEMODEL_H