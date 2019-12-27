#include "modelhandler.h"
#include "customtypes.h"
#include <QDebug>
#include <QDynamicPropertyChangeEvent>

ModelHandler::ModelHandler(QObject *parent) :
    QObject(parent),
    m_attribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1")),
    m_attribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, "-1")),
    m_attribute_axle_type_rear(PartAttribute(CustomTypes::AttributeAxleTypeRear, "-1")),
    m_attribute_steerer_tube_diameter(PartAttribute(CustomTypes::AttributeSteererTubeDiameter, "-1")),
    m_attribute_headset(PartAttribute(CustomTypes::AttributeHeadset, "-1"))
{
    connect(this, &ModelHandler::map_part_table_ready, this, &ModelHandler::fill_selected_parts_model);
    connect(this, &ModelHandler::part_deleted, this, &ModelHandler::clean_properties);
    connect(this, &ModelHandler::attribute_wheel_sizeChanged, this, &ModelHandler::property_handler);
    connect(this, &ModelHandler::attribute_axle_type_frontChanged, this, &ModelHandler::property_handler);
    connect(this, &ModelHandler::attribute_axle_type_rearChanged, this, &ModelHandler::property_handler);
    connect(this, &ModelHandler::attribute_steerer_tube_diameterChanged, this, &ModelHandler::property_handler);
    connect(this, &ModelHandler::attribute_headsetChanged, this, &ModelHandler::property_handler);
}

ModelHandler::PartAttribute ModelHandler::attribute_wheel_size() const
{
    return m_attribute_wheel_size;
}

ModelHandler::PartAttribute ModelHandler::attribute_axle_type_front() const
{
    return m_attribute_axle_type_front;
}

ModelHandler::PartAttribute ModelHandler::attribute_axle_type_rear() const
{
    return m_attribute_axle_type_rear;
}

ModelHandler::PartAttribute ModelHandler::attribute_steerer_tube_diameter() const
{
    return m_attribute_steerer_tube_diameter;
}

ModelHandler::PartAttribute ModelHandler::attribute_headset() const
{
    return m_attribute_headset;
}

void ModelHandler::property_handler(ModelHandler::PartAttribute attribute)
{
    switch(attribute.first){
    case CustomTypes::AttributeWheelSize:
        m_model_fork->setFilter(create_filter(CustomTypes::PartFork));
        m_model_frame->setFilter(create_filter(CustomTypes::PartFrame));
        m_model_front_wheel->setFilter(create_filter(CustomTypes::PartFrontWheel));
        m_model_rear_wheel->setFilter(create_filter(CustomTypes::PartRearWheel));
        break;
    case CustomTypes::AttributeAxleTypeFront:
        m_model_fork->setFilter(create_filter(CustomTypes::PartFork));
        m_model_front_wheel->setFilter(create_filter(CustomTypes::PartFrontWheel));
        break;
    case CustomTypes::AttributeAxleTypeRear:
        m_model_frame->setFilter(create_filter(CustomTypes::PartFrame));
        m_model_rear_wheel->setFilter(create_filter(CustomTypes::PartRearWheel));
    case CustomTypes::AttributeSteererTubeDiameter:
        m_model_fork->setFilter(create_filter(CustomTypes::PartFork));
        m_model_headset->setFilter(create_filter(CustomTypes::PartHeadset));
    case CustomTypes::AttributeHeadset:
        m_model_headset->setFilter(create_filter(CustomTypes::PartHeadset));
        m_model_frame->setFilter(create_filter(CustomTypes::PartFrame));
        m_model_fork->setFilter(create_filter(CustomTypes::PartFork));
    }
}

void ModelHandler::init()
{
    QMap<CustomTypes::AttributeName, int> m_map_part_column_index;

    m_map_part_table.insert(CustomTypes::PartFrame, "frame_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeAxleTypeRear, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeHeadset, 5);
    m_map_column_index.insert(CustomTypes::PartFrame, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartFork, "fork_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeAxleTypeFront, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeSteererTubeDiameter, 5);
    m_map_column_index.insert(CustomTypes::PartFork, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartFrontWheel, "front_wheel_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeAxleTypeFront, 4);
    m_map_column_index.insert(CustomTypes::PartFrontWheel, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartRearWheel, "rear_wheel_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeAxleTypeRear, 4);
    m_map_column_index.insert(CustomTypes::PartRearWheel, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartHeadset, "headset_view");
    m_map_part_column_index.insert(CustomTypes::AttributeHeadset, 3);
    m_map_column_index.insert(CustomTypes::PartHeadset, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_attribute_counter.insert(CustomTypes::AttributeWheelSize, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeAxleTypeFront, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeAxleTypeRear, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeHeadset, 0);

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
    case CustomTypes::PartRearWheel:
        m_model_rear_wheel = model;
        break;
    case CustomTypes::PartHeadset:
        m_model_headset = model;
        break;
    }
}

void ModelHandler::set_properties(CustomTypes::PartType part_type, QList<QString> *list)
{
    switch(part_type){
    case CustomTypes::PartFork:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize,
                                              list->at(m_map_column_index[CustomTypes::PartFork][CustomTypes::AttributeWheelSize])));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront,
                                                   list->at(m_map_column_index[CustomTypes::PartFork][CustomTypes::AttributeAxleTypeFront])));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]++;
        setAttribute_steerer_tube_diameter(PartAttribute(CustomTypes::AttributeSteererTubeDiameter,
                                                   list->at(m_map_column_index[CustomTypes::PartFork][CustomTypes::AttributeSteererTubeDiameter])));
        m_map_attribute_counter[CustomTypes::AttributeSteererTubeDiameter]++;
        break;
    case CustomTypes::PartFrame:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize,
                                              list->at(m_map_column_index[CustomTypes::PartFrame][CustomTypes::AttributeWheelSize])));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        setAttribute_axle_type_rear(PartAttribute(CustomTypes::AttributeAxleTypeRear,
                                                  list->at(m_map_column_index[CustomTypes::PartFrame][CustomTypes::AttributeAxleTypeRear])));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear]++;
        setAttribute_headset(PartAttribute(CustomTypes::AttributeHeadset,
                                                  list->at(m_map_column_index[CustomTypes::PartFrame][CustomTypes::AttributeHeadset])));
        m_map_attribute_counter[CustomTypes::AttributeHeadset]++;
        break;
    case CustomTypes::PartFrontWheel:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize,
                                              list->at(m_map_column_index[CustomTypes::PartFrontWheel][CustomTypes::AttributeWheelSize])));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront,
                                                   list->at(m_map_column_index[CustomTypes::PartFrontWheel][CustomTypes::AttributeAxleTypeFront])));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]++;
        break;
    case CustomTypes::PartRearWheel:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize,
                                              list->at(m_map_column_index[CustomTypes::PartRearWheel][CustomTypes::AttributeWheelSize])));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        setAttribute_axle_type_rear(PartAttribute(CustomTypes::AttributeAxleTypeRear,
                                                  list->at(m_map_column_index[CustomTypes::PartRearWheel][CustomTypes::AttributeAxleTypeRear])));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear]++;
        break;
    case CustomTypes::PartHeadset:
        setAttribute_headset(PartAttribute(CustomTypes::AttributeHeadset,
                                                  list->at(m_map_column_index[CustomTypes::PartHeadset][CustomTypes::AttributeHeadset])));
        m_map_attribute_counter[CustomTypes::AttributeHeadset]++;
        break;
    }
}

void ModelHandler::clean_properties(CustomTypes::PartType part_type)
{
    switch(part_type){
    case CustomTypes::PartFork:
    {
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]--;
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront] <= 0)
            setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeSteererTubeDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSteererTubeDiameter] <= 0)
            setAttribute_steerer_tube_diameter(PartAttribute(CustomTypes::AttributeSteererTubeDiameter, "-1"));
        break;
    }
    case CustomTypes::PartFrame:
    {
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear]--;
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear] <= 0)
            setAttribute_axle_type_rear(PartAttribute(CustomTypes::AttributeAxleTypeRear, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeHeadset]--;
        if (m_map_attribute_counter[CustomTypes::AttributeHeadset] <= 0)
            setAttribute_headset(PartAttribute(CustomTypes::AttributeHeadset, "-1"));
        break;
    }
    case CustomTypes::PartFrontWheel:
    {
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]--;
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront] <= 0)
            setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, "-1"));
        break;
    }
    case CustomTypes::PartRearWheel:
    {
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear]--;
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear] <= 0)
            setAttribute_axle_type_rear(PartAttribute(CustomTypes::AttributeAxleTypeRear, "-1"));
    }
    case CustomTypes::PartHeadset:
        m_map_attribute_counter[CustomTypes::AttributeHeadset]--;
        if (m_map_attribute_counter[CustomTypes::AttributeHeadset] <= 0)
            setAttribute_headset(PartAttribute(CustomTypes::AttributeHeadset, "-1"));
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
        if (attribute_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter = '%1'").arg(attribute_steerer_tube_diameter().second);
        }
        if (attribute_headset().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter IN (SELECT steerer_tube_diameter FROM headset_compatibility WHERE shis = '%1')").arg(attribute_headset().second);
        }
        break;
    }
    case CustomTypes::PartFrame:
    {
        if (attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(attribute_wheel_size().second);
        }
        if (attribute_axle_type_rear().second != "-1"){
            filter_properties_list << QString("axle_type_rear = '%1'").arg(attribute_axle_type_rear().second);
        }
        if (attribute_headset().second != "-1"){
            filter_properties_list << QString("shis = '%1'").arg(attribute_headset().second);
        }
        if (attribute_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("shis IN (SELECT shis FROM headset_compatibility WHERE steerer_tube_diameter = '%1')").arg(attribute_steerer_tube_diameter().second);
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
    case CustomTypes::PartRearWheel:
    {
        if (attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(attribute_wheel_size().second);
        }
        if (attribute_axle_type_rear().second != "-1"){
            filter_properties_list << QString("axle_type_rear = '%1'").arg(attribute_axle_type_rear().second);
        }
        break;
    }
    case CustomTypes::PartHeadset:
    {
        if (attribute_headset().second != "-1"){
            filter_properties_list << QString("shis = '%1'").arg(attribute_headset().second);
        }
        if (attribute_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("shis IN (SELECT shis FROM headset_compatibility WHERE steerer_tube_diameter = '%1')").arg(attribute_steerer_tube_diameter().second);
        }
        break;
    }
    }
    qDebug() << part_type << filter_properties_list.join(" AND ");
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

void ModelHandler::setAttribute_axle_type_rear(ModelHandler::PartAttribute attribute_axle_type_rear)
{
    if (m_attribute_axle_type_rear == attribute_axle_type_rear)
        return;

    m_attribute_axle_type_rear = attribute_axle_type_rear;
    emit attribute_axle_type_rearChanged(m_attribute_axle_type_rear);
}

void ModelHandler::setAttribute_steerer_tube_diameter(ModelHandler::PartAttribute attribute_steerer_tube_diameter)
{
    if (m_attribute_steerer_tube_diameter == attribute_steerer_tube_diameter)
        return;

    m_attribute_steerer_tube_diameter = attribute_steerer_tube_diameter;
    emit attribute_steerer_tube_diameterChanged(m_attribute_steerer_tube_diameter);
}

void ModelHandler::setAttribute_headset(ModelHandler::PartAttribute attribute_headset)
{
    if (m_attribute_headset == attribute_headset)
        return;

    m_attribute_headset = attribute_headset;
    emit attribute_headsetChanged(m_attribute_headset);
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
