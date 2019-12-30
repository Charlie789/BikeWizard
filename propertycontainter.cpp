#include "propertycontainter.h"

PropertyContainer::PropertyContainer(QObject *parent) :
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

    m_selected_front_brake(PartAttribute(CustomTypes::AttributeSelectedFrontBrake, "-1")),
    m_selected_rear_brake(PartAttribute(CustomTypes::AttributeSelectedRearBrake, "-1"))

{
    connect(this, &PropertyContainer::attribute_wheel_sizeChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_axle_type_frontChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_axle_type_rearChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_steerer_tube_diameterChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_headsetChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_handlebar_diameterChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_stem_steerer_tube_diameterChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_seatpost_diameterChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_saddle_mountingChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_tire_widthChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_bb_typeChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_bb_axis_typeChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_bb_axis_lengthChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_chain_speedChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_min_sprocket_toothChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_max_sprocket_toothChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_min_derailleur_toothChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_max_derailleur_toothChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_max_front_derailleur_toothChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_min_front_derailleur_toothChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_chain_lineChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_crank_speedChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_front_derailleur_mountChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_max_crank_toothChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_front_disc_sizeChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_rear_disc_sizeChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_front_disc_mountChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_rear_disc_mountChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_front_disc_brake_mountChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_rear_disc_brake_mountChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_front_vbrake_mountChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::attribute_rear_vbrake_mountChanged, this, &PropertyContainer::property_changed);

    connect(this, &PropertyContainer::selected_front_brakeChanged, this, &PropertyContainer::property_changed);
    connect(this, &PropertyContainer::selected_rear_brakeChanged, this, &PropertyContainer::property_changed);

    connect(this, &PropertyContainer::selected_front_brakeChanged, this, &PropertyContainer::brake_property_changed);
    connect(this, &PropertyContainer::selected_rear_brakeChanged, this, &PropertyContainer::brake_property_changed);
    connect(this, &PropertyContainer::attribute_front_vbrake_mountChanged, this, &PropertyContainer::brake_property_changed);
    connect(this, &PropertyContainer::attribute_rear_vbrake_mountChanged, this, &PropertyContainer::brake_property_changed);
    connect(this, &PropertyContainer::attribute_front_disc_mountChanged, this, &PropertyContainer::brake_property_changed);
    connect(this, &PropertyContainer::attribute_rear_disc_mountChanged, this, &PropertyContainer::brake_property_changed);
    connect(this, &PropertyContainer::attribute_front_disc_brake_mountChanged, this, &PropertyContainer::brake_property_changed);
    connect(this, &PropertyContainer::attribute_rear_disc_brake_mountChanged, this, &PropertyContainer::brake_property_changed);

}

PartAttribute PropertyContainer::attribute_wheel_size() const
{
    return m_attribute_wheel_size;
}

PartAttribute PropertyContainer::attribute_axle_type_front() const
{
    return m_attribute_axle_type_front;
}

PartAttribute PropertyContainer::attribute_axle_type_rear() const
{
    return m_attribute_axle_type_rear;
}

PartAttribute PropertyContainer::attribute_steerer_tube_diameter() const
{
    return m_attribute_steerer_tube_diameter;
}

PartAttribute PropertyContainer::attribute_headset() const
{
    return m_attribute_headset;
}

PartAttribute PropertyContainer::attribute_handlebar_diameter() const
{
    return m_attribute_handlebar_diameter;
}

PartAttribute PropertyContainer::attribute_stem_steerer_tube_diameter() const
{
    return m_attribute_stem_steerer_tube_diameter;
}

PartAttribute PropertyContainer::attribute_seatpost_diameter() const
{
    return m_attribute_seatpost_diameter;
}

PartAttribute PropertyContainer::attribute_saddle_mounting() const
{
    return m_attribute_saddle_mounting;
}

PartAttribute PropertyContainer::attribute_tire_width() const
{
    return m_attribute_tire_width;
}

PartAttribute PropertyContainer::attribute_bb_type() const
{
    return m_attribute_bb_type;
}

PartAttribute PropertyContainer::attribute_bb_axis_type() const
{
    return m_attribute_bb_axis_type;
}

PartAttribute PropertyContainer::attribute_bb_axis_length() const
{
    return m_attribute_bb_axis_length;
}

PartAttribute PropertyContainer::attribute_chain_speed() const
{
    return m_attribute_chain_speed;
}

PartAttribute PropertyContainer::attribute_min_sprocket_tooth() const
{
    return m_attribute_min_sprocket_tooth;
}

PartAttribute PropertyContainer::attribute_max_sprocket_tooth() const
{
    return m_attribute_max_sprocket_tooth;
}

PartAttribute PropertyContainer::attribute_min_derailleur_tooth() const
{
    return m_attribute_min_derailleur_tooth;
}

PartAttribute PropertyContainer::attribute_max_derailleur_tooth() const
{
    return m_attribute_max_derailleur_tooth;
}

PartAttribute PropertyContainer::attribute_max_front_derailleur_tooth() const
{
    return m_attribute_max_front_derailleur_tooth;
}

PartAttribute PropertyContainer::attribute_min_front_derailleur_tooth() const
{
    return m_attribute_min_front_derailleur_tooth;
}

PartAttribute PropertyContainer::attribute_chain_line() const
{
    return m_attribute_chain_line;
}

PartAttribute PropertyContainer::attribute_crank_speed() const
{
    return m_attribute_crank_speed;
}

PartAttribute PropertyContainer::attribute_front_derailleur_mount() const
{
    return m_attribute_front_derailleur_mount;
}

PartAttribute PropertyContainer::attribute_max_crank_tooth() const
{
    return m_attribute_max_crank_tooth;
}

PartAttribute PropertyContainer::attribute_front_disc_size() const
{
    return m_attribute_front_disc_size;
}

PartAttribute PropertyContainer::attribute_rear_disc_size() const
{
    return m_attribute_rear_disc_size;
}

PartAttribute PropertyContainer::attribute_front_disc_mount() const
{
    return m_attribute_front_disc_mount;
}

PartAttribute PropertyContainer::attribute_rear_disc_mount() const
{
    return m_attribute_rear_disc_mount;
}

PartAttribute PropertyContainer::attribute_front_disc_brake_mount() const
{
    return m_attribute_front_disc_brake_mount;
}

PartAttribute PropertyContainer::attribute_rear_disc_brake_mount() const
{
    return m_attribute_rear_disc_brake_mount;
}

PartAttribute PropertyContainer::attribute_front_vbrake_mount() const
{
    return m_attribute_front_vbrake_mount;
}

PartAttribute PropertyContainer::attribute_rear_vbrake_mount() const
{
    return m_attribute_rear_vbrake_mount;
}

PartAttribute PropertyContainer::selected_rear_brake() const
{
    return m_selected_rear_brake;
}

void PropertyContainer::setAttribute_wheel_size(PartAttribute attribute_wheel_size)
{
    if (m_attribute_wheel_size == attribute_wheel_size)
        return;

    m_attribute_wheel_size = attribute_wheel_size;
    emit attribute_wheel_sizeChanged(m_attribute_wheel_size);
}

void PropertyContainer::setAttribute_axle_type_front(PartAttribute attribute_axle_type_front)
{
    if (m_attribute_axle_type_front == attribute_axle_type_front)
        return;

    m_attribute_axle_type_front = attribute_axle_type_front;
    emit attribute_axle_type_frontChanged(m_attribute_axle_type_front);
}

void PropertyContainer::setAttribute_axle_type_rear(PartAttribute attribute_axle_type_rear)
{
    if (m_attribute_axle_type_rear == attribute_axle_type_rear)
        return;

    m_attribute_axle_type_rear = attribute_axle_type_rear;
    emit attribute_axle_type_rearChanged(m_attribute_axle_type_rear);
}

void PropertyContainer::setAttribute_steerer_tube_diameter(PartAttribute attribute_steerer_tube_diameter)
{
    if (m_attribute_steerer_tube_diameter == attribute_steerer_tube_diameter)
        return;

    m_attribute_steerer_tube_diameter = attribute_steerer_tube_diameter;
    emit attribute_steerer_tube_diameterChanged(m_attribute_steerer_tube_diameter);
}

void PropertyContainer::setAttribute_headset(PartAttribute attribute_headset)
{
    if (m_attribute_headset == attribute_headset)
        return;

    m_attribute_headset = attribute_headset;
    emit attribute_headsetChanged(m_attribute_headset);
}

void PropertyContainer::setAttribute_handlebar_diameter(PartAttribute attribute_handlebar_diameter)
{
    if (m_attribute_handlebar_diameter == attribute_handlebar_diameter)
        return;

    m_attribute_handlebar_diameter = attribute_handlebar_diameter;
    emit attribute_handlebar_diameterChanged(m_attribute_handlebar_diameter);
}

void PropertyContainer::setAttribute_stem_steerer_tube_diameter(PartAttribute attribute_stem_steerer_tube_diameter)
{
    if (m_attribute_stem_steerer_tube_diameter == attribute_stem_steerer_tube_diameter)
        return;

    m_attribute_stem_steerer_tube_diameter = attribute_stem_steerer_tube_diameter;
    emit attribute_stem_steerer_tube_diameterChanged(m_attribute_stem_steerer_tube_diameter);
}

void PropertyContainer::setAttribute_seatpost_diameter(PartAttribute attribute_seatpost_diameter)
{
    if (m_attribute_seatpost_diameter == attribute_seatpost_diameter)
        return;

    m_attribute_seatpost_diameter = attribute_seatpost_diameter;
    emit attribute_seatpost_diameterChanged(m_attribute_seatpost_diameter);
}

void PropertyContainer::setAttribute_saddle_mounting(PartAttribute attribute_saddle_mounting)
{
    if (m_attribute_saddle_mounting == attribute_saddle_mounting)
        return;

    m_attribute_saddle_mounting = attribute_saddle_mounting;
    emit attribute_saddle_mountingChanged(m_attribute_saddle_mounting);
}

void PropertyContainer::setAttribute_tire_width(PartAttribute attribute_tire_width)
{
    if (m_attribute_tire_width == attribute_tire_width)
        return;

    m_attribute_tire_width = attribute_tire_width;
    emit attribute_tire_widthChanged(m_attribute_tire_width);
}

void PropertyContainer::setAttribute_bb_type(PartAttribute attribute_bb_type)
{
    if (m_attribute_bb_type == attribute_bb_type)
        return;

    m_attribute_bb_type = attribute_bb_type;
    emit attribute_bb_typeChanged(m_attribute_bb_type);
}

void PropertyContainer::setAttribute_bb_axis_type(PartAttribute attribute_bb_axis_type)
{
    if (m_attribute_bb_axis_type == attribute_bb_axis_type)
        return;

    m_attribute_bb_axis_type = attribute_bb_axis_type;
    emit attribute_bb_axis_typeChanged(m_attribute_bb_axis_type);
}

void PropertyContainer::setAttribute_bb_axis_length(PartAttribute attribute_bb_axis_length)
{
    if (m_attribute_bb_axis_length == attribute_bb_axis_length)
        return;

    m_attribute_bb_axis_length = attribute_bb_axis_length;
    emit attribute_bb_axis_lengthChanged(m_attribute_bb_axis_length);
}

void PropertyContainer::setAttribute_chain_speed(PartAttribute attribute_chain_speed)
{
    if (m_attribute_chain_speed == attribute_chain_speed)
        return;

    m_attribute_chain_speed = attribute_chain_speed;
    emit attribute_chain_speedChanged(m_attribute_chain_speed);
}

void PropertyContainer::setAttribute_min_sprocket_tooth(PartAttribute attribute_min_sprocket_tooth)
{
    if (m_attribute_min_sprocket_tooth == attribute_min_sprocket_tooth)
        return;

    m_attribute_min_sprocket_tooth = attribute_min_sprocket_tooth;
    emit attribute_min_sprocket_toothChanged(m_attribute_min_sprocket_tooth);
}

void PropertyContainer::setAttribute_max_sprocket_tooth(PartAttribute attribute_max_sprocket_tooth)
{
    if (m_attribute_max_sprocket_tooth == attribute_max_sprocket_tooth)
        return;

    m_attribute_max_sprocket_tooth = attribute_max_sprocket_tooth;
    emit attribute_max_sprocket_toothChanged(m_attribute_max_sprocket_tooth);
}

void PropertyContainer::setAttribute_min_derailleur_tooth(PartAttribute attribute_min_derailleur_tooth)
{
    if (m_attribute_min_derailleur_tooth == attribute_min_derailleur_tooth)
        return;

    m_attribute_min_derailleur_tooth = attribute_min_derailleur_tooth;
    emit attribute_min_derailleur_toothChanged(m_attribute_min_derailleur_tooth);
}

void PropertyContainer::setAttribute_max_derailleur_tooth(PartAttribute attribute_max_derailleur_tooth)
{
    if (m_attribute_max_derailleur_tooth == attribute_max_derailleur_tooth)
        return;

    m_attribute_max_derailleur_tooth = attribute_max_derailleur_tooth;
    emit attribute_max_derailleur_toothChanged(m_attribute_max_derailleur_tooth);
}

void PropertyContainer::setAttribute_max_front_derailleur_tooth(PartAttribute attribute_max_front_derailleur_tooth)
{
    if (m_attribute_max_front_derailleur_tooth == attribute_max_front_derailleur_tooth)
        return;

    m_attribute_max_front_derailleur_tooth = attribute_max_front_derailleur_tooth;
    emit attribute_max_front_derailleur_toothChanged(m_attribute_max_front_derailleur_tooth);
}

void PropertyContainer::setAttribute_min_front_derailleur_tooth(PartAttribute attribute_min_front_derailleur_tooth)
{
    if (m_attribute_min_front_derailleur_tooth == attribute_min_front_derailleur_tooth)
        return;

    m_attribute_min_front_derailleur_tooth = attribute_min_front_derailleur_tooth;
    emit attribute_min_front_derailleur_toothChanged(m_attribute_min_front_derailleur_tooth);
}

void PropertyContainer::setAttribute_chain_line(PartAttribute attribute_chain_line)
{
    if (m_attribute_chain_line == attribute_chain_line)
        return;

    m_attribute_chain_line = attribute_chain_line;
    emit attribute_chain_lineChanged(m_attribute_chain_line);
}

void PropertyContainer::setAttribute_crank_speed(PartAttribute attribute_crank_speed)
{
    if (m_attribute_crank_speed == attribute_crank_speed)
        return;

    m_attribute_crank_speed = attribute_crank_speed;
    emit attribute_crank_speedChanged(m_attribute_crank_speed);
}

void PropertyContainer::setAttribute_front_derailleur_mount(PartAttribute attribute_front_derailleur_mount)
{
    if (m_attribute_front_derailleur_mount == attribute_front_derailleur_mount)
        return;

    m_attribute_front_derailleur_mount = attribute_front_derailleur_mount;
    emit attribute_front_derailleur_mountChanged(m_attribute_front_derailleur_mount);
}

void PropertyContainer::setAttribute_max_crank_tooth(PartAttribute attribute_max_crank_tooth)
{
    if (m_attribute_max_crank_tooth == attribute_max_crank_tooth)
        return;

    m_attribute_max_crank_tooth = attribute_max_crank_tooth;
    emit attribute_max_crank_toothChanged(m_attribute_max_crank_tooth);
}

void PropertyContainer::setAttribute_front_disc_size(PartAttribute attribute_front_disc_size)
{
    if (m_attribute_front_disc_size == attribute_front_disc_size)
        return;

    m_attribute_front_disc_size = attribute_front_disc_size;
    emit attribute_front_disc_sizeChanged(m_attribute_front_disc_size);
}

void PropertyContainer::setAttribute_rear_disc_size(PartAttribute attribute_rear_disc_size)
{
    if (m_attribute_rear_disc_size == attribute_rear_disc_size)
        return;

    m_attribute_rear_disc_size = attribute_rear_disc_size;
    emit attribute_rear_disc_sizeChanged(m_attribute_rear_disc_size);
}

void PropertyContainer::setAttribute_front_disc_mount(PartAttribute attribute_front_disc_mount)
{
    if (m_attribute_front_disc_mount == attribute_front_disc_mount)
        return;

    m_attribute_front_disc_mount = attribute_front_disc_mount;
    emit attribute_front_disc_mountChanged(m_attribute_front_disc_mount);
}

void PropertyContainer::setAttribute_rear_disc_mount(PartAttribute attribute_rear_disc_mount)
{
    if (m_attribute_rear_disc_mount == attribute_rear_disc_mount)
        return;

    m_attribute_rear_disc_mount = attribute_rear_disc_mount;
    emit attribute_rear_disc_mountChanged(m_attribute_rear_disc_mount);
}

void PropertyContainer::setAttribute_front_disc_brake_mount(PartAttribute attribute_front_disc_brake_mount)
{
    if (m_attribute_front_disc_brake_mount == attribute_front_disc_brake_mount)
        return;

    m_attribute_front_disc_brake_mount = attribute_front_disc_brake_mount;
    emit attribute_front_disc_brake_mountChanged(m_attribute_front_disc_brake_mount);
}

void PropertyContainer::setAttribute_rear_disc_brake_mount(PartAttribute attribute_rear_disc_brake_mount)
{
    if (m_attribute_rear_disc_brake_mount == attribute_rear_disc_brake_mount)
        return;

    m_attribute_rear_disc_brake_mount = attribute_rear_disc_brake_mount;
    emit attribute_rear_disc_brake_mountChanged(m_attribute_rear_disc_brake_mount);
}

void PropertyContainer::setAttribute_front_vbrake_mount(PartAttribute attribute_front_vbrake_mount)
{
    if (m_attribute_front_vbrake_mount == attribute_front_vbrake_mount)
        return;

    m_attribute_front_vbrake_mount = attribute_front_vbrake_mount;
    emit attribute_front_vbrake_mountChanged(m_attribute_front_vbrake_mount);
}

void PropertyContainer::setAttribute_rear_vbrake_mount(PartAttribute attribute_rear_vbrake_mount)
{
    if (m_attribute_rear_vbrake_mount == attribute_rear_vbrake_mount)
        return;

    m_attribute_rear_vbrake_mount = attribute_rear_vbrake_mount;
    emit attribute_rear_vbrake_mountChanged(m_attribute_rear_vbrake_mount);
}

void PropertyContainer::setSelected_front_brake(PartAttribute selected_front_brake)
{
    if (m_selected_front_brake == selected_front_brake)
        return;

    m_selected_front_brake = selected_front_brake;
    emit selected_front_brakeChanged(m_selected_front_brake);
}

void PropertyContainer::setSelected_rear_brake(PartAttribute selected_rear_brake)
{
    if (m_selected_rear_brake == selected_rear_brake)
        return;

    m_selected_rear_brake = selected_rear_brake;
    emit selected_rear_brakeChanged(m_selected_rear_brake);
}

PartAttribute PropertyContainer::selected_front_brake() const
{
    return m_selected_front_brake;
}
