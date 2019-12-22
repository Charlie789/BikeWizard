#include "modelhandler.h"
#include "customtypes.h"
#include <QDebug>
#include <QDynamicPropertyChangeEvent>

ModelHandler::ModelHandler(QObject *parent) :
    QObject(parent),
    m_attribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"))
{
    connect(this, &ModelHandler::map_part_table_ready, this, &ModelHandler::fill_selected_parts_model);
    connect(this, &ModelHandler::attribute_wheel_sizeChanged, this, &ModelHandler::property_handler);
}

ModelHandler::PartAttribute ModelHandler::attribute_wheel_size() const
{
    return m_attribute_wheel_size;
}

void ModelHandler::property_handler(ModelHandler::PartAttribute attribute)
{
    switch(attribute.first){
    case CustomTypes::AttributeWheelSize:
    {
        m_model_fork->setFilter(create_filter(CustomTypes::PartFork));
        m_model_frame->setFilter(create_filter(CustomTypes::PartFrame));
        break;
    }
    }
}

void ModelHandler::init()
{
    m_map_part_table.insert(CustomTypes::PartFrame, "frame");
    m_map_part_table.insert(CustomTypes::PartFork, "fork");

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
    }
}

void ModelHandler::set_properties(CustomTypes::PartType part_type, QModelIndexList* list)
{
    switch(part_type){
    case CustomTypes::PartFork:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, list->at(2).data().toString()));
        break;
    case CustomTypes::PartFrame:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, list->at(2).data().toString()));
        break;
    }
}

QString ModelHandler::create_filter(CustomTypes::PartType part_type)
{
    QStringList filter_properties_list;
    switch(part_type){
    case CustomTypes::PartFork:
    {
        if (attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = %1").arg(attribute_wheel_size().second);
        }
        break;
    }
    case CustomTypes::PartFrame:
    {
        if (attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = %1").arg(attribute_wheel_size().second);
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

void ModelHandler::fill_selected_parts_model(QMap<CustomTypes::PartType, QString> map_part)
{
    for(auto e : map_part.keys()){
        QList<QStandardItem *> rowData;
        rowData << new QStandardItem(map_part.value(e));
        rowData << new QStandardItem(QString("%1").arg(e));
        m_model_selected_parts.appendRow(rowData);
        emit selected_parts_model_ready(&m_model_selected_parts);
    }
}
