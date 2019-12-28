#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

#include <QMap>

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
        PartGrip
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
        AttributeBBAxisLength
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
