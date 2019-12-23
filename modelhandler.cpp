#include "modelhandler.h"
#include "customtypes.h"
#include <QDebug>
#include <QDynamicPropertyChangeEvent>

ModelHandler::ModelHandler(QObject *parent) :
    QObject(parent),
    m_attribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1")),
    m_attribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, "-1"))
{
    connect(this, &ModelHandler::map_part_table_ready, this, &ModelHandler::fill_selected_parts_model);
    connect(this, &ModelHandler::part_deleted, this, &ModelHandler::clean_properties);
    connect(this, &ModelHandler::attribute_wheel_sizeChanged, this, &ModelHandler::property_handler);
    connect(this, &ModelHandler::attribute_axle_type_frontChanged, this, &ModelHandler::property_handler);
}

ModelHandler::PartAttribute ModelHandler::attribute_wheel_size() const
{
    return m_attribute_wheel_size;
}

ModelHandler::PartAttribute ModelHandler::attribute_axle_type_front() const
{
    return m_attribute_axle_type_front;
}

void ModelHandler::property_handler(ModelHandler::PartAttribute attribute)
{
    switch(attribute.first){
    case CustomTypes::AttributeWheelSize:
        m_model_fork->setFilter(create_filter(CustomTypes::PartFork));
        m_model_frame->setFilter(create_filter(CustomTypes::PartFrame));
        m_model_front_wheel->setFilter(create_filter(CustomTypes::PartFrontWheel));
        break;
    case CustomTypes::AttributeAxleTypeFront:
        m_model_fork->setFilter(create_filter(CustomTypes::PartFork));
        m_model_front_wheel->setFilter(create_filter(CustomTypes::PartFrontWheel));
        break;
    }
}

void ModelHandler::init()
{
    m_map_part_table.insert(CustomTypes::PartFrame, "frame");
    m_map_part_table.insert(CustomTypes::PartFork, "fork");
    m_map_part_table.insert(CustomTypes::PartFrontWheel, "front_wheel");

    m_map_attribute_counter.insert(CustomTypes::AttributeWheelSize, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeAxleTypeFront, 0);

    emit map_part_table_ready(m_map_part_table);
}

void ModelHandler::set_model(CustomTypes::PartType part_type, QSqlTableModel* model)
{
    switch (part_type){
    case CustomTypes::PartFrame:
        m_model_frame = model;
        break;
    case CustomTypes::PartFork:
        m_model_fork = model;
        break;
    case CustomTypes::PartFrontWheel:
        m_model_front_wheel = model;
        break;
    }
}

void ModelHandler::set_properties(CustomTypes::PartType part_type, QList<QString> *list)
{
    switch(part_type){
    case CustomTypes::PartFork:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, list->at(2)));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, list->at(3)));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]++;
        break;
    case CustomTypes::PartFrame:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, list->at(2)));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        qDebug() << m_map_attribute_counter[CustomTypes::AttributeWheelSize];
        break;
    case CustomTypes::PartFrontWheel:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, list->at(2)));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, list->at(3)));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]++;
        break;
    }
}

void ModelHandler::clean_properties(CustomTypes::PartType part_type)
{
    switch(part_type){
    case CustomTypes::PartFork:
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]--;
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront] <= 0)
            setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, "-1"));
        break;
    case CustomTypes::PartFrame:
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        qDebug() << m_map_attribute_counter[CustomTypes::AttributeWheelSize];
        break;
    case CustomTypes::PartFrontWheel:
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]--;
        qDebug() << m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront];
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront] <= 0)
            setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, "-1"));
        break;
    }
}

void ModelHandler::set_selected_part(CustomTypes::PartType part_type, QList<QString>* list)
{
    for (int i = 0; i < m_model_selected_parts.rowCount(); ++i){
        QModelIndex index_part_type = m_model_selected_parts.index(i, TableProperties::SelectedParts::ColumnPartType);
        if (m_model_selected_parts.data(index_part_type).toInt() == part_type){
            QModelIndex index_part_name = m_model_selected_parts.index(i, TableProperties::SelectedParts::ColumnPartName);
            QModelIndex index_part_id = m_model_selected_parts.index(i, TableProperties::SelectedParts::ColumnPartID);
            m_model_selected_parts.setData(index_part_name, list->at(1));
            m_model_selected_parts.setData(index_part_id, list->at(0));
        }
    }
}

void ModelHandler::delete_selected_part(CustomTypes::PartType part_type)
{
    for (int i = 0; i < m_model_selected_parts.rowCount(); ++i){
        QModelIndex index_part_type = m_model_selected_parts.index(i, TableProperties::SelectedParts::ColumnPartType);
        if (m_model_selected_parts.data(index_part_type).toInt() == part_type){
            QModelIndex index_part_name = m_model_selected_parts.index(i, TableProperties::SelectedParts::ColumnPartName);
            QModelIndex index_part_id = m_model_selected_parts.index(i, TableProperties::SelectedParts::ColumnPartID);
            m_model_selected_parts.setData(index_part_name, "Nie wybrano części");
            m_model_selected_parts.setData(index_part_id, "-1");
        }
    }
    emit part_deleted(part_type);
}

QString ModelHandler::create_filter(CustomTypes::PartType part_type)
{
    QStringList filter_properties_list;
    switch(part_type){
    case CustomTypes::PartFork:
    {
        if (attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(attribute_wheel_size().second);
        }
        if (attribute_axle_type_front().second != "-1"){
            filter_properties_list << QString("axle_type_front = '%1'").arg(attribute_axle_type_front().second);
        }
        break;
    }
    case CustomTypes::PartFrame:
    {
        if (attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(attribute_wheel_size().second);
        }
        break;
    }
    case CustomTypes::PartFrontWheel:
    {
        if (attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(attribute_wheel_size().second);
        }
        if (attribute_axle_type_front().second != "-1"){
            filter_properties_list << QString("axle_type_front = '%1'").arg(attribute_axle_type_front().second);
        }
        break;
    }
    }
    qDebug() << filter_properties_list.join(" AND ");
    return filter_properties_list.join(" AND ");
}


void ModelHandler::setAttribute_wheel_size(PartAttribute attribute_wheel_size)
{
    if (m_attribute_wheel_size == attribute_wheel_size)
        return;

    m_attribute_wheel_size = attribute_wheel_size;
    emit attribute_wheel_sizeChanged(m_attribute_wheel_size);
}

void ModelHandler::setAttribute_axle_type_front(PartAttribute attribute_axle_type_front)
{
    if (m_attribute_axle_type_front == attribute_axle_type_front)
        return;

    m_attribute_axle_type_front = attribute_axle_type_front;
    emit attribute_axle_type_frontChanged(m_attribute_axle_type_front);
}

void ModelHandler::fill_selected_parts_model(QMap<CustomTypes::PartType, QString> map_part)
{
    for(auto e : map_part.keys()){
        QList<QStandardItem *> rowData;
        rowData << new QStandardItem(map_part.value(e));
        rowData << new QStandardItem("Nie wybrano części");
        rowData << new QStandardItem(QString("%1").arg(e));
        rowData << new QStandardItem("model");
        m_model_selected_parts.appendRow(rowData);
        m_model_selected_parts.setHeaderData(0, Qt::Horizontal, "Rodzaj części");
        m_model_selected_parts.setHeaderData(1, Qt::Horizontal, "Nazwa części");
        m_model_selected_parts.setHeaderData(2, Qt::Horizontal, "");
        emit selected_parts_model_ready(&m_model_selected_parts);
    }
}
