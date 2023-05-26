#ifndef QPROGRESSBARGELEGATE_H
#define QPROGRESSBARGELEGATE_H

#include <QStyledItemDelegate>

class QProgressBarDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
    QProgressBarDelegate(QObject* parent = nullptr);
    ~QProgressBarDelegate();

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
#endif // QPROGRESSBARGELEGATE_H