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

    QString generate_order_frame();
    QString generate_parts_header();
    QString generate_part_rows();
    QString generate_sign_space();
    QString generate_header();

public slots:
    void order_bike();
    void set_selected_parts_model(QStandardItemModel* model);
    void generate_order();

private slots:
    void decrease_quantity();

signals:
    void send_part_ID(QString part_ID, int quantity);

};

#endif // ORDERBIKE_H
