#include "QProgressBarDelegate.h"
#include <QProgressBar>
#include <QApplication>

QProgressBarDelegate::QProgressBarDelegate(QObject* parent) 
    :QStyledItemDelegate(parent) 
{

}

QProgressBarDelegate::~QProgressBarDelegate() 
{

}

QWidget* QProgressBarDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const 
{
    if (index.column() == 1) // 第二列显示进度条
    {
        QProgressBar* editor = new QProgressBar(parent);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void QProgressBarDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const 
{
    if (index.column() == 1) // 第二列设置进度条值
    {
        int progress = index.data(Qt::DisplayRole).toInt();
        QProgressBar* progressBar = qobject_cast<QProgressBar*>(editor);
        progressBar->setValue(progress);
        return;
    }

    QStyledItemDelegate::setEditorData(editor, index);
}

void QProgressBarDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const 
{
    if (index.column() == 1) // 第二列获取进度条值
    {
        QProgressBar* progressBar = qobject_cast<QProgressBar*>(editor);
        int progress = progressBar->value();
        model->setData(index, progress, Qt::EditRole);
        return;
    }

    QStyledItemDelegate::setModelData(editor, model, index);
}

void QProgressBarDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const 
{
    editor->setGeometry(option.rect);
}

void QProgressBarDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const 
{
    if (index.column() == 1) // 第二列显示进度条
    {
        int progress = index.data().toInt();

        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = progress;
        progressBarOption.textVisible = true;
        progressBarOption.textAlignment = Qt::AlignCenter;
        progressBarOption.text = QString("%1%").arg(progress); // 显示具体的进度数值

        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
