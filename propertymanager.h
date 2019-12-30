#ifndef PROPERTYMANAGER_H
#define PROPERTYMANAGER_H

#include <QObject>
#include "propertycontainter.h"
#include "customtypes.h"

class PropertyManager : public QObject
{
    Q_OBJECT
public:
    explicit PropertyManager(QObject *parent = nullptr);

signals:

private:
    PropertyContainer* m_property_container;

public slots:
    void init_properties(PropertyContainer* property);
    void set_properties(QList<PartAttribute> list);

};

#endif // PROPERTYMANAGER_H
