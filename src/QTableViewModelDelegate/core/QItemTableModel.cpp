#include "QItemTableModel.h"
#include <QDebug>
#include <QProgressBar>
QItemTableModel::QItemTableModel(QObject* parent) :
    QAbstractItemModel(parent) 
{

}

QItemTableModel::~QItemTableModel() {
}

int QItemTableModel::rowCount(const QModelIndex& parent) const 
{
    if (parent.isValid())
        return 0; // 没有子项

    return m_data.size();
}

int QItemTableModel::columnCount(const QModelIndex& parent) const 
{
    if (parent.isValid())
        return 0; // 没有子项

    return 5; // 两列数据
}

QVariant QItemTableModel::data(const QModelIndex& index, int role) const 
{
    //if (!index.isValid())
    //    return QVariant();

    //if (role == Qt::DisplayRole) {
    //    if (index.column() == 0) // 第一列显示文本
    //        return m_data[index.row()].text;
    //} else if (role == Qt::TextAlignmentRole && index.column() == 1) // 第二列对齐方式为居中
    //{
    //    return Qt::AlignCenter;
    //} else if (role == Qt::DecorationRole && index.column() == 1) // 第二列显示进度条
    //{
    //    int progress = m_data[index.row()].progress;

    //    QProgressBar* progressBar = new QProgressBar();
    //    progressBar->setValue(progress);
    //    progressBar->setAlignment(Qt::AlignCenter);
    //    progressBar->setMinimumSize(100, 20);

    //    return QVariant::fromValue(progressBar);
    //}
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) // 第一列显示文本
            return m_data[index.row()].text;
        else if (index.column() == 1) // 第二列显示进度条的数值
            return m_data[index.row()].progress;
    } else if (role == Qt::TextAlignmentRole && index.column() == 1) // 第二列对齐方式为居中
    {
        return Qt::AlignCenter;
    }

    return QVariant();
}

Qt::ItemFlags QItemTableModel::flags(const QModelIndex& index) const 
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (index.column() == 1)
        return Qt::ItemIsEditable | Qt::ItemIsEnabled; // 第二列可编辑

    return Qt::ItemIsEnabled;
}

bool QItemTableModel::setData(const QModelIndex& index, const QVariant& value, int role) 
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    if (index.column() == 1) // 第二列数据为进度条值
    {
        int progress = value.toInt();
        if (progress < 0 || progress > 100)
            return false;

        m_data[index.row()].progress = progress;
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

QVariant QItemTableModel::headerData(int section, Qt::Orientation orientation, int role) const 
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0)
            return "Item";
        else if (section == 1)
            return "Progress";
    }

    return QVariant();
}

QModelIndex QItemTableModel::index(int row, int column, const QModelIndex& parent) const 
{
    if (parent.isValid() || row < 0 || row >= rowCount() || column < 0 || column >= columnCount())
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex QItemTableModel::parent(const QModelIndex& child) const 
{
    Q_UNUSED(child);
    return QModelIndex();
}
