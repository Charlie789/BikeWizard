#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

#include <QMap>

namespace CustomTypes {
    enum PartType{
        PartFrame,
        PartFork
    };

    enum AttributeName{
        AttributeWheelSize
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
