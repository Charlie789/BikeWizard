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
    m_attribute_bb_axis_length(PartAttribute(CustomTypes::AttributeBBAxisLength, "-1")),
    m_attribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1")),
    m_attribute_min_sprocket_tooth(PartAttribute(CustomTypes::AttributeMinSprocketTooth, "-1")),
    m_attribute_max_sprocket_tooth(PartAttribute(CustomTypes::AttributeMaxSprocketTooth, "-1")),
    m_attribute_min_derailleur_tooth(PartAttribute(CustomTypes::AttributeMinDerailleurTooth, "-1")),
    m_attribute_max_derailleur_tooth(PartAttribute(CustomTypes::AttributeMaxDerailleurTooth, "-1")),
    m_attribute_max_front_derailleur_tooth(PartAttribute(CustomTypes::AttributeMaxFrontDerailleurTooth, "-1")),
    m_attribute_min_front_derailleur_tooth(PartAttribute(CustomTypes::AttributeMinFrontDerailleurTooth, "-1")),
    m_attribute_chain_line(PartAttribute(CustomTypes::AttributeChainLine, "-1")),
    m_attribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed, "-1")),
    m_attribute_front_derailleur_mount(PartAttribute(CustomTypes::AttributeFrontDerailleurMount, "-1")),
    m_attribute_max_crank_tooth(PartAttribute(CustomTypes::AttributeMaxCrankTooth, "-1")),
    m_attribute_front_disc_size(PartAttribute(CustomTypes::AttributeFrontDiscSize, "-1")),
    m_attribute_rear_disc_size(PartAttribute(CustomTypes::AttributeRearDiscSize, "-1")),
    m_attribute_front_disc_mount(PartAttribute(CustomTypes::AttributeFrontDiscMount, "-1")),
    m_attribute_rear_disc_mount(PartAttribute(CustomTypes::AttributeRearDiscMount, "-1")),
    m_attribute_front_disc_brake_mount(PartAttribute(CustomTypes::AttributeFrontDiscBrakeMount, "-1")),
    m_attribute_rear_disc_brake_mount(PartAttribute(CustomTypes::AttributeRearDiscBrakeMount, "-1")),
    m_attribute_front_vbrake_mount(PartAttribute(CustomTypes::AttributeFrontVBrakeMount, "-1")),
    m_attribute_rear_vbrake_mount(PartAttribute(CustomTypes::AttributeRearVBrakeMount, "-1")),

    m_selected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake,"-1")),
    m_selected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake,"-1"))

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
    connect(this, &ModelHandler::attribute_chain_speedChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_min_sprocket_toothChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_max_sprocket_toothChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_min_derailleur_toothChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_max_derailleur_toothChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_max_front_derailleur_toothChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_min_front_derailleur_toothChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_chain_lineChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_crank_speedChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_front_derailleur_mountChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_max_crank_toothChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_front_disc_sizeChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_rear_disc_sizeChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_front_disc_mountChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_rear_disc_mountChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_front_disc_brake_mountChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_rear_disc_brake_mountChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_front_vbrake_mountChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::attribute_rear_vbrake_mountChanged, this, &ModelHandler::filter_handler);

    connect(this, &ModelHandler::selected_front_brakeChanged, this, &ModelHandler::filter_handler);
    connect(this, &ModelHandler::selected_rear_brakeChanged, this, &ModelHandler::filter_handler);

    connect(this, &ModelHandler::attribute_front_disc_mountChanged, this, &ModelHandler::check_disc_allowed);
    connect(this, &ModelHandler::attribute_rear_disc_mountChanged, this, &ModelHandler::check_disc_allowed);
    connect(this, &ModelHandler::attribute_front_disc_brake_mountChanged, this, &ModelHandler::check_disc_allowed);
    connect(this, &ModelHandler::attribute_rear_disc_brake_mountChanged, this, &ModelHandler::check_disc_allowed);
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

ModelHandler::PartAttribute ModelHandler::attribute_chain_speed() const
{
    return m_attribute_chain_speed;
}

ModelHandler::PartAttribute ModelHandler::attribute_min_sprocket_tooth() const
{
    return m_attribute_min_sprocket_tooth;
}

ModelHandler::PartAttribute ModelHandler::attribute_max_sprocket_tooth() const
{
    return m_attribute_max_sprocket_tooth;
}

ModelHandler::PartAttribute ModelHandler::attribute_min_derailleur_tooth() const
{
    return m_attribute_min_derailleur_tooth;
}

ModelHandler::PartAttribute ModelHandler::attribute_max_derailleur_tooth() const
{
    return m_attribute_max_derailleur_tooth;
}

ModelHandler::PartAttribute ModelHandler::attribute_max_front_derailleur_tooth() const
{
    return m_attribute_max_front_derailleur_tooth;
}

ModelHandler::PartAttribute ModelHandler::attribute_min_front_derailleur_tooth() const
{
    return m_attribute_min_front_derailleur_tooth;
}

ModelHandler::PartAttribute ModelHandler::attribute_chain_line() const
{
    return m_attribute_chain_line;
}

ModelHandler::PartAttribute ModelHandler::attribute_crank_speed() const
{
    return m_attribute_crank_speed;
}

ModelHandler::PartAttribute ModelHandler::attribute_front_derailleur_mount() const
{
    return m_attribute_front_derailleur_mount;
}

ModelHandler::PartAttribute ModelHandler::attribute_max_crank_tooth() const
{
    return m_attribute_max_crank_tooth;
}

ModelHandler::PartAttribute ModelHandler::attribute_front_disc_size() const
{
    return m_attribute_front_disc_size;
}

ModelHandler::PartAttribute ModelHandler::attribute_rear_disc_size() const
{
    return m_attribute_rear_disc_size;
}

ModelHandler::PartAttribute ModelHandler::attribute_front_disc_mount() const
{
    return m_attribute_front_disc_mount;
}

ModelHandler::PartAttribute ModelHandler::attribute_rear_disc_mount() const
{
    return m_attribute_rear_disc_mount;
}

ModelHandler::PartAttribute ModelHandler::attribute_front_disc_brake_mount() const
{
    return m_attribute_front_disc_brake_mount;
}

ModelHandler::PartAttribute ModelHandler::attribute_rear_disc_brake_mount() const
{
    return m_attribute_rear_disc_brake_mount;
}

ModelHandler::PartAttribute ModelHandler::attribute_front_vbrake_mount() const
{
    return m_attribute_front_vbrake_mount;
}

ModelHandler::PartAttribute ModelHandler::attribute_rear_vbrake_mount() const
{
    return m_attribute_rear_vbrake_mount;
}

ModelHandler::PartAttribute ModelHandler::selected_rear_brake() const
{
    return m_selected_rear_brake;
}

ModelHandler::PartAttribute ModelHandler::selected_front_brake() const
{
    return m_selected_front_brake;
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
        setAttribute_front_vbrake_mount(PartAttribute(CustomTypes::AttributeFrontVBrakeMount,
                                                  list->at(m_map_column_index[CustomTypes::PartFork][CustomTypes::AttributeFrontVBrakeMount])));
        m_map_attribute_counter[CustomTypes::AttributeFrontVBrakeMount]++;
        setAttribute_front_disc_brake_mount(PartAttribute(CustomTypes::AttributeFrontDiscBrakeMount,
                                                  list->at(m_map_column_index[CustomTypes::PartFork][CustomTypes::AttributeFrontDiscBrakeMount])));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount]++;
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
        setAttribute_front_derailleur_mount(PartAttribute(CustomTypes::AttributeFrontDerailleurMount,
                                                  list->at(m_map_column_index[CustomTypes::PartFrame][CustomTypes::AttributeFrontDerailleurMount])));
        m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount]++;
        setAttribute_rear_vbrake_mount(PartAttribute(CustomTypes::AttributeRearVBrakeMount,
                                                  list->at(m_map_column_index[CustomTypes::PartFrame][CustomTypes::AttributeRearVBrakeMount])));
        m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount]++;
        setAttribute_rear_disc_brake_mount(PartAttribute(CustomTypes::AttributeRearDiscBrakeMount,
                                                  list->at(m_map_column_index[CustomTypes::PartFrame][CustomTypes::AttributeRearDiscBrakeMount])));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount]++;
        break;
    case CustomTypes::PartFrontWheel:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize,
                                              list->at(m_map_column_index[CustomTypes::PartFrontWheel][CustomTypes::AttributeWheelSize])));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        setAttribute_axle_type_front(PartAttribute(CustomTypes::AttributeAxleTypeFront,
                                                   list->at(m_map_column_index[CustomTypes::PartFrontWheel][CustomTypes::AttributeAxleTypeFront])));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeFront]++;
        setAttribute_front_disc_mount(PartAttribute(CustomTypes::AttributeFrontDiscMount,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontWheel][CustomTypes::AttributeFrontDiscMount])));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount]++;
        break;
    case CustomTypes::PartRearWheel:
        setAttribute_wheel_size(PartAttribute(CustomTypes::AttributeWheelSize,
                                              list->at(m_map_column_index[CustomTypes::PartRearWheel][CustomTypes::AttributeWheelSize])));
        m_map_attribute_counter[CustomTypes::AttributeWheelSize]++;
        setAttribute_axle_type_rear(PartAttribute(CustomTypes::AttributeAxleTypeRear,
                                                  list->at(m_map_column_index[CustomTypes::PartRearWheel][CustomTypes::AttributeAxleTypeRear])));
        m_map_attribute_counter[CustomTypes::AttributeAxleTypeRear]++;
        setAttribute_rear_disc_mount(PartAttribute(CustomTypes::AttributeRearDiscMount,
                                                  list->at(m_map_column_index[CustomTypes::PartRearWheel][CustomTypes::AttributeRearDiscMount])));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscMount]++;
        setAttribute_rear_vbrake_mount(PartAttribute(CustomTypes::AttributeRearVBrakeMount,
                                                  list->at(m_map_column_index[CustomTypes::PartRearWheel][CustomTypes::AttributeRearVBrakeMount])));
        m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount]++;
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
    case CustomTypes::PartCassette:
        setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed,
                                                  list->at(m_map_column_index[CustomTypes::PartCassette][CustomTypes::AttributeChainSpeed])));
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]++;
        setAttribute_min_sprocket_tooth(PartAttribute(CustomTypes::AttributeMinSprocketTooth,
                                                  list->at(m_map_column_index[CustomTypes::PartCassette][CustomTypes::AttributeMinSprocketTooth])));
        m_map_attribute_counter[CustomTypes::AttributeMinSprocketTooth]++;
        setAttribute_max_sprocket_tooth(PartAttribute(CustomTypes::AttributeMaxSprocketTooth,
                                                  list->at(m_map_column_index[CustomTypes::PartCassette][CustomTypes::AttributeMaxSprocketTooth])));
        m_map_attribute_counter[CustomTypes::AttributeMaxSprocketTooth]++;
        break;
    case CustomTypes::PartChain:
        setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed,
                                                  list->at(m_map_column_index[CustomTypes::PartChain][CustomTypes::AttributeChainSpeed])));
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]++;
        break;
    case CustomTypes::PartRearDerailleur:
        setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed,
                                                  list->at(m_map_column_index[CustomTypes::PartRearDerailleur][CustomTypes::AttributeChainSpeed])));
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]++;
        setAttribute_min_derailleur_tooth(PartAttribute(CustomTypes::AttributeMinDerailleurTooth,
                                                  list->at(m_map_column_index[CustomTypes::PartRearDerailleur][CustomTypes::AttributeMinDerailleurTooth])));
        m_map_attribute_counter[CustomTypes::AttributeMinDerailleurTooth]++;
        setAttribute_max_derailleur_tooth(PartAttribute(CustomTypes::AttributeMaxDerailleurTooth,
                                                  list->at(m_map_column_index[CustomTypes::PartRearDerailleur][CustomTypes::AttributeMaxDerailleurTooth])));
        m_map_attribute_counter[CustomTypes::AttributeMaxDerailleurTooth]++;
        break;
    case CustomTypes::PartFrontDerailleur:
        setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontDerailleur][CustomTypes::AttributeChainSpeed])));
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]++;
        setAttribute_min_front_derailleur_tooth(PartAttribute(CustomTypes::AttributeMinFrontDerailleurTooth,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontDerailleur][CustomTypes::AttributeMinFrontDerailleurTooth])));
        m_map_attribute_counter[CustomTypes::AttributeMinFrontDerailleurTooth]++;
        setAttribute_max_front_derailleur_tooth(PartAttribute(CustomTypes::AttributeMaxFrontDerailleurTooth,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontDerailleur][CustomTypes::AttributeMaxFrontDerailleurTooth])));
        m_map_attribute_counter[CustomTypes::AttributeMaxFrontDerailleurTooth]++;
        setAttribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontDerailleur][CustomTypes::AttributeCrankSpeed])));
        m_map_attribute_counter[CustomTypes::AttributeCrankSpeed]++;
        setAttribute_chain_line(PartAttribute(CustomTypes::AttributeChainLine,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontDerailleur][CustomTypes::AttributeChainLine])));
        m_map_attribute_counter[CustomTypes::AttributeChainLine]++;
        setAttribute_front_derailleur_mount(PartAttribute(CustomTypes::AttributeFrontDerailleurMount,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontDerailleur][CustomTypes::AttributeFrontDerailleurMount])));
        m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount]++;
        break;
    case CustomTypes::PartCrank:
        setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed,
                                                  list->at(m_map_column_index[CustomTypes::PartCrank][CustomTypes::AttributeChainSpeed])));
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]++;
        setAttribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed,
                                                  list->at(m_map_column_index[CustomTypes::PartCrank][CustomTypes::AttributeCrankSpeed])));
        m_map_attribute_counter[CustomTypes::AttributeCrankSpeed]++;
        setAttribute_chain_line(PartAttribute(CustomTypes::AttributeChainLine,
                                                  list->at(m_map_column_index[CustomTypes::PartCrank][CustomTypes::AttributeChainLine])));
        m_map_attribute_counter[CustomTypes::AttributeChainLine]++;
        setAttribute_max_crank_tooth(PartAttribute(CustomTypes::AttributeMaxCrankTooth,
                                                  list->at(m_map_column_index[CustomTypes::PartCrank][CustomTypes::AttributeMaxCrankTooth])));
        m_map_attribute_counter[CustomTypes::AttributeMaxCrankTooth]++;
        setAttribute_bb_axis_type(PartAttribute(CustomTypes::AttributeBBAxisType,
                                                  list->at(m_map_column_index[CustomTypes::PartCrank][CustomTypes::AttributeBBAxisType])));
        m_map_attribute_counter[CustomTypes::AttributeBBAxisType]++;
        break;
    case CustomTypes::PartFrontShifter:
        setAttribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontShifter][CustomTypes::AttributeCrankSpeed])));
        m_map_attribute_counter[CustomTypes::AttributeCrankSpeed]++;
        break;
    case CustomTypes::PartRearShifter:
        setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed,
                                                  list->at(m_map_column_index[CustomTypes::PartRearShifter][CustomTypes::AttributeChainSpeed])));
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]++;
        break;
    case CustomTypes::PartFrontDisc:
        setAttribute_front_disc_size(PartAttribute(CustomTypes::AttributeFrontDiscSize,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontDisc][CustomTypes::AttributeFrontDiscSize])));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscSize]++;
        setAttribute_front_disc_mount(PartAttribute(CustomTypes::AttributeFrontDiscMount,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontDisc][CustomTypes::AttributeFrontDiscMount])));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount]++;
        break;
    case CustomTypes::PartRearDisc:
        setAttribute_rear_disc_size(PartAttribute(CustomTypes::AttributeRearDiscSize,
                                                  list->at(m_map_column_index[CustomTypes::PartRearDisc][CustomTypes::AttributeRearDiscSize])));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscSize]++;
        setAttribute_rear_disc_mount(PartAttribute(CustomTypes::AttributeRearDiscMount,
                                                  list->at(m_map_column_index[CustomTypes::PartRearDisc][CustomTypes::AttributeRearDiscMount])));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscMount]++;
        break;
    case CustomTypes::PartFrontDiscBrakeSet:
        setAttribute_front_disc_brake_mount(PartAttribute(CustomTypes::AttributeFrontDiscBrakeMount,
                                                  list->at(m_map_column_index[CustomTypes::PartFrontDiscBrakeSet][CustomTypes::AttributeFrontDiscBrakeMount])));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount]++;
        setSelected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake, "disc"));
        break;
    case CustomTypes::PartRearDiscBrakeSet:
        setAttribute_rear_disc_brake_mount(PartAttribute(CustomTypes::AttributeRearDiscBrakeMount,
                                                  list->at(m_map_column_index[CustomTypes::PartRearDiscBrakeSet][CustomTypes::AttributeRearDiscBrakeMount])));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount]++;
        setSelected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake, "disc"));
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
        m_map_attribute_counter[CustomTypes::AttributeFrontVBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontVBrakeMount] <= 0)
            setAttribute_front_vbrake_mount(PartAttribute(CustomTypes::AttributeFrontVBrakeMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount] <= 0)
            setAttribute_front_disc_brake_mount(PartAttribute(CustomTypes::AttributeFrontDiscBrakeMount, "-1"));
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
        m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount] <= 0)
            setAttribute_front_derailleur_mount(PartAttribute(CustomTypes::AttributeFrontDerailleurMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount] <= 0)
            setAttribute_rear_vbrake_mount(PartAttribute(CustomTypes::AttributeRearVBrakeMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount] <= 0)
            setAttribute_rear_disc_brake_mount(PartAttribute(CustomTypes::AttributeRearDiscBrakeMount, "-1"));
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
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount] <= 0)
            setAttribute_front_disc_mount(PartAttribute(CustomTypes::AttributeFrontDiscMount, "-1"));
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
        m_map_attribute_counter[CustomTypes::AttributeRearDiscMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscMount] <= 0)
            setAttribute_rear_disc_mount(PartAttribute(CustomTypes::AttributeRearDiscMount, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearVBrakeMount] <= 0)
            setAttribute_rear_vbrake_mount(PartAttribute(CustomTypes::AttributeRearVBrakeMount, "-1"));
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
    case CustomTypes::PartCassette:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMinSprocketTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMinSprocketTooth] <= 0)
            setAttribute_min_sprocket_tooth(PartAttribute(CustomTypes::AttributeMinSprocketTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMaxSprocketTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMaxSprocketTooth] <= 0)
            setAttribute_max_sprocket_tooth(PartAttribute(CustomTypes::AttributeMaxSprocketTooth, "-1"));
        break;
    }
    case CustomTypes::PartChain:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        break;
    }
    case CustomTypes::PartRearDerailleur:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMinDerailleurTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMinDerailleurTooth] <= 0)
            setAttribute_min_derailleur_tooth(PartAttribute(CustomTypes::AttributeMinDerailleurTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMaxDerailleurTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMaxDerailleurTooth] <= 0)
            setAttribute_max_derailleur_tooth(PartAttribute(CustomTypes::AttributeMaxDerailleurTooth, "-1"));
        break;
    }
    case CustomTypes::PartFrontDerailleur:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMinFrontDerailleurTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMinFrontDerailleurTooth] <= 0)
            setAttribute_min_front_derailleur_tooth(PartAttribute(CustomTypes::AttributeMinFrontDerailleurTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMaxFrontDerailleurTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMaxFrontDerailleurTooth] <= 0)
            setAttribute_max_front_derailleur_tooth(PartAttribute(CustomTypes::AttributeMaxFrontDerailleurTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeCrankSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeCrankSpeed] <= 0)
            setAttribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeChainLine]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainLine] <= 0)
            setAttribute_chain_line(PartAttribute(CustomTypes::AttributeChainLine, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDerailleurMount] <= 0)
            setAttribute_front_derailleur_mount(PartAttribute(CustomTypes::AttributeFrontDerailleurMount, "-1"));
        break;
    }
    case CustomTypes::PartCrank:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeCrankSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeCrankSpeed] <= 0)
            setAttribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeChainLine]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainLine] <= 0)
            setAttribute_chain_line(PartAttribute(CustomTypes::AttributeChainLine, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeMaxCrankTooth]--;
        if (m_map_attribute_counter[CustomTypes::AttributeMaxCrankTooth] <= 0)
            setAttribute_max_crank_tooth(PartAttribute(CustomTypes::AttributeMaxCrankTooth, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeBBAxisType]--;
        if (m_map_attribute_counter[CustomTypes::AttributeBBAxisType] <= 0)
            setAttribute_bb_axis_type(PartAttribute(CustomTypes::AttributeBBAxisType, "-1"));
        break;
    }
    case CustomTypes::PartFrontShifter:
    {
        m_map_attribute_counter[CustomTypes::AttributeCrankSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeCrankSpeed] <= 0)
            setAttribute_crank_speed(PartAttribute(CustomTypes::AttributeCrankSpeed, "-1"));
        break;
    }
    case CustomTypes::PartRearShifter:
    {
        m_map_attribute_counter[CustomTypes::AttributeChainSpeed]--;
        if (m_map_attribute_counter[CustomTypes::AttributeChainSpeed] <= 0)
            setAttribute_chain_speed(PartAttribute(CustomTypes::AttributeChainSpeed, "-1"));
        break;
    }
    case CustomTypes::PartFrontDisc:
    {
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscSize] <= 0)
            setAttribute_front_disc_size(PartAttribute(CustomTypes::AttributeFrontDiscSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscMount] <= 0)
            setAttribute_front_disc_mount(PartAttribute(CustomTypes::AttributeFrontDiscMount, "-1"));
        break;
    }
    case CustomTypes::PartRearDisc:
    {
        m_map_attribute_counter[CustomTypes::AttributeRearDiscSize]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscSize] <= 0)
            setAttribute_rear_disc_size(PartAttribute(CustomTypes::AttributeRearDiscSize, "-1"));
        m_map_attribute_counter[CustomTypes::AttributeRearDiscMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscMount] <= 0)
            setAttribute_rear_disc_mount(PartAttribute(CustomTypes::AttributeRearDiscMount, "-1"));
        break;
    }
    case CustomTypes::PartFrontDiscBrakeSet:
    {
        m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeFrontDiscBrakeMount] <= 0)
            setAttribute_front_disc_brake_mount(PartAttribute(CustomTypes::AttributeFrontDiscBrakeMount, "-1"));
        setSelected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake, "-1"));
        break;
    }
    case CustomTypes::PartRearDiscBrakeSet:
    {
        m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount]--;
        if (m_map_attribute_counter[CustomTypes::AttributeRearDiscBrakeMount] <= 0)
            setAttribute_rear_disc_brake_mount(PartAttribute(CustomTypes::AttributeRearDiscBrakeMount, "-1"));
        setSelected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake, "-1"));
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
        if (attribute_front_disc_brake_mount().second != "-1"){
            filter_properties_list << QString("disc_brake_mount = '%1'").arg(attribute_front_disc_brake_mount().second);
        }
        if (selected_front_brake().second == "disc"){
            filter_properties_list << QString("disc_brake_mount IS NOT NULL");
        } else if (selected_front_brake().second == "vbrake") {
            filter_properties_list << QString("v_brake_mount IS NOT NULL");
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
        if (attribute_front_derailleur_mount().second != "-1"){
            filter_properties_list << QString("front_derailleur_mount = '%1'").arg(attribute_front_derailleur_mount().second);
        }

        if (selected_rear_brake().second == "disc"){
            filter_properties_list << QString("disc_brake_mount IS NOT NULL");
        } else if (selected_rear_brake().second == "vbrake") {
            filter_properties_list << QString("v_brake_mount IS NOT NULL");
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
        if (attribute_front_disc_mount().second != "-1"){
            filter_properties_list << QString("disc_mount_system = '%1'").arg(attribute_front_disc_mount().second);
        }
        if (selected_front_brake().second == "disc"){
            filter_properties_list << QString("disc_mount_system IS NOT NULL");
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
        if (attribute_rear_disc_mount().second != "-1"){
            filter_properties_list << QString("disc_mount_system = '%1'").arg(attribute_rear_disc_mount().second);
        }
        if (selected_rear_brake().second == "disc"){
            filter_properties_list << QString("disc_mount_system IS NOT NULL");
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
    case CustomTypes::PartCassette:
    {
        if (attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(attribute_chain_speed().second);
        }
        if (attribute_min_derailleur_tooth().second != "-1"){
            filter_properties_list << QString("min_sprocket_tooth >= '%1'").arg(attribute_min_derailleur_tooth().second);
        }
        if (attribute_max_derailleur_tooth().second != "-1"){
            filter_properties_list << QString("max_sprocket_tooth <= '%1'").arg(attribute_max_derailleur_tooth().second);
        }
        break;
    }
    case CustomTypes::PartChain:
    {
        if (attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(attribute_chain_speed().second);
        }
        break;
    }
    case CustomTypes::PartRearDerailleur:
    {
        if (attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(attribute_chain_speed().second);
        }
        if (attribute_min_sprocket_tooth().second != "-1"){
            filter_properties_list << QString("min_sprocket_tooth <= '%1'").arg(attribute_min_sprocket_tooth().second);
        }
        if (attribute_max_sprocket_tooth().second != "-1"){
            filter_properties_list << QString("max_sprocket_tooth >= '%1'").arg(attribute_max_sprocket_tooth().second);
        }
        break;
    }
    case CustomTypes::PartFrontDerailleur:
    {
        if (attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(attribute_chain_speed().second);
        }
        if (attribute_crank_speed().second != "-1"){
            filter_properties_list << QString("crank_speed = '%1'").arg(attribute_crank_speed().second);
        }
        if (attribute_chain_line().second != "-1"){
            filter_properties_list << QString("chain_line = '%1'").arg(attribute_chain_line().second);
        }
        if (attribute_max_crank_tooth().second != "-1"){
            filter_properties_list << QString("max_chainring_tooth >= '%1' AND min_chainring_tooth <= '%1'").arg(attribute_max_crank_tooth().second);
        }
        if (attribute_front_derailleur_mount().second != "-1"){
            filter_properties_list << QString("front_derailleur_mount = '%1'").arg(attribute_front_derailleur_mount().second);
        }
        break;
    }
    case CustomTypes::PartCrank:
    {
        if (attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(attribute_chain_speed().second);
        }
        if (attribute_crank_speed().second != "-1"){
            filter_properties_list << QString("crank_speed = '%1'").arg(attribute_crank_speed().second);
        }
        if (attribute_chain_line().second != "-1"){
            filter_properties_list << QString("chain_line = '%1'").arg(attribute_chain_line().second);
        }
        if (attribute_bb_axis_type().second != "-1"){
            filter_properties_list << QString("bb_axis_type = '%1'").arg(attribute_bb_axis_type().second);
        }
        if (attribute_max_front_derailleur_tooth().second != "-1"){
            filter_properties_list << QString("max_chainring_tooth <= '%1'").arg(attribute_max_front_derailleur_tooth().second);
        }
        if (attribute_min_front_derailleur_tooth().second != "-1"){
            filter_properties_list << QString("max_chainring_tooth >= '%1'").arg(attribute_min_front_derailleur_tooth().second);
        }
        break;
    }
    case CustomTypes::PartFrontShifter:
    {
        if (attribute_crank_speed().second != "-1"){
            filter_properties_list << QString("crank_speed = '%1'").arg(attribute_crank_speed().second);
        }
        break;
    }
    case CustomTypes::PartRearShifter:
    {
        if (attribute_chain_speed().second != "-1"){
            filter_properties_list << QString("chain_speed = '%1'").arg(attribute_chain_speed().second);
        }
        break;
    }
    case CustomTypes::PartFrontDisc:
    {
        if (attribute_front_disc_size().second != "-1"){
            filter_properties_list << QString("disc_brake_size = '%1'").arg(attribute_front_disc_size().second);
        }
        if (attribute_front_disc_mount().second != "-1" && !attribute_front_disc_mount().second.isEmpty()){
            filter_properties_list << QString("disc_mount_system = '%1'").arg(attribute_front_disc_mount().second);
        }
        break;
    }
    case CustomTypes::PartRearDisc:
    {
        if (attribute_rear_disc_size().second != "-1"){
            filter_properties_list << QString("disc_brake_size = '%1'").arg(attribute_rear_disc_size().second);
        }
        if (attribute_rear_disc_mount().second != "-1"){
            filter_properties_list << QString("disc_mount_system = '%1'").arg(attribute_rear_disc_mount().second);
        }
        break;
    }
    case CustomTypes::PartFrontDiscBrakeSet:
    {
        if (attribute_front_disc_brake_mount().second != "-1" && !attribute_front_disc_brake_mount().second.isEmpty()){
            filter_properties_list << QString("disc_brake_mount_system = '%1'").arg(attribute_front_disc_brake_mount().second);
        }
        break;
    }
    case CustomTypes::PartRearDiscBrakeSet:
    {
        if (attribute_rear_disc_brake_mount().second != "-1" && !attribute_rear_disc_brake_mount().second.isEmpty()){
            filter_properties_list << QString("disc_brake_mount_system = '%1'").arg(attribute_rear_disc_brake_mount().second);
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

void ModelHandler::setAttribute_chain_speed(ModelHandler::PartAttribute attribute_chain_speed)
{
    if (m_attribute_chain_speed == attribute_chain_speed)
        return;

    m_attribute_chain_speed = attribute_chain_speed;
    emit attribute_chain_speedChanged(m_attribute_chain_speed);
}

void ModelHandler::setAttribute_min_sprocket_tooth(ModelHandler::PartAttribute attribute_min_sprocket_tooth)
{
    if (m_attribute_min_sprocket_tooth == attribute_min_sprocket_tooth)
        return;

    m_attribute_min_sprocket_tooth = attribute_min_sprocket_tooth;
    emit attribute_min_sprocket_toothChanged(m_attribute_min_sprocket_tooth);
}

void ModelHandler::setAttribute_max_sprocket_tooth(ModelHandler::PartAttribute attribute_max_sprocket_tooth)
{
    if (m_attribute_max_sprocket_tooth == attribute_max_sprocket_tooth)
        return;

    m_attribute_max_sprocket_tooth = attribute_max_sprocket_tooth;
    emit attribute_max_sprocket_toothChanged(m_attribute_max_sprocket_tooth);
}

void ModelHandler::setAttribute_min_derailleur_tooth(ModelHandler::PartAttribute attribute_min_derailleur_tooth)
{
    if (m_attribute_min_derailleur_tooth == attribute_min_derailleur_tooth)
        return;

    m_attribute_min_derailleur_tooth = attribute_min_derailleur_tooth;
    emit attribute_min_derailleur_toothChanged(m_attribute_min_derailleur_tooth);
}

void ModelHandler::setAttribute_max_derailleur_tooth(ModelHandler::PartAttribute attribute_max_derailleur_tooth)
{
    if (m_attribute_max_derailleur_tooth == attribute_max_derailleur_tooth)
        return;

    m_attribute_max_derailleur_tooth = attribute_max_derailleur_tooth;
    emit attribute_max_derailleur_toothChanged(m_attribute_max_derailleur_tooth);
}

void ModelHandler::setAttribute_max_front_derailleur_tooth(ModelHandler::PartAttribute attribute_max_front_derailleur_tooth)
{
    if (m_attribute_max_front_derailleur_tooth == attribute_max_front_derailleur_tooth)
        return;

    m_attribute_max_front_derailleur_tooth = attribute_max_front_derailleur_tooth;
    emit attribute_max_front_derailleur_toothChanged(m_attribute_max_front_derailleur_tooth);
}

void ModelHandler::setAttribute_min_front_derailleur_tooth(ModelHandler::PartAttribute attribute_min_front_derailleur_tooth)
{
    if (m_attribute_min_front_derailleur_tooth == attribute_min_front_derailleur_tooth)
        return;

    m_attribute_min_front_derailleur_tooth = attribute_min_front_derailleur_tooth;
    emit attribute_min_front_derailleur_toothChanged(m_attribute_min_front_derailleur_tooth);
}

void ModelHandler::setAttribute_chain_line(ModelHandler::PartAttribute attribute_chain_line)
{
    if (m_attribute_chain_line == attribute_chain_line)
        return;

    m_attribute_chain_line = attribute_chain_line;
    emit attribute_chain_lineChanged(m_attribute_chain_line);
}

void ModelHandler::setAttribute_crank_speed(ModelHandler::PartAttribute attribute_crank_speed)
{
    if (m_attribute_crank_speed == attribute_crank_speed)
        return;

    m_attribute_crank_speed = attribute_crank_speed;
    emit attribute_crank_speedChanged(m_attribute_crank_speed);
}

void ModelHandler::setAttribute_front_derailleur_mount(ModelHandler::PartAttribute attribute_front_derailleur_mount)
{
    if (m_attribute_front_derailleur_mount == attribute_front_derailleur_mount)
        return;

    m_attribute_front_derailleur_mount = attribute_front_derailleur_mount;
    emit attribute_front_derailleur_mountChanged(m_attribute_front_derailleur_mount);
}

void ModelHandler::setAttribute_max_crank_tooth(ModelHandler::PartAttribute attribute_max_crank_tooth)
{
    if (m_attribute_max_crank_tooth == attribute_max_crank_tooth)
        return;

    m_attribute_max_crank_tooth = attribute_max_crank_tooth;
    emit attribute_max_crank_toothChanged(m_attribute_max_crank_tooth);
}

void ModelHandler::setAttribute_front_disc_size(ModelHandler::PartAttribute attribute_front_disc_size)
{
    if (m_attribute_front_disc_size == attribute_front_disc_size)
        return;

    m_attribute_front_disc_size = attribute_front_disc_size;
    emit attribute_front_disc_sizeChanged(m_attribute_front_disc_size);
}

void ModelHandler::setAttribute_rear_disc_size(ModelHandler::PartAttribute attribute_rear_disc_size)
{
    if (m_attribute_rear_disc_size == attribute_rear_disc_size)
        return;

    m_attribute_rear_disc_size = attribute_rear_disc_size;
    emit attribute_rear_disc_sizeChanged(m_attribute_rear_disc_size);
}

void ModelHandler::setAttribute_front_disc_mount(ModelHandler::PartAttribute attribute_front_disc_mount)
{
    if (m_attribute_front_disc_mount == attribute_front_disc_mount)
        return;

    m_attribute_front_disc_mount = attribute_front_disc_mount;
    emit attribute_front_disc_mountChanged(m_attribute_front_disc_mount);
}

void ModelHandler::setAttribute_rear_disc_mount(ModelHandler::PartAttribute attribute_rear_disc_mount)
{
    if (m_attribute_rear_disc_mount == attribute_rear_disc_mount)
        return;

    m_attribute_rear_disc_mount = attribute_rear_disc_mount;
    emit attribute_rear_disc_mountChanged(m_attribute_rear_disc_mount);
}

void ModelHandler::setAttribute_front_disc_brake_mount(ModelHandler::PartAttribute attribute_front_disc_brake_mount)
{
    if (m_attribute_front_disc_brake_mount == attribute_front_disc_brake_mount)
        return;

    m_attribute_front_disc_brake_mount = attribute_front_disc_brake_mount;
    emit attribute_front_disc_brake_mountChanged(m_attribute_front_disc_brake_mount);
}

void ModelHandler::setAttribute_rear_disc_brake_mount(ModelHandler::PartAttribute attribute_rear_disc_brake_mount)
{
    if (m_attribute_rear_disc_brake_mount == attribute_rear_disc_brake_mount)
        return;

    m_attribute_rear_disc_brake_mount = attribute_rear_disc_brake_mount;
    emit attribute_rear_disc_brake_mountChanged(m_attribute_rear_disc_brake_mount);
}

void ModelHandler::setAttribute_front_vbrake_mount(ModelHandler::PartAttribute attribute_front_vbrake_mount)
{
    if (m_attribute_front_vbrake_mount == attribute_front_vbrake_mount)
        return;

    m_attribute_front_vbrake_mount = attribute_front_vbrake_mount;
    emit attribute_front_vbrake_mountChanged(m_attribute_front_vbrake_mount);
}

void ModelHandler::setAttribute_rear_vbrake_mount(ModelHandler::PartAttribute attribute_rear_vbrake_mount)
{
    if (m_attribute_rear_vbrake_mount == attribute_rear_vbrake_mount)
        return;

    m_attribute_rear_vbrake_mount = attribute_rear_vbrake_mount;
    emit attribute_rear_vbrake_mountChanged(m_attribute_rear_vbrake_mount);
}

void ModelHandler::setSelected_front_brake(ModelHandler::PartAttribute selected_front_brake)
{
    if (m_selected_front_brake == selected_front_brake)
        return;

    m_selected_front_brake = selected_front_brake;
    emit selected_front_brakeChanged(m_selected_front_brake);
}

void ModelHandler::setSelected_rear_brake(PartAttribute selected_brake)
{
    if (m_selected_rear_brake == selected_brake)
        return;

    m_selected_rear_brake = selected_brake;
    emit selected_rear_brakeChanged(m_selected_rear_brake);
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

void ModelHandler::check_disc_allowed(ModelHandler::PartAttribute part_attribute)
{
    switch (part_attribute.first) {
    case CustomTypes::AttributeFrontDiscBrakeMount:
    case CustomTypes::AttributeFrontDiscMount:
        if (part_attribute.second.isEmpty()){
            emit block_part(CustomTypes::PartFrontDisc);
            emit block_part(CustomTypes::PartFrontDiscBrakeSet);
        } else {
            emit unlock_part(CustomTypes::PartFrontDisc);
            emit unlock_part(CustomTypes::PartFrontDiscBrakeSet);
        }
        break;
    case CustomTypes::AttributeRearDiscBrakeMount:
    case CustomTypes::AttributeRearDiscMount:
        if (part_attribute.second.isEmpty()){
            emit block_part(CustomTypes::PartRearDisc);
            emit block_part(CustomTypes::PartRearDiscBrakeSet);
        } else {
            emit unlock_part(CustomTypes::PartRearDisc);
            emit unlock_part(CustomTypes::PartRearDiscBrakeSet);
        }
        break;
    default:
        break;
    }
}
