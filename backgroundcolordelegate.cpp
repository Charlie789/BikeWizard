#include "backgroundcolordelegate.h"
#include <QDebug>

BackgroundColorDelegate::BackgroundColorDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void BackgroundColorDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    QStyleOptionViewItem* m_option = option;
    int quantity_column = index.model()->columnCount();
    if (index.sibling(index.row(), quantity_column - 2).data().toInt() > 0)
        return;
    m_option->backgroundBrush = QBrush(QColor(Qt::red));
}
