#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

namespace CustomTypes {
    enum PartType {
        PartFrame = 1,
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
            ColumnPartPrice,
            ColumnPartType,
            ColumnPartID
        };
    }
    namespace Parts {
        enum Columns {
            ColumnCompany,
            ColumnName,
            ColumnID
        };
    }
    namespace Bike {
        enum Columns {
            ColumnFrame = 1,
            ColumnFork,
            ColumnFrontWheel,
            ColumnRearWheel,
            ColumnHeadset,
            ColumnHandlebar,
            ColumnStem,
            ColumnSeatpost,
            ColumnSaddle,
            ColumnTire,
            ColumnInnerTube,
            ColumnBB,
            ColumnGrip,
            ColumnCassette,
            ColumnChain,
            ColumnRearDerailleur,
            ColumnFrontDerailleur,
            ColumnCrank,
            ColumnFrontShifter,
            ColumnRearShifter,
            ColumnFrontDisc,
            ColumnRearDisc,
            ColumnFrontDiscBrakeSet,
            ColumnRearDiscBrakeSet,
            ColumnFrontVBrake,
            ColumnRearVBrake,
            ColumnFrontLever,
            ColumnRearLever
        };
    }
}

#endif // CUSTOMTYPES_H
