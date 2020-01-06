#include "modelhandler.h"
#include "customtypes.h"
#include <QDebug>
#include <QDynamicPropertyChangeEvent>

ModelHandler::ModelHandler(QObject *parent) :
    QObject(parent)
{
    connect(this, &ModelHandler::map_part_table_ready, this, &ModelHandler::fill_selected_parts_model);
    connect(this, &ModelHandler::part_deleted, this, &ModelHandler::clean_properties);
    connect(this, &ModelHandler::send_selected_part, this, &ModelHandler::set_properties);
    connect(this, &ModelHandler::send_selected_part, this, &ModelHandler::set_selected_part);
}

void ModelHandler::filter_handler(PartAttribute)
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
    m_model_cassette->setFilter(create_filter(CustomTypes::PartCassette));
    m_model_chain->setFilter(create_filter(CustomTypes::PartChain));
    m_model_rear_derailleur->setFilter(create_filter(CustomTypes::PartRearDerailleur));
    m_model_front_derailleur->setFilter(create_filter(CustomTypes::PartFrontDerailleur));
    m_model_crank->setFilter(create_filter(CustomTypes::PartCrank));
    m_model_front_shifter->setFilter(create_filter(CustomTypes::PartFrontShifter));
    m_model_rear_shifter->setFilter(create_filter(CustomTypes::PartRearShifter));
    m_model_front_disc->setFilter(create_filter(CustomTypes::PartFrontDisc));
    m_model_rear_disc->setFilter(create_filter(CustomTypes::PartRearDisc));
    m_model_front_disc_brake_set->setFilter(create_filter(CustomTypes::PartFrontDiscBrakeSet));
    m_model_rear_disc_brake_set->setFilter(create_filter(CustomTypes::PartRearDiscBrakeSet));
    m_model_front_vbrake->setFilter(create_filter(CustomTypes::PartFrontVBrake));
    m_model_rear_vbrake->setFilter(create_filter(CustomTypes::PartRearVBrake));
    m_model_front_lever->setFilter(create_filter(CustomTypes::PartFrontLever));
    m_model_rear_lever->setFilter(create_filter(CustomTypes::PartRearLever));
}

void ModelHandler::init_db()
{
    QMap<CustomTypes::AttributeName, int> m_map_part_column_index;

    m_map_part_table.insert(CustomTypes::PartFrame, "frame_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeAxleTypeRear, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeHeadset, 5);
    m_map_part_column_index.insert(CustomTypes::AttributeSeatpostDiameter, 6);
    m_map_part_column_index.insert(CustomTypes::AttributeBBType, 7);
    m_map_part_column_index.insert(CustomTypes::AttributeFrontDerailleurMount, 8);
    m_map_part_column_index.insert(CustomTypes::AttributeRearVBrakeMount, 9);
    m_map_part_column_index.insert(CustomTypes::AttributeRearDiscBrakeMount, 10);
    m_map_column_index.insert(CustomTypes::PartFrame, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartFork, "fork_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeAxleTypeFront, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeSteererTubeDiameter, 5);
    m_map_part_column_index.insert(CustomTypes::AttributeFrontVBrakeMount, 6);
    m_map_part_column_index.insert(CustomTypes::AttributeFrontDiscBrakeMount, 7);
    m_map_column_index.insert(CustomTypes::PartFork, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartFrontWheel, "front_wheel_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeAxleTypeFront, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeFrontDiscMount, 5);
    m_map_part_column_index.insert(CustomTypes::AttributeFrontVBrakeMount, 6);
    m_map_column_index.insert(CustomTypes::PartFrontWheel, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartRearWheel, "rear_wheel_view");
    m_map_part_column_index.insert(CustomTypes::AttributeWheelSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeAxleTypeRear, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeRearDiscMount, 5);
    m_map_part_column_index.insert(CustomTypes::AttributeRearVBrakeMount, 6);
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

    m_map_part_table.insert(CustomTypes::PartCassette, "cassette_view");
    m_map_part_column_index.insert(CustomTypes::AttributeChainSpeed, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeMinSprocketTooth, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeMaxSprocketTooth, 5);
    m_map_column_index.insert(CustomTypes::PartCassette, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartChain, "chain_view");
    m_map_part_column_index.insert(CustomTypes::AttributeChainSpeed, 3);
    m_map_column_index.insert(CustomTypes::PartChain, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartRearDerailleur, "rear_derailleur_view");
    m_map_part_column_index.insert(CustomTypes::AttributeChainSpeed, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeMinDerailleurTooth, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeMaxDerailleurTooth, 5);
    m_map_column_index.insert(CustomTypes::PartRearDerailleur, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartFrontDerailleur, "front_derailleur_view");
    m_map_part_column_index.insert(CustomTypes::AttributeFrontDerailleurMount, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeCrankSpeed, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeMaxFrontDerailleurTooth, 5);
    m_map_part_column_index.insert(CustomTypes::AttributeMinFrontDerailleurTooth, 6);
    m_map_part_column_index.insert(CustomTypes::AttributeChainSpeed, 7);
    m_map_part_column_index.insert(CustomTypes::AttributeChainLine, 8);
    m_map_column_index.insert(CustomTypes::PartFrontDerailleur, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartCrank, "crank_view");
    m_map_part_column_index.insert(CustomTypes::AttributeMaxCrankTooth, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeCrankSpeed, 4);
    m_map_part_column_index.insert(CustomTypes::AttributeChainLine, 5);
    m_map_part_column_index.insert(CustomTypes::AttributeChainSpeed, 6);
    m_map_part_column_index.insert(CustomTypes::AttributeBBAxisType, 7);
    m_map_column_index.insert(CustomTypes::PartCrank, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartFrontShifter, "front_shifter_view");
    m_map_part_column_index.insert(CustomTypes::AttributeCrankSpeed, 3);
    m_map_column_index.insert(CustomTypes::PartFrontShifter, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartRearShifter, "rear_shifter_view");
    m_map_part_column_index.insert(CustomTypes::AttributeChainSpeed, 3);
    m_map_column_index.insert(CustomTypes::PartRearShifter, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartFrontDisc, "disc_brake_view");
    m_map_part_column_index.insert(CustomTypes::AttributeFrontDiscSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeFrontDiscMount, 4);
    m_map_column_index.insert(CustomTypes::PartFrontDisc, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartRearDisc, "disc_brake_view");
    m_map_part_column_index.insert(CustomTypes::AttributeRearDiscSize, 3);
    m_map_part_column_index.insert(CustomTypes::AttributeRearDiscMount, 4);
    m_map_column_index.insert(CustomTypes::PartRearDisc, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartFrontDiscBrakeSet, "front_disc_brake_set_view");
    m_map_part_column_index.insert(CustomTypes::AttributeFrontDiscBrakeMount, 3);
    m_map_column_index.insert(CustomTypes::PartFrontDiscBrakeSet, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartRearDiscBrakeSet, "rear_disc_brake_set_view");
    m_map_part_column_index.insert(CustomTypes::AttributeRearDiscBrakeMount, 3);
    m_map_column_index.insert(CustomTypes::PartRearDiscBrakeSet, m_map_part_column_index);
    m_map_part_column_index.clear();

    m_map_part_table.insert(CustomTypes::PartFrontVBrake, "front_vbrake_view");

    m_map_part_table.insert(CustomTypes::PartRearVBrake, "rear_vbrake_view");

    m_map_part_table.insert(CustomTypes::PartFrontLever, "front_lever_view");

    m_map_part_table.insert(CustomTypes::PartRearLever, "rear_lever_view");

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
    m_map_attribute_counter.insert(CustomTypes::AttributeChainSpeed, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeMinSprocketTooth, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeMaxSprocketTooth, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeMinDerailleurTooth, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeMaxDerailleurTooth, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeMaxFrontDerailleurTooth, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeMinFrontDerailleurTooth, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeChainLine, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeCrankSpeed, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeFrontDerailleurMount, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeMaxCrankTooth, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeFrontDiscSize, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeRearDiscSize, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeFrontDiscMount, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeRearDiscMount, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeFrontDiscBrakeMount, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeRearDiscBrakeMount, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeFrontVBrakeMount, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeRearVBrakeMount, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeSelectedFrontBrake, 0);
    m_map_attribute_counter.insert(CustomTypes::AttributeSelectedRearBrake, 0);

    emit map_part_table_ready(m_map_part_table);
}

void ModelHandler::init_properties(PropertyContainer *prop)
{
    m_property_container = prop;
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
    case CustomTypes::PartCassette:
        m_model_cassette = model;
        break;
    case CustomTypes::PartChain:
        m_model_chain = model;
        break;
    case CustomTypes::PartRearDerailleur:
        m_model_rear_derailleur = model;
        break;
    case CustomTypes::PartFrontDerailleur:
        m_model_front_derailleur = model;
        break;
    case CustomTypes::PartCrank:
        m_model_crank = model;
        break;
    case CustomTypes::PartFrontShifter:
        m_model_front_shifter = model;
        break;
    case CustomTypes::PartRearShifter:
        m_model_rear_shifter = model;
        break;
    case CustomTypes::PartFrontDisc:
        m_model_front_disc = model;
        break;
    case CustomTypes::PartRearDisc:
        m_model_rear_disc = model;
        break;
    case CustomTypes::PartFrontDiscBrakeSet:
        m_model_front_disc_brake_set = model;
        break;
    case CustomTypes::PartRearDiscBrakeSet:
        m_model_rear_disc_brake_set = model;
        break;
    case CustomTypes::PartFrontVBrake:
        m_model_front_vbrake = model;
        break;
    case CustomTypes::PartRearVBrake:
        m_model_rear_vbrake = model;
        break;
    case CustomTypes::PartFrontLever:
        m_model_front_lever = model;
        break;
    case CustomTypes::PartRearLever:
        m_model_rear_lever = model;
        break;
    }
}

void ModelHandler::set_properties(CustomTypes::PartType part_type, QList<QString> *list)
{
    QList<PartAttribute> property_attributes_list;
    QList<CustomTypes::AttributeName> keys = m_map_column_index[part_type].keys();
    for (int key_number = 0; key_number < keys.count(); key_number++){
        property_attributes_list.append(PartAttribute(keys[key_number], list->at(m_map_column_index[part_type][keys[key_number]])));
        m_map_attribute_counter[keys[key_number]]++;
    }
    emit property_attribute_list_ready(property_attributes_list);
    switch(part_type){
    case CustomTypes::PartFrontDisc:
    case CustomTypes::PartFrontDiscBrakeSet:
        m_property_container->setSelected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake, "disc"));
        m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake]++;
        break;
    case CustomTypes::PartRearDisc:
    case CustomTypes::PartRearDiscBrakeSet:
        m_property_container->setSelected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake, "disc"));
        m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake]++;
        break;
    case CustomTypes::PartFrontVBrake:
    case CustomTypes::PartFrontLever:
        m_property_container->setSelected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake, "vbrake"));
        m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake]++;
        break;
    case CustomTypes::PartRearVBrake:
    case CustomTypes::PartRearLever:
        m_property_container->setSelected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake, "vbrake"));
        m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake]++;
        break;
    default:
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
            m_property_container->setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]--;
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront] <= 0)
            m_property_container->setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeSteererTubeDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSteererTubeDiameter] <= 0)
            m_property_container->setAttribute_steerer_tube_diameter(PartAttribute(CustomTypes::AttributeSteererTubeDiameter, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontVBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontVBrakeMount] <= 0)
            m_property_container->setAttribute_front_vbrake_mount(PartAttribute(CustomTypes::AttributeFrontVBrakeMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount] <= 0)
            m_property_container->setAttribute_front_disc_brake_mount(PartAttribute(CustomTypes::AttributeFrontDiscBrakeMount, "-1"));
        break;
    }
    case CustomTypes::PartFrame:
    {
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            m_property_container->setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear]--;
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear] <= 0)
            m_property_container->setAttribute_axle_type_rear(PartAttribute(CustomTypes::AttributeAxleTypeRear, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeHeadset]--;
        if (m_map_attribute_counter[CustomTypes::AttributeHeadset] <= 0)
            m_property_container->setAttribute_headset(PartAttribute(CustomTypes::AttributeHeadset, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter] <= 0)
            m_property_container->setAttribute_seatpost_diameter(PartAttribute(CustomTypes::AttributeSeatpostDiameter, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeBBType]--;
        if (m_map_attribute_counter[CustomTypes::AttributeBBType] <= 0)
            m_property_container->setAttribute_bb_type(PartAttribute(CustomTypes::AttributeBBType, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount] <= 0)
            m_property_container->setAttribute_front_derailleur_mount(PartAttribute(CustomTypes::AttributeFrontDerailleurMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount] <= 0)
            m_property_container->setAttribute_rear_vbrake_mount(PartAttribute(CustomTypes::AttributeRearVBrakeMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount] <= 0)
            m_property_container->setAttribute_rear_disc_brake_mount(PartAttribute(CustomTypes::AttributeRearDiscBrakeMount, "-1"));
        break;
    }
    case CustomTypes::PartFrontWheel:
    {
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            m_property_container->setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]--;
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront] <= 0)
            m_property_container->setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount] <= 0)
            m_property_container->setAttribute_front_disc_mount(PartAttribute(CustomTypes::AttributeFrontDiscMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontVBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontVBrakeMount] <= 0)
            m_property_container->setAttribute_front_vbrake_mount(PartAttribute(CustomTypes::AttributeFrontVBrakeMount, "-1"));
        break;
    }
    case CustomTypes::PartRearWheel:
    {
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            m_property_container->setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear]--;
        if (m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear] <= 0)
            m_property_container->setAttribute_axle_type_rear(PartAttribute(CustomTypes::AttributeAxleTypeRear, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscMount] <= 0)
            m_property_container->setAttribute_rear_disc_mount(PartAttribute(CustomTypes::AttributeRearDiscMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount] <= 0)
            m_property_container->setAttribute_rear_vbrake_mount(PartAttribute(CustomTypes::AttributeRearVBrakeMount, "-1"));
        break;
    }
    case CustomTypes::PartHeadset:
    {
        m_map_attribute_counter[CustomTypes::AttributeHeadset]--;
        if (m_map_attribute_counter[CustomTypes::AttributeHeadset] <= 0)
            m_property_container->setAttribute_headset(PartAttribute(CustomTypes::AttributeHeadset, "-1"));
        break;
    }
    case CustomTypes::PartHandlebar:
    {
        m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter] <= 0)
            m_property_container->setAttribute_handlebar_diameter(PartAttribute(CustomTypes::AttributeHandlebarDiameter, "-1"));
        break;
    }
    case CustomTypes::PartStem:
    {
        m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeHandlebarDiameter] <= 0)
            m_property_container->setAttribute_handlebar_diameter(PartAttribute(CustomTypes::AttributeHandlebarDiameter, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeStemSteererTubeDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeStemSteererTubeDiameter] <= 0)
            m_property_container->setAttribute_stem_steerer_tube_diameter(PartAttribute(CustomTypes::AttributeStemSteererTubeDiameter, "-1"));
        break;
    }
    case CustomTypes::PartSeatpost:
    {
        m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSeatpostDiameter] <= 0)
            m_property_container->setAttribute_seatpost_diameter(PartAttribute(CustomTypes::AttributeSeatpostDiameter, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeSaddleMounting]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSaddleMounting] <= 0)
            m_property_container->setAttribute_saddle_mounting(PartAttribute(CustomTypes::AttributeSaddleMounting, "-1"));
        break;
    }
    case CustomTypes::PartSaddle:
    {
        m_map_attribute_counter[CustomTypes::AttributeSaddleMounting]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSaddleMounting] <= 0)
            m_property_container->setAttribute_saddle_mounting(PartAttribute(CustomTypes::AttributeSaddleMounting, "-1"));
        break;
    }
    case CustomTypes::PartTire:
    {
        m_map_attribute_counter[CustomTypes::AttributeTireWidth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeTireWidth] <= 0)
            m_property_container->setAttribute_tire_width(PartAttribute(CustomTypes::AttributeTireWidth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeWheelSize] <= 0)
            m_property_container->setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize, "-1"));
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
            m_property_container->setAttribute_bb_type(PartAttribute(CustomTypes::AttributeBBType, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeBBAxisType]--;
        if (m_map_attribute_counter[CustomTypes::AttributeBBAxisType] <= 0)
            m_property_container->setAttribute_bb_axis_type(PartAttribute(CustomTypes::AttributeBBAxisType, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeBBAxisLength]--;
        if (m_map_attribute_counter[CustomTypes::AttributeBBAxisLength] <= 0)
            m_property_container->setAttribute_bb_axis_length(PartAttribute(CustomTypes::AttributeBBAxisLength, "-1"));
        break;
    }
    case CustomTypes::PartGrip:
    {
        break;
    }
    case CustomTypes::PartCassette:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            m_property_container->setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMinSprocketTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMinSprocketTooth] <= 0)
            m_property_container->setAttribute_min_sprocket_tooth(PartAttribute(CustomTypes::AttributeMinSprocketTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMaxSprocketTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMaxSprocketTooth] <= 0)
            m_property_container->setAttribute_max_sprocket_tooth(PartAttribute(CustomTypes::AttributeMaxSprocketTooth, "-1"));
        break;
    }
    case CustomTypes::PartChain:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            m_property_container->setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        break;
    }
    case CustomTypes::PartRearDerailleur:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            m_property_container->setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMinDerailleurTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMinDerailleurTooth] <= 0)
            m_property_container->setAttribute_min_derailleur_tooth(PartAttribute(CustomTypes::AttributeMinDerailleurTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMaxDerailleurTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMaxDerailleurTooth] <= 0)
            m_property_container->setAttribute_max_derailleur_tooth(PartAttribute(CustomTypes::AttributeMaxDerailleurTooth, "-1"));
        break;
    }
    case CustomTypes::PartFrontDerailleur:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            m_property_container->setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMinFrontDerailleurTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMinFrontDerailleurTooth] <= 0)
            m_property_container->setAttribute_min_front_derailleur_tooth(PartAttribute(CustomTypes::AttributeMinFrontDerailleurTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMaxFrontDerailleurTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMaxFrontDerailleurTooth] <= 0)
            m_property_container->setAttribute_max_front_derailleur_tooth(PartAttribute(CustomTypes::AttributeMaxFrontDerailleurTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeCrankSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeCrankSpeed] <= 0)
            m_property_container->setAttribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeChainLine]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainLine] <= 0)
            m_property_container->setAttribute_chain_line(PartAttribute(CustomTypes::AttributeChainLine, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount] <= 0)
            m_property_container->setAttribute_front_derailleur_mount(PartAttribute(CustomTypes::AttributeFrontDerailleurMount, "-1"));
        break;
    }
    case CustomTypes::PartCrank:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            m_property_container->setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeCrankSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeCrankSpeed] <= 0)
            m_property_container->setAttribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeChainLine]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainLine] <= 0)
            m_property_container->setAttribute_chain_line(PartAttribute(CustomTypes::AttributeChainLine, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMaxCrankTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMaxCrankTooth] <= 0)
            m_property_container->setAttribute_max_crank_tooth(PartAttribute(CustomTypes::AttributeMaxCrankTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeBBAxisType]--;
        if (m_map_attribute_counter[CustomTypes::AttributeBBAxisType] <= 0)
            m_property_container->setAttribute_bb_axis_type(PartAttribute(CustomTypes::AttributeBBAxisType, "-1"));
        break;
    }
    case CustomTypes::PartFrontShifter:
    {
        m_map_attribute_counter[CustomTypes::AttributeCrankSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeCrankSpeed] <= 0)
            m_property_container->setAttribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed, "-1"));
        break;
    }
    case CustomTypes::PartRearShifter:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            m_property_container->setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        break;
    }
    case CustomTypes::PartFrontDisc:
    {
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscSize] <= 0)
            m_property_container->setAttribute_front_disc_size(PartAttribute(CustomTypes::AttributeFrontDiscSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount] <= 0)
            m_property_container->setAttribute_front_disc_mount(PartAttribute(CustomTypes::AttributeFrontDiscMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake] <= 0)
            m_property_container->setSelected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake, "-1"));
        break;
    }
    case CustomTypes::PartRearDisc:
    {
        m_map_attribute_counter[CustomTypes::AttributeRearDiscSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscSize] <= 0)
            m_property_container->setAttribute_rear_disc_size(PartAttribute(CustomTypes::AttributeRearDiscSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscMount] <= 0)
            m_property_container->setAttribute_rear_disc_mount(PartAttribute(CustomTypes::AttributeRearDiscMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake] <= 0)
            m_property_container->setSelected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake, "-1"));
        break;
    }
    case CustomTypes::PartFrontDiscBrakeSet:
    {
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount] <= 0)
            m_property_container->setAttribute_front_disc_brake_mount(PartAttribute(CustomTypes::AttributeFrontDiscBrakeMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake] <= 0)
            m_property_container->setSelected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake, "-1"));
        break;
    }
    case CustomTypes::PartRearDiscBrakeSet:
    {
        m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount] <= 0)
            m_property_container->setAttribute_rear_disc_brake_mount(PartAttribute(CustomTypes::AttributeRearDiscBrakeMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake] <= 0)
            m_property_container->setSelected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake, "-1"));
        break;
    }
    case CustomTypes::PartFrontVBrake:
    {
        m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake] <= 0)
            m_property_container->setSelected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake, "-1"));
        break;
    }
    case CustomTypes::PartRearVBrake:
    {
        m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake] <= 0)
            m_property_container->setSelected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake, "-1"));
        break;
    }
    case CustomTypes::PartFrontLever:
    {
        m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSelectedFrontBrake] <= 0)
            m_property_container->setSelected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake, "-1"));
        break;
    }
    case CustomTypes::PartRearLever:
    {
        m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake]--;
        if (m_map_attribute_counter[CustomTypes::AttributeSelectedRearBrake] <= 0)
            m_property_container->setSelected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake, "-1"));
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
            QModelIndex index_part_price = m_model_selected_parts.index(i, TableProperties::SelectedParts::ColumnPartPrice);
            m_model_selected_parts.setData(index_part_name, list->at(1));
            m_model_selected_parts.setData(index_part_id, list->at(2));
            m_model_selected_parts.setData(index_part_price, list->last());
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
            QModelIndex index_part_price = m_model_selected_parts.index(i, TableProperties::SelectedParts::ColumnPartPrice);
            m_model_selected_parts.setData(index_part_name, "Nie wybrano części");
            m_model_selected_parts.setData(index_part_id, "-1");
            m_model_selected_parts.setData(index_part_price, "0");
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
        if (m_property_container->attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(m_property_container->attribute_wheel_size().second);
        }
        if (m_property_container->attribute_axle_type_front().second != "-1"){
            filter_properties_list << QString("axle_type_front = '%1'").arg(m_property_container->attribute_axle_type_front().second);
        }
        if (m_property_container->attribute_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter = '%1'").arg(m_property_container->attribute_steerer_tube_diameter().second);
        }
        if (m_property_container->attribute_headset().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter IN (SELECT steerer_tube_diameter FROM headset_compatibility WHERE shis = '%1')").arg(m_property_container->attribute_headset().second);
        }
        if (m_property_container->attribute_stem_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter IN (SELECT steerer_tube_diameter FROM steerer_tube_diameter_compatibility WHERE stem_tube_diameter = '%1')").arg(m_property_container->attribute_stem_steerer_tube_diameter().second);
        }
        if (m_property_container->attribute_front_disc_brake_mount().second != "-1"){
            filter_properties_list << QString("disc_brake_mount = '%1'").arg(m_property_container->attribute_front_disc_brake_mount().second);
        }
        if (m_property_container->selected_front_brake().second == "disc"){
            filter_properties_list << QString("disc_brake_mount IS NOT NULL");
        } else if (m_property_container->selected_front_brake().second == "vbrake") {
            filter_properties_list << QString("v_brake_mount IS NOT NULL");
        }
        break;
    }
    case CustomTypes::PartFrame:
    {
        if (m_property_container->attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(m_property_container->attribute_wheel_size().second);
        }
        if (m_property_container->attribute_axle_type_rear().second != "-1"){
            filter_properties_list << QString("axle_type_rear = '%1'").arg(m_property_container->attribute_axle_type_rear().second);
        }
        if (m_property_container->attribute_headset().second != "-1"){
            filter_properties_list << QString("shis = '%1'").arg(m_property_container->attribute_headset().second);
        }
        if (m_property_container->attribute_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("shis IN (SELECT shis FROM headset_compatibility WHERE steerer_tube_diameter = '%1')").arg(m_property_container->attribute_steerer_tube_diameter().second);
        }
        if (m_property_container->attribute_stem_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("shis IN (SELECT shis FROM headset_compatibility WHERE steerer_tube_diameter IN (SELECT steerer_tube_diameter FROM steerer_tube_diameter_compatibility WHERE stem_tube_diameter = '%1'))").arg(m_property_container->attribute_stem_steerer_tube_diameter().second);
        }
        if (m_property_container->attribute_seatpost_diameter().second != "-1"){
            filter_properties_list << QString("seatpost_diameter = '%1'").arg(m_property_container->attribute_seatpost_diameter().second);
        }
        if (m_property_container->attribute_bb_type().second != "-1"){
            filter_properties_list << QString("bb_type = '%1'").arg(m_property_container->attribute_bb_type().second);
        }
        if (m_property_container->attribute_front_derailleur_mount().second != "-1"){
            filter_properties_list << QString("front_derailleur_mount = '%1'").arg(m_property_container->attribute_front_derailleur_mount().second);
        }
        if (m_property_container->attribute_rear_disc_brake_mount().second != "-1"){
            filter_properties_list << QString("disc_brake_mount = '%1'").arg(m_property_container->attribute_rear_disc_brake_mount().second);
        }
        if (m_property_container->selected_rear_brake().second == "disc"){
            filter_properties_list << QString("disc_brake_mount IS NOT NULL");
        } else if (m_property_container->selected_rear_brake().second == "vbrake") {
            filter_properties_list << QString("v_brake_mount IS NOT NULL");
        }
        break;
    }
    case CustomTypes::PartFrontWheel:
    {
        if (m_property_container->attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(m_property_container->attribute_wheel_size().second);
        }
        if (m_property_container->attribute_axle_type_front().second != "-1"){
            filter_properties_list << QString("axle_type_front = '%1'").arg(m_property_container->attribute_axle_type_front().second);
        }
        if (m_property_container->attribute_front_disc_mount().second != "-1"){
            filter_properties_list << QString("disc_mount_system = '%1'").arg(m_property_container->attribute_front_disc_mount().second);
        }
        if (m_property_container->selected_front_brake().second == "disc"){
            filter_properties_list << QString("disc_mount_system IS NOT NULL");
        } else if (m_property_container->selected_front_brake().second == "vbrake") {
            filter_properties_list << QString("v_brake_mount IS NOT NULL");
        }
        break;
    }
    case CustomTypes::PartRearWheel:
    {
        if (m_property_container->attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(m_property_container->attribute_wheel_size().second);
        }
        if (m_property_container->attribute_axle_type_rear().second != "-1"){
            filter_properties_list << QString("axle_type_rear = '%1'").arg(m_property_container->attribute_axle_type_rear().second);
        }
        if (m_property_container->attribute_rear_disc_mount().second != "-1"){
            filter_properties_list << QString("disc_mount_system = '%1'").arg(m_property_container->attribute_rear_disc_mount().second);
        }
        if (m_property_container->selected_rear_brake().second == "disc"){
            filter_properties_list << QString("disc_mount_system IS NOT NULL");
        } else if (m_property_container->selected_rear_brake().second == "vbrake") {
            filter_properties_list << QString("v_brake_mount IS NOT NULL");
        }
        break;
    }
    case CustomTypes::PartHeadset:
    {
        if (m_property_container->attribute_headset().second != "-1"){
            filter_properties_list << QString("shis = '%1'").arg(m_property_container->attribute_headset().second);
        }
        if (m_property_container->attribute_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("shis IN (SELECT shis FROM headset_compatibility WHERE steerer_tube_diameter = '%1')").arg(m_property_container->attribute_steerer_tube_diameter().second);
        }
        if (m_property_container->attribute_stem_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("shis IN (SELECT shis FROM headset_compatibility WHERE steerer_tube_diameter IN (SELECT steerer_tube_diameter FROM steerer_tube_diameter_compatibility WHERE stem_tube_diameter = '%1'))").arg(m_property_container->attribute_stem_steerer_tube_diameter().second);
        }
        break;
    }
    case CustomTypes::PartHandlebar:
    {
        if (m_property_container->attribute_handlebar_diameter().second != "-1"){
            filter_properties_list << QString("handlebar_diameter = '%1'").arg(m_property_container->attribute_handlebar_diameter().second);
        }
        break;
    }
    case CustomTypes::PartStem:
    {
        if (m_property_container->attribute_handlebar_diameter().second != "-1"){
            filter_properties_list << QString("handlebar_diameter = '%1'").arg(m_property_container->attribute_handlebar_diameter().second);
        }
        if (m_property_container->attribute_steerer_tube_diameter().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter IN (SELECT stem_tube_diameter FROM steerer_tube_diameter_compatibility WHERE steerer_tube_diameter = '%1')").arg(m_property_container->attribute_steerer_tube_diameter().second);
        }
        if (m_property_container->attribute_headset().second != "-1"){
            filter_properties_list << QString("steerer_tube_diameter IN (SELECT stem_tube_diameter FROM steerer_tube_diameter_compatibility WHERE steerer_tube_diameter in (SELECT steerer_tube_diameter FROM headset_compatibility WHERE shis = '%1'))").arg(m_property_container->attribute_headset().second);
        }
        break;
    }
    case CustomTypes::PartSeatpost:
    {
        if (m_property_container->attribute_seatpost_diameter().second != "-1"){
            filter_properties_list << QString("seatpost_diameter = '%1'").arg(m_property_container->attribute_seatpost_diameter().second);
        }
        if (m_property_container->attribute_saddle_mounting().second != "-1"){
            filter_properties_list << QString("saddle_mounting = '%1'").arg(m_property_container->attribute_saddle_mounting().second);
        }
        break;
    }
    case CustomTypes::PartSaddle:
    {
        if (m_property_container->attribute_saddle_mounting().second != "-1"){
            filter_properties_list << QString("saddle_mounting = '%1'").arg(m_property_container->attribute_saddle_mounting().second);
        }
        break;
    }
    case CustomTypes::PartTire:
    {
        if (m_property_container->attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(m_property_container->attribute_wheel_size().second);
        }
        break;
    }
    case CustomTypes::PartInnerTube:
    {
        if (m_property_container->attribute_wheel_size().second != "-1"){
            filter_properties_list << QString("wheel_size = '%1'").arg(m_property_container->attribute_wheel_size().second);
        }
        if (m_property_container->attribute_tire_width().second != "-1"){
            filter_properties_list << QString("min_tire_width <= '%1' AND max_tire_width >= '%1'").arg(m_property_container->attribute_tire_width().second);
        }
        break;
    }
    case CustomTypes::PartBB:
    {
        if (m_property_container->attribute_bb_type().second != "-1"){
            filter_properties_list << QString("bb_type = '%1'").arg(m_property_container->attribute_bb_type().second);
        }
        if (m_property_container->attribute_bb_axis_type().second != "-1"){
            filter_properties_list << QString("bb_axis_type = '%1'").arg(m_property_container->attribute_bb_axis_type().second);
        }
        if (m_property_container->attribute_bb_axis_length().second != "-1" && m_property_container->attribute_bb_axis_length().second != "0"){
            filter_properties_list << QString("bb_axis_length = '%1'").arg(m_property_container->attribute_bb_axis_length().second);
        }
        break;
    }
    case CustomTypes::PartGrip:
    {
        break;
    }
    case CustomTypes::PartCassette:
    {
        if (m_property_container->attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(m_property_container->attribute_chain_speed().second);
        }
        if (m_property_container->attribute_min_derailleur_tooth().second != "-1"){
            filter_properties_list << QString("min_sprocket_tooth >= '%1'").arg(m_property_container->attribute_min_derailleur_tooth().second);
        }
        if (m_property_container->attribute_max_derailleur_tooth().second != "-1"){
            filter_properties_list << QString("max_sprocket_tooth <= '%1'").arg(m_property_container->attribute_max_derailleur_tooth().second);
        }
        break;
    }
    case CustomTypes::PartChain:
    {
        if (m_property_container->attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(m_property_container->attribute_chain_speed().second);
        }
        break;
    }
    case CustomTypes::PartRearDerailleur:
    {
        if (m_property_container->attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(m_property_container->attribute_chain_speed().second);
        }
        if (m_property_container->attribute_min_sprocket_tooth().second != "-1"){
            filter_properties_list << QString("min_sprocket_tooth <= '%1'").arg(m_property_container->attribute_min_sprocket_tooth().second);
        }
        if (m_property_container->attribute_max_sprocket_tooth().second != "-1"){
            filter_properties_list << QString("max_sprocket_tooth >= '%1'").arg(m_property_container->attribute_max_sprocket_tooth().second);
        }
        break;
    }
    case CustomTypes::PartFrontDerailleur:
    {
        if (m_property_container->attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(m_property_container->attribute_chain_speed().second);
        }
        if (m_property_container->attribute_crank_speed().second != "-1"){
            filter_properties_list << QString("crank_speed = '%1'").arg(m_property_container->attribute_crank_speed().second);
        }
        if (m_property_container->attribute_chain_line().second != "-1"){
            filter_properties_list << QString("chain_line = '%1'").arg(m_property_container->attribute_chain_line().second);
        }
        if (m_property_container->attribute_max_crank_tooth().second != "-1"){
            filter_properties_list << QString("max_chainring_tooth >= '%1' AND min_chainring_tooth <= '%1'").arg(m_property_container->attribute_max_crank_tooth().second);
        }
        if (m_property_container->attribute_front_derailleur_mount().second != "-1"){
            filter_properties_list << QString("front_derailleur_mount = '%1'").arg(m_property_container->attribute_front_derailleur_mount().second);
        }
        break;
    }
    case CustomTypes::PartCrank:
    {
        if (m_property_container->attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(m_property_container->attribute_chain_speed().second);
        }
        if (m_property_container->attribute_crank_speed().second != "-1"){
            filter_properties_list << QString("crank_speed = '%1'").arg(m_property_container->attribute_crank_speed().second);
        }
        if (m_property_container->attribute_chain_line().second != "-1"){
            filter_properties_list << QString("chain_line = '%1'").arg(m_property_container->attribute_chain_line().second);
        }
        if (m_property_container->attribute_bb_axis_type().second != "-1"){
            filter_properties_list << QString("bb_axis_type = '%1'").arg(m_property_container->attribute_bb_axis_type().second);
        }
        if (m_property_container->attribute_max_front_derailleur_tooth().second != "-1"){
            filter_properties_list << QString("max_chainring_tooth <= '%1'").arg(m_property_container->attribute_max_front_derailleur_tooth().second);
        }
        if (m_property_container->attribute_min_front_derailleur_tooth().second != "-1"){
            filter_properties_list << QString("max_chainring_tooth >= '%1'").arg(m_property_container->attribute_min_front_derailleur_tooth().second);
        }
        break;
    }
    case CustomTypes::PartFrontShifter:
    {
        if (m_property_container->attribute_crank_speed().second != "-1"){
            filter_properties_list << QString("crank_speed = '%1'").arg(m_property_container->attribute_crank_speed().second);
        }
        break;
    }
    case CustomTypes::PartRearShifter:
    {
        if (m_property_container->attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(m_property_container->attribute_chain_speed().second);
        }
        break;
    }
    case CustomTypes::PartFrontDisc:
    {
        if (m_property_container->attribute_front_disc_size().second != "-1"){
            filter_properties_list << QString("disc_brake_size = '%1'").arg(m_property_container->attribute_front_disc_size().second);
        }
        if (m_property_container->attribute_front_disc_mount().second != "-1" && !m_property_container->attribute_front_disc_mount().second.isEmpty()){
            filter_properties_list << QString("disc_mount_system = '%1'").arg(m_property_container->attribute_front_disc_mount().second);
        }
        break;
    }
    case CustomTypes::PartRearDisc:
    {
        if (m_property_container->attribute_rear_disc_size().second != "-1"){
            filter_properties_list << QString("disc_brake_size = '%1'").arg(m_property_container->attribute_rear_disc_size().second);
        }
        if (m_property_container->attribute_rear_disc_mount().second != "-1"){
            filter_properties_list << QString("disc_mount_system = '%1'").arg(m_property_container->attribute_rear_disc_mount().second);
        }
        break;
    }
    case CustomTypes::PartFrontDiscBrakeSet:
    {
        if (m_property_container->attribute_front_disc_brake_mount().second != "-1" && !m_property_container->attribute_front_disc_brake_mount().second.isEmpty()){
            filter_properties_list << QString("disc_brake_mount_system = '%1'").arg(m_property_container->attribute_front_disc_brake_mount().second);
        }
        break;
    }
    case CustomTypes::PartRearDiscBrakeSet:
    {
        if (m_property_container->attribute_rear_disc_brake_mount().second != "-1" && !m_property_container->attribute_rear_disc_brake_mount().second.isEmpty()){
            filter_properties_list << QString("disc_brake_mount_system = '%1'").arg(m_property_container->attribute_rear_disc_brake_mount().second);
        }
        break;
    }

    case CustomTypes::PartFrontVBrake:
    case CustomTypes::PartRearVBrake:
    case CustomTypes::PartFrontLever:
    case CustomTypes::PartRearLever:
    {
        break;
    }
    }
    qDebug() << part_type << filter_properties_list.join(" AND ");
    return filter_properties_list.join(" AND ");
}

void ModelHandler::fill_selected_parts_model(QMap<CustomTypes::PartType, QString> map_part)
{
    for(auto e : map_part.keys()){
        QList<QStandardItem *> rowData;
        rowData << new QStandardItem(map_part.value(e));
        rowData << new QStandardItem("Nie wybrano części");
        rowData << new QStandardItem("0");
        rowData << new QStandardItem(QString("%1").arg(e));
        rowData << new QStandardItem("-1");
        m_model_selected_parts.appendRow(rowData);
        m_model_selected_parts.setHeaderData(0, Qt::Horizontal, "Rodzaj części");
        m_model_selected_parts.setHeaderData(1, Qt::Horizontal, "Nazwa części");
        m_model_selected_parts.setHeaderData(2, Qt::Horizontal, "Cena");
        m_model_selected_parts.setHeaderData(3, Qt::Horizontal, "");
        m_model_selected_parts.setHeaderData(4, Qt::Horizontal, "ID");
    }
    emit selected_parts_model_ready(&m_model_selected_parts);
}

void ModelHandler::check_disc_allowed(PartAttribute part_attribute)
{
    switch (part_attribute.first) {
    case CustomTypes::AttributeSelectedFrontBrake:
        if (part_attribute.second == "vbrake"){
            emit block_part(CustomTypes::PartFrontDisc);
            emit block_part(CustomTypes::PartFrontDiscBrakeSet);
            emit unlock_part(CustomTypes::PartFrontVBrake);
            emit unlock_part(CustomTypes::PartFrontLever);
        } else if (part_attribute.second == "disc"){
            emit unlock_part(CustomTypes::PartFrontDisc);
            emit unlock_part(CustomTypes::PartFrontDiscBrakeSet);
            emit block_part(CustomTypes::PartFrontVBrake);
            emit block_part(CustomTypes::PartFrontLever);
        } else {
            emit unlock_part(CustomTypes::PartFrontDisc);
            emit unlock_part(CustomTypes::PartFrontDiscBrakeSet);
            emit unlock_part(CustomTypes::PartFrontVBrake);
            emit unlock_part(CustomTypes::PartFrontLever);
        }
        break;
    case CustomTypes::AttributeSelectedRearBrake:
        if (part_attribute.second == "vbrake"){
            emit block_part(CustomTypes::PartRearDisc);
            emit block_part(CustomTypes::PartRearDiscBrakeSet);
            emit unlock_part(CustomTypes::PartRearVBrake);
            emit unlock_part(CustomTypes::PartRearLever);
        } else if (part_attribute.second == "disc"){
            emit unlock_part(CustomTypes::PartRearDisc);
            emit unlock_part(CustomTypes::PartRearDiscBrakeSet);
            emit block_part(CustomTypes::PartRearVBrake);
            emit block_part(CustomTypes::PartRearLever);
        } else {
            emit unlock_part(CustomTypes::PartRearDisc);
            emit unlock_part(CustomTypes::PartRearDiscBrakeSet);
            emit unlock_part(CustomTypes::PartRearVBrake);
            emit unlock_part(CustomTypes::PartRearLever);
        }
        break;
    case CustomTypes::AttributeFrontDiscBrakeMount:
    case CustomTypes::AttributeFrontDiscMount:
        if (part_attribute.second.isEmpty()){
            emit block_part(CustomTypes::PartFrontDisc);
            emit block_part(CustomTypes::PartFrontDiscBrakeSet);
        } else {
            if(m_property_container->selected_front_brake().second != "vbrake"){
                emit unlock_part(CustomTypes::PartFrontDisc);
                emit unlock_part(CustomTypes::PartFrontDiscBrakeSet);
            }
        }
        break;
    case CustomTypes::AttributeRearDiscBrakeMount:
    case CustomTypes::AttributeRearDiscMount:
        if (part_attribute.second.isEmpty()){
            emit block_part(CustomTypes::PartRearDisc);
            emit block_part(CustomTypes::PartRearDiscBrakeSet);
        } else {
            if(m_property_container->selected_rear_brake().second != "vbrake"){
                emit unlock_part(CustomTypes::PartRearDisc);
                emit unlock_part(CustomTypes::PartRearDiscBrakeSet);
            }
        }
        break;
    case CustomTypes::AttributeFrontVBrakeMount:
        if ((part_attribute.second == "1" || part_attribute.second == "-1") && m_property_container->selected_front_brake().second != "disc") {
            emit unlock_part(CustomTypes::PartFrontVBrake);
            emit unlock_part(CustomTypes::PartFrontLever);
        } else {
            emit block_part(CustomTypes::PartFrontVBrake);
            emit block_part(CustomTypes::PartFrontLever);
        }
        break;
    case CustomTypes::AttributeRearVBrakeMount:
        if (part_attribute.second == "1" || part_attribute.second == "-1") {
            emit unlock_part(CustomTypes::PartRearVBrake);
            emit unlock_part(CustomTypes::PartRearLever);
        } else {
            emit block_part(CustomTypes::PartRearVBrake);
            emit block_part(CustomTypes::PartRearLever);
        }
        break;
    default:
        break;
    }
}

void ModelHandler::save_bike()
{
    QStringList part_list;
    for(auto e : m_map_part_table.keys()){
        QString table_name;
        if (e == 20){
            table_name = "front_disc_view";
        } else if (e == 21){
            table_name = "rear_disc_view";
        } else {
            table_name = m_map_part_table.value(e);
        }
        QStringList table_name_split = table_name.split("_");
        table_name_split.removeLast();
        table_name_split.append("ID");
        part_list << table_name_split.join("_");
    }
    QStringList part_id_list;
    for(auto e : m_map_part_table.keys()){
        QString part_ID = m_model_selected_parts.item(e, TableProperties::SelectedParts::ColumnPartID)->data(Qt::DisplayRole).toString();
        part_id_list << part_ID;
    }
    emit send_bike_to_save(part_list, part_id_list);
}

void ModelHandler::set_parts(QList<QString>* part_list)
{
    QSqlTableModel* model = nullptr;
    QList<QString> list;
    for (int part_type = 1; part_type < part_list->length(); part_type++){
        switch (part_type) {
        case CustomTypes::PartFrame:
            model = m_model_frame;
            break;
        case CustomTypes::PartFork:
            model = m_model_fork;
            break;
        case CustomTypes::PartFrontWheel:
            model = m_model_front_wheel;
            break;
        case CustomTypes::PartRearWheel:
            model = m_model_rear_wheel;
            break;
        case CustomTypes::PartHeadset:
            model = m_model_headset;
            break;
        case CustomTypes::PartHandlebar:
            model = m_model_handlebar;
            break;
        case CustomTypes::PartStem:
            model = m_model_stem;
            break;
        case CustomTypes::PartSeatpost:
            model = m_model_seatpost;
            break;
        case CustomTypes::PartSaddle:
            model = m_model_saddle;
            break;
        case CustomTypes::PartTire:
            model = m_model_tire;
            break;
        case CustomTypes::PartInnerTube:
            model = m_model_inner_tube;
            break;
        case CustomTypes::PartBB:
            model = m_model_bb;
            break;
        case CustomTypes::PartGrip:
            model = m_model_grip;
            break;
        case CustomTypes::PartCassette:
            model = m_model_cassette;
            break;
        case CustomTypes::PartChain:
            model = m_model_chain;
            break;
        case CustomTypes::PartRearDerailleur:
            model = m_model_rear_derailleur;
            break;
        case CustomTypes::PartFrontDerailleur:
            model = m_model_front_derailleur;
            break;
        case CustomTypes::PartCrank:
            model = m_model_crank;
            break;
        case CustomTypes::PartFrontShifter:
            model = m_model_front_shifter;
            break;
        case CustomTypes::PartRearShifter:
            model = m_model_rear_shifter;
            break;
        case CustomTypes::PartFrontDisc:
            model = m_model_front_disc;
            break;
        case CustomTypes::PartRearDisc:
            model = m_model_rear_disc;
            break;
        case CustomTypes::PartFrontDiscBrakeSet:
            model = m_model_front_disc_brake_set;
            break;
        case CustomTypes::PartRearDiscBrakeSet:
            model = m_model_rear_disc_brake_set;
            break;
        case CustomTypes::PartFrontVBrake:
            model = m_model_front_vbrake;
            break;
        case CustomTypes::PartRearVBrake:
            model = m_model_rear_vbrake;
            break;
        case CustomTypes::PartFrontLever:
            model = m_model_front_lever;
            break;
        case CustomTypes::PartRearLever:
            model = m_model_rear_lever;
            break;
        }
        list.clear();
        if(part_list->at(part_type) != "0"){
            for (int row = 0; row < model->rowCount(); row++){
                if (model->data(model->index(row, 2)) == part_list->at(part_type)){
                    for (int column = 0; column < model->columnCount(); column++){
                        list << model->data(model->index(row, column)).toString();
                    }
                    break;
                }
            }
            emit send_selected_part((CustomTypes::PartType)part_type, &list);
        }
    }
}
