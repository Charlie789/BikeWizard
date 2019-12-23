#ifndef MODELHANDLER_H
#define MODELHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMap>
#include <QSqlTableModel>
#include <QPair>
#include <QStandardItemModel>
#include "customtypes.h"

class ModelHandler : public QObject
{
    Q_OBJECT

    typedef QPair<CustomTypes::AttributeName, QString> PartAttribute;

    Q_PROPERTY(PartAttribute attribute_wheel_size READ attribute_wheel_size WRITE setAttribute_wheel_size NOTIFY attribute_wheel_sizeChanged);
    Q_PROPERTY(PartAttribute attribute_axle_type_front READ attribute_axle_type_front WRITE setAttribute_axle_type_front NOTIFY attribute_axle_type_frontChanged);

public:
    explicit ModelHandler(QObject *parent = nullptr);

    PartAttribute attribute_wheel_size() const;
    PartAttribute attribute_axle_type_front() const;

private:
    QMap<CustomTypes::PartType, QString> m_map_part_table;
    QMap<CustomTypes::PartType, QList<QString>> m_map_part_property_list;
    QMap<CustomTypes::AttributeName, int> m_map_attribute_counter;

    QSqlTableModel* m_model_frame;
    QSqlTableModel* m_model_fork;
    QSqlTableModel* m_model_front_wheel;

    QStandardItemModel m_model_selected_parts;

    void property_handler(PartAttribute attribute);

    PartAttribute m_attribute_wheel_size;
    PartAttribute m_attribute_axle_type_front;

signals:
    void map_part_table_ready(QMap<CustomTypes::PartType, QString> map_part);
    void selected_parts_model_ready(QStandardItemModel* model);
    void part_deleted(CustomTypes::PartType part_type);

    void attribute_wheel_sizeChanged(PartAttribute attribute_wheel_size);
    void attribute_axle_type_frontChanged(PartAttribute attribute_axle_type_front);

public slots:
    void init();
    void set_model(CustomTypes::PartType part_type, QSqlTableModel* model);
    void set_properties(CustomTypes::PartType part_type, QList<QString> *list);
    void clean_properties(CustomTypes::PartType part_type);
    void set_selected_part(CustomTypes::PartType part_type, QList<QString> *list);
    void delete_selected_part(CustomTypes::PartType part_type);
    QString create_filter(CustomTypes::PartType part_type);

    void setAttribute_wheel_size(PartAttribute attribute_wheel_size);
    void setAttribute_axle_type_front(PartAttribute attribute_axle_type_front);

private slots:
    void fill_selected_parts_model(QMap<CustomTypes::PartType, QString> map_part);
};

#endif // MODELHANDLER_H
