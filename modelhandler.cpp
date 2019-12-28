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
    m_attribute_headset(PartAttribute(CustomTypes::AttributeHeadset, "-1")),
    m_attribute_handlebar_diameter(PartAttribute(CustomTypes::AttributeHandlebarDiameter, "-1")),
    m_attribute_stem_steerer_tube_diameter(PartAttribute(CustomTypes::AttributeStemSteererTubeDiameter, "-1")),
    m_attribute_seatpost_diameter(PartAttribute(CustomTypes::AttributeSeatpostDiameter, "-1")),
    m_attribute_saddle_mounting(PartAttribute(CustomTypes::AttributeSaddleMounting, "-1")),
    m_attribute_tire_width(PartAttribute(CustomTypes::AttributeTireWidth, "-1")),
    m_attribute_bb_type(PartAttribute(CustomTypes::AttributeBBType, "-1")),
    m_attribute_bb_axis_type(PartAttribute(CustomTypes::AttributeBBAxisType, "-1")),
    m_attribute_bb_axis_length(PartAttribute(CustomTypes::AttributeBBAxisLength, "-1"))

{
    connect(this, &ModelHandler::map_part_table_ready, this, &ModelHandler::fill_selected_parts_model);
    connect(this, &ModelHandler::part_deleted, this, &ModelHandler::clean_properties);
    connect(this, &ModelHandler::attribute_wheel_sizeChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_axle_type_frontChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_axle_type_rearChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_steerer_tube_diameterChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_headsetChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_handlebar_diameterChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_stem_steerer_tube_diameterChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_seatpost_diameterChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_saddle_mountingChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_tire_widthChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_bb_typeChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_bb_axis_typeChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_bb_axis_lengthChanged, this, &ModelHandler::filter_handler);
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

ModelHandler::PartAttribute ModelHandler::attribute_handlebar_diameter() const
{
    return m_attribute_handlebar_diameter;
}

ModelHandler::PartAttribute ModelHandler::attribute_stem_steerer_tube_diameter() const
{
    return m_attribute_stem_steerer_tube_diameter;
}

ModelHandler::PartAttribute ModelHandler::attribute_seatpost_diameter() const
{
    return m_attribute_seatpost_diameter;
}

ModelHandler::PartAttribute ModelHandler::attribute_saddle_mounting() const
{
    return m_attribute_saddle_mounting;
}

ModelHandler::PartAttribute ModelHandler::attribute_tire_width() const
{
    return m_attribute_tire_width;
}

ModelHandler::PartAttribute ModelHandler::attribute_bb_type() const
{
    return m_attribute_bb_type;
}

ModelHandler::PartAttribute ModelHandler::attribute_bb_axis_type() const
{
    return m_attribute_bb_axis_type;
}

ModelHandler::PartAttribute ModelHandler::attribute_bb_axis_length() const
{
    return m_attribute_bb_axis_length;
}

void ModelHandler::filter_handler(ModelHandler::PartAttribute)
{
    m_model_frame->setFilter(create_filter(CustomTypes::PartFrame));
    m_model_fork->setFilter(create_filter(CustomTypes::PartFork));
    m_model_front_wheel->setFilter(create_filter(CustomTypes::PartFrontWheel));
    m_model_rear_wheel->setFilter(create_filter(CustomTypes::PartRearWheel));
    m_model_headset->setFilter(create_filter(CustomTypes::PartHeadset));
    m_model_handlebar->setFilter(create_filter(CustomTypes::PartHandlebar));
    m_model_stem->setFilter(create_filter(CustomTypes::PartStem));
    m_model_seatpost->setFilter(create_filter(CustomTypes::PartSeatpost));
    m_model_saddle->setFilter(create_filter(CustomTypes::PartSaddle));
    m_model_tire->setFilter(create_filter(CustomTypes::PartTire));
    m_model_inner_tube->setFilter(create_filter(CustomTypes::PartInnerTube));
    m_model_bb->setFilter(create_filter(CustomTypes::PartBB));
    m_model_grip->setFilter(create_filter(CustomTypes::PartGrip));
}

void ModelHandler::init()
{
    QMap<CustomTypes::AttributeName, int> m_map_part_column_index;

    m_map_part_table.insert(CustomTypes::PartFrame, "frame_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeAxleTypeRear, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeHeadset, 5);
    m_map_part_column_index.insert(CustomTypes::AttributeSeatpostDiameter, 6);
    m_map_part_column_index.insert(CustomTypes::AttributeBBType, 7);
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

    m_map_part_table.insert(CustomTypes::PartHandlebar, "handlebar_view");
    m_map_part_column_index.insert(CustomTypes::AttributeHandlebarDiameter, 3);
    m_map_column_index.insert(CustomTypes::PartHandlebar, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartStem, "stem_view");
    m_map_part_column_index.insert(CustomTypes::AttributeHandlebarDiameter, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeStemSteererTubeDiameter, 4);
    m_map_column_index.insert(CustomTypes::PartStem, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartSeatpost, "seatpost_view");
    m_map_part_column_index.insert(CustomTypes::AttributeSeatpostDiameter, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeSaddleMounting, 4);
    m_map_column_index.insert(CustomTypes::PartSeatpost, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartSaddle, "saddle_view");
    m_map_part_column_index.insert(CustomTypes::AttributeSaddleMounting, 3);
    m_map_column_index.insert(CustomTypes::PartSaddle, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartTire, "tire_view");
    m_map_part_column_index.insert(CustomTypes::AttributeTireWidth, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 4);
    m_map_column_index.insert(CustomTypes::PartTire, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartInnerTube, "inner_tube_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 5);
    m_map_column_index.insert(CustomTypes::PartInnerTube, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartBB, "bottom_bracket_view");
    m_map_part_column_index.insert(CustomTypes::AttributeBBAxisLength, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeBBType, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeBBAxisType, 5);
    m_map_column_index.insert(CustomTypes::PartBB, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartGrip, "grip_view");

    m_map_attribute_counter.insert(CustomTypes::AttributeWheelSize, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeAxleTypeFront, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeAxleTypeRear, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeHeadset, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeHandlebarDiameter, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeStemSteererTubeDiameter, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeSeatpostDiameter, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeSaddleMounting, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeTireWidth, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeBBType, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeBBAxisType, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeBBAxisLength, 0);

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
    case CustomTypes::PartHandlebar:
        m_model_handlebar = model;
        break;
    case CustomTypes::PartStem:
        m_model_stem = model;
        break;
    case CustomTypes::PartSeatpost:
        m_model_seatpost = model;
        break;
    case CustomTypes::PartSaddle:
        m_model_saddle = model;
        break;
    case CustomTypes::PartTire:
        m_model_tire = model;
        break;
    case CustomTypes::PartInnerTube:
        m_model_inner_tube = model;
        break;
    case CustomTypes::PartBB:
        m_model_bb = model;
        break;
    case CustomTypes::PartGrip:
        m_model_grip = model;
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
        setAttribute_seatpost_diameter(PartAttribute(CustomTypes::AttributeSeatpostDiameter,
                                                  list->at(m_map_column_index[CustomTypes::PartFrame][CustomTypes::AttributeSeatpostDiameter])));
        m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter]++;
        setAttribute_bb_type(PartAttribute(CustomTypes::AttributeBBType,
                                                  list->at(m_map_column_index[CustomTypes::PartFrame][CustomTypes::AttributeBBType])));
        m_map_attribute_counter[CustomTypes::AttributeBBType]++;
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
    case CustomTypes::PartHandlebar:
        setAttribute_handlebar_diameter(PartAttribute(CustomTypes::AttributeHandlebarDiameter,
                                                  list->at(m_map_column_index[CustomTypes::PartHandlebar][CustomTypes::AttributeHandlebarDiameter])));
        m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter]++;
        break;
    case CustomTypes::PartStem:
        setAttribute_handlebar_diameter(PartAttribute(CustomTypes::AttributeHandlebarDiameter,
                                                  list->at(m_map_column_index[CustomTypes::PartStem][CustomTypes::AttributeHandlebarDiameter])));
        m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter]++;
        setAttribute_stem_steerer_tube_diameter(PartAttribute(CustomTypes::AttributeStemSteererTubeDiameter,
                                                  list->at(m_map_column_index[CustomTypes::PartStem][CustomTypes::AttributeStemSteererTubeDiameter])));
        m_map_attribute_counter[CustomTypes::AttributeStemSteererTubeDiameter]++;
        break;
    case CustomTypes::PartSeatpost:
        setAttribute_seatpost_diameter(PartAttribute(CustomTypes::AttributeSeatpostDiameter,
                                                  list->at(m_map_column_index[CustomTypes::PartSeatpost][CustomTypes::AttributeSeatpostDiameter])));
        m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter]++;
        setAttribute_saddle_mounting(PartAttribute(CustomTypes::AttributeSaddleMounting,
                                                  list->at(m_map_column_index[CustomTypes::PartSeatpost][CustomTypes::AttributeSaddleMounting])));
        m_map_attribute_counter[CustomTypes::AttributeSaddleMounting]++;
        break;
    case CustomTypes::PartSaddle:
        setAttribute_saddle_mounting(PartAttribute(CustomTypes::AttributeSaddleMounting,
                                                  list->at(m_map_column_index[CustomTypes::PartSaddle][CustomTypes::AttributeSaddleMounting])));
        m_map_attribute_counter[CustomTypes::AttributeSaddleMounting]++;
        break;
    case CustomTypes::PartTire:
        setAttribute_tire_width(PartAttribute(CustomTypes::AttributeTireWidth,
                                                  list->at(m_map_column_index[CustomTypes::PartTire][CustomTypes::AttributeTireWidth])));
        m_map_attribute_counter[CustomTypes::AttributeTireWidth]++;
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize,
                                              list->at(m_map_column_index[CustomTypes::PartTire][CustomTypes::AttributeWheelSize])));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        break;
    case CustomTypes::PartInnerTube:
        break;
    case CustomTypes::PartBB:
        setAttribute_bb_type(PartAttribute(CustomTypes::AttributeBBType,
                                                  list->at(m_map_column_index[CustomTypes::PartBB][CustomTypes::AttributeBBType])));
        m_map_attribute_counter[CustomTypes::AttributeBBType]++;
        setAttribute_bb_axis_type(PartAttribute(CustomTypes::AttributeBBAxisType,
                                                  list->at(m_map_column_index[CustomTypes::PartBB][CustomTypes::AttributeBBAxisType])));
        m_map_attribute_counter[CustomTypes::AttributeBBAxisType]++;
        setAttribute_bb_axis_length(PartAttribute(CustomTypes::AttributeBBAxisLength,
                                                  list->at(m_map_column_index[CustomTypes::PartBB][CustomTypes::AttributeBBAxisLength])));
        m_map_attribute_counter[CustomTypes::AttributeBBAxisLength]++;
        break;
    case CustomTypes::PartGrip:
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
        m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter] <= 0)
            setAttribute_seatpost_diameter(PartAttribute(CustomTypes::AttributeSeatpostDiameter, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeBBType]--;
        if (m_map_attribute_counter[CustomTypes::AttributeBBType] <= 0)
            setAttribute_bb_type(PartAttribute(CustomTypes::AttributeBBType, "-1"));
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
        break;
    }
    case CustomTypes::PartHeadset:
    {
        m_map_attribute_counter[CustomTypes::AttributeHeadset]--;
        if (m_map_attribute_counter[CustomTypes::AttributeHeadset] <= 0)
            setAttribute_headset(PartAttribute(CustomTypes::AttributeHeadset, "-1"));
        break;
    }
    case CustomTypes::PartHandlebar:
    {
        m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter] <= 0)
            setAttribute_handlebar_diameter(PartAttribute(CustomTypes::AttributeHandlebarDiameter, "-1"));
        break;
    }
    case CustomTypes::PartStem:
    {
        m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter] <= 0)
            setAttribute_handlebar_diameter(PartAttribute(CustomTypes::AttributeHandlebarDiameter, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeStemSteererTubeDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeStemSteererTubeDiameter] <= 0)
            setAttribute_stem_steerer_tube_diameter(PartAttribute(CustomTypes::AttributeStemSteererTubeDiameter, "-1"));
        break;
    }
    case CustomTypes::PartSeatpost:
    {
        m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter] <= 0)
            setAttribute_seatpost_diameter(PartAttribute(CustomTypes::AttributeSeatpostDiameter, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeSaddleMounting]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSaddleMounting] <= 0)
            setAttribute_saddle_mounting(PartAttribute(CustomTypes::AttributeSaddleMounting, "-1"));
        break;
    }
    case CustomTypes::PartSaddle:
    {
        m_map_attribute_counter[CustomTypes::AttributeSaddleMounting]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSaddleMounting] <= 0)
            setAttribute_saddle_mounting(PartAttribute(CustomTypes::AttributeSaddleMounting, "-1"));
        break;
    }
    case CustomTypes::PartTire:
    {
        m_map_attribute_counter[CustomTypes::AttributeTireWidth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeTireWidth] <= 0)
            setAttribute_tire_width(PartAttribute(CustomTypes::AttributeTireWidth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        break;
    }
    case CustomTypes::PartInnerTube:
    {
        break;
    }
    case CustomTypes::PartBB:
    {
        m_map_attribute_counter[CustomTypes::AttributeBBType]--;
        if (m_map_attribute_counter[CustomTypes::AttributeBBType] <= 0)
            setAttribute_bb_type(PartAttribute(CustomTypes::AttributeBBType, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeBBAxisType]--;
        if (m_map_attribute_counter[CustomTypes::AttributeBBAxisType] <= 0)
            setAttribute_bb_axis_type(PartAttribute(CustomTypes::AttributeBBAxisType, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeBBAxisLength]--;
        if (m_map_attribute_counter[CustomTypes::AttributeBBAxisLength] <= 0)
            setAttribute_bb_axis_length(PartAttribute(CustomTypes::AttributeBBAxisLength, "-1"));
        break;
    }
    case CustomTypes::PartGrip:
    {
        break;
    }
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
        if (attribute_stem_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter IN (SELECT steerer_tube_diameter FROM steerer_tube_diameter_compatibility WHERE stem_tube_diameter = '%1')").arg(attribute_stem_steerer_tube_diameter().second);
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
        if (attribute_stem_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("shis IN (SELECT shis FROM headset_compatibility WHERE steerer_tube_diameter IN (SELECT steerer_tube_diameter FROM steerer_tube_diameter_compatibility WHERE stem_tube_diameter = '%1'))").arg(attribute_stem_steerer_tube_diameter().second);
        }
        if (attribute_seatpost_diameter().second != "-1"){
            filter_properties_list << QString("seatpost_diameter = '%1'").arg(attribute_seatpost_diameter().second);
        }
        if (attribute_bb_type().second != "-1"){
            filter_properties_list << QString("bb_type = '%1'").arg(attribute_bb_type().second);
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
        if (attribute_stem_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("shis IN (SELECT shis FROM headset_compatibility WHERE steerer_tube_diameter IN (SELECT steerer_tube_diameter FROM steerer_tube_diameter_compatibility WHERE stem_tube_diameter = '%1'))").arg(attribute_stem_steerer_tube_diameter().second);
        }
        break;
    }
    case CustomTypes::PartHandlebar:
    {
        if (attribute_handlebar_diameter().second != "-1"){
            filter_properties_list << QString("handlebar_diameter = '%1'").arg(attribute_handlebar_diameter().second);
        }
        break;
    }
    case CustomTypes::PartStem:
    {
        if (attribute_handlebar_diameter().second != "-1"){
            filter_properties_list << QString("handlebar_diameter = '%1'").arg(attribute_handlebar_diameter().second);
        }
        if (attribute_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter IN (SELECT stem_tube_diameter FROM steerer_tube_diameter_compatibility WHERE steerer_tube_diameter = '%1')").arg(attribute_steerer_tube_diameter().second);
        }
        if (attribute_headset().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter IN (SELECT stem_tube_diameter FROM steerer_tube_diameter_compatibility WHERE steerer_tube_diameter in (SELECT steerer_tube_diameter FROM headset_compatibility WHERE shis = '%1'))").arg(attribute_headset().second);
        }
        break;
    }
    case CustomTypes::PartSeatpost:
    {
        if (attribute_seatpost_diameter().second != "-1"){
            filter_properties_list << QString("seatpost_diameter = '%1'").arg(attribute_seatpost_diameter().second);
        }
        if (attribute_saddle_mounting().second != "-1"){
            filter_properties_list << QString("saddle_mounting = '%1'").arg(attribute_saddle_mounting().second);
        }
        break;
    }
    case CustomTypes::PartSaddle:
    {
        if (attribute_saddle_mounting().second != "-1"){
            filter_properties_list << QString("saddle_mounting = '%1'").arg(attribute_saddle_mounting().second);
        }
        break;
    }
    case CustomTypes::PartTire:
    {
        if (attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(attribute_wheel_size().second);
        }
        break;
    }
    case CustomTypes::PartInnerTube:
    {
        if (attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(attribute_wheel_size().second);
        }
        if (attribute_tire_width().second != "-1"){
            filter_properties_list << QString("min_tire_width <= '%1' AND max_tire_width >= '%1'").arg(attribute_tire_width().second);
        }
        break;
    }
    case CustomTypes::PartBB:
    {
        if (attribute_bb_type().second != "-1"){
            filter_properties_list << QString("bb_type = '%1'").arg(attribute_bb_type().second);
        }
        if (attribute_bb_axis_type().second != "-1"){
            filter_properties_list << QString("bb_axis_type = '%1'").arg(attribute_bb_axis_type().second);
        }
        if (attribute_bb_axis_length().second != "-1" && attribute_bb_axis_length().second != "0"){
            filter_properties_list << QString("bb_axis_length = '%1'").arg(attribute_bb_axis_length().second);
        }
        break;
    }
    case CustomTypes::PartGrip:
    {
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

void ModelHandler::setAttribute_handlebar_diameter(ModelHandler::PartAttribute attribute_handlebar_diameter)
{
    if (m_attribute_handlebar_diameter == attribute_handlebar_diameter)
        return;

    m_attribute_handlebar_diameter = attribute_handlebar_diameter;
    emit attribute_handlebar_diameterChanged(m_attribute_handlebar_diameter);
}

void ModelHandler::setAttribute_stem_steerer_tube_diameter(ModelHandler::PartAttribute attribute_stem_steerer_tube_diameter)
{
    if (m_attribute_stem_steerer_tube_diameter == attribute_stem_steerer_tube_diameter)
        return;

    m_attribute_stem_steerer_tube_diameter = attribute_stem_steerer_tube_diameter;
    emit attribute_stem_steerer_tube_diameterChanged(m_attribute_stem_steerer_tube_diameter);
}

void ModelHandler::setAttribute_seatpost_diameter(ModelHandler::PartAttribute attribute_seatpost_diameter)
{
    if (m_attribute_seatpost_diameter == attribute_seatpost_diameter)
        return;

    m_attribute_seatpost_diameter = attribute_seatpost_diameter;
    emit attribute_seatpost_diameterChanged(m_attribute_seatpost_diameter);
}

void ModelHandler::setAttribute_saddle_mounting(ModelHandler::PartAttribute attribute_saddle_mounting)
{
    if (m_attribute_saddle_mounting == attribute_saddle_mounting)
        return;

    m_attribute_saddle_mounting = attribute_saddle_mounting;
    emit attribute_saddle_mountingChanged(m_attribute_saddle_mounting);
}

void ModelHandler::setAttribute_tire_width(ModelHandler::PartAttribute attribute_tire_width)
{
    if (m_attribute_tire_width == attribute_tire_width)
        return;

    m_attribute_tire_width = attribute_tire_width;
    emit attribute_tire_widthChanged(m_attribute_tire_width);
}

void ModelHandler::setAttribute_bb_type(ModelHandler::PartAttribute attribute_bb_type)
{
    if (m_attribute_bb_type == attribute_bb_type)
        return;

    m_attribute_bb_type = attribute_bb_type;
    emit attribute_bb_typeChanged(m_attribute_bb_type);
}

void ModelHandler::setAttribute_bb_axis_type(ModelHandler::PartAttribute attribute_bb_axis_type)
{
    if (m_attribute_bb_axis_type == attribute_bb_axis_type)
        return;

    m_attribute_bb_axis_type = attribute_bb_axis_type;
    emit attribute_bb_axis_typeChanged(m_attribute_bb_axis_type);
}

void ModelHandler::setAttribute_bb_axis_length(ModelHandler::PartAttribute attribute_bb_axis_length)
{
    if (m_attribute_bb_axis_length == attribute_bb_axis_length)
        return;

    m_attribute_bb_axis_length = attribute_bb_axis_length;
    emit attribute_bb_axis_lengthChanged(m_attribute_bb_axis_length);
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
