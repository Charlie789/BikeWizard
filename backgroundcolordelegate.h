#ifndef BACKGROUNDCOLORDELEGATE_H
#define BACKGROUNDCOLORDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class BackgroundColorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    BackgroundColorDelegate(QObject *parent = 0);

    // QStyledItemDelegate interface
protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const;
};

#endif // BACKGROUNDCOLORDELEGATE_H
