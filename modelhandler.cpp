#include "modelhandler.h"
#include "customtypes.h"
#include <QDebug>
#include <QDynamicPropertyChangeEvent>

ModelHandler::ModelHandler(QObject *parent) :
    QObject(parent),
    m_attribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"))
{
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
        set_filter(m_model_fork, create_filter(CustomTypes::PartFork));
        set_filter(m_model_frame, create_filter(CustomTypes::PartFrame));
        break;
    }
    }
}


void ModelHandler::set_filter(QSqlTableModel *model, QString filter)
{
    model->setFilter(filter);

}

void ModelHandler::set_properties(CustomTypes::PartType part_type, const QString value)
{
    switch(part_type){
    case CustomTypes::PartFork:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, value));
        break;
    case CustomTypes::PartFrame:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, value));
        break;
    }
}

void ModelHandler::set_model(QSqlTableModel* model, CustomTypes::PartType part_type)
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

void ModelHandler::init()
{
    m_map_part_table.insert(CustomTypes::PartFrame, "frame");
    m_map_part_table.insert(CustomTypes::PartFork, "fork");

    emit map_part_table_ready(m_map_part_table);
}

void ModelHandler::setAttribute_wheel_size(PartAttribute attribute_wheel_size)
{
    if (m_attribute_wheel_size == attribute_wheel_size)
        return;

    m_attribute_wheel_size = attribute_wheel_size;
    emit attribute_wheel_sizeChanged(m_attribute_wheel_size);
}
