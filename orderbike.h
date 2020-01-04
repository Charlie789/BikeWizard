#ifndef ORDERBIKE_H
#define ORDERBIKE_H

#include <QObject>
#include <QStandardItemModel>
#include "customtypes.h"

class OrderBike : public QObject
{
    Q_OBJECT
public:
    explicit OrderBike(QObject *parent = nullptr);

private:
    QStandardItemModel* m_selected_parts_model;

public slots:
    void order_bike();
    void set_selected_parts_model(QStandardItemModel* model);

private slots:
    void decrease_quantity();

signals:
    void send_part_ID(QString part_ID);

};

#endif // ORDERBIKE_H
