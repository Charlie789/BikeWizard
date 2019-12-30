#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

namespace CustomTypes {
    enum PartType {
        PartFrame,
        PartFork,
        PartFrontWheel,
        PartRearWheel,
        PartHeadset,
        PartHandlebar,
        PartStem,
        PartSeatpost,
        PartSaddle,
        PartTire,
        PartInnerTube,
        PartBB,
        PartGrip,
        PartCassette,
        PartChain,
        PartRearDerailleur,
        PartFrontDerailleur,
        PartCrank,
        PartFrontShifter,
        PartRearShifter,
        PartFrontDisc,
        PartRearDisc,
        PartFrontDiscBrakeSet,
        PartRearDiscBrakeSet,
        PartFrontVBrake,
        PartRearVBrake,
        PartFrontLever,
        PartRearLever
    };

    enum AttributeName {
        AttributeWheelSize,
        AttributeAxleTypeFront,
        AttributeAxleTypeRear,
        AttributeSteererTubeDiameter,
        AttributeHeadset,
        AttributeHandlebarDiameter,
        AttributeStemSteererTubeDiameter,
        AttributeSeatpostDiameter,
        AttributeSaddleMounting,
        AttributeTireWidth,
        AttributeBBType,
        AttributeBBAxisType,
        AttributeBBAxisLength,
        AttributeChainSpeed,
        AttributeMinSprocketTooth,
        AttributeMaxSprocketTooth,
        AttributeMinDerailleurTooth,
        AttributeMaxDerailleurTooth,
        AttributeMaxFrontDerailleurTooth,
        AttributeMinFrontDerailleurTooth,
        AttributeMaxCrankTooth,
        AttributeChainLine,
        AttributeCrankSpeed,
        AttributeFrontDerailleurMount,
        AttributeFrontDiscSize,
        AttributeRearDiscSize,
        AttributeFrontDiscMount,
        AttributeRearDiscMount,
        AttributeFrontDiscBrakeMount,
        AttributeRearDiscBrakeMount,
        AttributeFrontVBrakeMount,
        AttributeRearVBrakeMount,
        AttributeSelectedFrontBrake,
        AttributeSelectedRearBrake,
    };

}

namespace TableProperties {
    namespace SelectedParts {
        enum Columns {
            ColumnPartName = 1,
            ColumnPartType,
            ColumnPartID
        };
    }
}

#endif // CUSTOMTYPES_H
