#include "propertymanager.h"

PropertyManager::PropertyManager(QObject *parent) : QObject(parent)
{

}

void PropertyManager::init_properties(PropertyContainer *property)
{
    m_property_container = property;
}

void PropertyManager::set_properties(QList<PartAttribute> list)
{
    for(int i = 0; i < list.count(); i++){
        switch (list[i].first){

        case CustomTypes::AttributeWheelSize:
            m_property_container->setAttribute_wheel_size(list[i]);
            break;
        case CustomTypes::AttributeAxleTypeFront:
            m_property_container->setAttribute_axle_type_front(list[i]);
            break;
        case CustomTypes::AttributeAxleTypeRear:
            m_property_container->setAttribute_axle_type_rear(list[i]);
            break;
        case CustomTypes::AttributeSteererTubeDiameter:
            m_property_container->setAttribute_steerer_tube_diameter(list[i]);
            break;
        case CustomTypes::AttributeHeadset:
            m_property_container->setAttribute_headset(list[i]);
            break;
        case CustomTypes::AttributeHandlebarDiameter:
            m_property_container->setAttribute_handlebar_diameter(list[i]);
            break;
        case CustomTypes::AttributeStemSteererTubeDiameter:
            m_property_container->setAttribute_stem_steerer_tube_diameter(list[i]);
            break;
        case CustomTypes::AttributeSeatpostDiameter:
            m_property_container->setAttribute_seatpost_diameter(list[i]);
            break;
        case CustomTypes::AttributeSaddleMounting:
            m_property_container->setAttribute_saddle_mounting(list[i]);
            break;
        case CustomTypes::AttributeTireWidth:
            m_property_container->setAttribute_tire_width(list[i]);
            break;
        case CustomTypes::AttributeBBType:
            m_property_container->setAttribute_bb_type(list[i]);
            break;
        case CustomTypes::AttributeBBAxisType:
            m_property_container->setAttribute_bb_axis_type(list[i]);
            break;
        case CustomTypes::AttributeBBAxisLength:
            m_property_container->setAttribute_bb_axis_length(list[i]);
            break;
        case CustomTypes::AttributeChainSpeed:
            m_property_container->setAttribute_chain_speed(list[i]);
            break;
        case CustomTypes::AttributeMinSprocketTooth:
            m_property_container->setAttribute_min_sprocket_tooth(list[i]);
            break;
        case CustomTypes::AttributeMaxSprocketTooth:
            m_property_container->setAttribute_max_sprocket_tooth(list[i]);
            break;
        case CustomTypes::AttributeMinDerailleurTooth:
            m_property_container->setAttribute_min_derailleur_tooth(list[i]);
            break;
        case CustomTypes::AttributeMaxDerailleurTooth:
            m_property_container->setAttribute_max_derailleur_tooth(list[i]);
            break;
        case CustomTypes::AttributeMaxFrontDerailleurTooth:
            m_property_container->setAttribute_max_front_derailleur_tooth(list[i]);
            break;
        case CustomTypes::AttributeMinFrontDerailleurTooth:
            m_property_container->setAttribute_min_front_derailleur_tooth(list[i]);
            break;
        case CustomTypes::AttributeMaxCrankTooth:
            m_property_container->setAttribute_max_crank_tooth(list[i]);
            break;
        case CustomTypes::AttributeChainLine:
            m_property_container->setAttribute_chain_line(list[i]);
            break;
        case CustomTypes::AttributeCrankSpeed:
            m_property_container->setAttribute_crank_speed(list[i]);
            break;
        case CustomTypes::AttributeFrontDerailleurMount:
            m_property_container->setAttribute_front_derailleur_mount(list[i]);
            break;
        case CustomTypes::AttributeFrontDiscSize:
            m_property_container->setAttribute_front_disc_size(list[i]);
            break;
        case CustomTypes::AttributeRearDiscSize:
            m_property_container->setAttribute_rear_disc_size(list[i]);
            break;
        case CustomTypes::AttributeFrontDiscMount:
            m_property_container->setAttribute_front_disc_mount(list[i]);
            break;
        case CustomTypes::AttributeRearDiscMount:
            m_property_container->setAttribute_rear_disc_mount(list[i]);
            break;
        case CustomTypes::AttributeFrontDiscBrakeMount:
            m_property_container->setAttribute_front_disc_brake_mount(list[i]);
            break;
        case CustomTypes::AttributeRearDiscBrakeMount:
            m_property_container->setAttribute_rear_disc_brake_mount(list[i]);
            break;
        case CustomTypes::AttributeFrontVBrakeMount:
            m_property_container->setAttribute_front_vbrake_mount(list[i]);
            break;
        case CustomTypes::AttributeRearVBrakeMount:
            m_property_container->setAttribute_rear_vbrake_mount(list[i]);
            break;
        case CustomTypes::AttributeSelectedFrontBrake:
            m_property_container->setSelected_front_brake(list[i]);
            break;
        case CustomTypes::AttributeSelectedRearBrake:
            m_property_container->setSelected_rear_brake(list[i]);
            break;
        }
    }
}
