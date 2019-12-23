#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

#include <QMap>

namespace CustomTypes {
    enum PartType{
        PartFrame,
        PartFork,
        PartFrontWheel,
        PartRearWheel
    };

    enum AttributeName{
        AttributeWheelSize,
        AttributeAxleTypeFront,
        AttributeAxleTypeRear
    };

}

namespace TableProperties {
    namespace SelectedParts {
        enum Columns{
            ColumnPartName = 1,
            ColumnPartType,
            ColumnPartID
        };
    }
}

#endif // CUSTOMTYPES_H
