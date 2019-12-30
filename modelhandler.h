#ifndef MODELHANDLER_H
#define MODELHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMap>
#include <QSqlTableModel>
#include <QPair>
#include <QStandardItemModel>
#include "customtypes.h"
#include "propertycontainter.h"

class ModelHandler : public QObject
{
    Q_OBJECT

public:
    explicit ModelHandler(QObject *parent = nullptr);

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
    QSqlTableModel* m_model_cassette;
    QSqlTableModel* m_model_chain;
    QSqlTableModel* m_model_rear_derailleur;
    QSqlTableModel* m_model_front_derailleur;
    QSqlTableModel* m_model_crank;
    QSqlTableModel* m_model_front_shifter;
    QSqlTableModel* m_model_rear_shifter;
    QSqlTableModel* m_model_front_disc;
    QSqlTableModel* m_model_rear_disc;
    QSqlTableModel* m_model_front_disc_brake_set;
    QSqlTableModel* m_model_rear_disc_brake_set;
    QSqlTableModel* m_model_front_vbrake;
    QSqlTableModel* m_model_rear_vbrake;
    QSqlTableModel* m_model_front_lever;
    QSqlTableModel* m_model_rear_lever;

    QStandardItemModel m_model_selected_parts;

    PropertyContainer* m_property_container;

signals:
    void map_part_table_ready(QMap<CustomTypes::PartType, QString> map_part);
    void selected_parts_model_ready(QStandardItemModel* model);
    void part_deleted(CustomTypes::PartType part_type);
    void block_part(CustomTypes::PartType part_type);
    void unlock_part(CustomTypes::PartType part_type);
    void property_attribute_list_ready(QList<PartAttribute>);

public slots:
    void init_db();
    void init_properties(PropertyContainer* prop);
    void set_model(CustomTypes::PartType part_type, QSqlTableModel* model);
    void set_properties(CustomTypes::PartType part_type, QList<QString> *list);
    void clean_properties(CustomTypes::PartType part_type);
    void set_selected_part(CustomTypes::PartType part_type, QList<QString> *list);
    void delete_selected_part(CustomTypes::PartType part_type);
    QString create_filter(CustomTypes::PartType part_type);
    void filter_handler(PartAttribute);
    void check_disc_allowed(PartAttribute part_attribute);

private slots:
    void fill_selected_parts_model(QMap<CustomTypes::PartType, QString> map_part);
};

#endif // MODELHANDLER_H
