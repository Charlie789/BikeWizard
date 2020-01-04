#include "orderbike.h"
#include <QDebug>

OrderBike::OrderBike(QObject *parent) : QObject(parent)
{

}

void OrderBike::order_bike()
{
    decrease_quantity();
}

void OrderBike::set_selected_parts_model(QStandardItemModel* model)
{
    m_selected_parts_model = model;
}

void OrderBike::decrease_quantity()
{
    for (int i = 0; i < m_selected_parts_model->rowCount(); i++){
        for (int column = 0; column < m_selected_parts_model->columnCount(); column++){
            qDebug() << m_selected_parts_model->item(i, column)->data(Qt::DisplayRole);
        }
        QString part_ID = m_selected_parts_model->item(i, TableProperties::SelectedParts::ColumnPartID)->data(Qt::DisplayRole).toString();
        qDebug() << part_ID;
        emit send_part_ID(part_ID);
    }
}
