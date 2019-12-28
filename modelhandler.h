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
    Q_PROPERTY(PartAttribute attribute_axle_type_rear READ attribute_axle_type_rear WRITE setAttribute_axle_type_rear NOTIFY attribute_axle_type_rearChanged);
    Q_PROPERTY(PartAttribute attribute_steerer_tube_diameter READ attribute_steerer_tube_diameter WRITE setAttribute_steerer_tube_diameter NOTIFY attribute_steerer_tube_diameterChanged);
    Q_PROPERTY(PartAttribute attribute_headset READ attribute_headset WRITE setAttribute_headset NOTIFY attribute_headsetChanged);
    Q_PROPERTY(PartAttribute attribute_handlebar_diameter READ attribute_handlebar_diameter WRITE setAttribute_handlebar_diameter NOTIFY attribute_handlebar_diameterChanged);
    Q_PROPERTY(PartAttribute attribute_stem_steerer_tube_diameter READ attribute_stem_steerer_tube_diameter WRITE setAttribute_stem_steerer_tube_diameter NOTIFY attribute_stem_steerer_tube_diameterChanged);
    Q_PROPERTY(PartAttribute attribute_seatpost_diameter READ attribute_seatpost_diameter WRITE setAttribute_seatpost_diameter NOTIFY attribute_seatpost_diameterChanged);
    Q_PROPERTY(PartAttribute attribute_saddle_mounting READ attribute_saddle_mounting WRITE setAttribute_saddle_mounting NOTIFY attribute_saddle_mountingChanged);
    Q_PROPERTY(PartAttribute attribute_tire_width READ attribute_tire_width WRITE setAttribute_tire_width NOTIFY attribute_tire_widthChanged);
    Q_PROPERTY(PartAttribute attribute_bb_type READ attribute_bb_type WRITE setAttribute_bb_type NOTIFY attribute_bb_typeChanged);
    Q_PROPERTY(PartAttribute attribute_bb_axis_type READ attribute_bb_axis_type WRITE setAttribute_bb_axis_type NOTIFY attribute_bb_axis_typeChanged);
    Q_PROPERTY(PartAttribute attribute_bb_axis_length READ attribute_bb_axis_length WRITE setAttribute_bb_axis_length NOTIFY attribute_bb_axis_lengthChanged);

public:
    explicit ModelHandler(QObject *parent = nullptr);

    PartAttribute attribute_wheel_size() const;
    PartAttribute attribute_axle_type_front() const;
    PartAttribute attribute_axle_type_rear() const;
    PartAttribute attribute_steerer_tube_diameter() const;
    PartAttribute attribute_headset() const;
    PartAttribute attribute_handlebar_diameter() const;
    PartAttribute attribute_stem_steerer_tube_diameter() const;
    PartAttribute attribute_seatpost_diameter() const;
    PartAttribute attribute_saddle_mounting() const;
    PartAttribute attribute_tire_width() const;
    PartAttribute attribute_bb_type() const;
    PartAttribute attribute_bb_axis_type() const;
    PartAttribute attribute_bb_axis_length() const;

private:
    QMap<CustomTypes::PartType, QString> m_map_part_table;
    QMap<CustomTypes::PartType, QList<QString>> m_map_part_property_list;
    QMap<CustomTypes::AttributeName, int> m_map_attribute_counter;
    QMap<CustomTypes::PartType, QMap<CustomTypes::AttributeName, int>> m_map_column_index;

    QSqlTableModel* m_model_frame;
    QSqlTableModel* m_model_fork;
    QSqlTableModel* m_model_front_wheel;
    QSqlTableModel* m_model_rear_wheel;
    QSqlTableModel* m_model_headset;
    QSqlTableModel* m_model_handlebar;
    QSqlTableModel* m_model_stem;
    QSqlTableModel* m_model_seatpost;
    QSqlTableModel* m_model_saddle;
    QSqlTableModel* m_model_tire;
    QSqlTableModel* m_model_inner_tube;
    QSqlTableModel* m_model_bb;
    QSqlTableModel* m_model_grip;

    QStandardItemModel m_model_selected_parts;

    void filter_handler(PartAttribute);

    PartAttribute m_attribute_wheel_size;
    PartAttribute m_attribute_axle_type_front;
    PartAttribute m_attribute_axle_type_rear;
    PartAttribute m_attribute_steerer_tube_diameter;
    PartAttribute m_attribute_headset;
    PartAttribute m_attribute_handlebar_diameter;
    PartAttribute m_attribute_stem_steerer_tube_diameter;
    PartAttribute m_attribute_seatpost_diameter;
    PartAttribute m_attribute_saddle_mounting;
    PartAttribute m_attribute_tire_width;
    PartAttribute m_attribute_bb_type;
    PartAttribute m_attribute_bb_axis_type;
    PartAttribute m_attribute_bb_axis_length;

signals:
    void map_part_table_ready(QMap<CustomTypes::PartType, QString> map_part);
    void selected_parts_model_ready(QStandardItemModel* model);
    void part_deleted(CustomTypes::PartType part_type);

    void attribute_wheel_sizeChanged(PartAttribute attribute_wheel_size);
    void attribute_axle_type_frontChanged(PartAttribute attribute_axle_type_front);
    void attribute_axle_type_rearChanged(PartAttribute attribute_axle_type_rear);
    void attribute_steerer_tube_diameterChanged(PartAttribute attribute_steerer_tube_diameter);
    void attribute_headsetChanged(PartAttribute attribute_headset);
    void attribute_handlebar_diameterChanged(PartAttribute attribute_handlebar_diameter);
    void attribute_stem_steerer_tube_diameterChanged(PartAttribute attribute_stem_steerer_tube_diameter);
    void attribute_seatpost_diameterChanged(PartAttribute attribute_seatpost_diameter);
    void attribute_saddle_mountingChanged(PartAttribute attribute_saddle_mounting);
    void attribute_tire_widthChanged(PartAttribute attribute_tire_width);
    void attribute_bb_typeChanged(PartAttribute attribute_bb_type);
    void attribute_bb_axis_typeChanged(PartAttribute attribute_bb_axis_type);
    void attribute_bb_axis_lengthChanged(PartAttribute attribute_bb_axis_length);

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
    void setAttribute_axle_type_rear(PartAttribute attribute_axle_type_rear);
    void setAttribute_steerer_tube_diameter(PartAttribute attribute_steerer_tube_diameter);
    void setAttribute_headset(PartAttribute attribute_headset);
    void setAttribute_handlebar_diameter(PartAttribute attribute_handlebar_diameter);
    void setAttribute_stem_steerer_tube_diameter(PartAttribute attribute_stem_steerer_tube_diameter);
    void setAttribute_seatpost_diameter(PartAttribute attribute_seatpost_diameter);
    void setAttribute_saddle_mounting(PartAttribute attribute_saddle_mounting);
    void setAttribute_tire_width(PartAttribute attribute_tire_width);
    void setAttribute_bb_type(PartAttribute attribute_bb_type);
    void setAttribute_bb_axis_type(PartAttribute attribute_bb_axis_type);
    void setAttribute_bb_axis_length(PartAttribute attribute_bb_axis_length);

private slots:
    void fill_selected_parts_model(QMap<CustomTypes::PartType, QString> map_part);
};

#endif // MODELHANDLER_H
