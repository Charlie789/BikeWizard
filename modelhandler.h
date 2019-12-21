#ifndef MODELHANDLER_H
#define MODELHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMap>
#include <QSqlTableModel>
#include <QPair>
#include "customtypes.h"

class ModelHandler : public QObject
{
    Q_OBJECT

    typedef QPair<CustomTypes::AttributeName, QString> PartAttribute;

    Q_PROPERTY(PartAttribute attribute_wheel_size READ attribute_wheel_size WRITE setAttribute_wheel_size NOTIFY attribute_wheel_sizeChanged);

public:
    explicit ModelHandler(QObject *parent = nullptr);

    PartAttribute attribute_wheel_size() const;

private:
    QMap<CustomTypes::PartType, QString> m_map_part_table;
    QMap<CustomTypes::PartType, QList<QString>> m_map_part_property_list;

    QSqlTableModel* m_model_frame;
    QSqlTableModel* m_model_fork;

    PartAttribute m_attribute_wheel_size;

    void property_handler(PartAttribute attribute);


signals:
    void attribute_wheel_sizeChanged(PartAttribute attribute_wheel_size);
    void map_part_table_ready(QMap<CustomTypes::PartType, QString> map_part);

public slots:
    void set_filter(QSqlTableModel* model, QString filter);
    void set_properties(CustomTypes::PartType part_type, const QString value);
    void set_model(QSqlTableModel *model, CustomTypes::PartType part_type);
    QString create_filter(CustomTypes::PartType part_type);
    void init();

    void setAttribute_wheel_size(PartAttribute attribute_wheel_size);
};

#endif // MODELHANDLER_H
